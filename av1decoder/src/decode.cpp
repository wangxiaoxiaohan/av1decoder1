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
residual()
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
transform_tree(startX, startY, w, h)
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
transform_block(plane, baseX, baseY, txSz, x, y)
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
coeffs(plane, startX, startY, txSz)
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
int decode::add_sample(){



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
  | | | | | |
  | |x x x x
  | |x x x x
  |	|x x x x
  | |x x x x
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