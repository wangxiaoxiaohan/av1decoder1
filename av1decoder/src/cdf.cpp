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
    //解码单个语法元素或者数据，在这个过程中，SymbolValue和SymbolRange已经锁定，只是根据 cdf 数组来查到底是哪个值
    do {
        symbol++; //逐个尝试
        prev = cur;
        f = ( 1 << 15 ) - cdfArray[ symbol ]; //计算范围
        cur = ((sbCtx->SymbolRange >> 8) * (f >> EC_PROB_SHIFT)) >> (7 - EC_PROB_SHIFT); //将概率进行缩放
        cur += EC_MIN_PROB * (N - symbol - 1);//进行修正，保证概率总和为1
    } while ( sbCtx->SymbolValue < cur );
    //更新算术编码的范围 和 输入符号，这只是部分过程，在renormalized过程还要继续更新，
    //  比如sbCtx->SymbolRange = prev - cur; 这个操作，你会发现SymbolRange会变得很小，在renormalized过程
    //会进行放大(左移)操作，SymbolValue也是同理，只不过SymbolValue本身就是是从码流中读出来的待解码的值，
    //后面对他进行的操作也是用新读进来的若干位填满15位
    sbCtx->SymbolRange = prev - cur;
    sbCtx->SymbolValue = sbCtx->SymbolValue - cur; //这里是为什么？为什么不是直接丢掉若干位？还是说编码器端也是这样做的
                                                   //所以默认这样做？             
//renormalized 这个过程会继续读入码流满15位，以便为后续的解码做准备
    int bits = 15 - FloorLog2( sbCtx->SymbolRange );//这解答了以前对于算术编码的一个疑问，如果区间一直划分，岂不是
                                                    //单单表示区间范围的值就会越来越长，解决办法是每次解码一个符号
    sbCtx->SymbolRange <<= bits;                   //就进行扩展，放大区间
   
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