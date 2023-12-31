#include "decode.h"
#include "header_common.h"
#include "cdf.h"
#include <string.h>
decode::decode(){
	sb = &Symbol::Instance();
}
decode::~decode(){


}
//这个函数内部 不应该用到  TileData PartitionData BlockData 需要想办法去掉
int decode::decode_frame_wrapup( AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if(frameHdr->show_existing_frame == 0){
		if( frameHdr->loop_filter_params.loop_filter_level[ 0 ] != 0 || frameHdr->loop_filter_params.loop_filter_level[ 1 ] != 0){
			printf("loop filter\n");
			loopFilter(av1Ctx); 
		}

		// FILE *fp = fopen("test.yuv", "wb");
		// int h = av1Ctx->frameHdr.si.FrameHeight;
		// int w = av1Ctx->frameHdr.si.FrameWidth;
		// uint8_t buf[w];
		// for (int i = 0; i < h; i++) {
		// 	for (int j = 0; j < w; j++) {
		// 		buf[j] = av1Ctx->currentFrame->CurrFrame[0][ i][ j];
		// 	}
		// 	fwrite(buf, sizeof(uint8_t),w, fp);
		// }
		// int subX = av1Ctx->seqHdr.color_config.subsampling_x;
		// int subY = av1Ctx->seqHdr.color_config.subsampling_y;
		// uint8_t buf1[((w + subX) >> subX ) * 2];
		// for (int i = 0; i < (h + subY) >> subY ; i++) {
		// 	for (int j = 0; j < (w + subX) >> subX; j++) {
		// 		buf1[j * 2] = av1Ctx->currentFrame->CurrFrame[1][ i][ j];
		// 		buf1[j * 2 + 1] = av1Ctx->currentFrame->CurrFrame[2][ i][ j];
		// 	}
		// 	fwrite(buf1, sizeof(uint8_t),((w + subX) >> subX ) * 2, fp);
		// }
		// fclose(fp);

		cdef(av1Ctx); 

		// FILE *fp = fopen("test.yuv", "wb");
		// int h = av1Ctx->frameHdr.si.FrameHeight;
		// int w = av1Ctx->frameHdr.si.FrameWidth;
		// uint8_t buf[w];
		// for (int i = 0; i < h; i++) {
		// for (int j = 0; j < w; j++) {
		// 	buf[j] = av1Ctx->currentFrame->CdefFrame[0][ i][ j];
		// }
		// fwrite(buf, sizeof(uint8_t),w, fp);
		// }
		// int subX = av1Ctx->seqHdr.color_config.subsampling_x;
		// int subY = av1Ctx->seqHdr.color_config.subsampling_y;
		// uint8_t buf1[((w + subX) >> subX ) * 2];
		// for (int i = 0; i < (h + subY) >> subY ; i++) {
		// 	for (int j = 0; j < (w + subX) >> subX; j++) {
		// 		buf1[j * 2] = av1Ctx->currentFrame->CdefFrame[1][ i][ j];
		// 		buf1[j * 2 + 1] = av1Ctx->currentFrame->CdefFrame[2][ i][ j];
		// 	}
		// 	fwrite(buf1, sizeof(uint8_t),((w + subX) >> subX ) * 2, fp);
		// }
		// fclose(fp);

		upscalingProcess(av1Ctx->currentFrame->CdefFrame,av1Ctx->currentFrame->UpscaledCdefFrame,av1Ctx);
		upscalingProcess(av1Ctx->currentFrame->CurrFrame,av1Ctx->currentFrame->UpscaledCurrFrame,av1Ctx);
		loopRestoration(av1Ctx); 
		motionFieldMotionVectorStorage(av1Ctx);
		if(frameHdr->segmentation_params.segmentation_enabled == 1 && frameHdr->segmentation_params.segmentation_update_map ==0){
			for(int row = 0 ; row < frameHdr->MiRows ; row ++ ){
				for(int col = 0 ; col < frameHdr->MiCols ; col ++ ){
					av1Ctx->SegmentIds[ row ][ col ] = av1Ctx->PrevSegmentIds[ row ][ col ];
				}
			}
		}
	}else{
		if(frameHdr->frame_type == KEY_FRAME){
			referenceFrameLoading(av1Ctx);
		}
		
	}
	referenceFrameUpdate(av1Ctx);
	if(frameHdr->show_frame == 1 || frameHdr->show_existing_frame == 1){
		output(av1Ctx);
	}

}
int decode::init_non_coeff_cdfs(CDFArrays *cdf){
    memcpy(cdf->Intra_Frame_Y_Mode,Default_Intra_Frame_Y_Mode_Cdf,sizeof(Default_Intra_Frame_Y_Mode_Cdf));
    memcpy(cdf->Y_Mode,Default_Y_Mode_Cdf,sizeof(Default_Y_Mode_Cdf));
    memcpy(cdf->Uv_Mode_Cfl_Not_Allowed,Default_Uv_Mode_Cfl_Not_Allowed_Cdf, sizeof(Default_Uv_Mode_Cfl_Not_Allowed_Cdf));
    memcpy(cdf->Uv_Mode_Cfl_Allowed,Default_Uv_Mode_Cfl_Allowed_Cdf ,sizeof(Default_Uv_Mode_Cfl_Allowed_Cdf));

    memcpy(cdf->Angle_Delta,Default_Angle_Delta_Cdf,sizeof(Default_Angle_Delta_Cdf));
    memcpy(cdf->Intrabc,Default_Intrabc_Cdf,sizeof(Default_Intrabc_Cdf));

    memcpy(cdf->Partition_W8,Default_Partition_W8_Cdf,sizeof(Default_Partition_W8_Cdf));
    memcpy(cdf->Partition_W16,Default_Partition_W16_Cdf ,sizeof(Default_Partition_W16_Cdf));
    memcpy(cdf->Partition_W32,Default_Partition_W32_Cdf ,sizeof(Default_Partition_W32_Cdf));
    memcpy(cdf->Partition_W64,Default_Partition_W64_Cdf ,sizeof(Default_Partition_W64_Cdf));
    memcpy(cdf->Partition_W128,Default_Partition_W128_Cdf ,sizeof(Default_Partition_W128_Cdf));

    memcpy(cdf->Tx_8x8,Default_Tx_8x8_Cdf,sizeof(Default_Tx_8x8_Cdf));
    memcpy(cdf->Tx_16x16,Default_Tx_16x16_Cdf,sizeof(Default_Tx_16x16_Cdf));
    memcpy(cdf->Tx_32x32,Default_Tx_32x32_Cdf,sizeof(Default_Tx_32x32_Cdf));
    memcpy(cdf->Tx_64x64,Default_Tx_64x64_Cdf,sizeof(Default_Tx_64x64_Cdf));

    memcpy(cdf->Txfm_Split,Default_Txfm_Split_Cdf,sizeof(Default_Txfm_Split_Cdf));
    memcpy(cdf->Filter_Intra_Mode,Default_Filter_Intra_Mode_Cdf,sizeof(Default_Filter_Intra_Mode_Cdf));
    memcpy(cdf->Filter_Intra,Default_Filter_Intra_Cdf,sizeof(Default_Filter_Intra_Cdf));
    memcpy(cdf->Segment_Id,Default_Segment_Id_Cdf,sizeof(Default_Segment_Id_Cdf));
    memcpy(cdf->Segment_Id_Predicted,Default_Segment_Id_Predicted_Cdf,sizeof(Default_Segment_Id_Predicted_Cdf));
    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        for(int j = 0 ; j < 2 ; j++){
            memcpy(cdf->Mv_Class0_Hp[i][j],Default_Mv_Class0_Hp_Cdf,sizeof(Default_Mv_Class0_Hp_Cdf));
            memcpy(cdf->Mv_Hp[i][j],Default_Mv_Hp_Cdf,sizeof(Default_Mv_Hp_Cdf));
            memcpy(cdf->Mv_Sign[i][j],Default_Mv_Sign_Cdf,sizeof(Default_Mv_Sign_Cdf));
            memcpy(cdf->Mv_Bit[i][j],Default_Mv_Bit_Cdf,sizeof(Default_Mv_Bit_Cdf));
            memcpy(cdf->Mv_Class0_Bit[i][j],Default_Mv_Class0_Bit_Cdf,sizeof(Default_Mv_Class0_Bit_Cdf));
        }
    }
    memcpy(cdf->New_Mv,Default_New_Mv_Cdf,sizeof(Default_New_Mv_Cdf));
    memcpy(cdf->Zero_Mv,Default_Zero_Mv_Cdf,sizeof(Default_Zero_Mv_Cdf));
    memcpy(cdf->Ref_Mv,Default_Ref_Mv_Cdf,sizeof(Default_Ref_Mv_Cdf));
    memcpy(cdf->Drl_Mode,Default_Drl_Mode_Cdf,sizeof(Default_Drl_Mode_Cdf));
    memcpy(cdf->Is_Inter,Default_Is_Inter_Cdf,sizeof(Default_Is_Inter_Cdf));

    memcpy(cdf->Comp_Mode,Default_Comp_Mode_Cdf,sizeof(Default_Comp_Mode_Cdf));
    memcpy(cdf->Skip_Mode,Default_Skip_Mode_Cdf,sizeof(Default_Skip_Mode_Cdf));
    memcpy(cdf->Skip,Default_Skip_Cdf,sizeof(Default_Skip_Cdf));
    memcpy(cdf->Comp_Ref,Default_Comp_Ref_Cdf,sizeof(Default_Comp_Ref_Cdf));

    memcpy(cdf->Comp_Bwd_Ref,Default_Comp_Bwd_Ref_Cdf,sizeof(Default_Comp_Bwd_Ref_Cdf));
    memcpy(cdf->Single_Ref,Default_Single_Ref_Cdf,sizeof(Default_Single_Ref_Cdf));
    memcpy(cdf->Compound_Mode,Default_Compound_Mode_Cdf,sizeof(Default_Compound_Mode_Cdf));

    memcpy(cdf->Interp_Filter,Default_Interp_Filter_Cdf,sizeof(Default_Interp_Filter_Cdf));
    memcpy(cdf->Motion_Mode,Default_Motion_Mode_Cdf,sizeof(Default_Motion_Mode_Cdf));

    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        memcpy(cdf->Mv_Joint[i],Default_Mv_Joint_Cdf,sizeof(Default_Mv_Joint_Cdf));
        memcpy(cdf->Mv_Class[i],Default_Mv_Class_Cdf,sizeof(Default_Mv_Class_Cdf));
        memcpy(cdf->Mv_Class0_Fr[i],Default_Mv_Class0_Fr_Cdf,sizeof(Default_Mv_Class0_Fr_Cdf));
        memcpy(cdf->Mv_Fr[i],Default_Mv_Fr_Cdf,sizeof(Default_Mv_Fr_Cdf));
    }
    memcpy(cdf->Palette_Y_Size,Default_Palette_Y_Size_Cdf,sizeof(Default_Palette_Y_Size_Cdf));
    memcpy(cdf->Palette_Uv_Size,Default_Palette_Uv_Size_Cdf,sizeof(Default_Palette_Uv_Size_Cdf));

    memcpy(cdf->Palette_Size_2_Y_Color,Default_Palette_Size_2_Y_Color_Cdf,sizeof(Default_Palette_Size_2_Y_Color_Cdf));
    memcpy(cdf->Palette_Size_3_Y_Color,Default_Palette_Size_3_Y_Color_Cdf,sizeof(Default_Palette_Size_3_Y_Color_Cdf));
    memcpy(cdf->Palette_Size_4_Y_Color,Default_Palette_Size_4_Y_Color_Cdf,sizeof(Default_Palette_Size_4_Y_Color_Cdf));
    memcpy(cdf->Palette_Size_5_Y_Color,Default_Palette_Size_5_Y_Color_Cdf,sizeof(Default_Palette_Size_5_Y_Color_Cdf));
    memcpy(cdf->Palette_Size_6_Y_Color,Default_Palette_Size_6_Y_Color_Cdf,sizeof(Default_Palette_Size_6_Y_Color_Cdf));
    memcpy(cdf->Palette_Size_7_Y_Color,Default_Palette_Size_7_Y_Color_Cdf,sizeof(Default_Palette_Size_7_Y_Color_Cdf));
    memcpy(cdf->Palette_Size_8_Y_Color,Default_Palette_Size_8_Y_Color_Cdf,sizeof(Default_Palette_Size_8_Y_Color_Cdf));
    
    memcpy(cdf->Palette_Size_2_Uv_Color,Default_Palette_Size_2_Uv_Color_Cdf,sizeof(Default_Palette_Size_2_Uv_Color_Cdf));
    memcpy(cdf->Palette_Size_3_Uv_Color,Default_Palette_Size_3_Uv_Color_Cdf,sizeof(Default_Palette_Size_3_Uv_Color_Cdf));
    memcpy(cdf->Palette_Size_4_Uv_Color,Default_Palette_Size_4_Uv_Color_Cdf,sizeof(Default_Palette_Size_4_Uv_Color_Cdf));
    memcpy(cdf->Palette_Size_5_Uv_Color,Default_Palette_Size_5_Uv_Color_Cdf,sizeof(Default_Palette_Size_5_Uv_Color_Cdf));
    memcpy(cdf->Palette_Size_6_Uv_Color,Default_Palette_Size_6_Uv_Color_Cdf,sizeof(Default_Palette_Size_6_Uv_Color_Cdf));
    memcpy(cdf->Palette_Size_7_Uv_Color,Default_Palette_Size_7_Uv_Color_Cdf,sizeof(Default_Palette_Size_7_Uv_Color_Cdf));
    memcpy(cdf->Palette_Size_8_Uv_Color,Default_Palette_Size_8_Uv_Color_Cdf,sizeof(Default_Palette_Size_8_Uv_Color_Cdf));

	memcpy(cdf->Palette_Y_Mode,Default_Palette_Y_Mode_Cdf,sizeof(Default_Palette_Y_Mode_Cdf));
    memcpy(cdf->Palette_Uv_Mode,Default_Palette_Uv_Mode_Cdf,sizeof(Default_Palette_Uv_Mode_Cdf));
	
    memcpy(cdf->Delta_Q,Default_Delta_Q_Cdf,sizeof(Default_Delta_Q_Cdf));
    memcpy(cdf->Delta_Lf,Default_Delta_Lf_Cdf,sizeof(Default_Delta_Lf_Cdf));

    for(int i = 0 ; i < FRAME_LF_COUNT ; i++)
        memcpy(cdf->Delta_Lf_Muti[i],Default_Delta_Lf_Cdf,sizeof(Default_Delta_Lf_Cdf));

    memcpy(cdf->Intra_Tx_Type_Set1,Default_Intra_Tx_Type_Set1_Cdf,sizeof(Default_Intra_Tx_Type_Set1_Cdf));
    memcpy(cdf->Intra_Tx_Type_Set2,Default_Intra_Tx_Type_Set2_Cdf,sizeof(Default_Intra_Tx_Type_Set2_Cdf));
    memcpy(cdf->Inter_Tx_Type_Set1,Default_Inter_Tx_Type_Set1_Cdf,sizeof(Default_Inter_Tx_Type_Set1_Cdf));
    memcpy(cdf->Inter_Tx_Type_Set2,Default_Inter_Tx_Type_Set2_Cdf,sizeof(Default_Inter_Tx_Type_Set2_Cdf));
    memcpy(cdf->Inter_Tx_Type_Set3,Default_Inter_Tx_Type_Set3_Cdf,sizeof(Default_Inter_Tx_Type_Set3_Cdf));

    memcpy(cdf->Compound_Idx,Default_Compound_Idx_Cdf,sizeof(Default_Compound_Idx_Cdf));
    memcpy(cdf->Comp_Group_Idx,Default_Comp_Group_Idx_Cdf,sizeof(Default_Comp_Group_Idx_Cdf));
    memcpy(cdf->Compound_Type,Default_Compound_Type_Cdf,sizeof(Default_Compound_Type_Cdf));
    memcpy(cdf->Inter_Intra,Default_Inter_Intra_Cdf,sizeof(Default_Inter_Intra_Cdf));
    memcpy(cdf->Inter_Intra_Mode,Default_Inter_Intra_Mode_Cdf,sizeof(Default_Inter_Intra_Mode_Cdf));

    memcpy(cdf->Wedge_Index,Default_Wedge_Index_Cdf,sizeof(Default_Wedge_Index_Cdf));
    memcpy(cdf->Wedge_Inter_Intra,Default_Wedge_Inter_Intra_Cdf,sizeof(Default_Wedge_Inter_Intra_Cdf));
    memcpy(cdf->Use_Obmc,Default_Use_Obmc_Cdf,sizeof(Default_Use_Obmc_Cdf));
    memcpy(cdf->Comp_Ref_Type,Default_Comp_Ref_Type_Cdf,sizeof(Default_Comp_Ref_Type_Cdf));
    memcpy(cdf->Uni_Comp_Ref,Default_Uni_Comp_Ref_Cdf,sizeof(Default_Uni_Comp_Ref_Cdf));

    memcpy(cdf->Cfl_Sign,Default_Cfl_Sign_Cdf,sizeof(Default_Cfl_Sign_Cdf));
    memcpy(cdf->Cfl_Alpha,Default_Cfl_Alpha_Cdf,sizeof(Default_Cfl_Alpha_Cdf));
    memcpy(cdf->Use_Wiener,Default_Use_Wiener_Cdf,sizeof(Default_Use_Wiener_Cdf));
    memcpy(cdf->Use_Sgrproj,Default_Use_Sgrproj_Cdf,sizeof(Default_Use_Sgrproj_Cdf));
    memcpy(cdf->Restoration_Type,Default_Restoration_Type_Cdf,sizeof(Default_Restoration_Type_Cdf));

}
//indicates that this frame can be decoded without dependence on previous coded frames
int decode::setup_past_independence(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
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
int decode::init_coeff_cdfs(AV1DecodeContext *av1Ctx,CDFArrays *cdf){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
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
    memcpy(cdf->Txb_Skip,Default_Txb_Skip_Cdf[idx],sizeof(Default_Txb_Skip_Cdf[idx]));
    memcpy(cdf->Eob_Pt_16,Default_Eob_Pt_16_Cdf[idx],sizeof(Default_Eob_Pt_16_Cdf[idx]));
    memcpy(cdf->Eob_Pt_32,Default_Eob_Pt_32_Cdf[idx],sizeof(Default_Eob_Pt_32_Cdf[idx]));
    memcpy(cdf->Eob_Pt_64,Default_Eob_Pt_64_Cdf[idx],sizeof(Default_Eob_Pt_64_Cdf[idx]));
    memcpy(cdf->Eob_Pt_128,Default_Eob_Pt_128_Cdf[idx],sizeof(Default_Eob_Pt_128_Cdf[idx]));
    memcpy(cdf->Eob_Pt_256,Default_Eob_Pt_256_Cdf[idx],sizeof(Default_Eob_Pt_256_Cdf[idx]));
    memcpy(cdf->Eob_Pt_512,Default_Eob_Pt_512_Cdf[idx],sizeof(Default_Eob_Pt_512_Cdf[idx]));
    memcpy(cdf->Eob_Pt_1024,Default_Eob_Pt_1024_Cdf[idx],sizeof(Default_Eob_Pt_1024_Cdf[idx]));

    memcpy(cdf->Eob_Extra,Default_Eob_Extra_Cdf[idx],sizeof(Default_Eob_Extra_Cdf[idx]));
    memcpy(cdf->Dc_Sign,Default_Dc_Sign_Cdf[idx],sizeof(Default_Dc_Sign_Cdf[idx]));
    memcpy(cdf->Coeff_Base_Eob,Default_Coeff_Base_Eob_Cdf[idx],sizeof(Default_Coeff_Base_Eob_Cdf[idx]));
    memcpy(cdf->Coeff_Base,Default_Coeff_Base_Cdf[idx],sizeof(Default_Coeff_Base_Cdf[idx]));
    memcpy(cdf->Coeff_Br,Default_Coeff_Br_Cdf[idx],sizeof(Default_Coeff_Br_Cdf[idx]));
}
//从参考帧上下文拷贝cdf到当前framecontext
int decode::load_cdfs(AV1DecodeContext *av1Ctx,int ctx){
	memcpy(&av1Ctx->currentFrame->cdfCtx,&av1Ctx->ref_frames[ctx]->cdfCtx,sizeof(CDFArrays));
}
//保存cdf到参考帧上下文
int decode::save_cdfs(AV1DecodeContext *av1Ctx,int ctx){
	memcpy(&av1Ctx->ref_frames[ctx]->cdfCtx,&av1Ctx->currentFrame->cdfCtx,sizeof(CDFArrays));
}

int decode::save_grain_params(AV1DecodeContext *av1Ctx,int i){
	memcpy(&av1Ctx->ref_frames[i]->frameHdr.film_grain_params,
		&av1Ctx->currentFrame->frameHdr.film_grain_params,
		sizeof(av1Ctx->ref_frames[i]->frameHdr.film_grain_params));
}
int decode::load_grain_params(AV1DecodeContext *av1Ctx,int i){
	memcpy(&av1Ctx->currentFrame->frameHdr.film_grain_params,
			&av1Ctx->ref_frames[i]->frameHdr.film_grain_params,
			sizeof(av1Ctx->ref_frames[i]->frameHdr.film_grain_params));
}

//加载主参考帧的一些参数
int decode::load_previous(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int prevFrame = frameHdr->ref_frame_idx[ frameHdr->primary_ref_frame ];
	load_loop_filter_params(av1Ctx,prevFrame);
	//frameHdr->global_motion_params.PrevGmParams = av1Ctx->SavedGmParams[ prevFrame ];
	memcpy(frameHdr->global_motion_params.PrevGmParams,av1Ctx->SavedGmParams[ prevFrame ],sizeof(frameHdr->global_motion_params.PrevGmParams));
	load_segmentation_params(av1Ctx,prevFrame);

}

//the values of loop_filter_ref_deltas[ j ] for j = 0 ..
//TOTAL_REFS_PER_FRAME-1, and the values of loop_filter_mode_deltas[ j ] for j = 0 .. 1 should be 
//loaded from an area of memory indexed by i.

int decode::load_loop_filter_params(AV1DecodeContext *av1Ctx,int prevFrame){

	memcpy(av1Ctx->currentFrame->frameHdr.loop_filter_params.loop_filter_ref_deltas,
		av1Ctx->ref_frames[prevFrame]->frameHdr.loop_filter_params.loop_filter_ref_deltas,
		TOTAL_REFS_PER_FRAME * sizeof(uint8_t));
	memcpy(av1Ctx->currentFrame->frameHdr.loop_filter_params.loop_filter_mode_deltas,
		av1Ctx->ref_frames[prevFrame]->frameHdr.loop_filter_params.loop_filter_mode_deltas,
		2 * sizeof(uint8_t));

	
}

int decode::save_loop_filter_params(AV1DecodeContext *av1Ctx,int i){
	memcpy(av1Ctx->currentFrame->frameHdr.loop_filter_params.loop_filter_ref_deltas,
		av1Ctx->ref_frames[i]->frameHdr.loop_filter_params.loop_filter_ref_deltas,
		TOTAL_REFS_PER_FRAME * sizeof(uint8_t));
	memcpy(av1Ctx->currentFrame->frameHdr.loop_filter_params.loop_filter_mode_deltas,
		av1Ctx->ref_frames[i]->frameHdr.loop_filter_params.loop_filter_mode_deltas,
		2 * sizeof(uint8_t));
}
int decode::load_segmentation_params(AV1DecodeContext *av1Ctx,int prevFrame){
	memcpy(av1Ctx->currentFrame->frameHdr.segmentation_params.FeatureEnabled,
		av1Ctx->ref_frames[prevFrame]->frameHdr.segmentation_params.FeatureEnabled,
		MAX_SEGMENTS * SEG_LVL_MAX * sizeof(uint8_t));
	memcpy(av1Ctx->currentFrame->frameHdr.segmentation_params.FeatureData,
		av1Ctx->ref_frames[prevFrame]->frameHdr.segmentation_params.FeatureData,
		MAX_SEGMENTS * SEG_LVL_MAX * sizeof(int16_t));
}
int decode::save_segmentation_params(AV1DecodeContext *av1Ctx,int i){
	memcpy(av1Ctx->ref_frames[i]->frameHdr.segmentation_params.FeatureEnabled,
		av1Ctx->currentFrame->frameHdr.segmentation_params.FeatureEnabled,
		MAX_SEGMENTS * SEG_LVL_MAX * sizeof(uint8_t));
	memcpy(av1Ctx->ref_frames[i]->frameHdr.segmentation_params.FeatureData,
		av1Ctx->currentFrame->frameHdr.segmentation_params.FeatureData,
		MAX_SEGMENTS * SEG_LVL_MAX * sizeof(int16_t));
}
int decode::load_previous_segment_ids(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int prevFrame = frameHdr->ref_frame_idx[ frameHdr->primary_ref_frame ];
	if(frameHdr->segmentation_params.segmentation_enabled){
		//load参数，这里为什么是save动作？
		//设置 RefMiCols 和 RefMiRows 的目的是为了在解码过程中保持块大小的一致性，以正确地引用之前帧的数据。
		av1Ctx->RefMiCols[ prevFrame ] = frameHdr->MiCols;
		av1Ctx->RefMiRows[ prevFrame ] = frameHdr->MiRows;

		for(int row  = 0; row < frameHdr->MiRows  ; row ++ ){
			for(int col  = 0; col < frameHdr->MiCols  ; col ++ ){
				av1Ctx->PrevSegmentIds[ row ][ col ] = av1Ctx->SavedSegmentIds[ prevFrame ][ row ][ col ];
			}
		}
		//memcpy(av1Ctx->PrevSegmentIds,av1Ctx->SavedSegmentIds[ prevFrame ],sizeof(uint8_t) * frameHdr->MiRows * frameHdr->MiCols);

	}else{

		for(int row  = 0; row < frameHdr->MiRows  ; row ++ ){
			for(int col  = 0; col < frameHdr->MiCols  ; col ++ ){
				av1Ctx->PrevSegmentIds[ row ][ col ] = 0;
			}
		}
		//memset(av1Ctx->PrevSegmentIds, 0,sizeof(uint8_t) * frameHdr->MiRows * frameHdr->MiCols);
	}
}

//7.8
int decode::set_frame_refs(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	for (int i = 0; i < REFS_PER_FRAME; i++ )
		frameHdr->ref_frame_idx[ i ] = -1;
	frameHdr->ref_frame_idx[ LAST_FRAME - LAST_FRAME ] = frameHdr->last_frame_idx;
	frameHdr->ref_frame_idx[ GOLDEN_FRAME - LAST_FRAME ] = frameHdr->gold_frame_idx;

	int usedFrame[REFS_PER_FRAME];
	for (int i = 0; i < NUM_REF_FRAMES; i++ )
		usedFrame[ i ] = 0;
	usedFrame[ frameHdr->last_frame_idx ] = 1;
	usedFrame[ frameHdr->gold_frame_idx ] = 1;
	int  curFrameHint = 1 << (seqHdr->OrderHintBits - 1);
	int shiftedOrderHints[NUM_REF_FRAMES];
	for (int  i = 0; i < NUM_REF_FRAMES; i++ )
		shiftedOrderHints[ i ] = curFrameHint + get_relative_dist( seqHdr->enable_order_hint,seqHdr->OrderHintBits , av1Ctx->RefOrderHint[ i ], frameHdr->OrderHint );

	int lastOrderHint = shiftedOrderHints[frameHdr->last_frame_idx ];
	//It is a requirement of bitstream conformance that lastOrderHint is strictly less than curFrameHint
	if(!(lastOrderHint < curFrameHint)){
		//如果不满足，该做什么？？ spec只是说需要确认。。。
		//直接退出当前流程？？
	}

	int goldOrderHint = shiftedOrderHints[ frameHdr->gold_frame_idx ];
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
		frameHdr->ref_frame_idx[ ALTREF_FRAME - LAST_FRAME ] = ref;
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
		frameHdr->ref_frame_idx[ BWDREF_FRAME - LAST_FRAME ] = ref;
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
		frameHdr->ref_frame_idx[ ALTREF2_FRAME - LAST_FRAME ] = ref;
		usedFrame[ ref ] = 1;
	}

 //remaining references are set to be forward references in anti-chronological order
 //剩余的参考帧被设置为按反时间顺序的前向参考帧
	for (int i = 0; i < REFS_PER_FRAME - 2; i++ ) {
		int refFrame = Ref_Frame_List[ i ];
		if ( frameHdr->ref_frame_idx[ refFrame - LAST_FRAME ] < 0 ) {
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
				frameHdr->ref_frame_idx[ refFrame - LAST_FRAME ] = ref;
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
		if ( frameHdr->ref_frame_idx[ i ] < 0 ) {
			frameHdr->ref_frame_idx[ i ] = ref;
		}
	}

}
//7.9
int decode::motion_field_estimation(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int w8 = frameHdr->MiCols >> 1; // Width of motion field in 8x8 luma sample units
	int h8 = frameHdr->MiRows >> 1; // Height of motion field in 8x8 luma sample units

	for (int ref = LAST_FRAME; ref <= ALTREF_FRAME; ref++) {
		for (int y = 0; y < h8; y++) {
			for (int x = 0; x < w8; x++) {
				for (int j = 0; j < 2; j++) {
					av1Ctx->MotionFieldMvs[ref][y][x][j] = -1 << 15; // Initialize to invalid motion vector
				}
			}
		}
	}

	int lastIdx = frameHdr->ref_frame_idx[0]; // Reference frame index for LAST_FRAME
	int curGoldOrderHint = frameHdr->OrderHints[GOLDEN_FRAME]; // Expected output order for GOLDEN_FRAME of current frame
	int lastAltOrderHint = av1Ctx->SavedOrderHints[lastIdx][ALTREF_FRAME]; // Expected output order for ALTREF_FRAME of LAST_FRAME
	int useLast = (lastAltOrderHint != curGoldOrderHint) ? 1 : 0; // Whether to project motion vectors from LAST_FRAME

	if (useLast == 1) {
		// Invoke projection process for LAST_FRAME with dstSign = -1 (discard output)
		motion_filed_project(av1Ctx,LAST_FRAME, -1);
	}

	int refStamp = MFMV_STACK_SIZE - 2; // Limit on how many reference frames need to be projected
	int useBwd = (get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits,frameHdr->OrderHints[BWDREF_FRAME], frameHdr->OrderHint) > 0) ? 1 : 0; // Whether to use BWDREF_FRAME

	if (useBwd == 1) {
		int projOutput = motion_filed_project(av1Ctx,BWDREF_FRAME, 1); // Invoke projection for BWDREF_FRAME with dstSign = 1
		if (projOutput == 1) {
			refStamp--;
		}
	}

	int useAlt2 = (get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits,frameHdr->OrderHints[ALTREF2_FRAME], frameHdr->OrderHint) > 0) ? 1 : 0; // Whether to use ALTREF2_FRAME

	if (useAlt2 == 1) {
		int projOutput = motion_filed_project(av1Ctx,ALTREF2_FRAME, 1); // Invoke projection for ALTREF2_FRAME with dstSign = 1
		if (projOutput == 1) {
			refStamp--;
		}
	}

	int useAlt = (get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits,frameHdr->OrderHints[ALTREF_FRAME], frameHdr->OrderHint) > 0) ? 1 : 0; // Whether to use ALTREF_FRAME

	if (useAlt == 1 && refStamp >= 0) {
		int projOutput = motion_filed_project(av1Ctx,ALTREF_FRAME, 1); // Invoke projection for ALTREF_FRAME with dstSign = 1
		if (projOutput == 1) {
			refStamp--;
		}
	}

	if (refStamp >= 0) {
		// Invoke projection process for LAST2_FRAME with dstSign = -1 (discard output)
		motion_filed_project(av1Ctx,LAST2_FRAME, -1);
	}

}
//The process projects the motion vectors from a whole reference frame and stores the results in MotionFieldMvs.
//The process outputs a single boolean value representing whether the source frame was valid for this operation. If the
//output is zero, no modification is made to MotionFieldMvs
int decode::motion_filed_project(AV1DecodeContext *av1Ctx,int src,int dstSign){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int srcIdx = frameHdr->ref_frame_idx[src - LAST_FRAME];
	int w8 = frameHdr->MiCols >> 1;
	int h8 = frameHdr->MiRows >> 1;

	if (av1Ctx->RefMiRows[srcIdx] != frameHdr->MiRows || 
		av1Ctx->RefMiCols[srcIdx] != frameHdr->MiCols || 
		av1Ctx->RefFrameType[srcIdx] == INTRA_ONLY_FRAME || 
		av1Ctx->RefFrameType[srcIdx] == KEY_FRAME) {
		// Exit the process with output set to 0
		return 0;
	}
	for (int y8 = 0; y8 < h8; y8++) {
		for (int x8 = 0; x8 < w8; x8++) {
			int row = 2 * y8 + 1; 
			int col = 2 * x8 + 1;
			int srcRef = av1Ctx->SavedRefFrames[srcIdx][row][col];
			
			if (srcRef > INTRA_FRAME) {
				int refToCur = get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits,frameHdr->OrderHints[src], frameHdr->OrderHint);
				int refOffset = get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits,frameHdr->OrderHints[src], av1Ctx->SavedOrderHints[srcIdx][srcRef]);
				int posValid = (Abs(refToCur) <= MAX_FRAME_DISTANCE) &&
							(Abs(refOffset) <= MAX_FRAME_DISTANCE) &&
							(refOffset > 0);
				
				if (posValid) {
					int mv[2];
					//mv = av1Ctx->SavedMvs[srcIdx][row][col];
					mv[0] = av1Ctx->SavedMvs[srcIdx][row][col][0];
					mv[1] = av1Ctx->SavedMvs[srcIdx][row][col][1];

					int projMv[2];
					get_mv_projection(mv, refToCur * dstSign, refOffset,projMv);
					int PosY8,PosX8;
					posValid = get_block_position(av1Ctx,&PosX8,&PosY8,x8, y8, dstSign, projMv);
					
					if (posValid) {
						for (int dst = LAST_FRAME; dst <= ALTREF_FRAME; dst++) {
							int refToDst = get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits,
																		frameHdr->OrderHint, frameHdr->OrderHints[dst]);
							get_mv_projection(mv, refToDst, refOffset,projMv);
							av1Ctx->MotionFieldMvs[dst][PosY8][PosX8][0] = projMv[0];
							av1Ctx->MotionFieldMvs[dst][PosY8][PosX8][1] = projMv[1];
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
int decode::get_mv_projection(int *mv,int numerator,int denominator,int *projMv){

	int clippedDenominator = Min(MAX_FRAME_DISTANCE, denominator);
	int clippedNumerator = Clip3(-MAX_FRAME_DISTANCE, MAX_FRAME_DISTANCE, numerator);


	for (int i = 0; i < 2; i++) {
		int scaled = Round2Signed(mv[i] * clippedNumerator * Div_Mult[clippedDenominator], 14);
		projMv[i] = scaled;
	}
}
//process returns a flag posValid that indicates if the position should be used
int decode::get_block_position(AV1DecodeContext *av1Ctx,int *PosX8,int *PosY8, int x8, int y8, int dstSign, int *projMv ){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int posValid = 1;

	*PosY8 = project(&posValid,&y8, projMv[ 0 ], dstSign, frameHdr->MiRows >> 1, MAX_OFFSET_HEIGHT);
	*PosX8 = project(&posValid,&x8, projMv[ 1 ], dstSign, frameHdr->MiCols >> 1, MAX_OFFSET_WIDTH);

	return posValid;
}

//7.10
/*  find mv stack  and about start...*/
int decode::find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, 
								 BlockData *b_data, AV1DecodeContext *av1Ctx){

	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
									
	av1Ctx->currentFrame->mvpCtx->NumMvFound = 0;
	av1Ctx->currentFrame->mvpCtx->NewMvCount = 0;
	setup_global_mv(0,av1Ctx->currentFrame->mvpCtx->GlobalMvs[0],b_data,av1Ctx);
	setup_global_mv(1,av1Ctx->currentFrame->mvpCtx->GlobalMvs[1],b_data,av1Ctx);
	av1Ctx->currentFrame->mvpCtx->FoundMatch = 0;
	scan_row(-1,isCompound,b_data,av1Ctx);
	int foundAboveMatch,foundLeftMatch;

	foundAboveMatch = av1Ctx->currentFrame->mvpCtx->FoundMatch ;
	av1Ctx->currentFrame->mvpCtx->FoundMatch = 0;
	scan_col(-1,isCompound,b_data,av1Ctx);
	foundLeftMatch = av1Ctx->currentFrame->mvpCtx->FoundMatch ;
	av1Ctx->currentFrame->mvpCtx->FoundMatch = 0;

	int bh4 = Num_4x4_Blocks_High[ b_data->MiSize ];
	int bw4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
	if(Max( bw4, bh4 ) <= 16){
		scan_point(-1,bw4,isCompound,b_data,av1Ctx);
	}

	if(av1Ctx->currentFrame->mvpCtx->FoundMatch == 1){
		foundAboveMatch = 1;
	}
	av1Ctx->currentFrame->mvpCtx->CloseMatches = foundAboveMatch + foundLeftMatch;
	int numNearest = av1Ctx->currentFrame->mvpCtx->NumMvFound;
	int numNew = av1Ctx->currentFrame->mvpCtx->NewMvCount;
	if(numNearest > 0){
		for(int idx = 0 ;idx < numNearest - 1;idx ++ ){
				av1Ctx->currentFrame->mvpCtx->WeightStack[ idx ] += REF_CAT_LEVEL;
		}
	}
	av1Ctx->currentFrame->mvpCtx->ZeroMvContext = 0;
	if(frameHdr->use_ref_frame_mvs == 1){

		temporal_scan(isCompound,b_data,av1Ctx);
	}
	scan_point(-1,-1,isCompound,b_data,av1Ctx);
	if(av1Ctx->currentFrame->mvpCtx->FoundMatch == 1){
		foundAboveMatch = 1;
	}

	av1Ctx->currentFrame->mvpCtx->FoundMatch =0;
	scan_row(-3,isCompound,b_data,av1Ctx);
	if(av1Ctx->currentFrame->mvpCtx->FoundMatch == 1){
		foundAboveMatch = 1;
	}
	av1Ctx->currentFrame->mvpCtx->FoundMatch =0;

	scan_col(-3,isCompound,b_data,av1Ctx);
	if(av1Ctx->currentFrame->mvpCtx->FoundMatch == 1){
		foundLeftMatch = 1;
	}
	av1Ctx->currentFrame->mvpCtx->FoundMatch = 0;


	if(bh4 > 1){
		scan_row(-5,isCompound,b_data,av1Ctx);
	}
	if(av1Ctx->currentFrame->mvpCtx->FoundMatch == 1){
		foundAboveMatch = 1;
	}
	av1Ctx->currentFrame->mvpCtx->FoundMatch = 0;

	if(bw4 > 1){
		scan_col(-5,isCompound,b_data,av1Ctx);
	}
	if(av1Ctx->currentFrame->mvpCtx->FoundMatch == 1){
		foundLeftMatch = 1;
	}

	av1Ctx->currentFrame->mvpCtx->TotalMatches = foundAboveMatch + foundLeftMatch;

	Sorting(0,numNearest,isCompound,av1Ctx);
	Sorting(numNearest,av1Ctx->currentFrame->mvpCtx->NumMvFound,isCompound,av1Ctx);
	if(av1Ctx->currentFrame->mvpCtx->NumMvFound < 2){
		extra_search(isCompound,b_data,av1Ctx);
	}
	context_and_clamping(isCompound,numNew,b_data,av1Ctx);

}
//7.10.2.1
int decode::setup_global_mv(int refList,int *mv,
								 BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	int ref,typ;
	ref = b_data->RefFrame[ refList ];
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
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
		int x = b_data->MiCol * MI_SIZE + Block_Width[ b_data->MiSize ] / 2 - 1;
		int y = b_data->MiRow * MI_SIZE + Block_Height[ b_data->MiSize ] / 2 - 1;
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
	lower_mv_precision(av1Ctx, mv);
}
int decode::lower_mv_precision(AV1DecodeContext *av1Ctx,int *candMv){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if(frameHdr->allow_high_precision_mv == 1)
		return ERROR_CODE;
	for(int idx =0 ; idx < 2 ;idx ++){	
		if ( frameHdr->force_integer_mv ) {
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
//7.10.2.2
int decode::scan_row(int deltaRow,int isCompound,
				BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int deltaCol = 0;
	if(Abs(deltaRow) > 1){
		deltaRow += b_data->MiRow & 1;
		deltaCol = 1 - (b_data->MiCol & 1);
	}
	int i = 0 ;
	int bw4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
	int end4 = Min( Min( bw4,frameHdr->MiCols - b_data->MiCol ), 16 );
	while (i < end4)
	{
		int mvRow = b_data->MiRow + deltaRow;
		int mvCol = b_data->MiCol + deltaCol + i;
		if (!is_inside(mvRow, mvCol,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd))
			break;
		int len = Min(bw4, Num_4x4_Blocks_Wide[av1Ctx->MiSizes[mvRow][mvCol]]);
		if (Abs(deltaRow) > 1)
		len = Max(2, len);
		int useStep16 = bw4 >= 16;
		if (useStep16)
			len = Max(4, len);
		int weight = len * 2;
		add_ref_mv_candidate(mvRow, mvCol, isCompound, weight,b_data,av1Ctx);
		i += len;
	}
}
//7.10.2.3
int decode::scan_col(int deltaCol,int isCompound,
			BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int deltaRow = 0;
	if(Abs(deltaRow) > 1){	
		deltaRow = 1 - (b_data->MiRow & 1);
		deltaCol += b_data->MiCol & 1;
	}
	int i = 0;
	int bh4 = Num_4x4_Blocks_High[ b_data->MiSize ];
	int end4 = Min( Min( bh4,frameHdr->MiRows - b_data->MiRow ), 16 );

	while ( i < end4 ) {
		int mvRow = b_data->MiRow + deltaRow + i;
		int mvCol = b_data->MiCol + deltaCol;
		if ( !is_inside(mvRow,mvCol,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd) )
			break;
		int len = Min(bh4, Num_4x4_Blocks_High[ av1Ctx->MiSizes[ mvRow ][ mvCol ] ]);
		if ( Abs(deltaCol) > 1 )
			len = Max(2, len);
		int useStep16 = bh4 >= 16;
		if ( useStep16 )
			len = Max(4, len);
		int weight = len * 2;
		add_ref_mv_candidate( mvRow, mvCol, isCompound, weight,b_data,av1Ctx);
		i += len;
	}

}
//This process examines the candidate to find matching reference frames.
//7.10.2.7
int decode::add_ref_mv_candidate(int mvRow,int  mvCol,int  isCompound,int weight,
								BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if(av1Ctx->IsInters[ mvRow ][ mvCol ] == 0){
		return ERROR_CODE;
	}
	if(isCompound == 0){
		for(int candList = 0 ;candList < 2; candList ++){
			if(av1Ctx->RefFrames[ mvRow ][ mvCol ][ candList ] == b_data->RefFrame[ 0 ]){
				search_stack(mvRow, mvCol, candList,weight, b_data,av1Ctx);

			}
		}  
	}else{
		if(av1Ctx->RefFrames[ mvRow ][ mvCol ][ 0 ] == b_data->RefFrame[ 0 ] &&
		 av1Ctx->RefFrames[ mvRow ][ mvCol ][ 1 ]  == b_data->RefFrame[ 1 ]){
			compound_search_stack(mvRow, mvCol, weight, b_data,av1Ctx);
		 }
	}
}
//This process searches the stack for an exact match with a candidate motion vector. If present, the weight of the candidate
//motion vector is added to the weight of its counterpart in the stack, otherwise the process adds a motion vector to the
//stack.
//7.10.2.8
int decode::search_stack(int mvRow,int mvCol,int candList,int weight,
						BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int candMode = av1Ctx->YModes[ mvRow ][ mvCol ];
	int candSize = av1Ctx->MiSizes[ mvRow ][ mvCol ];
	int candMv[2];
	int large =  Min( Block_Width[ candSize ],Block_Height[ candSize ] ) >= 8;
	if(( candMode == GLOBALMV && candMode == GLOBAL_GLOBALMV) && 
				( frameHdr->global_motion_params.GmType[ b_data->RefFrame[ 0 ] ] > TRANSLATION )  && ( large == 1 ))
	{
		//candMv = av1Ctx->GlobalMvs[ 0 ];
		memcpy(candMv,av1Ctx->currentFrame->mvpCtx->GlobalMvs[ 0 ],2* sizeof(int));
	}else{	
		//candMv = p_data->Mvs[ mvRow ][ mvCol ][ candList ];
		memcpy(candMv,av1Ctx->Mvs[ mvRow ][ mvCol ][ candList ],2* sizeof(int));
	}
	lower_precision(candMv,av1Ctx);
	if(candMode == NEWMV ||
			candMode == NEW_NEWMV ||
			candMode == NEAR_NEWMV ||
			candMode == NEW_NEARMV ||
			candMode == NEAREST_NEWMV ||
			candMode == NEW_NEARESTMV)
	{
		av1Ctx->currentFrame->mvpCtx->NewMvCount += 1;
	}
	av1Ctx->currentFrame->mvpCtx->FoundMatch = 1;


	for (int idx = 0; idx < av1Ctx->currentFrame->mvpCtx->NumMvFound; idx++) {
		if (candMv[0] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0][0] && candMv[1] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0][1]) {
			av1Ctx->currentFrame->mvpCtx->WeightStack[idx] += weight;
		}else{
			if( av1Ctx->currentFrame->mvpCtx->NumMvFound < MAX_REF_MV_STACK_SIZE){
				//av1Ctx->RefStackMv[ av1Ctx->NumMvFound][0] = candMv;
				memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[ av1Ctx->currentFrame->mvpCtx->NumMvFound][0],candMv,2 * sizeof(int));
				av1Ctx->currentFrame->mvpCtx->WeightStack[ av1Ctx->currentFrame->mvpCtx->NumMvFound] = weight;
				av1Ctx->currentFrame->mvpCtx->NumMvFound++;
			}

		}
	}

}
//This process searches the stack for an exact match with a candidate pair of motion vectors. If present, the weight of the
//candidate pair of motion vectors is added to the weight of its counterpart in the stack, otherwise the process adds the
//motion vectors to the stack.
int decode::compound_search_stack(int  mvRow ,int  mvCol,int weight,
				BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int candMvs[2][2]; 
	//int candMvs[2][2] = Mvs[ mvRow ][ mvCol ];
	memcpy(candMvs,av1Ctx->Mvs[ mvRow ][ mvCol ],2 * 2 * sizeof(int));
	int candMode = av1Ctx->YModes[ mvRow ][ mvCol ];
	int candSize = av1Ctx->MiSizes[ mvRow ][ mvCol ];
	if(candMode == GLOBAL_GLOBALMV){
		for(int refList = 0 ; refList < 2; refList ++){
			if(frameHdr->global_motion_params.GmType[ b_data->RefFrame[ refList ] ] > TRANSLATION)
			  //candMvs[ refList ] = GlobalMvs[ refList ];
			  memcpy(candMvs[ refList ],av1Ctx->currentFrame->mvpCtx->GlobalMvs[ refList ],2 * sizeof(int));
		}

	}
	for(int i = 0 ; i < 2; i ++){
		lower_precision(candMvs[i],av1Ctx);
	}
	av1Ctx->currentFrame->mvpCtx->FoundMatch = 1;
	for(int idx =0 ;idx < av1Ctx->currentFrame->mvpCtx->NumMvFound ;idx ++){
		if(candMvs[ 0 ][0] == av1Ctx->currentFrame->mvpCtx->RefStackMv[ idx ][ 0 ][0] && candMvs[ 0 ][1] == av1Ctx->currentFrame->mvpCtx->RefStackMv[ idx ][ 0 ][1]
			&&  candMvs[ 1 ][0] == av1Ctx->currentFrame->mvpCtx->RefStackMv[ idx ][ 1 ][0] && candMvs[ 1 ][1] == av1Ctx->currentFrame->mvpCtx->RefStackMv[ idx ][ 1 ][1]){
				av1Ctx->currentFrame->mvpCtx->WeightStack[ idx ] += weight;

		}else{
			if(av1Ctx->currentFrame->mvpCtx->NumMvFound < MAX_REF_MV_STACK_SIZE){
				for(int i = 0 ; i < 2 ; i++)
					//av1Ctx->RefStackMv[ av1Ctx->NumMvFound ][ i ] = candMvs[ i ] ;
					memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[ av1Ctx->currentFrame->mvpCtx->NumMvFound ][ i ] ,candMvs[ i ],2 * sizeof(int));
				av1Ctx->currentFrame->mvpCtx->WeightStack[ av1Ctx->currentFrame->mvpCtx->NumMvFound ] = weight;
				av1Ctx->currentFrame->mvpCtx->NumMvFound += 1;

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
		av1Ctx->currentFrame->mvpCtx->NewMvCount += 1;
	}
}
//7.10.2.4
int decode::scan_point(int deltaRow,int deltaCol,int isCompound,
					BlockData *b_data,AV1DecodeContext *av1Ctx){
	int mvRow = b_data->MiRow + deltaRow;
	int mvCol = b_data->MiCol + deltaCol;
	int weight = 4;
	if((is_inside( mvRow, mvCol ,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd) == 1) && 
					av1Ctx->RefFrames[ mvRow ][ mvCol ][ 0 ] != 0xff/*RefFrames[ mvRow ][ mvCol ][ 0 ] has been written*/ )
		add_ref_mv_candidate(mvRow,mvCol,isCompound,weight,b_data,av1Ctx);
}
//7.10.2.5
//This process scans the motion vectors in a previous frame looking for candidates which use the same reference frame.
int decode::temporal_scan(int isCompound,BlockData *b_data,AV1DecodeContext *av1Ctx)
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
			add_tpl_ref_mv(deltaRow, deltaCol, isCompound,b_data,av1Ctx);
		}
	}
	const int8_t tplSamplePos[3][2] = {
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
				add_tpl_ref_mv(deltaRow, deltaCol, isCompound,b_data,av1Ctx);
			}
		}
	}
}

