#include "decode.h"
#include "header_common.h"
#include "cdf.h"
#include <string.h>
decode::decode(){
    
}
decode::~decode(){


}
int decode::init_non_coeff_cdfs(CDFArrays *cdf){
    memcpy(cdf->Intra_Frame_Y_Mode,Default_Intra_Frame_Y_Mode_Cdf,sizeof(Default_Intra_Frame_Y_Mode_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Y_Mode,Default_Y_Mode_Cdf,sizeof(Default_Y_Mode_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Uv_Mode_Cfl_Not_Allowed,Default_Uv_Mode_Cfl_Not_Allowed_Cdf, sizeof(Default_Uv_Mode_Cfl_Not_Allowed_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Uv_Mode_Cfl_Allowed,Default_Uv_Mode_Cfl_Allowed_Cdf ,sizeof(Default_Uv_Mode_Cfl_Allowed_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Angle_Delta,Default_Angle_Delta_Cdf,sizeof(Default_Angle_Delta_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Intrabc,Default_Intrabc_Cdf,sizeof(Default_Intrabc_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Partition_W8,Default_Partition_W8_Cdf,sizeof(Default_Partition_W8_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Partition_W16,Default_Partition_W16_Cdf ,sizeof(Default_Partition_W16_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Partition_W32,Default_Partition_W32_Cdf ,sizeof(Default_Partition_W32_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Partition_W64,Default_Partition_W64_Cdf ,sizeof(Default_Partition_W64_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Partition_W128,Default_Partition_W128_Cdf ,sizeof(Default_Partition_W128_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Tx_8x8,Default_Tx_8x8_Cdf,sizeof(Default_Tx_8x8_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Tx_16x16,Default_Tx_16x16_Cdf,sizeof(Default_Tx_16x16_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Tx_32x32,Default_Tx_32x32_Cdf,sizeof(Default_Tx_32x32_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Tx_64x64,Default_Tx_64x64_Cdf,sizeof(Default_Tx_64x64_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Txfm_Split,Default_Txfm_Split_Cdf,sizeof(Default_Txfm_Split_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Filter_Intra_Mode,Default_Filter_Intra_Mode_Cdf,sizeof(Default_Filter_Intra_Mode_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Filter_Intra,Default_Filter_Intra_Cdf,sizeof(Default_Filter_Intra_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Segment_Id,Default_Segment_Id_Cdf,sizeof(Default_Segment_Id_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Segment_Id_Predicted,Default_Segment_Id_Predicted_Cdf,sizeof(Default_Segment_Id_Predicted_Cdf)/sizeof(uint16_t));
    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        for(int j = 0 ; i < 2 ; j++){
            memcpy(cdf->Mv_Class0_Hp[i][j],Default_Mv_Class0_Hp_Cdf,sizeof(Default_Mv_Class0_Hp_Cdf)/sizeof(uint16_t));
            memcpy(cdf->Mv_Hp[i][j],Default_Mv_Hp_Cdf,sizeof(Default_Mv_Hp_Cdf)/sizeof(uint16_t));
            memcpy(cdf->Mv_Sign[i][j],Default_Mv_Sign_Cdf,sizeof(Default_Mv_Sign_Cdf)/sizeof(uint16_t));
            memcpy(cdf->Mv_Bit[i][j],Default_Mv_Bit_Cdf,sizeof(Default_Mv_Bit_Cdf)/sizeof(uint16_t));
            memcpy(cdf->Mv_Class0_Bit[i][j],Default_Mv_Class0_Bit_Cdf,sizeof(Default_Mv_Class0_Bit_Cdf)/sizeof(uint16_t));
        }
    }
    memcpy(cdf->New_Mv,Default_New_Mv_Cdf,sizeof(Default_New_Mv_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Zero_Mv,Default_Zero_Mv_Cdf,sizeof(Default_Zero_Mv_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Ref_Mv,Default_Ref_Mv_Cdf,sizeof(Default_Ref_Mv_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Ref_Mv,Default_Ref_Mv_Cdf,sizeof(Default_Ref_Mv_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Drl_Mode,Default_Drl_Mode_Cdf,sizeof(Default_Drl_Mode_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Is_Inter,Default_Is_Inter_Cdf,sizeof(Default_Is_Inter_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Is_Inter,Default_Is_Inter_Cdf,sizeof(Default_Is_Inter_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Comp_Mode,Default_Comp_Mode_Cdf,sizeof(Default_Comp_Mode_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Skip_Mode,Default_Skip_Mode_Cdf,sizeof(Default_Skip_Mode_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Skip,Default_Skip_Cdf,sizeof(Default_Skip_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Comp_Ref,Default_Comp_Ref_Cdf,sizeof(Default_Comp_Ref_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Comp_Bwd_Ref,Default_Comp_Bwd_Ref_Cdf,sizeof(Default_Comp_Bwd_Ref_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Single_Ref,Default_Single_Ref_Cdf,sizeof(Default_Single_Ref_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Compound_Mode,Default_Compound_Mode_Cdf,sizeof(Default_Compound_Mode_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Interp_Filter,Default_Interp_Filter_Cdf,sizeof(Default_Interp_Filter_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Motion_Mode,Default_Motion_Mode_Cdf,sizeof(Default_Motion_Mode_Cdf)/sizeof(uint16_t));

    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        memcpy(cdf->Mv_Joint[i],Default_Mv_Joint_Cdf,sizeof(Default_Mv_Joint_Cdf)/sizeof(uint16_t));
        memcpy(cdf->Mv_Class[i],Default_Mv_Class_Cdf,sizeof(Default_Mv_Class_Cdf)/sizeof(uint16_t));
        memcpy(cdf->Mv_Class0_Fr[i],Default_Mv_Class0_Fr_Cdf,sizeof(Default_Mv_Class0_Fr_Cdf)/sizeof(uint16_t));
        memcpy(cdf->Mv_Fr[i],Default_Mv_Fr_Cdf,sizeof(Default_Mv_Fr_Cdf)/sizeof(uint16_t));
    }
    memcpy(cdf->Palette_Y_Size,Default_Palette_Y_Size_Cdf,sizeof(Default_Palette_Y_Size_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Uv_Size,Default_Palette_Uv_Size_Cdf,sizeof(Default_Palette_Uv_Size_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Palette_Size_2_Y_Color,Default_Palette_Size_2_Y_Color_Cdf,sizeof(Default_Palette_Size_2_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_3_Y_Color,Default_Palette_Size_3_Y_Color_Cdf,sizeof(Default_Palette_Size_3_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_4_Y_Color,Default_Palette_Size_4_Y_Color_Cdf,sizeof(Default_Palette_Size_4_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_5_Y_Color,Default_Palette_Size_5_Y_Color_Cdf,sizeof(Default_Palette_Size_5_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_6_Y_Color,Default_Palette_Size_6_Y_Color_Cdf,sizeof(Default_Palette_Size_6_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_7_Y_Color,Default_Palette_Size_7_Y_Color_Cdf,sizeof(Default_Palette_Size_7_Y_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_8_Y_Color,Default_Palette_Size_8_Y_Color_Cdf,sizeof(Default_Palette_Size_8_Y_Color_Cdf)/sizeof(uint16_t));


    memcpy(cdf->Palette_Size_2_Uv_Color,Default_Palette_Size_2_Uv_Color_Cdf,sizeof(Default_Palette_Size_2_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_3_Uv_Color,Default_Palette_Size_3_Uv_Color_Cdf,sizeof(Default_Palette_Size_3_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_4_Uv_Color,Default_Palette_Size_4_Uv_Color_Cdf,sizeof(Default_Palette_Size_4_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_5_Uv_Color,Default_Palette_Size_5_Uv_Color_Cdf,sizeof(Default_Palette_Size_5_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_6_Uv_Color,Default_Palette_Size_6_Uv_Color_Cdf,sizeof(Default_Palette_Size_6_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_7_Uv_Color,Default_Palette_Size_7_Uv_Color_Cdf,sizeof(Default_Palette_Size_7_Uv_Color_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Palette_Size_8_Uv_Color,Default_Palette_Size_8_Uv_Color_Cdf,sizeof(Default_Palette_Size_8_Uv_Color_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Delta_Q,Default_Delta_Q_Cdf,sizeof(Default_Delta_Q_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Delta_Lf,Default_Delta_Lf_Cdf,sizeof(Default_Delta_Lf_Cdf)/sizeof(uint16_t));

    for(int i = 0 ; i < FRAME_LF_COUNT ; i++)
        memcpy(cdf->Delta_Lf_Muti[i],Default_Delta_Lf_Cdf,sizeof(Default_Delta_Lf_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Intra_Tx_Type_Set1,Default_Intra_Tx_Type_Set1_Cdf,sizeof(Default_Intra_Tx_Type_Set1_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Intra_Tx_Type_Set2,Default_Intra_Tx_Type_Set2_Cdf,sizeof(Default_Intra_Tx_Type_Set2_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Inter_Tx_Type_Set1,Default_Inter_Tx_Type_Set1_Cdf,sizeof(Default_Inter_Tx_Type_Set1_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Inter_Tx_Type_Set2,Default_Inter_Tx_Type_Set2_Cdf,sizeof(Default_Inter_Tx_Type_Set2_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Inter_Tx_Type_Set3,Default_Inter_Tx_Type_Set3_Cdf,sizeof(Default_Inter_Tx_Type_Set3_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Compound_Idx,Default_Compound_Idx_Cdf,sizeof(Default_Compound_Idx_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Comp_Group_Idx,Default_Comp_Group_Idx_Cdf,sizeof(Default_Comp_Group_Idx_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Compound_Type,Default_Compound_Type_Cdf,sizeof(Default_Compound_Type_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Inter_Intra,Default_Inter_Intra_Cdf,sizeof(Default_Inter_Intra_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Inter_Intra_Mode,Default_Inter_Intra_Mode_Cdf,sizeof(Default_Inter_Intra_Mode_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Wedge_Index,Default_Wedge_Index_Cdf,sizeof(Default_Wedge_Index_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Wedge_Inter_Intra,Default_Wedge_Inter_Intra_Cdf,sizeof(Default_Wedge_Inter_Intra_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Use_Obmc,Default_Use_Obmc_Cdf,sizeof(Default_Use_Obmc_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Comp_Ref_Type,Default_Comp_Ref_Type_Cdf,sizeof(Default_Comp_Ref_Type_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Uni_Comp_Ref,Default_Uni_Comp_Ref_Cdf,sizeof(Default_Uni_Comp_Ref_Cdf)/sizeof(uint16_t));

    memcpy(cdf->Cfl_Sign,Default_Cfl_Sign_Cdf,sizeof(Default_Cfl_Sign_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Cfl_Alpha,Default_Cfl_Alpha_Cdf,sizeof(Default_Cfl_Alpha_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Use_Wiener,Default_Use_Wiener_Cdf,sizeof(Default_Use_Wiener_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Use_Sgrproj,Default_Use_Sgrproj_Cdf,sizeof(Default_Use_Sgrproj_Cdf)/sizeof(uint16_t));
    memcpy(cdf->Restoration_Type,Default_Restoration_Type_Cdf,sizeof(Default_Restoration_Type_Cdf)/sizeof(uint16_t));

}
//indicates that this frame can be decoded without dependence on previous coded frames
int decode::setup_past_independence(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = av1Ctx->curFrameHdr;
	for(int i = 0 ; i < MAX_SEGMENTS; i++){
		for(int j = 0 ; j < SEG_LVL_MAX ; j++){
			frameHdr->segmentation_params.FeatureData[ i ][ j ] = 0;
			frameHdr->segmentation_params.FeatureEnabled[ i ][ j ] = 0;
		}

	}
	for(int row = 0 ; row < frameHdr->MiRows; row++){
		for(int col = 0 ; col < frameHdr->MiCols ; col++){
			av1Ctx->PrevSegmentIds[ row ][ col ] = 0;
		}

	}

	for(int ref = LAST_FRAME ; ref <= ALTREF_FRAME ; ref ++){
		frameHdr->global_motion_params.GmType[ ref ] = IDENTITY;
		for(int i = 0 ; i <= 5 ; i++){
			frameHdr->global_motion_params.PrevGmParams[ ref ][ i ] = ( ( i % 3 == 2 ) ? 1 << WARPEDMODEL_PREC_BITS : 0 ) ;
		}
	}
	frameHdr->loop_filter_params.loop_filter_delta_enabled = 1;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ INTRA_FRAME ] = 1;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ LAST_FRAME ] = 0;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ LAST2_FRAME ] = 0;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ LAST3_FRAME ] = 0;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ BWDREF_FRAME ] = 0;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ GOLDEN_FRAME ] = -1;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ ALTREF_FRAME ] = -1;
	frameHdr->loop_filter_params.loop_filter_ref_deltas[ ALTREF2_FRAME ] = -1;
	for(int i = 0 ; i <= 1; i++) 
		frameHdr->loop_filter_params.loop_filter_mode_deltas[ i ] = 0;


}
//从参考帧拷贝cdf到当前framecontext
int decode::load_cdfs(AV1DecodeContext *av1Ctx,int ctx){
	memcpy(&av1Ctx->currentFrame.cdfCtx,&av1Ctx->ref_frames[ctx]->cdfCtx,sizeof(av1Ctx->ref_frames[ctx]->cdfCtx));
}
//加载主参考帧的一些参数
int decode::load_previous(AV1DecodeContext *av1Ctx){
	int prevFrame = ref_frame_idx[ primary_ref_frame ];
	frameHdr->global_motion_params.PrevGmParams = SavedGmParams[ prevFrame ];
	load_loop_filter_params(av1Ctx,prevFrame);
	load_segmentation_params(av1Ctx,prevFrame);

}
//the values of loop_filter_ref_deltas[ j ] for j = 0 ..
//TOTAL_REFS_PER_FRAME-1, and the values of loop_filter_mode_deltas[ j ] for j = 0 .. 1 should be 
//loaded from an area of memory indexed by i.

int decode::load_loop_filter_params(AV1DecodeContext *av1Ctx,int prevFrame){

	memcpy(av1Ctx->currentFrame.frameHdr.loop_filter_params.loop_filter_ref_deltas,
		av1Ctx->ref_frames[prevFrame]->frameHdr.loop_filter_params.loop_filter_ref_deltas,
		TOTAL_REFS_PER_FRAME * sizeof(uint8_t));
	memcpy(av1Ctx->currentFrame.frameHdr.loop_filter_params.loop_filter_mode_deltas,
		av1Ctx->ref_frames[prevFrame]->frameHdr.loop_filter_params.loop_filter_mode_deltas,
		2 * sizeof(uint8_t));

	
}
int decode::load_segmentation_params(AV1DecodeContext *av1Ctx,int prevFrame){
	memcpy(av1Ctx->currentFrame.frameHdr.segmentation_params.FeatureEnabled,
		av1Ctx->ref_frames[prevFrame]->frameHdr.segmentation_params.FeatureEnabled,
		MAX_SEGMENTS * SEG_LVL_MAX * sizeof(uint8_t));
	memcpy(av1Ctx->currentFrame.frameHdr.segmentation_params.FeatureData,
		av1Ctx->ref_frames[prevFrame]->frameHdr.segmentation_params.FeatureData,
		MAX_SEGMENTS * SEG_LVL_MAX * sizeof(int16_t));
}
int decode::load_previous_segment_ids(){
	int prevFrame = ref_frame_idx[ primary_ref_frame ];
	if(segmentation_enabled){
		//load参数，这里为什么是save动作？
		//设置 RefMiCols 和 RefMiRows 的目的是为了在解码过程中保持块大小的一致性，以正确地引用之前帧的数据。
		RefMiCols[ prevFrame ] = MiCols;
		RefMiRows[ prevFrame ] = MiRows;
		for(int row  = 0; row < MiRows  ; row ++ ){
			for(int col  = 0; col < MiCols  ; col ++ ){
				PrevSegmentIds[ row ][ col ] = SavedSegmentIds[ prevFrame ][ row ][ col ];
			}
		}

	}else{
		for(int row  = 0; row < MiRows  ; row ++ ){
			for(int col  = 0; col < MiCols  ; col ++ ){
				PrevSegmentIds[ row ][ col ] = 0;
			}
		}
	}
}
int decode::init_coeff_cdfs(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = av1Ctx->curFrameHdr;
    CDFArrays *cdf = &av1Ctx->currentFrame.cdfCtx;
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
    memcpy(cdf->Txb_Skip,Default_Txb_Skip_Cdf[idx],sizeof(Default_Txb_Skip_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Eob_Pt_16,Default_Eob_Pt_16_Cdf[idx],sizeof(Default_Eob_Pt_16_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Eob_Pt_32,Default_Eob_Pt_32_Cdf[idx],sizeof(Default_Eob_Pt_32_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Eob_Pt_64,Default_Eob_Pt_64_Cdf[idx],sizeof(Default_Eob_Pt_64_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Eob_Pt_128,Default_Eob_Pt_128_Cdf[idx],sizeof(Default_Eob_Pt_128_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Eob_Pt_256,Default_Eob_Pt_256_Cdf[idx],sizeof(Default_Eob_Pt_256_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Eob_Pt_512,Default_Eob_Pt_512_Cdf[idx],sizeof(Default_Eob_Pt_512_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Eob_Pt_1024,Default_Eob_Pt_1024_Cdf[idx],sizeof(Default_Eob_Pt_1024_Cdf[idx])/sizeof(uint16_t));

    memcpy(cdf->Eob_Extra,Default_Eob_Extra_Cdf[idx],sizeof(Default_Eob_Pt_32_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Dc_Sign,Default_Dc_Sign_Cdf[idx],sizeof(Default_Eob_Pt_32_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Coeff_Base_Eob,Default_Coeff_Base_Eob_Cdf[idx],sizeof(Default_Y_Mode_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Coeff_Base,Default_Coeff_Base_Cdf[idx],sizeof(Default_Y_Mode_Cdf[idx])/sizeof(uint16_t));
    memcpy(cdf->Coeff_Br,Default_Coeff_Br_Cdf[idx],sizeof(Default_Y_Mode_Cdf[idx])/sizeof(uint16_t));
}

//7.8
int decode::set_frame_refs(){
	for (int i = 0; i < REFS_PER_FRAME; i++ )
		ref_frame_idx[ i ] = -1;
	ref_frame_idx[ LAST_FRAME - LAST_FRAME ] = last_frame_idx;
	ref_frame_idx[ GOLDEN_FRAME - LAST_FRAME ] = gold_frame_idx;

	int usedFrame[REFS_PER_FRAME];
	for (int i = 0; i < NUM_REF_FRAMES; i++ )
		usedFrame[ i ] = 0;
	usedFrame[ last_frame_idx ] = 1;
	usedFrame[ gold_frame_idx ] = 1;
	int  curFrameHint = 1 << (OrderHintBits - 1);
	for (int  i = 0; i < NUM_REF_FRAMES; i++ )
		shiftedOrderHints[ i ] = curFrameHint + get_relative_dist( RefOrderHint[ i ], OrderHint );

	int lastOrderHint = shiftedOrderHints[last_frame_idx ];
	//It is a requirement of bitstream conformance that lastOrderHint is strictly less than curFrameHint
	if(!(lastOrderHint < curFrameHint)){
		//如果不满足，该做什么？？ spec只是说需要确认。。。
		//直接退出当前流程？？
	}

	int goldOrderHint = shiftedOrderHints[ gold_frame_idx ];
	if(!(goldOrderHint < curFrameHint) ){
		//如果不满足，该做什么？？
	}
// ALTREF_FRAME reference is set to be a backward reference to the frame with highest output order 
//ALTREF_FRAME参考帧被设置为输出顺序最高的帧的后向参考帧
	//find_latest_backward()
	int ref = -1;
	int latestOrderHint = INT_MIN;
	for (int  i = 0; i < NUM_REF_FRAMES; i++ ) {
		int hint = shiftedOrderHints[ i ];
		if ( !usedFrame[ i ] &&
			hint >= curFrameHint &&
		( ref < 0 || hint >= latestOrderHint ) ) {
			ref = i;
			latestOrderHint = hint;
		}
	}
	if ( ref >= 0 ) {
		ref_frame_idx[ ALTREF_FRAME - LAST_FRAME ] = ref;
		usedFrame[ ref ] = 1;
	}

//BWDREF_FRAME reference is set to be a backward reference to the closest frame
//BWDREF_FRAME参考帧被设置为最近帧的后向参考帧
	ref = -1;
	int earliestOrderHint = INT_MIN;
	for (int i = 0; i < NUM_REF_FRAMES; i++ ) {
		int hint = shiftedOrderHints[ i ];
		if ( !usedFrame[ i ] &&
		hint >= curFrameHint &&
		( ref < 0 || hint < earliestOrderHint ) ) {
			ref = i;
			earliestOrderHint = hint;
		}
	}
	if ( ref >= 0 ) {
		ref_frame_idx[ BWDREF_FRAME - LAST_FRAME ] = ref;
		usedFrame[ ref ] = 1;
	}
//ALTREF2_FRAME reference is set to the next closest backward reference
//ALTREF2_FRAME参考帧被设置为次近的后向参考帧。
	ref = -1;
	earliestOrderHint = INT_MIN;
	for (int i = 0; i < NUM_REF_FRAMES; i++ ) {
		int hint = shiftedOrderHints[ i ];
		if ( !usedFrame[ i ] &&
		hint >= curFrameHint &&
		( ref < 0 || hint < earliestOrderHint ) ) {
			ref = i;
			earliestOrderHint = hint;
		}
	}
	if ( ref >= 0 ) {
		ref_frame_idx[ ALTREF2_FRAME - LAST_FRAME ] = ref;
		usedFrame[ ref ] = 1;
	}

 //remaining references are set to be forward references in anti-chronological order
 //剩余的参考帧被设置为按反时间顺序的前向参考帧
	for (int i = 0; i < REFS_PER_FRAME - 2; i++ ) {
		int refFrame = Ref_Frame_List[ i ];
		if ( ref_frame_idx[ refFrame - LAST_FRAME ] < 0 ) {
			ref = -1;
			latestOrderHint = INT_MIN;
			for (int  i = 0; i < NUM_REF_FRAMES; i++ ) {
				int hint = shiftedOrderHints[ i ];
				if ( !usedFrame[ i ] &&
				hint < curFrameHint &&
				( ref < 0 || hint >= latestOrderHint ) ) {
					ref = i;
					latestOrderHint = hint;
				}
			}


		if ( ref >= 0 ) {
			ref_frame_idx[ refFrame - LAST_FRAME ] = ref;
			usedFrame[ ref ] = 1;
		}
		}
	}
//Finally, any remaining references are set to the reference frame with smallest output order
//最后，剩余的参考帧被设置为输出顺序最小的参考帧
	ref = -1;
	earliestOrderHint = INT_MIN;
	for (int i = 0; i < NUM_REF_FRAMES; i++ ) {
		int hint = shiftedOrderHints[ i ];
		if ( ref < 0 || hint < earliestOrderHint ) {
			ref = i;
			earliestOrderHint = hint;
		}
	}
	for (int i = 0; i < REFS_PER_FRAME; i++ ) {
		if ( ref_frame_idx[ i ] < 0 ) {
			ref_frame_idx[ i ] = ref;
		}
	}

}
//7.9
int decode::motion_field_estimation(){
	int w8 = MiCols >> 1;
	int h8 = MiRows >> 1;
//As the linear projection can create a field with holes, the motion fields are initialized to an invalid motion vector of -32768,-32768
	for (int  ref = LAST_FRAME; ref <= ALTREF_FRAME; ref++ )
		for (int  y = 0; y < h8 ; y++ )
			for (int  x = 0; x < w8; x++ )
				for (int  j = 0; j < 2; j++ )
				MotionFieldMvs[ ref ][ y ][ x ][ j ] = -1 << 15;

	int lastIdx = ref_frame_idx[ 0 ];
	int curGoldOrderHint = OrderHints[ GOLDEN_FRAME ];
	int lastAltOrderHint = SavedOrderHints[ lastIdx ][ ALTREF_FRAME ];
	int useLast =  (lastAltOrderHint != curGoldOrderHint );
	if(useLast == 1){


	}

}
//The process projects the motion vectors from a whole reference frame and stores the results in MotionFieldMvs.
//The process outputs a single boolean value representing whether the source frame was valid for this operation. If the
//output is zero, no modification is made to MotionFieldMvs
int decode::motion_filed_project(int src,int dstSign){
	int srcIdx = ref_frame_idx[src - LAST_FRAME];
	int w8 = MiCols >> 1;
	int h8 = MiRows >> 1;

	if (RefMiRows[srcIdx] != MiRows || RefMiCols[srcIdx] != MiCols || RefFrameType[srcIdx] == INTRA_ONLY_FRAME || RefFrameType[srcIdx] == KEY_FRAME) {
		// Exit the process with output set to 0
		// ...
		return 0;
	}
	for (int y8 = 0; y8 < h8; y8++) {
		for (int x8 = 0; x8 < w8; x8++) {
			int row = 2 * y8 + 1; 
			int col = 2 * x8 + 1;
			int srcRef = SavedRefFrames[srcIdx][row][col];
			
			if (srcRef > INTRA_FRAME) {
				int refToCur = get_relative_dist(OrderHints[src], OrderHint);
				int refOffset = get_relative_dist(OrderHints[src], SavedOrderHints[srcIdx][srcRef]);
				int posValid = (Abs(refToCur) <= MAX_FRAME_DISTANCE) &&
							(Abs(refOffset) <= MAX_FRAME_DISTANCE) &&
							(refOffset > 0);
				
				if (posValid) {
					int mv = SavedMvs[srcIdx][row][col];
					int projMv = get_mv_projection(mv, refToCur * dstSign, refOffset);
					posValid = get_block_position(x8, y8, dstSign, projMv);
					
					if (posValid) {
						for (int dst = LAST_FRAME; dst <= ALTREF_FRAME; dst++) {
							int refToDst = get_relative_dist(OrderHint, OrderHints[dst]);
							projMv = get_mv_projection(mv, refToDst, refOffset);
							MotionFieldMvs[dst][PosY8][PosX8] = projMv;
						}
					}
				}
			}
		}
	}
}
//This process starts with a motion vector mv from a previous frame. This motion vector gives the displacement expected
//when moving a certain number of frames (given by the variable denominator). In order to use the motion vector for
//predictions using a different reference frame, the length of the motion vector must be scaled
int decode::get_mv_projection(int *projMv, int *mv,int numerator,int denominator){

	int clippedDenominator = Min(MAX_FRAME_DISTANCE, denominator);
	int clippedNumerator = Clip3(-MAX_FRAME_DISTANCE, MAX_FRAME_DISTANCE, numerator);


	for (int i = 0; i < 2; i++) {
		int scaled = Round2Signed(mv[i] * clippedNumerator * Div_Mult[clippedDenominator], 14);
		projMv[i] = scaled;
	}
}
//process returns a flag posValid that indicates if the position should be used
int decode::get_block_position(int *PosX8,int *PosY8, int x8, int y8, int dstSign, int *projMv ){

	int posValid = 1;

	*PosY8 = project(&posValid,&y8, projMv[ 0 ], dstSign, MiRows >> 1, MAX_OFFSET_HEIGHT);
	*PosX8 = project(&posValid,&x8, projMv[ 1 ], dstSign, MiCols >> 1, MAX_OFFSET_WIDTH);

	return posValid;
}

//7.10
/*  find mv stack  and about start...*/
int decode::find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, TileData *t_data,
								 PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1ctx){

	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;
									
	av1ctx->NumMvFound = 0;
	av1ctx->NewMvCount = 0;
	setup_global_mv(0,av1ctx->GlobalMvs[0],b_data,av1ctx);
	setup_global_mv(1,av1ctx->GlobalMvs[1],b_data,av1ctx);
	av1ctx->FoundMatch = 0;
	scan_row(-1,isCompound,p_data,b_data);
	int foundAboveMatch,foundLeftMatch;

	foundAboveMatch = av1ctx->FoundMatch ;
	av1ctx->FoundMatch = 0;
	scan_col(-1,isCompound);
	foundLeftMatch = av1ctx->FoundMatch ;
	av1ctx->FoundMatch = 0;

	int bh4 = Num_4x4_Blocks_High[ b_data->MiSize ];
	int bw4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
	if(Max( bw4, bh4 ) <= 16){
		scan_point(-1,bw4,isCompound);
	}

	if(av1ctx->FoundMatch == 1){
		foundAboveMatch = 1;
	}
	av1ctx->CloseMatches = foundAboveMatch + foundLeftMatch;
	int numNearest = av1ctx->NumMvFound;
	int numNew = av1ctx->NewMvCount;
	if(numNearest > 0){
		for(int idx = 0 ;idx < numNearest - 1;idx ++ ){
				WeightStack[ idx ] += REF_CAT_LEVEL;
		}
	}
	av1ctx->ZeroMvContext = 0;
	if(frameHdr->use_ref_frame_mvs == 1){

		temporal_scan(isCompound);
	}
	scan_point(-1,-1,isCompound);
	if(av1ctx->FoundMatch == 1){
		foundAboveMatch = 1;
	}

	av1ctx->FoundMatch =0;
	scan_row(-3,isCompound,p_data,b_data);
	if(av1ctx->FoundMatch == 1){
		foundAboveMatch = 1;
	}
	av1ctx->FoundMatch =0;

	scan_col(-3,isCompound);
	if(av1ctx->FoundMatch == 1){
		foundLeftMatch = 1;
	}
	av1ctx->FoundMatch = 0;


	if(bh4 > 1){
		scan_row(-5,isCompound);
	}
	if(av1ctx->FoundMatch == 1){
		foundAboveMatch = 1;
	}
	av1ctx->FoundMatch = 0;

	if(bw4 > 1){
		scan_col(-5,isCompound);
	}
	if(av1ctx->FoundMatch == 1){
		foundLeftMatch = 1;
	}

	av1ctx->TotalMatches = foundAboveMatch + foundLeftMatch;

	Sorting(0,numNearest,isCompound);
	Sorting(numNearest,av1ctx->NumMvFound,isCompound);
	if(av1ctx->NumMvFound < 2){
		extra_search(isCompound);
	}
	context_and_clamping(isCompound,numNew);

}
//7.10.2.1
int decode::setup_global_mv(int refList,int *mv,
								 BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	int ref,typ;
	ref = b_data->RefFrame[ refList ];
	frameHeader *frameHdr = av1Ctx->frameHdr;
	if (ref == INTRA_FRAME || typ == IDENTITY)
	{
		mv[0] = 0;
		mv[1] = 0;
	}
	else if (typ == TRANSLATION)
	{
		mv[0] = frameHdr->global_motion_params.gm_params[ref][0] >> (WARPEDMODEL_PREC_BITS - 3);
		mv[1] = frameHdr->global_motion_params.gm_params[ref][1] >> (WARPEDMODEL_PREC_BITS - 3);
	}
	else
	{
		int x = b_data->MiCol * MI_SIZE + 4 * Num_4x4_Blocks_Wide[ b_data->MiSize ] / 2 - 1;
		int y = b_data->MiRow * MI_SIZE + 4 * Num_4x4_Blocks_High[ b_data->MiSize ] / 2 - 1;
		int xc = (frameHdr->global_motion_params.gm_params[ref][2] - (1 << WARPEDMODEL_PREC_BITS)) * x +
			 frameHdr->global_motion_params.gm_params[ref][3] * y +
			 frameHdr->global_motion_params.gm_params[ref][0];
		int yc = frameHdr->global_motion_params.gm_params[ref][4] * x +
			 (frameHdr->global_motion_params.gm_params[ref][5] - (1 << WARPEDMODEL_PREC_BITS)) * y +
			 frameHdr->global_motion_params.gm_params[ref][1];
		if (frameHdr->allow_high_precision_mv)
		{
			mv[0] = Round2Signed(yc, WARPEDMODEL_PREC_BITS - 3);
			mv[1] = Round2Signed(xc, WARPEDMODEL_PREC_BITS - 3);
		}
		else
		{
			mv[0] = Round2Signed(yc, WARPEDMODEL_PREC_BITS - 2) * 2;
			mv[1] = Round2Signed(xc, WARPEDMODEL_PREC_BITS - 2) * 2;
		}
	}
	lower_mv_precision(mv);
}
int decode::lower_mv_precision(int force_integer_mv,int *candMv){

	if(low_high_precision_mv == 1)
		return;
	for(int idx =0 ; idx < 2 ;idx ++){	
		if ( force_integer_mv ) {
			int a = Abs( candMv[ idx ] );
			int aInt = (a + 3) >> 3;
			if ( candMv[ idx ] > 0 )
				candMv[ idx ] = aInt << 3;
			else
				candMv[ idx ] = -( aInt << 3 );
		} else {
			if ( candMv[ idx ] & 1 ) {
				if ( candMv[ idx ] > 0 )
					candMv[ idx ]--;
				else
					candMv[ idx ]++;
			}
		}
	}
}
int decode::scan_row(int deltaRow,int isCompound,
				TileData t_data,PartitionData p_data,BlockData *b_data,AV1DecodeContext *av1Ctx){
	int deltaCol = 0;
	if(Abs(deltaRow) > 1){
		deltaRow += b_data->MiRow & 1;
		deltaCol = 1 - (b_data->MiCol & 1);
	}
	int i = 0 ;
	int bw4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
	int end4 = Min( Min( bw4,p_data->MiCols - b_data->MiCol ), 16 );
	while (i < end4)
	{
		int mvRow = b_data->MiRow + deltaRow;
		int mvCol = b_data->MiCol + deltaCol + i;
		if (!is_inside(mvRow, mvCol,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd))
			break;
		int len = Min(bw4, Num_4x4_Blocks_Wide[p_data->MiSizes[mvRow][mvCol]]);
		if (Abs(deltaRow) > 1)
		len = Max(2, len);
		int useStep16 = bw4 >= 16;
		if (useStep16)
			len = Max(4, len);
		int weight = len * 2;
		add_ref_mv_candidate(mvRow, mvCol, isCompound, weight,t_data,p_data,b_data);
		i += len;
	}
}
int decode::scan_col(int deltaCol,int isCompound,
			TileData t_data,PartitionData p_data,BlockData *b_data,AV1DecodeContext *av1Ctx){
	int deltaRow = 0;
	if(Abs(deltaRow) > 1){	
		deltaRow = 1 - (b_data->MiRow & 1);
		deltaCol += b_data->MiCol & 1
	}
	int i = 0;
	int bh4 = Num_4x4_Blocks_High[ b_data->MiSize ];
	int end4 = Min( Min( bh4,p_data->MiRows - b_data->MiRow ), 16 );

	while ( i < end4 ) {
		int mvRow = b_data->MiRow + deltaRow + i;
		int mvCol = b_data->MiCol + deltaCol;
		if ( !is_inside(mvRow,mvCol,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd) )
			break;
		int len = Min(bh4, Num_4x4_Blocks_High[ p_data->MiSizes[ mvRow ][ mvCol ] ]);
		if ( Abs(deltaCol) > 1 )
			len = Max(2, len);
		int useStep16 = bh4 >= 16;
		if ( useStep16 )
			len = Max(4, len);
		int weight = len * 2;
		add_ref_mv_candidate( mvRow, mvCol, isCompound, weight,t_data,p_data,b_data);
		i += len;
	}

}
//This process examines the candidate to find matching reference frames.
int decode::add_ref_mv_candidate(int mvRow,int  mvCol,int  isCompound,int weight,
								TileData t_data,PartitionData p_data,BlockData *b_data,AV1DecodeContext *av1Ctx){
	if(IsInters[ mvRow ][ mvCol ] == 0){
		return;
	}
	if(isCompound == 0){
		for(int candList = 0 ;candList < 2; candList ++){
			if(RefFrames[ mvRow ][ mvCol ][ candList ] == RefFrame[ 0 ]){
				search_stack(mvRow, mvCol, candList,weight,t_data, p_data, b_data,av1Ctx);

			}
		}
	}else{
		if(RefFrames[ mvRow ][ mvCol ][ 0 ] == RefFrame[ 0 ] &&
		 RefFrames[ mvRow ][ mvCol ][ 1 ]  == RefFrame[ 1 ]){
			Compound_search_stack(mvRow, mvCol, weight,t_data, p_data, b_data,av1Ctx);
		 }
	}
}
//This process searches the stack for an exact match with a candidate motion vector. If present, the weight of the candidate
//motion vector is added to the weight of its counterpart in the stack, otherwise the process adds a motion vector to the
//stack.

int decode::search_stack(int mvRow,int mvCol,int candList,int weight,
						TileData t_data,PartitionData p_data,BlockData *b_data,AV1DecodeContext *av1Ctx){
	int candMode = p_data->YModes[ mvRow ][ mvCol ];
	int candSize = p_data->MiSizes[ mvRow ][ mvCol ];
	int candMode;
	int candMv[2];
	int large =  Min( Block_Width[ candSize ],Block_Height[ candSize ] ) >= 8;
	if(( candMode == GLOBALMV && candMode == GLOBAL_GLOBALMV) && 
				( GmType[ RefFrame[ 0 ] ] > TRANSLATION )  && ( large == 1 ))
	{
		candMv = b_data->GlobalMvs[ 0 ];
	}else{	
		candMv = p_data->Mvs[ mvRow ][ mvCol ][ candList ];
	}
	lower_precision(candMv,av1Ctx);
	if(candMode == NEWMV ||
			candMode == NEW_NEWMV ||
			candMode == NEAR_NEWMV ||
			candMode == NEW_NEARMV ||
			candMode == NEAREST_NEWMV ||
			candMode == NEW_NEARESTMV)
	{
		b_data->NewMvCount += 1;
	}
	b_data->FoundMatch = 1;


	for (int idx = 0; idx < av1ctx->NumMvFound; idx++) {
		if (is_equal(candMv, av1ctx->RefStackMv[idx][0])) {
			WeightStack[idx] += weight;
		}else{
			if( b_data->NumMvFound < MAX_REF_MV_STACK_SIZE){
				av1ctx->RefStackMv[ b_data->NumMvFound][0] = candMv;
				WeightStack[ b_data->NumMvFound] = weight;
				 b_data->NumMvFound++;
			}

		}
	}

}
//This process searches the stack for an exact match with a candidate pair of motion vectors. If present, the weight of the
//candidate pair of motion vectors is added to the weight of its counterpart in the stack, otherwise the process adds the
//motion vectors to the stack.
int decode::compound_search_stack(int  mvRow ,int  mvCol,int weight,
				TileData t_data,PartitionData p_data,BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = av1Ctx->frameHdr;
	int candMvs[2][2] = Mvs[ mvRow ][ mvCol ];
	int candMode = p_data->AboveRefFrame[ mvRow ][ mvCol ];
	int candSize = p_data->MiSizes[ mvRow ][ mvCol ];
	if(candMode == GLOBAL_GLOBALMV){
		for(int refList = 0 ; refList < 2; refList ++){
			if(frameHdr->global_motion_params.GmType[ RefFrame[ refList ] ] > TRANSLATION)
			  candMvs[ refList ] = GlobalMvs[ refList ];
		}

	}
	for(int i = 0 ; i < 2; i ++){
		lower_precision(candMvs[i],av1Ctx);
	}
	b_data->FoundMatch = 1;
	for(int idx =0 ;idx < b_data->NumMvFound ;idx ++){
		if(is_equal(candMvs[ 0 ],av1ctx->RefStackMv[ idx ][ 0 ]) &&
			is_equal(candMvs[ 1 ],av1ctx->RefStackMv[ idx ][ 1 ])){
				WeightStack[ idx ] += weight;

		}else{
			if(b_data->NumMvFound < MAX_REF_MV_STACK_SIZE){
				for(int i = 0 ; i < 2 ; i++)
					av1ctx->RefStackMv[ b_data->NumMvFound ][ i ] = candMvs[ i ] ;
				WeightStack[ b_data->NumMvFound ] = weight;
				b_data->NumMvFound += 1;

			}

		}
	}
	if(candMode == NEWMV ||
			candMode == NEW_NEWMV ||
			candMode == NEAR_NEWMV ||
			candMode == NEW_NEARMV ||
			candMode == NEAREST_NEWMV ||
			candMode == NEW_NEARESTMV)
	{
		b_data->NewMvCount += 1;
	}
}
//7.10.2.4
int decode::scan_point(int deltaRow,int deltaCol,int isCompound,
					TileData t_data,PartitionData p_data,BlockData *b_data,AV1DecodeContext *av1Ctx){
	int mvRow = MiRow + deltaRow;
	int mvCol = MiCol + deltaCol;
	int weight = 4;
	if((is_inside( mvRow, mvCol ) == 1) && RefFrames[ mvRow ][ mvCol ][ 0 ] != 0xff/*RefFrames[ mvRow ][ mvCol ][ 0 ] has been written*/ )
		add_ref_mv_candidate(mvRow,mvCol,isCompound,weight,t_data, p_data, b_data,av1Ctx);
}
//This process scans the motion vectors in a previous frame looking for candidates which use the same reference frame.
int decode::temporal_scan(int isCompound,BlockData *b_data)
{
	int bw4 = Num_4x4_Blocks_Wide[b_data->MiSize];
	int bh4 = Num_4x4_Blocks_High[b_data->MiSize];
	int stepW4 = (bw4 >= 16) ? 4 : 2;
	int stepH4 = (bh4 >= 16) ? 4 : 2;
	//scans the locations within the block
	for (int deltaRow = 0; deltaRow < Min(bh4, 16); deltaRow += stepH4)
	{
		for (int deltaCol = 0; deltaCol < Min(bw4, 16); deltaCol += stepW4)
		{
			add_tpl_ref_mv(deltaRow, deltaCol, isCompound);
		}
	}
	const uint8_t tplSamplePos[3][2] = {
		{ bh4, -2 }, { bh4, bw4 }, { bh4 - 2, bw4 }
	};

	// then scans positions around the block (but still within the same superblock)
	int allowExtension = ((bh4 >= Num_4x4_Blocks_High[BLOCK_8X8]) &&
					  (bh4 < Num_4x4_Blocks_High[BLOCK_64X64]) &&
					  (bw4 >= Num_4x4_Blocks_Wide[BLOCK_8X8]) &&
					  (bw4 < Num_4x4_Blocks_Wide[BLOCK_64X64])) ;
	if (allowExtension)
	{
		for (int i = 0; i < 3; i++)
		{
			int deltaRow = tplSamplePos[i][0];
			int deltaCol = tplSamplePos[i][1];
			if (check_sb_border(b_data->MiRow , b_data->MiCol,deltaRow, deltaCol))
			{
				add_tpl_ref_mv(deltaRow, deltaCol, isCompound);
			}
		}
	}
}

//7.10.2.6
//This process looks up a motion vector from the motion field and adds it into the stack.
int decode::add_tpl_ref_mv(int deltaRow, int deltaCol, int isCompound,BlockData *b_data)
{
	int mvRow = (b_data->MiRow + deltaRow) | 1;
	int mvCol = (b_data->MiCol + deltaCol) | 1;
	if (is_inside(mvRow, mvCol) == 0)
		return 0;
	int x8 = mvCol >> 1;
	int y8 = mvRow >> 1;

	if (deltaRow == 0 && deltaCol == 0)
	{
		b_data->ZeroMvContext = 1;
	}
	if (!isCompound)
	{
		int candMv[2] = MotionFieldMvs[RefFrame[0]][y8][x8];
		if (candMv[0] == -1 << 15)
			return;
		lower_mv_precision(candMv);
		if (deltaRow == 0 && deltaCol == 0)
		{
			if (Abs(candMv[0] - GlobalMvs[0][0]) >= 16 ||
				Abs(candMv[1] - GlobalMvs[0][1]) >= 16)
				b_data->ZeroMvContext = 1;
			else
				b_data->ZeroMvContext = 0;
		}
		int idx;
		for (idx = 0; idx < b_data->NumMvFound; idx++)
		{
			if (candMv[0] == av1ctx->RefStackMv[idx][0][0] &&
				candMv[1] == av1ctx->RefStackMv[idx][0][1])

				break;
		}
		if (idx < b_data->NumMvFound)
		{
			WeightStack[idx] += 2;
		}
		else if (b_data->NumMvFound < MAX_REF_MV_STACK_SIZE)
		{
			av1ctx->RefStackMv[b_data->NumMvFound][0] = candMv;
			WeightStack[b_data->NumMvFound] = 2;
			b_data->NumMvFound += 1;
		}
	}
	else
	{
		int candMv0[2] = MotionFieldMvs[RefFrame[0]][y8][x8];
		if (candMv0[0] == -1 << 15)
			return;
		int candMv1[2] = MotionFieldMvs[RefFrame[1]][y8][x8];
		if (candMv1[0] == -1 << 15)
			return;
		lower_mv_precision(candMv0);
		lower_mv_precision(candMv1);
		if (deltaRow == 0 && deltaCol == 0)
		{
			if (Abs(candMv0[0] - GlobalMvs[0][0]) >= 16 ||
				Abs(candMv0[1] - GlobalMvs[0][1]) >= 16 ||
				Abs(candMv1[0] - GlobalMvs[1][0]) >= 16 ||
				Abs(candMv1[1] - GlobalMvs[1][1]) >= 16)
				b_data->ZeroMvContext = 1;
			else
				b_data->ZeroMvContext = 0;
		}
		int idx;
		for (idx = 0; idx < b_data->NumMvFound; idx++)
		{
			if (candMv0[0] == av1ctx->RefStackMv[idx][0][0] &&
				candMv0[1] == av1ctx->RefStackMv[idx][0][1] &&
				candMv1[0] == av1ctx->RefStackMv[idx][1][0] &&
				candMv1[1] == av1ctx->RefStackMv[idx][1][1])
				break;
		}
		if (idx <b_data-> NumMvFound)
		{
			WeightStack[idx] += 2;
		}
		else if (b_data->NumMvFound < MAX_REF_MV_STACK_SIZE)
		{
			av1ctx->RefStackMv[b_data->NumMvFound][0] = candMv0;
			av1ctx->RefStackMv[b_data->NumMvFound][1] = candMv1;
			WeightStack[b_data->NumMvFound] = 2;
			b_data->NumMvFound += 1;
		}
	}
}
// performs a stable sort of part of the stack of motion vectors according to the corresponding weight.
int decode::Sorting(int start,int end ,int isCompound){
    while (end > start) {
        int newEnd = start;
        for (int idx = start + 1; idx < end; idx++) {
            if (WeightStack[idx - 1] < WeightStack[idx]) {
                swap_stack(idx - 1, idx, isCompound, av1ctx->RefStackMv, WeightStack);
                newEnd = idx;
            }
        }
        end = newEnd;
    }
}
void decode::swap_stack(int i, int j, int isCompound, int RefStackMv[][2][2], int WeightStack[]) {
    int temp = WeightStack[i];
    WeightStack[i] = WeightStack[j];
    WeightStack[j] = temp;
    
    for (int list = 0; list < 1 + isCompound; list++) {
        for (int comp = 0; comp < 2; comp++) {
            temp = av1ctx->RefStackMv[i][list][comp];
            av1ctx->RefStackMv[i][list][comp] = RefStackMv[j][list][comp];
            av1ctx->RefStackMv[j][list][comp] = temp;
        }
    }
}
//This process adds additional motion vectors to RefStackMv until it has 2 choices of motion vector by first searching the
//left and above neighbors for partially matching candidates, and second adding global motion candidates
int decode::extra_search(int isCompound)
{
	int RefIdCountp[2];
	int RefDiffCount[2];

	for (int list = 0; list < 2; list++)
	{
		RefIdCount[list] = 0;
		RefDiffCount[list] = 0;
	}
	int w4 = Min(16, Num_4x4_Blocks_Wide[MiSize]);
	int h4 = Min(16, Num_4x4_Blocks_High[MiSize]);
	int w4 = Min(w4, MiCols - MiCol);
	int h4 = Min(h4, MiRows - MiRow);
	int num4x4 = Min(w4, h4);
	//The first pass searches the row above, the second searches the column to the left.
	for (int pass = 0; pass < 2; pass++)
	{
		int idx = 0;
		while (idx < num4x4 && NumMvFound < 2)
		{
			int mvRow;
			int mvCol;
			if (pass == 0)
			{
				mvRow = MiRow - 1;
				mvCol = MiCol + idx;
			}
			else
			{
				mvRow = MiRow + idx;
				mvCol = MiCol - 1;
			}
			if (!is_inside(mvRow, mvCol))
				break;
			add_extra_mv_candidate(mvRow, mvCol, isCompound);
			if (pass == 0)
			{
				idx += Num_4x4_Blocks_Wide[MiSizes[mvRow][mvCol]];
			}
			else
			{
				idx += Num_4x4_Blocks_High[MiSizes[mvRow][mvCol]];
			}
		}
	}
	if (isCompound == 1)
	{
		for (int list = 0; list < 2; list++)
		{
			int compCount = 0;
			for (int idx = 0; idx < RefIdCount[list]; idx++)
			{
				combinedMvs[compCount][list] = RefIdMvs[list][idx];
				compCount++;
			}
			for (int idx = 0; idx < RefDiffCount[list] && compCount < 2; idx++)
			{
				combinedMvs[compCount][list] = RefDiffMvs[list][idx];
				compCount++;
			}
			while (compCount < 2)
			{
				combinedMvs[compCount][list] = GlobalMvs[list];
				compCount++;
			}
		}
		if (NumMvFound == 1)
		{
			if (combinedMvs[0][0] == av1ctx->RefStackMv[0][0] &&
				combinedMvs[0][1] == av1ctx->RefStackMv[0][1])
			{
				av1ctx->RefStackMv[NumMvFound][0] = combinedMvs[1][0];
				av1ctx->RefStackMv[NumMvFound][1] = combinedMvs[1][1];
			}
			else
			{
				av1ctx->RefStackMv[NumMvFound][0] = combinedMvs[0][0];
				av1ctx->RefStackMv[NumMvFound][1] = combinedMvs[0][1];
			}
			WeightStack[NumMvFound] = 2;
			NumMvFound++;
		}
		else
		{
			for (int idx = 0; idx < 2; idx++)
			{
				av1ctx->RefStackMv[NumMvFound][0] = combinedMvs[idx][0];
				av1ctx->RefStackMv[NumMvFound][1] = combinedMvs[idx][1];
				WeightStack[NumMvFound] = 2;
				NumMvFound++;
			}
		}
	}
	else
	{
		for (int idx = NumMvFound; idx < 2; idx++)
		{
			av1ctx->RefStackMv[idx][0] = GlobalMvs[0];
		}
	}
}
//This process may modify the contents of the global variables RefIdMvs, RefIdCount, RefDiffMvs, RefDiffCount,
//RefStackMv, WeightStack, and NumMvFound.
int decode::add_extra_mv_candidate(int mvRow, int mvCol, int isCompound)
{
	if (isCompound)
	{
		for (int candList = 0; candList < 2; candList++)
		{
			int candRef = RefFrames[mvRow][mvCol][candList];
			if (candRef > INTRA_FRAME)
			{
				for (int list = 0; list < 2; list++)
				{
					int candMv = Mvs[mvRow][mvCol][candList];
					if (candRef == RefFrame[list] && RefIdCount[list] < 2)
					{
						RefIdMvs[list][RefIdCount[list]] = candMv;
						RefIdCount[list]++;
					}
					else if (RefDiffCount[list] < 2)
					{
						if (RefFrameSignBias[candRef] != RefFrameSignBias[RefFrame[list]])
						{
							candMv[0] *= -1;
							candMv[1] *= -1;
						}
						RefDiffMvs[list][RefDiffCount[list]] = candMv;
						RefDiffCount[list]++;
					}
				}
			}
		}
	}
	else
	{
		for (int candList = 0; candList < 2; candList++)
		{
			int candRef = RefFrames[mvRow][mvCol][candList];
			if (candRef > INTRA_FRAME)
			{
				int candMv = Mvs[mvRow][mvCol][candList];
				if (RefFrameSignBias[candRef] != RefFrameSignBias[RefFrame[0]])
				{
					candMv[0] *= -1;
					candMv[1] *= -1;
				}
				for (int idx = 0; idx < NumMvFound; idx++)
				{
					if (candMv == av1ctx->RefStackMv[idx][0])
						break;
				}
				if (int idx == NumMvFound)
				{
					av1ctx->RefStackMv[idx][0] = candMv;
					WeightStack[idx] = 2;
					NumMvFound++;
				}
			}
		}
	}
}
//This process computes contexts to be used when decoding syntax elements, and clamps the candidates in RefStackMv
int decode::context_and_clamping(int isCompound, int numNew)
{
	int bw = 4 * Num_4x4_Blocks_Wide[MiSize];
	int bh = 4 * Num_4x4_Blocks_High[MiSize];
	int numLists = isCompound ? 2 : 1;
	for (int idx = 0; idx < NumMvFound; idx++)
	{
		int z = 0;
		if (idx + 1 < NumMvFound)
		{
			int w0 = WeightStack[idx];
			int w1 = WeightStack[idx + 1];
			if (w0 >= REF_CAT_LEVEL)
			{
				if (w1 < REF_CAT_LEVEL)
				{
					z = 1;
				}
			}
			else
			{
				z = 2;
			}
		}
		DrlCtxStack[idx] = z;
	}
	for (int list = 0; list < numLists; list++ ) {
		for (int idx = 0; idx < NumMvFound ; idx++ ) {
			int refMv[2] = av1ctx->RefStackMv[ idx ][ list ];
			refMv[ 0 ] = clamp_mv_row( refMv[ 0 ], MV_BORDER + bh * 8);
			refMv[ 1 ] = clamp_mv_col( refMv[ 1 ], MV_BORDER + bw * 8);
			av1ctx->RefStackMv[ idx ][ list ] = refMv;
		}
	}	
	if ( av1ctx->CloseMatches == 0 ) {
		av1ctx->NewMvContext = Min( av1ctx->TotalMatches, 1 ); // 0,1
		av1ctx->RefMvContext = av1ctx->TotalMatches;
	} else if ( av1ctx->CloseMatches == 1 ) {
		av1ctx->NewMvContext = 3 - Min( numNew, 1 ); // 2,3
		av1ctx->RefMvContext = 2 + av1ctx->TotalMatches;
	} else {
		av1ctx->NewMvContext = 5 - Min( numNew, 1 ); // 4,5
		av1ctx->RefMvContext = 5;
	}
}
int decode::clamp_mv_row( mvec, border ) { 
	int bh4 = Num_4x4_Blocks_High[ MiSize ];
	int mbToTopEdge = -((MiRow * MI_SIZE) * 8);
	int mbToBottomEdge = ((MiRows - bh4 - MiRow) * MI_SIZE) * 8;
	return Clip3( mbToTopEdge - border, mbToBottomEdge + border, mvec );
}
int decode::clamp_mv_col( mvec, border ) { 
	int bw4 = Num_4x4_Blocks_Wide[ MiSize ];
	int mbToLeftEdge = -((MiCol * MI_SIZE) * 8);
	int mbToRightEdge = ((MiCols - bw4 - MiCol) * MI_SIZE) * 8;
	return Clip3( mbToLeftEdge - border, mbToRightEdge + border, mvec );
}
int decode::lower_precision(int *candMv,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = av1Ctx->frameHdr;
	if(frameHdr->allow_high_precision_mv == 1)
		return 0;
	for (int i = 0; i < 2; i++)
	{
		if (frameHdr->force_integer_mv)
		{
			int a = Abs(candMv[i]);
			int aInt = (a + 3) >> 3;
			if (candMv[i] > 0)
				candMv[ i ] = aInt << 3;
			else
				candMv[i] = -(aInt << 3);
		}
		else
		{
			if (candMv[i] & 1)
			{
				if (candMv[i] > 0)
					candMv[i]--;
				else
					candMv[i]++;
			}
		}
	}
}
int decode::residual()
{
	sbMask = use_128x128_superblock ? 31 : 15;
	widthChunks = Max(1, Block_Width[MiSize] >> 6)
		heightChunks = Max(1, Block_Height[MiSize] >> 6)
			miSizeChunk = (widthChunks > 1 || heightChunks > 1) ? BLOCK_64X64 : MiSize;
	for (chunkY = 0; chunkY < heightChunks; chunkY++)
	{
		for (chunkX = 0; chunkX < widthChunks; chunkX++)
		{
			miRowChunk = MiRow + (chunkY << 4);
			miColChunk = MiCol + (chunkX << 4);
			subBlockMiRow = miRowChunk & sbMask;
			subBlockMiCol = miColChunk & sbMask;
			for (plane = 0; plane < 1 + HasChroma * 2; plane++)
			{
				txSz = Lossless ? TX_4X4 : get_tx_size(plane, TxSize);
				stepX = Tx_Width[txSz] >> 2;
				stepY = Tx_Height[txSz] >> 2;
				planeSz = get_plane_residual_size(miSizeChunk, plane);
				num4x4W = Num_4x4_Blocks_Wide[planeSz];
				num4x4H = Num_4x4_Blocks_High[planeSz];
				subX = (plane > 0) ? subsampling_x : 0;
				subY = (plane > 0) ? subsampling_y : 0;
				baseX = (miColChunk >> subX) * MI_SIZE;
				baseY = (miRowChunk >> subY) * MI_SIZE;
				if (is_inter && !Lossless && !plane)
				{
					transform_tree(baseX, baseY, num4x4W * 4, num4x4H * 4);
				}
				else
				{
					baseXBlock = (MiCol >> subX) * MI_SIZE;
					baseYBlock = (MiRow >> subY) * MI_SIZE;
					for (y = 0; y < num4x4H; y += stepY)
						for (x = 0; x < num4x4W; x += stepX)
							transform_block(plane, baseXBlock, baseYBlock, txSz,
											x + ((chunkX << 4) >> subX),
											y + ((chunkY << 4) >> subY));
				}
			}
		}
	}
}
int decode::transform_tree(startX, startY, w, h)
{
	maxX = MiCols * MI_SIZE;
	maxY = MiRows * MI_SIZE;
	if (startX >= maxX || startY >= maxY)
	{
		return;
	}
	row = startY >> MI_SIZE_LOG2;
	col = startX >> MI_SIZE_LOG2;
	lumaTxSz = InterTxSizes[row][col];
	lumaW = Tx_Width[lumaTxSz];
	lumaH = Tx_Height[lumaTxSz];
	if (w <= lumaW && h <= lumaH)
	{
		txSz = find_tx_size(w, h);
		transform_block(0, startX, startY, txSz, 0, 0);
	}
	else
	{
		if (w > h)
		{
			transform_tree(startX, startY, w / 2, h);
			transform_tree(startX + w / 2, startY, w / 2, h);
		}
		else if (w < h)
		{
			transform_tree(startX, startY, w, h / 2);
			transform_tree(startX, startY + h / 2, w, h / 2);
		}
		else
		{
			transform_tree(startX, startY, w / 2, h / 2);
			transform_tree(startX + w / 2, startY, w / 2, h / 2);
			transform_tree(startX, startY + h / 2, w / 2, h / 2);
			transform_tree(startX + w / 2, startY + h / 2, w / 2, h / 2);
		}
	}
}
int decode::transform_block(plane, baseX, baseY, txSz, x, y)
{
	startX = baseX + 4 * x;
	startY = baseY + 4 * y;
	subX = (plane > 0) ? subsampling_x : 0;
	subY = (plane > 0) ? subsampling_y : 0;
	row = (startY << subY) >> MI_SIZE_LOG2;
	col = (startX << subX) >> MI_SIZE_LOG2;
	sbMask = use_128x128_superblock ? 31 : 15;
	subBlockMiRow = row & sbMask;
	subBlockMiCol = col & sbMask;
	stepX = Tx_Width[txSz] >> MI_SIZE_LOG2;
	stepY = Tx_Height[txSz] >> MI_SIZE_LOG2;
	maxX = (MiCols * MI_SIZE) >> subX;
	maxY = (MiRows * MI_SIZE) >> subY;
	if (startX >= maxX || startY >= maxY)
	{
		return;
	}
	if (!is_inter)
	{
		if (((plane == 0) && PaletteSizeY) ||
			((plane != 0) && PaletteSizeUV))
		{
			predict_palette(plane, startX, startY, x, y, txSz);
		}
		else
		{
			isCfl = (plane > 0 && UVMode == UV_CFL_PRED);
			if (plane == 0)
			{
				mode = YMode;
			}
			else
			{
				mode = (isCfl) ? DC_PRED : UVMode;
			}
			log2W = Tx_Width_Log2[txSz] log2H = Tx_Height_Log2[txSz] ;
			predict_intra(plane, startX, startY,
						(plane == 0 ? AvailL : AvailLChroma) || x > 0,
						(plane == 0 ? AvailU : AvailUChroma) || y > 0,
						BlockDecoded[plane][(subBlockMiRow >> subY) - 1][(subBlockMiCol >> subX) + stepX],
						BlockDecoded[plane][(subBlockMiRow >> subY) + stepY][(subBlockMiCol >> subX) - 1],
						mode,
						log2W, log2H);
			if (isCfl)
			{
				predict_chroma_from_luma(plane, startX, startY, txSz);
			}
		}
		if (plane == 0)
		{
			MaxLumaW = startX + stepX * 4;
			MaxLumaH = startY + stepY * 4;
		}
	}
	if (!skip)
	{
		eob = coeffs(plane, startX, startY, txSz);
		if (eob > 0)
			reconstruct(plane, startX, startY, txSz);
	}
	for (i = 0; i < stepY; i++)
	{
		for (j = 0; j < stepX; j++)
		{
			LoopfilterTxSizes[plane]
							 [(row >> subY) + i]
							 [(col >> subX) + j] = txSz;
			BlockDecoded[plane]
						[(subBlockMiRow >> subY) + i]
						[(subBlockMiCol >> subX) + j] = 1;
		}
	}
}
int decode::coeffs(plane, startX, startY, txSz)
{
	x4 = startX >> 2;
	y4 = startY >> 2;
	w4 = Tx_Width[txSz] >> 2;
	h4 = Tx_Height[txSz] >> 2;
	txSzCtx = (Tx_Size_Sqr[txSz] + Tx_Size_Sqr_Up[txSz] + 1) >> 1;
	ptype = plane > 0;
	segEob = (txSz == TX_16X64 || txSz == TX_64X16) ? 512 : Min(1024, Tx_Width[txSz] * Tx_Height[txSz]);
	for (c = 0; c < segEob; c++)
		Quant[c] = 0;
	for (i = 0; i < 64; i++)
		for (j = 0; j < 64; j++)
			Dequant[i][j] = 0;
	eob = 0;
	culLevel = 0;
	dcCategory = 0;
	all_zero; // S()
	if (all_zero)
	{
		c = 0;
		if (plane == 0)
		{
			for (i = 0; i < w4; i++)
			{
				for (j = 0; j < h4; j++)
				{
					TxTypes[y4 + j][x4 + i] = DCT_DCT;
				}
			}
		}
	}
	else
	{
		if (plane == 0)
			transform_type(x4, y4, txSz);
		PlaneTxType = compute_tx_type(plane, txSz, x4, y4);
		scan = get_scan(txSz);
		eobMultisize = Min(Tx_Width_Log2[txSz], 5) + Min(Tx_Height_Log2[txSz], 5) - 4;
		if (eobMultisize == 0)
		{
			eob_pt_16; // S()
			eobPt = eob_pt_16 + 1;
		}
		else if (eobMultisize == 1)
		{
			eob_pt_32; // S()
			eobPt = eob_pt_32 + 1;
		}
		else if (eobMultisize == 2)
		{
			eob_pt_64; // S()
			eobPt = eob_pt_64 + 1;
		}
		else if (eobMultisize == 3)
		{
			eob_pt_128; // S()
			eobPt = eob_pt_128 + 1;
		}
		else if (eobMultisize == 4)
		{
			eob_pt_256; // S()
			eobPt = eob_pt_256 + 1;
		}
		else if (eobMultisize == 5)
		{
			eob_pt_512; // S()
			eobPt = eob_pt_512 + 1;
		}
		else
		{
			eob_pt_1024; // S()
			eobPt = eob_pt_1024 + 1;
		}
		eob = (eobPt < 2) ? eobPt : ((1 << (eobPt - 2)) + 1);
		eobShift = Max(-1, eobPt - 3);
		if (eobShift >= 0)
		{
			eob_extra; // S()
			if (eob_extra)
			{
				eob += (1 << eobShift);
			}
			for (i = 1; i < Max(0, eobPt - 2); i++)
			{
				eobShift = Max(0, eobPt - 2) - 1 - i;
				eob_extra_bit; // L(1)
				if (eob_extra_bit)
				{
					eob += (1 << eobShift);
				}
			}
		}
		for (c = eob - 1; c >= 0; c--)
		{
			pos = scan[c];
			if (c == (eob - 1))
			{
				coeff_base_eob; // S()
				level = coeff_base_eob + 1;
			}
			else
			{
				coeff_base; // S()
				level = coeff_base;
			}
			if (level > NUM_BASE_LEVELS)
			{
				for (idx = 0;
					 idx < COEFF_BASE_RANGE / (BR_CDF_SIZE - 1);
					 idx++)
				{
					coeff_br; // S()
					level += coeff_br;
					if (coeff_br < (BR_CDF_SIZE - 1))
						break;
				}
			}
			Quant[pos] = level;
		}
		for (c = 0; c < eob; c++)
		{
			pos = scan[c];
			if (Quant[pos] != 0)
			{
				if (c == 0)
				{
					dc_sign; // S()
					sign = dc_sign;
				}
				else
				{
					sign_bit; // L(1)
					sign = sign_bit;
				}
			}
			else
			{
				sign = 0;
			}
			if (Quant[pos] >
				(NUM_BASE_LEVELS + COEFF_BASE_RANGE))
			{
				length = 0;
				do
				{
					length++;
					golomb_length_bit; // L(1)
				} while (!golomb_length_bit)
					x = 1;
				for (i = length - 2; i >= 0; i--)
				{
					golomb_data_bit; // L(1)
					x = (x << 1) | golomb_data_bit;
				}
				Quant[pos] = x + COEFF_BASE_RANGE + NUM_BASE_LEVELS;
			}
			if (pos == 0 && Quant[pos] > 0)
			{
				dcCategory = sign ? 1 : 2;
			}
			Quant[pos] = Quant[pos] & 0xFFFFF;
			culLevel += Quant[pos];
			if (sign)
				Quant[pos] = -Quant[pos];
		}
		culLevel = Min(63, culLevel);
	}
	for (i = 0; i < w4; i++)
	{
		AboveLevelContext[plane][x4 + i] = culLevel;
		AboveDcContext[plane][x4 + i] = dcCategory;
	}
	for (i = 0; i < h4; i++)
	{
		LeftLevelContext[plane][y4 + i] = culLevel;
		LeftDcContext[plane][y4 + i] = dcCategory;
	}
	return eob;
}
/*  find mv stack end ...*/
//7.10.3
int decode::has_overlappable_candidates(PartitionData *p_data, BlockData *b_data)
{
	if (b_data->AvailU)
	{
		int w4 = Num_4x4_Blocks_Wide[b_data->MiSize];
		for (int x4 = b_data->MiCol; x4 < Min(p_data->MiCols, b_data->MiCol + w4); x4 += 2)
		{
			if (RefFrames[b_data->MiRow - 1][x4 | 1][0] > INTRA_FRAME)
				return 1;
		}
	}
	if (b_data->AvailL)
	{
		int h4 = Num_4x4_Blocks_High[b_data->MiSize];
		for (int y4 = b_data->MiRow; y4 < Min(p_data->MiRows, b_data->MiRow + h4); y4 += 2)
		{
			if (RefFrames[y4 | 1][b_data->MiCol - 1][0] > INTRA_FRAME)
				return 1;
		}
	}
	return 0;
}

//7.10.4
//The process examines the neighboring inter predicted blocks and estimates a local warp transformation based on the
//motion vectors.
//The process produces a variable NumSamples containing the number of valid candidates found, and an array CandList
//containing sorted candidates.
int decode::find_warp_samples(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx)
{
	frameHeader *frameHdr = av1ctx->curFrameHdr;
	int doTopLeft = 1;
	int doTopRight = 1;
	av1ctx->NumSamples = 0;
	av1ctx->NumSamplesScanned = 0;
	int w4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
	int h4 = Num_4x4_Blocks_High[ b_data->MiSize ];
	if (b_data->AvailU)
	{
		int srcSize = p_data->MiSizes[b_data->MiRow - 1][b_data->MiCol];
		int srcW = Num_4x4_Blocks_Wide[srcSize];
		if (w4 <= srcW)
		{
			int colOffset = -(b_data->MiCol & (srcW - 1));
			if (colOffset < 0)
				doTopLeft = 0;
			if (colOffset + srcW > w4)
				doTopRight = 0;
			add_sample(-1, 0);
		}
		else
		{
			int miStep = 0;//???
			for (int i = 0; i < Min(w4,frameHdr->MiCols - b_data->MiCol); i += miStep)
			{
				srcSize = MiSizes[b_data->MiRow - 1][b_data->MiCol + i];
				srcW = Num_4x4_Blocks_Wide[srcSize];
				miStep = Min(w4, srcW);
				add_sample(-1, i);
			}
		}
	}
	if (b_data->AvailL)
	{
		int srcSize = MiSizes[b_data->MiRow][b_data->MiCol - 1];
		int srcH = Num_4x4_Blocks_High[srcSize];
		if (h4 <= srcH)
		{
			int rowOffset = -(b_data->MiRow & (srcH - 1));
			if (rowOffset < 0)
				doTopLeft = 0;
			add_sample(0, -1);
		}
		else
		{
			int miStep = 0;//???
			for (int i = 0; i < Min(h4, frameHdr->MiRows - b_data->MiRow); i += miStep)
			{
				srcSize = MiSizes[b_data->MiRow + i][b_data->MiCol - 1];
				srcH = Num_4x4_Blocks_High[srcSize];
				miStep = Min(h4, srcH);
				add_sample(i, -1);
			}
		}
	}
	if (doTopLeft)
	{
		add_sample(-1, -1);
	}
	if (doTopRight)
	{
		if (Max(w4, h4) <= 16)
		{
			add_sample(-1, w4);
		}
	}
	if (av1ctx->NumSamples == 0 && av1ctx->NumSamplesScanned > 0)
		av1ctx->NumSamples = 1;
}
int decode::add_sample(int deltaRow,int deltaCol){
    if (NumSamplesScanned >= LEAST_SQUARES_SAMPLES_MAX) {
        return; 
    }

    int mvRow = MiRow + deltaRow;
    int mvCol = MiCol + deltaCol;

    if (!is_inside(mvRow, mvCol)) {
        return; 
    }

    if (!isWrittenFrame[mvRow][mvCol][0]) {
        return; 
    }

    if (RefFrames[mvRow][mvCol][0] != RefFrame[0]) {
        return; 

    if (RefFrames[mvRow][mvCol][1] != NONE) {
        return; 
    }

    int candSz = MiSizes[mvRow][mvCol];
    int candW4 = Num_4x4_Blocks_Wide[candSz];
    int candH4 = Num_4x4_Blocks_High[candSz];
    int candRow = mvRow & ~(candH4 - 1);
    int candCol = mvCol & ~(candW4 - 1);
    int midY = candRow * 4 + candH4 * 2 - 1;
    int midX = candCol * 4 + candW4 * 2 - 1;
    int threshold = Clip3(16, 112, max(Block_Width[MiSize], Block_Height[MiSize]));
    int mvDiffRow = abs(Mvs[candRow][candCol][0][0] - Mv[0][0]);
    int mvDiffCol = abs(Mvs[candRow][candCol][0][1] - Mv[0][1]);
    int valid = ((mvDiffRow + mvDiffCol) <= threshold);

    CandList[NumSamples][0] = midY * 8;
    CandList[NumSamples][1] = midX * 8;
    CandList[NumSamples][2] = midY * 8 + Mvs[candRow][candCol][0][0];
    CandList[NumSamples][3] = midX * 8 + Mvs[candRow][candCol][0][1];

    NumSamplesScanned++;

    if (valid == 1) {
        NumSamples++;
    }

    if (valid == 0 && NumSamplesScanned > 1) {
        return;
    }


}
int decode::get_above_tx_width(int row, int col,PartitionData *p_data,BlockData *b_data)
{
	if (row == b_data->MiRow)
	{
		if (!b_data->AvailU)
		{
			return 64;
		}
		else if (Skips[row - 1][col] && IsInters[row - 1][col])
		{
			return 4 * Num_4x4_Blocks_Wide[p_data->MiSizes[row - 1][col]];
		}
	}
	return Tx_Width[InterTxSizes[row - 1][col]];
}
int decode::get_left_tx_height(int row,int col,PartitionData *p_data,BlockData *b_data)
{
	if (col == b_data->MiCol)
	{
		if (!b_data->AvailL)
		{
			return 64;
		}
		else if (p_data->Skips[row][col - 1] && p_data->IsInters[row][col - 1])
		{
			return 4 * Num_4x4_Blocks_Wide[p_data->MiSizes[row][col - 1]];
		}
	}
	return Tx_Height[p_data->InterTxSizes[row][col - 1]];
}

/*帧内预测*/
//The process makes use of the already reconstructed samples in the current frame CurrFrame to form a 
//prediction for the current block.

int decode::predict_intra(int plane,int x,int y,int haveLeft,int haveAbove,
				int haveAboveRight,int haveBelowLeft,int mode,int log2W,int log2H,
				PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1){

	int w = 1 << log2W;
	int h = 1 << log2H;
	int maxX = ( MiCols * MI_SIZE ) - 1;
	int maxY = ( MiRows * MI_SIZE ) - 1;

	if(plane > 0){
		maxX = ( ( MiCols * MI_SIZE ) >> subsampling_x ) - 1;
		maxY = ( ( MiRows * MI_SIZE ) >> subsampling_y ) - 1;
	}

    for (int i = 0; i < w + h - 1; i++) {
        if (haveAbove == 0 && haveLeft == 1) {
            // 如果haveAbove为0且haveLeft为1，设置AboveRow[i]等于左侧的像素值
            AboveRow[i] = CurrFrame[y][x - 1];
        } else if (haveAbove == 0 && haveLeft == 0) {
            // 如果haveAbove和haveLeft都为0，设置AboveRow[i]为(1 << (BitDepth - 1)) - 1
            AboveRow[i] = (1 << (BitDepth - 1)) - 1;
        } else {
            // 如果以上两个条件都不满足
            int aboveLimit = x + (haveAboveRight ? 2 * w : w) - 1;
            AboveRow[i] = CurrFrame[plane][y - 1][Min(aboveLimit, x+i)];
        }

    }
    for (int i = 0; i < w + h - 1; i++) {
        if (haveLeft == 0 && haveAbove == 1) {
            // 如果haveLeft为0且haveAbove为1，设置LeftCol[i]等于上方的像素值
            LeftCol[i] = CurrFrame[y - 1][x];
        } else if (haveLeft == 0 && haveAbove == 0) {
            // 如果haveLeft和haveAbove都为0，设置LeftCol[i]为(1 << (BitDepth - 1)) + 1
            LeftCol[i] = (1 << (BitDepth - 1)) + 1;
        } else {
            // 如果以上两个条件都不满足
            int leftLimit = y + (haveBelowLeft ? 2 * h : h) - 1;
            LeftCol[i] = CurrFrame[plane][Min(leftLimit, y+i)][x - 1];
        }
    }
	if(haveAbove == 1 && haveLeft == 1){
		AboveRow[ -1 ] == [ plane ][ y-1 ][x-1 ];
	}else if(haveAbove == 1){
		AboveRow[ -1 ] == [ plane ][ y-1 ][x ];
	}else if(haveLeft == 1) {
		AboveRow[ -1 ] == [ plane ][ y ][x-1 ];
	}else{
		AboveRow[ -1 ] == 1 << ( BitDepth - 1 ).;
	}
	LeftCol[ -1 ] = AboveRow[ -1 ];

	if(plane == 0 && use_filter_intra){
		recursiveIntraPrdiction();
	}else if( is_directional_mode( mode ) ){
		DCIntraPrediction();
	}else if(mode == SMOOTH_PRED || mode == SMOOTH_V_PRED  || mode == SMOOTH_H_PRED ){
		smoothIntraPrediction(); 
	}
}
//7.11.2.3
//For each block of 4x2 samples, this process first prepares an array p of 7 neighboring samples, and then produces the
//output block by filtering this array
//输入指定的区域，将之分割为一个一个的 4 * 2小块，进行一系列操作(预测，滤波)生成帧内预测样本
//输出在 pred数组中
int decode::recursiveIntraPrdiction(int w, int h,uint8_t **pred)
{
	int w4 = w >> 2;
	int h2 = h >> 1;
	int i;

	for (int i2 = 0; i2 < h2 - 1; i2++)
	{
		for (int j4 = 0; j4 < w4 - 1; j4++)
		{
			//对于每个 4 * 2块，做以下操作

			//这个循环为当前 4 * 2块准备一个数组，包含7个样本
			uint8_t p[7];
			for (i = 0; i < 7; i++)
			{
				if (i < 5)
				{
					if (i2 == 0)
					{
						p[i][j4 * 4 + i] = AboveRow[(j4 << 2) + i - (i + 1)];
					}
					else if (j4 == 0 && i == 0)
					{
						p[i][j4 * 4 + i] = LeftCol[(i2 << 1) - 1];
					}
					else
					{
						p[i][j4 * 4 + i] = pred[(i + 1) * 4][(j4 << 2) + i - (i + 1)];
					}
				}
				else
				{
					if (j4 == 0)
					{
						p[i][j4 * 4 + i] = LeftCol[(i2 << 1) + i - 4];
					}
					else
					{
						p[i][j4 * 4 + i] = pred[(i + 1) * 4 + 1][(j4 << 2) - (i + 1)];
					}
				}
			}
			//对当前 4 * 2 块内的每一个像素 进行滤波处理
			for (int i1 = 0; i1 < 2; i1++)
			{
				for (int j1 = 0; j1 < 4; j1++)
				{
					int pr = 0;
					for (int i = 0; i < 7; i++)
					{
						pr += Intra_Filter_Taps[filter_intra_mode][i1][j1][i] * pred[i][(j4 << 2) + i];
					}
					pred[(i2 << 1) + i1][(j4 << 2) + j1] = Clip1(Round2Signed(pr / INTRA_FILTER_SCALE_BITS));
				}
			}
		}
	}
}
//7.11.2.4
//The process uses a directional filter to generate filtered samples from the samples in LeftCol and AboveRow
//使用“方向滤波器”和左侧、上边的像素进行帧内预测，生成帧内预测样本
//这就是最常见的帧内预测模式
int decode::directionalIntraPrediction(int plane,int x,int y,int haveLeft,int haveAbove,
								int mode ,int w ,int h ,int maxX,int maxY,uint8_t **pred){
	int angleDelta = plane == 0 ? AngleDeltaY : AngleDeltaUV;
	int pAngle = ( Mode_To_Angle[ mode ] + angleDelta * ANGLE_STEP );
	int upsampleAbove = 0;
	int upsampleLeft = 0;
	if(enable_intra_edge_filter == 1){
		if(pAngle != 90 && pAngle != 180){
			if(pAngle > 90 && pAngle < 180 && (w + h)){
				//7.11.2.7
				filterCornor(LeftCol,AboveRow);
			}
			//7.11.2.8
			intrafilterType(); 
			if(haveAbove == 1){
				//7.11.2.9
				int strength = intraEdgeFilterStrengthSelection(w,h,filterType,pAngle - 90 );
				int numPx =  Min( w, ( maxX - x + 1 ) ) + ( pAngle < 90 ? h : 0 ) + 1;
				//7.11.2.12 
				intraEdgeFilter(numPx,strength,0);
			}
			if(haveLeft == 1){
				int strength = intraEdgeFilterStrengthSelection(w,h,filterType,pAngle - 180 );
				int numPx =   Min( h, ( maxY - y + 1 ) ) + ( pAngle > 180 ? w : 0 ) + 1;
				//7.11.2.12 
				intraEdgeFilter(numPx,strength,1);
			}
		}

		//7.11.2.10
		int upsampleAbove = intraEdgeUpsampleSelection(w,h,filterType,pAngle - 90 );
		int numPx = ( w + (pAngle < 90 ? h : 0) );
		if(upsampleAbove == 1){
			//7.11.2.11
			 intraEdgeUpsample(numPx,0);
		}
		int upsampleLeft = intraEdgeUpsampleSelection(w,h,filterType,pAngle - 180 );
		numPx = ( h + (pAngle > 180 ? w : 0) );
		if(upsampleLeft == 1){
			intraEdgeUpsample(numPx,1);
		}
	}

	int dx;
	if( < 90)
		dx = Dr_Intra_Derivative[ pAngle ];
	else if(pAngle > 90 && pAngle < 180)
		dx =	Dr_Intra_Derivative[ 180 - pAngle ];
	else{
		//dx should be undefined;
	}
	
	int dy;
	if( dy > 90 && dy < 180)
		dy = Dr_Intra_Derivative[ pAngle - 90 ];
	else if(pAngle > 180)
		dy =	Dr_Intra_Derivative[ 270 - pAngle ];
	else{
		//dx should be undefined;
	}

	if(pAngle < 90){
			for(int i = 0 ; i < h){
				for(int j = 0 ; j < w ; j++){
					int idx = ( i + 1 ) * dx;
					int base = (idx >> ( 6 - upsampleAbove ) ) + (j << upsampleAbove);
					int shift = ( (idx << upsampleAbove) >> 1 ) & 0x1F;
					int maxBaseX = (w + h - 1) << upsampleAbove;
					if(base < maxBaseX){
							pred[ i ][ j ] = Round2( AboveRow[ base ] * ( 32 - shift ) + AboveRow[ base + 1 ] * shift, 5 );
					}else{
						pred[ i ][ j ] = AboveRow[maxBaseX ];
					}
				}
			}

	}else if(pAngle > 90 && pAngle < 180){

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int idx, base, shift;
				
				int idx = (j << 6) - (i + 1) * dx;
				
				int base = idx >> (6 - upsampleAbove);
				
				if (base >= -(1 << upsampleAbove)) {
					int shift = ((idx << upsampleAbove) >> 1) & 0x1F;

					pred[i][j] = Round2(AboveRow[base] * (32 - shift) + AboveRow[base + 1] * shift, 5);
				} else {
					int idx = (i << 6) - (j + 1) * dy;
					base = idx >> (6 - upsampleLeft);
					
					shift = ((idx << upsampleLeft) >> 1) & 0x1F;

					pred[i][j] = Round2(LeftCol[base] * (32 - shift) + LeftCol[base + 1] * shift, 5);
				}
			}
		}

	}else if(pAngle > 180){
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int idx, base, shift;

				idx = (j + 1) * dy;

				base = (idx >> (6 - upsampleLeft)) + (i << upsampleLeft);

				shift = ((idx << upsampleLeft) >> 1) & 0x1F;

				pred[i][j] = Round2(LeftCol[base] * (32 - shift) + LeftCol[base + 1] * shift, 5);
			}
		}
	}
	else if (pAngle == 90)
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				pred[i][j] = AboveRow[j];
			}
		}
	}
	else if (pAngle == 180)
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				pred[i][j] = LeftCol[i];
			}
		}
	}
}
//7.11.2.5
//DC 模式帧内预测
//DC 模式 ，就是算平均值
/*
	| | | | | | AboveRow
	| |x x x x
	| |x x x x
	| |x x x x
	| |x x x x
  LeftCol
  如果 左侧上边都有效，则 计算 左侧列 和上边行像素总平均值
   否则只有行左侧列或者右侧行有效，则只考虑一边的平均值
   把平均值赋给块内每一个像素
*/
int decode::DCIntraPrediction(int haveLeft ,int haveAbove,int log2W,int log2H,int w,int h,int **pred)
{

	int sum = 0;
	int avg, leftAvg, aboveAvg;

	// Calculate the average of available edge samples
	if (haveLeft == 1 && haveAbove == 1)
	{
		// Case 1: Both left and above samples are available
		sum = 0;
		for (int k = 0; k < h; k++)
			sum += LeftCol[k];
		for (int k = 0; k < w; k++)
			sum += AboveRow[k];
		sum += (w + h) >> 1;
		avg = sum / (w + h);

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				pred[i][j] = avg;
			}
		}
	}
	else if (haveLeft == 1 && haveAbove == 0)
	{
		// Case 2: Only left samples are available
		for (int k = 0; k < h; k++)
		{
			sum += LeftCol[k];
		}
		leftAvg = Clip1((sum + (h >> 1)) >> log2H);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				pred[i][j] = leftAvg;
			}
		}
	}
	else if (haveLeft == 0 && haveAbove == 1)
	{
		// Case 3: Only above samples are available
		for (int k = 0; k < w; k++)
		{
			sum += AboveRow[k];
		}
		aboveAvg = Clip1((sum + (w >> 1)) >> log2W);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				pred[i][j] = aboveAvg;
			}
		}
	}
	else
	{
		// Case 4: No valid samples available
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				pred[i][j] = 1 << (BitDepth - 1);
			}
		}
	}
}
//7.11.2.7 
//使用插值的方法生成预测像素
//smWeights* 是一个权重值，用来
int decode::smoothIntraPrediction(int mode, int log2W, int log2H, int w, int h, int *LeftCol, int *AboveRow, int **pred){
    if (mode == SMOOTH_PRED) {
        const int *smWeightsX;
        const int *smWeightsY;
 		if(log2W == 2){
			smWeightsX = Sm_Weights_Tx_4x4;
		}else if(log2W == 3){
			smWeightsX = Sm_Weights_Tx_8x8;
		}else if(log2W == 4){
			smWeightsX = Sm_Weights_Tx_16x16;
		}else if(log2W == 5){	
			smWeightsX = Sm_Weights_Tx_32x32;
		}else if(log2W == 6){
			smWeightsX = Sm_Weights_Tx_64x64;
		}

 		if(log2H == 2){
			 smWeightsY = Sm_Weights_Tx_4x4; 
		}else if(log2H == 3){
			smWeightsY = Sm_Weights_Tx_8x8;
		}else if(log2H == 4){
			smWeightsY = Sm_Weights_Tx_16x16;
		}else if(log2H == 5){	
			smWeightsY = Sm_Weights_Tx_32x32;
		}else if(log2H == 6){
			smWeightsY = Sm_Weights_Tx_64x64;
		}
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int smoothPred = smWeightsY[i] * AboveRow[j] +
                                 (256 - smWeightsY[i]) * LeftCol[h - 1] +
                                 smWeightsX[j] * LeftCol[i] +
                                 (256 - smWeightsX[j]) * AboveRow[w - 1];
                pred[i][j] = Round2(smoothPred, 9);
            }
        }
    } else if (mode == SMOOTH_V_PRED) {
        const int *smWeights;
 		if(log2W == 2){
			smWeights = Sm_Weights_Tx_4x4;
		}else if(log2W == 3){
			smWeights = Sm_Weights_Tx_8x8;
		}else if(log2W == 4){
			smWeights = Sm_Weights_Tx_16x16;
		}else if(log2W == 5){	
			smWeights = Sm_Weights_Tx_32x32;
		}else if(log2W == 6){
			smWeights = Sm_Weights_Tx_64x64;
		}
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int smoothPred = smWeights[i] * AboveRow[j] +
                                 (256 - smWeights[i]) * LeftCol[h - 1];
                pred[i][j] = Round2(smoothPred, 8);
            }
        }
    } else if (mode == SMOOTH_H_PRED) {
        const int *smWeights;
 		if(log2W == 2){
			smWeights = Sm_Weights_Tx_4x4;
		}else if(log2W == 3){
			smWeights = Sm_Weights_Tx_8x8;
		}else if(log2W == 4){
			smWeights = Sm_Weights_Tx_16x16;
		}else if(log2W == 5){	
			smWeights = Sm_Weights_Tx_32x32;
		}else if(log2W == 6){
			smWeights = Sm_Weights_Tx_64x64;
		}
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int smoothPred = smWeights[j] * LeftCol[i] +
                                 (256 - smWeights[j]) * AboveRow[w - 1];
                pred[i][j] = Round2(smoothPred, 8);
            }
        }
    }

}
//7.11.2.7 使用一个三抽头滤波器对 leftcol aboverow角落像素进行滤波
int decode::filterCornor(Array8 *LeftCol,Array8 *AboveRow){
	int s = (*LeftCol)[ 0 ] * 5 + (*AboveRow)[ -1 ] * 6 + (*AboveRow)[ 0 ] * 5;
	LeftCol[-1] = Round2(s, 4);
	AboveRow[-1] = Round2(s, 4);
}
//7.11.2.8
//如果左边或上边的块使用了smooth mode ，则返回值为1
int decode::intrafilterType(iny plane){
	return get_filter_type(plane);
}


int decode::is_smooth(int row, int col, int plane) {
    int mode;
    if (plane == 0) {
        mode = YModes[row][col];
    } else {
        if (RefFrames[row][col][0] > INTRA_FRAME) {
            return 0;
        }
        mode = UVModes[row][col];
    }
    return (mode == SMOOTH_PRED || mode == SMOOTH_V_PRED || mode == SMOOTH_H_PRED);
}

int decode::get_filter_type(int plane) {
    int aboveSmooth = 0;
    int leftSmooth = 0;
    int r, c;

    if ((plane == 0) ? AvailU : AvailUChroma) {
        r = MiRow - 1;
        c = MiCol;

        if (plane > 0) {
            if (subsampling_x && !(MiCol & 1)) {
                c++;
            }
            if (subsampling_y && (MiRow & 1)) {
                r--;
            }
        }

        aboveSmooth = is_smooth(r, c, plane);
    }

    if ((plane == 0) ? AvailL : AvailLChroma) {
        r = MiRow;
        c = MiCol - 1;

        if (plane > 0) {
            if (subsampling_x && (MiCol & 1)) {
                c--;
            }
            if (subsampling_y && !(MiRow & 1)) {
                r++;
            }
        }

        leftSmooth = is_smooth(r, c, plane);
    }

    return aboveSmooth || leftSmooth;
}
//7.11.2.9
//滤波强度
int decode::intraEdgeFilterStrengthSelection(int w, int h, int filterType, int delta)
{
	int  d =  Abs( delta );
	int  blkWh =  w + h;
	int strength = 0;
	if (filterType == 0)
	{
		if (blkWh <= 8)
		{
			if (d >= 56)
				strength = 1;
		}
		else if (blkWh <= 12)
		{
			if (d >= 40)
				strength = 1
		}
		else if (blkWh <= 16)
		{
			if (d >= 40)
				strength = 1
		}
		else if (blkWh <= 24)
		{
			if (d >= 8)
				strength = 1;
			if (d >= 16)1
			if (d >= 32)
				strength = 3;
		}
		else if (blkWh <= 32)
		{
			strength = 1;
			if (d >= 4)
				strength = 2;
			if (d >= 32)
				strength = 3;
		}
		else
		{
			strength = 3;
		}
	}
	else
	{
		if (blkWh <= 8)
		{
			if (d >= 40)
				strength = 1;
			if (d >= 64)
				strength = 2;
		}
		else if (blkWh <= 16)
		{
			if (d >= 20)
				strength = 1;
			if (d >= 48)
				strength = 2;
		}
		else if (blkWh <= 24)
		{
			if (d >= 4)
				strength = 3;
		}
		else
		{
			strength = 3;
		}
	}
	return strength;
}
int decode::intraEdgeFilterStrengthSelection(int w, int h, int filterType, int delta){

	int useUpsample;
	int  d =  Abs( delta );
	int  blkWh =  w + h;
	if ( d <= 0 || d >= 40 ) {
		useUpsample = 0;
	} else if ( filterType == 0 ) {
		useUpsample = (blkWh <= 16);
	} else {
		useUpsample = (blkWh <= 8);
	}
	return useUpsample;
}
int decode::intraEdgeUpsample(int numPx,int dir){
	Array8 *buf;
	if(dir == 0 )
		buf = AboveRow;
	else 
		buf = LeftCol;

    int dup[numPx + 3];


    dup[0] = buf[-1];
    for (int i = -1; i < numPx; i++) {
        dup[i + 2] = buf[i];
    }
    dup[numPx + 2] = buf[numPx - 1];


    buf[-2] = dup[0];
    for (int i = 0; i < numPx; i++) {
        int s = -dup[i] + (9 * dup[i + 1]) + (9 * dup[i + 2]) - dup[i + 3];
        s = Clip1(Round2(s, 4));
        buf[2 * i - 1] = s;
        buf[2 * i] = dup[i + 2];
    }

}
int decode::intraEdgeFilter(int sz, int strength, int left){
    if (strength == 0) {
        return; 
    }

    int edge[sz]; 
    for (int i = 0; i < sz; i++) {
        edge[i] = (left ? LeftCol[i - 1] : AboveRow[i - 1]);
    }

    for (int i = 1; i < sz; i++) {
        int s = 0;


        for (int j = 0; j < INTRA_EDGE_TAPS; j++) {
            int k = Clip3(0, sz - 1, i - 2 + j);
            s += Intra_Edge_Kernel[strength - 1][j] * edge[k];
        }

        if (left) {
            LeftCol[i - 1] = (s + 8) >> 4;
        } else {
            AboveRow[i - 1] = (s + 8) >> 4;
        }
    }

}
/*帧内预测结束*/
/*帧间预测*/

int decode::predict_inter(int plane, int x, int y,int w ,int h ,int candRow,int candCol){
	roundingVariablesDerivation();
	int LocalValid;
	if(plane == 0 && motion_mode == LOCALWARP){
		warpEstimation(CandList,LocalWarpParams,&LocalValid);
	}
	if(plane == 0 && motion_mode == LOCALWARP && LocalValid == 1){
		int a,b,g,d;//these values will bediscard;
		setupShear(LocalWarpParams,&LocalValid,&a,&b,&g,&d);
	}
	int refList = 0;

genArray:
	int refFrame = RefFrames[ candRow ][ candCol ][ refList ];
	int globalValid;
    if((YMode == GLOBALMV || YMode == GLOBAL_GLOBALMV) && GmType[ refFrame ] > TRANSLATION){
		int a,b,g,d;//these values will bediscard;
		setupShear(gm_params[ refFrame ],&globalValid,&a,&b,&g,&d);
	}

	int useWarp = 0;
    if (w >= 8 && h >= 8) {
		useWarp = 0;
    }else if( force_integer_mv == 0){
		useWarp = 0;
	}else if(motion_mode ==LOCALWARP && LocalValid = 1){
		useWarp = 1;
	}else if(
		(YMode == GLOBALMV || YMode == GLOBAL_GLOBALMV) && GmType[ refFrame ] > TRANSLATION &&
		is_scaled( refFrame ) == 0 && globalValid == 1)
	{
		useWarp = 2;
	}else{
		useWarp = 0;
	}
	int mv[2] = Mvs[ candRow ][ candCol ][ refList ];
	int refIdx ;
	if(use_intrabc == 0){
		refIdx == ref_frame_idx[ refFrame - LAST_FRAME ];
	}else{
		refIdx = -1;
		//These values ensure that the motion vector scaling has no effect
		//spec 是这样说的 ，但是还是没明白为啥
		RefFrameWidth[ -1 ] = FrameWidth;
		RefUpscaledWidth[ -1 ] = UpscaledWidth;
	}
	motionVectorScaling( plane,refIdx, x, y, mv );

//These values are needed to avoid intrabc prediction being cropped to the frame boundaries
	if(use_intrabc == 1){
		RefFrameWidth[ -1 ] = MiCols * MI_SIZE;
		RefFrameHeight[ -1 ] = MiRows * MI_SIZE;
		RefUpscaledWidth[ -1 ] = MiCols * MI_SIZE;
	}

// 这里有问题！！
	if(useWarp == 0){
		for(int i8 = 0 ; i8 < ((h-1) >> 3 ;i8 ++)){
			for(int j8 = 0 ; j8 < ((w-1) >> 3 ;j8 ++)){
				//块扭曲操作，每次一个 8*8大小的子块
				blockWarp(useWarp,plane,refList,x,y,i8,j8,w,h);
			}
		} 
		

	}
	if(useWarp == 0){
		blockInterPrediction(plane, refIdx,startX, startY, stepX, stepY, w, h, candRow, candCol );
	}

	if(isCompound == 1){
		refList = 1;
		goto genArray;
	}

	if(compound_type == COMPOUND_WEDGE && plane == 0){
		wedgeMask(w,h);
	}else if(compound_type == COMPOUND_INTRA){
		intraModeVariantMask(w,h);
	}else if(compound_type == COMPOUND_DIFFWTD && plane == 0){
		differenceWeightMask(preds,w,h);
	}

	if(compound_type == COMPOUND_DISTANCE){
		distanceWeights(candRow,candCol);
	}

	if(isCompound == 0 && IsInterIntra == 0){
		for(int i = 0 ; i < h ; i ++){
			for(int j = 0 ; j < w ; j ++){
				CurrFrame[ plane ][ y + i ][ x + j ] = Clip1(preds[ 0 ][ i ][ j ] );
			}
		}
	}else if(compound_type == COMPOUND_AVERAGE){
		for(int i = 0 ; i < h ; i ++){
			for(int j = 0 ; j < w ; j ++){
				CurrFrame[ plane ][ y + i ][ x + j ] = Clip1( Round2( preds[ 0 ][ i ][ j ] + preds[ 1 ][ i ][ j ], 1 + InterPostRound ) );
			}
		}
	}else if(compound_type == COMPOUND_DISTANCE){
		for(int i = 0 ; i < h ; i ++){
			for(int j = 0 ; j < w ; j ++){
				CurrFrame[ plane ][ y + i ][ x + j ] = Clip1( Round2( FwdWeight * preds[ 0 ][ i ][ j ] + BckWeight * preds[ 1 ][ i ][ j ], 4 + InterPostRound ) )
			}
		}
	}else{
		maskBlend(preds,plane ,x,y,w,h);
	}

	if(motion_mode == OBMC ){
		overlappedMotionCompensation();
	}

}
//7.11.3.2
int decode::roundingVariablesDerivation(){
	int isCompound =  RefFrames[ candRow ][ candCol ][ 1 ] > INTRA_FRAME;

	InterRound0 = 3;
	InterRound1 = isCompound ? 7 : 11;
    if (BitDepth == 12) {
        InterRound0 += 2;
    }

    if (isCompound) {
        InterRound1 = 7;
    } else {
        InterRound1 = 11;
    }

    if (BitDepth == 12 && !isCompound) {
        InterRound1 -= 2;
    }
    InterPostRound = 2 * FILTER_BITS - (InterRound0 + InterRound1);


}
//7.11.3.6
int decode::setupShear(int *LocalWarpParams,int *warpValid,int *alpha,int *beta,int *gamma,int *delta){
   int divShift, divFactor;
    int warpValid;
    int alpha, beta, gamma, delta;


    int alpha0 = Clip3(-32768, 32767, warpParams[2] - (1 << WARPEDMODEL_PREC_BITS));
    int beta0 = Clip3(-32768, 32767, warpParams[3]);

    resolveDivisor(warpParams[2], &divShift, &divFactor);

    int v = warpParams[4] << WARPEDMODEL_PREC_BITS;
    int gamma0 = Clip3(-32768, 32767, Round2Signed(v * divFactor, divShift));

    int w = warpParams[3] * warpParams[4];
    int delta0 = Clip3(-32768, 32767, warpParams[5] - Round2Signed(w * divFactor, divShift) - (1 << WARPEDMODEL_PREC_BITS));

    *alpha = (Round2Signed(alpha0, WARP_PARAM_REDUCE_BITS)) << WARP_PARAM_REDUCE_BITS;
    *beta = (Round2Signed(beta0, WARP_PARAM_REDUCE_BITS)) << WARP_PARAM_REDUCE_BITS;
    *gamma = (Round2Signed(gamma0, WARP_PARAM_REDUCE_BITS)) << WARP_PARAM_REDUCE_BITS;
    *delta = (Round2Signed(delta0, WARP_PARAM_REDUCE_BITS)) << WARP_PARAM_REDUCE_BITS;

    if ((4 * abs(alpha) + 7 * abs(beta)) >= (1 << WARPEDMODEL_PREC_BITS) ||
        (4 * abs(gamma) + 4 * abs(delta)) >= (1 << WARPEDMODEL_PREC_BITS)) {
        warpValid = 0;
    } else {
        warpValid = 1;
    }
}
//7.11.3.7
int decode::resolveDivisor(int d, int *divShift, int *divFactor){

    int n = (int)floor(log(fabs(d)) / log(2));
    int e = abs(d) - (1 << n);
    int f;
    if (n > DIV_LUT_BITS) {
        f = (int)round((double)e / (1 << (n - DIV_LUT_BITS)));
    } else {
        f = e << (DIV_LUT_BITS - n);
    }

    *divShift = n + DIV_LUT_PREC_BITS;

    if (d < 0) {
        *divFactor = -Div_Lut[f];
    } else {
        *divFactor = Div_Lut[f];
    }
}
//7.11.3.8
int decode::warpEstimation(int **CandList, int LocalWarpParams[6], int *LocalValid){
	int A[2][2] = {{0}};
    int Bx[2] = {0};
    int By[2] = {0};

    int w4 = Num_4x4_Blocks_Wide[MiSize];
    int h4 = Num_4x4_Blocks_High[MiSize];
    int midY = MiRow * 4 + h4 * 2 - 1;
    int midX = MiCol * 4 + w4 * 2 - 1;
    int suy = midY * 8;
    int sux = midX * 8;
    int duy = suy + Mv[0][0];
    int dux = sux + Mv[0][1];

    for (int i = 0; i < NumSamples; i++) {
        int sy = CandList[i][0] - suy;
        int sx = CandList[i][1] - sux;
        int dy = CandList[i][2] - duy;
        int dx = CandList[i][3] - dux;

        if (abs(sx - dx) < LS_MV_MAX && abs(sy - dy) < LS_MV_MAX) {
            A[0][0] += ls_product(sx, sx) + 8;
            A[0][1] += ls_product(sx, sy) + 4;
            A[1][1] += ls_product(sy, sy) + 8;
            Bx[0] += ls_product(sx, dx) + 8;
            Bx[1] += ls_product(sy, dx) + 4;
            By[0] += ls_product(sx, dy) + 4;
            By[1] += ls_product(sy, dy) + 8;
        }
    }

    int det = A[0][0] * A[1][1] - A[0][1] * A[0][1];
    
    if (det == 0) {
        *LocalValid = 0;
        return;
    }

    int divShift = 0;
    int divFactor = 0; 

	resolveDivisor(det,&divShift,&divFactor);

    // 计算 LocalWarpParams
    divShift -= WARPEDMODEL_PREC_BITS;
    if (divShift < 0) {
        divFactor = divFactor << (-divShift);
        divShift = 0;
    }

    LocalWarpParams[2] = diag(A[1][1] * Bx[0] - A[0][1] * Bx[1],divFactor,divShift);
    LocalWarpParams[3] = nondiag(-A[0][1] * Bx[0] + A[0][0] * Bx[1],divFactor,divShift);
    LocalWarpParams[4] = nondiag(A[1][1] * By[0] - A[0][1] * By[1],divFactor,divShift);
    LocalWarpParams[5] = diag(-A[0][1] * By[0] + A[0][0] * By[1],divFactor,divShift);

    int mvx = Mv[0][1];
    int mvy = Mv[0][0];
    int vx = mvx * (1 << (WARPEDMODEL_PREC_BITS - 3)) - (midX * (LocalWarpParams[2] - (1 << WARPEDMODEL_PREC_BITS)) + midY * LocalWarpParams[3]);
    int vy = mvy * (1 << (WARPEDMODEL_PREC_BITS - 3)) - (midX * LocalWarpParams[4] + midY * (LocalWarpParams[5] - (1 << WARPEDMODEL_PREC_BITS)));

    LocalWarpParams[0] = Clip3(-WARPEDMODEL_TRANS_CLAMP, WARPEDMODEL_TRANS_CLAMP - 1, vx);
    LocalWarpParams[1] = Clip3(-WARPEDMODEL_TRANS_CLAMP, WARPEDMODEL_TRANS_CLAMP - 1, vy);

}
////7.11.3.3
int decode::motionVectorScaling(int plane, int refIdx, int x, int y, int mv[2]){
	int xScale, yScale;
    int subX, subY;
    int halfSample = 1 << (SUBPEL_BITS - 1);
    int origX, origY;
    int baseX, baseY;
    int off;
    int startX, startY;
    int stepX, stepY;

    if (plane == 0) {
        subX = 0;
        subY = 0;
    } else {
        subX = subsampling_x;
        subY = subsampling_y;
    }

    origX = (x << SUBPEL_BITS) + ((2 * mv[1]) >> subX) + halfSample;
    origY = (y << SUBPEL_BITS) + ((2 * mv[0]) >> subY) + halfSample;

    xScale = ((RefUpscaledWidth[refIdx] << REF_SCALE_SHIFT) + (FrameWidth / 2)) / FrameWidth;
    yScale = ((RefFrameHeight[refIdx] << REF_SCALE_SHIFT) + (FrameHeight / 2)) / FrameHeight;

    baseX = (origX * xScale - (halfSample << REF_SCALE_SHIFT));
    baseY = (origY * yScale - (halfSample << REF_SCALE_SHIFT));

    off = (1 << (SCALE_SUBPEL_BITS - SUBPEL_BITS)) / 2;

    startX = (Round2Signed(baseX, REF_SCALE_SHIFT + SUBPEL_BITS - SCALE_SUBPEL_BITS) + off);
    startY = (Round2Signed(baseY, REF_SCALE_SHIFT + SUBPEL_BITS - SCALE_SUBPEL_BITS) + off);

    stepX = Round2Signed(xScale, REF_SCALE_SHIFT - SCALE_SUBPEL_BITS);
    stepY = Round2Signed(yScale, REF_SCALE_SHIFT - SCALE_SUBPEL_BITS);
}
////7.11.3.5
int decode::blockWarp(int useWarp,int plane,int refList,int x,int y,
						int i8,int j8,int w,int h,int **pred)
{
	
    int refIdx = ref_frame_idx[RefFrame[refList] - LAST_FRAME];

    // Calculate ref
    int ref = FrameStore[refIdx];

    // Calculate subX and subY
    int subX, subY;
    if (plane == 0) {
        subX = 0;
        subY = 0;
    } else {
        subX = subsampling_x;
        subY = subsampling_y;
    }

    // Calculate lastX and lastY
    int lastX = ((RefUpscaledWidth[refIdx] + subX) >> subX) - 1;
    int lastY = ((RefFrameHeight[refIdx] + subY) >> subY) - 1;

    // Calculate srcX and srcY
    int srcX = (x + j8 * 8 + 4) << subX;
    int srcY = (y + i8 * 8 + 4) << subY;

    // Calculate warpParams
    float warpParams[6];
    if (useWarp == 1) {
        for (int i = 0; i < 6; i++) {
            warpParams[i] = LocalWarpParams[i];
        }
    } else if (useWarp == 2) {
        for (int i = 0; i < 6; i++) {
            warpParams[i] = gm_params[RefFrame[refList]][i];
        }
    }

    // Calculate dstX and dstY
    float dstX = warpParams[2] * srcX + warpParams[3] * srcY + warpParams[0];
    float dstY = warpParams[4] * srcX + warpParams[5] * srcY + warpParams[1];

    // Invoke shear process
    int warpValid, alpha, beta, gamma, delta;
    setupShear(warpParams, &warpValid, &alpha, &beta, &gamma, &delta);

    // Sub-sample interpolation - Horizontal filter
    int intermediate[15][8];
    for (int i1 = -7; i1 < 8; i1++) {
        for (int i2 = -4; i2 < 4; i2++) {
            float sx = sx4 + alpha * i2 + beta * i1;
            int offs = Round2(sx, WARPEDDIFF_PREC_BITS) + WARPEDPIXEL_PREC_SHIFTS;
            int s = 0;
            for (int i3 = 0; i3 < 8; i3++) {
                s += Warped_Filters[offs][i3] *
                     ref[plane][Clip3(0, lastY, iy4 + i1)][Clip3(0, lastX, ix4 + i2 - 3 + i3)];
            }
            intermediate[i1 + 7][i2 + 4] = Round2(s, InterRound0);
        }
    }

    // Sub-sample interpolation - Vertical filter
    for (int i1 = -4; i1 < Min(4, h - i8 * 8 - 4); i1++) {
        for (int i2 = -4; i2 < Min(4, w - j8 * 8 - 4); i2++) {
            float sy = sy4 + gamma * i2 + delta * i1;
            int offs = Round2(sy, WARPEDDIFF_PREC_BITS) + WARPEDPIXEL_PREC_SHIFTS;
            int s = 0;
            for (int i3 = 0; i3 < 8; i3++) {
                s += Warped_Filters[offs][i3] * intermediate[i1 + i3 + 4][i2 + 4];
            }
            pred[i8 * 8 + i1 + 4][j8 * 8 + i2 + 4] = Round2(s, InterRound1);
        }
    }
}
//7.11.3.4
//The sub-sample interpolation is effected via two one-dimensional convolutions. First a horizontal filter is used to build up a
//temporary array, and then this array is vertically filtered to obtain the final prediction. The fractional parts of the motion
//vectors determine the filtering process. If the fractional part is zero, then the filtering is equivalent to a straight sample
//copy
int decode::block_inter_prediction(int plane, int refIdx, int x, int y, int xStep, int yStep, int w, int h, int candRow, int candCol, int ref[plane][lastY + 1][lastX + 1]) {
    // Calculate ref
    int ref[plane][lastY + 1][lastX + 1];
    if (refIdx == -1) {
        ref = CurrFrame;
    } else if (refIdx >= 0) {
        ref = FrameStore[refIdx];
    }

    // Calculate subX and subY
    int subX, subY;
    if (plane == 0) {
        subX = 0;
        subY = 0;
    } else {
        subX = subsampling_x;
        subY = subsampling_y;
    }

    // Calculate lastX and lastY
    int lastX = ((RefUpscaledWidth[refIdx] + subX) >> subX) - 1;
    int lastY = ((RefFrameHeight[refIdx] + subY) >> subY) - 1;

    // Calculate intermediateHeight
    int intermediateHeight = (((h - 1) * yStep + (1 << SCALE_SUBPEL_BITS) - 1) >> SCALE_SUBPEL_BITS) + 8;

    // Sub-sample interpolation - Horizontal filter
    int interpFilter = InterpFilters[candRow][candCol][1];
    if (w <= 4) {
        if (interpFilter == EIGHTTAP || interpFilter == EIGHTTAP_SHARP) {
            interpFilter = 4;
        } else if (interpFilter == EIGHTTAP_SMOOTH) {
            interpFilter = 5;
        }
    }
    
    for (int r = 0; r < intermediateHeight; r++) {
        for (int c = 0; c < w; c++) {
            int s = 0;
            int p = x + xStep * c;
            for (int t = 0; t < 8; t++) {
                s += Subpel_Filters[interpFilter][(p >> 6) & SUBPEL_MASK][t] *
                     ref[plane][Clip3(0, lastY, (y >> 10) + r - 3)][Clip3(0, lastX, (p >> 10) + t - 3)];
            }
            intermediate[r][c] = Round2(s, InterRound0);
        }
    }

    // Sub-sample interpolation - Vertical filter
    interpFilter = InterpFilters[candRow][candCol][0];
    if (h <= 4) {
        if (interpFilter == EIGHTTAP || interpFilter == EIGHTTAP_SHARP) {
            interpFilter = 4;
        } else if (interpFilter == EIGHTTAP_SMOOTH) {
            interpFilter = 5;
        }
    }
    
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            int s = 0;
            int p = (y & 1023) + yStep * r;
            for (int t = 0; t < 8; t++) {
                s += Subpel_Filters[interpFilter][(p >> 6) & SUBPEL_MASK][t] * intermediate[(p >> 10) + t][c];
            }
            pred[r][c] = Round2(s, InterRound1);
        }
    }
}
//7.11.3.11
int decode::wedgeMask(int w,int h){
	initializeWedgeMaskTable();
	for ( i = 0; i < h; i++ ) {
		for ( j = 0; j < w; j++ ) {
			Mask[ i ][ j ] = WedgeMasks[ MiSize ][ wedge_sign ][ wedge_index ][ i ][ j ];
		}
	}
}
int decode::initializeWedgeMaskTable() {
    int w, h,shift, sum, avg, flipSign, msk;
    
    w = MASK_MASTER_SIZE;
	h = MASK_MASTER_SIZE;

	for (int j = 0; j < w; j++)
	{
		shift = MASK_MASTER_SIZE / 4;
		for (int i = 0; i < h; i += 2)
		{
			MasterMask[WEDGE_OBLIQUE63][i][j] = Wedge_Master_Oblique_Even[Clip3(0,
																				MASK_MASTER_SIZE - 1, j - shift)];
			shift -= 1;
			MasterMask[WEDGE_OBLIQUE63][i + 1][j] = Wedge_Master_Oblique_Odd[Clip3(0,
																				   MASK_MASTER_SIZE - 1, j - shift)];
			MasterMask[WEDGE_VERTICAL][i][j] = Wedge_Master_Vertical[j];
			MasterMask[WEDGE_VERTICAL][i + 1][j] = Wedge_Master_Vertical[j];
		}
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			msk = MasterMask[WEDGE_OBLIQUE63][i][j];
			MasterMask[WEDGE_OBLIQUE27][j][i] = msk;
			MasterMask[WEDGE_OBLIQUE117][i][w - 1 - j] = 64 - msk;
			MasterMask[WEDGE_OBLIQUE153][w - 1 - j][i] = 64 - msk;
			MasterMask[WEDGE_HORIZONTAL][j][i] = MasterMask[WEDGE_VERTICAL][i][j];
		}
	}
	// Populate WedgeMasks for different block sizes and wedge types
    for (int bsize = BLOCK_8X8; bsize < BLOCK_SIZES; bsize++) {
        if (Wedge_Bits[bsize] > 0) {
            w = Block_Width[bsize];
            h = Block_Height[bsize];
            for (int wedge = 0; wedge < WEDGE_TYPES; wedge++) {
                int dir = get_wedge_direction(bsize, wedge);
                int xoff = MASK_MASTER_SIZE / 2 - ((get_wedge_xoff(bsize, wedge) * w) >> 3);
                int yoff = MASK_MASTER_SIZE / 2 - ((get_wedge_yoff(bsize, wedge) * h) >> 3);
                sum = 0;
                for (int i = 0; i < w; i++)
                    sum += MasterMask[dir][yoff][xoff + i];
                for (int i = 1; i < h; i++)
                    sum += MasterMask[dir][yoff + i][xoff];
                avg = (sum + (w + h - 1) / 2) / (w + h - 1);
                flipSign = (avg < 32);
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j++) {
                        WedgeMasks[bsize][flipSign][wedge][i][j] = MasterMask[dir][yoff + i][xoff + j];
                        WedgeMasks[bsize][!flipSign][wedge][i][j] = 64 - MasterMask[dir][yoff + i][xoff + j];
                    }
                }
            }
        }
    }
}
//7.11.3.13
//This process prepares an array Mask containing the blending weights for the luma samples.
int decode::intraModeVariantMask(int w, int h)
{
	int sizeScale = MAX_SB_SIZE / Max(h, w);
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			if (interintra_mode == II_V_PRED)
			{
				Mask[i][j] = Ii_Weights_1d[i * sizeScale];
			}
			else if (interintra_mode == II_H_PRED)
			{
				Mask[i][j] = Ii_Weights_1d[j * sizeScale];
			}
			else if (interintra_mode == II_SMOOTH_PRED)
			{
				Mask[i][j] = Ii_Weights_1d[Min(i, j) * sizeScale];
			}
			else
			{
				Mask[i][j] = 32;
			}
		}
	}
}
//7.11.3.12
//This process prepares an array Mask containing the blending weights for the luma samples
int decode::differenceWeightMask(int ***preds, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int diff = Abs(preds[0][i][j] - preds[1][i][j]);
			diff = Round2(diff, (BitDepth - 8) + InterPostRound);
			m = Clip3(0, 64, 38 + diff / 16);
			if (mask_type)
				Mask[i][j] = 64 - m;
			else
				Mask[i][j] = m;
		}
	}
}
//7.11.3.15
//This process computes weights to be used for blending predictions together based on the expected output times of the
//reference frames.
int decode::distanceWeights(int candRow,int candCol)
{
 	int refList;  
    int h;  
    int dist[2];  
    int d0, d1;  
    int order;  
    int i;  
  
    for (refList = 0; refList < 2; refList++) {  
        h = OrderHints[RefFrames[candRow][candCol][refList]];  
        dist[refList] = fmin(fmax(0, Abs(get_relative_dist(h, OrderHint))), MAX_FRAME_DISTANCE);  
    }  
  
    d0 = dist[1];  
    d1 = dist[0];  
    order = d0 <= d1;  
  
    if (d0 == 0 || d1 == 0) {  
        FwdWeight = Quant_Dist_Lookup[3][order];  
        BckWeight = Quant_Dist_Lookup[3][1 - order];  
    } else {  
        for (i = 0; i < 3; i++) {  
            int c0 = Quant_Dist_Weight[i][order];  
            int c1 = Quant_Dist_Weight[i][1 - order];  
  
            if (order) {  
                if (d0 * c0 > d1 * c1)  
                    break;  
            } else {  
                if (d0 * c0 < d1 * c1)  
                    break;  
            }  
        }  
  
        FwdWeight = Quant_Dist_Lookup[i][order];  
        BckWeight = Quant_Dist_Lookup[i][1 - order];  
    }  
}
//The process combines two predictions according to the mask. It makes use of an array Mask containing the blending
//weights to apply (the weights are defined for the current plane samples if compound_type is equal to
//COMPOUND_INTRA, or the luma plane otherwise).
int decode::maskBlend(int ***preds,int plane ,int x,int y,int w,int h){
  	int x, y;  
    int subX, subY;  
    int m;  
    int pred0, pred1;  
  
    if (plane == 0) {  
        subX = subY = 0;  
    } else {  
        subX = subsampling_x;  
        subY = subsampling_y;  
    }  
  
    for (y = 0; y < h; y++) {  
        for (x = 0; x < w; x++) {  
            if ((!subX && !subY) || (interintra && !wedge_interintra)) {  
                m = Mask[y][x];  
            } else if (subX && !subY) {  
                m = Round2(Mask[y][2*x] + Mask[y][2*x+1], 1);  
            } else if (!subX && subY) {  
                m = Round2(Mask[2*y][x] + Mask[2*y+1][x], 1);  
            } else {  
                m = Round2(Mask[2*y][2*x] + Mask[2*y][2*x+1] + Mask[2*y+1][2*x] + Mask[2*y+1][2*x+1], 2);  
            }  
  
            if (interintra) {  
                pred0 = Clip1(Round2(preds[0][y][x], InterPostRound));  
                pred1 = CurrFrame[plane][y+dstY][x+dstX];  
                CurrFrame[plane][y+dstY][x+dstX] = Round2(m * pred1 + (64 - m) * pred0, 6);  
            } else {  
                pred0 = preds[0][y][x];  
                pred1 = preds[1][y][x];  
                CurrFrame[plane][y+dstY][x+dstX] = Clip1(Round2(m * pred0 + (64 - m) * pred1, 6 + InterPostRound));  
            }  
        }  
    }  

}
//This process blends the inter predicted samples for the current block with inter predicted samples based on motion
//vectors from the above and left blocks.
//The maximum number of overlapped predictions is limited based on the size of the block.
//For small blocks, only the left neighbor will be used to form the prediction
//7.11.3.9

int decode::overlappedMotionCompensation(int plane, int w ,int h) {
    int AvailU = 1; // 上方是否可用
    int AvailL = 1; // 左侧是否可用
    int pass;
    int w4, x4, y4, nCount, nLimit;
    int candRow, candCol, candSz, step4, predW, predH, mask;

    if (AvailU) {
        if (get_plane_residual_size(MiSize, plane) >= BLOCK_8X8) {
            pass = 0;
            w4 = Num_4x4_Blocks_Wide[MiSize];
            x4 = MiCol;
            y4 = MiRow;
            nCount = 0;
            nLimit = Min(4, Mi_Width_Log2[MiSize]);

            while (nCount < nLimit && x4 < Min(MiCols, MiCol + w4)) {
                candRow = MiRow - 1;
                candCol = x4 | 1;
                candSz = MiSizes[candRow][candCol];
                step4 = Clip3(2, 16, Num_4x4_Blocks_Wide[candSz]);

                if (RefFrames[candRow][candCol][0] > INTRA_FRAME) {
                    nCount += 1;
                    predW = Min(w, (step4 * MI_SIZE) >> subX);
                    predH = Min(h >> 1, 32 >> subY);
                    mask = get_obmc_mask(predH);
                    predict_overlap(MiSize, plane, x4, y4, predW, predH, subX, subY);
                }

                x4 += step4;
            }
        }
    }

    if (AvailL) {
        pass = 1;
        h4 = Num_4x4_Blocks_High[MiSize];
        x4 = MiCol;
        y4 = MiRow;
        nCount = 0;
        nLimit = Min(4, Mi_Height_Log2[MiSize]);

        while (nCount < nLimit && y4 < Min(MiRows, MiRow + h4)) {
            candCol = MiCol - 1;
            candRow = y4 | 1;
            candSz = MiSizes[candRow][candCol];
            step4 = Clip3(2, 16, Num_4x4_Blocks_High[candSz]);

            if (RefFrames[candRow][candCol][0] > INTRA_FRAME) {
                nCount += 1;
                predW = Min(w >> 1, 32 >> subX);
                predH = Min(h, (step4 * MI_SIZE) >> subY);
                mask = get_obmc_mask(predW);
                predict_overlap(MiSize, plane, x4, y4, predW, predH, subX, subY);
            }

            y4 += step4;
        }34
    }
}

int decode::predict_overlap(){
	mv = Mvs[ candRow ][ candCol ][ 0 ];
	int refIdx = ref_frame_idx[ RefFrames[ candRow ][ candCol ][ 0 ] - LAST_FRAME ];
	predX = (x4 * 4) >> subX;
	predY = (y4 * 4) >> subY;
	motionVectorScaling(plane,refIdx,predX, predY, mv);
	block_inter_prediction(plane, refIdx, startX, startY, stepX, stepY,predW, predH, candRow, candCol);
	for(int i = 0; i < predH;i++){
		for(int j = 0; j < predW;j++){
			obmcPred[ i ][ j ] = Clip1( obmcPred[ i ][ j ] );
		}
	}
	OverlapBlending(plane, predX, predY, predW, predH, pass, obmcPred,mask);

}
//7.11.3.10

int decode::OverlapBlending(int plane ,int predX,int predY,int predW,int predH ,int pass,int **obmcPred,int *mask){
	int m;
	for(int i = 0; i < predH;i++){
		for(int j = 0; j < predW;j++){
			if(pass == 0){
				//blend from above
				m =  mask[ i ];
			}else{
				//blend from left
				m = mask[ j ];
			}
			CurrFrame[ plane ][ predY + i ][ predX + j ] = Round2( m * CurrFrame[ plane ][ predY + i ][ predX + j ]
					+ (64 - m) * obmcPred[ i ][ j ], 6);
		}
	}
} 

//7.11.4
int decode::palettePrediction(int plane, int startX, int startY, int x, int y, int txSz) {
    int w = Tx_Width[txSz]; // 获取变换块的宽度
    int h = Tx_Height[txSz]; // 获取变换块的高度
    int* palette; // 调色板数组
    int* map; // 颜色映射数组

    if (plane == 0) {
        palette = palette_colors_y;
        map = ColorMapY;
    } else {
        palette = (plane == 1) ? palette_colors_u : palette_colors_v;
        map = ColorMapUV;
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            CurrFrame[plane][startY + i][startX + j] = palette[map[y * 4 + i][x * 4 + j]];
        }
    }
}
//7.11.5
int decode::predictChromaFromLuma(int plane, int startX, int startY, int txSz) {
    int w = Tx_Width[txSz]; // 获取变换块的宽度
    int h = Tx_Height[txSz]; // 获取变换块的高度
    int subX = subsampling_x;
    int subY = subsampling_y;
    int alpha = (plane == 1) ? CflAlphaU : CflAlphaV;
    int L[MAX_FRAME_HEIGHT][MAX_FRAME_WIDTH]; // 保存亮度样本
    int lumaAvg = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int lumaY = (startY + i) << subY;
            lumaY = (lumaY < MaxLumaH - (1 << subY)) ? lumaY : MaxLumaH - (1 << subY);
            int t = 0;
            for (int dy = 0; dy <= subY; dy += 1) {
                for (int dx = 0; dx <= subX; dx += 1) {
                    t += CurrFrame[0][lumaY + dy][startX + j * (1 << subX) + dx];
                }
            }
            int v = t << (3 - subX - subY);
            L[i][j] = v;
            lumaAvg += v;
        }
    }

    lumaAvg = (lumaAvg + (1 << (Tx_Width_Log2[txSz] + Tx_Height_Log2[txSz] - 1))) >> (Tx_Width_Log2[txSz] + Tx_Height_Log2[txSz]);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int dc = CurrFrame[plane][startY + i][startX + j];
            int scaledLuma = (alpha * (L[i][j] - lumaAvg)) >> 6;
            CurrFrame[plane][startY + i][startX + j] = (dc + scaledLuma < 0) ? 0 : ((dc + scaledLuma > 255) ? 255 : dc + scaledLuma);
        }
    }
}

//7.12
int decode::get_dc_quant(int plane) {
    int qindex = get_qindex(0, segment_id,  FeatureData);
    
    if (plane == 0) {
        return dc_q(qindex + DeltaQYDc);
    } else if (plane == 1) {
        return dc_q(qindex + DeltaQUDc);
    } else {
        return dc_q(qindex + DeltaQVDc);
    }
}

// Function to calculate the quantizer value for the ac coefficient for a given plane.
int decode::get_ac_quant(int plane) {
    int qindex = get_qindex(0, segment_id, FeatureData);
    
    if (plane == 0) {
        return ac_q(qindex);
    } else if (plane == 1) {
        return ac_q(qindex + DeltaQUAc);
    } else {
        return ac_q(qindex + DeltaQVAc);
    }
}
int decode::reconstruct(int plane, int x, int y, int txSz) {
    int dqDenom;
	if (txSz == TX_32X32 || txSz == TX_16X32 || txSz == TX_32X16 || txSz == TX_16X64 || txSz == TX_64X16) {
        dqDenom = 2;
    } else if (txSz == TX_64X64 || txSz == TX_32X64 || txSz == TX_64X32) {
        dqDenom =  4;
    } else {
        dqDenom =  1;
    }
    int log2W = Tx_Width_Log2[txSz];
    int log2H = Tx_Height_Log2[txSz];
    int w = 1 << log2W;
    int h = 1 << log2H;
    int tw = Min(32, w);
    int th = Min(32, h);
    int flipUD = (PlaneTxType == FLIPADST_DCT || PlaneTxType == FLIPADST_ADST || PlaneTxType == V_FLIPADST || PlaneTxType == FLIPADST_FLIPADST) ? 1 : 0;
    int flipLR = (PlaneTxType == DCT_FLIPADST || PlaneTxType == ADST_FLIPADST || PlaneTxType == H_FLIPADST || PlaneTxType == FLIPADST_FLIPADST) ? 1 : 0;
    
    for (int i = 0; i < th; i++) {
        for (int j = 0; j < tw; j++) {
            int q = (i == 0 && j == 0) ? 
					get_dc_quant(plane, segment_id, DeltaQYDc, DeltaQUDc, DeltaQVDc, quant_idx[plane][segment_id], 0, 0, 0, FeatureData) : 
					get_ac_quant(plane, segment_id, DeltaQUAc, DeltaQVAc, quant_idx[plane][segment_id], 0, 0, 0, FeatureData);
            
            int q2 = using_qmatrix ? Round2(q * Quantizer_Matrix[SegQMLevel[plane][segment_id]][plane > 0][Qm_Offset[txSz] + i * tw + j], 5) : q;
            
            int dq = Quant[i * tw + j] * q2;
            int sign = (dq < 0) ? -1 : 1;
            int dq2 = sign * (Abs(dq) & 0xFFFFFF) / dqDenom;
            
			Dequant[ i ][ j ] = Clip3( - ( 1 << ( 7 + BitDepth ) ), ( 1 << ( 7 + BitDepth ) ) - 1, dq2 );

        }
    }
    
    // Invoke the 2D inverse transform block process here (not shown in this code).
	twoDInverseTransformBlock();

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int xx = flipLR ? (w - j - 1) : j;
            int yy = flipUD ? (h - i - 1) : i;
            
            CurrFrame[plane][y + yy][x + xx] = Clip1(CurrFrame[plane][y + yy][x + xx] + Residual[i][j]);
        }
    }
    // 无损模式下 需要完全无损 ，因此 Residual 内的每个像素 用 1 + BitDepth位来表示，即比位深度还多一位
	//确保不会溢出 ，保证数据 无损
    if (Lossless == 1) {
        // Ensure values in the Residual array are representable by a signed integer with 1 + BitDepth bits (not shown in this code).
    }
}
//7.13.2.2 翻转数组
int decode::inverseDCTArrayPermutation(int n,int T)
{
    int copyT[1 << n];
    // 复制数组 T 到 copyT
	memcpy(copyT,T,1 << n);
    // 根据位翻转函数 brev(n, i) 重新排列数组 T
    for (int i = 0; i < (1 << n); i++) {
        T[i] = copyT[brev(n, i)];
    }
}
//7.13.2.3 一维反 DCT 变换
int decode::inverseDCT(int T[], int n, int r) {
    // 步骤1：执行逆 DCT 排列
    inverseDCTArrayPermutation(T, n);

    if (n == 6) {

        for (int i = 0; i < 16; i++) {
            B(32 + i, 63 - i, 63 - 4 * brev(4, i), 0, r ,T);
        }

        for (int i = 0; i < 16; i++) {
            H(32 + i * 2, 33 + i * 2, i & 1, r ,T);
        }


        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                B(62 - i * 4 - j, 33 + i * 4 + j, 60 - 16 * brev(2, i) + 64 * j, 1, r ,T);
            }
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 2; j++) {
                B(32 + i * 4 + j, 35 + i * 4 - j, i & 1, r ,T);
            }
        }
    } else if (n >= 5) {

        for (int i = 0; i < 8; i++) {
            B(16 + i, 31 - i, 6 + (brev(3, 7 - i) << 3), 0, r ,T);
        }


        for (int i = 0; i < 4; i++) {
            B(8 + i, 15 - i, 12 + (brev(2, 3 - i) << 4), 0, r ,T);
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                B(30 - 4 * i - j, 17 + 4 * i + j, 24 + (j << 6) + ((1 - i) << 5), 1, r ,T);
            }
        }
    } else if (n >= 4) {

        for (int i = 0; i < 4; i++) {
            B(8 + i, 9 + i, i & 1, r ,T);
        }

        for (int i = 0; i < 4; i++) {
            H(8 + 2 * i, 9 + 2 * i, i & 1, r ,T);
        }
    }

    for (int i = 0; i < 2; i++) {
        B(2 * i, 2 * i + 1, 32 + 16 * i, 1 - i, r ,T);
    }

    for (int i = 0; i < 2; i++) {
        H(4 + 2 * i, 5 + 2 * i, i, r ,T);
    }

    for (int i = 0; i < 2; i++) {
        B(6, 5, 32, 1, r ,T);
    }

    for (int i = 0; i < 2; i++) {
        B(13 - i, 10 + i, 32, 1, r ,T);
    }
}
//7.13.2.4
void decode::inverseADSTInputArrayPermutation(int* T, int n) {
    int n0 = 1 << n;
    int copyT[n0]; 

	memcpy(copyT,T,n0);
    // 执行位逆序排列
    for (int i = 0; i < n0; i++) {
		 //区分奇偶
        int idx = (i & 1) ? (i - 1) : (n0 - i - 1);
        T[i] = copyT[idx];
    }

}
//7.13.2.5
void decode::inverseADSTOutputArrayPermutation(int* T, int n) {
    int n0 = 1 << n;
    int copyT[n0];
	memcpy(copyT,T,n0);
    // 执行输出数组排列
    for (int i = 0; i < n0; i++) {
        int a = ((i >> 3) & 1);
        int b = ((i >> 2) & 1) ^ ((i >> 3) & 1);
        int c = ((i >> 1) & 1) ^ ((i >> 2) & 1);
        int d = (i & 1) ^ ((i >> 1) & 1);

        int idx = ((d << 3) | (c << 2) | (b << 1) | a) >> (4 - n);

        T[i] = (i & 1) ? (-copyT[idx]) : copyT[idx];
    }
}
//7.13.2.6
void inverseADST4(int* T, int r) {
    const int SINPI_1_9 = 1321;
    const int SINPI_2_9 = 2482;
    const int SINPI_3_9 = 3344;
    const int SINPI_4_9 = 3803;

    int s[7];
    int x[4];

    s[0] = SINPI_1_9 * T[0];
    s[1] = SINPI_2_9 * T[0];
    s[2] = SINPI_3_9 * T[1];
    s[3] = SINPI_4_9 * T[2];
    s[4] = SINPI_1_9 * T[2];
    s[5] = SINPI_2_9 * T[3];
    s[6] = SINPI_4_9 * T[3];

    int a7 = T[0] - T[2];
    int b7 = a7 + T[3];

    s[0] = s[0] + s[3];
    s[1] = s[1] - s[4];
    s[3] = s[2];
    s[2] = SINPI_3_9 * b7;
    s[0] = s[0] + s[5];
    s[1] = s[1] - s[6];

    x[0] = s[0] + s[3];
    x[1] = s[1] + s[3];
    x[2] = s[2];
    x[3] = s[0] + s[1] - s[3];

    T[0] = Round2(x[0], 12);
    T[1] = Round2(x[1], 12);
    T[2] = Round2(x[2], 12);
    T[3] = Round2(x[3], 12);
}
//7.13.2.7
void decode::inverseADST8(int* T, int r) {

    int n = 3;
	inverseADSTInputArrayPermutation(T,3);

    for (int i = 0; i < 4; i++) {
        int a = 2 * i;
        int b = 2 * i + 1;
        int angle = 60 - 16 * i;
        B(a, b, angle, 1, r ,T);
    }


    for (int i = 0; i < 4; i++) {
        int a = i;
        int b = 4 + i;
        H(a, b, 0, r,T);
    }


    for (int i = 0; i < 2; i++) {
        int a = 4 + 3 * i;
        int b = 5 + i;
        int angle = 48 - 32 * i;
        B(a, b, angle, 1, r,T);
    }


    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            int a = 4 * j + i;
            int b = 2 + 4 * j + i;
            H(a, b, 0, r,T);
        }
    }

    for (int i = 0; i < 2; i++) {
        int a = 2 + 4 * i;
        int b = 3 + 4 * i;
        int angle = 32;
        B(a, b, angle, 1, r,T);
    }

	inverseADSTOutputArrayPermutation(T,3);
}
//7.13.2.8
void inverseADST16(int* T, int r) {
    // Step 1: Invoke the ADST input array permutation process with n = 4
    int n = 4;
    int copyT[16];
	inverseADSTInputArrayPermutation(T,4);

    for (int i = 0; i < 8; i++) {
        int a = 2 * i;
        int b = 2 * i + 1;
        int angle = 62 - 8 * i;
        B(a, b, angle, 1, r ,T);
    }

    for (int i = 0; i < 8; i++) {
        int a = i;
        int b = 8 + i;
        H(a, b, 0, r,T);
    }


    for (int i = 0; i < 2; i++) {
        int a = 8 + 2 * i;
        int b = 9 + 2 * i;
        int angle1 = 56 - 32 * i;
        B(a, b, angle1, 1, r,T);

        int c = 13 + 2 * i;
        int d = 12 + 2 * i;
        int angle2 = 8 + 32 * i;
        B(c, d, angle2, 1, r,T);
    }

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 4; i++) {
            int a = 8 * j + i;
            int b = 4 + 8 * j + i;
            H(a, b, 0, r,T);
        }
    }


    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            int a = 4 + 8 * j + 3 * i;
            int b = 5 + 8 * j + i;
            int angle = 48 - 32 * i;
            B(a, b, angle, 1, r,T);
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            int a = 4 * j + i;
            int b = 2 + 4 * j + i;
            H(a, b, 0, r,T);
        }
    }


    for (int i = 0; i < 4; i++) {
        int a = 2 + 4 * i;
        int b = 3 + 4 * i;
        int angle = 32;
        B(a, b, angle, 1, r,T);
    }
	inverseADSTOutputArrayPermutation(T,4);
}


//7.13.2.9. 
void decode::inverseADST(int T[],int n,int r){
	if(n == 2 ){
		inverseADST4(T,r);
	}else if(n == 3){
		inverseADST8(T,r);
	}else if(n ==4){
		inverseADST16(T,r);
	}
}
//7.13.2.10
void decode::inverseWalshHadamardTransform(int* T, int shift) {
    int a = T[0] >> shift;
    int c = T[1] >> shift;
    int d = T[2] >> shift;
    int b = T[3] >> shift;

    a += c;
    d -= b;
    int e = (a - d) >> 1;
    b = e - b;
    c = e - c;
    a -= b;

    T[0] = a;
    T[1] = b;
    T[2] = c;
    T[3] = d;
}
//7.13.2.11
void decode::inverseIdentityTransform4(int* T){
	for(int i = 0 ; i < 4 ; i ++){
		T[ i ] = Round2( T[ i ] * 5793, 12 );
	}
}

//7.13.2.12
void decode::inverseIdentityTransform8(int* T){
	for(int i = 0 ; i < 8 ; i ++){
		T[ i ] = T[ i ] * 2;
	}
}

//7.13.2.13
void decode::inverseIdentityTransform16(int* T){
	for(int i = 0 ; i < 16 ; i ++){
		T[ i ] = Round2( T[ i ] * 11586, 12 );
	}
}

//7.13.2.14
void decode::inverseIdentityTransform32(int* T){
	for(int i = 0 ; i < 32 ; i ++){
		T[ i ] = T[ i ] * 4;
	}
}

//7.13.2.15
void decode::inverseIdentityTransform(int *T,int n){
	if( n == 2){
		inverseIdentityTransform4(T);
	}else if(n == 3){
		inverseIdentityTransform8(T);
	}else if(n == 4){
		inverseIdentityTransform16(T);
	}else if(n == 5){
		inverseIdentityTransform32(T);
	}
}
void decode::twoDinverseTransform(int txSz,int T[];) {
    int log2W = Tx_Width_Log2[txSz];
    int log2H = Tx_Height_Log2[txSz];
    int w = 1 << log2W;
    int h = 1 << log2H;
    int rowShift = Lossless ? 0 : Transform_Row_Shift[txSz];
    int colShift = Lossless ? 0 : 4;
    int rowClampRange = BitDepth + 8;
    int colClampRange = Max(BitDepth + 6, 16);


    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i < 32 && j < 32) {
                T[j] = Dequant[i][j];
            } else {
                T[j] = 0;
            }
        }

        if (Abs(log2W - log2H) == 1) {
            for (int j = 0; j < w; j++) {
                T[j] = Round2(T[j] * 2896, 12);
            }
        }

        if (Lossless) {
            inverseWalshHadamardTransform(T, 2);
        } else if (PlaneTxType == DCT_DCT || PlaneTxType == ADST_DCT || PlaneTxType == FLIPADST_DCT || PlaneTxType == H_DCT) {
            inverseDCT(T, log2W, rowClampRange);
        } else if (PlaneTxType == DCT_ADST || PlaneTxType == ADST_ADST || PlaneTxType == DCT_FLIPADST ||
                   PlaneTxType == FLIPADST_FLIPADST || PlaneTxType == ADST_FLIPADST || PlaneTxType == FLIPADST_ADST ||
                   PlaneTxType == H_ADST || PlaneTxType == H_FLIPADST) {
            inverseADST(T, log2W, rowClampRange);
        } else {
            inverseIdentityTransform(T, log2W);
        }

        for (int j = 0; j < w; j++) {
            Residual[i][j] = Round2(T[j], rowShift);
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Residual[i][j] = Min(Max(-((1 << (colClampRange - 1))), Residual[i][j]), ((1 << (colClampRange - 1)) - 1));
        }
    }

    for (int j = 0; j < w; j++) {
        int T[h];
        for (int i = 0; i < h; i++) {
            T[i] = Residual[i][j];
        }

        if (Lossless) {
            inverseWalshHadamardTransform(T, 0);
        } else if (PlaneTxType == DCT_DCT || PlaneTxType == DCT_ADST || PlaneTxType == DCT_FLIPADST || PlaneTxType == V_DCT) {
            inverseDCT(T, log2H, colClampRange);
        } else if (PlaneTxType == ADST_DCT || PlaneTxType == ADST_ADST || PlaneTxType == FLIPADST_DCT ||
                   PlaneTxType == FLIPADST_FLIPADST || PlaneTxType == ADST_FLIPADST || PlaneTxType == FLIPADST_ADST ||
                   PlaneTxType == V_ADST || PlaneTxType == V_FLIPADST) {
            inverseADST(T, log2H, colClampRange);
        } else {
            inverseIdentityTransform(T, log2H);
        }

        for (int i = 0; i < h; i++) {
            Residual[i][j] = Round2(T[i], colShift);
        }
    }
}
//7.14
void decode::loopFilter(int **CurrFrame){
	for ( plane = 0; plane < NumPlanes; plane++ ) {
		if ( plane == 0 || loop_filter_level[ 1 + plane ] ) {
			for ( pass = 0; pass < 2; pass++ ) {
				rowStep = ( plane == 0 ) ? 1 : ( 1 << subsampling_y );
				colStep = ( plane == 0 ) ? 1 : ( 1 << subsampling_x );
				for ( row = 0; row < MiRows; row += rowStep )
				for ( col = 0; col < MiCols; col += colStep )
				loop_filter_edge( plane, pass, row, col );
			}
		}
	}
}
void decode::edgeLoopFilter(int plane, int pass, int row, int col) {
    int subX, subY, dx, dy, x, y, onScreen, xP, yP, prevRow, prevCol, MiSize, txSz, planeSize, skip, isIntra, prevTxSz;
    int isBlockEdge, isTxEdge, applyFilter, filterSize;
    int lvl, limit, blimit, thresh;

    // Derive subX and subY
    if (plane == 0) {
        subX = subY = 0;
    } else {
        subX = subsampling_x;
        subY = subsampling_y;
    }

    // Derive dx and dy
    if (pass == 0) {
        dx = 1;
        dy = 0;
    } else {
        dy = 1;
        dx = 0;
    }

    // Derive x and y
    x = col * MI_SIZE;
    y = row * MI_SIZE;

    // Adjust row and col
    row = (row | subY);
    col = (col | subX);

    // Derive onScreen
    onScreen = 1;
    if (x >= FrameWidth || y >= FrameHeight || (pass == 0 && x == 0) || (pass == 1 && y == 0)) {
        onScreen = 0;
    }

    if (onScreen == 0) {
        return; // No filtering is applied if off-screen
    }

    // Derive xP and yP
    xP = x >> subX;
    yP = y >> subY;

    // Derive prevRow and prevCol
    prevRow = row - (dy << subY);
    prevCol = col - (dx << subX);

    // Set MiSize, txSz, planeSize, skip, isIntra, and prevTxSz
    MiSize = MiSizes[row][col];
    txSz = LoopfilterTxSizes[plane][row >> subY][col >> subX];
    planeSize = get_plane_residual_size(MiSize, plane);
    skip = Skips[row][col];
    isIntra = RefFrames[row][col][0] <= INTRA_FRAME;
    prevTxSz = LoopfilterTxSizes[plane][prevRow >> subY][prevCol >> subX];

    // Derive isBlockEdge
    isBlockEdge = 0;
    if ((pass == 0 && xP % Block_Width[planeSize] == 0) || (pass == 1 && yP % Block_Height[planeSize] == 0)) {
        isBlockEdge = 1;
    }

    // Derive isTxEdge
    isTxEdge = 0;
    if ((pass == 0 && xP % Tx_Width[txSz] == 0) || (pass == 1 && yP % Tx_Height[txSz] == 0)) {
        isTxEdge = 1;
    }

    // Derive applyFilter
    applyFilter = 0;
    if (isTxEdge == 0) {
        applyFilter = 0;
    } else if (isBlockEdge == 1 || skip == 0 || isIntra == 1) {
        applyFilter = 1;
    } else {
        applyFilter = 0;
    }
//注意这里没写完
    // Invoke filter size process (section 7.14.3) to calculate filterSize

    // Invoke adaptive filter strength process (section 7.14.4) to calculate lvl, limit, blimit, and thresh

    // If lvl is equal to 0, invoke adaptive filter strength process for prevRow, prevCol

    // Apply sample filtering process (section 7.14.6) for each sample if applyFilter is 1 and lvl is greater than 0
}
//7.14.3
//The purpose of this process is to reduce the width of the chroma filters and to ensure that different boundaries can be
//filtered in parallel.
int decode::filterSize(int txSz, int prevTxSz, int pass, int plane) {
    int baseSize;

    // Derive baseSize based on pass
    if (pass == 0) {
        baseSize = min(Tx_Width[prevTxSz], Tx_Width[txSz]);
    } else {
        baseSize = min(Tx_Height[prevTxSz], Tx_Height[txSz]);
    }

    // Derive filterSize based on plane
    int filterSize;
    if (plane == 0) {
        filterSize = min(16, baseSize);
    } else {
        filterSize = min(8, baseSize);
    }

    return filterSize;
}
//7.14.4
void adaptiveFilterStrength(int row, int col, int plane, int pass, int& lvl, int& limit, int& blimit, int& thresh) {
    // Derive segment, ref, mode, modeType, and deltaLF
    int segment = SegmentIds[row][col];
    int ref = RefFrames[row][col][0];
    int mode = YModes[row][col];
    int modeType;

    if (mode >= NEARESTMV && mode != GLOBALMV && mode != GLOBAL_GLOBALMV) {
        modeType = 1;
    } else {
        modeType = 0;
    }

    int deltaLF;
    if (delta_lf_multi == 0) {
        deltaLF = DeltaLFs[row][col][0];
    } else {
        deltaLF = DeltaLFs[row][col][plane == 0 ? pass : (plane + 1)];
    }

    // Invoke the adaptive filter strength selection process
    lvl = adaptiveFilterStrengthSelection(segment, ref, modeType, deltaLF, plane, pass);

    // Derive shift
    int shift;
    if (loop_filter_sharpness > 4) {
        shift = 2;
    } else if (loop_filter_sharpness > 0) {
        shift = 1;
    } else {
        shift = 0;
    }

    // Derive limit
    if (loop_filter_sharpness > 0) {
        limit = Clip3(1, 9 - loop_filter_sharpness, lvl >> shift);
    } else {
        limit = max(1, lvl >> shift);
    }

    // Derive blimit and thresh
    blimit = 2 * (lvl + 2) + limit;
    thresh = lvl >> 4;
}
//7.14.5
int AdaptiveFilterStrengthSelection(int segment, int ref, int modeType, int deltaLF, int plane, int pass) {
    // 初始化变量
    int i = (plane == 0) ? pass : (plane + 1);
    int baseFilterLevel = Clip3(0, MAX_LOOP_FILTER, deltaLF + loop_filter_level[i]);
    int lvlSeg = baseFilterLevel;
    int feature = SEG_LVL_ALT_LF_Y_V + i;

    // 检查segment特征是否激活
    if (seg_feature_active_idx(segment, feature) == 1) {
        lvlSeg += FeatureData[segment][feature];
        lvlSeg = Clip3(0, MAX_LOOP_FILTER, lvlSeg);
    }

    // 如果loop_filter_delta_enabled为1，应用delta值
    if (loop_filter_delta_enabled == 1) {
        int nShift = lvlSeg >> 5;
        
        if (ref == INTRA_FRAME) {
            lvlSeg += (loop_filter_ref_deltas[INTRA_FRAME] << nShift);
        } else {
            lvlSeg += (loop_filter_ref_deltas[ref] << nShift) + (loop_filter_mode_deltas[modeType] << nShift);
        }
        
        lvlSeg = Clip3(0, MAX_LOOP_FILTER, lvlSeg);
    }

    return lvlSeg;
}
//7.14.6
void sampleFiltering(int x,int  y,int  plane, int limit,int  blimit,int  thresh,int  dx,int  dy,int  filterSize){

	// 调用Filter Mask生成过程
	int hevMask, filterMask, flatMask, flatMask2;
	GenerateFilterMasks(x, y, plane, limit, blimit, thresh, dx, dy, filterSize, hevMask, filterMask, flatMask, flatMask2);

	// 根据Filter Mask和Filter Size选择适当的Filter过程
	if (filterMask == 0) {
		// 不需要滤波
	} else if (filterSize == 4 || flatMask == 0) {
		// 使用狭窄滤波过程
		NarrowFilterProcess(x, y, plane, dx, dy, hevMask);
	} else if (filterSize == 8 || flatMask2 == 0) {
		// 使用宽滤波过程，log2Size为3
		WideFilterProcess(x, y, plane, dx, dy, 3);
	} else {
		// 使用宽滤波过程，log2Size为4
		WideFilterProcess(x, y, plane, dx, dy, 4);
	}
}
////7.14.6.2
void filterMask(int x,int y.int plane,int limit,int blimit,int thresh,int dx,int dy,int filterSize)
{
	int q0 = CurrFrame[ plane ][ y ][ x ];
	int q1 = CurrFrame[ plane ][ y + dy ][ x + dx ];
	int q2 = CurrFrame[ plane ][ y + dy * 2 ][ x + dx * 2 ];
	int q3 = CurrFrame[ plane ][ y + dy * 3 ][ x + dx * 3 ];
	int q4 = CurrFrame[ plane ][ y + dy * 4 ][ x + dx * 4 ];
	int q5 = CurrFrame[ plane ][ y + dy * 5 ][ x + dx * 5 ];
	int q6 = CurrFrame[ plane ][ y + dy * 6 ][ x + dx * 6 ];
	int p0 = CurrFrame[ plane ][ y - dy ][ x - dx ];
	int p1 = CurrFrame[ plane ][ y - dy * 2 ][ x - dx * 2 ];
	int p2 = CurrFrame[ plane ][ y - dy * 3 ][ x - dx * 3 ];
	int p3 = CurrFrame[ plane ][ y - dy * 4 ][ x - dx * 4 ];
	int p4 = CurrFrame[ plane ][ y - dy * 5 ][ x - dx * 5 ];
	int p5 = CurrFrame[ plane ][ y - dy * 6 ][ x - dx * 6 ];
	int p6 = CurrFrame[ plane ][ y - dy * 7 ][ x - dx * 7 ];
	// hev : means |high| edge| variance|
	hevMask = 0 ;
	int threshBd = thresh << (BitDepth - 8)；
	hevMask |= (Abs( p1 - p0 ) > threshBd)；
	hevMask |= (Abs( q1 - q0 ) > threshBd)；

	int filterLen;//滤波器抽头(taps)数
	if(filterSize == 4){
		filterLen = 4;
	}else if(plane == 0){
		filterLen = 6;
	}else if(filterSize == 8){
		filterLen = 8;
	}else{
		filterLen = 16;
	}
//filterMask的值指示靠近边缘的相邻样本(在指定边界两侧的四个样本内)
//的变化是否小于由limit和blimit给出的限制。它用于确定是否应该执行某种过滤，计算方法如下:
	int limitBd = limit << (BitDepth - 8);
	int blimitBd = blimit << (BitDepth - 8);
	int mask = 0;
	mask |= (Abs( p1 - p0 ) > limitBd);
	mask |= (Abs( q1 - q0 ) > limitBd);
	mask |= (Abs( p0 - q0 ) * 2 + Abs( p1 - q1 ) / 2 > blimitBd);
	if ( filterLen >= 6 ) {
		mask |= (Abs( p2 - p1 ) > limitBd);
		mask |= (Abs( q2 - q1 ) > limitBd);
	}
	if ( filterLen >= 8 ) {
		mask |= (Abs( p3 - p2 ) > limitBd);
		mask |= (Abs( q3 - q2 ) > limitBd);
	}

	filterMask = (mask == 0);

	//只有当filterSize >= 8时才需要flatMask的值。
	//它测量来自指定边界两侧的样本是否在一个平坦区域内。
	//即这些样本与边界上的样本是否最多存在(1 << (BitDepth - 8))的差异。计算方法如下:
	int thresholdBd = 1 << (BitDepth - 8);
	if ( filterSize >= 8 ) {
		 mask = 0
		mask |= (Abs( p1 - p0 ) > thresholdBd);
		mask |= (Abs( q1 - q0 ) > thresholdBd);
		mask |= (Abs( p2 - p0 ) > thresholdBd);
		mask |= (Abs( q2 - q0 ) > thresholdBd);
		if ( filterLen >= 8 ) {
			mask |= (Abs( p3 - p0 ) > thresholdBd);
			mask |= (Abs( q3 - q0 ) > thresholdBd);
		}
		flatMask = (mask == 0);
	}
	//假设前面四个点(0,1,2,3)都在同一个平坦区域， flatMask2 代表后面3个点也在同一个平坦区域
	// 如果 flatMask & flatMask2 == 0 ,则所有点都在一个平坦区域
	thresholdBd = 1 << (BitDepth - 8);
	if ( filterSize >= 16 ) {
		mask = 0;
		mask |= (Abs( p6 - p0 ) > thresholdBd);
		mask |= (Abs( q6 - q0 ) > thresholdBd);
		mask |= (Abs( p5 - p0 ) > thresholdBd);
		mask |= (Abs( q5 - q0 ) > thresholdBd);
		mask |= (Abs( p4 - p0 ) > thresholdBd);
		mask |= (Abs( q4 - q0 ) > thresholdBd);
		flatMask2 = (mask == 0);
	}

}
//This process modifies up to two samples on each side of the 
//specified boundary depending on the value of hevMask 
void narrowFilter(int hevMask,int x,int y,int plane,int dx ,int dy){
	int q0 = CurrFrame[ plane ][ y ][ x ];
	int q1 = CurrFrame[ plane ][ y + dy ][ x + dx ];
	int p0 = CurrFrame[ plane ][ y - dy ][ x - dx ];
	int p1 = CurrFrame[ plane ][ y - dy * 2 ][ x - dx * 2 ];
	int ps1 = p1 - (0x80 << (BitDepth - 8));
	int ps0 = p0 - (0x80 << (BitDepth - 8));
	int qs0 = q0 - (0x80 << (BitDepth - 8));
	int qs1 = q1 - (0x80 << (BitDepth - 8));
	int filter = hevMask ? filter4_clamp( ps1 - qs1 ) : 0;
	filter = filter4_clamp( filter + 3 * (qs0 - ps0) );
	int filter1 = filter4_clamp( filter + 4 ) >> 3;
	int filter2 = filter4_clamp( filter + 3 ) >> 3;
	int oq0 = filter4_clamp( qs0 - filter1 ) + (0x80 << (BitDepth - 8));
	int op0 = filter4_clamp( ps0 + filter2 ) + (0x80 << (BitDepth - 8));
	CurrFrame[ plane ][ y ][ x ] = oq0;
	CurrFrame[ plane ][ y - dy ][ x - dx ] = op0;
	if ( !hevMask ) {
		filter = Round2( filter1, 1 );
		int oq1 = filter4_clamp( qs1 - filter ) + (0x80 << (BitDepth - 8));
		int op1 = filter4_clamp( ps1 + filter ) + (0x80 << (BitDepth - 8));
		CurrFrame[ plane ][ y + dy ][ x + dx ] = oq1;
		CurrFrame[ plane ][ y - dy * 2 ][ x - dx * 2 ] = op1;
	}

}
void wideFilter(int x,int y,int plane,int dx ,int dy,int log2Size){
	//specifying the number of filter taps on each side of the central sample
	int n;
	
	if(log2Size == 4){
		n = 6;
	}else if(plane == 0){
		n = 4;
	}else {
		n = 2;
	}
	//(specifying the number of filter taps equal to 2 on each side of the central sample needed to give a unity DC gain
	int n2;
	if(log2Size == 3 && plane == 0){
		n2 = 0;
	}else{
		n2 = 1;
	}

}