#include "cdf.h"
#include "header_common.h"
#include "bitstream.h"
#include <string.h>

void Symbol::initSymbol(SymbolContext *sbCtx,bitSt *bs,int sz){

    sbCtx->numBits = Min( sz * 8, 15);
    sbCtx->buf = readBits(bs,sbCtx->numBits); //????
    
    //printf("sbCtx->buf %d\n",sbCtx->buf);
    sbCtx->paddedBuf  = ( sbCtx->buf << (15 - sbCtx->numBits) );
    //printf("sbCtx->paddedBuf %d\n",sbCtx->paddedBuf);
    sbCtx->SymbolValue =   ((1 << 15) - 1) ^ sbCtx->paddedBuf;
    //printf("sbCtx->SymbolValue %d\n",sbCtx->SymbolValue);
    sbCtx->SymbolRange = 1 << 15;
    sbCtx->SymbolMaxBits = 8 * sz - 15;
}
/*
void Symbol::exit_symbol(SymbolContext *sbCtx,bitSt *bs,int TileNum,AV1DecodeContext *av1Ctx){
    if(sbCtx->SymbolMaxBits < -14 )
        return;
    int trailingBitPosition = get_position(bs) - Min(15, sbCtx->SymbolMaxBits + 15);
    readBits(bs,Max(0, sbCtx->SymbolMaxBits));
    int paddingEndPosition = get_position(bs);
    if(!trailingBitPosition == 1)
        return;
    
    //待做 1
    //It is a requirement of bitstream conformance that the bit at position x is equal to 0 for values of x strictly between
    //trailingBitPosition and paddingEndPosition.
    
    //待做 2 保存 在解码过程中 更新过的cdf ，frame_end_update_cdf() 里面会用
    frameHeader *frameHdr = &av1Ctx->currentFrame->frameHdr;
    if(frameHdr->disable_frame_end_update_cdf == 0 &&
        TileNum == frameHdr->tile_info.context_update_tile_id){
        copyCdf(&av1Ctx->tileSavedCdf,&av1Ctx->currentFrame->cdfCtx,av1Ctx); //?
    }
    

}
void Symbol::frame_end_update_cdf(AV1DecodeContext *av1Ctx){
    copyCdf(&av1Ctx->currentFrame->cdfCtx,&av1Ctx->tileSavedCdf,av1Ctx);
}*/
int Symbol::read_literal(SymbolContext *sbCtx,bitSt *bs,int n){

    int x = 0;
    for (int  i = 0 ; i < n; i++ ) {
        x = 2 * x + decodeSymbolBool( sbCtx,bs);
    }
    return x;
}
int Symbol::decodeSymbolBool(SymbolContext *sbCtx,bitSt *bs){
    uint16_t cdf[3];
    cdf[ 0 ] = 1 << 14;
    cdf[ 1 ] = 1 << 15;
    cdf[ 2 ] = 0;
    return decodeSymbol(sbCtx,bs,cdf,3);

}
int Symbol::readNS(SymbolContext *sbCtx,bitSt *bs,int n ) {
    int w = FloorLog2(n) + 1;
    int m = (1 << w) - n;
    int v = read_literal(sbCtx,bs,w-1); // L(w - 1)
    if (v < m)
        return v;
    int extra_bit = read_literal(sbCtx,bs,1); // L(1)
    return (v << 1) - m + extra_bit;
}