//7.10.2.6
//This process looks up a motion vector from the motion field and adds it into the stack.
int decode::add_tpl_ref_mv(int deltaRow, int deltaCol, int isCompound,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	int mvRow = (b_data->MiRow + deltaRow) | 1;
	int mvCol = (b_data->MiCol + deltaCol) | 1;
	if (is_inside(mvRow, mvCol,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd) == 0)
		return 0;
	int x8 = mvCol >> 1;
	int y8 = mvRow >> 1;

	if (deltaRow == 0 && deltaCol == 0)
	{
		av1Ctx->currentFrame->mvpCtx->ZeroMvContext = 1;
	}
	if (!isCompound)
	{
		int candMv[2];
		//int candMv[2] = av1Ctx->MotionFieldMvs[b_data->RefFrame[0]][y8][x8];
		memcpy(candMv,av1Ctx->MotionFieldMvs[b_data->RefFrame[0]][y8][x8],2 * sizeof(int));
		if (candMv[0] == -1 << 15)
			return ERROR_CODE;
		lower_mv_precision(av1Ctx,candMv);
		if (deltaRow == 0 && deltaCol == 0)
		{
			if (Abs(candMv[0] - av1Ctx->currentFrame->mvpCtx->GlobalMvs[0][0]) >= 16 ||
				Abs(candMv[1] - av1Ctx->currentFrame->mvpCtx->GlobalMvs[0][1]) >= 16)
				av1Ctx->currentFrame->mvpCtx->ZeroMvContext = 1;
			else
				av1Ctx->currentFrame->mvpCtx->ZeroMvContext = 0;
		}
		int idx;
		for (idx = 0; idx < av1Ctx->currentFrame->mvpCtx->NumMvFound; idx++)
		{
			if (candMv[0] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0][0] &&
				candMv[1] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0][1])

				break;
		}
		if (idx < av1Ctx->currentFrame->mvpCtx->NumMvFound)
		{
			av1Ctx->currentFrame->mvpCtx->WeightStack[idx] += 2;
		}
		else if (av1Ctx->currentFrame->mvpCtx->NumMvFound < MAX_REF_MV_STACK_SIZE)
		{
			//av1Ctx->RefStackMv[av1Ctx->NumMvFound][0] = candMv;
			memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][0],candMv,2 * sizeof(int)); 
			av1Ctx->currentFrame->mvpCtx->WeightStack[av1Ctx->currentFrame->mvpCtx->NumMvFound] = 2;
			av1Ctx->currentFrame->mvpCtx->NumMvFound += 1;
		}
	}
	else
	{
		//int candMv0[2] = av1Ctx->MotionFieldMvs[b_data->RefFrame[0]][y8][x8];
		int candMv0[2];
		memcpy(candMv0,av1Ctx->MotionFieldMvs[b_data->RefFrame[0]][y8][x8],2 * sizeof(int)); 
		if (candMv0[0] == -1 << 15)
			return ERROR_CODE;
		//int candMv1[2] = av1Ctx->MotionFieldMvs[b_data->RefFrame[1]][y8][x8];
		int candMv1[2] ;
		memcpy(candMv1,av1Ctx->MotionFieldMvs[b_data->RefFrame[1]][y8][x8],2 * sizeof(int)); 
		if (candMv1[0] == -1 << 15)
			return ERROR_CODE;
		lower_mv_precision(av1Ctx,candMv0);
		lower_mv_precision(av1Ctx,candMv1);
		if (deltaRow == 0 && deltaCol == 0)
		{
			if (Abs(candMv0[0] - av1Ctx->currentFrame->mvpCtx->GlobalMvs[0][0]) >= 16 ||
				Abs(candMv0[1] - av1Ctx->currentFrame->mvpCtx->GlobalMvs[0][1]) >= 16 ||
				Abs(candMv1[0] - av1Ctx->currentFrame->mvpCtx->GlobalMvs[1][0]) >= 16 ||
				Abs(candMv1[1] - av1Ctx->currentFrame->mvpCtx->GlobalMvs[1][1]) >= 16)
				av1Ctx->currentFrame->mvpCtx->ZeroMvContext = 1;
			else
				av1Ctx->currentFrame->mvpCtx->ZeroMvContext = 0;
		}
		int idx;
		for (idx = 0; idx < av1Ctx->currentFrame->mvpCtx->NumMvFound; idx++)
		{
			if (candMv0[0] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0][0] &&
				candMv0[1] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0][1] &&
				candMv1[0] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][1][0] &&
				candMv1[1] == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][1][1])
				break;
		}
		if (idx < av1Ctx->currentFrame->mvpCtx->NumMvFound)
		{
			av1Ctx->currentFrame->mvpCtx->WeightStack[idx] += 2;
		}
		else if (av1Ctx->currentFrame->mvpCtx->NumMvFound < MAX_REF_MV_STACK_SIZE)
		{
			//av1Ctx->RefStackMv[av1Ctx->NumMvFound][0] = candMv0;
			//av1Ctx->RefStackMv[av1Ctx->NumMvFound][1] = candMv1;
			memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][0],candMv0,2 * sizeof(int)); 
			memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][1],candMv1,2 * sizeof(int)); 
			av1Ctx->currentFrame->mvpCtx->WeightStack[av1Ctx->currentFrame->mvpCtx->NumMvFound] = 2;
			av1Ctx->currentFrame->mvpCtx->NumMvFound += 1;
		}
	}
}
//7.10.2.11
// performs a stable sort of part of the stack of motion vectors according to the corresponding weight.
int decode::Sorting(int start,int end ,int isCompound,AV1DecodeContext *av1Ctx){
    while (end > start) {
        int newEnd = start;
        for (int idx = start + 1; idx < end; idx++) {
            if (av1Ctx->currentFrame->mvpCtx->WeightStack[idx - 1] < av1Ctx->currentFrame->mvpCtx->WeightStack[idx]) {
                swap_stack(idx - 1, idx, isCompound, av1Ctx->currentFrame->mvpCtx->RefStackMv, av1Ctx->currentFrame->mvpCtx->WeightStack,av1Ctx);
                newEnd = idx;
            }
        }
        end = newEnd;
    }
}
void decode::swap_stack(int i, int j, int isCompound, int RefStackMv[][2][2], int WeightStack[],AV1DecodeContext *av1Ctx) {
    int temp = WeightStack[i];
    WeightStack[i] = WeightStack[j];
    WeightStack[j] = temp;
    
    for (int list = 0; list < 1 + isCompound; list++) {
        for (int comp = 0; comp < 2; comp++) {
            temp = av1Ctx->currentFrame->mvpCtx->RefStackMv[i][list][comp];
            av1Ctx->currentFrame->mvpCtx->RefStackMv[i][list][comp] = RefStackMv[j][list][comp];
            av1Ctx->currentFrame->mvpCtx->RefStackMv[j][list][comp] = temp;
        }
    }
}
//7.10.2.12
//This process adds additional motion vectors to RefStackMv until it has 2 choices of motion vector by first searching the
//left and above neighbors for partially matching candidates, and second adding global motion candidates
int decode::extra_search(int isCompound, BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int RefIdCountp[2];

	for (int list = 0; list < 2; list++)
	{
		av1Ctx->currentFrame->mvpCtx->RefIdCount[list] = 0;
		av1Ctx->currentFrame->mvpCtx->RefDiffCount[list] = 0;
	}
	int w4 = Min(16, Num_4x4_Blocks_Wide[b_data->MiSize]);
	int h4 = Min(16, Num_4x4_Blocks_High[b_data->MiSize]);
	w4 = Min(w4, frameHdr->MiCols - b_data->MiCol);
	h4 = Min(h4, frameHdr->MiRows - b_data->MiRow);
	int num4x4 = Min(w4, h4);
	//The first pass searches the row above, the second searches the column to the left.
	for (int pass = 0; pass < 2; pass++)
	{
		int idx = 0;
		while (idx < num4x4 && av1Ctx->currentFrame->mvpCtx->NumMvFound < 2)
		{
			int mvRow;
			int mvCol;
			if (pass == 0)
			{
				mvRow = b_data->MiRow - 1;
				mvCol = b_data->MiCol + idx;
			}
			else
			{
				mvRow = b_data->MiRow + idx;
				mvCol = b_data->MiCol - 1;
			}
			if (!is_inside(mvRow, mvCol,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd))
				break;
			add_extra_mv_candidate(mvRow, mvCol, isCompound,b_data,av1Ctx);
			if (pass == 0)
			{
				idx += Num_4x4_Blocks_Wide[av1Ctx->MiSizes[mvRow][mvCol]];
			}
			else
			{
				idx += Num_4x4_Blocks_High[av1Ctx->MiSizes[mvRow][mvCol]];
			}
		}
	}
	if (isCompound == 1)
	{
		int combinedMvs[2][2][2];
		for (int list = 0; list < 2; list++)
		{
			int compCount = 0;
			for (int idx = 0; idx < av1Ctx->currentFrame->mvpCtx->RefIdCount[list]; idx++)
			{
				//combinedMvs[compCount][list] = av1Ctx->RefIdMvs[list][idx];
				memcpy(combinedMvs[compCount][list],av1Ctx->currentFrame->mvpCtx->RefIdMvs[list][idx],2 * sizeof(int));
				compCount++;
			}
			for (int idx = 0; idx < av1Ctx->currentFrame->mvpCtx->RefDiffCount[list] && compCount < 2; idx++)
			{
				//combinedMvs[compCount][list] = av1Ctx->RefDiffMvs[list][idx];
				memcpy(combinedMvs[compCount][list],av1Ctx->currentFrame->mvpCtx->RefDiffMvs[list][idx],2* sizeof(int));
				compCount++;
			}
			while (compCount < 2)
			{
				//combinedMvs[compCount][list] = av1Ctx->GlobalMvs[list];
				memcpy(combinedMvs[compCount][list],av1Ctx->currentFrame->mvpCtx->GlobalMvs[list],2* sizeof(int));
				compCount++;
			}
		}
		if (av1Ctx->currentFrame->mvpCtx->NumMvFound == 1)
		{
			if (combinedMvs[0][0] == av1Ctx->currentFrame->mvpCtx->RefStackMv[0][0] &&
				combinedMvs[0][1] == av1Ctx->currentFrame->mvpCtx->RefStackMv[0][1])
			{
				//av1Ctx->RefStackMv[av1Ctx->NumMvFound][0] = combinedMvs[1][0];
				//av1Ctx->RefStackMv[av1Ctx->NumMvFound][1] = combinedMvs[1][1];
				memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][0],combinedMvs[1][0],2* sizeof(int));
				memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][1],combinedMvs[1][1],2* sizeof(int));
			}
			else
			{
				//av1Ctx->RefStackMv[av1Ctx->NumMvFound][0] = combinedMvs[0][0];
				//av1Ctx->RefStackMv[av1Ctx->NumMvFound][1] = combinedMvs[0][1];
				memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][0],combinedMvs[0][0],2* sizeof(int));
				memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][1],combinedMvs[0][1],2* sizeof(int));
			}
			av1Ctx->currentFrame->mvpCtx->WeightStack[av1Ctx->currentFrame->mvpCtx->NumMvFound] = 2;
			av1Ctx->currentFrame->mvpCtx->NumMvFound++;
		}
		else
		{
			for (int idx = 0; idx < 2; idx++)
			{
				//av1Ctx->RefStackMv[NumMvFound][0] = combinedMvs[idx][0];
				//av1Ctx->RefStackMv[NumMvFound][1] = combinedMvs[idx][1];
				memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][0],combinedMvs[idx][0],2* sizeof(int));
				memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[av1Ctx->currentFrame->mvpCtx->NumMvFound][1],combinedMvs[idx][1],2* sizeof(int));
				av1Ctx->currentFrame->mvpCtx->WeightStack[av1Ctx->currentFrame->mvpCtx->NumMvFound] = 2;
				av1Ctx->currentFrame->mvpCtx->NumMvFound++;
			}
		}
	}
	else
	{
		for (int idx = av1Ctx->currentFrame->mvpCtx->NumMvFound; idx < 2; idx++)
		{
			//av1Ctx->RefStackMv[idx][0] = av1Ctx->GlobalMvs[0];
			memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0],av1Ctx->currentFrame->mvpCtx->GlobalMvs[0],2* sizeof(int));
		}
	}
}
//7.10.2.13
//This process may modify the contents of the global variables RefIdMvs, RefIdCount, RefDiffMvs, RefDiffCount,
//RefStackMv, WeightStack, and NumMvFound.
int decode::add_extra_mv_candidate(int mvRow, int mvCol, int isCompound,
									BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if (isCompound)
	{
		for (int candList = 0; candList < 2; candList++)
		{
			int candRef = av1Ctx->RefFrames[mvRow][mvCol][candList];
			if (candRef > INTRA_FRAME)
			{
				for (int list = 0; list < 2; list++)
				{
					//int candMv[2] = p_data->Mvs[mvRow][mvCol][candList];
					int candMv[2] ;
					memcpy(candMv,av1Ctx->Mvs[mvRow][mvCol][candList],2* sizeof(int));
					if (candRef == b_data->RefFrame[list] && av1Ctx->currentFrame->mvpCtx->RefIdCount[list] < 2)
					{
						//av1Ctx->currentFrame->mvpCtx->RefIdMvs[list][av1Ctx->currentFrame->mvpCtx->RefIdCount[list]] = candMv;
						memcpy(av1Ctx->currentFrame->mvpCtx->RefIdMvs[list][av1Ctx->currentFrame->mvpCtx->RefIdCount[list]] ,candMv,2 * sizeof(int));
						av1Ctx->currentFrame->mvpCtx->RefIdCount[list]++;
					}
					else if (av1Ctx->currentFrame->mvpCtx->RefDiffCount[list] < 2)
					{
						if (frameHdr->RefFrameSignBias[candRef] != frameHdr->RefFrameSignBias[b_data->RefFrame[list]])
						{
							candMv[0] *= -1;
							candMv[1] *= -1;
						}
						//av1Ctx->RefDiffMvs[list][av1Ctx->RefDiffCount[list]] = candMv;
						memcpy(av1Ctx->currentFrame->mvpCtx->RefDiffMvs[list][av1Ctx->currentFrame->mvpCtx->RefDiffCount[list]],candMv,2* sizeof(int));
						av1Ctx->currentFrame->mvpCtx->RefDiffCount[list]++;
					}
				}
			}
		}
	}
	else
	{
		for (int candList = 0; candList < 2; candList++)
		{
			int candRef = av1Ctx->RefFrames[mvRow][mvCol][candList];
			if (candRef > INTRA_FRAME)
			{
				int candMv[2];
				//int candMv = Mvs[mvRow][mvCol][candList];
				memcpy(candMv,av1Ctx->Mvs[mvRow][mvCol][candList],2* sizeof(int));
				if (frameHdr->RefFrameSignBias[candRef] != frameHdr->RefFrameSignBias[b_data->RefFrame[0]])
				{
					candMv[0] *= -1;
					candMv[1] *= -1;
				}
				int idx;
				for (idx = 0; idx < av1Ctx->currentFrame->mvpCtx->NumMvFound; idx++)
				{
					if (candMv == av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0])
						break;
				}
				if (idx == av1Ctx->currentFrame->mvpCtx->NumMvFound)
				{
					//av1Ctx->RefStackMv[idx][0] = candMv;
					memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[idx][0],candMv,2* sizeof(int));
					av1Ctx->currentFrame->mvpCtx->WeightStack[idx] = 2;
					av1Ctx->currentFrame->mvpCtx->NumMvFound++;
				}
			}
		}
	}
}
//7.10.2.14
//This process computes contexts to be used when decoding syntax elements, and clamps the candidates in RefStackMv
int decode::context_and_clamping(int isCompound, int numNew,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	int bw = Block_Width[b_data->MiSize];
	int bh = Block_Height[b_data->MiSize];
	int numLists = isCompound ? 2 : 1;
	for (int idx = 0; idx < av1Ctx->currentFrame->mvpCtx->NumMvFound; idx++)
	{
		int z = 0;
		if (idx + 1 < av1Ctx->currentFrame->mvpCtx->NumMvFound)
		{
			int w0 = av1Ctx->currentFrame->mvpCtx->WeightStack[idx];
			int w1 = av1Ctx->currentFrame->mvpCtx->WeightStack[idx + 1];
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
		av1Ctx->currentFrame->mvpCtx->DrlCtxStack[idx] = z;
	}
	for (int list = 0; list < numLists; list++ ) {
		for (int idx = 0; idx < av1Ctx->currentFrame->mvpCtx->NumMvFound ; idx++ ) {
			int refMv[2];
			//int refMv[2] = av1Ctx->RefStackMv[ idx ][ list ];
			memcpy(refMv,av1Ctx->currentFrame->mvpCtx->RefStackMv[ idx ][ list ],2* sizeof(int));
			refMv[ 0 ] = clamp_mv_row( refMv[ 0 ], MV_BORDER + bh * 8,b_data,av1Ctx);
			refMv[ 1 ] = clamp_mv_col( refMv[ 1 ], MV_BORDER + bw * 8,b_data,av1Ctx);
			//av1Ctx->RefStackMv[ idx ][ list ] = refMv;
			memcpy(av1Ctx->currentFrame->mvpCtx->RefStackMv[ idx ][ list ],refMv,2* sizeof(int));
		}
	}	
	if ( av1Ctx->currentFrame->mvpCtx->CloseMatches == 0 ) {
		av1Ctx->currentFrame->mvpCtx->NewMvContext = Min( av1Ctx->currentFrame->mvpCtx->TotalMatches, 1 ); // 0,1
		av1Ctx->currentFrame->mvpCtx->RefMvContext = av1Ctx->currentFrame->mvpCtx->TotalMatches;
	} else if ( av1Ctx->currentFrame->mvpCtx->CloseMatches == 1 ) {
		av1Ctx->currentFrame->mvpCtx->NewMvContext = 3 - Min( numNew, 1 ); // 2,3
		av1Ctx->currentFrame->mvpCtx->RefMvContext = 2 + av1Ctx->currentFrame->mvpCtx->TotalMatches;
	} else {
		av1Ctx->currentFrame->mvpCtx->NewMvContext = 5 - Min( numNew, 1 ); // 4,5
		av1Ctx->currentFrame->mvpCtx->RefMvContext = 5;
	}
}
int decode::clamp_mv_row(int  mvec, int border ,BlockData *b_data,AV1DecodeContext *av1Ctx) { 
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int bh4 = Num_4x4_Blocks_High[ b_data->MiSize ];
	int mbToTopEdge = -((b_data->MiRow * MI_SIZE) * 8);
	int mbToBottomEdge = ((frameHdr->MiRows - bh4 - b_data->MiRow) * MI_SIZE) * 8;
	return Clip3( mbToTopEdge - border, mbToBottomEdge + border, mvec );
}
int decode::clamp_mv_col(int mvec,int border ,BlockData *b_data,AV1DecodeContext *av1Ctx) { 
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int bw4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
	int mbToLeftEdge = -((b_data->MiCol * MI_SIZE) * 8);
	int mbToRightEdge = ((frameHdr->MiCols - bw4 -b_data->MiCol) * MI_SIZE) * 8;
	return Clip3( mbToLeftEdge - border, mbToRightEdge + border, mvec );
}
int decode::lower_precision(int *candMv,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
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
int decode::get_tx_size(int plane,int txSz, int subsampling_x, int subsampling_y,BlockData *b_data)
{
	if (plane == 0)
		return txSz;
	int uvTx = Max_Tx_Size_Rect[get_plane_residual_size(b_data->MiSize, plane, subsampling_x, subsampling_y)];
	if (Tx_Width[uvTx] == 64 || Tx_Height[uvTx] == 64)
	{
		if (Tx_Width[uvTx] == 16)
		{
			return TX_16X32;
		}
		if (Tx_Height[uvTx] == 16)
		{
			return TX_32X16;
		}
		return TX_32X32;
	}
	return uvTx;
}
//7.10.3
int decode::has_overlappable_candidates( BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if (b_data->AvailU)
	{
		int w4 = Num_4x4_Blocks_Wide[b_data->MiSize];
		for (int x4 = b_data->MiCol; x4 < Min(frameHdr->MiCols, b_data->MiCol + w4); x4 += 2)
		{
			if (av1Ctx->RefFrames[b_data->MiRow - 1][x4 | 1][0] > INTRA_FRAME)
				return 1;
		}
	}
	if (b_data->AvailL)
	{
		int h4 = Num_4x4_Blocks_High[b_data->MiSize];
		for (int y4 = b_data->MiRow; y4 < Min(frameHdr->MiRows, b_data->MiRow + h4); y4 += 2)
		{
			if (av1Ctx->RefFrames[y4 | 1][b_data->MiCol - 1][0] > INTRA_FRAME)
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
int decode::find_warp_samples(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int doTopLeft = 1;
	int doTopRight = 1;
	av1Ctx->currentFrame->mvpCtx->NumSamples = 0;
	av1Ctx->currentFrame->mvpCtx->NumSamplesScanned = 0;
	int w4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
	int h4 = Num_4x4_Blocks_High[ b_data->MiSize ];
	if (b_data->AvailU)
	{
		int srcSize = av1Ctx->MiSizes[b_data->MiRow - 1][b_data->MiCol];
		int srcW = Num_4x4_Blocks_Wide[srcSize];
		if (w4 <= srcW)
		{
			int colOffset = -(b_data->MiCol & (srcW - 1));
			if (colOffset < 0)
				doTopLeft = 0;
			if (colOffset + srcW > w4)
				doTopRight = 0;
			add_sample(-1, 0,b_data,av1Ctx);
		}
		else
		{
			int miStep = 0;//???
			for (int i = 0; i < Min(w4,frameHdr->MiCols - b_data->MiCol); i += miStep)
			{
				srcSize = av1Ctx->MiSizes[b_data->MiRow - 1][b_data->MiCol + i];
				srcW = Num_4x4_Blocks_Wide[srcSize];
				miStep = Min(w4, srcW);
				add_sample(-1, i,b_data,av1Ctx);
			}
		}
	}
	if (b_data->AvailL)
	{
		int srcSize = av1Ctx->MiSizes[b_data->MiRow][b_data->MiCol - 1];
		int srcH = Num_4x4_Blocks_High[srcSize];
		if (h4 <= srcH)
		{
			int rowOffset = -(b_data->MiRow & (srcH - 1));
			if (rowOffset < 0)
				doTopLeft = 0;
			add_sample(0, -1,b_data,av1Ctx);
		}
		else
		{
			int miStep = 0;//???
			for (int i = 0; i < Min(h4, frameHdr->MiRows - b_data->MiRow); i += miStep)
			{
				srcSize = av1Ctx->MiSizes[b_data->MiRow + i][b_data->MiCol - 1];
				srcH = Num_4x4_Blocks_High[srcSize];
				miStep = Min(h4, srcH);
				add_sample(i, -1,b_data,av1Ctx);
			}
		}
	}
	if (doTopLeft)
	{
		add_sample(-1, -1,b_data,av1Ctx);
	}
	if (doTopRight)
	{
		if (Max(w4, h4) <= 16)
		{
			add_sample(-1, w4,b_data,av1Ctx);
		}
	}
	if (av1Ctx->currentFrame->mvpCtx->NumSamples == 0 && av1Ctx->currentFrame->mvpCtx->NumSamplesScanned > 0)
		av1Ctx->currentFrame->mvpCtx->NumSamples = 1;
}
int decode::add_sample(int deltaRow,int deltaCol,
				BlockData *b_data,AV1DecodeContext *av1Ctx){
    if (av1Ctx->currentFrame->mvpCtx->NumSamplesScanned >= LEAST_SQUARES_SAMPLES_MAX) {
        return ERROR_CODE; 
    }

    int mvRow = b_data->MiRow + deltaRow;
    int mvCol = b_data->MiCol + deltaCol;

    if (!is_inside(mvRow, mvCol,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd)) {
        return ERROR_CODE; 
    }
		//has not been written for this frame 是否被写了  到底该怎么写 还要想想
    if (av1Ctx->RefFrames[mvRow][mvCol][0]  == 0) {
        return ERROR_CODE; 
    }

    if (av1Ctx->RefFrames[mvRow][mvCol][0] != b_data->RefFrame[0]) 
        return ERROR_CODE; 

    if (av1Ctx->RefFrames[mvRow][mvCol][1] != NONE) {
        return ERROR_CODE; 
    }

    int candSz = av1Ctx->MiSizes[mvRow][mvCol];
    int candW4 = Num_4x4_Blocks_Wide[candSz];
    int candH4 = Num_4x4_Blocks_High[candSz];
    int candRow = mvRow & ~(candH4 - 1);
    int candCol = mvCol & ~(candW4 - 1);
    int midY = candRow * 4 + candH4 * 2 - 1;
    int midX = candCol * 4 + candW4 * 2 - 1;
    int threshold = Clip3(16, 112, Max(Block_Width[b_data->MiSize], Block_Height[b_data->MiSize]));
    int mvDiffRow = Abs(av1Ctx->Mvs[candRow][candCol][0][0] - b_data->Mv[0][0]);
    int mvDiffCol = Abs(av1Ctx->Mvs[candRow][candCol][0][1] - b_data->Mv[0][1]);
    int valid = ((mvDiffRow + mvDiffCol) <= threshold);

	av1Ctx->currentFrame->mvpCtx->NumSamplesScanned++;


    if (valid == 0 && av1Ctx->currentFrame->mvpCtx->NumSamplesScanned > 1) {
        return ERROR_CODE;
    }

    b_data->CandList[av1Ctx->currentFrame->mvpCtx->NumSamples][0] = midY * 8;
    b_data->CandList[av1Ctx->currentFrame->mvpCtx->NumSamples][1] = midX * 8;
    b_data->CandList[av1Ctx->currentFrame->mvpCtx->NumSamples][2] = midY * 8 + av1Ctx->Mvs[candRow][candCol][0][0];
    b_data->CandList[av1Ctx->currentFrame->mvpCtx->NumSamples][3] = midX * 8 + av1Ctx->Mvs[candRow][candCol][0][1];


    if (valid == 1) {
        av1Ctx->currentFrame->mvpCtx->NumSamples++;
    }

}
int decode::get_above_tx_width(int row, int col,BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	if (row == b_data->MiRow)
	{
		if (!b_data->AvailU)
		{
			return 64;
		}
		else if (av1Ctx->Skips[row - 1][col] && av1Ctx->IsInters[row - 1][col])
		{
			return Block_Width[av1Ctx->MiSizes[row - 1][col]];
		}
	}
	return Tx_Width[av1Ctx->InterTxSizes[row - 1][col]];
}
int decode::get_left_tx_height(int row,int col,BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	if (col == b_data->MiCol)
	{
		if (!b_data->AvailL)
		{
			return 64;
		}
		else if (av1Ctx->Skips[row][col - 1] && av1Ctx->IsInters[row][col - 1])
		{
			return Block_Width[av1Ctx->MiSizes[row][col - 1]];
		}
	}
	return Tx_Height[av1Ctx->InterTxSizes[row][col - 1]];
}
/*  find mv stack end ...*/

int decode::residual(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int sbMask = seqHdr->use_128x128_superblock ? 31 : 15;
	int widthChunks = Max(1, Block_Width[b_data->MiSize] >> 6);
	int	heightChunks = Max(1, Block_Height[b_data->MiSize] >> 6);
	int	miSizeChunk = (widthChunks > 1 || heightChunks > 1) ? BLOCK_64X64 : b_data->MiSize;
	for (int chunkY = 0; chunkY < heightChunks; chunkY++)
	{
		for (int chunkX = 0; chunkX < widthChunks; chunkX++)
		{
			int miRowChunk = b_data->MiRow + (chunkY << 4);
			int miColChunk = b_data->MiCol + (chunkX << 4);
			int subBlockMiRow = miRowChunk & sbMask;
			int subBlockMiCol = miColChunk & sbMask;
			for (int plane = 0; plane < 1 + b_data->HasChroma * 2; plane++)
			{
				int txSz = b_data->Lossless ? TX_4X4 : get_tx_size(plane, b_data->TxSize,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y,b_data);
				int stepX = Tx_Width[txSz] >> 2;
				int stepY = Tx_Height[txSz] >> 2;
				int planeSz = get_plane_residual_size(miSizeChunk, plane,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y);
				int num4x4W = Num_4x4_Blocks_Wide[planeSz];
				int num4x4H = Num_4x4_Blocks_High[planeSz];
				printf("stepX %d stepY %d num4x4W:%d num4x4H %d \n",stepX ,stepY ,num4x4W,num4x4H );
				int subX = (plane > 0) ? seqHdr->color_config.subsampling_x : 0;
				int subY = (plane > 0) ? seqHdr->color_config.subsampling_y : 0;
				int baseX = (miColChunk >> subX) * MI_SIZE;
				int baseY = (miRowChunk >> subY) * MI_SIZE;
				if (b_data->is_inter && !b_data->Lossless && !plane)
				{
					transform_tree(baseX, baseY, num4x4W * 4, num4x4H * 4,sbCtx,bs,b_data,av1Ctx);
				}
				else
				{
					int baseXBlock = (b_data->MiCol >> subX) * MI_SIZE;
					int baseYBlock = (b_data->MiRow >> subY) * MI_SIZE;
					printf("residual b_data->MiCol:%d b_data->MiRow :%d subX:%d subY:%d\n",
							b_data->MiCol,b_data->MiRow,subX,subY);
					for (int y = 0; y < num4x4H; y += stepY)
						for (int x = 0; x < num4x4W; x += stepX){
							transform_block(plane, baseXBlock, baseYBlock, txSz,
											x + ((chunkX << 4) >> subX),
											y + ((chunkY << 4) >> subY),
											sbCtx,bs,b_data,av1Ctx);
						}
				}
			}
		}
	}
}
int decode::transform_tree(int startX, int startY,int w,int h,SymbolContext *sbCtx,bitSt *bs,
							 BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int maxX = frameHdr->MiCols * MI_SIZE;
	int maxY = frameHdr->MiRows * MI_SIZE;
	if (startX >= maxX || startY >= maxY)
	{
		return ERROR_CODE;
	}
	int row = startY >> MI_SIZE_LOG2;
	int col = startX >> MI_SIZE_LOG2;
	int lumaTxSz = av1Ctx->InterTxSizes[row][col];
	int lumaW = Tx_Width[lumaTxSz];
	int lumaH = Tx_Height[lumaTxSz];
	if (w <= lumaW && h <= lumaH)
	{
		int txSz = find_tx_size(w, h);
		transform_block(0, startX, startY, txSz, 0, 0,sbCtx,bs,b_data,av1Ctx);
	}
	else
	{
		if (w > h)
		{
			transform_tree(startX, startY, w / 2, h,sbCtx,bs,b_data,av1Ctx);
			transform_tree(startX + w / 2, startY, w / 2, h,sbCtx,bs,b_data,av1Ctx);
		}
		else if (w < h)
		{
			transform_tree(startX, startY, w, h / 2,sbCtx,bs,b_data,av1Ctx);
			transform_tree(startX, startY + h / 2, w, h / 2,sbCtx,bs,b_data,av1Ctx);
		}
		else
		{
			transform_tree(startX, startY, w / 2, h / 2,sbCtx,bs,b_data,av1Ctx);
			transform_tree(startX + w / 2, startY, w / 2, h / 2,sbCtx,bs,b_data,av1Ctx);
			transform_tree(startX, startY + h / 2, w / 2, h / 2,sbCtx,bs,b_data,av1Ctx);
			transform_tree(startX + w / 2, startY + h / 2, w / 2, h / 2,sbCtx,bs,b_data,av1Ctx);
		}
	}
}
int decode::transform_block(int plane,int baseX,int baseY,int txSz,int x,int y,SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	//printf("transform_block baseX:%d baseY:%d x:%d y:%d\n",baseX,baseY,x,y);
	int startX = baseX + 4 * x;
	int startY = baseY + 4 * y;
	int subX = (plane > 0) ? seqHdr->color_config.subsampling_x : 0;
	int subY = (plane > 0) ? seqHdr->color_config.subsampling_y : 0;
	int row = (startY << subY) >> MI_SIZE_LOG2;
	int col = (startX << subX) >> MI_SIZE_LOG2;
	int sbMask = seqHdr->use_128x128_superblock ? 31 : 15;
	int subBlockMiRow = row & sbMask;
	int subBlockMiCol = col & sbMask;
	int stepX = Tx_Width[txSz] >> MI_SIZE_LOG2;
	int stepY = Tx_Height[txSz] >> MI_SIZE_LOG2;
	int maxX = (frameHdr->MiCols * MI_SIZE) >> subX;
	int maxY = (frameHdr->MiRows * MI_SIZE) >> subY;
	if (startX >= maxX || startY >= maxY)
	{
		return ERROR_CODE;
	}
	if (!b_data->is_inter)
	{
		//if (((plane == 0) && b_data->PaletteSizeY) ||
		//	((plane != 0) && b_data->PaletteSizeUV))
		//{
		//	predict_palette(plane, startX, startY, x, y, txSz,b_data,av1Ctx);
		//}
		//else
		//{
			int isCfl = (plane > 0 && b_data->UVMode == UV_CFL_PRED);
			int mode;
			if (plane == 0)
			{
				mode = b_data->YMode;
			}
			else
			{
				mode = (isCfl) ? DC_PRED : b_data->UVMode;
			}
			int log2W = Tx_Width_Log2[txSz];
			int log2H = Tx_Height_Log2[txSz];
			predict_intra(plane, startX, startY,
						(plane == 0 ? b_data->AvailL : b_data->AvailLChroma) || x > 0,
						(plane == 0 ? b_data->AvailU : b_data->AvailUChroma) || y > 0,
						(*av1Ctx->BlockDecoded)[plane][(subBlockMiRow >> subY) - 1][(subBlockMiCol >> subX) + stepX],
						(*av1Ctx->BlockDecoded)[plane][(subBlockMiRow >> subY) + stepY][(subBlockMiCol >> subX) - 1],
						mode,log2W, log2H, b_data,av1Ctx);
			if (isCfl)
			{
				//predict_chroma_from_luma(plane, startX, startY, txSz,b_data,av1Ctx);
			}
		//}
		if (plane == 0)
		{
			b_data->MaxLumaW = startX + stepX * 4;
			b_data->MaxLumaH = startY + stepY * 4;
		}
	}
	if (!b_data->skip)
	{
		int eob = coeffs(plane, startX, startY, txSz,sbCtx,bs,b_data,av1Ctx);
		if (eob > 0)
			reconstruct(plane, startX, startY, txSz,b_data,av1Ctx);
	}
	for (int i = 0; i < stepY; i++)
	{
		for (int j = 0; j < stepX; j++)
		{
			av1Ctx->LoopfilterTxSizes[plane]
							 [(row >> subY) + i]
							 [(col >> subX) + j] = txSz;
			(*av1Ctx->BlockDecoded)[plane]
						[(subBlockMiRow >> subY) + i]
						[(subBlockMiCol >> subX) + j] = 1;
		}
	}
}
int decode::calculateCoeffBrCtx(int txSz,int plane, int x4,int y4,int pos,BlockData *b_data,AV1DecodeContext *av1Ctx){
	int ctx;
	int adjTxSz = Adjusted_Tx_Size[txSz];
	int bwl = Tx_Width_Log2[adjTxSz];
	int txw = Tx_Width[adjTxSz];
	int txh = Tx_Height[adjTxSz];
	int row = pos >> bwl;
	int col = pos - (row << bwl);
	int mag = 0 ;
	int txType = compute_tx_type(plane, txSz, x4, y4,b_data,av1Ctx);
	int txClass = get_tx_class(txType);
	for (int i = 0; i < 3; i++)
	{
		int refRow = row + Mag_Ref_Offset_With_Tx_Class[txClass][i][0];
		int refCol = col + Mag_Ref_Offset_With_Tx_Class[txClass][i][1];
		if ( refRow >= 0 &&
		refCol >= 0 &&
		refRow < txh &&
		refCol < (1 << bwl) ) {
			mag += Min( b_data->Quant[ refRow * txw + refCol ], COEFF_BASE_RANGE + NUM_BASE_LEVELS + 1 );
		}

	}
	mag = Min((mag + 1) >> 1, 6) ;
	if (pos == 0)
	{
		ctx = mag;
	}
	else if (txClass == 0)
	{
		if ((row < 2) && (col < 2))
		{
			ctx = mag + 7;
		}
		else
		{
			ctx = mag + 14;
		}
	}
	else
	{
		if (txClass == 1)
		{
			if (col == 0)
			{
				ctx = mag + 7;
			}
			else
			{
				ctx = mag + 14;
			}
		}
		else
		{
			if (row == 0)
			{
				ctx = mag + 7;
			}
			else
			{
				ctx = mag + 14;
			}
		}
	}
	return ctx;
}
int decode::calculateDcSignCtx(int plane, int x4,int y4,int w4,int h4,AV1DecodeContext *av1Ctx)
{
	int ctx;
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int maxX4 = frameHdr->MiCols;
	int maxY4 = frameHdr->MiRows;
	if (plane > 0)
	{
		maxX4 = maxX4 >> seqHdr->color_config.subsampling_x;
		maxY4 = maxY4 >> seqHdr->color_config.subsampling_y;
	}
	int dcSign = 0;
	int sign;
	for (int k = 0; k < w4; k++)
	{
		if (x4 + k < maxX4)
		{
			sign = av1Ctx->AboveDcContext[plane][x4 + k];
			if (sign == 1)
			{
				dcSign--;
			}
			else if (sign == 2)
			{
				dcSign++;
			}
		}
	}
	for (int k = 0; k < h4; k++)
	{
		if (y4 + k < maxY4)
		{
			sign = av1Ctx->LeftDcContext[plane][y4 + k];
			if (sign == 1)
			{
				dcSign--;
			}
			else if (sign == 2)
			{
				dcSign++;
			}
		}
	}
	if (dcSign < 0)
	{
		ctx = 1;
	}
	else if (dcSign > 0)
	{
		ctx = 2;
	}
	else
	{
		ctx = 0;
	}
	return ctx;
}
int decode::coeffs(int plane,int startX,int startY,int txSz,SymbolContext *sbCtx,bitSt *bs,
							 BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int x4 = startX >> 2;
	int y4 = startY >> 2;
	int w4 = Tx_Width[txSz] >> 2;
	int h4 = Tx_Height[txSz] >> 2;
	int txSzCtx = (Tx_Size_Sqr[txSz] + Tx_Size_Sqr_Up[txSz] + 1) >> 1;
	int ptype = plane > 0;
	int segEob = (txSz == TX_16X64 || txSz == TX_64X16) ? 512 : Min(1024, Tx_Width[txSz] * Tx_Height[txSz]);
	for (int c = 0; c < segEob; c++)
		b_data->Quant[c] = 0;
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++)
			b_data->Dequant[i][j] = 0;
	int eob = 0;
	int culLevel = 0;
	int dcCategory = 0;

	int ctx = cacluteAllZeroCtx( plane, txSz,  x4, y4, w4, h4, b_data,av1Ctx);
	int all_zero = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Txb_Skip[ txSzCtx ][ ctx ],3); // S()
	printf("decodeSymbol all_zero %d\n",all_zero);
	if (all_zero)
	{
		int c = 0;
		if (plane == 0)
		{
			for (int i = 0; i < w4; i++)
			{
				for (int j = 0; j < h4; j++)
				{
					av1Ctx->TxTypes[y4 + j][x4 + i] = DCT_DCT;
				}
			}
		}
	}
	else
	{
		if (plane == 0)
			transform_type(x4, y4,txSz,sbCtx,bs,b_data,av1Ctx);
		b_data->PlaneTxType = compute_tx_type(plane, txSz, x4, y4,b_data,av1Ctx);
		const uint16_t  *scan = get_scan(txSz,b_data->PlaneTxType);
		int eobMultisize = Min(Tx_Width_Log2[txSz], 5) + Min(Tx_Height_Log2[txSz], 5) - 4;
		int eobPt;
		int txType = compute_tx_type( plane, txSz, x4, y4,b_data,av1Ctx);
		int ctx = ( get_tx_class( txType ) == TX_CLASS_2D ) ? 0 : 1;
		if (eobMultisize == 0)
		{
			int eob_pt_16 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Pt_16[ ptype ][ ctx ],6); // S()
			//printf("decodeSymbol eob_pt_16 %d \n",eob_pt_16);
			eobPt = eob_pt_16 + 1;
		}
		else if (eobMultisize == 1)
		{
			int eob_pt_32  = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Pt_32[ ptype ][ ctx ],7); // S()
			//printf("decodeSymbol eob_pt_32 %d \n",eob_pt_32);
			eobPt = eob_pt_32 + 1;
		}
		else if (eobMultisize == 2)
		{
			int eob_pt_64  = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Pt_64[ ptype ][ ctx ],8); // S()
			//printf("decodeSymbol eob_pt_64 %d \n",eob_pt_64);
			eobPt = eob_pt_64 + 1;
		}
		else if (eobMultisize == 3)
		{
			int eob_pt_128 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Pt_128[ ptype ][ ctx ],9); // S()
			//printf("decodeSymbol eob_pt_128 %d \n",eob_pt_128);
			eobPt = eob_pt_128 + 1;
		}
		else if (eobMultisize == 4)
		{
			int eob_pt_256 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Pt_256[ ptype ][ ctx ],10); // S()
			//printf("decodeSymbol eob_pt_256 %d \n",eob_pt_256);
			eobPt = eob_pt_256 + 1;
		}
		else if (eobMultisize == 5)
		{
			
			int eob_pt_512 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Pt_512[ ptype ],11); // S()
			//printf("decodeSymbol eob_pt_512 %d \n",eob_pt_512);
			eobPt = eob_pt_512 + 1;
		}
		else
		{
			
			int eob_pt_1024 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Pt_1024[ ptype ],12); // S()
			//printf("decodeSymbol eob_pt_1024 %d\n",eob_pt_1024);
			eobPt = eob_pt_1024 + 1;
		}
		eob = (eobPt < 2) ? eobPt : ((1 << (eobPt - 2)) + 1);
		int eobShift = Max(-1, eobPt - 3);
		if (eobShift >= 0)
		{
			int eob_extra = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Eob_Extra[ txSzCtx ][ ptype ][ eobPt - 3 ],3); // S()
			//printf("decodeSymbol eob_extra %d eobPt - 3: %d\n",eob_extra,eobPt - 3);
			if (eob_extra)
			{
				eob += (1 << eobShift);
			}
			for (int i = 1; i < Max(0, eobPt - 2); i++)
			{
				eobShift = Max(0, eobPt - 2) - 1 - i;
				
				int eob_extra_bit = sb->read_literal(sbCtx,bs,1); // L(1)
				//printf("read_literal eob_extra_bit %d\n",eob_extra_bit);
				if (eob_extra_bit)
				{
					eob += (1 << eobShift);
				}
			}
		}
		//printf("eob %d\n",eob);
		//eob + ac + dc， 最后一个下标0是 dc
		printf("coeffs\n");
		for (int c = eob - 1; c >= 0; c--)
		{
			int pos = scan[c];
			int level;
			//eob
			if (c == (eob - 1))
			{
				ctx =  get_coeff_base_ctx(txSz, plane, x4, y4, scan[c], c, 1,b_data,av1Ctx) - SIG_COEF_CONTEXTS + SIG_COEF_CONTEXTS_EOB;
				
				int coeff_base_eob = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Coeff_Base_Eob[ txSzCtx ][ ptype ][ ctx ],4);// S()
				//printf("decodeSymbol coeff_base_eob %d ctx %d\n",coeff_base_eob,ctx);
				level = coeff_base_eob + 1;
			}
			//ac + dc
			else
			{
				ctx = get_coeff_base_ctx(txSz, plane, x4, y4, scan[c], c, 0,b_data,av1Ctx);
				
				int coeff_base =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Coeff_Base[ txSzCtx ][ ptype ][ ctx ],5); // S()
				//printf("decodeSymbol coeff_base %d  txSzCtx %d ptype %d ,ctx %d\n",coeff_base,txSzCtx,ptype,ctx);
				level = coeff_base;
			}
			////printf("level %d\n",level);
			if (level > NUM_BASE_LEVELS)
			{
				//-------- compute coeff_br symbol ctx
				int ctx = calculateCoeffBrCtx(txSz,plane,x4,y4,pos,b_data,av1Ctx);
				//printf("coeff_br ctx %d\n",ctx);
				//------
				for (int idx = 0; idx < COEFF_BASE_RANGE / (BR_CDF_SIZE - 1); idx++)
				{
					int coeff_br = sb->decodeSymbol(sbCtx, bs, av1Ctx->tileSavedCdf.Coeff_Br[Min(txSzCtx, TX_32X32)][ptype][ctx], BR_CDF_SIZE + 1); // S()
					//printf("decodeSymbol coeff_br %d  Min(txSzCtx, TX_32X32) %d ptype %d  c %d pos %d idx %d\n",coeff_br,Min(txSzCtx, TX_32X32),ptype,c,pos,idx);
					level += coeff_br;
					if (coeff_br < (BR_CDF_SIZE - 1))
						break;
				}
			}
			b_data->Quant[pos] = level;
			//printf(" qu1 %d |",b_data->Quant[pos]);
		}
		printf("coeffs 2\n");
		for (int c = 0; c < eob; c++)
		{
			int pos = scan[c];
			int sign;
			if (b_data->Quant[pos] != 0)
			{
				//第一个, dc
				if (c == 0)
				{
				//-------- 
				int dcSignCtx = calculateDcSignCtx( plane,  x4, y4, w4, h4, av1Ctx);
				//---------
				//printf("decodeSymbol dc_sign\n");
					sign = sb->decodeSymbol(sbCtx, bs, av1Ctx->tileSavedCdf.Dc_Sign[ptype][dcSignCtx], 3); // S()
					//sign = dc_sign;
				}
				else
				{
					
					sign = sb->read_literal(sbCtx,bs,1); // L(1)
					//printf("read_literal sign_bit %d\n",sign_bit);
					//sign = sign_bit;
				}
			}
			else
			{
				sign = 0;
			}
			if (b_data->Quant[pos] > (NUM_BASE_LEVELS + COEFF_BASE_RANGE))
			{
				int length = 0;
				int golomb_length_bit;
				do
				{
					length++;
					//printf("read_literal golomb_length_bit\n");
					golomb_length_bit = sb->read_literal(sbCtx,bs,1); // L(1)
				} while (!golomb_length_bit);
				int x = 1;
				int golomb_data_bit;
				for (int i = length - 2; i >= 0; i--)
				{
					//printf("read_literal golomb_data_bit\n");
					golomb_data_bit = sb->read_literal(sbCtx,bs,1); // L(1)
					x = (x << 1) | golomb_data_bit;
				}
				//printf("golomb_data_bit x %d\n",x);
			 	b_data->Quant[pos] = x + COEFF_BASE_RANGE + NUM_BASE_LEVELS;
			}
			if (pos == 0 && b_data->Quant[pos] > 0)
			{
				dcCategory = sign ? 1 : 2;
			}
			b_data->Quant[pos] = b_data->Quant[pos] & 0xFFFFF;
			//printf("qu2 %d |",b_data->Quant[pos]);
			culLevel += b_data->Quant[pos];
			if (sign)
				b_data->Quant[pos] = -b_data->Quant[pos];
		}
		culLevel = Min(63, culLevel);
	}
	for (int i = 0; i < w4; i++)
	{
		av1Ctx->AboveLevelContext[plane][x4 + i] = culLevel;
		av1Ctx->AboveDcContext[plane][x4 + i] = dcCategory;
	}
	for (int i = 0; i < h4; i++)
	{
		av1Ctx->LeftLevelContext[plane][y4 + i] = culLevel;
		av1Ctx->LeftDcContext[plane][y4 + i] = dcCategory;
	}
	return eob;
}
int decode::cacluteAllZeroCtx(int plane,int txSz, int x4,int y4,int w4,int h4, BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int ctx;
	int maxX4 = frameHdr->MiCols;
	int maxY4 = frameHdr->MiRows;
	if (plane > 0)
	{
		maxX4 = maxX4 >> seqHdr->color_config.subsampling_x;
		maxY4 = maxY4 >> seqHdr->color_config.subsampling_y;
	}
	int w = Tx_Width[txSz];
	int h = Tx_Height[txSz];
	int bsize = get_plane_residual_size(b_data->MiSize, plane,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y);
	int bw = Block_Width[bsize];
	int bh = Block_Height[bsize];
	if (plane == 0)
	{
		int top = 0;
		int left = 0;
		for (int k = 0; k < w4; k++)
		{
			if (x4 + k < maxX4)
				top = Max(top, av1Ctx->AboveLevelContext[plane][x4 + k]);
		}
		for (int k = 0; k < h4; k++)
		{
			if (y4 + k < maxY4)
				left = Max(left, av1Ctx->LeftLevelContext[plane][y4 + k]);
		}
		top = Min(top, 255);
		left = Min(left, 255);
		if (bw == w && bh == h)
		{
			ctx = 0;
		}
		else if (top == 0 && left == 0)
		{
			ctx = 1;
		}
		else if (top == 0 || left == 0)
		{
			ctx = 2 + (Max(top, left) > 3);
		}
		else if (Max(top, left) <= 3)
		{
			ctx = 4;
		}
		else if (Min(top, left) <= 3)
		{
			ctx = 5;
		}
		else
		{
			ctx = 6;
		}
	}
	else
	{
		int above = 0;
		int left = 0;
		for (int i = 0; i < w4; i++)
		{
			if (x4 + i < maxX4)
			{
				above |= av1Ctx->AboveLevelContext[plane][x4 + i];
				above |= av1Ctx->AboveDcContext[plane][x4 + i];
			}
		}
		for (int i = 0; i < h4; i++)
		{
			if (y4 + i < maxY4)
			{
				left |= av1Ctx->LeftLevelContext[plane][y4 + i];
				left |= av1Ctx->LeftDcContext[plane][y4 + i];
			}
		}
		ctx = (above != 0) + (left != 0);
		ctx += 7;
		if (bw * bh > w * h)
			ctx += 3;
	}
	return ctx;
}
int decode::transform_type(int x4,int  y4,int txSz,SymbolContext *sbCtx,bitSt *bs,
						BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int set = get_tx_set(txSz,b_data->is_inter,frameHdr->reduced_tx_set);
	int TxType;
	if (set > 0 &&
		(frameHdr->segmentation_params.segmentation_enabled ? 
			seg_instance->get_qindex(1, b_data->segment_id,frameHdr,av1Ctx->CurrentQIndex) : frameHdr->quantization_params.base_q_idx) > 0)
	{
		uint16_t *cdf;
		int size;

		if (b_data->is_inter)
		{
			if(set == TX_SET_INTER_1){
				cdf = av1Ctx->tileSavedCdf.Inter_Tx_Type_Set1[ Tx_Size_Sqr[ txSz ] ];
				size = 17;
			}else if(set == TX_SET_INTER_2){
				cdf = av1Ctx->tileSavedCdf.Inter_Tx_Type_Set2;
				size = 13;
			}else if(set == TX_SET_INTER_3){
				cdf = av1Ctx->tileSavedCdf.Inter_Tx_Type_Set3[ Tx_Size_Sqr[ txSz ] ];
				size = 3;
			}
			//printf("decodeSymbol inter_tx_type\n");
			int inter_tx_type = sb->decodeSymbol(sbCtx,bs,cdf,size); // S()
			if (set == TX_SET_INTER_1)
				TxType = Tx_Type_Inter_Inv_Set1[inter_tx_type];
			else if (set == TX_SET_INTER_2)
				TxType = Tx_Type_Inter_Inv_Set2[inter_tx_type];
			else
				TxType = Tx_Type_Inter_Inv_Set3[inter_tx_type];
		}
		else
		{
			int intraDir;
			if( b_data->use_filter_intra == 1){
				intraDir = Filter_Intra_Mode_To_Intra_Dir[ b_data->filter_intra_mode ];
			}else{
				intraDir = b_data->YMode;
			}
			if(set == TX_SET_INTRA_1){
				cdf = av1Ctx->tileSavedCdf.Intra_Tx_Type_Set1[ Tx_Size_Sqr[ txSz ] ][ intraDir ];
				size = 8;
			}else if(set == TX_SET_INTRA_2){
				cdf = av1Ctx->tileSavedCdf.Intra_Tx_Type_Set2[ Tx_Size_Sqr[ txSz ] ][ intraDir ];
				size = 6;
			}
			//printf("decodeSymbol intra_tx_type\n");
			int intra_tx_type = sb->decodeSymbol(sbCtx,bs,cdf,size); // S()
			if (set == TX_SET_INTRA_1)
				TxType = Tx_Type_Intra_Inv_Set1[intra_tx_type];
			else
				TxType = Tx_Type_Intra_Inv_Set2[intra_tx_type];
		}
	}
	else
	{
		TxType = DCT_DCT;
	}
	for (int i = 0; i < (Tx_Width[txSz] >> 2); i++)
	{
		for (int j = 0; j < (Tx_Height[txSz] >> 2); j++)
		{
			av1Ctx->TxTypes[y4 + j][x4 + i] = TxType;
		}
	}
}
int decode::compute_tx_type(int plane, int txSz,int blockX,int blockY,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int txSzSqrUp = Tx_Size_Sqr_Up[txSz];
	if (b_data->Lossless || txSzSqrUp > TX_32X32)
		return DCT_DCT;
	int txSet = get_tx_set(txSz,b_data->is_inter,frameHdr->reduced_tx_set);
	if (plane == 0)
	{
		return av1Ctx->TxTypes[blockY][blockX];
	}
	int txType;
	if (b_data->is_inter)
	{
		int x4 = Max(b_data->MiCol, blockX << seqHdr->color_config.subsampling_x);
		int y4 = Max(b_data->MiRow, blockY << seqHdr->color_config.subsampling_y);
		txType = av1Ctx->TxTypes[y4][x4];
		if (!is_tx_type_in_set(txSet, txType,b_data->is_inter))
			return DCT_DCT;
		return txType;
	}
	txType = Mode_To_Txfm[b_data->UVMode];
	if (!is_tx_type_in_set(txSet, txType,b_data->is_inter)) 
		return DCT_DCT;
	return txType;
}
int decode::get_coeff_base_ctx(int txSz, int plane, int blockX, int blockY, int pos, int c, int isEob,
						BlockData *b_data,AV1DecodeContext *av1Ctx) {
    int adjTxSz = Adjusted_Tx_Size[txSz];
    int bwl = Tx_Width_Log2[adjTxSz];
    int width = 1 << bwl;
    int height = Tx_Height[adjTxSz];
    int txType = compute_tx_type(plane, txSz, blockX, blockY,b_data,av1Ctx);

    if (isEob) {
        if (c == 0) {
            return SIG_COEF_CONTEXTS - 4;
        }
        if (c <= (height << bwl) / 8) {
            return SIG_COEF_CONTEXTS - 3;
        }
        if (c <= (height << bwl) / 4) {
            return SIG_COEF_CONTEXTS - 2;
        }
        return SIG_COEF_CONTEXTS - 1;
    }

    int txClass = get_tx_class(txType);
    int row = pos >> bwl;
    int col = pos - (row << bwl);
    int mag = 0;

    for (int idx = 0; idx < SIG_REF_DIFF_OFFSET_NUM; idx++) {
        int refRow = row + Sig_Ref_Diff_Offset[txClass][idx][0];
        int refCol = col + Sig_Ref_Diff_Offset[txClass][idx][1];

        if (refRow >= 0 &&
            refCol >= 0 &&
            refRow < height &&
            refCol < width) {
            mag += Min(Abs(b_data->Quant[(refRow << bwl) + refCol]), 3);
        }
    }

    int ctx = Min((mag + 1) >> 1, 4);

    if (txClass == TX_CLASS_2D) {
        if (row == 0 && col == 0) {
            return 0;
        }
        return ctx + Coeff_Base_Ctx_Offset[txSz][Min(row, 4)][Min(col, 4)];
    }

    int idx = (txClass == TX_CLASS_VERT) ? row : col;
    return ctx + Coeff_Base_Pos_Ctx_Offset[Min(idx, 2)];
}


