#include "cdf.h"
#include "header_common.h"
#include "bitstream.h"
#include <string.h>
int copyCdf(CDFArrays *dst,CDFArrays *src,AV1DecodeContext *av1Ctx){
   	memcpy(dst->Intra_Frame_Y_Mode,src->Intra_Frame_Y_Mode,sizeof(Default_Intra_Frame_Y_Mode_Cdf)/sizeof(uint16_t));
    memcpy(dst->Y_Mode,src->Y_Mode,sizeof(Default_Y_Mode_Cdf)/sizeof(uint16_t));
    memcpy(dst->Uv_Mode_Cfl_Not_Allowed,src->Uv_Mode_Cfl_Not_Allowed, sizeof(Default_Uv_Mode_Cfl_Not_Allowed_Cdf)/sizeof(uint16_t));
    memcpy(dst->Uv_Mode_Cfl_Allowed,src->Uv_Mode_Cfl_Allowed ,sizeof(Default_Uv_Mode_Cfl_Allowed_Cdf)/sizeof(uint16_t));

    memcpy(dst->Angle_Delta,src->Angle_Delta,sizeof(Default_Angle_Delta_Cdf)/sizeof(uint16_t));
    memcpy(dst->Intrabc,src->Intrabc,sizeof(Default_Intrabc_Cdf)/sizeof(uint16_t));

    memcpy(dst->Partition_W8,src->Partition_W8,sizeof(Default_Partition_W8_Cdf)/sizeof(uint16_t));
    memcpy(dst->Partition_W16,src->Partition_W16 ,sizeof(Default_Partition_W16_Cdf)/sizeof(uint16_t));
    memcpy(dst->Partition_W32,src->Partition_W32 ,sizeof(Default_Partition_W32_Cdf)/sizeof(uint16_t));
    memcpy(dst->Partition_W64,src->Partition_W64 ,sizeof(Default_Partition_W64_Cdf)/sizeof(uint16_t));
    memcpy(dst->Partition_W128,src->Partition_W128 ,sizeof(Default_Partition_W128_Cdf)/sizeof(uint16_t));

    memcpy(dst->Tx_8x8,src->Tx_8x8,sizeof(Default_Tx_8x8_Cdf)/sizeof(uint16_t));
    memcpy(dst->Tx_16x16,src->Tx_16x16,sizeof(Default_Tx_16x16_Cdf)/sizeof(uint16_t));
    memcpy(dst->Tx_32x32,src->Tx_32x32,sizeof(Default_Tx_32x32_Cdf)/sizeof(uint16_t));
    memcpy(dst->Tx_64x64,src->Tx_64x64,sizeof(Default_Tx_64x64_Cdf)/sizeof(uint16_t));

    memcpy(dst->Txfm_Split,src->Txfm_Split,sizeof(Default_Txfm_Split_Cdf)/sizeof(uint16_t));
    memcpy(dst->Filter_Intra_Mode,src->Filter_Intra_Mode,sizeof(Default_Filter_Intra_Mode_Cdf)/sizeof(uint16_t));
    memcpy(dst->Filter_Intra,src->Filter_Intra,sizeof(Default_Filter_Intra_Cdf)/sizeof(uint16_t));
    memcpy(dst->Segment_Id,src->Segment_Id,sizeof(Default_Segment_Id_Cdf)/sizeof(uint16_t));
    memcpy(dst->Segment_Id_Predicted,src->Segment_Id_Predicted,sizeof(Default_Segment_Id_Predicted_Cdf)/sizeof(uint16_t));
    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        for(int j = 0 ; i < 2 ; j++){
            memcpy(dst->Mv_Class0_Hp[i][j],src->Mv_Class0_Hp[i][j],sizeof(Default_Mv_Class0_Hp_Cdf)/sizeof(uint16_t));
            memcpy(dst->Mv_Hp[i][j],src->Mv_Hp[i][j],sizeof(Default_Mv_Hp_Cdf)/sizeof(uint16_t));
            memcpy(dst->Mv_Sign[i][j],src->Mv_Sign[i][j],sizeof(Default_Mv_Sign_Cdf)/sizeof(uint16_t));
            memcpy(dst->Mv_Bit[i][j],src->Mv_Bit[i][j],sizeof(Default_Mv_Bit_Cdf)/sizeof(uint16_t));
            memcpy(dst->Mv_Class0_Bit[i][j],src->Mv_Class0_Bit[i][j],sizeof(Default_Mv_Class0_Bit_Cdf)/sizeof(uint16_t));
        }
    }
    memcpy(dst->New_Mv,src->New_Mv,sizeof(Default_New_Mv_Cdf)/sizeof(uint16_t));
    memcpy(dst->Zero_Mv,src->Zero_Mv,sizeof(Default_Zero_Mv_Cdf)/sizeof(uint16_t));
    memcpy(dst->Ref_Mv,src->Ref_Mv,sizeof(Default_Ref_Mv_Cdf)/sizeof(uint16_t));
    memcpy(dst->Drl_Mode,src->Drl_Mode,sizeof(Default_Drl_Mode_Cdf)/sizeof(uint16_t));
    memcpy(dst->Is_Inter,src->Is_Inter,sizeof(Default_Is_Inter_Cdf)/sizeof(uint16_t));

    memcpy(dst->Is_Inter,src->Is_Inter,sizeof(Default_Is_Inter_Cdf)/sizeof(uint16_t));
    memcpy(dst->Comp_Mode,src->Comp_Mode,sizeof(Default_Comp_Mode_Cdf)/sizeof(uint16_t));
    memcpy(dst->Skip_Mode,src->Skip_Mode,sizeof(Default_Skip_Mode_Cdf)/sizeof(uint16_t));
    memcpy(dst->Skip,src->Skip,sizeof(Default_Skip_Cdf)/sizeof(uint16_t));
    memcpy(dst->Comp_Ref,src->Comp_Ref,sizeof(Default_Comp_Ref_Cdf)/sizeof(uint16_t));

    memcpy(dst->Comp_Bwd_Ref,src->Comp_Bwd_Ref,sizeof(Default_Comp_Bwd_Ref_Cdf)/sizeof(uint16_t));
    memcpy(dst->Single_Ref,src->Single_Ref,sizeof(Default_Single_Ref_Cdf)/sizeof(uint16_t));
    memcpy(dst->Compound_Mode,src->Compound_Mode,sizeof(Default_Compound_Mode_Cdf)/sizeof(uint16_t));

    memcpy(dst->Interp_Filter,src->Interp_Filter,sizeof(Default_Interp_Filter_Cdf)/sizeof(uint16_t));
    memcpy(dst->Motion_Mode,src->Motion_Mode,sizeof(Default_Motion_Mode_Cdf)/sizeof(uint16_t));

    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        memcpy(dst->Mv_Joint[i],src->Mv_Joint[i],sizeof(Default_Mv_Joint_Cdf)/sizeof(uint16_t));
        memcpy(dst->Mv_Class[i],src->Mv_Class[i],sizeof(Default_Mv_Class_Cdf)/sizeof(uint16_t));
        memcpy(dst->Mv_Class0_Fr[i],src->Mv_Class0_Fr[i],sizeof(Default_Mv_Class0_Fr_Cdf)/sizeof(uint16_t));
        memcpy(dst->Mv_Fr[i],src->Mv_Fr[i],sizeof(Default_Mv_Fr_Cdf)/sizeof(uint16_t));
    }
    memcpy(dst->Palette_Y_Size,src->Palette_Y_Size,sizeof(Default_Palette_Y_Size_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Uv_Size,src->Palette_Uv_Size,sizeof(Default_Palette_Uv_Size_Cdf)/sizeof(uint16_t));

    memcpy(dst->Palette_Size_2_Y_Color,src->Palette_Size_2_Y_Color,sizeof(Default_Palette_Size_2_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_3_Y_Color,src->Palette_Size_3_Y_Color,sizeof(Default_Palette_Size_3_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_4_Y_Color,src->Palette_Size_4_Y_Color,sizeof(Default_Palette_Size_4_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_5_Y_Color,src->Palette_Size_5_Y_Color,sizeof(Default_Palette_Size_5_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_6_Y_Color,src->Palette_Size_6_Y_Color,sizeof(Default_Palette_Size_6_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_7_Y_Color,src->Palette_Size_7_Y_Color,sizeof(Default_Palette_Size_7_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_8_Y_Color,src->Palette_Size_8_Y_Color,sizeof(Default_Palette_Size_8_Y_Color_Cdf)/sizeof(uint16_t));


    memcpy(dst->Palette_Size_2_Uv_Color,src->Palette_Size_2_Uv_Color,sizeof(Default_Palette_Size_2_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_3_Uv_Color,src->Palette_Size_3_Uv_Color,sizeof(Default_Palette_Size_3_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_4_Uv_Color,src->Palette_Size_4_Uv_Color,sizeof(Default_Palette_Size_4_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_5_Uv_Color,src->Palette_Size_5_Uv_Color,sizeof(Default_Palette_Size_5_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_6_Uv_Color,src->Palette_Size_6_Uv_Color,sizeof(Default_Palette_Size_6_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_7_Uv_Color,src->Palette_Size_7_Uv_Color,sizeof(Default_Palette_Size_7_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(dst->Palette_Size_8_Uv_Color,src->Palette_Size_8_Uv_Color,sizeof(Default_Palette_Size_8_Uv_Color_Cdf)/sizeof(uint16_t));

    memcpy(dst->Delta_Q,src->Delta_Q,sizeof(Default_Delta_Q_Cdf)/sizeof(uint16_t));
    memcpy(dst->Delta_Lf,src->Delta_Lf,sizeof(Default_Delta_Lf_Cdf)/sizeof(uint16_t));

    for(int i = 0 ; i < FRAME_LF_COUNT ; i++)
        memcpy(dst->Delta_Lf_Muti[i],src->Delta_Lf_Muti[i],sizeof(Default_Delta_Lf_Cdf)/sizeof(uint16_t));

    memcpy(dst->Intra_Tx_Type_Set1,src->Intra_Tx_Type_Set1,sizeof(Default_Intra_Tx_Type_Set1_Cdf)/sizeof(uint16_t));
    memcpy(dst->Intra_Tx_Type_Set2,src->Intra_Tx_Type_Set2,sizeof(Default_Intra_Tx_Type_Set2_Cdf)/sizeof(uint16_t));
    memcpy(dst->Inter_Tx_Type_Set1,src->Inter_Tx_Type_Set1,sizeof(Default_Inter_Tx_Type_Set1_Cdf)/sizeof(uint16_t));
    memcpy(dst->Inter_Tx_Type_Set2,src->Inter_Tx_Type_Set2,sizeof(Default_Inter_Tx_Type_Set2_Cdf)/sizeof(uint16_t));
    memcpy(dst->Inter_Tx_Type_Set3,src->Inter_Tx_Type_Set3,sizeof(Default_Inter_Tx_Type_Set3_Cdf)/sizeof(uint16_t));

    memcpy(dst->Compound_Idx,src->Compound_Idx,sizeof(Default_Compound_Idx_Cdf)/sizeof(uint16_t));
    memcpy(dst->Comp_Group_Idx,src->Comp_Group_Idx,sizeof(Default_Comp_Group_Idx_Cdf)/sizeof(uint16_t));
    memcpy(dst->Compound_Type,src->Compound_Type,sizeof(Default_Compound_Type_Cdf)/sizeof(uint16_t));
    memcpy(dst->Inter_Intra,src->Inter_Intra,sizeof(Default_Inter_Intra_Cdf)/sizeof(uint16_t));
    memcpy(dst->Inter_Intra_Mode,src->Inter_Intra_Mode,sizeof(Default_Inter_Intra_Mode_Cdf)/sizeof(uint16_t));

    memcpy(dst->Wedge_Index,src->Wedge_Index,sizeof(Default_Wedge_Index_Cdf)/sizeof(uint16_t));
    memcpy(dst->Wedge_Inter_Intra,src->Wedge_Inter_Intra,sizeof(Default_Wedge_Inter_Intra_Cdf)/sizeof(uint16_t));
    memcpy(dst->Use_Obmc,src->Use_Obmc,sizeof(Default_Use_Obmc_Cdf)/sizeof(uint16_t));
    memcpy(dst->Comp_Ref_Type,src->Comp_Ref_Type,sizeof(Default_Comp_Ref_Type_Cdf)/sizeof(uint16_t));
    memcpy(dst->Uni_Comp_Ref,src->Uni_Comp_Ref,sizeof(Default_Uni_Comp_Ref_Cdf)/sizeof(uint16_t));

    memcpy(dst->Cfl_Sign,src->Cfl_Sign,sizeof(Default_Cfl_Sign_Cdf)/sizeof(uint16_t));
    memcpy(dst->Cfl_Alpha,src->Cfl_Alpha,sizeof(Default_Cfl_Alpha_Cdf)/sizeof(uint16_t));
    memcpy(dst->Use_Wiener,src->Use_Wiener,sizeof(Default_Use_Wiener_Cdf)/sizeof(uint16_t));
    memcpy(dst->Use_Sgrproj,src->Use_Sgrproj,sizeof(Default_Use_Sgrproj_Cdf)/sizeof(uint16_t));
    memcpy(dst->Restoration_Type,src->Restoration_Type,sizeof(Default_Restoration_Type_Cdf)/sizeof(uint16_t));

	frameHeader *frameHdr = &av1Ctx->currentFrame->frameHdr;
    int idx;
    if(frameHdr->quantization_params.base_q_idx == 20){
        idx = 0 ;
    }else if(frameHdr->quantization_params.base_q_idx < 60){
        idx = 1 ;
    }else if(frameHdr->quantization_params.base_q_idx < 120){
        idx = 2 ;
    }else{
        idx = 3 ;
    }
    memcpy(dst->Txb_Skip,src->Txb_Skip,sizeof(Default_Txb_Skip_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Eob_Pt_16,src->Eob_Pt_16,sizeof(Default_Eob_Pt_16_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Eob_Pt_32,src->Eob_Pt_32,sizeof(Default_Eob_Pt_32_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Eob_Pt_64,src->Eob_Pt_64,sizeof(Default_Eob_Pt_64_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Eob_Pt_128,src->Eob_Pt_128,sizeof(Default_Eob_Pt_128_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Eob_Pt_256,src->Eob_Pt_256,sizeof(Default_Eob_Pt_256_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Eob_Pt_512,src->Eob_Pt_512,sizeof(Default_Eob_Pt_512_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Eob_Pt_1024,src->Eob_Pt_1024,sizeof(Default_Eob_Pt_1024_Cdf[idx])/sizeof(uint16_t));

    memcpy(dst->Eob_Extra,src->Eob_Extra,sizeof(Default_Eob_Pt_32_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Dc_Sign,src->Dc_Sign,sizeof(Default_Eob_Pt_32_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Coeff_Base_Eob,src->Coeff_Base_Eob,sizeof(Default_Y_Mode_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Coeff_Base,src->Coeff_Base,sizeof(Default_Y_Mode_Cdf[idx])/sizeof(uint16_t));
    memcpy(dst->Coeff_Br,src->Coeff_Br,sizeof(Default_Y_Mode_Cdf[idx])/sizeof(uint16_t));

}
void Symbol::initSymbol(SymbolContext *sbCtx,bitSt *bs,int sz){
    sbCtx->numBits = Min( sz * 8, 15);
    sbCtx->buf = readBits(bs,sbCtx->numBits); //????
    sbCtx->paddedBuf  = ( sbCtx->buf << (15 - sbCtx->numBits) );
    sbCtx->SymbolValue =   ((1 << 15) - 1) ^ sbCtx->paddedBuf;
    sbCtx->SymbolRange = 1 << 15;
    sbCtx->SymbolMaxBits = 8 * sz - 15;
}
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
}
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
    int extra_bit = read_literal(sbCtx,bs,1);; // L(1)
    return (v << 1) - m + extra_bit;
}

int Symbol::decodeSymbol(SymbolContext *sbCtx,bitSt *bs,uint16_t *cdfArray,int N){

    int cur = sbCtx->SymbolRange;
    int symbol = -1;
    int prev;
    int f;
    //解码单个语法元素或者数据，在这个过程中，
    //SymbolValue和SymbolRange是上次解码的时候已经定下来的输入值
    //SymbolValue是待解码的符号，也就是源数据，SymbolRange是算术编码的范围
    //在loop中根据 cdf 数组来查到底是哪个值
    do {
        symbol++; //逐个尝试
        prev = cur;
        f = ( 1 << 15 ) - cdfArray[ symbol ]; //计算范围
        cur = ((sbCtx->SymbolRange >> 8) * (f >> EC_PROB_SHIFT)) >> (7 - EC_PROB_SHIFT); //将概率进行缩放
        cur += EC_MIN_PROB * (N - symbol - 1);//进行修正，保证概率总和为1
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



//renormalized 这个过程会继续读入码流满15位，以便为后续的解码做准备
    int bits = 15 - FloorLog2( sbCtx->SymbolRange ); //需要继续读进来的数据位数
    sbCtx->numBits = Min( bits, Max(0, sbCtx->SymbolMaxBits) ); //修正需要读取位数
    int newData =  readBits(bs,sbCtx->numBits); //读取，接下来几步将新读进来的数据和之前剩下的组合起来，凑满15位
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
        int b2 = i ? k + i - 1 : k;
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