int Symbol::decodeSymbol(SymbolContext *sbCtx,bitSt *bs,uint16_t *cdfArray,int N){

    N -= 1;//用的地方都 用错了 ，暂时这里改
    int cur = sbCtx->SymbolRange;
    int symbol = -1;
    int prev;
    int f;
    //解码单个语法元素或者数据，在这个过程中，
    //SymbolValue和SymbolRange是上次解码的时候已经定下来的输入值
    //SymbolValue是待解码的符号，也就是源数据，SymbolRange是算术编码的范围
    //在loop中根据 cdf 数组来查到底是哪个值
    // cur 代表当前
   // printf("SymbolValue %d SymbolRange %d\n",sbCtx->SymbolValue,sbCtx->SymbolRange);
    do {
        symbol++; //逐个尝试
        prev = cur;
        f = ( 1 << 15 ) - cdfArray[ symbol ]; //计算范围
        cur = ((sbCtx->SymbolRange >> 8) * (f >> EC_PROB_SHIFT)) >> (7 - EC_PROB_SHIFT); //将概率进行缩放
        cur += EC_MIN_PROB * (N - symbol - 1);//进行修正，保证概率总和为1
        if(symbol >= N){
            printf("symbol out of range\n");
        }
        //printf("curr %d symbol %d cdfArray[ symbol ] %d \n",cur,symbol,cdfArray[ symbol ]);
    } while ( sbCtx->SymbolValue < cur );
    //更新算术编码的范围 和 输入符号，这只是部分过程，在renormalized过程还要继续更新，
    //  比如sbCtx->SymbolRange = prev - cur; 这个操作，你会发现SymbolRange会变得很小，在renormalized过程
    //会进行放大(左移)操作，
    //这解答了以前对于算术编码的一个疑问，如果区间一直划分，岂不是
     //单单表示区间范围的值就会越来越长，解决办法是每次解码一个符号就进行扩展，放大区间
    //SymbolValue也是同理，只不过SymbolValue本身就是是从码流中读出来的待解码的值，
    //后面对他进行的操作也是用新读进来的若干位填满15位
    sbCtx->SymbolRange = prev - cur; //这里的时候 ，SymbolRange就已经更新为SymbolValue 所在那个小区域了
                                      
    sbCtx->SymbolValue = sbCtx->SymbolValue - cur; //这里是为什么？为什么不是直接丢掉若干位？还是说编码器端也是这样做的
                                                   //所以默认这样做？    
    //printf("SymbolValue %d SymbolRange %d\n",sbCtx->SymbolValue,sbCtx->SymbolRange);
    

//renormalized 这个过程会继续读入码流满15位，以便为后续的解码做准备
    int bits = 15 - FloorLog2( sbCtx->SymbolRange ); //需要继续读进来的数据位数
  //  printf("SymbolRange 1  %d\n",sbCtx->SymbolRange);
    sbCtx->SymbolRange = sbCtx->SymbolRange << bits;
 //  printf("SymbolRange 2  %d\n",sbCtx->SymbolRange);
    sbCtx->numBits = Min( bits, Max(0, sbCtx->SymbolMaxBits) ); //修正需要读取位数

    int newData =  readBits(bs,sbCtx->numBits); //读取，接下来几步将新读进来的数据和之前剩下的组合起来，凑满15位
   // printf("newData  %d\n",newData);

    int paddedData = newData << ( bits - sbCtx->numBits );
   // printf("paddedData  %d\n",paddedData);
 //   printf("SymbolValue 1  %d\n",sbCtx->SymbolValue);
    sbCtx->SymbolValue = paddedData ^ ( ( ( sbCtx->SymbolValue + 1 ) << bits ) - 1 );
//    printf("SymbolValue 2  %d\n",sbCtx->SymbolValue);
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
int Symbol::decode_signed_subexp_with_ref_bool(SymbolContext *sbCtx,bitSt *bs,int low, int high, int k, int r)
{
	int x = decode_unsigned_subexp_with_ref_bool(sbCtx,bs, high - low, k, r - low);
	return x + low;
}
int Symbol::decode_unsigned_subexp_with_ref_bool(SymbolContext *sbCtx,bitSt *bs,int mx, int k, int r)
{
	int v = decode_subexp_bool(sbCtx,bs,mx, k);
	if ((r << 1) <= mx)
	{
		return inverse_recenter(r, v);
	}
	else
	{
		return mx - 1 - inverse_recenter(mx - 1 - r, v);
	}
}
int Symbol::decode_subexp_bool(SymbolContext *sbCtx,bitSt *bs,int numSyms,int k)
{
    int i = 0;
    int mk = 0;
    while (1)
    {
        int b2 = i ? (k + i - 1) : k;
        int a = 1 << b2;
        if (numSyms <= mk + 3 * a)
        {
            int subexp_unif_bools = readNS(sbCtx,bs,numSyms - mk); // NS(numSyms - mk);
            return subexp_unif_bools + mk;
        }
        else
        {
            int subexp_more_bools = read_literal(sbCtx,bs,1); // L(1)
            if (subexp_more_bools)
            {
                i++ ;
                mk += a;
            }
            else
            {
                int subexp_bools = read_literal(sbCtx,bs,b2); // L(b2)
                return subexp_bools + mk;
            }
        }
    }
}