//7.11
/*帧内预测*/
//The process makes use of the already reconstructed samples in the current frame CurrFrame to form a 
//prediction for the current block.

int decode::predict_intra(int plane,int x,int y,int haveLeft,int haveAbove,
				int haveAboveRight,int haveBelowLeft,int mode,int log2W,int log2H,
				BlockData *b_data,AV1DecodeContext *av1Ctx){

	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int w = 1 << log2W;
	int h = 1 << log2H;
	int maxX = ( frameHdr->MiCols * MI_SIZE ) - 1;
	int maxY = ( frameHdr->MiRows * MI_SIZE ) - 1;

	if(plane > 0){
		maxX = ( ( frameHdr->MiCols * MI_SIZE ) >> seqHdr->color_config.subsampling_x ) - 1;
		maxY = ( ( frameHdr->MiRows * MI_SIZE ) >> seqHdr->color_config.subsampling_y ) - 1;
	}
	// int wLimit = frameHdr->si.FrameWidth % MI_SIZE == 0 ? maxX : maxX + MI_SIZE;
	// int hLimit = frameHdr->si.FrameHeight % MI_SIZE == 0 ? maxY : maxY + MI_SIZE;
	printf("haveLeft:%d haveAbove:%d haveAboveRight %d haveBelowLeft %d\n",haveLeft,haveAbove,haveAboveRight,haveBelowLeft);
    for (int i = 0; i < w + h; i++) {
        if (haveAbove == 0 && haveLeft == 1) {
            // 如果haveAbove为0且haveLeft为1，设置AboveRow[i]等于左侧的像素值
            (*b_data->AboveRow)[i] = av1Ctx->currentFrame->CurrFrame[plane][y][x - 1];
        } else if (haveAbove == 0 && haveLeft == 0) {
            // 如果haveAbove和haveLeft都为0，设置AboveRow[i]为(1 << (BitDepth - 1)) - 1
            (*b_data->AboveRow)[i] = (1 << (seqHdr->color_config.BitDepth - 1)) - 1;
        } else {

            int aboveLimit = x + (haveAboveRight ? 2 * w : w) - 1 ;
			//bug, readme.MD 问题8
			int lim = Min(aboveLimit, x+i) > maxX ? maxX : Min(aboveLimit, x+i);
			//int lim = Min(aboveLimit, x+i) ;
            (*b_data->AboveRow)[i] = av1Ctx->currentFrame->CurrFrame[plane][y - 1][lim];
			//printf("Min(aboveLimit, x+i) %d ",Min(aboveLimit, x+i));
		}
		//printf("AboveRow:%d i:%d ",(*b_data->AboveRow)[i],i);
    }
	printf("\n");
    for (int i = 0; i < w + h; i++) {
        if (haveLeft == 0 && haveAbove == 1) {
            // 如果haveLeft为0且haveAbove为1，设置LeftCol[i]等于上方的像素值
            (*b_data->LeftCol)[i] = av1Ctx->currentFrame->CurrFrame[plane][y - 1][x];
        } else if (haveLeft == 0 && haveAbove == 0) {
            // 如果haveLeft和haveAbove都为0，设置LeftCol[i]为(1 << (BitDepth - 1)) + 1
            (*b_data->LeftCol)[i] = (1 << (seqHdr->color_config.BitDepth - 1)) + 1;
        } else {
            int leftLimit = y + (haveBelowLeft ? 2 * h : h) - 1;
			//bug, readme.MD 问题8
			int lim = Min(leftLimit, y+i) > maxY ? maxY : Min(leftLimit, y+i);
			//int lim = Min(leftLimit, y+i);
            (*b_data->LeftCol)[i] = av1Ctx->currentFrame->CurrFrame[plane][lim][x - 1];
			//printf("Min(leftLimit, x+i) %d ",Min(leftLimit, y+i));
		}
		//printf("LeftCol:%d i:%d ",(*b_data->LeftCol)[i],i);
    }
	if(haveAbove == 1 && haveLeft == 1){
		(*b_data->AboveRow)[ -1 ] = av1Ctx->currentFrame->CurrFrame[ plane ][ y-1 ][x-1 ];
	}else if(haveAbove == 1){
		(*b_data->AboveRow)[ -1 ] = av1Ctx->currentFrame->CurrFrame[ plane ][ y-1 ][x ];
	}else if(haveLeft == 1) {
		(*b_data->AboveRow)[ -1 ] = av1Ctx->currentFrame->CurrFrame[ plane ][ y ][x-1 ];
	}else{
		(*b_data->AboveRow)[ -1 ] = 1 << ( seqHdr->color_config.BitDepth - 1 );
	}
	(*b_data->LeftCol)[ -1 ] = (*b_data->AboveRow)[ -1 ];

	//uint8_t pred[w][h];//内存大小需要确认
	uint16_t **pred =  new uint16_t *[h];
	for(int i = 0 ; i < h ; i++){
		pred[i] = new uint16_t[w];
	}
	printf("\n");
	if(plane == 0 && b_data->use_filter_intra){
		printf("recursiveIntraPrdiction\n");
		recursiveIntraPrdiction(w,h,pred,b_data,av1Ctx);
	}else if( is_directional_mode( mode ) ){
		printf("directionalIntraPrediction\n");
		directionalIntraPrediction( plane, x, y, haveLeft, haveAbove, mode, w, h, maxX, maxY,pred, b_data,av1Ctx);
	}else if(mode == SMOOTH_PRED || mode == SMOOTH_V_PRED  || mode == SMOOTH_H_PRED ){
		printf("smoothIntraPrediction\n");
		smoothIntraPrediction(mode, log2W, log2H, w,h,pred,b_data); 
	}else if(mode == DC_PRED){
		printf("DCIntraPrediction\n");
		DCIntraPrediction( haveLeft, haveAbove, log2W, log2H, w, h,pred,b_data,av1Ctx );
	}else if(mode == PAETH_PRED){
		printf("basicIntraPrediction\n");
		basicIntraPrediction(w,h,pred,b_data);
	}
	printf("\n");
	printf("pred\n");
	for(int i = 0 ; i < h ;i ++){
		for(int j = 0 ; j < w ;j ++){
			av1Ctx->currentFrame->CurrFrame[ plane ][ y + i ][ x + j ] = pred[ i ][ j ];
			//   if(pred[ i ][ j ] > 255)
			//   	printf("@@%d i:%d j:%d ",pred[ i ][ j ],i,j);
			//printf("%d ",pred[ i ][ j ]);
		}
	}
	printf("\n");
	for(int i = 0 ; i < h ; i++){
		delete [] pred[i];
	}
	delete [] pred;
}
//7.11.2.2
void decode::basicIntraPrediction(int w, int h, uint16_t** pred,BlockData *b_data) {

    // Perform intra prediction
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int base = (*b_data->AboveRow)[j] + (*b_data->LeftCol)[i] - (*b_data->AboveRow)[-1];
            int pLeft = Abs(base - (*b_data->LeftCol)[i]);
            int pTop = Abs(base - (*b_data->AboveRow)[j]);
            int pTopLeft = Abs(base - (*b_data->AboveRow)[-1]);

            if (pLeft <= pTop && pLeft <= pTopLeft) {
                pred[i][j] = (*b_data->LeftCol)[i];
            } else if (pTop <= pTopLeft) {
                pred[i][j] = (*b_data->AboveRow)[j];
            } else {
                pred[i][j] = (*b_data->AboveRow)[-1];
            }
        }
    }
}
//7.11.2.3
//For each block of 4x2 samples, this process first prepares an array p of 7 neighboring samples, and then produces the
//output block by filtering this array
//输入指定的区域，将之分割为一个一个的 4 * 2小块，进行一系列操作(预测，滤波)生成帧内预测样本
//输出在 pred数组中
int decode::recursiveIntraPrdiction(int w, int h,uint16_t **pred,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int w4 = w >> 2;
	int h2 = h >> 1;
	int i;

	for (int i2 = 0; i2 < h2; i2++)
	{
		for (int j4 = 0; j4 < w4; j4++)
		{
			//对于每个 4 * 2块，做以下操作

			//这个循环为当前 4 * 2块准备一个数组，包含7个样本
			uint16_t p[7];
			for (i = 0; i < 7; i++)
			{
				if (i < 5)
				{
					if (i2 == 0)
					{
						p[i] = (*b_data->AboveRow)[( j4 << 2 ) + i - 1 ];
					}
					else if (j4 == 0 && i == 0)
					{
						p[i] = (*b_data->LeftCol)[(i2 << 1) - 1];
					}
					else
					{
						p[i] =  pred[ ( i2 << 1 ) - 1 ][ ( j4 << 2 ) + i - 1 ];
					}
				}
				else
				{
					if (j4 == 0)
					{
						p[i] = (*b_data->LeftCol)[(i2 << 1) + i - 5];
					}
					else
					{
						p[i] = pred[ ( i2 << 1 ) + i - 5 ][ ( j4 << 2 ) - 1 ];
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
						pr += Intra_Filter_Taps[b_data->filter_intra_mode][( i1 << 2 ) + j1 ][i] * p[i];
					}
					pred[(i2 << 1) + i1][(j4 << 2) + j1] = Clip1(Round2Signed(pr,INTRA_FILTER_SCALE_BITS),seqHdr->color_config.BitDepth);
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
								int mode ,int w ,int h ,int maxX,int maxY,uint16_t **pred,
								BlockData *b_data ,AV1DecodeContext *av1Ctx){
	int angleDelta = plane == 0 ? b_data->AngleDeltaY : b_data->AngleDeltaUV;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int pAngle = ( Mode_To_Angle[ mode ] + angleDelta * ANGLE_STEP );
	printf("mode %d angleDelta %d pAngle %d\n",mode,angleDelta,pAngle);
	int upsampleAbove = 0;
	int upsampleLeft = 0;

	if(seqHdr->enable_intra_edge_filter == 1){
		int filterType ;
		if(pAngle != 90 && pAngle != 180){
			if(pAngle > 90 && pAngle < 180 && (w + h) >= 24){
				//7.11.2.7
				(*b_data->LeftCol)[-1] = (*b_data->AboveRow)[-1] =
					filterCornor(b_data->LeftCol,b_data->AboveRow);
			}
			//7.11.2.8
			filterType = intrafilterType(plane,b_data,av1Ctx); 
			if(haveAbove == 1){
				//7.11.2.9
				int strength = intraEdgeFilterStrengthSelection(w,h,filterType,pAngle - 90 );
				int numPx =  Min( w, ( maxX - x + 1 ) ) + ( pAngle < 90 ? h : 0 ) + 1;
				//7.11.2.12 
				intraEdgeFilter(numPx,strength,0,b_data);
			}
			if(haveLeft == 1){
				int strength = intraEdgeFilterStrengthSelection(w,h,filterType,pAngle - 180 );
				int numPx =   Min( h, ( maxY - y + 1 ) ) + ( pAngle > 180 ? w : 0 ) + 1;
				//7.11.2.12 
				intraEdgeFilter(numPx,strength,1,b_data);
			}
		}
		printf("\n");
		//7.11.2.10
		upsampleAbove = intraEdgeUpsampleSelection(w,h,filterType,pAngle - 90 );
		printf("upsampleAbove %d\n",upsampleAbove);
		int numPx = ( w + (pAngle < 90 ? h : 0) );
		if(upsampleAbove == 1){
			//7.11.2.11
			 intraEdgeUpsample(numPx,0,b_data,av1Ctx);
		}
		upsampleLeft = intraEdgeUpsampleSelection(w,h,filterType,pAngle - 180 );
		printf("upsampleLeft %d\n",upsampleAbove);
		numPx = ( h + (pAngle > 180 ? w : 0) );
		if(upsampleLeft == 1){
			intraEdgeUpsample(numPx,1,b_data,av1Ctx);
		}
	}

	printf("AboveRow  \n");
	int dx;
	if( pAngle < 90)
		dx = Dr_Intra_Derivative[ pAngle ];
	else if(pAngle > 90 && pAngle < 180)
		dx = Dr_Intra_Derivative[ 180 - pAngle ];
	else{
		//dx should be undefined;
	}
	
	int dy;
	if( pAngle > 90 && pAngle < 180)
		dy = Dr_Intra_Derivative[ pAngle - 90 ];
	else if(pAngle > 180)
		dy =	Dr_Intra_Derivative[ 270 - pAngle ];
	else{
		//dy should be undefined;
	}
	printf("dx %d dy %d\n",dx,dy);
	if(pAngle < 90){
			printf("pAngle < 90 \n");
			for(int i = 0 ; i < h; i++){
				for(int j = 0 ; j < w ; j++){
					int idx = ( i + 1 ) * dx;
					int base = (idx >> ( 6 - upsampleAbove ) ) + (j << upsampleAbove);
					int shift = ( (idx << upsampleAbove) >> 1 ) & 0x1F;
					int maxBaseX = (w + h - 1) << upsampleAbove;
					if(base < maxBaseX){
						//printf("|1@%d %d %d %d %d %d %d %d %d",i,j,upsampleAbove,dx,idx,base,shift,(*b_data->AboveRow)[ base ],(*b_data->AboveRow)[base + 1]);
							pred[ i ][ j ] = Round2( (*b_data->AboveRow)[ base ] * ( 32 - shift ) + (*b_data->AboveRow)[ base + 1 ] * shift, 5 );
					}else{
						//printf("|2@%d %d %d %d %d %d %d %d",i,j,upsampleAbove,dx,idx,maxBaseX,shift,(*b_data->AboveRow)[ maxBaseX ]);
						pred[ i ][ j ] = (*b_data->AboveRow)[maxBaseX ];
					}
				}
			}

	}else if(pAngle > 90 && pAngle < 180){
		printf("90 < pAngle <180 \n");
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int idx, base, shift;
				
				idx = (j << 6) - (i + 1) * dx;
				
				base = idx >> (6 - upsampleAbove);
				
				if (base >= -(1 << upsampleAbove)) {
					shift = ((idx << upsampleAbove) >> 1) & 0x1F;
					//0 17 0 7 1081 16 28 119 119
					//printf("|@%d %d %d %d %d %d %d %d %d",i,j,upsampleAbove,dx,idx,base,shift,(*b_data->AboveRow)[base],(*b_data->AboveRow)[base + 1]);
					pred[i][j] = Round2((*b_data->AboveRow)[base] * (32 - shift) + (*b_data->AboveRow)[base + 1] * shift, 5);
				} else {
					idx = (i << 6) - (j + 1) * dy;
					base = idx >> (6 - upsampleLeft);
					shift = ((idx << upsampleLeft) >> 1) & 0x1F;
					//&14 0 0 1104433174 -1104432278 -17256755 21 0 0
					//printf("|&%d %d %d %d %d %d %d %d %d",i,j,upsampleLeft,dy,idx,base,shift,(*b_data->LeftCol)[base],(*b_data->LeftCol)[base + 1]);
					pred[i][j] = Round2((*b_data->LeftCol)[base] * (32 - shift) + (*b_data->LeftCol)[base + 1] * shift, 5);
				}
			}
		}

	}else if(pAngle > 180){
		printf("pAngle > 180\n");
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int idx, base, shift;

				idx = (j + 1) * dy;

				base = (idx >> (6 - upsampleLeft)) + (i << upsampleLeft);

				shift = ((idx << upsampleLeft) >> 1) & 0x1F;
				//@1 31 0 211 6752 base:106 
				//printf("|@%d %d %d %d %d base:%d ",i,j,upsampleLeft,dy,idx,base);
				pred[i][j] = Round2((*b_data->LeftCol)[base] * (32 - shift) + (*b_data->LeftCol)[base + 1] * shift, 5);
			}
		}
	}
	else if (pAngle == 90)
	{
		printf("pAngle == 90\n");
		for (int j = 0; j < w; j++)
		{
			for (int i = 0; i < h; i++)
			{
				pred[i][j] = (*b_data->AboveRow)[j];
			}
		}
	}
	else if (pAngle == 180)
	{
		printf("pAngle == 180\n");
		for (int j = 0; j < w; j++)
		{
			for (int i = 0; i < h; i++)
			{
				pred[i][j] = (*b_data->LeftCol)[i];
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
int decode::DCIntraPrediction(int haveLeft ,int haveAbove,int log2W,int log2H,int w,int h,uint16_t **pred,
								BlockData *b_data,AV1DecodeContext *av1Ctx)
{

	int sum = 0;
	int avg, leftAvg, aboveAvg;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	// Calculate the average of available edge samples
	if (haveLeft == 1 && haveAbove == 1)
	{
		printf("l & a \n");
		// Case 1: Both left and above samples are available
		sum = 0;
		for (int k = 0; k < h; k++)
			sum += (*b_data->LeftCol)[k];
		for (int k = 0; k < w; k++)
			sum += (*b_data->AboveRow)[k];
		sum += (w + h) >> 1;
		avg = sum / (w + h);
		printf("sum %d  avg %d w+h %d\n",sum,avg,w+h);
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
		printf("l  \n");
		// Case 2: Only left samples are available
		for (int k = 0; k < h; k++)
		{
			sum += (*b_data->LeftCol)[k];
		}
		leftAvg = Clip1((sum + (h >> 1)) >> log2H,seqHdr->color_config.BitDepth);
		printf("sum %d  leftAvg %d\n",sum,leftAvg);
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
		printf(" a \n");
		// Case 3: Only above samples are available
		for (int k = 0; k < w; k++)
		{
			sum += (*b_data->AboveRow)[k];
		}
		aboveAvg = Clip1((sum + (w >> 1)) >> log2W,seqHdr->color_config.BitDepth);
		printf("sum %d  aboveAvg %d\n",sum,aboveAvg);
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
		printf("l & a either \n");
		printf("Avg %d\n",1 << ( seqHdr->color_config.BitDepth - 1));
		// Case 4: No valid samples available
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				pred[i][j] = 1 << ( seqHdr->color_config.BitDepth - 1);
			}
		}
	}
}
//7.11.2.7 
//使用插值的方法生成预测像素
//smWeights* 是一个权重值，用来
int decode::smoothIntraPrediction(int mode, int log2W, int log2H, int w, int h, uint16_t **pred,BlockData *b_data){
    if (mode == SMOOTH_PRED) {
        const uint8_t *smWeightsX;
        const uint8_t *smWeightsY;
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
				//printf("(*b_data->AboveRow)[j] %d",(*b_data->AboveRow)[j]);
                int smoothPred = smWeightsY[i] * (*b_data->AboveRow)[j] +
                                 (256 - smWeightsY[i]) * (*b_data->LeftCol)[h - 1] +
                                 smWeightsX[j] * (*b_data->LeftCol)[i] +
                                 (256 - smWeightsX[j]) * (*b_data->AboveRow)[w - 1];
                pred[i][j] = Round2(smoothPred, 9);
            }
        }
    } else if (mode == SMOOTH_V_PRED) {
        const uint8_t *smWeights;
 		if(log2H == 2){
			smWeights = Sm_Weights_Tx_4x4;
		}else if(log2H == 3){
			smWeights = Sm_Weights_Tx_8x8;
		}else if(log2H == 4){
			smWeights = Sm_Weights_Tx_16x16;
		}else if(log2H == 5){	
			smWeights = Sm_Weights_Tx_32x32;
		}else if(log2H == 6){
			smWeights = Sm_Weights_Tx_64x64;
		}
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int smoothPred = smWeights[i] * (*b_data->AboveRow)[j] +
                                 (256 - smWeights[i]) * (*b_data->LeftCol)[h - 1];
                pred[i][j] = Round2(smoothPred, 8);
            }
        }
    } else if (mode == SMOOTH_H_PRED) {
        const uint8_t *smWeights;
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
                int smoothPred = smWeights[j] * (*b_data->LeftCol)[i] +
                                 (256 - smWeights[j]) * (*b_data->AboveRow)[w - 1];
                pred[i][j] = Round2(smoothPred, 8);
            }
        }
    }

}
//7.11.2.7 使用一个三抽头滤波器对 leftcol aboverow角落像素进行滤波
int decode::filterCornor(Array16 *LeftCol,Array16 *AboveRow){
	int s = (*LeftCol)[ 0 ] * 5 + (*AboveRow)[ -1 ] * 6 + (*AboveRow)[ 0 ] * 5;
	return Round2(s,4);
}
//7.11.2.8
//如果左边或上边的块使用了smooth mode ，则返回值为1
int decode::intrafilterType(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx){
	return get_filter_type(plane,b_data,av1Ctx);
}


