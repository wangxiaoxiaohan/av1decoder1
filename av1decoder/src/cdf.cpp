#include "cdf.h"
#include "common.h"
#include "bitstream.h"

void cdf::initSymbol(SymbolContext *sbCtx,bitSt *bs,int sz){
    sbCtx->numBits = Min( sz * 8, 15);
    sbCtx->buf = readBits(bs,sbCtx->numBits); //????
    sbCtx->paddedBuf  = ( sbCtx->buf << (15 - sbCtx->numBits) );
    sbCtx->SymbolValue =   ((1 << 15) - 1) ^ sbCtx->paddedBuf;
    sbCtx->SymbolRange = 1 << 15;
    sbCtx->SymbolMaxBits = 8 * sz - 15;
}
int cdf::decodeSymbol(SymbolContext *sbCtx,bitSt *bs,uint16_t *cdfArray,int N){

    int cur = sbCtx->SymbolRange;
    int symbol = -1;
    int prev;
    int f;
    do {
        symbol++; //逐个尝试
        prev = cur;
        f = ( 1 << 15 ) - cdfArray[ symbol ]; //计算范围
        cur = ((sbCtx->SymbolRange >> 8) * (f >> EC_PROB_SHIFT)) >> (7 - EC_PROB_SHIFT); //将概率进行缩放
        cur += EC_MIN_PROB * (N - symbol - 1);//进行修正，保证概率总和为1
    } while ( sbCtx->SymbolValue < cur );
    sbCtx->SymbolRange = prev - cur;
    sbCtx->SymbolValue = sbCtx->SymbolValue - cur;
//renormalized
    int bits = 15 - FloorLog2( sbCtx->SymbolRange );
    sbCtx->SymbolRange <<= bits;
    sbCtx->numBits = Min( bits, Max(0, sbCtx->SymbolMaxBits) );
    int newData =  readBits(bs,sbCtx->numBits);
    int paddedData = newData << ( bits - sbCtx->numBits );
    sbCtx->SymbolValue = paddedData ^ ( ( ( sbCtx->SymbolValue + 1 ) << bits ) - 1 );
    sbCtx->SymbolMaxBits -= bits;
//update
    if(sbCtx->isUpdate){
        int rate = 3 + ( cdfArray[ N ] > 15 ) + ( cdfArray[ N ] > 31 ) + Min( FloorLog2( N ), 2 );
        int tmp = 0;
        for (int i = 0; i < N - 1; i++ ) {
            tmp = ( i == symbol ) ? ( 1 << 15 ) : tmp;
            if ( tmp < cdfArray[ i ] ) {
                cdfArray[ i ] -= ( ( cdfArray[ i ] - tmp ) >> rate );
            } else {
                cdfArray[ i ] += ( ( tmp - cdfArray[ i ] ) >> rate );
            }
        }
        cdfArray[ N ] += ( cdfArray[ N ] < 32 );
    }
    return symbol;
}