int decode::is_smooth(int row, int col, int plane,AV1DecodeContext *av1Ctx) {
    int mode;
    if (plane == 0) {
        mode = av1Ctx->YModes[row][col];
    } else {
        if (av1Ctx->RefFrames[row][col][0] > INTRA_FRAME) {
			return 0;
        }
        mode = av1Ctx->UVModes[row][col];
    }
    return (mode == SMOOTH_PRED || mode == SMOOTH_V_PRED || mode == SMOOTH_H_PRED);
}

int decode::get_filter_type(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx) {
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int aboveSmooth = 0;
    int leftSmooth = 0;
    int r, c;

    if ((plane == 0) ? b_data->AvailU : b_data->AvailUChroma) {
        r = b_data->MiRow - 1;
        c = b_data->MiCol;

        if (plane > 0) {
            if (seqHdr->color_config.subsampling_x && !(b_data->MiCol & 1)) {
                c++;
            }
            if (seqHdr->color_config.subsampling_y && (b_data->MiRow & 1)) {
                r--;
            }
        }

        aboveSmooth = is_smooth(r, c, plane,av1Ctx);
    }

    if ((plane == 0) ? b_data->AvailL :b_data->AvailLChroma) {
        r = b_data->MiRow;
        c = b_data->MiCol - 1;

        if (plane > 0) {
            if (seqHdr->color_config.subsampling_x && (b_data->MiCol & 1)) {
                c--;
            }
            if (seqHdr->color_config.subsampling_y && !(b_data->MiRow & 1)) {
                r++;
            }
        }

        leftSmooth = is_smooth(r, c, plane,av1Ctx);
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
				strength = 1;
		}
		else if (blkWh <= 16)
		{
			if (d >= 40)
				strength = 1;
		}
		else if (blkWh <= 24)
		{
			if (d >= 8)
				strength = 1;
			if (d >= 16)
				strength = 2;
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
//7.11.2.10
int decode::intraEdgeUpsampleSelection(int w, int h, int filterType, int delta){

	int useUpsample = 0;
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
int decode::intraEdgeUpsample(int numPx,int dir,BlockData *b_data,AV1DecodeContext *av1Ctx){
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	Array16 *buf;
	if(dir == 0 )
		buf = b_data->AboveRow;
	else 
		buf = b_data->LeftCol;

    int dup[numPx + 3];


    dup[0] = (*buf)[-1];
    for (int i = -1; i < numPx; i++) {
        dup[i + 2] = (*buf)[i];
    }
    dup[numPx + 2] = (*buf)[numPx - 1];


    (*buf)[-2] = dup[0];
	//printf("numPx 11%d \n",numPx);
    for (int i = 0; i < numPx; i++) {
        int s = -dup[i] + (9 * dup[i + 1]) + (9 * dup[i + 2]) - dup[i + 3];
        s = Clip1(Round2(s, 4),seqHdr->color_config.BitDepth);
        (*buf)[2 * i - 1] = s;
        (*buf)[2 * i] = dup[i + 2];
    }

}
int decode::intraEdgeFilter(int sz, int strength, int left,BlockData *b_data){
    if (strength == 0) {
		printf("intraEdgeFilter return imm\n");
        return ERROR_CODE; 
    }

    int edge[sz]; 
    for (int i = 0; i < sz; i++) {
        edge[i] = (left ? (*b_data->LeftCol)[i - 1] : (*b_data->AboveRow)[i - 1]);
    }

    for (int i = 1; i < sz; i++) {
        int s = 0;

        for (int j = 0; j < INTRA_EDGE_TAPS; j++) {
            int k = Clip3(0, sz - 1, i - 2 + j);
            s += Intra_Edge_Kernel[strength - 1][j] * edge[k];
        }

        if (left) {
            (*b_data->LeftCol)[i - 1] = (s + 8) >> 4;
        } else {
            (*b_data->AboveRow)[i - 1] = (s + 8) >> 4;
			printf("ef %d i:%d ",(*b_data->AboveRow)[i - 1],i - 1);
        }
    }

}
/*帧内预测结束*/
/*帧间预测*/

int decode::predict_inter(int plane, int x, int y,int w ,int h ,int candRow,int candCol,int IsInterIntra,
							BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int isCompound =  av1Ctx->RefFrames[ candRow ][ candCol ][ 1 ] > INTRA_FRAME;
	roundingVariablesDerivation(isCompound,av1Ctx);
	int LocalValid;
	int LocalWarpParams[6];
	if(plane == 0 && b_data->motion_mode == LOCALWARP){
		warpEstimation(b_data->CandList,LocalWarpParams,&LocalValid,b_data,av1Ctx);
	}
	if(plane == 0 && b_data->motion_mode == LOCALWARP && LocalValid == 1){
		int a,b,g,d;//these values will bediscard;
		setupShear(LocalWarpParams,&LocalValid,&a,&b,&g,&d);
	}
	int refList = 0;

genArray:
	int refFrame = av1Ctx->RefFrames[ candRow ][ candCol ][ refList ];
	int globalValid;
    if((b_data->YMode == GLOBALMV || b_data->YMode == GLOBAL_GLOBALMV) && frameHdr->global_motion_params.GmType[ refFrame ] > TRANSLATION){
		int a,b,g,d;//these values will bediscard;
		setupShear(frameHdr->global_motion_params.gm_params[ refFrame ],&globalValid,&a,&b,&g,&d);
	}

	int useWarp = 0;
    if (w >= 8 && h >= 8) {
		useWarp = 0;
    }else if( frameHdr->force_integer_mv == 0){
		useWarp = 0;
	}else if(b_data->motion_mode == LOCALWARP && LocalValid == 1){
		useWarp = 1;
	}else if(
		(b_data->YMode == GLOBALMV || b_data->YMode == GLOBAL_GLOBALMV) && frameHdr->global_motion_params.GmType[ refFrame ] > TRANSLATION &&
		is_scaled( refFrame ,frameHdr->ref_frame_idx,av1Ctx->RefUpscaledWidth,av1Ctx->RefFrameHeight,frameHdr->si.FrameWidth,frameHdr->si.RenderHeight) == 0 && globalValid == 1)
	{
		useWarp = 2;
	}else{
		useWarp = 0;
	}
	int mv[2];
	//	mv = p_data->Mvs[ candRow ][ candCol ][ refList ];
	memcpy(mv,av1Ctx->Mvs[ candRow ][ candCol ][ refList ],2* sizeof(int));
	int refIdx ;
	if(b_data->use_intrabc == 0){
		refIdx == frameHdr->ref_frame_idx[ refFrame - LAST_FRAME ];
	}else{
		refIdx = -1;
		//These values ensure that the motion vector scaling has no effect
		//spec 是这样说的 ，但是还是没明白为啥
		(*av1Ctx->RefFrameWidth)[ -1 ] = frameHdr->si.FrameWidth;
		(*av1Ctx->RefUpscaledWidth)[ -1 ] = frameHdr->si.UpscaledWidth;
	}
	int startX,startY,stepX,stepY;
	motionVectorScaling( plane,refIdx, x, y, mv, &startX,&startY,&stepX,&startY,av1Ctx);

//These values are needed to avoid intrabc prediction being cropped to the frame boundaries
	if(b_data->use_intrabc == 1){
		(*av1Ctx->RefFrameWidth)[ -1 ] = frameHdr->MiCols * MI_SIZE;
		(*av1Ctx->RefFrameHeight)[ -1 ] = frameHdr->MiRows * MI_SIZE;
		(*av1Ctx->RefUpscaledWidth)[ -1 ] = frameHdr->MiCols * MI_SIZE;
	}

	//uint8_t ***preds;
	uint16_t ***preds = new uint16_t**[2];
	for(int i = 0 ; i < 2 ; i++){
		preds[i] = new uint16_t *[h];
		for(int j = 0 ; j < h ; j++){
			preds[i][j] = new uint16_t[w];
		}	
	}

	if(useWarp == 0){
		for(int i8 = 0 ; i8 < ((h-1) >> 3 );i8 ++){
			for(int j8 = 0 ; j8 < ((w-1) >> 3) ;j8 ++){
				//块扭曲操作，每次一个 8*8大小的子块
				blockWarp(useWarp,plane,refList,x,y,i8,j8,w,h,preds[refList],LocalWarpParams,b_data,av1Ctx);
			}
		} 

	}
	if(useWarp == 0){
		block_inter_prediction(plane, refIdx,startX, startY, stepX, stepY, w, h, candRow, candCol,preds[refList],b_data,av1Ctx);
	}

	if(isCompound == 1 && refList == 0){
		refList = 1;
		goto genArray;
	}

	if(b_data->compound_type == COMPOUND_WEDGE && plane == 0){
		wedgeMask(w,h,b_data,av1Ctx);
	}else if(b_data->compound_type == COMPOUND_INTRA){
		intraModeVariantMask(w,h,b_data,av1Ctx);
	}else if(b_data->compound_type == COMPOUND_DIFFWTD && plane == 0){
		differenceWeightMask(preds,w,h,b_data,av1Ctx);
	}

	int FwdWeight,BckWeight;
	if(b_data->compound_type == COMPOUND_DISTANCE){
		distanceWeights(candRow,candCol,&FwdWeight,&BckWeight,av1Ctx);
	}

	if(isCompound == 0 && IsInterIntra == 0){
		for(int i = 0 ; i < h ; i ++){
			for(int j = 0 ; j < w ; j ++){
			    av1Ctx->currentFrame->CurrFrame[ plane ][ y + i ][ x + j ] = Clip1(preds[ 0 ][ i ][ j ] ,seqHdr->color_config.BitDepth);
			}
		}
	}else if(b_data->compound_type == COMPOUND_AVERAGE){
		for(int i = 0 ; i < h ; i ++){
			for(int j = 0 ; j < w ; j ++){
				av1Ctx->currentFrame->CurrFrame[ plane ][ y + i ][ x + j ] = Clip1( Round2( preds[ 0 ][ i ][ j ] + preds[ 1 ][ i ][ j ], 1 + av1Ctx->InterPostRound ),seqHdr->color_config.BitDepth );
			}
		}
	}else if(b_data->compound_type == COMPOUND_DISTANCE){
		for(int i = 0 ; i < h ; i ++){
			for(int j = 0 ; j < w ; j ++){
				av1Ctx->currentFrame->CurrFrame[ plane ][ y + i ][ x + j ] = Clip1( Round2( FwdWeight * preds[ 0 ][ i ][ j ] + BckWeight * preds[ 1 ][ i ][ j ], 4 + av1Ctx->InterPostRound ) ,seqHdr->color_config.BitDepth);
			}
		}
	}else{
		maskBlend(preds,plane ,x,y,w,h,b_data,av1Ctx);
	}

	if(b_data->motion_mode == OBMC ){
		overlappedMotionCompensation(plane,w,h,b_data,av1Ctx);
	}
	
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < h ; j++){
			delete [] preds[i][j];
		}
		delete [] preds[i];
	}
	delete [] preds;
}
//7.11.3.2
int decode::roundingVariablesDerivation(int isCompound,AV1DecodeContext *av1Ctx){
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	 av1Ctx->InterRound0 = 3;
	 av1Ctx->InterRound1 = isCompound ? 7 : 11;
    if (seqHdr->color_config.BitDepth == 12) {
        av1Ctx->InterRound0 += 2;
    }

    if (seqHdr->color_config.BitDepth == 12 && !isCompound) {
        av1Ctx->InterRound1 -= 2;
    }
    av1Ctx->InterPostRound = 2 * FILTER_BITS - (av1Ctx->InterRound0 + av1Ctx->InterRound1);


}
//7.11.3.6
int decode::setupShear(int *warpParams,int *warpValid,int *alpha,int *beta,int *gamma,int *delta){
   int divShift, divFactor;

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

    if ((4 * Abs(*alpha) + 7 * Abs(*beta)) >= (1 << WARPEDMODEL_PREC_BITS) ||
        (4 * Abs(*gamma) + 4 * Abs(*delta)) >= (1 << WARPEDMODEL_PREC_BITS)) {
        *warpValid = 0;
    } else {
        *warpValid = 1;
    }
}
//7.11.3.7
int decode::resolveDivisor(int d, int *divShift, int *divFactor){

    int n =  FloorLog2( Abs(d) );
    int e = Abs(d) - (1 << n);
    int f;
    if (n > DIV_LUT_BITS) {
        f = Round2( e, n - DIV_LUT_BITS );
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
int decode::warpEstimation(int CandList[4][4], int LocalWarpParams[6], int *LocalValid,BlockData *b_data,AV1DecodeContext *av1Ctx){
	int A[2][2] = {{0}};
    int Bx[2] = {0};
    int By[2] = {0};

    int w4 = Num_4x4_Blocks_Wide[b_data->MiSize];
    int h4 = Num_4x4_Blocks_High[b_data->MiSize];
    int midY = b_data->MiRow * 4 + h4 * 2 - 1;
    int midX = b_data->MiCol * 4 + w4 * 2 - 1;
    int suy = midY * 8;
    int sux = midX * 8;
    int duy = suy + b_data->Mv[0][0];
    int dux = sux + b_data->Mv[0][1];

    for (int i = 0; i < av1Ctx->currentFrame->mvpCtx->NumSamples; i++) {
        int sy = CandList[i][0] - suy;
        int sx = CandList[i][1] - sux;
        int dy = CandList[i][2] - duy;
        int dx = CandList[i][3] - dux;

        if (Abs(sx - dx) < LS_MV_MAX && Abs(sy - dy) < LS_MV_MAX) {
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
        return ERROR_CODE;
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

    int mvx = b_data->Mv[0][1];
    int mvy = b_data->Mv[0][0];
    int vx = mvx * (1 << (WARPEDMODEL_PREC_BITS - 3)) - (midX * (LocalWarpParams[2] - (1 << WARPEDMODEL_PREC_BITS)) + midY * LocalWarpParams[3]);
    int vy = mvy * (1 << (WARPEDMODEL_PREC_BITS - 3)) - (midX * LocalWarpParams[4] + midY * (LocalWarpParams[5] - (1 << WARPEDMODEL_PREC_BITS)));

    LocalWarpParams[0] = Clip3(-WARPEDMODEL_TRANS_CLAMP, WARPEDMODEL_TRANS_CLAMP - 1, vx);
    LocalWarpParams[1] = Clip3(-WARPEDMODEL_TRANS_CLAMP, WARPEDMODEL_TRANS_CLAMP - 1, vy);

}
////7.11.3.3
int decode::motionVectorScaling(int plane, int refIdx, int x, int y, int mv[2],
								int *startX,int *startY, int *stepX,int *stepY, AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int xScale, yScale;
    int subX, subY;
    int halfSample = 1 << (SUBPEL_BITS - 1);
    int origX, origY;
    int baseX, baseY;
    int off;

    if (plane == 0) {
        subX = 0;
        subY = 0;
    } else {
        subX = seqHdr->color_config.subsampling_x;
        subY = seqHdr->color_config.subsampling_y;
    }

    origX = (x << SUBPEL_BITS) + ((2 * mv[1]) >> subX) + halfSample;
    origY = (y << SUBPEL_BITS) + ((2 * mv[0]) >> subY) + halfSample;

    xScale = (( (*av1Ctx->RefUpscaledWidth)[refIdx] << REF_SCALE_SHIFT) + (frameHdr->si.FrameWidth / 2)) /frameHdr->si.FrameWidth;
    yScale = (((*av1Ctx->RefFrameHeight)[refIdx] << REF_SCALE_SHIFT) + (frameHdr->si.FrameHeight / 2)) / frameHdr->si.FrameHeight;

    baseX = (origX * xScale - (halfSample << REF_SCALE_SHIFT));
    baseY = (origY * yScale - (halfSample << REF_SCALE_SHIFT));

    off = (1 << (SCALE_SUBPEL_BITS - SUBPEL_BITS)) / 2;

    *startX = (Round2Signed(baseX, REF_SCALE_SHIFT + SUBPEL_BITS - SCALE_SUBPEL_BITS) + off);
    *startY = (Round2Signed(baseY, REF_SCALE_SHIFT + SUBPEL_BITS - SCALE_SUBPEL_BITS) + off);

    *stepX = Round2Signed(xScale, REF_SCALE_SHIFT - SCALE_SUBPEL_BITS);
    *stepY = Round2Signed(yScale, REF_SCALE_SHIFT - SCALE_SUBPEL_BITS);
}
////7.11.3.5
int decode::blockWarp(int useWarp,int plane,int refList,int x,int y,
						int i8,int j8,int w,int h,uint16_t **pred,int LocalWarpParams[6],
						BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int refIdx = frameHdr->ref_frame_idx[b_data->RefFrame[refList] - LAST_FRAME];

    // Calculate ref
    uint16_t ***ref = av1Ctx->FrameStore[refIdx];

    // Calculate subX and subY
    int subX, subY;
    if (plane == 0) {
        subX = 0;
        subY = 0;
    } else {
        subX = seqHdr->color_config.subsampling_x;
        subY = seqHdr->color_config.subsampling_y;
    }

    int lastX = (( (*av1Ctx->RefUpscaledWidth)[refIdx] + subX) >> subX) - 1;
    int lastY = (( (*av1Ctx->RefFrameHeight)[refIdx] + subY) >> subY) - 1;

    // Calculate srcX and srcY
    int srcX = (x + j8 * 8 + 4) << subX;
    int srcY = (y + i8 * 8 + 4) << subY;

    // Calculate warpParams
    int warpParams[6];
    if (useWarp == 1) {
        for (int i = 0; i < 6; i++) {
            warpParams[i] = LocalWarpParams[i];
        }
    } else if (useWarp == 2) {
        for (int i = 0; i < 6; i++) {
            warpParams[i] = frameHdr->global_motion_params.gm_params[b_data->RefFrame[refList]][i];
        }
    }

    // Calculate dstX and dstY
    int dstX = warpParams[2] * srcX + warpParams[3] * srcY + warpParams[0];
    int dstY = warpParams[4] * srcX + warpParams[5] * srcY + warpParams[1];

    // Invoke shear process
    int warpValid, alpha, beta, gamma, delta;
    setupShear(warpParams, &warpValid, &alpha, &beta, &gamma, &delta);

	int x4 = dstX >> subX;
	int y4 = dstY >> subY;
	int ix4 = x4 >> WARPEDMODEL_PREC_BITS;
	int sx4 = x4 & ((1 << WARPEDMODEL_PREC_BITS) - 1);
	int iy4 = y4 >> WARPEDMODEL_PREC_BITS;
	int sy4 = y4 & ((1 << WARPEDMODEL_PREC_BITS) - 1);

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
            intermediate[i1 + 7][i2 + 4] = Round2(s, av1Ctx->InterRound0);
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
            pred[i8 * 8 + i1 + 4][j8 * 8 + i2 + 4] = Round2(s, av1Ctx->InterRound1);
        }
    }
}
//7.11.3.4
//The sub-sample interpolation is effected via two one-dimensional convolutions. First a horizontal filter is used to build up a
//temporary array, and then this array is vertically filtered to obtain the final prediction. The fractional parts of the motion
//vectors determine the filtering process. If the fractional part is zero, then the filtering is equivalent to a straight sample
//copy
int decode::block_inter_prediction(int plane, int refIdx, int x, int y, int xStep, int yStep, 
						int w, int h, int candRow, int candCol,uint16_t **pred,
						BlockData *b_data,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;		
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    uint16_t ***ref;
    if (refIdx == -1) {
        ref = av1Ctx->currentFrame->CurrFrame;
    } else if (refIdx >= 0) {
        ref = av1Ctx->FrameStore[refIdx];
    }

    // Calculate subX and subY
    int subX, subY;
    if (plane == 0) {
        subX = 0;
        subY = 0;
    } else {
        subX = seqHdr->color_config.subsampling_x;
        subY = seqHdr->color_config.subsampling_y;
    }

    // Calculate lastX and lastY
    int lastX = (((*av1Ctx->RefUpscaledWidth)[refIdx] + subX) >> subX) - 1;
    int lastY = (((*av1Ctx->RefFrameHeight)[refIdx] + subY) >> subY) - 1;

    // Calculate intermediateHeight
    int intermediateHeight = (((h - 1) * yStep + (1 << SCALE_SUBPEL_BITS) - 1) >> SCALE_SUBPEL_BITS) + 8;

    // Sub-sample interpolation - Horizontal filter
    int interpFilter = av1Ctx->InterpFilters[candRow][candCol][1];
    if (w <= 4) {
        if (interpFilter == EIGHTTAP || interpFilter == EIGHTTAP_SHARP) {
            interpFilter = 4;
        } else if (interpFilter == EIGHTTAP_SMOOTH) {
            interpFilter = 5;
        }
    }
    int intermediate[intermediateHeight][w];
    for (int r = 0; r < intermediateHeight; r++) {
        for (int c = 0; c < w; c++) {
            int s = 0;
            int p = x + xStep * c;
            for (int t = 0; t < 8; t++) {
                s += Subpel_Filters[interpFilter][(p >> 6) & SUBPEL_MASK][t] *
                     ref[plane][Clip3(0, lastY, (y >> 10) + r - 3)][Clip3(0, lastX, (p >> 10) + t - 3)];
            }
            intermediate[r][c] = Round2(s, av1Ctx->InterRound0);
        }
    }

    // Sub-sample interpolation - Vertical filter
    interpFilter = av1Ctx->InterpFilters[candRow][candCol][0];
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
            pred[r][c] = Round2(s, av1Ctx->InterRound1);
        }
    }
}
//7.11.3.11
int decode::wedgeMask(int WMW,int WMH,BlockData *b_data,AV1DecodeContext *av1Ctx){
	int w, h,shift, sum, avg, flipSign, msk;
    w = MASK_MASTER_SIZE;
	h = MASK_MASTER_SIZE;

	uint8_t MasterMask[6][w][h];
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
	uint8_t WedgeMasks[BLOCK_SIZES][2][WEDGE_TYPES][h][w];
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
	for (int  i = 0; i < WMW; i++ ) {
		for (int  j = 0; j < WMH; j++ ) {
			b_data->Mask[ i ][ j ] = WedgeMasks[ b_data->MiSize ][ b_data->wedge_sign ][ b_data->wedge_index ][ i ][ j ];
		}
	}
}
//7.11.3.13
//This process prepares an array Mask containing the blending weights for the luma samples.
int decode::intraModeVariantMask(int w, int h,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	int sizeScale = MAX_SB_SIZE / Max(h, w);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (b_data->interintra_mode == II_V_PRED)
			{
				b_data->Mask[i][j] = Ii_Weights_1d[i * sizeScale];
			}
			else if (b_data->interintra_mode == II_H_PRED)
			{
				b_data->Mask[i][j] = Ii_Weights_1d[j * sizeScale];
			}
			else if (b_data->interintra_mode == II_SMOOTH_PRED)
			{
				b_data->Mask[i][j] = Ii_Weights_1d[Min(i, j) * sizeScale];
			}
			else
			{
				b_data->Mask[i][j] = 32;
			}
		}
	}
}
//7.11.3.12
//This process prepares an array Mask containing the blending weights for the luma samples
int decode::differenceWeightMask(uint16_t ***preds, int w, int h,BlockData *b_data,  AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int diff = Abs(preds[0][i][j] - preds[1][i][j]);
			diff = Round2(diff, (seqHdr->color_config.BitDepth - 8) + av1Ctx->InterPostRound);
			int m = Clip3(0, 64, 38 + diff / 16);
			if (b_data->mask_type)
				b_data->Mask[i][j] = 64 - m;
			else
				b_data->Mask[i][j] = m;
		}
	}
}
//7.11.3.15
//This process computes weights to be used for blending predictions together based on the expected output times of the
//reference frames.
int decode::distanceWeights(int candRow,int candCol,int *FwdWeight,int *BckWeight,  
							 AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
 	int refList;  
    int h;  
    int dist[2];  
    int d0, d1;  
    int order;  
    int i;  
  
    for (refList = 0; refList < 2; refList++) {  
		h = frameHdr->OrderHints[ av1Ctx->RefFrames[ candRow ][ candCol ][ refList ] ];
		dist[ refList ] = Clip3( 0, MAX_FRAME_DISTANCE, Abs( get_relative_dist( seqHdr->enable_order_hint,seqHdr->OrderHintBits,h, frameHdr->OrderHint ) ) );
    }  
  
    d0 = dist[1];  
    d1 = dist[0];  
    order = d0 <= d1;  
  
    if (d0 == 0 || d1 == 0) {  
        *FwdWeight = Quant_Dist_Lookup[3][order];  
        *BckWeight = Quant_Dist_Lookup[3][1 - order];  
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
  
        *FwdWeight = Quant_Dist_Lookup[i][order];  
        *BckWeight = Quant_Dist_Lookup[i][1 - order];  
    }  
}
//The process combines two predictions according to the mask. It makes use of an array Mask containing the blending
//weights to apply (the weights are defined for the current plane samples if compound_type is equal to
//COMPOUND_INTRA, or the luma plane otherwise).
int decode::maskBlend(uint16_t ***preds,int plane , int dstX,int dstY,int w,int h,BlockData *b_data,AV1DecodeContext *av1Ctx){
	
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int subX, subY;  
    int m;  
    int pred0, pred1;  
  
    if (plane == 0) {  
        subX = subY = 0;  
    } else {  
        subX = seqHdr->color_config.subsampling_x;  
        subY = seqHdr->color_config.subsampling_y;  
    }  
  
    for (int y = 0; y < h; y++) {  
        for (int x = 0; x < w; x++) {  
            if ((!subX && !subY) || (b_data->interintra && !b_data->wedge_interintra)) {  
                m = b_data->Mask[y][x];  
            } else if (subX && !subY) {  
                m = Round2(b_data->Mask[y][2*x] + b_data->Mask[y][2*x+1], 1);  
            } else if (!subX && subY) {  
                m = Round2(b_data->Mask[2*y][x] + b_data->Mask[2*y+1][x], 1);  
            } else {  
                m = Round2(b_data->Mask[2*y][2*x] + b_data->Mask[2*y][2*x+1] + b_data->Mask[2*y+1][2*x] + b_data->Mask[2*y+1][2*x+1], 2);  
            }  
  
            if (b_data->interintra) {  
                pred0 = Clip1(Round2(preds[0][y][x], av1Ctx->InterPostRound),seqHdr->color_config.BitDepth);  
                pred1 = av1Ctx->currentFrame->CurrFrame[plane][y+dstY][x+dstX];  
                av1Ctx->currentFrame->CurrFrame[plane][y+dstY][x+dstX] = Round2(m * pred1 + (64 - m) * pred0, 6);  
            } else {  
                pred0 = preds[0][y][x];  
                pred1 = preds[1][y][x];  
                av1Ctx->currentFrame->CurrFrame[plane][y+dstY][x+dstX] = Clip1(Round2(m * pred0 + (64 - m) * pred1, 6 + av1Ctx->InterPostRound),seqHdr->color_config.BitDepth);  
            }  
        }  
    }  

}
//This process blends the inter predicted samples for the current block with inter predicted samples based on motion
//vectors from the above and left blocks.
//The maximum number of overlapped predictions is limited based on the size of the block.
//For small blocks, only the left neighbor will be used to form the prediction
//7.11.3.9

int decode::overlappedMotionCompensation(int plane, int w ,int h,
					BlockData *b_data,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

    int pass;
    int w4, h4,x4, y4, nCount, nLimit;
    int candRow, candCol, candSz, step4, predW, predH;
	uint8_t *mask;

	int subX,subY;
    if (b_data->AvailU) {
        if (get_plane_residual_size(b_data->MiSize, plane,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y) >= BLOCK_8X8) {
            pass = 0;
            w4 = Num_4x4_Blocks_Wide[b_data->MiSize];
            x4 = b_data->MiCol;
            y4 = b_data->MiRow;
            nCount = 0;
            nLimit = Min(4, Mi_Width_Log2[b_data->MiSize]);

            while (nCount < nLimit && x4 < Min(frameHdr->MiCols, b_data->MiCol + w4)) {
                candRow = b_data->MiRow - 1;
                candCol = x4 | 1;
                candSz = av1Ctx->MiSizes[candRow][candCol];
                step4 = Clip3(2, 16, Num_4x4_Blocks_Wide[candSz]);

                if (av1Ctx->RefFrames[candRow][candCol][0] > INTRA_FRAME) {
                    nCount += 1;
                    predW = Min(w, (step4 * MI_SIZE) >> subX);
                    predH = Min(h >> 1, 32 >> subY);
                    mask = get_obmc_mask(predH);
                    predict_overlap(b_data->MiSize, plane, x4, y4, predW, predH, subX, subY, candRow,candCol,pass,
								mask,b_data,av1Ctx);
                }

                x4 += step4;
            }
        }
    }

    if (b_data->AvailL) {
        pass = 1;
        h4 = Num_4x4_Blocks_High[b_data->MiSize];
        x4 = b_data->MiCol;
        y4 = b_data->MiRow;
        nCount = 0;
        nLimit = Min(4, Mi_Height_Log2[b_data->MiSize]);

        while (nCount < nLimit && y4 < Min(frameHdr->MiRows, b_data->MiRow + h4)) {
            candCol = b_data->MiCol - 1;
            candRow = y4 | 1;
            candSz = av1Ctx->MiSizes[candRow][candCol];
            step4 = Clip3(2, 16, Num_4x4_Blocks_High[candSz]);

            if (av1Ctx->RefFrames[candRow][candCol][0] > INTRA_FRAME) {
                nCount += 1;
                predW = Min(w >> 1, 32 >> subX);
                predH = Min(h, (step4 * MI_SIZE) >> subY);
                mask = get_obmc_mask(predW);
                predict_overlap(b_data->MiSize, plane, x4, y4, predW, predH, subX, subY, candRow,candCol,pass,
								mask,b_data,av1Ctx);
            }

            y4 += step4;
        }
    }
}

int decode::predict_overlap(int MiSize,int plane ,int x4,int y4,int predW,int predH,int subX,int subY ,
						  int candRow,int candCol ,int pass,uint8_t *mask,BlockData *b_data, AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int mv[2];
	memcpy(mv,av1Ctx->Mvs[ candRow ][ candCol ][ 0 ],2* sizeof(int));
	int refIdx = frameHdr->ref_frame_idx[ av1Ctx->RefFrames[ candRow ][ candCol ][ 0 ] - LAST_FRAME ];
	int predX = (x4 * 4) >> subX;
	int predY = (y4 * 4) >> subY;
	int startX, startY, stepX, stepY;
	motionVectorScaling(plane,refIdx,predX, predY, mv ,&startX,&startY,&stepX,&stepY,av1Ctx);

	//uint8_t obmcPred[predH][predW];
	uint16_t **obmcPred =  new uint16_t *[predH];
	for(int i = 0 ; i < predH ; i++){
		obmcPred[i] = new uint16_t[predW];
	}
	block_inter_prediction(plane, refIdx, startX, startY, stepX, stepY,predW, predH, candRow, candCol,obmcPred,
										b_data,av1Ctx);

	
	for(int i = 0; i < predH;i++){
		for(int j = 0; j < predW;j++){
			obmcPred[ i ][ j ] = Clip1( obmcPred[ i ][ j ] ,seqHdr->color_config.BitDepth);
		}
	}
	OverlapBlending(plane, predX, predY, predW, predH, pass,obmcPred,mask,av1Ctx);

	
	for(int i = 0 ; i < predH ; i++){
		delete [] obmcPred[i] ;
	}
	delete [] obmcPred ;
}
//7.11.3.10

int decode::OverlapBlending(int plane ,int predX,int predY,int predW,int predH ,int pass,
						uint16_t **obmcPred,uint8_t *mask,AV1DecodeContext *av1Ctx){
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
			av1Ctx->currentFrame->CurrFrame[ plane ][ predY + i ][ predX + j ] = 
					Round2( m * av1Ctx->currentFrame->CurrFrame[ plane ][ predY + i ][ predX + j ] + (64 - m) * obmcPred[ i ][ j ], 6);
		}
	}
} 

//7.11.4
int decode::predict_palette(int plane, int startX, int startY, int x, int y, int txSz,
							BlockData *b_data,AV1DecodeContext *av1Ctx) {
    int w = Tx_Width[txSz]; // 获取变换块的宽度
    int h = Tx_Height[txSz]; // 获取变换块的高度
    uint16_t *palette; // 调色板数组
    uint8_t **map; // 颜色映射数组

    if (plane == 0) {
        palette =  b_data->palette_colors_y;
        map = b_data->ColorMapY;
    } else {
        palette = (plane == 1) ? b_data->palette_colors_u : b_data->palette_colors_v;
        map = b_data->ColorMapUV;
    }
	printf("pred pal\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            av1Ctx->currentFrame->CurrFrame[plane][startY + i][startX + j] = palette[map[y * 4 + i][x * 4 + j]];
			printf("%d ",palette[map[y * 4 + i][x * 4 + j]]);
		}
    }
	printf("\n");
}
//7.11.5
int decode::predict_chroma_from_luma(int plane, int startX, int startY, int txSz,BlockData *b_data,AV1DecodeContext *av1Ctx) {
    sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int w = 1 << Tx_Width_Log2[txSz];
    int h = 1 << Tx_Height_Log2[txSz];
    int subX = seqHdr->color_config.subsampling_x;
    int subY = seqHdr->color_config.subsampling_y;
    int alpha = (plane == 1) ? b_data->CflAlphaU : b_data->CflAlphaV;
    int L[h][w];
    int lumaAvg = 0;

    for (int i = 0; i < h; i++) {
        int lumaY = (startY + i) << subY;
        lumaY = Min(lumaY , b_data->MaxLumaH - (1 << subY));

        for (int j = 0; j < w; j++) {
            int lumaX = (startX + j) << subX;
            lumaX = Min(lumaX , b_data->MaxLumaW - (1 << subX));

            int t = 0;
            for (int dy = 0; dy <= subY; dy += 1) {
                for (int dx = 0; dx <= subX; dx += 1) {
                    t += av1Ctx->currentFrame->CurrFrame[0][lumaY + dy][lumaX + dx];
                }
            }

            int v = t << (3 - subX - subY);
            L[i][j] = v;
            lumaAvg += v;
        }
    }

    lumaAvg = Round2(lumaAvg , (1 << (Tx_Width_Log2[txSz] + Tx_Height_Log2[txSz] - 1)));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int dc = av1Ctx->currentFrame->CurrFrame[plane][startY + i][startX + j];
            //int scaledLuma = (int)((alpha * (L[i][j] - lumaAvg)) * 64);
			int scaledLuma = Round2Signed( alpha * ( L[ i ][ j ] - lumaAvg ), 6 );

            av1Ctx->currentFrame->CurrFrame[plane][startY + i][startX + j] = Clip1(dc + scaledLuma,seqHdr->color_config.BitDepth);
        	printf("pcfl plane%d i %d j %d %d|",plane ,startY + i,startX + j,av1Ctx->currentFrame->CurrFrame[plane][startY + i][startX + j]);
		}
    }
}                                                                                                                                                                                                                                              

//7.12
int decode::get_dc_quant(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    
    int qindex = seg_instance->get_qindex(0, b_data->segment_id,frameHdr,av1Ctx->CurrentQIndex);
    if (plane == 0) {
        return dc_q(qindex + frameHdr->quantization_params.DeltaQYDc,seqHdr->color_config.BitDepth);
    } else if (plane == 1) {
        return dc_q(qindex + frameHdr->quantization_params.DeltaQUDc,seqHdr->color_config.BitDepth);
    } else {
        return dc_q(qindex + frameHdr->quantization_params.DeltaQVDc,seqHdr->color_config.BitDepth);
    }
}

// Function to calculate the quantizer value for the ac coefficient for a given plane.
int decode::get_ac_quant(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int qindex = seg_instance->get_qindex(0, b_data->segment_id,frameHdr,av1Ctx->CurrentQIndex);
    
    if (plane == 0) {
        return ac_q(qindex,seqHdr->color_config.BitDepth);
    } else if (plane == 1) {
        return ac_q(qindex + frameHdr->quantization_params.DeltaQUAc,seqHdr->color_config.BitDepth);
    } else {
        return ac_q(qindex + frameHdr->quantization_params.DeltaQVAc,seqHdr->color_config.BitDepth);
    }
}
int decode::reconstruct(int plane, int x, int y, int txSz,BlockData *b_data,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
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
	printf("!!!!!!!txSZ %d log2W %d log2H %d\n",txSz,log2W,log2H);
    int w = 1 << log2W;
    int h = 1 << log2H;
    int tw = Min(32, w);
    int th = Min(32, h);
    int flipUD = (b_data->PlaneTxType == FLIPADST_DCT || b_data->PlaneTxType == FLIPADST_ADST || b_data->PlaneTxType == V_FLIPADST || b_data->PlaneTxType == FLIPADST_FLIPADST) ? 1 : 0;
    int flipLR = (b_data->PlaneTxType == DCT_FLIPADST || b_data->PlaneTxType == ADST_FLIPADST || b_data->PlaneTxType == H_FLIPADST || b_data->PlaneTxType == FLIPADST_FLIPADST) ? 1 : 0;
    printf("residual 11\n");

    for (int i = 0; i < th; i++) {
        for (int j = 0; j < tw; j++) {
            int q = (i == 0 && j == 0) ? 
					get_dc_quant(plane,b_data,av1Ctx) : 
					get_ac_quant(plane,b_data,av1Ctx);
            int q2;
    		if(frameHdr->quantization_params.using_qmatrix == 1 &&
				b_data->PlaneTxType < IDTX &&
				frameHdr->quantization_params.SegQMLevel[ plane ][ b_data->segment_id ] < 15)
			{
				q2 = Round2(q * Quantizer_Matrix[frameHdr->quantization_params.SegQMLevel[plane][b_data->segment_id]][plane > 0][Qm_Offset[txSz] + i * tw + j], 5);
			}else{
				q2 = q;
			}        
            int dq = b_data->Quant[i * tw + j] * q2;
            int sign = (dq < 0) ? -1 : 1;
            int dq2 = sign * (Abs(dq) & 0xFFFFFF) / dqDenom;
            //printf("idx %d ,%d @ %d  @ %d ",i * tw + j,q2,b_data->Quant[i * tw + j],dq2);
			b_data->Dequant[ i ][ j ] = Clip3( - ( 1 << ( 7 + seqHdr->color_config.BitDepth ) ), ( 1 << ( 7 + seqHdr->color_config.BitDepth ) ) - 1, dq2 );
			//printf("%d ",b_data->Dequant[ i ][ j ]);
        }
    }
	//反变换
    //uint16_t Residual[h][w];
	int16_t **Residual = new int16_t *[h];
	for(int i = 0 ; i < h ; i ++){
		Residual[i] = new int16_t[w];
	}
	printf("residual 22\n");
	twoDInverseTransformBlock(txSz,Residual,b_data,av1Ctx);
	printf("residual 33 \n");

	int X = x;
	int Y = y;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int xx = flipLR ? (w - j - 1) : j;
            int yy = flipUD ? (h - i - 1) : i;
            //printf("%d ", Residual[i][j]);
			//注意这里写的和spec 不一样，临时解法！！
            av1Ctx->currentFrame->CurrFrame[plane][Y + yy][X + xx] = Clip3(0,255,av1Ctx->currentFrame->CurrFrame[plane][Y + yy][X + xx] + Residual[i][j]);
        	//printf("x:%d y:%d xx:%d yy:%d ---",X,Y,xx,yy);
			
		}
    }
	printf("\n");
	printf("x:%d y:%d  ---",X,Y);
	printf("\n");
	for(int i = 0 ; i < h ; i ++){
		delete []  Residual[i];
	}
	delete [] Residual;
    // 无损模式下 需要完全无损 ，因此 Residual 内的每个像素 用 1 + BitDepth位来表示，即比位深度还多一位
	//确保不会溢出 ，保证数据 无损
    if (b_data->Lossless == 1) {
        // Ensure values in the Residual array are representable by a signed integer with 1 + BitDepth bits (not shown in this code).
    }
}
//7.13.2.2 翻转数组
int decode::inverseDCTArrayPermutation(int16_t T[],int n)
{
    int16_t copyT[1 << n];
    // 复制数组 T 到 copyT
	memcpy(copyT,T,(1 << n) * sizeof(int16_t));
    // 根据位翻转函数 brev(n, i) 重新排列数组 T
    for (int i = 0; i < (1 << n); i++) {
        T[i] = copyT[brev(n, i)];
    }
}
//7.13.2.3 一维反 DCT 变换
int decode::inverseDCT(int16_t T[], int n, int r) {
    // 步骤1：执行逆 DCT 排列
    inverseDCTArrayPermutation(T, n);

	if(n == 6){
		for(int i = 0 ; i < 16 ; i++){
			B( 32 + i, 63 - i, 63 - 4 * brev( 4, i ), 0, r ,T);
		}
	}
	if(n >= 5){
		for(int i = 0 ; i < 8 ; i++){
			 B( 16 + i, 31 - i, 6 + ( brev( 3, 7 - i ) << 3 ), 0, r ,T);
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 16 ; i++){
			H( 32 + i * 2, 33 + i * 2, i & 1, r ,T );
		}
	}
	if(n >= 4){
		for(int i = 0 ; i < 4 ; i++){
			 B( 8 + i, 15 - i, 12 + ( brev( 2, 3 - i ) << 4 ), 0, r ,T);
		}
	}
	if(n >= 5){
		for(int i = 0 ; i < 8 ; i++){
			 H( 16 + 2 * i, 17 + 2 * i, i & 1, r  ,T) ;
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 2 ; j++)
				B( 62 - i * 4 - j, 33 + i * 4 + j, 60 - 16 * brev( 2, i ) + 64 * j, 1, r  ,T);
		}
	}
	if(n >= 3){
		for(int i = 0 ; i < 2 ; i++){
			 B( 4 + i, 7 - i, 56 - 32 * i, 0, r ,T );
		}
	}
	if(n >= 4){
		for(int i = 0 ; i < 4; i++){
			H( 8 + 2 * i, 9 + 2 * i, i & 1, r  ,T);
		}
	}
	if(n >= 5){
		for(int i = 0 ;i < 2 ; i++ )
			for(int j = 0 ; j < 2 ;j ++)
				B( 30 - 4 * i - j, 17 + 4 * i + j, 24 + (j << 6) + ( ( 1 - i ) << 5 ), 1, r ,T );
	}
	if(n == 6){
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 0 ; j < 2 ; j++)
				H( 32 + i * 4 + j, 35 + i * 4 - j, i & 1, r ,T );
		}
	}
	for(int i = 0 ; i < 2 ; i ++)
		B( 2 * i, 2 * i + 1, 32 + 16 * i, 1 - i, r ,T );

	if(n >= 3){
		for(int i = 0 ; i < 2; i++){
			H( 4 + 2 * i, 5 + 2 * i, i, r  ,T);
		}
	}
	if(n >= 4){
		for(int i = 0 ; i < 2; i++){
			B( 14 - i, 9 + i, 48 + 64 * i, 1, r ,T );
		}
	}
	if(n >= 5){
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 2 ; j++)
				H( 16 + 4 * i + j, 19 + 4 * i - j, i & 1, r ,T );
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 2 ; i++){
			for(int j = 0 ; j < 4 ; j++)
				B( 61 - i * 8 - j, 34 + i * 8 + j, 56 - i * 32 + ( j >> 1 ) * 64, 1, r ,T );
		}
	}
	for(int i = 0 ; i < 2 ; i ++)
		H( i, 3 - i, 0, r  ,T);
	

	if(n >= 3){
		B( 6, 5, 32, 1, r  ,T);
	}
	if(n >= 4){
		for(int i = 0 ; i < 2; i++){
			for(int j = 0 ; j < 2 ; j++)
				H( 8 + 4 * i + j, 11 + 4 * i - j, i, r  ,T);
		}
	}
	if(n >= 5){
		for(int i = 0 ; i < 4 ; i++){
			B( 29 - i, 18 + i, 48 + ( i >> 1 ) * 64, 1, r  ,T);
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 4 ; j++)
				H( 32 + 8 * i + j, 39 + 8 * i - j, i & 1, r  ,T) ;
		}
	}

	if(n >= 3){
		for(int i = 0 ; i < 4; i++){
			H( i, 7 - i, 0, r ,T ) ;
		}
	}
	if(n >= 4){
		for(int i = 0 ; i < 2; i++){
			B( 13 - i, 10 + i, 32, 1, r ,T ) ;
		}
	}
	if(n >= 5){
		for(int i = 0 ; i < 2 ; i++){
			for(int j = 0 ; j < 4 ; j++)
				H( 16 + i * 8 + j, 23 + i * 8 - j, i, r ,T );
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 8 ; i++){
			B( 59 - i, 36 + i, i < 4 ? 48 : 112, 1, r ,T );
		}
	}
	if(n >= 4){
		for(int i = 0 ; i < 8; i++){
			H( i, 15 - i, 0, r  ,T);
		}
	}
	if(n >= 5){
		for(int i = 0 ; i < 5; i++){
			B( 27 - i, 20 + i, 32, 1, r ,T );
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 8 ; i++){
			H( 32 + i, 47 - i, 0, r  ,T);
			H( 48 + i, 63 - i, 1, r ,T );
		}
	}
	if(n == 5){
		for(int i = 0 ; i < 16 ; i++){
			H( i, 31 - i, 0, r ,T );
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 8 ; i++){
			B( 55 - i, 40 + i, 32, 1, r ,T ) ;
		}
	}
	if(n == 6){
		for(int i = 0 ; i < 32 ; i++){
			H( i, 63 - i, 0, r ,T);
		}
	}
}
//7.13.2.4
void decode::inverseADSTInputArrayPermutation(int16_t* T, int n) {
    int n0 = 1 << n;
    int16_t copyT[n0]; 

	memcpy(copyT,T,n0 * sizeof(int16_t));
    // 执行位逆序排列
    for (int i = 0; i < n0; i++) {
		 //区分奇偶
        int idx = (i & 1) ? (i - 1) : (n0 - i - 1);
        T[i] = copyT[idx];
    }

}
//7.13.2.5
void decode::inverseADSTOutputArrayPermutation(int16_t* T, int n) {
    int n0 = 1 << n;
    int16_t copyT[n0];
	memcpy(copyT,T,n0* sizeof(int16_t));
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
void decode::inverseADST4(int16_t* T, int r) {

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
void decode::inverseADST8(int16_t* T, int r) {

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
void decode::inverseADST16(int16_t* T, int r) {
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
void decode::inverseADST(int16_t *T,int n,int r){
	if(n == 2 ){
		inverseADST4(T,r);
	}else if(n == 3){
		inverseADST8(T,r);
	}else if(n ==4){
		inverseADST16(T,r);
	}
}
//7.13.2.10
void decode::inverseWalshHadamardTransform(int16_t* T, int shift) {
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
void decode::inverseIdentityTransform4(int16_t* T){
	for(int i = 0 ; i < 4 ; i ++){
		T[ i ] = Round2( T[ i ] * 5793, 12 );
	}
}

//7.13.2.12
void decode::inverseIdentityTransform8(int16_t* T){
	for(int i = 0 ; i < 8 ; i ++){
		T[ i ] = T[ i ] * 2;
	}
}

//7.13.2.13
void decode::inverseIdentityTransform16(int16_t* T){
	for(int i = 0 ; i < 16 ; i ++){
		T[ i ] = Round2( T[ i ] * 11586, 12 );
	}
}

//7.13.2.14
void decode::inverseIdentityTransform32(int16_t* T){
	for(int i = 0 ; i < 32 ; i ++){
		T[ i ] = T[ i ] * 4;
	}
}

//7.13.2.15
void decode::inverseIdentityTransform(int16_t *T,int n){
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
void decode::twoDInverseTransformBlock(int txSz,int16_t **Residual,BlockData *b_data, AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int log2W = Tx_Width_Log2[ txSz ];
    int log2H = Tx_Height_Log2[txSz];
    int w = 1 << log2W;
    int h = 1 << log2H;
    int rowShift = b_data->Lossless ? 0 : Transform_Row_Shift[txSz];
    int colShift = b_data->Lossless ? 0 : 4;
    int rowClampRange = seqHdr->color_config.BitDepth + 8;
    int colClampRange = Max(seqHdr->color_config.BitDepth + 6, 16);

	int16_t T[w];
	//printf("Residual 11\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i < 32 && j < 32) {
                T[j] = b_data->Dequant[i][j];
            } else {
                T[j] = 0;
            }
        }

        if (Abs(log2W - log2H) == 1) {
            for (int j = 0; j < w; j++) {
                T[j] = Round2(T[j] * 2896, 12);
            }
        }

        if (b_data->Lossless) {
            inverseWalshHadamardTransform(T, 2);
        } else if (b_data->PlaneTxType == DCT_DCT || b_data->PlaneTxType == ADST_DCT || b_data->PlaneTxType == FLIPADST_DCT || b_data->PlaneTxType == H_DCT) {
			//printf("T 11 aa\n");
			for (int j = 0; j < w; j++) {
				//printf("%d ",T[j]);
			}
			//printf("T 11 bb\n");   
			inverseDCT(T, log2W, rowClampRange);
			for (int j = 0; j < w; j++) {
				//printf("%d ",T[j]);
			}
			//printf("T 11 cc\n"); 
        } else if (b_data->PlaneTxType == DCT_ADST || b_data->PlaneTxType == ADST_ADST || b_data->PlaneTxType == DCT_FLIPADST ||
                   b_data->PlaneTxType == FLIPADST_FLIPADST || b_data->PlaneTxType == ADST_FLIPADST || b_data->PlaneTxType == FLIPADST_ADST ||
                   b_data->PlaneTxType == H_ADST || b_data->PlaneTxType == H_FLIPADST) {
            inverseADST(T, log2W, rowClampRange);
        } else {
            inverseIdentityTransform(T, log2W);
        }
		//printf("Residual 11 dd\n"); 
        for (int j = 0; j < w; j++) {
            Residual[i][j] = Round2(T[j], rowShift);
			//printf("%d ",Residual[i][j]);
        }
		
    }
	//printf("\n");
	//printf("Residual 22\n");
    for (int i = 0; i < h; i++) {
		
        for (int j = 0; j < w; j++) {
            Residual[i][j] = Min(Max(-((1 << (colClampRange - 1))), Residual[i][j]), ((1 << (colClampRange - 1)) - 1));
		}
		
    }
	//printf("\n");
	//printf("Residual 33\n");
	int16_t T1[h];
    for (int j = 0; j < w; j++) {
        
        for (int i = 0; i < h; i++) {
            T1[i] = Residual[i][j];
        }

        if (b_data->Lossless) {
            inverseWalshHadamardTransform(T1, 0);
        } else if (b_data->PlaneTxType == DCT_DCT || b_data->PlaneTxType == DCT_ADST || b_data->PlaneTxType == DCT_FLIPADST || b_data->PlaneTxType == V_DCT) {
            inverseDCT(T1, log2H, colClampRange);
        } else if (b_data->PlaneTxType == ADST_DCT || b_data->PlaneTxType == ADST_ADST || b_data->PlaneTxType == FLIPADST_DCT ||
                   b_data->PlaneTxType == FLIPADST_FLIPADST || b_data->PlaneTxType == ADST_FLIPADST || b_data->PlaneTxType == FLIPADST_ADST ||
                   b_data->PlaneTxType == V_ADST || b_data->PlaneTxType == V_FLIPADST) {
            inverseADST(T1, log2H, colClampRange);
        } else {
            inverseIdentityTransform(T1, log2H);
        }
		
        for (int i = 0; i < h; i++) {
            Residual[i][j] = Round2(T1[i], colShift);
			//printf("%d ",Residual[i][j]);

        }
		
    }
	//printf("\n");
}
//7.14
void decode::loopFilter(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	for (int  plane = 0; plane < seqHdr->color_config.NumPlanes; plane++ ) {
		if ( plane == 0 || frameHdr->loop_filter_params.loop_filter_level[ 1 + plane ] ) {
			for (int pass = 0; pass < 2; pass++ ) {
				int rowStep = ( plane == 0 ) ? 1 : ( 1 << seqHdr->color_config.subsampling_y );
				int colStep = ( plane == 0 ) ? 1 : ( 1 << seqHdr->color_config.subsampling_x );
				for (int row = 0; row < frameHdr->MiRows; row += rowStep )
					for (int col = 0; col < frameHdr->MiCols; col += colStep )
						edgeLoopFilter( plane, pass, row, col,av1Ctx);
			}
		}
	}
}
void decode::edgeLoopFilter(int plane, int pass, int row, int col,AV1DecodeContext *av1Ctx) {
   	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int subX, subY, dx, dy, x, y, onScreen, xP, yP, prevRow, prevCol;
    int isBlockEdge, isTxEdge, applyFilter;


    // Derive subX and subY
    if (plane == 0) {
        subX = subY = 0;
    } else {
        subX = seqHdr->color_config.subsampling_x;
        subY = seqHdr->color_config.subsampling_y;
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
    if (x >= frameHdr->si.FrameWidth || y >= frameHdr->si.FrameHeight || (pass == 0 && x == 0) || (pass == 1 && y == 0)) {
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
    int MiSize = av1Ctx->MiSizes[row][col];
    int txSz = av1Ctx->LoopfilterTxSizes[plane][row >> subY][col >> subX];
    int planeSize = get_plane_residual_size(MiSize, plane,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y);
    int skip = av1Ctx->Skips[row][col];
    int isIntra = av1Ctx->RefFrames[row][col][0] <= INTRA_FRAME;
    int prevTxSz = av1Ctx->LoopfilterTxSizes[plane][prevRow >> subY][prevCol >> subX];

    // Derive isBlockEdge
    isBlockEdge = 0;
    if ((pass == 0 && xP % (Block_Width[planeSize]) == 0) || (pass == 1 && yP % (Block_Height[planeSize]) == 0)) {
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
	int filterSize = filterSizeProcess(txSz,prevTxSz,pass,plane);

	int lvl,limit,blimit,thresh;
	adaptiveFilterStrength(row,col,plane,pass,&lvl,&limit,&blimit,&thresh,av1Ctx);

	if(lvl == 0){
		adaptiveFilterStrength(prevRow,prevCol,plane,pass,&lvl,&limit,&blimit,&thresh,av1Ctx);
	}

	for(int i = 0 ; i < MI_SIZE ; i++){
		if(applyFilter == 1 && lvl > 0){
			sampleFiltering(xP + dy * i,yP + dx * i,plane, limit, blimit, thresh, dx, dy,filterSize,av1Ctx);
		}
	}


}
//7.14.3
//The purpose of this process is to reduce the width of the chroma filters and to ensure that different boundaries can be
//filtered in parallel.
int decode::filterSizeProcess(int txSz, int prevTxSz, int pass, int plane) {
    int baseSize;

    // Derive baseSize based on pass
    if (pass == 0) {
        baseSize = Min(Tx_Width[prevTxSz], Tx_Width[txSz]);
    } else {
        baseSize = Min(Tx_Height[prevTxSz], Tx_Height[txSz]);
    }

    // Derive filterSize based on plane
    int filterSize;
    if (plane == 0) {
        filterSize = Min(16, baseSize);
    } else {
        filterSize = Min(8, baseSize);
    }

    return filterSize;
}
//7.14.4
void decode::adaptiveFilterStrength(int row, int col, int plane, int pass, int* lvl, int* limit, int* blimit, int* thresh,
							AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

    int segment = av1Ctx->SegmentIds[row][col];
    int ref = av1Ctx->RefFrames[row][col][0];
    int mode = av1Ctx->YModes[row][col];
    int modeType;

    if (mode >= NEARESTMV && mode != GLOBALMV && mode != GLOBAL_GLOBALMV) {
        modeType = 1;
    } else {
        modeType = 0;
    }

    int deltaLF;
    if (frameHdr->delta_lf_params.delta_lf_multi == 0) {
        deltaLF = av1Ctx->DeltaLFs[row][col][0];
    } else {
        deltaLF = av1Ctx->DeltaLFs[row][col][plane == 0 ? pass : (plane + 1)];
    }

    // Invoke the adaptive filter strength selection process
    *lvl = adaptiveFilterStrengthSelection(segment, ref, modeType, deltaLF, plane, pass,av1Ctx);

    // Derive shift
    int shift;
    if (frameHdr->loop_filter_params.loop_filter_sharpness > 4) {
        shift = 2;
    } else if (frameHdr->loop_filter_params.loop_filter_sharpness > 0) {
        shift = 1;
    } else {
        shift = 0;
    }

    // Derive limit
    if (frameHdr->loop_filter_params.loop_filter_sharpness > 0) {
        *limit = Clip3(1, 9 - frameHdr->loop_filter_params.loop_filter_sharpness, (*lvl)  >> shift);
    } else {
        *limit = Max(1, (*lvl) >> shift);
    }

    // Derive blimit and thresh
    *blimit = 2 * ((*lvl)  + 2) + *limit;
    *thresh = (*lvl)  >> 4;
}
//7.14.5
int decode::adaptiveFilterStrengthSelection(int segment, int ref, int modeType, int deltaLF, int plane, int pass,
									AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    // 初始化变量
    int i = (plane == 0) ? pass : (plane + 1);
    int baseFilterLevel = Clip3(0, MAX_LOOP_FILTER, deltaLF + frameHdr->loop_filter_params.loop_filter_level[i]);
    int lvlSeg = baseFilterLevel;
    int feature = SEG_LVL_ALT_LF_Y_V + i;

    // 检查segment特征是否激活
    if (seg_instance->seg_feature_active_idx(segment, feature,frameHdr) == 1) {
        lvlSeg += frameHdr->segmentation_params.FeatureData[segment][feature];
        lvlSeg = Clip3(0, MAX_LOOP_FILTER, lvlSeg);
    }

    // 如果loop_filter_delta_enabled为1，应用delta值
    if (frameHdr->loop_filter_params.loop_filter_delta_enabled == 1) {
        int nShift = lvlSeg >> 5;
        
        if (ref == INTRA_FRAME) {
            lvlSeg += (frameHdr->loop_filter_params.loop_filter_ref_deltas[INTRA_FRAME] << nShift);
        } else {
            lvlSeg += (frameHdr->loop_filter_params.loop_filter_ref_deltas[ref] << nShift) +
			(frameHdr->loop_filter_params.loop_filter_mode_deltas[modeType] << nShift);
        }
        
        lvlSeg = Clip3(0, MAX_LOOP_FILTER, lvlSeg);
    }

    return lvlSeg;
}
//7.14.6
void decode::sampleFiltering(int x,int  y,int  plane, int limit,int  blimit,int  thresh,
							int  dx,int  dy,int  filterSize,AV1DecodeContext *av1Ctx){

	// 调用Filter Mask生成过程
	int hevMask, filterMask, flatMask, flatMask2;
	filterMaskProcess(x, y, plane, limit, blimit, thresh, dx, dy, filterSize, 
						&hevMask, &filterMask, &flatMask, &flatMask2,av1Ctx);

	// 根据Filter Mask和Filter Size选择适当的Filter过程
	if (filterMask == 0) {
		// 不需要滤波
	} else if (filterSize == 4 || flatMask == 0) {
		// 使用狭窄滤波过程
		narrowFilter(x, y, plane, dx, dy, hevMask,av1Ctx);
	} else if (filterSize == 8 || flatMask2 == 0) {
		// 使用宽滤波过程，log2Size为3
		wideFilter(x, y, plane, dx, dy, 3,av1Ctx);
	} else {
		// 使用宽滤波过程，log2Size为4
		wideFilter(x, y, plane, dx, dy, 4,av1Ctx);
	}
}
////7.14.6.2
void decode::filterMaskProcess(int x,int y,int plane,int limit,int blimit,int thresh,int dx,int dy,int filterSize,
						int *hevMask,int *filterMask,int *flatMask ,int *flatMask2,
						AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int q0 = av1Ctx->currentFrame->CurrFrame[ plane ][ y ][ x ];
	int q1 = av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy ][ x + dx ];
	int q2 = av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy * 2 ][ x + dx * 2 ];
	int q3 = av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy * 3 ][ x + dx * 3 ];
	int q4 = av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy * 4 ][ x + dx * 4 ];
	int q5 = av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy * 5 ][ x + dx * 5 ];
	int q6 = av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy * 6 ][ x + dx * 6 ];
	int p0 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy ][ x - dx ];
	int p1 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 2 ][ x - dx * 2 ];
	int p2 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 3 ][ x - dx * 3 ];
	int p3 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 4 ][ x - dx * 4 ];
	int p4 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 5 ][ x - dx * 5 ];
	int p5 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 6 ][ x - dx * 6 ];
	int p6 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 7 ][ x - dx * 7 ];
	// hev : means |high| edge| variance|
	*hevMask = 0 ;
	int threshBd = thresh << (seqHdr->color_config.BitDepth - 8);
	*hevMask |= (Abs( p1 - p0 ) > threshBd);
	*hevMask |= (Abs( q1 - q0 ) > threshBd);

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
//的差异是否小于由limit和blimit给出的限制。它用于确定是否应该执行某种过滤，
	int limitBd = limit << (seqHdr->color_config.BitDepth - 8);
	int blimitBd = blimit << (seqHdr->color_config.BitDepth - 8);
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

	*filterMask = (mask == 0);

	//只有当filterSize >= 8时才需要flatMask的值。
	//它测量来自指定边界两侧的样本是否在一个平坦区域内。
	//即这些样本与边界上的样本是否最多存在(1 << (BitDepth - 8))的差异。计算方法如下:
	int thresholdBd = 1 << (seqHdr->color_config.BitDepth - 8);
	if ( filterSize >= 8 ) {
		mask = 0;
		mask |= (Abs( p1 - p0 ) > thresholdBd);
		mask |= (Abs( q1 - q0 ) > thresholdBd);
		mask |= (Abs( p2 - p0 ) > thresholdBd);
		mask |= (Abs( q2 - q0 ) > thresholdBd);
		if ( filterLen >= 8 ) {
			mask |= (Abs( p3 - p0 ) > thresholdBd);
			mask |= (Abs( q3 - q0 ) > thresholdBd);
		}
		*flatMask = (mask == 0);
	}
	//假设前面四个点(0,1,2,3)都在同一个平坦区域， flatMask2 代表后面3个点也在同一个平坦区域
	// 如果 flatMask & flatMask2 == 0 ,则所有点都在一个平坦区域
	thresholdBd = 1 << (seqHdr->color_config.BitDepth - 8);
	if ( filterSize >= 16 ) {
		mask = 0;
		mask |= (Abs( p6 - p0 ) > thresholdBd);
		mask |= (Abs( q6 - q0 ) > thresholdBd);
		mask |= (Abs( p5 - p0 ) > thresholdBd);
		mask |= (Abs( q5 - q0 ) > thresholdBd);
		mask |= (Abs( p4 - p0 ) > thresholdBd);
		mask |= (Abs( q4 - q0 ) > thresholdBd);
		*flatMask2 = (mask == 0);
	}

}
//This process modifies up to two samples on each side of the 
//specified boundary depending on the value of hevMask 
void decode::narrowFilter(int x,int y,int plane,int dx ,int dy,int hevMask,AV1DecodeContext *av1Ctx){
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int q0 = av1Ctx->currentFrame->CurrFrame[ plane ][ y ][ x ];
	int q1 = av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy ][ x + dx ];
	int p0 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy ][ x - dx ];
	int p1 = av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 2 ][ x - dx * 2 ];
	int ps1 = p1 - (0x80 << (seqHdr->color_config.BitDepth - 8));
	int ps0 = p0 - (0x80 << (seqHdr->color_config.BitDepth - 8));
	int qs0 = q0 - (0x80 << (seqHdr->color_config.BitDepth - 8));
	int qs1 = q1 - (0x80 << (seqHdr->color_config.BitDepth - 8));
	int filter = hevMask ? filter4_clamp( ps1 - qs1,seqHdr->color_config.BitDepth ) : 0;
	filter = filter4_clamp( filter + 3 * (qs0 - ps0) ,seqHdr->color_config.BitDepth);
	int filter1 = filter4_clamp( filter + 4  ,seqHdr->color_config.BitDepth) >> 3;
	int filter2 = filter4_clamp( filter + 3  ,seqHdr->color_config.BitDepth) >> 3;
	int oq0 = filter4_clamp( qs0 - filter1 ,seqHdr->color_config.BitDepth ) + (0x80 << (seqHdr->color_config.BitDepth - 8));
	int op0 = filter4_clamp( ps0 + filter2  ,seqHdr->color_config.BitDepth) + (0x80 << (seqHdr->color_config. BitDepth - 8));
	av1Ctx->currentFrame->CurrFrame[ plane ][ y ][ x ] = oq0;
	av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy ][ x - dx ] = op0;
	if ( !hevMask ) {
		filter = Round2( filter1, 1 );
		int oq1 = filter4_clamp( qs1 - filter,seqHdr->color_config.BitDepth ) + (0x80 << (seqHdr->color_config.BitDepth - 8));
		int op1 = filter4_clamp( ps1 + filter,seqHdr->color_config.BitDepth ) + (0x80 << (seqHdr->color_config.BitDepth - 8));
		av1Ctx->currentFrame->CurrFrame[ plane ][ y + dy ][ x + dx ] = oq1;
		av1Ctx->currentFrame->CurrFrame[ plane ][ y - dy * 2 ][ x - dx * 2 ] = op1;
	}

}
void decode::wideFilter(int x,int y,int plane,int dx ,int dy,int log2Size,AV1DecodeContext *av1Ctx){
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
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
	int F[2 * n];
	for (int i = -n; i < n; i++) {
		int t = 0;
		for (int j = -n; j <= n; j++) {
			int p = Clip3(-(n + 1), n, i + j);
			int tap = (Abs(j) <= n2) ? 2 : 1;
			t += av1Ctx->currentFrame->CurrFrame[plane][y + p * dy][x + p * dx] * tap;
		}
		
		// 将滤波结果保存到数组 F
		F[i + n] = Round2(t, log2Size);
	}

	// 应用滤波结果到当前帧
	for (int i = -n; i < n; i++) {
		av1Ctx->currentFrame->CurrFrame[plane][y + i * dy][x + i * dx] = F[i + n];
	}
}
//7.15
void decode::cdef(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int step4 = Num_4x4_Blocks_Wide[ BLOCK_8X8 ];
	int cdefSize4 = Num_4x4_Blocks_Wide[ BLOCK_64X64 ];
	int   cdefMask4 = ~(cdefSize4 - 1);
	for (int r = 0; r < frameHdr->MiRows; r += step4 ) {
		for (int c = 0; c < frameHdr->MiCols; c += step4 ) {
			int baseR = r & cdefMask4;
			int baseC = c & cdefMask4;
			int idx = av1Ctx->currentFrame->cdef_idx[ baseR ][ baseC ];
			cdefBlock(r, c, idx,av1Ctx);
		}
	}
}
void decode::cdefBlock(int r, int c, int idx,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int startY = r * MI_SIZE;
    int endY = startY + MI_SIZE * 2;
    int startX = c * MI_SIZE;
    int endX = startX + MI_SIZE * 2;

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            av1Ctx->currentFrame->CdefFrame[0][y][x] = av1Ctx->currentFrame->CurrFrame[0][y][x];
        }
    }

    if (seqHdr->color_config.NumPlanes > 1) {
        startY >>= seqHdr->color_config.subsampling_y;
        endY >>= seqHdr->color_config.subsampling_y;
        startX >>= seqHdr->color_config.subsampling_x;
        endX >>= seqHdr->color_config.subsampling_x;

        for (int y = startY; y < endY; y++) {
            for (int x = startX; x < endX; x++) {
                av1Ctx->currentFrame->CdefFrame[1][y][x] = av1Ctx->currentFrame->CurrFrame[1][y][x];
                av1Ctx->currentFrame->CdefFrame[2][y][x] = av1Ctx->currentFrame->CurrFrame[2][y][x];
            }
        }
    }

    if (idx == -1) {
        return;
    }

    int coeffShift = seqHdr->color_config.BitDepth - 8;
    int skip = (av1Ctx->Skips[r][c] && av1Ctx->Skips[r + 1][c] && 
				av1Ctx->Skips[r][c + 1] && av1Ctx->Skips[r + 1][c + 1]);

    if (skip == 0) {
        int yDir, var;
        cdefDirectionProcess(r, c, &yDir, &var,av1Ctx);
        int priStr = frameHdr->cdef_params.cdef_y_pri_strength[idx] << coeffShift;
        int secStr = frameHdr->cdef_params.cdef_y_sec_strength[idx] << coeffShift;
        int dir = (priStr == 0) ? 0 : yDir;
		printf("var %d\n",var);
        int varStr = (var >> 6) ? Min(FloorLog2(var >> 6), 12) : 0;
        priStr = (var ? (priStr * (4 + varStr) + 8) >> 4 : 0);
        int damping = frameHdr->cdef_params.CdefDamping + coeffShift;

        cdefFilter(0, r, c, priStr, secStr, damping, dir,av1Ctx);

        if (seqHdr->color_config.NumPlanes == 1) {
            return;
        }

        priStr = frameHdr->cdef_params.cdef_uv_pri_strength[idx] << coeffShift;
        secStr = frameHdr->cdef_params.cdef_uv_sec_strength[idx] << coeffShift;
        dir = (priStr == 0) ? 0 : Cdef_Uv_Dir[seqHdr->color_config.subsampling_x][seqHdr->color_config.subsampling_y][yDir];
        damping = frameHdr->cdef_params.CdefDamping + coeffShift - 1;

        cdefFilter(1, r, c, priStr, secStr, damping, dir,av1Ctx);
        cdefFilter(2, r, c, priStr, secStr, damping, dir,av1Ctx);
    }
}
//7.15.2
void decode::cdefDirectionProcess(int r, int c, int *yDir, int *var,
								 AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int64_t cost[8];
    int partial[8][15];
    int64_t bestCost = 0;
    *yDir = 0;
    int x0 = c << MI_SIZE_LOG2;
    int y0 = r << MI_SIZE_LOG2;

    for (int i = 0; i < 8; i++) {
        cost[i] = 0;
        for (int j = 0; j < 15; j++) {
            partial[i][j] = 0;
        }
    }
	int x;
	////printf(" x0 %d y0 %d\n",x0,y0);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            x = (av1Ctx->currentFrame->CurrFrame[0][y0 + i][x0 + j] >> (seqHdr->color_config.BitDepth - 8)) - 128;
			////printf(" x %d src %d",x,av1Ctx->currentFrame->CurrFrame[0][y0 + i][x0 + j]);
			partial[0][i + j] += x;
            partial[1][i + j / 2] += x;
            partial[2][i] += x;
            partial[3][3 + i - j / 2] += x;
            partial[4][7 + i - j] += x;
            partial[5][3 - i / 2 + j] += x;
            partial[6][j] += x;
            partial[7][i / 2 + j] += x;
        }
    }
    for (int i = 0; i < 8; i++) {
        cost[2] += partial[2][i] * partial[2][i];
        cost[6] += partial[6][i] * partial[6][i];
    }

    cost[2] *= Div_Table[8];
    cost[6] *= Div_Table[8];

    for (int i = 0; i < 7; i++) {
        cost[0] += (partial[0][i] * partial[0][i] + partial[0][14 - i] * partial[0][14 - i]) * Div_Table[i + 1];
        cost[4] += (partial[4][i] * partial[4][i] + partial[4][14 - i] * partial[4][14 - i]) * Div_Table[i + 1];
    }

    cost[0] += partial[0][7] * partial[0][7] * Div_Table[8];
    cost[4] += partial[4][7] * partial[4][7] * Div_Table[8];

    for (int i = 1; i < 8; i += 2) {
        for (int j = 0; j < 4 + 1; j++) {
            cost[i] += partial[i][3 + j] * partial[i][3 + j];
        }
        cost[i] *= Div_Table[8];

        for (int j = 0; j < 4 - 1; j++) {
            cost[i] += (partial[i][j] * partial[i][j] + partial[i][10 - j] * partial[i][10 - j]) * Div_Table[2 * j + 2];
        }
    }

    for (int i = 0; i < 8; i++) {
        if (cost[i] > bestCost) {
            bestCost = cost[i];
            *yDir = i;
        }
    }
	////printf("bestCost %d yDir %d cost %d %d %d %d %d %d %d %d\n",bestCost,*yDir,cost[0],cost[1],cost[2],cost[3],cost[4],cost[5],cost[6],cost[7]);
    *var = (bestCost - cost[(*yDir + 4) & 7]) >> 10;
}
//7.15.3
void decode::cdefFilter(int plane, int r, int c, int priStr, int secStr, int damping, int dir,
						AV1DecodeContext *av1Ctx ){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    int subX = (plane > 0) ? seqHdr->color_config.subsampling_x : 0;
    int subY = (plane > 0) ? seqHdr->color_config.subsampling_y : 0;
    int x0 = (c * MI_SIZE) >> subX;
    int y0 = (r * MI_SIZE) >> subY;
    int w = 8 >> subX;
    int h = 8 >> subY;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int sum = 0;
            int x = av1Ctx->currentFrame->CurrFrame[plane][y0 + i][x0 + j];
            int max = x;
            int min = x;

            for (int k = 0; k < 2; k++) {
                for (int sign = -1; sign <= 1; sign += 2) {
					int CdefAvailable;
                    int p = cdef_get_at(plane, x0, y0, i, j, dir, k, sign, subX, subY,
								&CdefAvailable,av1Ctx->currentFrame->CurrFrame,av1Ctx);

                    if (CdefAvailable) {
                        sum += Cdef_Pri_Taps[(priStr >> (seqHdr->color_config.BitDepth - 8)) & 1][k] * constrain(p - x, priStr, damping);
                        max = Max(p, max);
                        min = Min(p, min);
                    }

                    for (int dirOff = -2; dirOff <= 2; dirOff += 4) {
                        int s = cdef_get_at(plane, x0, y0, i, j, (dir + dirOff) & 7, k, sign, subX, subY,
						&CdefAvailable,av1Ctx->currentFrame->CurrFrame,av1Ctx);

                        if (CdefAvailable) {
                            sum += Cdef_Sec_Taps[(priStr >> (seqHdr->color_config.BitDepth - 8)) & 1][k] * constrain(s - x, secStr, damping);
                            max = Max(s, max);
                            min = Min(s, min);
                        }
                    }
                }
            }

            av1Ctx->currentFrame->CurrFrame[plane][y0 + i][x0 + j] = Clip3(min, max, x + ((8 + sum - (sum < 0)) >> 4));
        }
    }
}



int decode::cdef_get_at(int plane,int x0,int y0,int i, int j,int dir,int k,int sign,int subX,int subY,
						int * CdefAvailable,uint16_t ***CurrFrame,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int y = y0 + i + sign * Cdef_Directions[dir][k][0];
	int x = x0 + j + sign * Cdef_Directions[dir][k][1];
	int candidateR = (y << subY) >> MI_SIZE_LOG2;
	int candidateC = (x << subX) >> MI_SIZE_LOG2;
	if ( is_inside_filter_region( candidateR, candidateC,frameHdr->MiCols, frameHdr->MiRows) ) {
		*CdefAvailable = 1;
		return CurrFrame[ plane ][ y ][ x ];
	} else {
		*CdefAvailable = 0;
		return 0;
	}
}
//7.16
void decode::upscalingProcess(uint16_t ***inputFrame,uint16_t ***outputFrame,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++) {
        int subX, subY;

        if (plane > 0) {
            subX = seqHdr->color_config.subsampling_x;
            subY = seqHdr->color_config.subsampling_y;
        } else {
            subX = 0;
            subY = 0;
        }

        int downscaledPlaneW = Round2(frameHdr->si.FrameWidth, subX);
        int upscaledPlaneW = Round2(frameHdr->si.UpscaledWidth, subX);
        int planeH = Round2(frameHdr->si.FrameHeight, subY);
        int stepX = ((downscaledPlaneW << SUPERRES_SCALE_BITS) + (upscaledPlaneW / 2)) / upscaledPlaneW;
        int err = (upscaledPlaneW * stepX) - (downscaledPlaneW << SUPERRES_SCALE_BITS);
        int initialSubpelX = (-((upscaledPlaneW - downscaledPlaneW) << (SUPERRES_SCALE_BITS - 1)) + upscaledPlaneW / 2) / upscaledPlaneW + (1 << (SUPERRES_EXTRA_BITS - 1)) - err / 2;
        initialSubpelX &= SUPERRES_SCALE_MASK;
        int miW = frameHdr->MiCols >> subX;
        int minX = 0;
        int maxX = miW * 4 - 1;

        for (int y = 0; y < planeH; y++) {
            for (int x = 0; x < upscaledPlaneW; x++) {
                int srcX = -(1 << SUPERRES_SCALE_BITS) + initialSubpelX + x * stepX;
                int srcXPx = (srcX >> SUPERRES_SCALE_BITS);
                int srcXSubpel = (srcX & SUPERRES_SCALE_MASK) >> SUPERRES_EXTRA_BITS;
                int sum = 0;

                for (int k = 0; k < SUPERRES_FILTER_TAPS; k++) {
                    int sampleX = Clip1(srcXPx + k - SUPERRES_FILTER_OFFSET,seqHdr->color_config.BitDepth);
                    int px = inputFrame[plane][y][sampleX];
                    sum += px * Upscale_Filter[srcXSubpel][k];
                }

                outputFrame[plane][y][x] = Clip1(sum >> 8,seqHdr->color_config.BitDepth);
            }
        }
    }
}
//7.17
void decode::loopRestoration(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	//memcpy(av1Ctx->currentFrame->lrCtx->LrFrame,av1Ctx->currentFrame->UpscaledCdefFrame,size);
	for(int i = 0; i < 3 ; i ++){
		////printf("FrameHeight %d UpscaledWidth %d \n",frameHdr->si.FrameHeight,frameHdr->si.UpscaledWidth);
		for(int j = 0 ; j < frameHdr->si.FrameHeight; j++){
			for(int k = 0 ; k < frameHdr->si.UpscaledWidth; k++){
				av1Ctx->currentFrame->lrCtx->LrFrame[i][j][k] = av1Ctx->currentFrame->UpscaledCdefFrame[i][j][k] ;
			}
			//memcpy(av1Ctx->currentFrame->lrCtx->LrFrame[i][j],
			//	av1Ctx->currentFrame->UpscaledCdefFrame[i][j],frameHdr->si.UpscaledWidth * sizeof(int));
		}
	}

	// 如果不需要循环恢复，直接返回
	if (frameHdr->lr_params.UsesLr == 0) {
		return;
	}

	// 循环遍历图像块 以 4*4块为单位 
	for (int y = 0; y < frameHdr->si.FrameHeight; y += MI_SIZE) {
		for (int x = 0; x < frameHdr->si.UpscaledWidth; x += MI_SIZE) {
			for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++) {
				// 检查是否需要进行循环恢复
				if (frameHdr->lr_params.FrameRestorationType[plane] != RESTORE_NONE) {
					int row = y >> MI_SIZE_LOG2;
					int col = x >> MI_SIZE_LOG2;
					// 调用循环恢复块过程
					loopRestoreBlock(plane, row, col,av1Ctx);
				}
			}
		}
	}
}
//7.17.1
void decode::loopRestoreBlock(int plane,int row ,int col,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int lumaY = row * MI_SIZE;

	int stripeNum = (lumaY + 8) / 64;

	int subX, subY;
	if (plane == 0) {
		subX = 0;
		subY = 0;
	} else {
		subX = seqHdr->color_config.subsampling_x;
		subY = seqHdr->color_config.subsampling_y;
	}

	int StripeStartY = (-8 + stripeNum * 64) >> subY;
	int StripeEndY = StripeStartY + (64 >> subY) - 1;


	int unitSize = frameHdr->lr_params.LoopRestorationSize[plane];
	int unitRows = count_units_in_frame(unitSize, Round2(frameHdr->si.FrameHeight, subY));
	int unitCols = count_units_in_frame(unitSize, Round2(frameHdr->si.UpscaledWidth, subX));


	int unitRow = Min(unitRows - 1, ((row * MI_SIZE + 8) >> subY) / unitSize);
	int unitCol = Min(unitCols - 1, (col * MI_SIZE >> subX) / unitSize);

	int PlaneEndX = Round2(frameHdr->si.UpscaledWidth, subX) - 1;
	int PlaneEndY = Round2(frameHdr->si.FrameHeight, subY) - 1;


	int x = col * MI_SIZE >> subX;
	int y = row * MI_SIZE >> subY;
	int w = Min(MI_SIZE >> subX, PlaneEndX - x + 1);
	int h = Min(MI_SIZE >> subY, PlaneEndY - y + 1);

	int rType = av1Ctx->currentFrame->lrCtx->LrType[plane][unitRow][unitCol];

	// 根据rType选择滤波器
	if (rType == RESTORE_WIENER) {
		wienerFilter(plane, unitRow, unitCol, x, y, w, h,av1Ctx);
	} else if (rType == RESTORE_SGRPROJ) {
		selfGuidedFilter(plane, unitRow, unitCol, x, y, w, h,av1Ctx);
	} else {
		// 不应用滤波
	}
}
//7.17.2
void decode::selfGuidedFilter(int plane,int unitRow,int unitCol, int x,int y,int w,int h,
							AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int set = av1Ctx->currentFrame->lrCtx->LrSgrSet[plane][unitRow][unitCol];
	int pass = 0;
	//int flt0[h][w];
	int **flt0 =  new int *[h];
	for(int i = 0 ; i < h ; i++){
		flt0[i] = new int[w];
	}
	boxFilter(plane, x, y, w, h, set, pass,flt0,av1Ctx);
	pass = 1;
	//int flt1[h][w];
	int **flt1 =  new int *[h];
	for(int i = 0 ; i < h ; i++){
		flt1[i] = new int[w];
	}
	boxFilter(plane, x, y, w, h, set, pass,flt1,av1Ctx);

	// 计算权重和参数
	int w0 = av1Ctx->currentFrame->lrCtx->LrSgrXqd[plane][unitRow][unitCol][0];
	int w1 = av1Ctx->currentFrame->lrCtx->LrSgrXqd[plane][unitRow][unitCol][1];
	int w2 = (1 << SGRPROJ_PRJ_BITS) - w0 - w1;
	int r0 = Sgr_Params[set][0];
	int r1 = Sgr_Params[set][2];

	// 应用恢复过程
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int u = av1Ctx->currentFrame->UpscaledCdefFrame[plane][y + i][x + j] << SGRPROJ_RST_BITS;
			int v = w1 * u;
			
			if (r0 != 0) {
				v += w0 * flt0[i][j];
			} else {
				v += w0 * u;
			}
			
			if (r1 != 0) {
				v += w2 * flt1[i][j];
			} else {
				v += w2 * u;
			}
			
			int s = Round2(v, SGRPROJ_RST_BITS + SGRPROJ_PRJ_BITS);
			av1Ctx->currentFrame->lrCtx->LrFrame[plane][y + i][x + j] = Clip1(s,seqHdr->color_config.BitDepth);
		}
	}
	for(int i = 0 ; i < h ; i ++){
		delete [] flt0[i];
		delete [] flt1[i];
	}
	delete flt0;
	delete flt1;
}
//7.17.3
void decode::boxFilter(int plane,int x,int y,int w,int h,int set ,int pass,int **F,
				AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

	// 计算r和eps
	int r = Sgr_Params[set][pass * 2];
	if (r == 0) {
		return; // 立即退出
	}
	int eps = Sgr_Params[set][pass * 2 + 1];

	// 准备A和B数组
	int n = (2 * r + 1) * (2 * r + 1);
	int n2e = n * n * eps;
	int s = (((1 << SGRPROJ_MTABLE_BITS) + n2e / 2) / n2e);
	//int[][] A = new int[h + 2][w + 2];
	//int[][] B = new int[h + 2][w + 2];
	int A[h + 2][w + 2];
	int B[h + 2][w + 2];
	for (int i = -1; i < h + 1; i++) {
		for (int j = -1; j < w + 1; j++) {
			int a = 0;
			int b = 0;
			for (int dy = -r; dy <= r; dy++) {
				for (int dx = -r; dx <= r; dx++) {
					int c = getSourceSample(plane, x + j + dx, y + i + dy,av1Ctx);
					a += c * c;
					b += c;
				}
			}
			a = Round2(a, 2 * (seqHdr->color_config.BitDepth - 8));
			int d = Round2(b, seqHdr->color_config.BitDepth - 8);
			int p = Max(0, a * n - d * d);
			int z = Round2(p * s, SGRPROJ_MTABLE_BITS);
			int a2 = 0;
			if (z >= 255) {
				a2 = 256;
			} else if (z == 0) {
				a2 = 1;
			} else {
				a2 = ((z << SGRPROJ_SGR_BITS) + (z / 2)) / (z + 1);
			}
			int oneOverN = ((1 << SGRPROJ_RECIP_BITS) + (n / 2)) / n;
			int b2 = ((1 << SGRPROJ_SGR_BITS) - a2) * b * oneOverN;
			A[i + 1][j + 1] = a2;
			B[i + 1][j + 1] = Round2(b2, SGRPROJ_RECIP_BITS);
		}
	}

	for (int i = 0; i < h; i++) {
		int shift = 5;
		if (pass == 0 && (i & 1) != 0) {
			shift = 4;
		}
		for (int j = 0; j < w; j++) {
			int a = 0;
			int b = 0;
			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					int weight = (pass == 0) ? ((i + dy) & 1) ? ((dx == 0) ? 6 : 5) : 0 : ((dx == 0 || dy == 0) ? 4 : 3);
					a += weight * A[i + dy + 1][j + dx + 1];
					b += weight * B[i + dy + 1][j + dx + 1];
				}
			}
			int v = a * av1Ctx->currentFrame->UpscaledCdefFrame[plane][y + i][x + j] + b;
			F[i][j] = Round2(v, SGRPROJ_SGR_BITS + shift - SGRPROJ_RST_BITS);
		}
	}
}
//7.17.4
void decode::wienerFilter(int plane ,int unitRow,int unitCol,int x,int y,int w,int h,
							AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int isCompound = 0;
	roundingVariablesDerivation(isCompound,av1Ctx);
	

	int vfilter[7];
	int hfilter[7];
	wienerCoefficient(av1Ctx->currentFrame->lrCtx->LrWiener[plane][unitRow][unitCol][0],vfilter);
	wienerCoefficient(av1Ctx->currentFrame->lrCtx->LrWiener[plane][unitRow][unitCol][1],hfilter);


	int intermediate[h + 6][ w ];
	int offset = (1 << (seqHdr->color_config.BitDepth + FILTER_BITS - av1Ctx->InterRound0 - 1));
	int limit = (1 << (seqHdr->color_config.BitDepth + 1 + FILTER_BITS - av1Ctx->InterRound0)) - 1;

	for (int r = 0; r < h + 6; r++) {
		for (int c = 0; c < w; c++) {
			int s = 0;
			for (int t = 0; t < 7; t++) {
				s += hfilter[t] * getSourceSample(plane, x + c + t - 3, y + r - 3,av1Ctx);
			}
			int v = Round2(s, av1Ctx->InterRound0);
			intermediate[r][c] = Clip3(-offset, limit - offset, v);
		}
	}

	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {
			int s = 0;
			for (int t = 0; t < 7; t++) {
				s += vfilter[t] * intermediate[r + t][c];
			}
			int v = Round2(s, av1Ctx->InterRound1);
			av1Ctx->currentFrame->lrCtx->LrFrame[plane][y + r][x + c] = Clip1(v,seqHdr->color_config.BitDepth);
		}
	}
}
//7.17.5
void decode::wienerCoefficient(uint16_t coeff[3],int filter[7]){
	filter[ 3 ] = 128;
	for (int i = 0; i < 3; i++ ) {
		int c = coeff[ i ];
		filter[ i ] = c;
		filter[ 6 - i ] = c;
		filter[ 3 ] -= 2 * c;
	}

}
//7.17.6
int decode::getSourceSample(int plane ,int x,int y, AV1DecodeContext *av1Ctx){
	// 确保x和y在合法范围内
	x = Min(av1Ctx->currentFrame->lrCtx->PlaneEndX, x);
	x = Max(0, x);
	y = Min(av1Ctx->currentFrame->lrCtx->PlaneEndY, y);
	y = Max(0, y);

	// 根据y的位置确定样本来源
	if (y < av1Ctx->currentFrame->lrCtx->StripeStartY) {
		y = Max(av1Ctx->currentFrame->lrCtx->StripeStartY - 2, y);
		return av1Ctx->currentFrame->UpscaledCurrFrame[plane][y][x];
	} else if (y > av1Ctx->currentFrame->lrCtx->StripeEndY) {
		y = Min(av1Ctx->currentFrame->lrCtx->StripeEndY + 2, y);
		return av1Ctx->currentFrame->UpscaledCurrFrame[plane][y][x];
	} else {
		return av1Ctx->currentFrame->UpscaledCdefFrame[plane][y][x];
	}
}
//7.18.2
void decode::output(AV1DecodeContext *av1Ctx){
	int w,h,subX,subY,bitDepth;
	intermediateOutputPreparation(&w,&h,&subX,&subY,&bitDepth,av1Ctx);
	filmGrainSynthesis(w,h,subX,subY,av1Ctx);

}
void decode::intermediateOutputPreparation(int *w,int *h,int *subX,int *subY,int *bitDepth,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	if (frameHdr->show_existing_frame == 1) {
		// Copy from a previously decoded frame
		*w = (*av1Ctx->RefUpscaledWidth)[frameHdr->frame_to_show_map_idx];
		*h = (*av1Ctx->RefFrameHeight)[frameHdr->frame_to_show_map_idx];
		*subX = av1Ctx->RefSubsamplingX[frameHdr->frame_to_show_map_idx];
		*subY = av1Ctx->RefSubsamplingY[frameHdr->frame_to_show_map_idx];

		for (int y = 0; y < *h; y++) {
			for (int x = 0; x < *w; x++) {
				av1Ctx->currentFrame->OutY[y][x] = av1Ctx->FrameStore[frameHdr->frame_to_show_map_idx][0][y][x];
			}
		}

		for (int y = 0; y < ((*h + *subY) >> *subY); y++) {
			for (int x = 0; x < ((*w + *subX) >> *subX); x++) {
				av1Ctx->currentFrame->OutU[y][x] = av1Ctx->FrameStore[frameHdr->frame_to_show_map_idx][1][y][x];
				av1Ctx->currentFrame->OutV[y][x] = av1Ctx->FrameStore[frameHdr->frame_to_show_map_idx][2][y][x];
			}
		}
		*bitDepth = av1Ctx->RefBitDepth[frameHdr->frame_to_show_map_idx];
	} else {
		// Copy from the current frame
		*w = frameHdr->si.UpscaledWidth;
		*h = frameHdr->si.FrameHeight;
		*subX = seqHdr->color_config.subsampling_x;
		*subY = seqHdr->color_config.subsampling_y;

		//FILE *fp = fopen("test.yuv", "wb");

		for (int y = 0; y < *h; y++) {
			//uint8_t buf[*w];
			for (int x = 0; x < *w; x++) {
				av1Ctx->currentFrame->OutY[y][x] = av1Ctx->currentFrame->lrCtx->LrFrame[0][y][x];
				//printf("%d ",av1Ctx->currentFrame->OutY[y][x]);
				//buf[x] = av1Ctx->currentFrame->OutY[y][x];
			}
			//fwrite(buf, sizeof(uint8_t),*w, fp);
		}
		
		for (int y = 0; y < ((*h + *subY) >> *subY); y++) {
			//uint8_t buf[((*w + *subX) >> *subX ) * 2];

			for (int x = 0; x < ((*w + *subX) >> *subX); x++) {
				av1Ctx->currentFrame->OutU[y][x] = av1Ctx->currentFrame->lrCtx->LrFrame[1][y][x];
				av1Ctx->currentFrame->OutV[y][x] = av1Ctx->currentFrame->lrCtx->LrFrame[2][y][x];
				//buf[x * 2] = av1Ctx->currentFrame->OutU[y][x];
				//buf[x * 2 + 1]  = av1Ctx->currentFrame->OutV[y][x];
			}
			//fwrite(buf, sizeof(uint8_t),((*w + *subX) >> *subX ) * 2, fp);
			
		}
		//fclose(fp);
		*bitDepth = av1Ctx->RefBitDepth[0];  // BitDepth for each sample
	}

}
//7.18.3
//这里的bitdepth 到底是 用 序列参数集中的 还是 intermediateOutputPreparation中修改过的？？ 标记
void decode::filmGrainSynthesis(int w, int h, int subX, int subY,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    // 设置随机数生成器的初始状态
    int RandomRegister = frameHdr->film_grain_params.grain_seed;
    
    // 计算常数值
    int GrainCenter = 128 << (seqHdr->color_config.BitDepth - 8);
    int GrainMin = -GrainCenter;
    int GrainMax = (256 << (seqHdr->color_config.BitDepth - 8)) - 1 - GrainCenter;
    
    generateGrain(GrainMin,GrainMax,&RandomRegister,av1Ctx);

    // 初始化缩放查找表
    scalingLookupInitialization(av1Ctx);
    
    // 添加噪声
    addNoiseSynthesis(GrainMin,GrainMax,&RandomRegister, w, h, subX, subY,av1Ctx);

}
int decode::get_random_number( int bits ,int *RandomRegister) {
	int r = *RandomRegister;
	int bit = ((r >> 0) ^ (r >> 1) ^ (r >> 3) ^ (r >> 12)) & 1;
	r = (r >> 1) | (bit << 15);
	int result = (r >> (16 - bits)) & ((1 << bits) - 1);
	*RandomRegister = r;
	return result;
}
void decode::generateGrain(int GrainMin,int GrainMax, int *RandomRegister ,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    // 生成白噪声
    int shift = 12 - seqHdr->color_config.BitDepth + frameHdr->film_grain_params.grain_scale_shift;
    for (int y = 0; y < 73; y++) {
        for (int x = 0; x < 82; x++) {
            int g = 0;
            if (frameHdr->film_grain_params.num_y_points > 0) {
                g = Gaussian_Sequence[get_random_number(11,RandomRegister)];
            }
            av1Ctx->currentFrame->fgCtx->LumaGrain[y][x] = Round2(g, shift);
        }
    }

    // 应用自回归滤波
    shift = frameHdr->film_grain_params.ar_coeff_shift;
    for (int y = 3; y < 73; y++) {
        for (int x = 3; x < 82 - 3; x++) {
            int s = 0;
            int pos = 0;
            for (int deltaRow = -frameHdr->film_grain_params.ar_coeff_lag; deltaRow <= 0; deltaRow++) {
                for (int deltaCol = -frameHdr->film_grain_params.ar_coeff_lag; deltaCol <= frameHdr->film_grain_params.ar_coeff_lag; deltaCol++) {
                    if (deltaRow == 0 && deltaCol == 0) {
                        break;
                    }
                    int c = frameHdr->film_grain_params.ar_coeffs_y_plus_128[pos] - 128;
                    s += av1Ctx->currentFrame->fgCtx->LumaGrain[y + deltaRow][x + deltaCol] * c;
                    pos++;
                }
            }
            av1Ctx->currentFrame->fgCtx->LumaGrain[y][x] = Clip3(GrainMin, GrainMax, av1Ctx->currentFrame->fgCtx->LumaGrain[y][x] + Round2(s, shift));
        }
    }
	if(seqHdr->color_config.mono_chrome == 1) return;
    // 生成色度噪声
    int chromaW = (seqHdr->color_config.subsampling_x ? 44 : 82);
    int chromaH = (seqHdr->color_config.subsampling_y ? 38 : 73);
    shift = 12 - seqHdr->color_config.BitDepth + frameHdr->film_grain_params.grain_scale_shift;
    *RandomRegister = frameHdr->film_grain_params.grain_seed ^ 0xb524;
    for (int y = 0; y < chromaH; y++) {
        for (int x = 0; x < chromaW; x++) {
            int g = 0;
            if (frameHdr->film_grain_params.num_cb_points > 0 || frameHdr->film_grain_params.chroma_scaling_from_luma) {
                g = Gaussian_Sequence[get_random_number(11,RandomRegister)];
            }
            av1Ctx->currentFrame->fgCtx->CbGrain[y][x] = Round2(g, shift);
        }
    }

    *RandomRegister = frameHdr->film_grain_params.grain_seed ^ 0x49d8;
    for (int y = 0; y < chromaH; y++) {
        for (int x = 0; x < chromaW; x++) {
            int g = 0;
            if (frameHdr->film_grain_params.num_cr_points > 0 || frameHdr->film_grain_params.chroma_scaling_from_luma) {
                g = Gaussian_Sequence[get_random_number(11,RandomRegister)];
            }
            av1Ctx->currentFrame->fgCtx->CrGrain[y][x] = Round2(g, shift);
        }
    }

    // 应用自回归滤波到色度噪声
    shift = frameHdr->film_grain_params.ar_coeff_shift;
    for (int y = 3; y < chromaH; y++) {
        for (int x = 3; x < chromaW - 3; x++) {
            int s0 = 0;
            int s1 = 0;
            int pos = 0;
            for (int deltaRow = -frameHdr->film_grain_params.ar_coeff_lag; deltaRow <= 0; deltaRow++) {
                for (int deltaCol = -frameHdr->film_grain_params.ar_coeff_lag; deltaCol <= frameHdr->film_grain_params.ar_coeff_lag; deltaCol++) {
                    int c0 = frameHdr->film_grain_params.ar_coeffs_cb_plus_128[pos] - 128;
                    int c1 = frameHdr->film_grain_params.ar_coeffs_cr_plus_128[pos] - 128;
                    if (deltaRow == 0 && deltaCol == 0) {
                        if (frameHdr->film_grain_params.num_y_points > 0) {
                            int luma = 0;
                            int lumaX = ((x - 3) << seqHdr->color_config.subsampling_x) + 3;
                            int lumaY = ((y - 3) << seqHdr->color_config.subsampling_y) + 3;
                            for (int i = 0; i <= seqHdr->color_config.subsampling_y; i++) {
                                for (int j = 0; j <= seqHdr->color_config.subsampling_x; j++) {
                                    luma += av1Ctx->currentFrame->fgCtx->LumaGrain[lumaY + i][lumaX + j];
                                }
                            }
                            luma = Round2(luma, seqHdr->color_config.subsampling_x + seqHdr->color_config.subsampling_y);
                            s0 += luma * c0;
                            s1 += luma * c1;
                        }
                        break;
                    }
                    s0 += av1Ctx->currentFrame->fgCtx->CbGrain[y + deltaRow][x + deltaCol] * c0;
                    s1 += av1Ctx->currentFrame->fgCtx->CrGrain[y + deltaRow][x + deltaCol] * c1;
                    pos++;
                }
            }
            av1Ctx->currentFrame->fgCtx->CbGrain[y][x] = Clip3(GrainMin, GrainMax, av1Ctx->currentFrame->fgCtx->CbGrain[y][x] + Round2(s0, shift));
            av1Ctx->currentFrame->fgCtx->CrGrain[y][x] = Clip3(GrainMin, GrainMax, av1Ctx->currentFrame->fgCtx->CrGrain[y][x] + Round2(s1, shift));
        }
    }
}
void decode::scalingLookupInitialization(AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
    for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++) {
        int numPoints;
        if (plane == 0 || frameHdr->film_grain_params.chroma_scaling_from_luma)
            numPoints = frameHdr->film_grain_params.num_y_points;
        else if (plane == 1)
            numPoints = frameHdr->film_grain_params.num_cb_points;
        else
            numPoints = frameHdr->film_grain_params.num_cr_points;

        if (numPoints == 0) {
            for (int x = 0; x < 256; x++) {
                av1Ctx->currentFrame->fgCtx->ScalingLut[plane][x] = 0;
            }
        } else {
            for (int x = 0; x < get_x(plane, 0,av1Ctx); x++) {
                av1Ctx->currentFrame->fgCtx->ScalingLut[plane][x] = get_y(plane, 0,av1Ctx);
            }
            for (int i = 0; i < numPoints - 1; i++) {
                int deltaY = get_y(plane, i + 1,av1Ctx) - get_y(plane, i,av1Ctx);
                int deltaX = get_x(plane, i + 1,av1Ctx) - get_x(plane, i,av1Ctx);
                int delta = deltaY * ((65536 + (deltaX >> 1)) / deltaX);
                for (int x = 0; x < deltaX; x++) {
                    int v = get_y(plane, i,av1Ctx) + ((x * delta + 32768) >> 16);
                    av1Ctx->currentFrame->fgCtx->ScalingLut[plane][get_x(plane, i,av1Ctx) + x] = v;
                }
            }
            for (int x = get_x(plane, numPoints - 1,av1Ctx); x < 256; x++) {
                av1Ctx->currentFrame->fgCtx->ScalingLut[plane][x] = get_y(plane, numPoints - 1,av1Ctx);
            }
        }
    }
}

int decode::get_x(int plane, int i,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
    if (plane == 0 || frameHdr->film_grain_params.chroma_scaling_from_luma)
        return frameHdr->film_grain_params.point_y_value[i];
    else if (plane == 1)
        return frameHdr->film_grain_params.point_cb_value[i];
    else
        return frameHdr->film_grain_params.point_cr_value[i];
}

int decode::get_y(int plane, int i,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
    if (plane == 0 || frameHdr->film_grain_params.chroma_scaling_from_luma)
        return frameHdr->film_grain_params.point_y_scaling[i];
    else if (plane == 1)
        return frameHdr->film_grain_params.point_cb_scaling[i];
    else
        return frameHdr->film_grain_params.point_cr_scaling[i];
}
//This process combines the film grain with the image data.
void decode::addNoiseSynthesis(int GrainMin,int GrainMax,int * RandomRegister,int w, int h, int subX, int subY, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int lumaNum = 0;
	//First an array of noise data noiseStripe is generated for each 32 luma sample high stripe of the image.
	//noiseStripe[ lumaNum ][ 0 ] is 34 samples high and w samples wide
	//printf("addNoiseSynthesis \n");
	int16_t ****noiseStripe = new int16_t***[(h + 32) / 32];
	for(int i = 0 ; i < (h + 32) / 32 ; i++){
		noiseStripe[i] = new int16_t**[3];
		for(int j = 0 ; j < 3 ; j++){
			noiseStripe[i][j] =  new int16_t*[34];
			for(int k = 0 ; k < 34 ; k++){
				noiseStripe[i][j][k] = new int16_t[w + 34];
			}
		}
	}
	int rand,offsetX,offsetY,planeSubX,planeSubY,planeOffsetX,planeOffsetY,g,old;
	for (int y = 0; y < (h + 1) / 2; y += 16)
	{
		*RandomRegister = frameHdr->film_grain_params.grain_seed;
		*RandomRegister ^= ((lumaNum * 37 + 178) & 255) << 8;
		*RandomRegister ^= ((lumaNum * 173 + 105) & 255);
		for (int x = 0; x < (w + 1) / 2; x += 16)
		{
			rand = get_random_number(8,RandomRegister);
			offsetX = rand >> 4;
			offsetY = rand & 15;
			for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++)
			{
				planeSubX = (plane > 0) ? subX : 0;
				planeSubY = (plane > 0) ? subY : 0; 
				planeOffsetX = planeSubX ? 6 + offsetX : 9 + offsetX * 2;
				planeOffsetY = planeSubY ? 6 + offsetY : 9 + offsetY * 2;
				for (int i = 0; i < 34 >> planeSubY; i++)
				{
					for (int j = 0; j < 34 >> planeSubX; j++)
					{
						if (plane == 0)
							g = av1Ctx->currentFrame->fgCtx->LumaGrain[planeOffsetY + i][planeOffsetX + j];
						else if (plane == 1)
							g = av1Ctx->currentFrame->fgCtx->CbGrain[planeOffsetY + i][planeOffsetX + j];
						else
							g = av1Ctx->currentFrame->fgCtx->CrGrain[planeOffsetY + i][planeOffsetX + j];
						if (planeSubX == 0)
						{
							if (j < 2 && frameHdr->film_grain_params.overlap_flag && x > 0)
							{
								old = noiseStripe[lumaNum][plane][i][x * 2 + j];
								if (j == 0)
								{
									g = old * 27 + g * 17;
								}
								else
								{
									g = old * 17 + g * 27;
								}
								g = Clip3(GrainMin, GrainMax, Round2(g, 5));
							}
							//printf("1 %d %d |%d %d %d %d g %d\n",h,(h + 32) / 32 ,w,lumaNum,plane,i,x * 2+j,g);
							noiseStripe[lumaNum][plane][i][x * 2 + j] = g;
						}
						else
						{
							if (j == 0 && frameHdr->film_grain_params.overlap_flag && x > 0)
							{
								old = noiseStripe[lumaNum][plane][i][x + j];
								g = old * 23 + g * 22;
								g = Clip3(GrainMin, GrainMax, Round2(g, 5));
							}
							//[31 ][3][34][750]
							//printf("2,%d %d |%d %d %d %d g %d\n",h,(h + 32) / 32 ,w,lumaNum,plane,i,x+j,g);
							noiseStripe[lumaNum][plane][i][x + j] = g;
						}
					}
				}
			}
		}
		lumaNum++;
	}
	uint16_t **noiseImage[3];
	for(int i = 0; i < 3 ; i++){
		noiseImage[i] = new uint16_t*[h];
		for(int j = 0; j < h ; j++){
			noiseImage[i][j] = new uint16_t[w];
		}
	}
	for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++ ) {  
		int planeSubX = (plane > 0) ? subX : 0;  
		int planeSubY = (plane > 0) ? subY : 0;  
		for (int y = 0; y < ((h + planeSubY) >> planeSubY); y++ ) {  
			int lumaNum = y >> (5 - planeSubY);  
			int i = y - (lumaNum << (5 - planeSubY));  
			for (int x = 0; x < ((w + planeSubX) >> planeSubX); x++ ) {  
				int g = noiseStripe[lumaNum][plane][i][x];  
				if (planeSubY == 0) {  
					if (i < 2 && lumaNum > 0 && frameHdr->film_grain_params.overlap_flag) {  
						int old = noiseStripe[lumaNum - 1][plane][i + 32][x];  
						if (i == 0) {  
							g = old * 27 + g * 17;  
						} else {  
							g = old * 17 + g * 27;  
						}  
						g = Clip3(GrainMin, GrainMax, Round2(g, 5));  
					}  
				} else {  
					if (i < 1 && lumaNum > 0 && frameHdr->film_grain_params.overlap_flag) {  
						int old = noiseStripe[lumaNum - 1][plane][i + 16][x];  
						g = old * 23 + g * 22;  
						g = Clip3(GrainMin, GrainMax, Round2(g, 5));  
					}  
				}  
				noiseImage[plane][y][x] = g;  
			}  
		}  
	}
	int minValue,maxLuma,maxChroma;
	if ( frameHdr->film_grain_params.clip_to_restricted_range  ) {  
		minValue = 16 << (seqHdr->color_config.BitDepth - 8);  
		maxLuma = 235 << (seqHdr->color_config.BitDepth - 8);  
		if (seqHdr->color_config.matrix_coefficients == MC_IDENTITY )  
			maxChroma = maxLuma;  
		else  
			maxChroma = 240 << (seqHdr->color_config.BitDepth - 8);  
	} else {  
		minValue = 0;  
		maxLuma = (256 << (seqHdr->color_config.BitDepth - 8)) - 1;  
		maxChroma = maxLuma;  
	}  
	//ScalingShift = grain_scaling_minus_8 + 8;  
	int lumaX,lumaY,lumaNextX,averageLuma;
	uint16_t orig,merged,combined,noise;
	for (int y = 0; y < ( (h + subY) >> subY); y++ ) {
		for (int x = 0; x < ( (w + subX) >> subX); x++ ) { 
			lumaX = x << subX;  
			lumaY = y << subY;  
			lumaNextX = Min( lumaX + 1, w - 1 );  
			if ( subX )  
				averageLuma = Round2( av1Ctx->currentFrame->OutY[ lumaY ][ lumaX ] + av1Ctx->currentFrame->OutY[ lumaY ][ lumaNextX ], 1 );  
			else  
				averageLuma = av1Ctx->currentFrame->OutY[ lumaY ][ lumaX ];  
			if ( frameHdr->film_grain_params.num_cb_points > 0 || frameHdr->film_grain_params.chroma_scaling_from_luma ) {  
				orig = av1Ctx->currentFrame->OutU[ y ][ x ];  
				if ( frameHdr->film_grain_params.chroma_scaling_from_luma ) {  
					merged = averageLuma;  
				} else {  
					combined = averageLuma * ( frameHdr->film_grain_params.cb_luma_mult - 128 ) + orig * ( frameHdr->film_grain_params.cb_mult - 128 );  
					merged = Clip1( ( combined >> 6 ) + ( (frameHdr->film_grain_params.cb_offset - 256 ) << (seqHdr->color_config.BitDepth - 8) ),seqHdr->color_config.BitDepth);  
				}  
				noise = noiseImage[ 1 ][ y ][ x ];  
				noise = Round2( scale_lut( 1, merged ,av1Ctx) * noise, frameHdr->film_grain_params.grain_scaling );  
				av1Ctx->currentFrame->OutU[ y ][ x ] = Clip3( minValue, maxChroma, orig + noise );  
			}  
			if ( frameHdr->film_grain_params.num_cr_points > 0 || frameHdr->film_grain_params.chroma_scaling_from_luma) {  
				orig = av1Ctx->currentFrame->OutV[ y ][ x ];  
				if ( frameHdr->film_grain_params.chroma_scaling_from_luma ) {  
					merged = averageLuma;  
				} else {  
					combined = averageLuma * ( frameHdr->film_grain_params.cr_luma_mult - 128 ) + orig * ( frameHdr->film_grain_params.cr_mult - 128 );  
					merged = Clip1( ( combined >> 6 ) + ( (frameHdr->film_grain_params.cr_offset - 256 ) << (seqHdr->color_config.BitDepth - 8) ) ,seqHdr->color_config.BitDepth);  
				}  
				noise = noiseImage[ 2 ][ y ][ x ];  
				noise = Round2( scale_lut( 2, merged ,av1Ctx) * noise, frameHdr->film_grain_params.grain_scaling );  
				av1Ctx->currentFrame->OutV[ y ][ x ] = Clip3( minValue, maxChroma, orig + noise );  
			}  
		}  
	}  
	
	for (int y = 0; y < h ; y++ ) {  
		for (int x = 0; x < w ; x++ ) {  
			orig = av1Ctx->currentFrame->OutY[ y ][ x ];  
			noise = noiseImage[ 0 ][ y ][ x ];  
			noise = Round2( scale_lut( 0, orig ,av1Ctx) * noise, frameHdr->film_grain_params.grain_scaling );  
			if ( frameHdr->film_grain_params.num_y_points > 0 ) {  
				av1Ctx->currentFrame->OutY[ y ][ x ] = Clip3( minValue, maxLuma, orig + noise );  
			}  
		}  
	}



	for(int i = 0 ; i < (h + 32) / 32 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			for(int k = 0 ; k < 34 ; k++){
				delete [] noiseStripe[i][j][k];
			}
			delete [] noiseStripe[i][j];
		}
		delete [] noiseStripe[i];
	}
	delete [] noiseStripe;

	for(int i = 0; i < 3 ; i++){
		for(int j = 0; j < h ; j++){
			delete [] noiseImage[i][j];
		}
		delete [] noiseImage[i];
	}

}
int decode::scale_lut( int plane,int index ,AV1DecodeContext *av1Ctx) {
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int shift = seqHdr->color_config.BitDepth - 8;
	int x = index >> shift;
	int rem = index - ( x << shift );
	if ( seqHdr->color_config.BitDepth == 8 || x == 255) {
		
	} else {
		int start = av1Ctx->currentFrame->fgCtx->ScalingLut[ plane ][ x ];
		int end = av1Ctx->currentFrame->fgCtx->ScalingLut[ plane ][ x + 1 ];
		return start + Round2( (end - start) * rem, shift );
	}
}

//7.19
void decode::motionFieldMotionVectorStorage(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	for (int row = 0; row < frameHdr->MiRows; row++) {
		for (int col = 0; col < frameHdr->MiCols; col++) {
			av1Ctx->currentFrame->mfmvCtx->MfRefFrames[row][col] = NONE;
			av1Ctx->currentFrame->mfmvCtx->MfMvs[row][col][0] = 0;
			av1Ctx->currentFrame->mfmvCtx->MfMvs[row][col][1] = 0;

			for (int list = 0; list < 2; list++) {
				int r = av1Ctx->RefFrames[row][col][list];

				if (r > INTRA_FRAME) {
					int refIdx = frameHdr->ref_frame_idx[r - LAST_FRAME];
					int dist = get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits, av1Ctx->RefOrderHint[refIdx], frameHdr->OrderHint);

					if (dist < 0) {
						int mvRow = av1Ctx->Mvs[row][col][list][0];
						int mvCol = av1Ctx->Mvs[row][col][list][1];

						if (Abs(mvRow) <= REFMVS_LIMIT && Abs(mvCol) <= REFMVS_LIMIT) {
							av1Ctx->currentFrame->mfmvCtx->MfRefFrames[row][col] = r;
							av1Ctx->currentFrame->mfmvCtx->MfMvs[row][col][0] = mvRow;
							av1Ctx->currentFrame->mfmvCtx->MfMvs[row][col][1] = mvCol;
						}
					}
				}
			}
		}
	}

}
void decode::referenceFrameUpdate( AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	for (int i = 0; i < NUM_REF_FRAMES; i++) {
		if ((frameHdr->refresh_frame_flags >> i) & 1) {
			av1Ctx->RefValid[i] = 1;
			av1Ctx->RefFrameId[i] = frameHdr->current_frame_id;
			(*av1Ctx->RefUpscaledWidth)[i] = frameHdr->si.UpscaledWidth;
			(*av1Ctx->RefFrameWidth)[i] = frameHdr->si.FrameWidth;
			(*av1Ctx->RefFrameHeight)[i] = frameHdr->si.FrameHeight;
			(*av1Ctx->RefRenderWidth)[i] = frameHdr->si.RenderWidth;
			(*av1Ctx->RefRenderHeight)[i] = frameHdr->si.RenderHeight;
			av1Ctx->RefMiCols[i] = frameHdr->MiCols;
			av1Ctx->RefMiRows[i] = frameHdr->MiRows;
			av1Ctx->RefFrameType[i] = frameHdr->frame_type;
			av1Ctx->RefSubsamplingX[i] = seqHdr->color_config.subsampling_x;
			av1Ctx->RefSubsamplingY[i] = seqHdr->color_config.subsampling_y;
			av1Ctx->RefBitDepth[i] = seqHdr->color_config.BitDepth;

			for (int j = 0; j < REFS_PER_FRAME; j++) {
				av1Ctx->SavedOrderHints[i][j + LAST_FRAME] = frameHdr->OrderHints[j + LAST_FRAME];
			}

			for (int y = 0; y < frameHdr->si.FrameHeight; y++) {
				for (int x = 0; x < frameHdr->si.UpscaledWidth; x++) {
					av1Ctx->FrameStore[i][0][y][x] = av1Ctx->currentFrame->lrCtx->LrFrame[0][y][x];
				}
			}

			for (int plane = 1; plane <= 2; plane++) {
				for (int y = 0; y < ((frameHdr->si.FrameHeight + seqHdr->color_config.subsampling_y) >> seqHdr->color_config.subsampling_y); y++) {
					for (int x = 0; x < ((frameHdr->si.UpscaledWidth + seqHdr->color_config.subsampling_x) >> seqHdr->color_config.subsampling_x); x++) {
						av1Ctx->FrameStore[i][plane][y][x] = av1Ctx->currentFrame->lrCtx->LrFrame[plane][y][x];
					}
				}
			}

			for (int row = 0; row < frameHdr->MiRows; row++) {
				for (int col = 0; col < frameHdr->MiCols; col++) {
					av1Ctx->SavedRefFrames[i][row][col] = av1Ctx->currentFrame->mfmvCtx->MfRefFrames[row][col];

					for (int comp = 0; comp <= 1; comp++) {
						av1Ctx->SavedMvs[i][row][col][comp] = av1Ctx->currentFrame->mfmvCtx->MfMvs[row][col][comp];
					}
				}
			}

			for (int ref = LAST_FRAME; ref <= ALTREF_FRAME; ref++) {
				for (int j = 0; j < 6; j++) {
					av1Ctx->SavedGmParams[i][ref][j] = frameHdr->global_motion_params.gm_params[ref][j];
				}
			}

			for (int row = 0; row < frameHdr->MiRows; row++) {
				for (int col = 0; col < frameHdr->MiCols; col++) {
					av1Ctx->SavedSegmentIds[i][row][col] = av1Ctx->SegmentIds[row][col];
				}
			}

			save_cdfs(av1Ctx,i);

			if (seqHdr->film_grain_params_present == 1) {
				save_grain_params(av1Ctx,i);
			}

			save_loop_filter_params(av1Ctx, i);
			save_segmentation_params(av1Ctx, i);
		}
	}

}
void decode::referenceFrameLoading( AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

	frameHdr->current_frame_id = av1Ctx->RefFrameId[frameHdr->frame_to_show_map_idx];//这里， spec 是不是写错了？？
	frameHdr->si.UpscaledWidth = (*av1Ctx->RefUpscaledWidth)[frameHdr->frame_to_show_map_idx];
	frameHdr->si.FrameWidth = (*av1Ctx->RefFrameWidth)[frameHdr->frame_to_show_map_idx];
	frameHdr->si.FrameHeight = (*av1Ctx->RefFrameHeight)[frameHdr->frame_to_show_map_idx];
	frameHdr->si.RenderWidth = (*av1Ctx->RefRenderWidth)[frameHdr->frame_to_show_map_idx];
	frameHdr->si.RenderHeight = (*av1Ctx->RefRenderHeight)[frameHdr->frame_to_show_map_idx];
	frameHdr->MiCols = av1Ctx->RefMiCols[frameHdr->frame_to_show_map_idx];
	frameHdr->MiRows = av1Ctx->RefMiRows[frameHdr->frame_to_show_map_idx];
	seqHdr->color_config.subsampling_x = av1Ctx->RefSubsamplingX[frameHdr->frame_to_show_map_idx];
	seqHdr->color_config.subsampling_y = av1Ctx->RefSubsamplingY[frameHdr->frame_to_show_map_idx];
	seqHdr->color_config.BitDepth = av1Ctx->RefBitDepth[frameHdr->frame_to_show_map_idx];
	frameHdr->OrderHint = av1Ctx->RefOrderHint[frameHdr->frame_to_show_map_idx];

	for (int j = 0; j < REFS_PER_FRAME; j++) {
		frameHdr->OrderHints[j + LAST_FRAME] = av1Ctx->SavedOrderHints[frameHdr->frame_to_show_map_idx][j + LAST_FRAME];
	}

	for (int y = 0; y < frameHdr->si.FrameHeight; y++) {
		for (int x = 0; x < frameHdr->si.UpscaledWidth; x++) {
			av1Ctx->currentFrame->lrCtx->LrFrame[0][y][x] = av1Ctx->FrameStore[frameHdr->frame_to_show_map_idx][0][y][x];
		}
	}

	for (int plane = 1; plane <= 2; plane++) {
		for (int y = 0; y < ((frameHdr->si.FrameHeight + seqHdr->color_config.subsampling_y) >> seqHdr->color_config.subsampling_y); y++) {
			for (int x = 0; x < ((frameHdr->si.UpscaledWidth + seqHdr->color_config.subsampling_x) >> seqHdr->color_config.subsampling_x); x++) {
				av1Ctx->currentFrame->lrCtx->LrFrame[plane][y][x] = av1Ctx->FrameStore[frameHdr->frame_to_show_map_idx][plane][y][x];
			}
		}
	}

	for (int row = 0; row < frameHdr->MiRows; row++) {
		for (int col = 0; col < frameHdr->MiCols; col++) {
			av1Ctx->currentFrame->mfmvCtx->MfRefFrames[row][col] = av1Ctx->SavedRefFrames[frameHdr->frame_to_show_map_idx][row][col];

			for (int comp = 0; comp <= 1; comp++) {
				av1Ctx->currentFrame->mfmvCtx->MfMvs[row][col][comp] = av1Ctx->SavedMvs[frameHdr->frame_to_show_map_idx][row][col][comp];
			}
		}
	}

	for (int ref = LAST_FRAME; ref <= ALTREF_FRAME; ref++) {
		for (int j = 0; j < 6; j++) {
			frameHdr->global_motion_params.gm_params[ref][j] = av1Ctx->SavedGmParams[frameHdr->frame_to_show_map_idx][ref][j];
		}
	}

	for (int row = 0; row < frameHdr->MiRows; row++) {
		for (int col = 0; col < frameHdr->MiCols; col++) {
			av1Ctx->SegmentIds[row][col] = av1Ctx->SavedSegmentIds[frameHdr->frame_to_show_map_idx][row][col];
		}
	}

	load_cdfs(av1Ctx, frameHdr->frame_to_show_map_idx);

	if (seqHdr->film_grain_params_present == 1) {
		load_grain_params( av1Ctx, frameHdr->frame_to_show_map_idx);
	}

	load_loop_filter_params(av1Ctx, frameHdr->frame_to_show_map_idx);
	load_segmentation_params(av1Ctx, frameHdr->frame_to_show_map_idx);


}