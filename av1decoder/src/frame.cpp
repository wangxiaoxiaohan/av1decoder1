#include "frame.h"
#include "segmentation.h"
#include <string.h>
frame::frame(){
	sb = &Symbol::Instance();
	seg_instance = &segmentation::Instance();
	decode_instance = &decode::Instance();
}
frame::~frame(){
	
}
int frame::parseUncompressedHeader(int sz, bitSt *bs, AV1DecodeContext *av1Ctx, sequenceHeader *seqHdr, obuHeader *obuheader, frameHeader *out)
{
	int idLen = seqHdr->additional_frame_id_length + seqHdr->delta_frame_id_length;
	if (seqHdr->reduced_still_picture_header)
	{
		out->show_existing_frame = 0;
		out->frame_type = KEY_FRAME;
		out->FrameIsIntra = 0;
		out->show_frame = 1;
		out->showable_frame = 0;
	}
	else
	{
		out->show_existing_frame = readOneBit(bs);
		if (out->show_existing_frame == 1)
		{
			out->frame_to_show_map_idx = readBits(bs, 3);
			if (seqHdr->decoder_model_info_present_flag && !seqHdr->timing_info.equal_picture_interval)
			{
				out->frame_presentation_time = readBits(bs, seqHdr->decoder_model_info.frame_presentation_time_length);
			}
			if (seqHdr->frame_id_numbers_present_flag)
			{
				out->display_frame_id = readBits(bs, idLen);
			}
			return 0;
		}
		out->frame_type = readBits(bs, 2);
		printf("frame_type %d\n",out->frame_type);
		out->FrameIsIntra = (out->frame_type == INTRA_ONLY_FRAME || out->frame_type == KEY_FRAME);
		out->show_frame = readOneBit(bs);
		if (out->show_frame && seqHdr->decoder_model_info_present_flag && !seqHdr->timing_info.equal_picture_interval)
		{
			out->frame_presentation_time = readBits(bs, seqHdr->decoder_model_info.frame_presentation_time_length);
		}
		if (out->show_frame)
		{
			out->showable_frame = out->frame_type != KEY_FRAME;
		}
		else
		{
			out->showable_frame = readOneBit(bs);
		}
		if (out->frame_type == SWITCH_FRAME || (out->frame_type == KEY_FRAME && out->show_frame))
		{
			out->error_resilient_mode = 1;
		}
		else
		{
			out->error_resilient_mode = readOneBit(bs);
		}
	}
	if (out->frame_type == KEY_FRAME && out->show_frame)
	{
		for (int i = 0; i < NUM_REF_FRAMES; i++)
		{
			av1Ctx->RefValid[i] = 0;
			//
			av1Ctx->RefOrderHint[i] = 0;
		}

		for (int i = 0; i < REFS_PER_FRAME; i++)
		{
			out->OrderHints[LAST_FRAME + i] = 0;
		}
	}
	out->disable_cdf_update = readOneBit(bs);
	if (seqHdr->seq_force_screen_content_tools == SELECT_SCREEN_CONTENT_TOOLS)
	{
		out->allow_screen_content_tools = readOneBit(bs);
	}
	else
	{
		out->allow_screen_content_tools = seqHdr->seq_force_screen_content_tools;
	}
	if (out->allow_screen_content_tools)
	{
		if (seqHdr->seq_force_integer_mv == SELECT_INTEGER_MV)
		{
			out->force_integer_mv = readOneBit(bs);
		}
		else
		{
			out->force_integer_mv = seqHdr->seq_force_integer_mv;
		}
	}
	else
	{
		out->force_integer_mv = 0;
	}

	if (out->FrameIsIntra)
	{
		out->force_integer_mv = 1;
	}

	if (seqHdr->frame_id_numbers_present_flag)
	{
		// PrevFrameID = current_frame_id
		out->current_frame_id = readBits(bs, idLen);
		// mark_ref_frames( idLen )
	}
	else
	{
		out->current_frame_id = 0;
	}

	if (out->frame_type == SWITCH_FRAME)
		out->frame_size_override_flag = 1;
	else if (seqHdr->reduced_still_picture_header)
		out->frame_size_override_flag = 0;
	else
		out->frame_size_override_flag = readOneBit(bs);

	out->OrderHint = readBits(bs, seqHdr->OrderHintBits);

	if (out->FrameIsIntra)
	{
		out->primary_ref_frame = PRIMARY_REF_NONE;
	}
	else
	{
		out->primary_ref_frame = readBits(bs, 3);
	}

	if (seqHdr->decoder_model_info_present_flag)
	{
		out->buffer_removal_time_present_flag = readOneBit(bs);
		if (out->buffer_removal_time_present_flag)
		{
			for (int opNum = 0; opNum < seqHdr->operating_points_cnt; opNum++)
			{
				if (seqHdr->seqOperatingPoint[opNum].decoder_model_present_for_this_op)
				{
					int opPtIdc = seqHdr->seqOperatingPoint[opNum].operating_point_idc;
					int inTemporalLayer = (opPtIdc >> obuheader->temporal_id) & 1;
					int inSpatialLayer = (opPtIdc >> (obuheader->spatial_id + 8)) & 1;
					if (opPtIdc == 0 || (inTemporalLayer && inSpatialLayer))
					{
						out->operating_points[opNum].buffer_removal_time = readBits(bs, seqHdr->decoder_model_info.buffer_removal_time_length);
					}
				}
			}
		}
	}
	if (out->frame_type == SWITCH_FRAME ||
		(out->frame_type == KEY_FRAME && out->show_frame))
	{
		out->refresh_frame_flags = (1 << NUM_REF_FRAMES) - 1;
	}
	else
	{
		out->refresh_frame_flags = readBits(bs, 8);
	}
	if (!out->FrameIsIntra || out->refresh_frame_flags != (1 << NUM_REF_FRAMES) - 1)
	{
		if (out->error_resilient_mode && seqHdr->enable_order_hint)
		{
			for (int i = 0; i < NUM_REF_FRAMES; i++)
			{
				out->ref_order_hint[i] = readBits(bs, seqHdr->OrderHintBits);
				if (out->ref_order_hint[i] != av1Ctx->RefOrderHint[i])
				{
					av1Ctx->RefValid[i] = 0;
				}
			}
		}
	}
	if (out->FrameIsIntra)
	{

		readFrameSize(bs, seqHdr, out, &out->si);
		readRenderSize(bs, seqHdr, out, &out->si);
		if (out->allow_screen_content_tools && out->si.UpscaledWidth == out->si.FrameWidth)
		{
			out->allow_intrabc = readOneBit(bs);
		}
	}
	else
	{
		if (!seqHdr->enable_order_hint)
		{
			out->frame_refs_short_signaling = 0;
		}
		else
		{
			out->frame_refs_short_signaling = readOneBit(bs);
			if (out->frame_refs_short_signaling)
			{
				out->last_frame_idx = readBits(bs, 3);
				out->gold_frame_idx = readBits(bs, 3);
				decode_instance->set_frame_refs(av1Ctx);
			}
		}
		for (int i = 0; i < REFS_PER_FRAME; i++)
		{
			if (!out->frame_refs_short_signaling)
				out->ref_frame_idx[i] = readBits(bs, 3);
			if (seqHdr->frame_id_numbers_present_flag)
			{
				out->delta_frame_id[i] = readBits(bs, seqHdr->delta_frame_id_length) + 1;
				out->expectedFrameId[i] = ((out->current_frame_id + (1 << idLen) -
											out->delta_frame_id[i]) %
										   (1 << idLen));
			}
		}
		if (out->frame_size_override_flag && !out->error_resilient_mode)
		{
			uint8_t found_ref;
			for (int i = 0; i < REFS_PER_FRAME; i++)
			{
				found_ref = readOneBit(bs);
				if (found_ref == 1)
				{
					// ref_frames
					out->si.UpscaledWidth = (*av1Ctx->RefUpscaledWidth)[out->ref_frame_idx[i]];
					out->si.FrameWidth = out->si.UpscaledWidth;
					out->si.FrameHeight = (*av1Ctx->RefFrameHeight)[out->ref_frame_idx[i]];	// RefFrameHeight[ ref_frame_idx[ i ] ]
					out->si.RenderWidth = (*av1Ctx->RefRenderWidth)[out->ref_frame_idx[i]];	// RefRenderWidth[ ref_frame_idx[ i ] ]
					out->si.RenderHeight = (*av1Ctx->RefRenderHeight)[out->ref_frame_idx[i]]; // RefRenderHeight[ ref_frame_idx[ i ] ]
					break;
				}
			}

			if (found_ref == 0)
			{
				readFrameSize(bs, seqHdr, out, &out->si);
				readRenderSize(bs, seqHdr, out, &out->si);
			}
			else
			{
				readSuperresParams(bs, seqHdr, &out->si);
				// compute image size;
				out->MiCols = 2 * ((out->si.FrameWidth + 7) >> 3);
				out->MiRows = 2 * ((out->si.FrameHeight + 7) >> 3);
			}
		}
		else
		{
			readFrameSize(bs, seqHdr, out, &out->si);
			readRenderSize(bs, seqHdr, out, &out->si);
		}

		if (out->force_integer_mv)
		{
			out->allow_high_precision_mv = 0;
		}
		else
		{
			out->allow_high_precision_mv = readOneBit(bs);
		}

		read_interpolation_filter(bs, out);
		out->is_motion_mode_switchable = readOneBit(bs);
		if (out->error_resilient_mode || !seqHdr->enable_ref_frame_mvs)
		{
			out->use_ref_frame_mvs = 0;
		}
		else
		{
			out->use_ref_frame_mvs = readOneBit(bs);
		}

		for (int i = 0; i < REFS_PER_FRAME; i++)
		{
			int refFrame = LAST_FRAME + i;
			//RefOrderHint 要在 Reference frame update process过程中 去更新，现阶段还没有 所以全是0
			int hint = av1Ctx->RefOrderHint[out->ref_frame_idx[i]];
			out->OrderHints[refFrame] = hint;
			if (!seqHdr->enable_order_hint)
			{
				out->RefFrameSignBias[refFrame] = 0;
			}
			else
			{
				out->RefFrameSignBias[refFrame] = get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits , hint, out->OrderHint) > 0;
			}
		}
	}

	if (seqHdr->reduced_still_picture_header || out->disable_cdf_update)
		out->disable_frame_end_update_cdf = 1;
	else
		out->disable_frame_end_update_cdf = readOneBit(bs);

	if (out->primary_ref_frame == PRIMARY_REF_NONE)
	{
		decode_instance->init_non_coeff_cdfs( &av1Ctx->tileSavedCdf);
		if(! av1Ctx->PrevSegmentIds){
			av1Ctx->PrevSegmentIds = new uint8_t*[out->MiRows];
			for(int i  = 0 ; i < out->MiRows ; i++){
				av1Ctx->PrevSegmentIds[i] = new uint8_t[out->MiCols];
			}		
		}

		decode_instance->setup_past_independence(av1Ctx);
	}
	else
	{
		//从主参考帧里面拷贝cdf
		 decode_instance->load_cdfs( av1Ctx,out->ref_frame_idx[ out->primary_ref_frame ] );
		 decode_instance->load_previous(av1Ctx);
	}
	if (out->use_ref_frame_mvs == 1)
	{
		 decode_instance->motion_field_estimation(av1Ctx);
	}
		

	// tile_info
	readTileInfo(bs, seqHdr, out);
	// quantization_params
	readQuantizationParams(bs, seqHdr, out);
	// segmentation_params

	readSegmentationParams(bs, seqHdr, out);
	// delta_q_params
	readDeltaQuantizerParams(bs, out);
	// delta_lf_params
	readDeltaLoopfilterParams(bs, out);

	if (out->primary_ref_frame == PRIMARY_REF_NONE)
	{
		 decode_instance->init_coeff_cdfs(av1Ctx,&av1Ctx->tileSavedCdf);
	}
	else
	{
		 decode_instance->load_previous_segment_ids(av1Ctx);
	}
	out->CodedLossless = 1;
	int segmentId;
	for (segmentId = 0; segmentId < MAX_SEGMENTS; segmentId++)
	{
		int qindex = seg_instance->get_qindex(1, segmentId,out,av1Ctx->CurrentQIndex);
		out->segmentation_params.LosslessArray[segmentId] = qindex == 0 && out->quantization_params.DeltaQYDc == 0 &&
								   out->quantization_params.DeltaQUAc == 0 && out->quantization_params.DeltaQUDc == 0 &&
								   out->quantization_params.DeltaQVAc == 0 && out->quantization_params.DeltaQVDc == 0;
		if (!out->segmentation_params.LosslessArray[segmentId])
			out->CodedLossless = 0;
		
		//segment dequant
		if (out->quantization_params.using_qmatrix)
		{
			if (out->segmentation_params.LosslessArray[segmentId])
			{
				out->quantization_params.SegQMLevel[0][segmentId] = 15;
				out->quantization_params.SegQMLevel[1][segmentId] = 15;
				out->quantization_params.SegQMLevel[2][segmentId] = 15;
			}
			else
			{
				out->quantization_params.SegQMLevel[0][segmentId] = out->quantization_params.qm_y;
				out->quantization_params.SegQMLevel[1][segmentId] = out->quantization_params.qm_u;
				out->quantization_params.SegQMLevel[2][segmentId] = out->quantization_params.qm_v;
			}
		}

	}
	out->AllLossless = out->CodedLossless && (out->si.FrameWidth == out->si.UpscaledWidth);
	
	//loop filter Params
	readLoopFilterParams(bs,out,seqHdr);
	//cdef Paramsaq
	readCdefParams(bs,out,seqHdr);

	readLrParams(bs,out,seqHdr);


	if ( out->CodedLossless == 1 ) {
		out->TxMode = ONLY_4X4;
	} else {
		int tx_mode_select  = readOneBit(bs);
		if ( tx_mode_select ) {
			out->TxMode = TX_MODE_SELECT;
		} else {
			out->TxMode = TX_MODE_LARGEST;
		}
	}

	if ( out->FrameIsIntra ) {
		out->reference_select = 0;
	} else {
		out->reference_select = readOneBit(bs);
	}

	readSkipModeParams(bs,out,av1Ctx,seqHdr);

	if ( out->FrameIsIntra || out->error_resilient_mode || !seqHdr->enable_warped_motion)
		out->allow_warped_motion = 0;
	else
		out->allow_warped_motion = readOneBit(bs);
	out->reduced_tx_set = readOneBit(bs);

	//global_motion_params
	readGlobalMotionParams(bs, out);
	//film_grain_params
	
	readFilmGrainParams(bs,out,seqHdr,av1Ctx);
	return sz - bs->offset;
}
int frame::mark_ref_frames(AV1DecodeContext *av1Ctx,int  idLen)
{
	int diffLen = av1Ctx->seqHdr.delta_frame_id_length;
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	for (int i = 0; i < NUM_REF_FRAMES; i++)
	{
		if (frameHdr->current_frame_id > (1 << diffLen))
		{
			if (av1Ctx->RefFrameId[i] > frameHdr->current_frame_id ||
				av1Ctx->RefFrameId[i] < (frameHdr->current_frame_id - (1 << diffLen)))
				av1Ctx->RefValid[i] = 0;
		}
		else
		{
			if (av1Ctx->RefFrameId[i] > frameHdr->current_frame_id &&
				av1Ctx->RefFrameId[i] < ((1 << idLen) +
								 frameHdr->current_frame_id -
								 (1 << diffLen)))
				av1Ctx->RefValid[i] = 0;
		}
	}
}
int frame::readTileInfo(bitSt *bs, sequenceHeader *seqHdr, frameHeader *frameHdr)
{
	const int sbCols = seqHdr->use_128x128_superblock ? ((frameHdr->MiCols + 31) >> 5) : ((frameHdr->MiCols + 15) >> 4);
	const int sbRows = seqHdr->use_128x128_superblock ? ((frameHdr->MiRows + 31) >> 5) : ((frameHdr->MiRows + 15) >> 4);
	const int sbShift = seqHdr->use_128x128_superblock ? 5 : 4;
	const int sbSize = sbShift + 2;
	const int maxTileWidthSb = MAX_TILE_WIDTH >> sbSize;
	int maxTileAreaSb = MAX_TILE_AREA >> (sbSize * 2);
	frameHdr->tile_info.minLog2TileCols = tile_log2(maxTileWidthSb, sbCols);
	frameHdr->tile_info.maxLog2TileCols = tile_log2(1, Min(sbCols, MAX_TILE_COLS));
	frameHdr->tile_info.maxLog2TileRows = tile_log2(1, Min(sbRows, MAX_TILE_ROWS));
	const int minLog2Tiles = Max(frameHdr->tile_info.minLog2TileCols, tile_log2(maxTileAreaSb, sbRows * sbCols));
	frameHdr->tile_info.uniform_tile_spacing_flag = readOneBit(bs);

	int startSb;
	if (frameHdr->tile_info.uniform_tile_spacing_flag)
	{
		frameHdr->tile_info.TileColsLog2 = frameHdr->tile_info.minLog2TileCols;
		while (frameHdr->tile_info.TileColsLog2 < frameHdr->tile_info.maxLog2TileCols)
		{
			frameHdr->tile_info.increment_tile_cols_log2 = readOneBit(bs);
			if (frameHdr->tile_info.increment_tile_cols_log2 == 1)
				frameHdr->tile_info.TileColsLog2++;
			else
				break;
		}
		const int tileWidthSb = (sbCols + (1 << frameHdr->tile_info.TileColsLog2) - 1) >> frameHdr->tile_info.TileColsLog2;
		int i = 0;
		for (startSb = 0; startSb < sbCols; startSb += tileWidthSb)
		{
			frameHdr->tile_info.MiColStarts[i] = startSb << sbShift;
			i += 1;
		}
		frameHdr->tile_info.MiColStarts[i] = frameHdr->MiCols;
		frameHdr->tile_info.TileCols = i;

		frameHdr->tile_info.minLog2TileRows = Max(minLog2Tiles - frameHdr->tile_info.TileColsLog2, 0);
		frameHdr->tile_info.TileRowsLog2 = frameHdr->tile_info.minLog2TileRows;
		while (frameHdr->tile_info.TileRowsLog2 < frameHdr->tile_info.maxLog2TileRows)
		{
			frameHdr->tile_info.increment_tile_rows_log2 = readOneBit(bs);
			if (frameHdr->tile_info.increment_tile_rows_log2 == 1)
				frameHdr->tile_info.TileRowsLog2++;
			else
				break;
		}
		const int tileHeightSb = (sbRows + (1 << frameHdr->tile_info.TileRowsLog2) - 1) >> frameHdr->tile_info.TileRowsLog2;
		i = 0;
		for (startSb = 0; startSb < sbRows; startSb += tileHeightSb)
		{
			frameHdr->tile_info.MiRowStarts[i] = startSb << sbShift;
			i += 1;
		}
		frameHdr->tile_info.MiRowStarts[i] = frameHdr->MiRows;
		frameHdr->tile_info.TileRows = i;
	}
	else
	{
		int widestTileSb = 0;
		startSb = 0;
		int i;
		for (i = 0; startSb < sbCols; i++)
		{
			frameHdr->tile_info.MiColStarts[i] = startSb << sbShift;
			const int maxWidth = Min(sbCols - startSb, maxTileWidthSb);
			frameHdr->tile_info.width_in_sbs = readns(bs, maxWidth) + 1;
			// const int sizeSb = width_in_sbs_minus_1 + 1;
			widestTileSb = Max(frameHdr->tile_info.width_in_sbs, widestTileSb);

			startSb += frameHdr->tile_info.width_in_sbs;
		}
		frameHdr->tile_info.MiColStarts[i] = frameHdr->MiCols;
		frameHdr->tile_info.TileCols = i;
		frameHdr->tile_info.TileColsLog2 = tile_log2(1, frameHdr->tile_info.TileCols);
		if (minLog2Tiles > 0)
			maxTileAreaSb = (sbRows * sbCols) >> (minLog2Tiles + 1);
		else
			maxTileAreaSb = sbRows * sbCols;
		const int maxTileHeightSb = Max(maxTileAreaSb / widestTileSb, 1);

		startSb = 0;
		for (i = 0; startSb < sbRows; i++)
		{
			frameHdr->tile_info.MiRowStarts[i] = startSb << sbShift;
			const int maxHeight = Min(sbRows - startSb, maxTileHeightSb);
			frameHdr->tile_info.height_in_sbs = readns(bs, maxHeight) + 1;
			startSb += frameHdr->tile_info.height_in_sbs;
		}
		frameHdr->tile_info.MiRowStarts[i] = frameHdr->MiRows;
		frameHdr->tile_info.TileRows = i;
		frameHdr->tile_info.TileRowsLog2 = tile_log2(1, frameHdr->tile_info.TileRows);
	}
	if (frameHdr->tile_info.TileColsLog2 > 0 || frameHdr->tile_info.TileRowsLog2 > 0)
	{
		frameHdr->tile_info.context_update_tile_id = readBits(bs,
															  frameHdr->tile_info.TileRowsLog2 + frameHdr->tile_info.TileColsLog2);

		frameHdr->tile_info.TileSizeBytes = readBits(bs, 2) + 1;
	}
	else
	{
		frameHdr->tile_info.context_update_tile_id = 0;
	}
}
int frame::readQuantizationParams(bitSt *bs, sequenceHeader *seqHdr, frameHeader *frameHdr)
{
	frameHdr->quantization_params.base_q_idx = readBits(bs, 8);

	frameHdr->quantization_params.DeltaQYDc = readOneBit(bs) ? readsu(bs, 7) : 0;
	if (seqHdr->color_config.NumPlanes > 1)
	{
		int diff_uv_delta;//为1表示u和v的量化参数是分开的
		if (seqHdr->color_config.separate_uv_delta_q)
			diff_uv_delta = readOneBit(bs);
		else
			diff_uv_delta = 0;
		frameHdr->quantization_params.DeltaQUDc = readOneBit(bs) ? readsu(bs, 7) : 0;//read_delta_q(bs);
		frameHdr->quantization_params.DeltaQUAc = readOneBit(bs) ? readsu(bs, 7) : 0;
		    printf(" DeltaQUDc %d DeltaQUAc %d\n",frameHdr->quantization_params.DeltaQUDc,frameHdr->quantization_params.DeltaQUAc);
		if (diff_uv_delta)
		{
			frameHdr->quantization_params.DeltaQVDc = readOneBit(bs) ? readsu(bs, 7) : 0;
			frameHdr->quantization_params.DeltaQVAc = readOneBit(bs) ? readsu(bs, 7) : 0;
			printf(" DeltaQVDc %d DeltaQVAc %d\n",frameHdr->quantization_params.DeltaQVDc,frameHdr->quantization_params.DeltaQVAc);
		}
		else
		{
			frameHdr->quantization_params.DeltaQVDc = frameHdr->quantization_params.DeltaQUDc;
			frameHdr->quantization_params.DeltaQVAc = frameHdr->quantization_params.DeltaQUAc;
		}
	}
	else
	{
		frameHdr->quantization_params.DeltaQUDc = 0;
		frameHdr->quantization_params.DeltaQUAc = 0;
		frameHdr->quantization_params.DeltaQVDc = 0;
		frameHdr->quantization_params.DeltaQVAc = 0;
	}

	frameHdr->quantization_params.using_qmatrix = readOneBit(bs);
	if (frameHdr->quantization_params.using_qmatrix)
	{
		frameHdr->quantization_params.qm_y = readBits(bs, 4);
		frameHdr->quantization_params.qm_u = readBits(bs, 4);

		if (!seqHdr->color_config.separate_uv_delta_q)
			frameHdr->quantization_params.qm_v = frameHdr->quantization_params.qm_u;
		else
			frameHdr->quantization_params.qm_v = readBits(bs, 4);
	}
}
//segmentation， dav1d的代码怎么和spec 对不上？ 官方libaom是能对上的
int frame::readSegmentationParams(bitSt *bs, sequenceHeader *seqHdr, frameHeader *frameHdr)
{
	frameHdr->segmentation_params.segmentation_enabled = readOneBit(bs);
	if (frameHdr->segmentation_params.segmentation_enabled == 1)
	{
		if (frameHdr->primary_ref_frame == PRIMARY_REF_NONE)
		{
			frameHdr->segmentation_params.segmentation_update_map = 1 ;
			frameHdr->segmentation_params.segmentation_temporal_update = 0;
			frameHdr->segmentation_params.segmentation_update_data = 1;
		}
		else
		{
			frameHdr->segmentation_params.segmentation_update_map = readOneBit(bs);
			if (frameHdr->segmentation_params.segmentation_update_map == 1)
				frameHdr->segmentation_params.segmentation_temporal_update = readOneBit(bs);
			frameHdr->segmentation_params.segmentation_update_data = readOneBit(bs);
		}
		if (frameHdr->segmentation_params.segmentation_update_data == 1)
		{
			for (int i = 0; i < MAX_SEGMENTS; i++)
			{
				for (int j = 0; j < SEG_LVL_MAX; j++)
				{
					frameHdr->segmentation_params.FeatureData[i][j] = 0;
					frameHdr->segmentation_params.FeatureEnabled[i][j] = readOneBit(bs);
					int clippedValue = 0 ;
					if (frameHdr->segmentation_params.FeatureEnabled[i][j]  == 1)
					{
						int bitsToRead = Segmentation_Feature_Bits[j];
						int limit = Segmentation_Feature_Max[j];
						int tmp;
						if (Segmentation_Feature_Signed[j] == 1)
						{
							tmp = readsu(bs,1 + bitsToRead);// su(1 + bitsToRead);
							clippedValue = Clip3(-limit, limit, tmp);
						}else{
							tmp = readBits(bs, bitsToRead); //f(bitsToRead)
							clippedValue = Clip3(0, limit, tmp);
						}
					}
					frameHdr->segmentation_params.FeatureData[i][j] = clippedValue;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_SEGMENTS; i++)
		{
			for (int j = 0; j < SEG_LVL_MAX; j++)
			{
				frameHdr->segmentation_params.FeatureEnabled[i][j] = 0 ;
				frameHdr->segmentation_params.FeatureData[i][j] = 0;
			}
		}
	}
	frameHdr->segmentation_params.SegIdPreSkip = 0;
	frameHdr->segmentation_params.LastActiveSegId = 0;
	for (int i = 0; i < MAX_SEGMENTS; i++)
	{
		for (int j = 0; j < SEG_LVL_MAX; j++)
		{
			if (frameHdr->segmentation_params.FeatureEnabled[i][j])
			{
				frameHdr->segmentation_params.LastActiveSegId = i;
				if (j >= SEG_LVL_REF_FRAME)
				{
					frameHdr->segmentation_params.SegIdPreSkip = 1;
				}
			}
		}
	}
}
int frame::readLoopFilterParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader){

	if ( frameHdr->CodedLossless || frameHdr->allow_intrabc ) {
			frameHdr->loop_filter_params.loop_filter_level[ 0 ] = 0;
			frameHdr->loop_filter_params.loop_filter_level[ 1 ] = 0;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ INTRA_FRAME ] = 1;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ LAST_FRAME ] = 0;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ LAST2_FRAME ] = 0;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ LAST3_FRAME ] = 0;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ BWDREF_FRAME ] = 0;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ GOLDEN_FRAME ] = -1;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ ALTREF_FRAME ] = -1;
			frameHdr->loop_filter_params.loop_filter_ref_deltas[ ALTREF2_FRAME ] = -1;
		for (int i = 0; i < 2; i++ ) {
			frameHdr->loop_filter_params.loop_filter_mode_deltas[ i ] = 0;
		}
		return 0;
	}

	frameHdr->loop_filter_params.loop_filter_level[ 0 ] = readBits(bs, 6);// f(6)
	frameHdr->loop_filter_params.loop_filter_level[ 1 ] = readBits(bs, 6);// f(6)
	if ( seqHeader->color_config.NumPlanes > 1 ) {
		if ( frameHdr->loop_filter_params.loop_filter_level[ 0 ] || frameHdr->loop_filter_params.loop_filter_level[ 1 ] ) {
			frameHdr->loop_filter_params.loop_filter_level[ 2 ] = readBits(bs, 6);//f(6)
			frameHdr->loop_filter_params.loop_filter_level[ 3 ] = readBits(bs, 6);//f(6)
		}
	}
	printf("loop_filter_level %d %d %d %d\n",frameHdr->loop_filter_params.loop_filter_level[0],
				frameHdr->loop_filter_params.loop_filter_level[1],frameHdr->loop_filter_params.loop_filter_level[2],frameHdr->loop_filter_params.loop_filter_level[3]);
	frameHdr->loop_filter_params.loop_filter_sharpness = readBits(bs, 3); // f(3)
	frameHdr->loop_filter_params.loop_filter_delta_enabled = readOneBit(bs); //f(1)
	if ( frameHdr->loop_filter_params.loop_filter_delta_enabled == 1 ) {
		frameHdr->loop_filter_params.loop_filter_delta_update = readOneBit(bs);// f(1)
			if ( frameHdr->loop_filter_params.loop_filter_delta_update == 1 ) {
				for (int i = 0; i < TOTAL_REFS_PER_FRAME; i++ ) {
					int update_ref_delta = readOneBit(bs);// f(1)
					if (update_ref_delta )
						frameHdr->loop_filter_params.loop_filter_ref_deltas[ i ] = readsu(bs, 1 + 6); //su(1+6)
				}
				for (int  i = 0; i < 2; i++ ) {
					int update_mode_delta = readOneBit(bs);//f(1)
					if ( update_mode_delta )
						frameHdr->loop_filter_params.loop_filter_mode_deltas[ i ] = readsu(bs, 1 + 6);//su(1+6)
				}

		}
	}
    for(int i  =0 ; i < 8 ; i++){
		printf(" %d ",frameHdr->loop_filter_params.loop_filter_ref_deltas[ i ]);
       
    }
    printf("\n");
    for(int i  =0 ; i < 2 ; i++){
         printf(" %d ",frameHdr->loop_filter_params.loop_filter_mode_deltas[ i ]);
    }

}
int frame::readCdefParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader)
{
	if ( frameHdr->CodedLossless || frameHdr->allow_intrabc || !seqHeader->enable_cdef) {
		frameHdr->cdef_params.cdef_bits = 0;
		frameHdr->cdef_params.cdef_y_pri_strength[0] = 0;
		frameHdr->cdef_params.cdef_y_sec_strength[0] = 0;
		frameHdr->cdef_params.cdef_uv_pri_strength[0] = 0;
		frameHdr->cdef_params.cdef_uv_sec_strength[0] = 0;
		frameHdr->cdef_params.CdefDamping = 3;
		return 0;
	}
	frameHdr->cdef_params.CdefDamping = readBits(bs, 2) + 3;
	frameHdr->cdef_params.cdef_bits = readBits(bs, 2);
	for (int i = 0; i < (1 << frameHdr->cdef_params.cdef_bits); i++ ) {
		frameHdr->cdef_params.cdef_y_pri_strength[i] = readBits(bs, 4);
		frameHdr->cdef_params.cdef_y_sec_strength[i] = readBits(bs, 2);
		if ( frameHdr->cdef_params.cdef_y_sec_strength[i] == 3 )
			frameHdr->cdef_params.cdef_y_sec_strength[i] += 1;
		if ( seqHeader->color_config.NumPlanes > 1 ) {
			frameHdr->cdef_params.cdef_uv_pri_strength[i] = readBits(bs, 4);
			frameHdr->cdef_params.cdef_uv_sec_strength[i] = readBits(bs, 2);
			if ( frameHdr->cdef_params.cdef_uv_sec_strength[i] == 3 )
				frameHdr->cdef_params.cdef_uv_sec_strength[i] += 1;

		}
	}

	return 0;
}
int frame::readLrParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader){
	if ( frameHdr->AllLossless || frameHdr->allow_intrabc || !seqHeader->enable_restoration ) {
		frameHdr->lr_params.FrameRestorationType[0] = RESTORE_NONE;
		frameHdr->lr_params.FrameRestorationType[1] = RESTORE_NONE;
		frameHdr->lr_params.FrameRestorationType[2] = RESTORE_NONE;
		frameHdr->lr_params.UsesLr = 0;
		return 0;
	}
	frameHdr->lr_params.UsesLr = 0;
	int usesChromaLr = 0;
	for (int  i = 0; i < seqHeader->color_config.NumPlanes; i++ ) {
		frameHdr->lr_params.lr_type[i]  = readBits(bs, 2);
		frameHdr->lr_params.FrameRestorationType[i] = Remap_Lr_Type[frameHdr->lr_params.lr_type[i]];
		if ( frameHdr->lr_params.FrameRestorationType[i] != RESTORE_NONE ) {
			frameHdr->lr_params.UsesLr = 1;
			if ( i > 0 ) {
				usesChromaLr = 1;
			}
		}
	}
	if ( frameHdr->lr_params.UsesLr ) {
		if ( seqHeader->use_128x128_superblock ) {
			frameHdr->lr_params.lr_unit_shift = readOneBit(bs);
		frameHdr->lr_params.lr_unit_shift++;
	} else {
		frameHdr->lr_params.lr_unit_shift  = readOneBit(bs);
		if ( frameHdr->lr_params.lr_unit_shift ) {
			frameHdr->lr_params.lr_unit_extra_shift  = readOneBit(bs);
			frameHdr->lr_params.lr_unit_shift += frameHdr->lr_params.lr_unit_extra_shift;
		}
	}
	frameHdr->lr_params.LoopRestorationSize[ 0 ] = RESTORATION_TILESIZE_MAX >> (2 - frameHdr->lr_params.lr_unit_shift);
	if ( seqHeader->color_config.subsampling_x && seqHeader->color_config.subsampling_y && usesChromaLr ) {
		frameHdr->lr_params.lr_uv_shift  = readOneBit(bs);
	} else {
		frameHdr->lr_params.lr_uv_shift = 0;
	}
		frameHdr->lr_params.LoopRestorationSize[ 1 ] = frameHdr->lr_params.LoopRestorationSize[ 0 ] >> frameHdr->lr_params.lr_uv_shift;
		frameHdr->lr_params.LoopRestorationSize[ 2 ] = frameHdr->lr_params.LoopRestorationSize[ 0 ] >> frameHdr->lr_params.lr_uv_shift;
	}


}
int frame::readSkipModeParams(bitSt *bs, frameHeader *frameHdr,AV1DecodeContext *av1Ctx,sequenceHeader *seqHeader)
{
	if ( frameHdr->FrameIsIntra || !frameHdr->reference_select || !seqHeader->enable_order_hint ) {
		frameHdr->skipModeAllowed = 0;
	} else {
		int forwardIdx = -1;
		int backwardIdx = -1;
		int refHint;
		int forwardHint;
		int backwardHint;
		int secondForwardIdx;
		int secondForwardHint;
		for (int  i = 0; i < REFS_PER_FRAME; i++ ) {
			refHint = av1Ctx->RefOrderHint[ frameHdr->ref_frame_idx[ i ] ];
			if ( get_relative_dist( seqHeader->enable_order_hint,seqHeader->OrderHintBits ,refHint, frameHdr->OrderHint ) < 0 ) {
				if ( forwardIdx < 0 ||get_relative_dist(seqHeader->enable_order_hint,seqHeader->OrderHintBits ,  refHint, forwardHint) > 0 ) {
					forwardIdx = i;
					forwardHint = refHint;
				}
			} else if ( get_relative_dist(seqHeader->enable_order_hint,seqHeader->OrderHintBits ,  refHint, frameHdr->OrderHint) > 0 ) {
				if ( backwardIdx < 0 || get_relative_dist(seqHeader->enable_order_hint,seqHeader->OrderHintBits ,  refHint, backwardHint) < 0 ) {
					backwardIdx = i;
					backwardHint = refHint;
				}
			}
		}
		if ( forwardIdx < 0 ) {
			frameHdr->skipModeAllowed = 0;
		} else if ( backwardIdx >= 0 ) {
			frameHdr->skipModeAllowed = 1;
			frameHdr->SkipModeFrame[ 0 ] = LAST_FRAME + Min(forwardIdx, backwardIdx);
			frameHdr->SkipModeFrame[ 1 ] = LAST_FRAME + Max(forwardIdx, backwardIdx);
		} else {
			secondForwardIdx = -1;
			for (int i = 0; i < REFS_PER_FRAME; i++ ) {
				refHint = av1Ctx->RefOrderHint[ frameHdr->ref_frame_idx[ i ] ];
				if ( get_relative_dist(seqHeader->enable_order_hint,seqHeader->OrderHintBits , refHint, forwardHint ) < 0 ) {
					if ( secondForwardIdx < 0 || get_relative_dist(seqHeader->enable_order_hint,seqHeader->OrderHintBits , refHint, secondForwardHint ) > 0 ) {
						secondForwardIdx = i;
						secondForwardHint = refHint;
					}
				}
			}
			if ( secondForwardIdx < 0 ) {
				frameHdr->skipModeAllowed = 0;
			} else {
				frameHdr->skipModeAllowed = 1;
				frameHdr->SkipModeFrame[ 0 ] = LAST_FRAME + Min(forwardIdx, secondForwardIdx);
				frameHdr->SkipModeFrame[ 1 ] = LAST_FRAME + Max(forwardIdx, secondForwardIdx);
			}
		}
	}
	if ( frameHdr->skipModeAllowed ) {
		frameHdr->skip_mode_present =  readOneBit(bs); 
	} else {
		frameHdr->skip_mode_present = 0;
	}


}
int frame::readGlobalMotionParams(bitSt *bs, frameHeader *frameHdr)
{
	
	for (int  ref = LAST_FRAME; ref <= ALTREF_FRAME; ref++ ) {
		frameHdr->global_motion_params.GmType[ ref ] = IDENTITY;
		for (int  i = 0; i < 6; i++ ) {
			frameHdr->global_motion_params.gm_params[ ref ][ i ] = ( ( i % 3 == 2 ) ? 1 << WARPEDMODEL_PREC_BITS : 0 );
		}
	}
	if ( frameHdr->FrameIsIntra )
		return 0;

	int type;
	for (int  ref = LAST_FRAME; ref <= ALTREF_FRAME; ref++ ) {
		frameHdr->global_motion_params.is_global = readOneBit(bs);
		if ( frameHdr->global_motion_params.is_global ) {
			frameHdr->global_motion_params.is_rot_zoom= readOneBit(bs);
			if ( frameHdr->global_motion_params.is_rot_zoom ) {
				type = ROTZOOM;
			} else {
				frameHdr->global_motion_params.is_translation= readOneBit(bs);
				type = frameHdr->global_motion_params.is_translation ? TRANSLATION : AFFINE;
			}
		} else {
			type = IDENTITY;
		}
		frameHdr->global_motion_params.GmType[ref] = type;
		if ( type >= ROTZOOM ) {
			read_global_param(frameHdr,bs,type,ref,2);
			read_global_param(frameHdr,bs,type,ref,3);
			if ( type == AFFINE ) {
				read_global_param(frameHdr,bs,type,ref,4);
				read_global_param(frameHdr,bs,type,ref,5);
			} else {
				frameHdr->global_motion_params.gm_params[ref][4] = -frameHdr->global_motion_params.gm_params[ref][3];
				frameHdr->global_motion_params.gm_params[ref][5] = frameHdr->global_motion_params.gm_params[ref][2];
			}
		}
		if ( type >= TRANSLATION ) {
			read_global_param(frameHdr,bs,type,ref,0);
			read_global_param(frameHdr,bs,type,ref,1);
		}
	}
}

int frame::readFilmGrainParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHdr,AV1DecodeContext *av1Ctx)
{
	if ( !seqHdr->film_grain_params_present ||(!frameHdr->show_frame && !frameHdr->showable_frame) ) {
		//reset_grain_params();
		memset(&frameHdr->film_grain_params, 0,sizeof(frameHdr->film_grain_params));
		return 0;
	}
	if ( !readOneBit(bs)/*apply_grain*/ ) {
		//reset_grain_params();
		memset(&frameHdr->film_grain_params, 0,sizeof(frameHdr->film_grain_params));
		return 0;
	}
	frameHdr->film_grain_params.grain_seed = readBits(bs, 16);
	if ( frameHdr->frame_type == INTER_FRAME )
		frameHdr->film_grain_params.update_grain = readOneBit(bs);
	else
		frameHdr->film_grain_params.update_grain = 1;

	if ( !frameHdr->film_grain_params.update_grain ) {
		frameHdr->film_grain_params.film_grain_params_ref_idx = readBits(bs, 3);// f(3)
		int tempGrainSeed = frameHdr->film_grain_params.grain_seed;
		decode_instance->load_grain_params(av1Ctx, frameHdr->film_grain_params.film_grain_params_ref_idx );
		frameHdr->film_grain_params.grain_seed = tempGrainSeed;
		return 0;
	}
	frameHdr->film_grain_params.num_y_points =  readBits(bs, 4);
	for (int i = 0; i < frameHdr->film_grain_params.num_y_points; i++ ) {
		frameHdr->film_grain_params.point_y_value[ i ] = readBits(bs, 8);// f(8)
		frameHdr->film_grain_params.point_y_scaling[ i ] = readBits(bs, 8);// f(8)
	}
	if ( seqHdr->color_config.mono_chrome ) {
		frameHdr->film_grain_params.chroma_scaling_from_luma = 0;
	} else {
		frameHdr->film_grain_params.chroma_scaling_from_luma = readOneBit(bs);
	}

	if ( seqHdr->color_config.mono_chrome || frameHdr->film_grain_params.chroma_scaling_from_luma || 
		( seqHdr->color_config.subsampling_x == 1 && seqHdr->color_config.subsampling_y == 1 && frameHdr->film_grain_params.num_y_points == 0 ))
	{
		frameHdr->film_grain_params.num_cb_points = 0;
		frameHdr->film_grain_params.num_cr_points = 0;
	} else {
		frameHdr->film_grain_params.num_cb_points = readBits(bs, 4);
		for (int i = 0; i < frameHdr->film_grain_params.num_cb_points; i++ ) {
			frameHdr->film_grain_params.point_cb_value[ i ] = readBits(bs, 8); 
			frameHdr->film_grain_params.point_cb_scaling[ i ] = readBits(bs, 8);
		}
		frameHdr->film_grain_params.num_cr_points = readBits(bs, 4);
		for (int i = 0; i < frameHdr->film_grain_params.num_cr_points; i++ ) {
			frameHdr->film_grain_params.point_cr_value[ i ] = readBits(bs, 8);
			frameHdr->film_grain_params.point_cr_scaling[ i ] = readBits(bs, 8);
		}
	}

	frameHdr->film_grain_params.grain_scaling = readBits(bs, 2) + 8;
	frameHdr->film_grain_params.ar_coeff_lag = readBits(bs, 2);
	int numPosLuma = 2 * frameHdr->film_grain_params.ar_coeff_lag * ( frameHdr->film_grain_params.ar_coeff_lag + 1 );
	int numPosChroma;
	if ( frameHdr->film_grain_params.num_y_points ) {
		numPosChroma = numPosLuma + 1;
		for (int  i = 0; i < numPosLuma; i++ )
			frameHdr->film_grain_params.ar_coeffs_y_plus_128[ i ] = readBits(bs, 8);
	} else {
		numPosChroma = numPosLuma;
	}
	if ( frameHdr->film_grain_params.chroma_scaling_from_luma || frameHdr->film_grain_params.num_cb_points ) {
		for (int i = 0; i < numPosChroma; i++ )
			frameHdr->film_grain_params.ar_coeffs_cb_plus_128[ i ] = readBits(bs, 8);
	}
	if ( frameHdr->film_grain_params.chroma_scaling_from_luma || frameHdr->film_grain_params.num_cr_points ) {
		for (int i = 0; i < numPosChroma; i++ )
			frameHdr->film_grain_params.ar_coeffs_cr_plus_128[ i ] = readBits(bs, 8);
	}
	frameHdr->film_grain_params.ar_coeff_shift =  readBits(bs, 2) + 6;
	frameHdr->film_grain_params.grain_scale_shift = readBits(bs, 2);

	if ( frameHdr->film_grain_params.num_cb_points ) {
		frameHdr->film_grain_params.cb_mult = readBits(bs, 8);
		frameHdr->film_grain_params.cb_luma_mult = readBits(bs, 8);
		frameHdr->film_grain_params.cb_offset = readBits(bs, 9);
	}
	if ( frameHdr->film_grain_params.num_cr_points ) {
		frameHdr->film_grain_params.cr_mult = readBits(bs, 8);
		frameHdr->film_grain_params.cr_luma_mult = readBits(bs, 8);
		frameHdr->film_grain_params.cr_offset = readBits(bs, 9);
	}
	frameHdr->film_grain_params.overlap_flag = readOneBit(bs);
	frameHdr->film_grain_params.clip_to_restricted_range = readOneBit(bs);

}


int frame::readDeltaQuantizerParams(bitSt *bs, frameHeader *frameHdr)
{
	frameHdr->delta_q_params.delta_q_res = 0;
	frameHdr->delta_q_params.delta_q_present = 0;

	if (frameHdr->quantization_params.base_q_idx > 0)
	{
		frameHdr->delta_q_params.delta_q_present = readOneBit(bs);
	}
	if (frameHdr->delta_q_params.delta_q_present)
	{
		frameHdr->delta_q_params.delta_q_res = readBits(bs, 2);
	}
	return 0;
}

int frame::readDeltaLoopfilterParams(bitSt *bs, frameHeader *frameHdr)
{
	frameHdr->delta_lf_params.delta_lf_present = 0;
	frameHdr->delta_lf_params.delta_lf_res = 0;
	frameHdr->delta_lf_params.delta_lf_multi = 0;
	if (frameHdr->delta_q_params.delta_q_present)
	{
		if (!frameHdr->allow_intrabc)
			frameHdr->delta_lf_params.delta_lf_present = readOneBit(bs);
		if (frameHdr->delta_lf_params.delta_lf_present)
		{
			frameHdr->delta_lf_params.delta_lf_res = readBits(bs, 2);
			frameHdr->delta_lf_params.delta_lf_multi = readOneBit(bs);
		}
	}
	return 0;
}

int frame::read_interpolation_filter(bitSt *bs, frameHeader *frameHdr)
{
	frameHdr->is_filter_switchable = readOneBit(bs);
	if (frameHdr->is_filter_switchable)
	{
		frameHdr->interpolation_filter = SWITCHABLE;
	}
	else
	{
		frameHdr->interpolation_filter = readBits(bs, 2);
	}
}

int frame::readSuperresParams(bitSt *bs, sequenceHeader *seqHdr, sizeInfo *si)
{
	if (seqHdr->enable_superres)
		si->use_superres = readOneBit(bs);
	else
		si->use_superres = 0;

	if (si->use_superres)
	{
		si->SuperresDenom = readBits(bs, SUPERRES_DENOM_BITS) + SUPERRES_DENOM_MIN;
	}
	else
	{
		si->SuperresDenom = SUPERRES_NUM;
	}
	si->UpscaledWidth = si->FrameWidth;

	
	si->FrameWidth = (si->UpscaledWidth * SUPERRES_NUM +
					  (si->SuperresDenom / 2)) /
					 si->SuperresDenom;

	return 0;
}
int frame::readFrameSize(bitSt *bs, sequenceHeader *seqHdr, frameHeader *frameHdr, sizeInfo *out)
{
	if (frameHdr->frame_size_override_flag)
	{

		out->FrameWidth = readBits(bs, seqHdr->frame_width_bits) + 1;
		out->FrameHeight = readBits(bs, seqHdr->frame_height_bits) + 1;
	}
	else
	{
		out->FrameWidth = seqHdr->max_frame_width;
		out->FrameHeight = seqHdr->max_frame_height;
	}
	//printf("FrameWidth %d\n",out->FrameWidth);
	//printf("FrameHeight %d\n",out->FrameHeight);
	readSuperresParams(bs, seqHdr, out);

	// compute image size;
	frameHdr->MiCols = 2 * ((out->FrameWidth + 7) >> 3);
	frameHdr->MiRows = 2 * ((out->FrameHeight + 7) >> 3);
	return 0;
}

int frame::readRenderSize(bitSt *bs, sequenceHeader *seqHdr, frameHeader *frameHdr, sizeInfo *out)
{
	out->render_and_frame_size_different = readOneBit(bs);
	if (out->render_and_frame_size_different == 1)
	{
		out->RenderWidth = readBits(bs, 16) + 1;
		out->RenderHeight = readBits(bs, 16) + 1;
	}
	else
	{
		out->RenderWidth = out->UpscaledWidth;
		out->RenderHeight = out->FrameHeight;
	}
}

int frame::read_delta_q(bitSt *bs)
{
	int delta_coded = readOneBit(bs);
	int delta_q;
	if (delta_coded)
	{
		delta_q = readBits(bs, 1 + 6);
	}
	else
	{
		delta_q = 0;
	}
	return delta_q;
}
int frame::read_global_param(frameHeader *frameHdr,bitSt *bs, int type,int ref,int idx ) { 
	int absBits = GM_ABS_ALPHA_BITS;
	int precBits = GM_ALPHA_PREC_BITS;
	if ( idx < 2 ) {
		if ( type == TRANSLATION ) {
			absBits = GM_ABS_TRANS_ONLY_BITS - !frameHdr->allow_high_precision_mv;
			precBits = GM_TRANS_ONLY_PREC_BITS - !frameHdr->allow_high_precision_mv;
		} else {
			absBits = GM_ABS_TRANS_BITS;
			precBits = GM_TRANS_PREC_BITS;
		}
	}
	int precDiff = WARPEDMODEL_PREC_BITS - precBits;

	int round = (idx % 3) == 2 ? (1 << WARPEDMODEL_PREC_BITS) : 0;
	int sub = (idx % 3) == 2 ? (1 << precBits) : 0;
	int mx = (1 << absBits);
	int r = (frameHdr->global_motion_params.PrevGmParams[ref][idx] >> precDiff) - sub;
	frameHdr->global_motion_params.gm_params[ref][idx] = (decode_signed_subexp_with_ref(bs, -mx, mx + 1, r )<< precDiff) + round;
}

void frame::allocDecodeContext(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int use_superblock = seqHdr->use_128x128_superblock;
	int WBuffMiSize;
	int HBuffMiSize;
	if(use_superblock){
		WBuffMiSize = (frameHdr->MiCols % 32) ? (frameHdr->MiCols / 32 + 1) * 32 : (frameHdr->MiCols / 32) * 32;
		HBuffMiSize = (frameHdr->MiRows % 32) ? (frameHdr->MiRows / 32 + 1) * 32 : (frameHdr->MiRows / 32) * 32;
	}else{
		WBuffMiSize = (frameHdr->MiCols % 16) ? (frameHdr->MiCols / 16 + 1) * 16 : (frameHdr->MiCols / 16) * 16;
		HBuffMiSize = (frameHdr->MiRows % 16) ? (frameHdr->MiRows / 16 + 1) * 16 : (frameHdr->MiRows / 16) * 16;
	}
	printf("WBuffMiSize %d HBuffMiSize %d \n",WBuffMiSize,HBuffMiSize);
	allocFrameContext(frameHdr,WBuffMiSize,HBuffMiSize,&av1Ctx->currentFrame);
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		allocFrameContext(frameHdr,WBuffMiSize,HBuffMiSize,&av1Ctx->ref_frames[i]);
	}

	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		for(int j = 0 ; j < 3 ; j ++){
			av1Ctx->FrameStore[i][j] = new uint16_t*[HBuffMiSize  * MI_SIZE];
			for(int k = 0 ; k < HBuffMiSize  * MI_SIZE ; k++){
				int w = frameHdr->si.UpscaledWidth > (WBuffMiSize * MI_SIZE) ? frameHdr->si.UpscaledWidth : (WBuffMiSize * MI_SIZE);
				av1Ctx->FrameStore[i][j][k] = new uint16_t[w];
			}
		}
	}
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		av1Ctx->SavedRefFrames[i] = new uint8_t*[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize ; j++){
			av1Ctx->SavedRefFrames[i][j] = new uint8_t[WBuffMiSize];
		}
	}
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		av1Ctx->SavedMvs[i] = new int**[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize ; j++){
			av1Ctx->SavedMvs[i][j] = new int*[WBuffMiSize];
			for(int k = 0 ; k < WBuffMiSize ;k ++){
				av1Ctx->SavedMvs[i][j][k] = new int[2];
			}
			
		}
	}
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		av1Ctx->SavedSegmentIds[i] = new uint8_t*[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize ; j++){
			av1Ctx->SavedSegmentIds[i][j] = new uint8_t[WBuffMiSize];
		}
	}

	av1Ctx->RefUpscaledWidth = new Array16(NUM_REF_FRAMES);
	av1Ctx->RefFrameWidth = new Array16(NUM_REF_FRAMES);
	av1Ctx->RefFrameHeight = new Array16(NUM_REF_FRAMES);
	av1Ctx->RefRenderWidth = new Array16(NUM_REF_FRAMES);
	av1Ctx->RefRenderHeight = new Array16(NUM_REF_FRAMES);

	av1Ctx->BlockDecoded = new tArray8(3,HBuffMiSize,WBuffMiSize);
	for(int i = 0 ; i < 3 ; i ++){
		av1Ctx->LoopfilterTxSizes[i] = new uint8_t*[HBuffMiSize];
		for(int j  = 0 ; j < HBuffMiSize ; j ++){
			av1Ctx->LoopfilterTxSizes[i][j] = new uint8_t[WBuffMiSize];
		}
		av1Ctx->AboveLevelContext[i] = new int[WBuffMiSize];
		av1Ctx->AboveDcContext[i] = new int[WBuffMiSize];
		av1Ctx->LeftLevelContext[i] = new int[HBuffMiSize];
		av1Ctx->LeftDcContext[i] = new int[HBuffMiSize];
	}
	av1Ctx->AboveSegPredContext = new int[WBuffMiSize];
	av1Ctx->LeftSegPredContext = new int[HBuffMiSize];

	av1Ctx->YModes = new uint8_t*[HBuffMiSize];
	av1Ctx->UVModes = new uint8_t*[HBuffMiSize];
	av1Ctx->CompGroupIdxs = new uint8_t*[HBuffMiSize];
	av1Ctx->CompoundIdxs = new uint8_t*[HBuffMiSize];
	av1Ctx->MiSizes = new uint8_t*[HBuffMiSize];
	av1Ctx->SegmentIds = new uint8_t*[HBuffMiSize];
	av1Ctx->IsInters = new uint8_t*[HBuffMiSize];
	av1Ctx->SkipModes = new uint8_t*[HBuffMiSize];
	av1Ctx->Skips = new uint8_t*[HBuffMiSize];
	av1Ctx->TxSizes = new uint8_t*[HBuffMiSize];
	av1Ctx->InterTxSizes = new uint8_t*[HBuffMiSize];
	for(int i = 0 ; i < HBuffMiSize ; i++){
		av1Ctx->YModes[i] = new uint8_t[WBuffMiSize];
		av1Ctx->UVModes[i] = new uint8_t[WBuffMiSize];
		av1Ctx->CompGroupIdxs[i] = new uint8_t[WBuffMiSize];
		av1Ctx->CompoundIdxs[i] = new uint8_t[WBuffMiSize];
		av1Ctx->MiSizes[i] = new uint8_t[WBuffMiSize];
		av1Ctx->SegmentIds[i] = new uint8_t[WBuffMiSize];
		av1Ctx->IsInters[i] = new uint8_t[WBuffMiSize];
		av1Ctx->SkipModes[i] = new uint8_t[WBuffMiSize];
		av1Ctx->Skips[i] = new uint8_t[WBuffMiSize];
		av1Ctx->TxSizes[i] = new uint8_t[WBuffMiSize];
		av1Ctx->InterTxSizes[i] = new uint8_t[WBuffMiSize];
	}

	for(int i = 0 ; i < 2 ; i++){

		av1Ctx->PaletteSizes[i] = new uint8_t*[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize ; j++){
			av1Ctx->PaletteSizes[i][j] = new uint8_t[WBuffMiSize];
		}
	}
	av1Ctx->RefFrames = new int**[HBuffMiSize];
	av1Ctx->InterpFilters = new uint8_t**[HBuffMiSize];
	for(int i = 0 ; i < HBuffMiSize ; i++){
		av1Ctx->RefFrames[i] = new int*[WBuffMiSize];
		av1Ctx->InterpFilters[i] = new uint8_t*[WBuffMiSize];
		for(int j = 0 ; j < WBuffMiSize ; j++){
			av1Ctx->RefFrames[i][j] = new int[2];
			av1Ctx->InterpFilters[i][j] = new uint8_t[2];
		}
	}


	av1Ctx->DeltaLFs = new uint8_t**[HBuffMiSize];
	for(int i = 0 ; i < HBuffMiSize ; i++){
		av1Ctx->DeltaLFs[i] = new uint8_t*[WBuffMiSize];
		for(int j = 0 ; j < WBuffMiSize ; j++){
			av1Ctx->DeltaLFs[i][j] = new uint8_t[FRAME_LF_COUNT];
		}
	}
	
	for(int i = 0 ; i < 2 ; i++){
		av1Ctx->PaletteColors[i] = new uint8_t**[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize ; j++){
			av1Ctx->PaletteColors[i][j] = new uint8_t*[WBuffMiSize];
			for(int k = 0 ; k < WBuffMiSize ; k++){
				//av1Ctx->PaletteColors[i][j][k] = new uint8_t[b_data.PaletteSizeY];
				//PaletteColors 的内存 在 decode_block 中分配
			}
		}
	}
	av1Ctx->Mvs = new int***[HBuffMiSize];
	for(int i = 0 ; i < HBuffMiSize ; i++){
		av1Ctx->Mvs[i] = new int**[WBuffMiSize];
		for(int j = 0 ; j < WBuffMiSize ; j++){
			av1Ctx->Mvs[i][j] = new int*[2];
			for(int k  = 0 ; k < 2 ; k ++){
				av1Ctx->Mvs[i][j][k] = new int[2];
			}
		}
	}
	for(int i  = 0 ; i < 8 ; i++){
		av1Ctx->MotionFieldMvs[i] = new int**[HBuffMiSize >> 1];
		for(int j = 0 ; j < HBuffMiSize >> 1; j++ ){
			av1Ctx->MotionFieldMvs[i][j] = new int*[WBuffMiSize >> 1];
			for(int k = 0 ; k < WBuffMiSize >> 1 ;k ++){
				av1Ctx->MotionFieldMvs[i][j][k] = new int[2];
			}
		}
	}

	av1Ctx->TxTypes = new uint8_t*[HBuffMiSize];
	for(int i  = 0 ; i < HBuffMiSize ; i++){
		av1Ctx->TxTypes[i] = new uint8_t[WBuffMiSize];
	}


}
void frame::releaseDecodeContext(AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

	int WBuffMiSize;
	int HBuffMiSize;
	int use_superblock = seqHdr->use_128x128_superblock;
	if(use_superblock){
		WBuffMiSize = (frameHdr->MiCols % 32) ? (frameHdr->MiCols / 32 + 1) * 32 : (frameHdr->MiCols / 32) * 32;
		HBuffMiSize = (frameHdr->MiRows % 32) ? (frameHdr->MiRows / 32 + 1) * 32 : (frameHdr->MiRows / 32) * 32;
	}else{
		WBuffMiSize = (frameHdr->MiCols % 16) ? (frameHdr->MiCols / 16 + 1) * 16 : (frameHdr->MiCols / 16) * 16;
		HBuffMiSize = (frameHdr->MiRows % 16) ? (frameHdr->MiRows / 16 + 1) * 16 : (frameHdr->MiRows / 16) * 16;
	}
	releaseFrameContext(frameHdr,WBuffMiSize, HBuffMiSize,av1Ctx->currentFrame);
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		releaseFrameContext(frameHdr,WBuffMiSize, HBuffMiSize,av1Ctx->ref_frames[i]);
	}

	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		for(int j = 0 ; j < 3 ; j ++){
			for(int k = 0 ; k < frameHdr->si.FrameHeight ; k++){
				delete[]  av1Ctx->FrameStore[i][j][k];
			}
			delete[]  av1Ctx->FrameStore[i][j] ;
		}
	}
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		for(int j = 0 ; j < HBuffMiSize ; j++){
			delete[]  av1Ctx->SavedRefFrames[i][j] ;
		}
		delete[]  av1Ctx->SavedRefFrames[i];
	}
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		for(int j = 0 ; j < HBuffMiSize ; j++){
			for(int k = 0 ; k < WBuffMiSize ;k ++){
				delete[] av1Ctx->SavedMvs[i][j][k] ;
			}
			delete[]  av1Ctx->SavedMvs[i][j] ;
		}
		delete[]  av1Ctx->SavedMvs[i] ;
	}
	for(int i = 0 ; i < NUM_REF_FRAMES ; i ++){
		for(int j = 0 ; j < HBuffMiSize ; j++){
			delete[]  av1Ctx->SavedSegmentIds[i][j] ;
		}
		delete[] av1Ctx->SavedSegmentIds[i] ;
	}
	
	delete av1Ctx->RefUpscaledWidth ;
	delete av1Ctx->RefFrameWidth ;
	delete av1Ctx->RefFrameHeight ;
	delete av1Ctx->RefRenderWidth ;
	delete av1Ctx->RefRenderHeight ;

	delete av1Ctx->BlockDecoded;
	for(int i = 0 ; i < 3 ; i ++){
		
		for(int j  = 0 ; j < HBuffMiSize ; j ++){
			delete[] av1Ctx->LoopfilterTxSizes[i][j];
		}
		delete[]  av1Ctx->LoopfilterTxSizes[i];

		delete[]  av1Ctx->AboveLevelContext[i];
		delete[]  av1Ctx->AboveDcContext[i];
		delete[]  av1Ctx->LeftLevelContext[i];
		delete[]  av1Ctx->LeftDcContext[i];
	}
	delete [] av1Ctx->AboveSegPredContext;
	delete [] av1Ctx->LeftSegPredContext;
		

	for(int i = 0 ; i < HBuffMiSize ; i++){
		delete [] av1Ctx->YModes[i] ;
		delete []av1Ctx->UVModes[i] ;
		delete []av1Ctx->CompGroupIdxs[i] ;
		delete []av1Ctx->CompoundIdxs[i] ;
		delete []av1Ctx->MiSizes[i] ;
		delete []av1Ctx->SegmentIds[i] ;
		delete []av1Ctx->SkipModes[i] ;
		delete []av1Ctx->Skips[i] ;
		delete []av1Ctx->TxSizes[i]  ;
		delete []av1Ctx->InterTxSizes[i] ;
	}
	delete [] av1Ctx->YModes ;
	delete [] av1Ctx->UVModes ;
	delete [] av1Ctx->CompGroupIdxs ;
	delete [] av1Ctx->CompoundIdxs ;
	delete [] av1Ctx->MiSizes ;
	delete [] av1Ctx->SegmentIds ;
	delete [] av1Ctx->SkipModes ;
	delete [] av1Ctx->Skips ;
	delete [] av1Ctx->TxSizes ;
	delete [] av1Ctx->InterTxSizes ;

	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < HBuffMiSize ; j++){
			delete [] av1Ctx->PaletteSizes[i][j] ;
		}
		delete [] av1Ctx->PaletteSizes[i] ;	
	}

	for(int i = 0 ; i < HBuffMiSize ; i++){
		for(int j = 0 ; j < 2 ; j++){
			delete [] av1Ctx->RefFrames[i][j] ;
			delete [] av1Ctx->InterpFilters[i][j];
		}
		delete []av1Ctx->RefFrames[i] ;
		delete [] av1Ctx->InterpFilters[i];
	}
	delete [] av1Ctx->RefFrames ;
	delete [] av1Ctx->InterpFilters ;

	for(int i = 0 ; i < HBuffMiSize ; i++){
		for(int j = 0 ; j < WBuffMiSize ; j++){
			delete [] av1Ctx->DeltaLFs[i];
		}
		delete [] av1Ctx->DeltaLFs[i] ;
	}
	delete [] av1Ctx->DeltaLFs ;

	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < HBuffMiSize ; j++){
			for(int k = 0 ; k < WBuffMiSize ; k++){
				delete [] av1Ctx->PaletteColors[i][j][k] ;
			}
			delete [] av1Ctx->PaletteColors[i][j] ;
		}
		delete [] av1Ctx->PaletteColors[i];
	}
	
	
	for(int i = 0 ; i < HBuffMiSize ; i++){
		
		for(int j = 0 ; j < WBuffMiSize ; j++){
			
			for(int k  = 0 ; k < 2 ; k ++){
				delete [] av1Ctx->Mvs[i][j][k];
			}
			delete [] av1Ctx->Mvs[i][j];
		}
		delete [] av1Ctx->Mvs[i];
	}	
	delete [] av1Ctx->Mvs ;

	for(int i  = 0 ; i < 8 ; i++){
		for(int j = 0 ; j < HBuffMiSize >> 1; j++ ){
			for(int k = 0 ; k < WBuffMiSize >> 1 ;k ++){
				delete [] av1Ctx->MotionFieldMvs[i][j][k];
			}
			delete [] av1Ctx->MotionFieldMvs[i][j];
		}
		delete [] av1Ctx->MotionFieldMvs[i] ;
	}
	
	for(int i  = 0 ; i < HBuffMiSize ; i++){
		delete []  av1Ctx->PrevSegmentIds[i];
	}
	delete [] av1Ctx->PrevSegmentIds;
	for(int i  = 0 ; i < HBuffMiSize ; i++){
		delete []  av1Ctx->TxTypes[i];
	}
	delete [] av1Ctx->TxTypes;
}
//关于色度内存的分配还要再优化
void frame::allocFrameContext(frameHeader *frameHdr ,int WBuffMiSize,int HBuffMiSize,FrameContext **fCtx){
	*fCtx  = (FrameContext *)malloc(sizeof(FrameContext));
	FrameContext *fc = *fCtx;
	for(int i = 0 ; i < 3 ; i++){
		fc->CurrFrame[i] = new uint16_t*[HBuffMiSize  * MI_SIZE];
		fc->CdefFrame[i] = new uint16_t*[HBuffMiSize  * MI_SIZE];
		fc->UpscaledCdefFrame[i] = new uint16_t*[HBuffMiSize  * MI_SIZE];
		fc->UpscaledCurrFrame[i] = new uint16_t*[HBuffMiSize  * MI_SIZE];
		for(int j = 0 ; j < HBuffMiSize * MI_SIZE; j++){
			int w = frameHdr->si.UpscaledWidth > (WBuffMiSize * MI_SIZE) ? frameHdr->si.UpscaledWidth : (WBuffMiSize * MI_SIZE);
			fc->CurrFrame[i][j] = new uint16_t[w];
			fc->CdefFrame[i][j] = new uint16_t[w];
			fc->UpscaledCdefFrame[i][j] = new uint16_t[w]; // 需要确定
			fc->UpscaledCurrFrame[i][j] = new uint16_t[w];  // 需要确定
		}
	}
//-------下面这几个内存大小(unit size维度)暂不确定
	fc->lrCtx = (LoopRestorationContext *)malloc(sizeof(LoopRestorationContext));


	//printf("frameHdr-> MiRows  * MI_SIZE %d frameHdr->MiCols * MI_SIZE %d \n",frameHdr-> MiRows  * MI_SIZE,frameHdr->MiCols * MI_SIZE);
	for(int i = 0 ; i < 3 ; i++){
		fc->lrCtx->LrFrame[i] = new uint16_t*[frameHdr-> MiRows  * MI_SIZE];
		for(int j = 0 ; j < HBuffMiSize  * MI_SIZE ; j++){
			int w = frameHdr->si.UpscaledWidth > (WBuffMiSize * MI_SIZE) ? frameHdr->si.UpscaledWidth : (WBuffMiSize * MI_SIZE);
			fc->lrCtx->LrFrame[i][j] =  new uint16_t[w];
		}
	}

	for(int i = 0 ; i < 3 ; i ++){
		fc->lrCtx->LrWiener[i]  = new uint16_t ***[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize; j++){
			fc->lrCtx->LrWiener[i][j] = new uint16_t **[WBuffMiSize];
			for(int k = 0 ; k < WBuffMiSize ; k++){
				fc->lrCtx->LrWiener[i][j][k] = new uint16_t *[2];
				for(int m = 0 ; m < 2 ; m++){
					fc->lrCtx->LrWiener[i][j][k][m] = new uint16_t[3];
				}
			}
		}
	}

	for(int i = 0 ; i < 3 ; i ++){
		fc->lrCtx->LrType[i]  = new uint16_t *[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize; j++){
			fc->lrCtx->LrType[i][j] = new uint16_t[WBuffMiSize];
		}
	}
	for(int i = 0 ; i < 3 ; i ++){
		fc->lrCtx->LrSgrSet[i]  = new uint16_t *[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize; j++){
			fc->lrCtx->LrSgrSet[i][j] = new uint16_t[WBuffMiSize];
		}
	}
	for(int i = 0 ; i < 3 ; i ++){
		fc->lrCtx->LrSgrXqd[i]  = new uint16_t **[HBuffMiSize];
		for(int j = 0 ; j < HBuffMiSize; j++){
			fc->lrCtx->LrSgrXqd[i][j] = new uint16_t*[WBuffMiSize];
			for(int k = 0 ; k < WBuffMiSize; k++){
				fc->lrCtx->LrSgrXqd[i][j][k] = new uint16_t[2];
			}
		}
	}

	fc->OutY = new uint16_t*[frameHdr->si.FrameHeight];
	for(int i = 0 ; i < frameHdr->si.FrameHeight ; i++){
		fc->OutY[i] =  new uint16_t[frameHdr->si.UpscaledWidth];
	}
	//两个色度分量内存分配需要优化
	fc->OutU = new uint16_t*[frameHdr->si.FrameHeight];
	for(int i = 0 ; i < frameHdr->si.FrameHeight ; i++){
		fc->OutU[i] =  new uint16_t[frameHdr->si.UpscaledWidth];
	}
	fc->OutV = new uint16_t*[frameHdr->si.FrameHeight];
	for(int i = 0 ; i < frameHdr->si.FrameHeight ; i++){
		fc->OutV[i] =  new uint16_t[frameHdr->si.UpscaledWidth];
	}


	fc->fgCtx = (FilmGainContext *)malloc(sizeof(FilmGainContext));	

	fc->mfmvCtx = (MFMVContext *)malloc(sizeof(MFMVContext));
	fc->mfmvCtx->MfRefFrames  = new int *[HBuffMiSize];
	for(int i = 0 ; i < HBuffMiSize; i++){
		fc->mfmvCtx->MfRefFrames[i] = new int[WBuffMiSize];
	}

	fc->mfmvCtx->MfMvs  = new int **[HBuffMiSize];
	for(int i = 0 ; i < HBuffMiSize; i++){
		fc->mfmvCtx->MfMvs[i] = new int*[WBuffMiSize];
		for(int j = 0 ; j < WBuffMiSize; j++){
			fc->mfmvCtx->MfMvs[i][j] = new int[2];
		}
	}

	fc->mvpCtx = (MVPredContext *)malloc(sizeof(MVPredContext));	

	fc->cdef_idx = new int16_t*[HBuffMiSize];
	for(int i  = 0 ; i < HBuffMiSize ; i++){
		fc->cdef_idx[i] = new int16_t[WBuffMiSize];
	}

}
void frame::releaseFrameContext(frameHeader *frameHdr ,int WBuffMiSize,int HBuffMiSize,FrameContext *fCtx){
	
	for(int i = 0 ; i < 3 ; i++){
		for(int j = 0 ; j < HBuffMiSize * MI_SIZE; j++){
			delete [] fCtx->CurrFrame[i][j];
			delete [] fCtx->CdefFrame[i][j] ;
			delete [] fCtx->UpscaledCdefFrame[i][j] ; 
			delete [] fCtx->UpscaledCurrFrame[i][j] ;
		}
		delete [] fCtx->CurrFrame[i];
		delete [] fCtx->CdefFrame[i] ;
		delete [] fCtx->UpscaledCdefFrame[i] ;
		delete [] fCtx->UpscaledCurrFrame[i] ;
	}
	
	for(int i = 0 ; i < 3 ; i++){	
		for(int j = 0 ; j < WBuffMiSize * MI_SIZE ; j++){
			delete [] fCtx->lrCtx->LrFrame[i][j] ;
		}
		delete [] fCtx->lrCtx->LrFrame[i] ;
	}	
	for(int i = 0 ; i < 3 ; i ++){	
		for(int j = 0 ; j < HBuffMiSize; j++){
			for(int k = 0 ; k < WBuffMiSize ; k++){
				for(int m = 0 ; m < 2 ; m++){
					delete [] fCtx->lrCtx->LrWiener[i][j][k][m];
				}
				delete [] fCtx->lrCtx->LrWiener[i][j][k];
			}
			delete [] fCtx->lrCtx->LrWiener[i][j];
		}
		delete [] fCtx->lrCtx->LrWiener[i];
	}

	for(int i = 0 ; i < 3 ; i ++){
		for(int j = 0 ; j < HBuffMiSize; j++){
			delete [] fCtx->lrCtx->LrType[i][j] ;
		}
		delete [] fCtx->lrCtx->LrType[i] ;
	}
	for(int i = 0 ; i < 3 ; i ++){
		for(int j = 0 ; j < HBuffMiSize; j++){
			delete [] fCtx->lrCtx->LrSgrSet[i][j];
		}
		delete [] fCtx->lrCtx->LrSgrSet[i];
	}
	for(int i = 0 ; i < 3 ; i ++){		
		for(int j = 0 ; j < HBuffMiSize; j++){
			for(int k = 0 ; k < WBuffMiSize; k++){
				delete [] fCtx->lrCtx->LrSgrXqd[i][j][k] ;
			}
			delete [] fCtx->lrCtx->LrSgrXqd[i][j] ;
		}
		delete [] fCtx->lrCtx->LrSgrXqd[i] ;
	}
	delete fCtx->lrCtx;

	
	for(int i = 0 ; i < frameHdr->si.FrameHeight ; i++){
		delete [] fCtx->OutY[i];
	}
	delete [] fCtx->OutY;
	
	for(int i = 0 ; i < frameHdr->si.FrameHeight ; i++){
		delete [] fCtx->OutU[i] ;
	}
	delete [] fCtx->OutU ;

	for(int i = 0 ; i < frameHdr->si.FrameHeight ; i++){
		delete [] fCtx->OutV[i];
	}
	delete [] fCtx->OutV ;



	delete fCtx->fgCtx;	
	
	
	for(int i = 0 ; i < HBuffMiSize; i++){
		delete [] fCtx->mfmvCtx->MfRefFrames[i] ;
	}
	delete [] fCtx->mfmvCtx->MfRefFrames  ;

	for(int i = 0 ; i < HBuffMiSize; i++){
		for(int j = 0 ; j < WBuffMiSize; j++){
			delete [] fCtx->mfmvCtx->MfMvs[i][j] ;
		}
		delete [] fCtx->mfmvCtx->MfMvs[i] ;
	}
	delete [] fCtx->mfmvCtx->MfMvs;

	delete fCtx->mfmvCtx ;

	delete fCtx->mvpCtx ;


	for(int i  = 0 ; i < HBuffMiSize ; i++){
		delete [] fCtx->cdef_idx[i];
	}
	delete [] fCtx->cdef_idx;
	delete fCtx ;
}
int copyCdf(CDFArrays *dst,CDFArrays *src,AV1DecodeContext *av1Ctx){
   	memcpy(dst->Intra_Frame_Y_Mode,src->Intra_Frame_Y_Mode,sizeof(Default_Intra_Frame_Y_Mode_Cdf));
    memcpy(dst->Y_Mode,src->Y_Mode,sizeof(Default_Y_Mode_Cdf));
    memcpy(dst->Uv_Mode_Cfl_Not_Allowed,src->Uv_Mode_Cfl_Not_Allowed, sizeof(Default_Uv_Mode_Cfl_Not_Allowed_Cdf));
    memcpy(dst->Uv_Mode_Cfl_Allowed,src->Uv_Mode_Cfl_Allowed ,sizeof(Default_Uv_Mode_Cfl_Allowed_Cdf));

    memcpy(dst->Angle_Delta,src->Angle_Delta,sizeof(Default_Angle_Delta_Cdf));
    memcpy(dst->Intrabc,src->Intrabc,sizeof(Default_Intrabc_Cdf));

    memcpy(dst->Partition_W8,src->Partition_W8,sizeof(Default_Partition_W8_Cdf));
    memcpy(dst->Partition_W16,src->Partition_W16 ,sizeof(Default_Partition_W16_Cdf));
    memcpy(dst->Partition_W32,src->Partition_W32 ,sizeof(Default_Partition_W32_Cdf));
    memcpy(dst->Partition_W64,src->Partition_W64 ,sizeof(Default_Partition_W64_Cdf));
    memcpy(dst->Partition_W128,src->Partition_W128 ,sizeof(Default_Partition_W128_Cdf));

    memcpy(dst->Tx_8x8,src->Tx_8x8,sizeof(Default_Tx_8x8_Cdf));
    memcpy(dst->Tx_16x16,src->Tx_16x16,sizeof(Default_Tx_16x16_Cdf));
    memcpy(dst->Tx_32x32,src->Tx_32x32,sizeof(Default_Tx_32x32_Cdf));
    memcpy(dst->Tx_64x64,src->Tx_64x64,sizeof(Default_Tx_64x64_Cdf));

    memcpy(dst->Txfm_Split,src->Txfm_Split,sizeof(Default_Txfm_Split_Cdf));
    memcpy(dst->Filter_Intra_Mode,src->Filter_Intra_Mode,sizeof(Default_Filter_Intra_Mode_Cdf));
    memcpy(dst->Filter_Intra,src->Filter_Intra,sizeof(Default_Filter_Intra_Cdf));
    memcpy(dst->Segment_Id,src->Segment_Id,sizeof(Default_Segment_Id_Cdf));
    memcpy(dst->Segment_Id_Predicted,src->Segment_Id_Predicted,sizeof(Default_Segment_Id_Predicted_Cdf));
    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        for(int j = 0 ; j < 2 ; j++){
            memcpy(dst->Mv_Class0_Hp[i][j],src->Mv_Class0_Hp[i][j],sizeof(Default_Mv_Class0_Hp_Cdf));
            memcpy(dst->Mv_Hp[i][j],src->Mv_Hp[i][j],sizeof(Default_Mv_Hp_Cdf));
            memcpy(dst->Mv_Sign[i][j],src->Mv_Sign[i][j],sizeof(Default_Mv_Sign_Cdf));
            memcpy(dst->Mv_Bit[i][j],src->Mv_Bit[i][j],sizeof(Default_Mv_Bit_Cdf));
            memcpy(dst->Mv_Class0_Bit[i][j],src->Mv_Class0_Bit[i][j],sizeof(Default_Mv_Class0_Bit_Cdf));
        }
    }
    memcpy(dst->New_Mv,src->New_Mv,sizeof(Default_New_Mv_Cdf));
    memcpy(dst->Zero_Mv,src->Zero_Mv,sizeof(Default_Zero_Mv_Cdf));
    memcpy(dst->Ref_Mv,src->Ref_Mv,sizeof(Default_Ref_Mv_Cdf));
    memcpy(dst->Drl_Mode,src->Drl_Mode,sizeof(Default_Drl_Mode_Cdf));
    memcpy(dst->Is_Inter,src->Is_Inter,sizeof(Default_Is_Inter_Cdf));

    memcpy(dst->Is_Inter,src->Is_Inter,sizeof(Default_Is_Inter_Cdf));
    memcpy(dst->Comp_Mode,src->Comp_Mode,sizeof(Default_Comp_Mode_Cdf));
    memcpy(dst->Skip_Mode,src->Skip_Mode,sizeof(Default_Skip_Mode_Cdf));
    memcpy(dst->Skip,src->Skip,sizeof(Default_Skip_Cdf));
    memcpy(dst->Comp_Ref,src->Comp_Ref,sizeof(Default_Comp_Ref_Cdf));

    memcpy(dst->Comp_Bwd_Ref,src->Comp_Bwd_Ref,sizeof(Default_Comp_Bwd_Ref_Cdf));
    memcpy(dst->Single_Ref,src->Single_Ref,sizeof(Default_Single_Ref_Cdf));
    memcpy(dst->Compound_Mode,src->Compound_Mode,sizeof(Default_Compound_Mode_Cdf));

    memcpy(dst->Interp_Filter,src->Interp_Filter,sizeof(Default_Interp_Filter_Cdf));
    memcpy(dst->Motion_Mode,src->Motion_Mode,sizeof(Default_Motion_Mode_Cdf));

    for(int i = 0 ; i < MV_CONTEXTS ; i++){
        memcpy(dst->Mv_Joint[i],src->Mv_Joint[i],sizeof(Default_Mv_Joint_Cdf));
        memcpy(dst->Mv_Class[i],src->Mv_Class[i],sizeof(Default_Mv_Class_Cdf));
        memcpy(dst->Mv_Class0_Fr[i],src->Mv_Class0_Fr[i],sizeof(Default_Mv_Class0_Fr_Cdf));
        memcpy(dst->Mv_Fr[i],src->Mv_Fr[i],sizeof(Default_Mv_Fr_Cdf));
    }
    memcpy(dst->Palette_Y_Size,src->Palette_Y_Size,sizeof(Default_Palette_Y_Size_Cdf));
    memcpy(dst->Palette_Uv_Size,src->Palette_Uv_Size,sizeof(Default_Palette_Uv_Size_Cdf));

    memcpy(dst->Palette_Size_2_Y_Color,src->Palette_Size_2_Y_Color,sizeof(Default_Palette_Size_2_Y_Color_Cdf));
    memcpy(dst->Palette_Size_3_Y_Color,src->Palette_Size_3_Y_Color,sizeof(Default_Palette_Size_3_Y_Color_Cdf));
    memcpy(dst->Palette_Size_4_Y_Color,src->Palette_Size_4_Y_Color,sizeof(Default_Palette_Size_4_Y_Color_Cdf));
    memcpy(dst->Palette_Size_5_Y_Color,src->Palette_Size_5_Y_Color,sizeof(Default_Palette_Size_5_Y_Color_Cdf));
    memcpy(dst->Palette_Size_6_Y_Color,src->Palette_Size_6_Y_Color,sizeof(Default_Palette_Size_6_Y_Color_Cdf));
    memcpy(dst->Palette_Size_7_Y_Color,src->Palette_Size_7_Y_Color,sizeof(Default_Palette_Size_7_Y_Color_Cdf));
    memcpy(dst->Palette_Size_8_Y_Color,src->Palette_Size_8_Y_Color,sizeof(Default_Palette_Size_8_Y_Color_Cdf));


    memcpy(dst->Palette_Size_2_Uv_Color,src->Palette_Size_2_Uv_Color,sizeof(Default_Palette_Size_2_Uv_Color_Cdf));
    memcpy(dst->Palette_Size_3_Uv_Color,src->Palette_Size_3_Uv_Color,sizeof(Default_Palette_Size_3_Uv_Color_Cdf));
    memcpy(dst->Palette_Size_4_Uv_Color,src->Palette_Size_4_Uv_Color,sizeof(Default_Palette_Size_4_Uv_Color_Cdf));
    memcpy(dst->Palette_Size_5_Uv_Color,src->Palette_Size_5_Uv_Color,sizeof(Default_Palette_Size_5_Uv_Color_Cdf));
    memcpy(dst->Palette_Size_6_Uv_Color,src->Palette_Size_6_Uv_Color,sizeof(Default_Palette_Size_6_Uv_Color_Cdf));
    memcpy(dst->Palette_Size_7_Uv_Color,src->Palette_Size_7_Uv_Color,sizeof(Default_Palette_Size_7_Uv_Color_Cdf));
    memcpy(dst->Palette_Size_8_Uv_Color,src->Palette_Size_8_Uv_Color,sizeof(Default_Palette_Size_8_Uv_Color_Cdf));

	memcpy(dst->Palette_Y_Mode,src->Palette_Y_Mode,sizeof(Default_Palette_Y_Mode_Cdf));
    memcpy(dst->Palette_Uv_Mode,src->Palette_Y_Mode,sizeof(Default_Palette_Uv_Mode_Cdf));
    memcpy(dst->Delta_Q,src->Delta_Q,sizeof(Default_Delta_Q_Cdf));
    memcpy(dst->Delta_Lf,src->Delta_Lf,sizeof(Default_Delta_Lf_Cdf));

    for(int i = 0 ; i < FRAME_LF_COUNT ; i++)
        memcpy(dst->Delta_Lf_Muti[i],src->Delta_Lf_Muti[i],sizeof(Default_Delta_Lf_Cdf));

    memcpy(dst->Intra_Tx_Type_Set1,src->Intra_Tx_Type_Set1,sizeof(Default_Intra_Tx_Type_Set1_Cdf));
    memcpy(dst->Intra_Tx_Type_Set2,src->Intra_Tx_Type_Set2,sizeof(Default_Intra_Tx_Type_Set2_Cdf));
    memcpy(dst->Inter_Tx_Type_Set1,src->Inter_Tx_Type_Set1,sizeof(Default_Inter_Tx_Type_Set1_Cdf));
    memcpy(dst->Inter_Tx_Type_Set2,src->Inter_Tx_Type_Set2,sizeof(Default_Inter_Tx_Type_Set2_Cdf));
    memcpy(dst->Inter_Tx_Type_Set3,src->Inter_Tx_Type_Set3,sizeof(Default_Inter_Tx_Type_Set3_Cdf));

    memcpy(dst->Compound_Idx,src->Compound_Idx,sizeof(Default_Compound_Idx_Cdf));
    memcpy(dst->Comp_Group_Idx,src->Comp_Group_Idx,sizeof(Default_Comp_Group_Idx_Cdf));
    memcpy(dst->Compound_Type,src->Compound_Type,sizeof(Default_Compound_Type_Cdf));
    memcpy(dst->Inter_Intra,src->Inter_Intra,sizeof(Default_Inter_Intra_Cdf));
    memcpy(dst->Inter_Intra_Mode,src->Inter_Intra_Mode,sizeof(Default_Inter_Intra_Mode_Cdf));

    memcpy(dst->Wedge_Index,src->Wedge_Index,sizeof(Default_Wedge_Index_Cdf));
    memcpy(dst->Wedge_Inter_Intra,src->Wedge_Inter_Intra,sizeof(Default_Wedge_Inter_Intra_Cdf));
    memcpy(dst->Use_Obmc,src->Use_Obmc,sizeof(Default_Use_Obmc_Cdf));
    memcpy(dst->Comp_Ref_Type,src->Comp_Ref_Type,sizeof(Default_Comp_Ref_Type_Cdf));
    memcpy(dst->Uni_Comp_Ref,src->Uni_Comp_Ref,sizeof(Default_Uni_Comp_Ref_Cdf));

    memcpy(dst->Cfl_Sign,src->Cfl_Sign,sizeof(Default_Cfl_Sign_Cdf));
    memcpy(dst->Cfl_Alpha,src->Cfl_Alpha,sizeof(Default_Cfl_Alpha_Cdf));
    memcpy(dst->Use_Wiener,src->Use_Wiener,sizeof(Default_Use_Wiener_Cdf));
    memcpy(dst->Use_Sgrproj,src->Use_Sgrproj,sizeof(Default_Use_Sgrproj_Cdf));
    memcpy(dst->Restoration_Type,src->Restoration_Type,sizeof(Default_Restoration_Type_Cdf));

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
    memcpy(dst->Txb_Skip,src->Txb_Skip,sizeof(Default_Txb_Skip_Cdf[idx]));
    memcpy(dst->Eob_Pt_16,src->Eob_Pt_16,sizeof(Default_Eob_Pt_16_Cdf[idx]));
    memcpy(dst->Eob_Pt_32,src->Eob_Pt_32,sizeof(Default_Eob_Pt_32_Cdf[idx]));
    memcpy(dst->Eob_Pt_64,src->Eob_Pt_64,sizeof(Default_Eob_Pt_64_Cdf[idx]));
    memcpy(dst->Eob_Pt_128,src->Eob_Pt_128,sizeof(Default_Eob_Pt_128_Cdf[idx]));
    memcpy(dst->Eob_Pt_256,src->Eob_Pt_256,sizeof(Default_Eob_Pt_256_Cdf[idx]));
    memcpy(dst->Eob_Pt_512,src->Eob_Pt_512,sizeof(Default_Eob_Pt_512_Cdf[idx]));
    memcpy(dst->Eob_Pt_1024,src->Eob_Pt_1024,sizeof(Default_Eob_Pt_1024_Cdf[idx]));

    memcpy(dst->Eob_Extra,src->Eob_Extra,sizeof(Default_Eob_Extra_Cdf[idx]));
    memcpy(dst->Dc_Sign,src->Dc_Sign,sizeof(Default_Dc_Sign_Cdf[idx]));
    memcpy(dst->Coeff_Base_Eob,src->Coeff_Base_Eob,sizeof(Default_Coeff_Base_Eob_Cdf[idx]));
    memcpy(dst->Coeff_Base,src->Coeff_Base,sizeof(Default_Coeff_Base_Cdf[idx]));
    memcpy(dst->Coeff_Br,src->Coeff_Br,sizeof(Default_Coeff_Br_Cdf[idx]));

}
void frame::exit_symbol(SymbolContext *sbCtx,bitSt *bs,int TileNum,AV1DecodeContext *av1Ctx){
    if(sbCtx->SymbolMaxBits < -14 )
        return;
    int trailingBitPosition = get_position(bs) - Min(15, sbCtx->SymbolMaxBits + 15);
    readBits(bs,Max(0, sbCtx->SymbolMaxBits));
    int paddingEndPosition = get_position(bs);
    //if(trailingBitPosition != 1)
    //    return;
    
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
void frame::frame_end_update_cdf(AV1DecodeContext *av1Ctx){
    copyCdf(&av1Ctx->currentFrame->cdfCtx,&av1Ctx->tileSavedCdf,av1Ctx);
}
int frame::decodeFrame(int sz, bitSt *bs, AV1DecodeContext *av1Ctx){

	frameHeader *frameHdr = &av1Ctx->frameHdr;

	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

	int NumTiles = frameHdr->tile_info.TileCols * frameHdr->tile_info.TileRows;
	int tile_start_and_end_present_flag = 0;
	int tg_start;
	int tg_end;
	int tileBits;
	int startpos = bs->offset;
	if ( NumTiles > 1 )
		tile_start_and_end_present_flag = readOneBit(bs);
	if ( NumTiles == 1 || !tile_start_and_end_present_flag ) {
		tg_start = 0;
		tg_end = NumTiles - 1;
	} else {
		tileBits = frameHdr->tile_info.TileColsLog2 + frameHdr->tile_info.TileRowsLog2;
		tg_start  =  readBits(bs,tileBits); 
		tg_end  =  readBits(bs,tileBits); 
	}
	BitStreamAlign(bs);
	sz -= (bs->offset - startpos);
	for (int TileNum = tg_start; TileNum <= tg_end; TileNum++ ) {
		int tileRow = TileNum / frameHdr->tile_info.TileCols;
		int tileCol = TileNum % frameHdr->tile_info.TileCols;
		int lastTile = TileNum == tg_end;
		int tileSize;
		if ( lastTile ) {
			tileSize = sz;
		} else {
			//tile_size_minus_1 le(TileSizeBytes);
			int tileSize = readle(bs,frameHdr->tile_info.TileSizeBytes) + 1;
			sz -= tileSize + frameHdr->tile_info.TileSizeBytes;
		}
		//TileData t_data;
		av1Ctx->MiRowStart = frameHdr->tile_info.MiRowStarts[ tileRow ];
		av1Ctx->MiRowEnd = frameHdr->tile_info.MiRowStarts[ tileRow + 1 ];
		av1Ctx->MiColStart = frameHdr->tile_info.MiColStarts[ tileCol ];
		av1Ctx->MiColEnd = frameHdr->tile_info.MiColStarts[ tileCol + 1 ];
	//	注意这个!!!! spec中有用，但是用到那个地方在 dav1d中，和libaom中又都没有用
		av1Ctx->CurrentQIndex = frameHdr->quantization_params.base_q_idx;
		//之所以 每个tile 进行一次 init_symbol 是因为tile内的所有语法元素和数据都是算术编码的，而tile层之上会有非算术编码的语法元素。
		//init_symbol( tileSize );
		SymbolContext symCtx;
		printf("sz %d \n",sz);
		sb->initSymbol(&symCtx,bs,sz);
		symCtx.isUpdate = !frameHdr->disable_cdf_update;
		decode_tile(&symCtx,bs,av1Ctx);
		exit_symbol(&symCtx,bs,TileNum,av1Ctx);
	}
	if ( tg_end == NumTiles - 1 ) {
		if ( !frameHdr->disable_frame_end_update_cdf ) {
			frame_end_update_cdf(av1Ctx);
		}
		//  for (int i = 0; i < 750; i++) {
		//  	for (int j = 0; j < 1000; j++) {
		//  		if(av1Ctx->currentFrame->CurrFrame[0][ i][ j] != 0 && av1Ctx->currentFrame->CurrFrame[0][ i][j] != 128){
		//  			printf("!!!!! y %d x %d  %d \n",i,j,av1Ctx->currentFrame->CurrFrame[0][ i][ j]);
		//  		}
		//  	}
		//  }
		// for (int i = 0; i < 8; i++) {
		// 	for (int j = 0; j < 8; j++) {
		// 		printf("!! %d \n",av1Ctx->currentFrame->CurrFrame[0][56 + i][56 + j]);
		// 	}
		// }
		decode_instance->decode_frame_wrapup(av1Ctx);
		av1Ctx->SeenFrameHeader = 0;
	}

}
int frame::decode_tile(SymbolContext *sbCtx,bitSt *bs,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	clear_above_context(av1Ctx );
	for (int i = 0; i < FRAME_LF_COUNT; i++ )
		av1Ctx->DeltaLF[ i ] = 0;
	for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++ ) {
		for (int pass = 0; pass < 2; pass++ ) {
			av1Ctx->RefSgrXqd[ plane ][ pass ] = Sgrproj_Xqd_Mid[ pass ];
			for (int i = 0; i < WIENER_COEFFS; i++ ) {
				av1Ctx->RefLrWiener[ plane ][ pass ][ i ] = Wiener_Taps_Mid[ i ];
			}
		}
	}
	int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64;
	int sbSize4 = Num_4x4_Blocks_Wide[ sbSize ];

	for (int  r = av1Ctx->MiRowStart; r < av1Ctx->MiRowEnd; r += sbSize4 ) {
		clear_left_context(av1Ctx );
		for (int  c = av1Ctx->MiColStart; c < av1Ctx->MiColEnd; c += sbSize4 ) {
			av1Ctx->ReadDeltas = frameHdr->delta_q_params.delta_q_present;
			clear_cdef( r, c ,av1Ctx);
			clear_block_decoded_flags( r, c, sbSize4 ,av1Ctx);
			read_lr(sbCtx,bs, r, c, sbSize,av1Ctx);
			//PartitionData p_data;
			decode_partition(sbCtx, bs ,r, c, sbSize ,av1Ctx);
		}
	}

}

int frame::decode_partition(SymbolContext *sbCtx,bitSt *bs,
						int r,int c,int bSize, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

	if (r >= frameHdr->MiRows || c >= frameHdr->MiCols)
		return 0;
	//是否有效，通过判断是否在帧内
	int AvailU = is_inside(r - 1, c,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd);
	int AvailL = is_inside(r, c - 1,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd);
	//当前块4*4数目
	int num4x4 = Num_4x4_Blocks_Wide[bSize] ;
	//
	int halfBlock4x4 = num4x4 >> 1 ;
	int quarterBlock4x4 = halfBlock4x4 >> 1 ;
	//当前块是否还有数据
	int hasRows = (r + halfBlock4x4) < frameHdr->MiRows;
	int hasCols = (c + halfBlock4x4) < frameHdr->MiCols ;

	int partition,split_or_horz,split_or_vert;

	uint16_t *partitionCdf;
	int size;
	int bsl = Mi_Width_Log2[ bSize ];
	int above = AvailU && ( Mi_Width_Log2[ av1Ctx->MiSizes[ r - 1 ][ c ] ] < bsl );
	int left = AvailL && ( Mi_Height_Log2[ av1Ctx->MiSizes[ r ][ c - 1 ] ] < bsl );
	int ctx = left * 2 + above;

	if(bsl == 1){
		partitionCdf = av1Ctx->tileSavedCdf.Partition_W8[ctx];
		size = 5;
	}else if(bsl == 2){
		partitionCdf = av1Ctx->tileSavedCdf.Partition_W16[ctx];
		size = 9;
	}else if(bsl == 3){
		partitionCdf = av1Ctx->tileSavedCdf.Partition_W32[ctx];
		size = 9;
	}else if(bsl == 4){
		partitionCdf = av1Ctx->tileSavedCdf.Partition_W64[ctx];
		size = 9;
	}else if(bsl == 5){
		partitionCdf = av1Ctx->tileSavedCdf.Partition_W128[ctx];
		size = 11;
	}

	if (bSize < BLOCK_8X8)
	{
		partition = PARTITION_NONE;
	}
	else if (hasRows && hasCols)
	{
		 //根据上边和左边的块来推出需要使用的cdf， 为什么MiSizes 还未初始化这里就在使用？
		 //在最左上角的时候AvailU AvailL都是0，自然  AvailU && 后面的就不会调了，就没有问题
		 printf("decodeSymbol partition\n");
		partition = sb->decodeSymbol(sbCtx,bs,partitionCdf,size);
		printf("partition:%d \n",partition);
	}
	else if (hasCols)
	{
		int psum = ( partitionCdf[ PARTITION_VERT ] - partitionCdf[ PARTITION_VERT - 1 ] +
		partitionCdf[ PARTITION_SPLIT ] - partitionCdf[ PARTITION_SPLIT - 1 ] +
		partitionCdf[ PARTITION_HORZ_A ] - partitionCdf[ PARTITION_HORZ_A - 1 ] +
		partitionCdf[ PARTITION_VERT_A ] - partitionCdf[ PARTITION_VERT_A - 1 ] +
		partitionCdf[ PARTITION_VERT_B ] - partitionCdf[ PARTITION_VERT_B - 1 ] );
		if ( bSize != BLOCK_128X128 )
		psum += partitionCdf[ PARTITION_VERT_4 ] - partitionCdf[ PARTITION_VERT_4 - 1 ];
		uint16_t cdf[3];
		cdf[0] = ( 1 << 15 ) - psum;
		cdf[1] = 1 << 15;
		cdf[2] = 0;

		printf("decodeSymbol split_or_horz\n");
		split_or_horz = sb->decodeSymbol(sbCtx,bs,cdf,3);
		partition = split_or_horz ? PARTITION_SPLIT : PARTITION_HORZ;
	}
	else if (hasRows)
	{
		int psum = ( partitionCdf[ PARTITION_VERT ] - partitionCdf[ PARTITION_VERT - 1 ] +
		partitionCdf[ PARTITION_SPLIT ] - partitionCdf[ PARTITION_SPLIT - 1 ] +
		partitionCdf[ PARTITION_HORZ_A ] - partitionCdf[ PARTITION_HORZ_A - 1 ] +
		partitionCdf[ PARTITION_VERT_A ] - partitionCdf[ PARTITION_VERT_A - 1 ] +
		partitionCdf[ PARTITION_VERT_B ] - partitionCdf[ PARTITION_VERT_B - 1 ] );
		if ( bSize != BLOCK_128X128 )
		psum += partitionCdf[ PARTITION_VERT_4 ] - partitionCdf[ PARTITION_VERT_4 - 1 ];
		uint16_t cdf[3];
		cdf[0] = ( 1 << 15 ) - psum;
		cdf[1] = 1 << 15;
		cdf[2] = 0;
		printf("decodeSymbol split_or_vert\n");
		split_or_vert = sb->decodeSymbol(sbCtx,bs,cdf,3);
		partition = split_or_vert ? PARTITION_SPLIT : PARTITION_VERT;
	}
	else
	{
		partition = PARTITION_SPLIT;
	}
	int subSize = Partition_Subsize[partition][bSize];
	int splitSize = Partition_Subsize[PARTITION_SPLIT][bSize] ;
	
	if (partition == PARTITION_NONE)
	{
		decode_block(sbCtx,bs,r, c, subSize,av1Ctx);
	}
	else if (partition == PARTITION_HORZ)
	{
		decode_block(sbCtx,bs,r, c, subSize,av1Ctx);
		if (hasRows)
			decode_block(sbCtx,bs,r + halfBlock4x4, c, subSize,av1Ctx);
	}
	else if (partition == PARTITION_VERT)
	{
		decode_block(sbCtx,bs,r, c, subSize,av1Ctx);
		if (hasCols)
			decode_block(sbCtx,bs,r, c + halfBlock4x4, subSize,av1Ctx);
	}
	else if (partition == PARTITION_SPLIT)
	{
		decode_partition(sbCtx,bs, r, c, subSize,av1Ctx);
		decode_partition(sbCtx,bs,r, c + halfBlock4x4, subSize,av1Ctx);
		decode_partition(sbCtx,bs,r + halfBlock4x4, c, subSize,av1Ctx);
		decode_partition(sbCtx,bs,r + halfBlock4x4, c + halfBlock4x4, subSize,av1Ctx);
	}
	else if (partition == PARTITION_HORZ_A)
	{
		decode_block(sbCtx,bs,r, c, splitSize,av1Ctx);
		decode_block(sbCtx,bs,r, c + halfBlock4x4, splitSize,av1Ctx);
		decode_block(sbCtx,bs,r + halfBlock4x4, c, subSize,av1Ctx);
	}
	else if (partition == PARTITION_HORZ_B)
	{
		decode_block(sbCtx,bs,r, c, subSize,av1Ctx);
		decode_block(sbCtx,bs,r + halfBlock4x4, c, splitSize,av1Ctx);
		decode_block(sbCtx,bs,r + halfBlock4x4, c + halfBlock4x4, splitSize,av1Ctx);
	}
	else if (partition == PARTITION_VERT_A)
	{
		decode_block(sbCtx,bs,r, c, splitSize,av1Ctx);
		decode_block(sbCtx,bs,r + halfBlock4x4, c, splitSize,av1Ctx);
		decode_block(sbCtx,bs,r, c + halfBlock4x4, subSize,av1Ctx);
	}
	else if (partition == PARTITION_VERT_B)
	{
		decode_block(sbCtx,bs,r, c, subSize,av1Ctx);
		decode_block(sbCtx,bs,r, c + halfBlock4x4, splitSize,av1Ctx);
		decode_block(sbCtx,bs,r + halfBlock4x4, c + halfBlock4x4, splitSize,av1Ctx);
	}
	else if (partition == PARTITION_HORZ_4)
	{
		decode_block(sbCtx,bs,r + quarterBlock4x4 * 0, c, subSize,av1Ctx);
		decode_block(sbCtx,bs,r + quarterBlock4x4 * 1, c, subSize,av1Ctx);
		decode_block(sbCtx,bs,r + quarterBlock4x4 * 2, c, subSize,av1Ctx) ;
		if (r + quarterBlock4x4 * 3 < frameHdr->MiRows)
			decode_block(sbCtx,bs,r + quarterBlock4x4 * 3, c, subSize,av1Ctx);
	}
	else
	{
		decode_block(sbCtx,bs,r, c + quarterBlock4x4 * 0, subSize,av1Ctx);
		decode_block(sbCtx,bs,r, c + quarterBlock4x4 * 1, subSize,av1Ctx);
		decode_block(sbCtx,bs,r, c + quarterBlock4x4 * 2, subSize,av1Ctx); 
		if (c + quarterBlock4x4 * 3 < frameHdr->MiCols)
			decode_block(sbCtx,bs, r, c + quarterBlock4x4 * 3, subSize,av1Ctx);
	}
}

int frame::decode_block(SymbolContext *sbCtx,bitSt *bs,int r,int c,int subSize, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

	BlockData b_data;
	memset(&b_data,0,sizeof(BlockData));
	b_data.MiRow = r;
	b_data.MiCol = c;
	b_data.MiSize = subSize;
	printf("b_data.MiRow %d  b_data.MiCol %d  b_data.MiSize %d\n",b_data.MiRow,b_data.MiCol,b_data.MiSize);
	//block 宽高 4*4 为单位
	int bw4 = Num_4x4_Blocks_Wide[subSize];
	int bh4 = Num_4x4_Blocks_High[subSize];
	int blockHeight = Block_Height[b_data.MiSize];
	int blockWidth = Block_Width[b_data.MiSize];

	b_data.AboveRow = new Array16(blockWidth + blockHeight);

	b_data.LeftCol = new Array16(blockWidth + blockHeight);

	b_data.Mask = new uint16_t*[blockHeight];
	for(int i = 0 ; i < blockHeight ; i++){
		b_data.Mask[i] = new uint16_t[blockWidth];
	}
	
	if (bh4 == 1 && seqHdr->color_config.subsampling_y && (b_data.MiRow & 1) == 0)
		b_data.HasChroma = 0 ;
	else if (bw4 == 1 && seqHdr->color_config.subsampling_x && (b_data.MiCol & 1) == 0)
		b_data.HasChroma = 0 ;
	else 
		b_data.HasChroma = seqHdr->color_config.NumPlanes > 1;
	b_data.AvailU = is_inside(r - 1, c,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd);
	b_data.AvailL = is_inside(r, c - 1,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd);
	b_data.AvailUChroma = b_data.AvailU;
	b_data.AvailLChroma = b_data.AvailL;
	if (b_data.HasChroma)
	{
		if (seqHdr->color_config.subsampling_y && bh4 == 1)
			b_data.AvailUChroma = is_inside(r - 2, c,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd);
		if (seqHdr->color_config.subsampling_x && bw4 == 1)
			b_data.AvailLChroma = is_inside(r, c - 2,av1Ctx->MiColStart,av1Ctx->MiColEnd,av1Ctx->MiRowStart,av1Ctx->MiRowEnd);
	}else {
		b_data.AvailUChroma = 0;
		b_data.AvailLChroma = 0;
	}

	mode_info(sbCtx,bs,&b_data,av1Ctx);
	palette_tokens(sbCtx,bs,&b_data,av1Ctx);
	read_block_tx_size(sbCtx,bs,&b_data,av1Ctx);	
	if (b_data.skip)
		reset_block_context(bw4, bh4,sbCtx,bs,&b_data,av1Ctx);
	int isCompound = b_data.RefFrame[1] > INTRA_FRAME;
	for (int y = 0; y < bh4; y++)
	{
		for (int x = 0; x < bw4; x++)
		{
			av1Ctx->YModes[r + y][c + x] = b_data.YMode ;
			if (b_data.RefFrame[0] == INTRA_FRAME && b_data.HasChroma)
				av1Ctx->UVModes[r + y][c + x] = b_data.UVMode ;
			for (int refList = 0; refList < 2; refList++){
				//printf("bh4 %d bw4 %d  r %d c %d r + y %d, c + x %d mirows %d, micols %d\n",bh4, bw4 , r ,c,r + y,c + x,frameHdr->MiRows,frameHdr->MiCols);
				av1Ctx->RefFrames[r + y][c + x][refList] = b_data.RefFrame[refList] ;
			}
				
			if (b_data.is_inter)
			{
					if (!b_data.use_intrabc)
					{
						av1Ctx->CompGroupIdxs[r + y][c + x] = b_data.comp_group_idx;
						av1Ctx->CompoundIdxs[r + y][c + x] = b_data.compound_idx;
					}
					for (int dir = 0; dir < 2; dir++)
					{
						av1Ctx->InterpFilters[r + y][c + x][dir] = b_data.interp_filter[dir];
					}
					for (int refList = 0; refList < 1 + isCompound; refList++)
					{
						//p_data->Mvs[r + y][c + x][refList] = b_data.Mv[refList];
						memcpy(av1Ctx->Mvs[r + y][c + x][refList],b_data.Mv[refList],sizeof(uint8_t) * 2);
					}
			}
		}
	}
	compute_prediction(sbCtx,bs,&b_data,av1Ctx);
	
	decode_instance->residual(sbCtx,bs,&b_data,av1Ctx) ;
	for (int y = 0; y < bh4; y++)
	{
		for (int x = 0; x < bw4; x++)
		{
			av1Ctx->IsInters[r + y][c + x] = b_data.is_inter;
			av1Ctx->SkipModes[r + y][c + x] = b_data.skip_mode;
			av1Ctx->Skips[r + y][c + x] = b_data.skip;
			av1Ctx->TxSizes[r + y][c + x] = b_data.TxSize;
			av1Ctx->MiSizes[r + y][c + x] = b_data.MiSize;
			av1Ctx->SegmentIds[r + y][c + x] = b_data.segment_id;
			av1Ctx->PaletteSizes[0][r + y][c + x] = b_data.PaletteSizeY;
			av1Ctx->PaletteSizes[1][r + y][c + x] = b_data.PaletteSizeUV ;
			
			//在 releasecontext中释放
			av1Ctx->PaletteColors[0][r + y][c + x] = new uint8_t[b_data.PaletteSizeY];
			av1Ctx->PaletteColors[1][r + y][c + x] = new uint8_t[b_data.PaletteSizeUV];
			for (int i = 0; i < b_data.PaletteSizeY; i++)
				av1Ctx->PaletteColors[0][r + y][c + x][i] = b_data.palette_colors_y[i] ;
			for (int i = 0; i < b_data.PaletteSizeUV; i++)
				av1Ctx->PaletteColors[1][r + y][c + x][i] = b_data.palette_colors_u[i] ;
			for (int i = 0; i < FRAME_LF_COUNT; i++)
				av1Ctx->DeltaLFs[r + y][c + x][i] = av1Ctx->DeltaLF[i];
		}
	}
	//其实没有必要判断，delete null没有问题
	if(b_data.has_palette_y)
		delete [] b_data.palette_colors_y;
	if(b_data.has_palette_uv){
		delete [] b_data.palette_colors_u;
		delete [] b_data.palette_colors_v;
	}
	if(b_data.has_palette_y || b_data.has_palette_uv)
		delete [] b_data.PaletteCache;

	if(b_data.PaletteSizeY){
		for(int i = 0 ; i < blockHeight; i++){
			delete [] b_data.ColorMapY[i] ;
		}
		delete [] b_data.ColorMapY;
 	}
	if(b_data.PaletteSizeUV){
		blockHeight = blockHeight >> seqHdr->color_config.subsampling_y;
		blockWidth = blockWidth >> seqHdr->color_config.subsampling_x;
		
		for(int i = 0 ; i < blockHeight; i++){
			delete [] b_data.ColorMapUV[i] ;
		}
		delete [] b_data.ColorMapUV;
	}
	printf("AboveRow addr %d\n",	b_data.AboveRow);
	printf("LeftCol addr %d\n",	b_data.LeftCol);
	delete b_data.AboveRow;
	printf("delete 22\n");
	delete b_data.LeftCol;

	for(int i = 0 ; i < blockHeight ; i++){
		delete [] b_data.Mask[i];
	}
	delete [] b_data.Mask;
}
int frame::mode_info(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if ( frameHdr->FrameIsIntra ) 
		intra_frame_mode_info(sbCtx,bs,b_data,av1Ctx );
	else
		inter_frame_mode_info(sbCtx,bs,b_data,av1Ctx);

}
int frame::intra_frame_mode_info(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx ){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	b_data->skip = 0 ;
	if (frameHdr->segmentation_params.SegIdPreSkip){
		//intra_segment_id();
		if ( frameHdr->segmentation_params.segmentation_enabled )
			read_segment_id(sbCtx,bs,b_data,av1Ctx);
		else
			b_data->segment_id = 0;
		b_data->Lossless = frameHdr->segmentation_params.LosslessArray[ b_data->segment_id ];

	}
	b_data->skip_mode = 0 ;
	//read_skip() 
	if ( frameHdr->segmentation_params.SegIdPreSkip &&
		 seg_instance->seg_feature_active( b_data->segment_id,SEG_LVL_SKIP, frameHdr) ) 
	{
		b_data->skip = 1;
	} else {
		int ctx = 0;
		if ( b_data->AvailU )
			ctx += av1Ctx->Skips[ b_data->MiRow - 1 ][ b_data->MiCol ];
		if ( b_data->AvailL )
			ctx += av1Ctx->Skips[ b_data->MiRow ][ b_data->MiCol - 1 ];
		printf("decodeSymbol skip\n");
		b_data->skip =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Skip[ctx],3);//S()
		printf("sb skip:%d\n",b_data->skip);
	}


	if (!frameHdr->segmentation_params.SegIdPreSkip){
		//intra_segment_id()
		if ( frameHdr->segmentation_params.segmentation_enabled )
			read_segment_id(sbCtx,bs,b_data,av1Ctx);
		else
			b_data->segment_id = 0;
		b_data->Lossless = frameHdr->segmentation_params.LosslessArray[ b_data->segment_id ];

	}
		
	read_cdef(sbCtx,bs,b_data,av1Ctx);
	read_delta_qindex(sbCtx,bs,b_data,av1Ctx);
	read_delta_lf(sbCtx,bs,b_data,av1Ctx);
	av1Ctx->ReadDeltas = 0 ;
	b_data->RefFrame[0] = INTRA_FRAME;
	b_data->RefFrame[1] = NONE ;

	if (frameHdr->allow_intrabc)
	{
		printf("decodeSymbol use_intrabc\n");
		b_data->use_intrabc =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Intrabc,3);// S()
	}
	else
	{
		b_data->use_intrabc = 0;
	}
	if (b_data->use_intrabc)
	{
		b_data->is_inter = 1 ;
		b_data->YMode = DC_PRED;
		b_data->motion_mode = SIMPLE;
		b_data->compound_type = COMPOUND_AVERAGE;
		b_data->PaletteSizeY = 0 ;
		b_data->PaletteSizeUV = 0 ;
		b_data->interp_filter[0] = BILINEAR;
		b_data->interp_filter[1] = BILINEAR;
		decode_instance->find_mv_stack(0,sbCtx,bs,b_data,av1Ctx);
		assign_mv(0, sbCtx,bs,b_data,av1Ctx );
	}
	else
	{
		b_data->is_inter = 0 ;
	//	intra_frame_y_mode ;//S()
		int abovemode = Intra_Mode_Context[ b_data->AvailU ? av1Ctx->YModes[ b_data->MiRow - 1 ][ b_data->MiCol ] : DC_PRED ];
		int leftmode = Intra_Mode_Context[ b_data->AvailL ? av1Ctx->YModes[ b_data->MiRow ][ b_data->MiCol - 1] : DC_PRED ];
		printf("decodeSymbol YMode\n");
		b_data->YMode = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Intra_Frame_Y_Mode[abovemode][leftmode],INTRA_MODES + 1);
		printf("sb YMode:%d\n",b_data->YMode);
		intra_angle_info_y( sbCtx,bs,b_data,av1Ctx) ;
		if (b_data->HasChroma)
		{
	

			uint16_t *uv_mode_cdf;
			int size;
			if(b_data->Lossless && 
					BLOCK_4X4 == get_plane_residual_size( b_data->MiSize, 1 ,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y)){
					uv_mode_cdf = av1Ctx->tileSavedCdf.Uv_Mode_Cfl_Allowed[b_data->YMode];
					size = UV_INTRA_MODES_CFL_ALLOWED + 1;
			// Block_Width[ x ] is defined to be equal to 4 * Num_4x4_Blocks_Wide[ x ].
			//Block_Height[ x ] is defined to be equal to 4 * Num_4x4_Blocks_High[ x ].
			}else if(!b_data->Lossless && Max( Block_Width[ b_data->MiSize ], Block_Height[ b_data->MiSize ] ) <= 32){
					uv_mode_cdf = av1Ctx->tileSavedCdf.Uv_Mode_Cfl_Allowed[b_data->YMode];
					size = UV_INTRA_MODES_CFL_ALLOWED + 1;
			}else{
					uv_mode_cdf = av1Ctx->tileSavedCdf.Uv_Mode_Cfl_Not_Allowed[b_data->YMode];
					size = UV_INTRA_MODES_CFL_NOT_ALLOWED + 1;
			}
			//uv_mode ;//S()
			printf("decodeSymbol UVMode\n");
			b_data->UVMode = sb->decodeSymbol(sbCtx,bs,uv_mode_cdf,size);
			printf("sb UVMode:%d\n",b_data->UVMode);
			if (b_data->UVMode == UV_CFL_PRED){
				read_cfl_alphas( sbCtx,bs,b_data,av1Ctx);
			} 
			intra_angle_info_uv(sbCtx,bs,b_data,av1Ctx);
		}
		b_data->PaletteSizeY = 0 ;
		b_data->PaletteSizeUV = 0 ;
		if (b_data->MiSize >= BLOCK_8X8 &&
			Block_Width[b_data->MiSize] <= 64 &&
			Block_Height[b_data->MiSize] <= 64 &&
			frameHdr->allow_screen_content_tools){
				palette_mode_info(sbCtx,bs,b_data,av1Ctx);
			} 
			filter_intra_mode_info(sbCtx,bs,b_data,av1Ctx);
	}
	
}
int frame::inter_frame_mode_info(SymbolContext *sbCtx, bitSt *bs, BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int use_intrabc = 0;
	b_data->LeftRefFrame[0] = b_data->AvailL ? av1Ctx->RefFrames[b_data->MiRow][b_data->MiCol - 1][0] : INTRA_FRAME;
	b_data->AboveRefFrame[0] = b_data->AvailU ? av1Ctx->RefFrames[b_data->MiRow - 1][b_data->MiCol][0] : INTRA_FRAME;
	b_data->LeftRefFrame[1] = b_data->AvailL ? av1Ctx->RefFrames[b_data->MiRow][b_data->MiCol - 1][1] : NONE;
	b_data->AboveRefFrame[1] = b_data->AvailU ? av1Ctx->RefFrames[b_data->MiRow - 1][b_data->MiCol][1] : NONE;
	b_data->LeftIntra = b_data->LeftRefFrame[0] <= INTRA_FRAME;
	b_data->AboveIntra = b_data->AboveRefFrame[0] <= INTRA_FRAME;
	b_data->LeftSingle = b_data->LeftRefFrame[1] <= INTRA_FRAME;
	b_data->AboveSingle = b_data->AboveRefFrame[1] <= INTRA_FRAME;
	b_data->skip = 0;
	inter_segment_id(1,sbCtx,bs,b_data,av1Ctx);
	//read_skip_mode();
	if ( seg_instance->seg_feature_active( b_data->segment_id,SEG_LVL_SKIP,frameHdr ) ||
		seg_instance->seg_feature_active( b_data->segment_id,SEG_LVL_REF_FRAME ,frameHdr) ||
		seg_instance->seg_feature_active( b_data->segment_id,SEG_LVL_GLOBALMV ,frameHdr) ||
		!frameHdr->skip_mode_present ||
		Block_Width[ b_data->MiSize ] < 8 ||
		Block_Height[ b_data->MiSize ] < 8 )
	{
		b_data->skip_mode = 0;
	} else {
		int ctx = 0;
		if ( b_data->AvailU )
			ctx += av1Ctx->SkipModes[ b_data->MiRow - 1 ][ b_data->MiCol ];
		if ( b_data->AvailL )
			ctx += av1Ctx->SkipModes[ b_data->MiRow ][ b_data->MiCol - 1 ];
			printf("decodeSymbol skip_mode\n");
		b_data->skip_mode = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Skip_Mode[ctx],3);// S()
	}

	if (b_data->skip_mode)
			b_data->skip = 1;
	else{
		//read_skip();
		if ( frameHdr->segmentation_params.SegIdPreSkip && 
			seg_instance->seg_feature_active(  b_data->segment_id,SEG_LVL_SKIP,frameHdr) ) {
			b_data->skip = 1;
		} else {
			int ctx = 0;
			if ( b_data->AvailU )
				ctx += av1Ctx->Skips[ b_data->MiRow - 1 ][ b_data->MiCol ];
			if ( b_data->AvailL )
				ctx += av1Ctx->Skips[ b_data->MiRow ][ b_data->MiCol - 1 ];
			printf("decodeSymbol skip\n");
			b_data->skip =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Skip[ctx],3);
		}

	}

	if (!frameHdr->segmentation_params.SegIdPreSkip)
		inter_segment_id(0,sbCtx,bs,b_data,av1Ctx);
	b_data->Lossless = frameHdr->segmentation_params.LosslessArray[b_data->segment_id];
	read_cdef(sbCtx,bs,b_data,av1Ctx);
	read_delta_qindex(sbCtx,bs,b_data,av1Ctx);
	read_delta_lf(sbCtx,bs,b_data,av1Ctx);
	av1Ctx->ReadDeltas = 0;
	//read_is_inter();
	if ( b_data->skip_mode ) {
		b_data->is_inter = 1;
	} else if ( seg_instance->seg_feature_active ( b_data->segment_id ,SEG_LVL_REF_FRAME,frameHdr) ) {
		b_data->is_inter = frameHdr->segmentation_params.FeatureData[ b_data->segment_id ][ SEG_LVL_REF_FRAME ] != INTRA_FRAME;
	} else if ( seg_instance->seg_feature_active (b_data->segment_id ,SEG_LVL_GLOBALMV,frameHdr ) ) {
		b_data->is_inter = 1;
	} else {
		int ctx;
		if ( b_data->AvailU && b_data->AvailL )
			ctx = (b_data->LeftIntra && b_data->AboveIntra) ? 3 : b_data->LeftIntra || b_data->AboveIntra;
		else if ( b_data->AvailU || b_data->AvailL )
			ctx = 2 * (b_data->AvailU ? b_data->AboveIntra : b_data->LeftIntra);
		else
			ctx = 0;
		printf("decodeSymbol is_inter\n");
		b_data->is_inter = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Is_Inter[ctx],3);//S()
	}

	if (b_data->is_inter)
		inter_block_mode_info(sbCtx,bs,b_data,av1Ctx);
	else
		intra_block_mode_info(sbCtx,bs,b_data,av1Ctx);
}
int frame::read_segment_id(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int prevUL,prevU,prevL;
	if (b_data->AvailU && b_data->AvailL)
		prevUL = av1Ctx->SegmentIds[b_data->MiRow - 1][b_data->MiCol - 1];
	else 
		prevUL = -1 ;
	if (b_data->AvailU)
		prevU = av1Ctx->SegmentIds[b_data->MiRow - 1][b_data->MiCol] ;
	else
		prevU = -1 ;
	if (b_data->AvailL)
		prevL = av1Ctx->SegmentIds[b_data->MiRow][b_data->MiCol - 1] ;
	else 
		prevL = -1 ;

	int pred;
	if (prevU == -1)
		pred = (prevL == -1) ? 0 : prevL ;
	else if (prevL == -1) 
		pred = prevU ;
	else 
		pred = (prevUL == prevU) ? prevU : prevL; 

	if (b_data->skip)
	{
		b_data->segment_id = pred;
	}
	else
	{
		int ctx;
		if ( prevUL < 0 )
			ctx = 0;
		else if ( (prevUL == prevU) && (prevUL == prevL) )
			ctx = 2;
		else if ( (prevUL == prevU) || (prevUL == prevL) || ( prevU == prevL) )
			ctx = 1;
		else
			ctx = 0;
			printf("decodeSymbol segment_id\n");
		b_data->segment_id = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Segment_Id[ctx],MAX_SEGMENTS + 1);//S() 
		b_data->segment_id  = neg_deinterleave( b_data->segment_id, pred,
						frameHdr->segmentation_params.LastActiveSegId + 1);
		printf("sb segment_id:%d\n",b_data->segment_id);
	}
}
int frame::read_cdef(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx){
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	if (b_data->skip || frameHdr->CodedLossless || !seqHdr->enable_cdef || frameHdr->allow_intrabc)
	{
		return ERROR_CODE;
	}
	int cdefSize4 = Num_4x4_Blocks_Wide[BLOCK_64X64] ;
	int cdefMask4 = ~(cdefSize4 - 1);
	int r = b_data->MiRow &cdefMask4;
	int c = b_data->MiCol & cdefMask4 ;
	if (av1Ctx->currentFrame->cdef_idx[r][c] == -1)
	{
		printf("read_literal cdef_idx\n");
		av1Ctx->currentFrame->cdef_idx[r][c] = sb->read_literal(sbCtx,bs,frameHdr->cdef_params.cdef_bits); //L(cdef_bits)
		printf("sb cdef_idx:%d\n",av1Ctx->currentFrame->cdef_idx[r][c]);
		int w4 = Num_4x4_Blocks_Wide[b_data->MiSize] ;
		int h4 = Num_4x4_Blocks_High[b_data->MiSize] ;
		for (int i = r; i < r + h4; i += cdefSize4)
		{
			for (int j = c; j < c + w4; j += cdefSize4)
			{
				av1Ctx->currentFrame->cdef_idx[i][j] = av1Ctx->currentFrame->cdef_idx[r][c];
			}
		}
	}
}
int frame::read_delta_qindex(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64 ;
	if (b_data->MiSize == sbSize && b_data->skip) 
		return ERROR_CODE;
	if (av1Ctx->ReadDeltas)
	{
		printf("decodeSymbol delta_q_abs\n");
		int delta_q_abs =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Delta_Q,DELTA_Q_SMALL + 2);//S() 
		if (delta_q_abs == DELTA_Q_SMALL)
		{
			printf("read_literal delta_q_rem_bits\n");
			int delta_q_rem_bits = sb->read_literal(sbCtx,bs,3);//L(3)
			delta_q_rem_bits++ ;
			printf("read_literal delta_q_abs_bits\n");
			int delta_q_abs_bits = sb->read_literal(sbCtx,bs,delta_q_rem_bits);//L(delta_q_rem_bits)
			delta_q_abs = delta_q_abs_bits + (1 << delta_q_rem_bits) + 1;
		}
		if (delta_q_abs)
		{
			printf("read_literal delta_q_abs_bits\n");
			int delta_q_sign_bit = sb->read_literal(sbCtx,bs,1);//L(1)
			int reducedDeltaQIndex = delta_q_sign_bit ? -delta_q_abs : delta_q_abs ;
			av1Ctx->CurrentQIndex = Clip3(1, 255, av1Ctx->CurrentQIndex + (reducedDeltaQIndex << frameHdr->delta_q_params.delta_q_res));
		}
	}
}
int frame::read_delta_lf(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64;

	if ( b_data->MiSize == sbSize && b_data->skip )
		return ERROR_CODE;
	if (av1Ctx->ReadDeltas && frameHdr->delta_lf_params.delta_lf_present)

	{
		int frameLfCount = 1 ;
		if (frameHdr->delta_lf_params.delta_lf_multi)
		{
			frameLfCount = (seqHdr->color_config.NumPlanes > 1) ? FRAME_LF_COUNT : (FRAME_LF_COUNT - 2);
		}
		for (int i = 0; i < frameLfCount; i++)
		{
			int delta_lf_abs;
			if(frameHdr->delta_lf_params.delta_lf_multi){
				printf("decodeSymbol delta_lf_abs 1\n");
				delta_lf_abs =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Delta_Lf_Muti[i],DELTA_LF_SMALL + 2); //S() 
			}else{
				printf("decodeSymbol delta_lf_abs 2\n");
				delta_lf_abs =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Delta_Lf,DELTA_LF_SMALL + 2); //S() 
			}
			int deltaLfAbs;
			if (delta_lf_abs == DELTA_LF_SMALL)
			{
				printf("read_literal delta_lf_rem_bits\n");
				int delta_lf_rem_bits = sb->read_literal(sbCtx,bs,3); //L(3)
				printf("read_literal delta_lf_abs_bits\n");
				int delta_lf_abs_bits = sb->read_literal(sbCtx,bs,delta_lf_rem_bits + 1); //L(n)
				deltaLfAbs = delta_lf_abs_bits + (1 << delta_lf_rem_bits) + 1;
			}
			else
			{
				deltaLfAbs = delta_lf_abs;
			}
			if (deltaLfAbs)
			{
				printf("read_literal delta_lf_sign_bit\n");
				int delta_lf_sign_bit = sb->read_literal(sbCtx,bs,1); //L(1)
				int reducedDeltaLfLevel = delta_lf_sign_bit ? -deltaLfAbs : deltaLfAbs;
				av1Ctx->DeltaLF[i] = Clip3(-MAX_LOOP_FILTER, MAX_LOOP_FILTER, av1Ctx->DeltaLF[i] + (reducedDeltaLfLevel << frameHdr->delta_lf_params.delta_lf_res));
			}
		}
	}
}
int frame::assign_mv(int isCompound,SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int compMode;
	for (int i = 0; i < 1 + isCompound; i++)
	{
		if (b_data->use_intrabc)
		{
			compMode = NEWMV;
		}
		else
		{
			//compMode = get_mode(i);

			if ( i == 0 ) {
				if ( b_data->YMode < NEAREST_NEARESTMV )
					compMode = b_data->YMode;
				else if ( b_data->YMode == NEW_NEWMV || b_data->YMode == NEW_NEARESTMV || b_data->YMode == NEW_NEARMV )
					compMode = NEWMV;
				else if ( b_data->YMode == NEAREST_NEARESTMV || b_data->YMode == NEAREST_NEWMV )
					compMode = NEARESTMV;
				else if ( b_data->YMode == NEAR_NEARMV || b_data->YMode == NEAR_NEWMV )
					compMode = NEARMV;
				else
					compMode = GLOBALMV;
			} else {
				if ( b_data->YMode == NEW_NEWMV || b_data->YMode == NEAREST_NEWMV || b_data->YMode == NEAR_NEWMV )
					compMode = NEWMV;

				else if ( b_data->YMode == NEAREST_NEARESTMV || b_data->YMode == NEW_NEARESTMV )
					compMode = NEARESTMV;
				else if ( b_data->YMode == NEAR_NEARMV || b_data->YMode == NEW_NEARMV )
					compMode = NEARMV;
				else
					compMode = GLOBALMV;
			}
		}
		int PredMv[2][2];

		if (b_data->use_intrabc)
		{

			//PredMv[0] = b_data->RefStackMv[0][0];
			 memcpy(PredMv[0], av1Ctx->currentFrame->mvpCtx->RefStackMv[0][0], sizeof(int) * 2);
			if (PredMv[0][0] == 0 && PredMv[0][1] == 0)
			{
				//PredMv[0] = b_data->RefStackMv[1][0];
				memcpy(PredMv[0], av1Ctx->currentFrame->mvpCtx->RefStackMv[1][0], sizeof(int) * 2);
			}
			if (PredMv[0][0] == 0 && PredMv[0][1] == 0)
			{
				int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64 ;
				int sbSize4 = Num_4x4_Blocks_High[sbSize] ;
				if (b_data->MiRow - sbSize4 < av1Ctx->MiRowStart)
				{
						PredMv[0][0] = 0 ;
						PredMv[0][1] = -(sbSize4 * MI_SIZE + INTRABC_DELAY_PIXELS) * 8;
				}
				else
				{
						PredMv[0][0] = -(sbSize4 * MI_SIZE * 8);
						PredMv[0][1] = 0;
				}
			}
		}
		else if (compMode == GLOBALMV)
		{

			//PredMv[i] = b_data->GlobalMvs[i];
			memcpy(PredMv[i], av1Ctx->currentFrame->mvpCtx->GlobalMvs[i], sizeof(int) * 2);
		}
		else
		{
			int pos = (compMode == NEARESTMV) ? 0 : av1Ctx->currentFrame->mvpCtx->RefMvIdx ;
			if (compMode == NEWMV && av1Ctx->currentFrame->mvpCtx->NumMvFound <= 1) 
				pos = 0 ;
			//PredMv[i] = b_data->RefStackMv[pos][i];
			memcpy(PredMv[i], av1Ctx->currentFrame->mvpCtx->RefStackMv[pos][i], sizeof(int) * 2);
		}
		uint8_t diffMv[2];
		if (compMode == NEWMV)
		{
			diffMv[ 0 ] = 0;
			diffMv[ 1 ] = 0;
			int MvCtx;
			if ( b_data->use_intrabc ) {
				MvCtx = MV_INTRABC_CONTEXT;
			} else {
				MvCtx = 0;
			}
			//???????????
			printf("decodeSymbol mv_joint\n");
			int mv_joint = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Joint[MvCtx],DELTA_LF_SMALL + 2);//S()
			if ( mv_joint == MV_JOINT_HZVNZ || mv_joint == MV_JOINT_HNZVNZ )
				diffMv[ 0 ] = read_mv_component(MvCtx, 0,sbCtx,bs,b_data,av1Ctx );
			if ( mv_joint == MV_JOINT_HNZVZ || mv_joint == MV_JOINT_HNZVNZ )
				diffMv[ 1 ] = read_mv_component(MvCtx ,1,sbCtx,bs,b_data,av1Ctx );
			b_data->Mv[ i ][ 0 ] = PredMv[ i ][ 0 ] + diffMv[ 0 ];
			b_data->Mv[ i ][ 1 ] = PredMv[ i ][ 1 ] + diffMv[ 1 ];

		}
		else
		{
			//b_data->Mv[i] = PredMv[i];
			memcpy(b_data->Mv[i], PredMv[i], sizeof(int) * 2);
		}
	}
}
int frame::read_mv_component(int MvCtx,int comp,SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
printf("decodeSymbol mv_sign\n");
	int mv_sign = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Sign[MvCtx][comp],3);//S()
printf("decodeSymbol mv_class\n");
	int mv_class = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Class[MvCtx][comp],MV_CLASSES + 1);//S() 
	int mag;
	
	if (mv_class == MV_CLASS_0)
	{
		int mv_class0_bit,mv_class0_fr,mv_class0_hp;
		printf("decodeSymbol mv_class0_bit\n");
		mv_class0_bit = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Class0_Bit[MvCtx][comp],3);//S() 
		if (frameHdr->force_integer_mv)
			mv_class0_fr = 3 ;
		else{
			printf("decodeSymbol mv_class0_fr\n");
			mv_class0_fr =  sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Class0_Fr[MvCtx][comp][mv_class0_bit],5);//S()
		}
		if (frameHdr->allow_high_precision_mv){
			printf("decodeSymbol mv_class0_hp\n");
			mv_class0_hp = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Class0_Hp[MvCtx][comp],3);//S() 
		}else{
			mv_class0_hp = 1; 
		}
		mag = ((mv_class0_bit << 3) | (mv_class0_fr << 1) | mv_class0_hp) + 1;
	}
	else
	{
		int mv_bit,mv_fr,mv_hp,mv_sign;
		int d = 0 ;
		for (int i = 0; i < mv_class; i++){
			printf("decodeSymbol mv_bit\n");
			mv_bit = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Bit[MvCtx][comp][i],3);
			d |= mv_bit << i;
		}
			
		mag = CLASS0_SIZE << (mv_class + 2) ;
		if (frameHdr->force_integer_mv) 
			mv_fr = 3 ;
		else {
			printf("decodeSymbol mv_fr\n");
			mv_fr = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Fr[MvCtx][comp],3); //S()
		}if (frameHdr->allow_high_precision_mv) {
			printf("decodeSymbol mv_hp\n");
			mv_hp = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Mv_Hp[MvCtx][comp],3); //S() 
		}else 
			mv_hp = 1 ;
		mag += ((d << 3) | (mv_fr << 1) | mv_hp) + 1;
	}
	return mv_sign ? -mag : mag;
}
int frame::intra_angle_info_y(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx) {
	b_data->AngleDeltaY = 0;
	if ( b_data->MiSize >= BLOCK_8X8 ) {
		if ( is_directional_mode( b_data->YMode ) ) {
			printf("decodeSymbol angle_delta_y\n");
			b_data->angle_delta_y = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Angle_Delta[b_data->YMode - V_PRED],(2 * MAX_ANGLE_DELTA + 1) + 1);// S()
			b_data->AngleDeltaY = b_data->angle_delta_y - MAX_ANGLE_DELTA;
		}
	}
}


int frame::intra_angle_info_uv(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx){
	b_data->AngleDeltaUV = 0;
	if ( b_data->MiSize >= BLOCK_8X8 ) {
		if ( is_directional_mode( b_data->UVMode ) ) {
			printf("decodeSymbol angle_delta_uv\n");
			b_data->angle_delta_uv = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Angle_Delta[b_data->UVMode - V_PRED],(2 * MAX_ANGLE_DELTA + 1) + 1); //S()
			b_data->AngleDeltaUV = b_data->angle_delta_uv - MAX_ANGLE_DELTA;
		}
	}
}
int frame::read_cfl_alphas(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	printf("decodeSymbol cfl_alpha_signs\n");
	int cfl_alpha_signs = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Cfl_Sign,CFL_JOINT_SIGNS + 1); // S()
	int signU = (cfl_alpha_signs + 1) / 3;
	int signV = (cfl_alpha_signs + 1) % 3;
	if (signU != CFL_SIGN_ZERO)
	{
		//cfl_alpha_u; // S()
		int ctx = (signU - 1) * 3 + signV;
		printf("decodeSymbol CflAlphaU\n");
		b_data->CflAlphaU = 1 + sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Cfl_Alpha[ctx],CFL_ALPHABET_SIZE + 1);
		if (signU == CFL_SIGN_NEG)
			b_data->CflAlphaU = -b_data->CflAlphaU;
	}
	else
	{
		b_data->CflAlphaU = 0;
	}
	if (signV != CFL_SIGN_ZERO)
	{
	//	cfl_alpha_v; // S()
		int ctx = (signV - 1) * 3 + signU;
		printf("decodeSymbol CflAlphaV\n");
		b_data->CflAlphaV = 1 + sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Cfl_Alpha[ctx],CFL_ALPHABET_SIZE + 1);

		if (signV == CFL_SIGN_NEG)
			b_data->CflAlphaV = -b_data->CflAlphaV;
	}
	else
	{
		b_data->CflAlphaV = 0;
	}
}
int frame::palette_mode_info(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int bsizeCtx = Mi_Width_Log2[b_data->MiSize] + Mi_Height_Log2[b_data->MiSize] - 2;
	int BitDepth = seqHdr->color_config.BitDepth;
	int paletteBits;
	//int has_palette_y;
	if (b_data->YMode == DC_PRED)
	{
		
		int ctx = 0;
		if ( b_data->AvailU && av1Ctx->PaletteSizes[ 0 ][ b_data->MiRow - 1 ][ b_data->MiCol ] > 0 )
			ctx += 1;
		if ( b_data->AvailL && av1Ctx->PaletteSizes[ 0 ][ b_data->MiRow ][ b_data->MiCol - 1 ] > 0 )
			ctx += 1;
		//has_palette_y; // S()
		printf("decodeSymbol has_palette_y\n");
		b_data->has_palette_y = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Palette_Y_Mode[bsizeCtx][ctx],3);
		if (b_data->has_palette_y )
		{
		//	palette_size_y_minus_2; // S()
		printf("decodeSymbol PaletteSizeY\n");
			b_data->PaletteSizeY = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Palette_Y_Size[bsizeCtx],PALETTE_SIZES + 1) + 2;
			b_data->palette_colors_y = new uint16_t[b_data->PaletteSizeY];
			b_data->PaletteCache = new uint16_t[b_data->PaletteSizeY];
			int cacheN = get_palette_cache(0,b_data,av1Ctx);
			
			int idx = 0;
			for (int i = 0; i < cacheN && idx < b_data->PaletteSizeY; i++)
			{
				//use_palette_color_cache_y; // L(1)
				printf("read_literal use_palette_color_cache_y\n");
				if (sb->read_literal(sbCtx,bs,1))
				{
						b_data->palette_colors_y[idx] = b_data->PaletteCache[i]; 
						idx++;
				}
			}
			if (idx < b_data->PaletteSizeY)
			{
				printf("read_literal palette_colors_y\n");
				b_data->palette_colors_y[idx] = sb->read_literal(sbCtx,bs,BitDepth); // L(BitDepth)
				idx++;
			}
			if (idx < b_data->PaletteSizeY)
			{
				int minBits = BitDepth - 3;
				//palette_num_extra_bits_y; //L(2)
				printf("read_literal paletteBits\n");
				paletteBits = minBits + sb->read_literal(sbCtx,bs,2);
			}
			while (idx < b_data->PaletteSizeY)
			{
				printf("read_literal palette_delta_y\n");
				int palette_delta_y = sb->read_literal(sbCtx,bs,paletteBits); // L(paletteBits)
				palette_delta_y++;
				b_data->palette_colors_y[idx] = Clip1(b_data->palette_colors_y[idx - 1] + palette_delta_y,seqHdr->color_config.BitDepth);
				int range = (1 << BitDepth) - b_data->palette_colors_y[idx] - 1 ;
				paletteBits = Min(paletteBits, CeilLog2(range));
				idx++;
			}
			//!!!!
			av1sort(b_data->palette_colors_y, 0, b_data->PaletteSizeY - 1);
		}
	}
	if (b_data->HasChroma && b_data->UVMode == DC_PRED)
	{
		//has_palette_uv; // S()
		int ctx = ( b_data->PaletteSizeY > 0 ) ? 1 : 0;
		printf("decodeSymbol has_palette_uv\n");
		b_data->has_palette_uv = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Palette_Uv_Mode[ctx],3);
		if (b_data->has_palette_uv)
		{
			//palette_size_uv_minus_2; // S()
			printf("decodeSymbol PaletteSizeUV\n");
			b_data->PaletteSizeUV = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Palette_Uv_Size[bsizeCtx],PALETTE_SIZES + 1) + 2;
			b_data->palette_colors_u = new uint16_t[b_data->PaletteSizeUV];
			b_data->palette_colors_v = new uint16_t[b_data->PaletteSizeUV];
			if(!b_data->has_palette_y){
				b_data->PaletteCache = new uint16_t[b_data->PaletteSizeUV];
			}
			int cacheN = get_palette_cache(1, b_data,av1Ctx);
			int idx = 0;
			for (int i = 0; i < cacheN && idx < b_data->PaletteSizeUV; i++)
			{
				//use_palette_color_cache_u; // L(1)
				printf("read_literal use_palette_color_cache_u\n");
				if (sb->read_literal(sbCtx,bs,1))
				{
						b_data->palette_colors_u[idx] = b_data->PaletteCache[i];
						idx++;
				}
			}
			if (idx < b_data->PaletteSizeUV)
			{
				printf("read_literal palette_colors_u\n");
				b_data->palette_colors_u[idx] = sb->read_literal(sbCtx,bs,BitDepth); // L(BitDepth)
				idx++;
			}
			if (idx < b_data->PaletteSizeUV)
			{
				int minBits = BitDepth - 3;
				//palette_num_extra_bits_u; // L(2)
				printf("read_literal paletteBits\n");
				paletteBits = minBits + sb->read_literal(sbCtx,bs,2);
			}
			while (idx < b_data->PaletteSizeUV)
			{
				//palette_delta_u; // L(paletteBits)
				b_data->palette_colors_u[idx] = Clip1(b_data->palette_colors_u[idx - 1] + sb->read_literal(sbCtx,bs,paletteBits),seqHdr->color_config.BitDepth);
				int range = (1 << BitDepth) - b_data->palette_colors_u[idx];
				paletteBits = Min(paletteBits, CeilLog2(range));
				idx++;
			}
			av1sort(b_data->palette_colors_u, 0, b_data->PaletteSizeUV - 1);
			//delta_encode_palette_colors_v; // L(1)
			printf("read_literal delta_encode_palette_colors_v\n");
			if (sb->read_literal(sbCtx,bs,1))
			{
				int minBits = BitDepth - 4;
				int maxVal = 1 << BitDepth;
				//palette_num_extra_bits_v; // L(2)
				printf("read_literal paletteBits\n");
				paletteBits = minBits + sb->read_literal(sbCtx,bs,2);
				printf("read_literal palette_colors_v\n");
				b_data->palette_colors_v[0] = sb->read_literal(sbCtx,bs,BitDepth); // L(BitDepth)
				for (idx = 1; idx < b_data->PaletteSizeUV; idx++)
				{
					printf("read_literal palette_delta_v\n");
					int palette_delta_v = sb->read_literal(sbCtx,bs,paletteBits); // L(paletteBits)
					if (palette_delta_v)
					{
						printf("read_literal palette_delta_sign_bit_v\n");
						//palette_delta_sign_bit_v; // L(1)
						if (sb->read_literal(sbCtx,bs,1))
						{
							palette_delta_v = -palette_delta_v;
						}
					}
					int val = b_data->palette_colors_v[idx - 1] + palette_delta_v;
					if (val < 0)
					val += maxVal;
					if (val >= maxVal)
					val -= maxVal;

					b_data->palette_colors_v[idx] = Clip1(val,seqHdr->color_config.BitDepth);
				}
			}
			else
			{
				for (idx = 0; idx < b_data->PaletteSizeUV; idx++)
				{
					printf("read_literal palette_colors_v\n");
						b_data->palette_colors_v[idx] = sb->read_literal(sbCtx,bs,BitDepth); // L(BitDepth)
				}
			}
		}
	}
}
int frame::filter_intra_mode_info(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	b_data->use_filter_intra = 0;
	if (seqHdr->enable_filter_intra &&
		b_data->YMode == DC_PRED && b_data->PaletteSizeY == 0 &&
		Max(Block_Width[b_data->MiSize], Block_Height[b_data->MiSize]) <= 32)
	{
		printf("decodeSymbol use_filter_intra\n");
		b_data->use_filter_intra = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Filter_Intra[b_data->MiSize],3); // S()
		if (b_data->use_filter_intra)
		{
			printf("decodeSymbol filter_intra_mode\n");
			b_data->filter_intra_mode = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Filter_Intra_Mode,6);// S()
		}
	}
}
int frame::get_palette_cache(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	int aboveN = 0 ;
	if ((b_data->MiRow * MI_SIZE) % 64){
		aboveN = av1Ctx->PaletteSizes[plane][b_data->MiRow - 1][b_data->MiCol];
	} 
	int leftN = 0 ;
	if (b_data->AvailL){
		leftN = av1Ctx->PaletteSizes[plane][b_data->MiRow][b_data->MiCol - 1];
	} 
	int aboveIdx = 0 ;
	int leftIdx = 0 ;
	int n = 0 ;
	while (aboveIdx < aboveN && leftIdx < leftN)
	{
		int aboveC = av1Ctx->PaletteColors[plane][b_data->MiRow - 1][b_data->MiCol][aboveIdx] ;
		int leftC = av1Ctx->PaletteColors[plane][b_data->MiRow][b_data->MiCol - 1][leftIdx] ;
		if (leftC < aboveC)
		{
			if (n == 0 || leftC != b_data->PaletteCache[n - 1])
			{
				b_data->PaletteCache[n] = leftC;
					n++;
			}
			leftIdx++;
		}
		else
		{
			if (n == 0 || aboveC != b_data->PaletteCache[n - 1])
			{
				b_data->PaletteCache[n] = aboveC;
					n++;
			}
			aboveIdx++ ;
			if (leftC == aboveC)
			{
				leftIdx++;
			}
		}
	}
	while (aboveIdx < aboveN)
	{
		int val = av1Ctx->PaletteColors[plane][b_data->MiRow - 1][b_data->MiCol][aboveIdx] ;
		aboveIdx++ ;
		if (n == 0 || val != b_data->PaletteCache[n - 1])
		{
			b_data->PaletteCache[n] = val;
				n++;
		}
	}
	while (leftIdx < leftN)
	{
		int val = av1Ctx->PaletteColors[plane][b_data->MiRow][b_data->MiCol - 1][leftIdx];
		leftIdx++ ;
		if (n == 0 || val != b_data->PaletteCache[n - 1])
		{
			b_data->PaletteCache[n] = val;
				n++;
		}
	}
	return n;
}
int frame::inter_segment_id(int preSkip,SymbolContext *sbCtx, bitSt *bs, BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	if (frameHdr->segmentation_params.segmentation_enabled)
	{
		//predictedSegmentId = get_segment_id();
		int bw4 = Num_4x4_Blocks_Wide[ b_data->MiSize ];
		int bh4 = Num_4x4_Blocks_High[ b_data->MiSize ];
		int xMis = Min( frameHdr->MiCols - b_data->MiCol, bw4 );
		int yMis = Min( frameHdr->MiRows - b_data->MiRow, bh4 );
		int predictedSegmentId = 7;
		for (int y = 0; y < yMis; y++ )
			for (int  x = 0; x < xMis; x++ )
				predictedSegmentId = Min( predictedSegmentId, av1Ctx->PrevSegmentIds[ b_data->MiRow + y ][b_data->MiCol + x ] );

		if (frameHdr->segmentation_params.segmentation_update_map)
		{
			if (preSkip && !frameHdr->segmentation_params.SegIdPreSkip)
			{
				b_data->segment_id = 0;
				return ERROR_CODE;
			}
			int seg_id_predicted;
			if (!preSkip)
			{
				if(b_data->skip)
				{
					seg_id_predicted = 0;
					for (int i = 0; i < Num_4x4_Blocks_Wide[b_data->MiSize]; i++)
						av1Ctx->AboveSegPredContext[b_data->MiCol + i] = seg_id_predicted;
					for (int i = 0; i < Num_4x4_Blocks_High[b_data->MiSize]; i++)
						av1Ctx->LeftSegPredContext[b_data->MiRow + i] = seg_id_predicted;
					read_segment_id( sbCtx, bs, b_data, av1Ctx);
					return ERROR_CODE;
				}
			}
			if (frameHdr->segmentation_params.segmentation_temporal_update == 1)
			{
				int ctx = av1Ctx->LeftSegPredContext[ b_data->MiRow ] + av1Ctx->AboveSegPredContext[ b_data->MiCol ];
				printf("decodeSymbol seg_id_predicted\n");
				seg_id_predicted = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Segment_Id_Predicted[ctx],3); //S()
				if (seg_id_predicted)
					b_data->segment_id = predictedSegmentId;
				else
					read_segment_id(sbCtx, bs,b_data, av1Ctx);
				for (int i = 0; i < Num_4x4_Blocks_Wide[b_data->MiSize]; i++)
					av1Ctx->AboveSegPredContext[b_data->MiCol + i] = seg_id_predicted;
				for (int i = 0; i < Num_4x4_Blocks_High[b_data->MiSize]; i++)
					av1Ctx->LeftSegPredContext[b_data->MiRow + i] = seg_id_predicted;
			}
			else
			{
				read_segment_id(sbCtx, bs, b_data, av1Ctx);
			}
		}
		else
		{
			b_data->segment_id = predictedSegmentId;
		}
	}
	else
	{
		b_data->segment_id = 0;
	}
}
int frame::inter_block_mode_info(SymbolContext *sbCtx, bitSt *bs, BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	b_data->PaletteSizeY = 0;
	b_data->PaletteSizeUV = 0;
	read_ref_frames(sbCtx,bs,b_data,av1Ctx);
	int isCompound = b_data->RefFrame[1] > INTRA_FRAME;
	decode_instance->find_mv_stack(isCompound,sbCtx,bs,b_data,av1Ctx);
	if (b_data->skip_mode)
	{
		b_data->YMode = NEAREST_NEARESTMV;
	}
	else if (seg_instance->seg_feature_active(b_data->segment_id, SEG_LVL_SKIP,frameHdr) ||
			 seg_instance->seg_feature_active(b_data->segment_id ,SEG_LVL_GLOBALMV,frameHdr))
	{
		b_data->YMode = GLOBALMV;
	}
	else if (isCompound)
	{
		int ctx = Compound_Mode_Ctx_Map[ av1Ctx->currentFrame->mvpCtx->RefMvContext >> 1 ][ Min(av1Ctx->currentFrame->mvpCtx->NewMvContext, COMP_NEWMV_CTXS - 1) ];
		printf("decodeSymbol compound_mode\n");
		int compound_mode = 
			sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Compound_Mode[ctx],COMPOUND_MODES + 1); //S()
		b_data->YMode = NEAREST_NEARESTMV + compound_mode;
	}
	else
	{
		//new_mv; //S()
		printf("decodeSymbol new_mv\n");
		if (sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.New_Mv[av1Ctx->currentFrame->mvpCtx->NewMvContext],3) == 0)
		{
			b_data->YMode = NEWMV;
		}
		else
		{
			//zero_mv; //S()
			printf("decodeSymbol zero_mv\n");
			if (sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Zero_Mv[av1Ctx->currentFrame->mvpCtx->ZeroMvContext],3 ) == 0)
			{
				b_data->YMode = GLOBALMV;
			}
			else
			{
				//ref_mv; //S()
				printf("decodeSymbol ref_mv\n");
				b_data->YMode = (sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Ref_Mv[av1Ctx->currentFrame->mvpCtx->RefMvContext],3 ) == 0) ? NEARESTMV : NEARMV;
			}
		}
	}
	av1Ctx->currentFrame->mvpCtx->RefMvIdx = 0;
	if (b_data->YMode == NEWMV || b_data->YMode == NEW_NEWMV)
	{
		for (int idx = 0; idx < 2; idx++)
		{

			if (av1Ctx->currentFrame->mvpCtx->NumMvFound > idx + 1)
			{
				//drl_mode; // S()
				printf("decodeSymbol drl_mode 1\n");
				if (sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Drl_Mode[av1Ctx->currentFrame->mvpCtx->DrlCtxStack[idx]],3 ) == 0)
				{
					av1Ctx->currentFrame->mvpCtx->RefMvIdx = idx;
					break;
				}
				av1Ctx->currentFrame->mvpCtx->RefMvIdx = idx + 1;
			}
		}
	}
	else if (has_nearmv(b_data->YMode))
	{
		av1Ctx->currentFrame->mvpCtx->RefMvIdx = 1;
		for (int idx = 1; idx < 3; idx++)
		{
			if (av1Ctx->currentFrame->mvpCtx->NumMvFound > idx + 1)
			{
				//drl_mode; // S()
				printf("decodeSymbol drl_mode 2\n");
				if (sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Drl_Mode[av1Ctx->currentFrame->mvpCtx->DrlCtxStack[idx]],3 ) == 0)
				{
					av1Ctx->currentFrame->mvpCtx->RefMvIdx = idx;
					break;
				}
				av1Ctx->currentFrame->mvpCtx->RefMvIdx = idx + 1;
			}
		}
	}
	assign_mv(isCompound,sbCtx,bs,b_data,av1Ctx);
	read_interintra_mode(isCompound,sbCtx,bs,b_data,av1Ctx);
	read_motion_mode(isCompound,sbCtx,bs,b_data,av1Ctx);
	read_compound_type(isCompound,sbCtx,bs,b_data,av1Ctx);
	if (frameHdr->interpolation_filter == SWITCHABLE)
	{
		for (int dir = 0; dir < (seqHdr->enable_dual_filter ? 2 : 1); dir++)
		{
			if (needs_interp_filter(b_data,av1Ctx))
			{
				int ctx = ((dir & 1) * 2 + (b_data->RefFrame[1] > INTRA_FRAME)) * 4;
				int leftType = 3;
				int aboveType = 3;
				if (b_data->AvailL)
				{
					if (av1Ctx->RefFrames[b_data->MiRow][b_data->MiCol - 1][0] == b_data->RefFrame[0] ||
						av1Ctx->RefFrames[b_data->MiRow][b_data->MiCol - 1][1] == b_data->RefFrame[0])
						leftType = av1Ctx->InterpFilters[b_data->MiRow][b_data->MiCol - 1][dir];
				}
				if (b_data->AvailU)
				{
					if (av1Ctx->RefFrames[b_data->MiRow - 1][b_data->MiCol][0] == b_data->RefFrame[0] ||
						av1Ctx->RefFrames[b_data->MiRow - 1][b_data->MiCol][1] == b_data->RefFrame[0])
						aboveType = av1Ctx->InterpFilters[b_data->MiRow - 1][b_data->MiCol][dir];
				}
				if (leftType == aboveType)
					ctx += leftType;
				else if (leftType == 3)
					ctx += aboveType;
				else if (aboveType == 3)
					ctx += leftType;
				else
					ctx += 3;
				printf("decodeSymbol interp_filter\n");
				b_data->interp_filter[dir] = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Interp_Filter[ctx],INTERP_FILTERS + 1); // S()
			}
			else
			{
				b_data->interp_filter[dir] = EIGHTTAP;
			}
		}
		if (!seqHdr->enable_dual_filter)
			b_data->interp_filter[1] = b_data->interp_filter[0];
	}
	else
	{
		for (int dir = 0; dir < 2; dir++)
			b_data->interp_filter[dir] = frameHdr->interpolation_filter;
	}
}
int frame::intra_block_mode_info(SymbolContext *sbCtx, bitSt *bs,BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;

	b_data->RefFrame[0] = INTRA_FRAME;
	b_data->RefFrame[1] = NONE;
	//y_mode; //S()
	printf("decodeSymbol intra  YMode\n");
	b_data->YMode = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Y_Mode[Size_Group[b_data->MiSize ]],INTRA_MODES + 1);
	intra_angle_info_y(sbCtx,bs,b_data,av1Ctx);
	if (b_data->HasChroma)
	{
		//uv_mode; //S()
		uint16_t *uv_mode_cdf;
		int size;
		if(b_data->Lossless && 
				BLOCK_4X4 == get_plane_residual_size( b_data->MiSize, 1 ,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y)){
				uv_mode_cdf = av1Ctx->tileSavedCdf.Uv_Mode_Cfl_Allowed[b_data->YMode];
				size = UV_INTRA_MODES_CFL_ALLOWED + 1;
		// Block_Width[ x ] is defined to be equal to 4 * Num_4x4_Blocks_Wide[ x ].
		//Block_Height[ x ] is defined to be equal to Block_Height[ x ].
		}else if(!b_data->Lossless && Max( Block_Width[ b_data->MiSize ], Block_Height[ b_data->MiSize ] ) <= 32){
				uv_mode_cdf = av1Ctx->tileSavedCdf.Uv_Mode_Cfl_Allowed[b_data->YMode];
				size = UV_INTRA_MODES_CFL_ALLOWED + 1;
		}else{
				uv_mode_cdf = av1Ctx->tileSavedCdf.Uv_Mode_Cfl_Not_Allowed[b_data->YMode];
				size = UV_INTRA_MODES_CFL_NOT_ALLOWED + 1;
		}
		//uv_mode ;//S()
		printf("decodeSymbol UVMode intra\n");
		b_data->UVMode = sb->decodeSymbol(sbCtx,bs,uv_mode_cdf,size);

		if (b_data->UVMode == UV_CFL_PRED)
		{
			read_cfl_alphas(sbCtx,bs,b_data,av1Ctx);
		}
		intra_angle_info_uv(sbCtx,bs,b_data,av1Ctx);
	}
	b_data->PaletteSizeY = 0;
	b_data->PaletteSizeUV = 0;
	if (b_data->MiSize >= BLOCK_8X8 &&
		Block_Width[b_data->MiSize] <= 64 &&
		Block_Height[b_data->MiSize] <= 64 &&
		frameHdr->allow_screen_content_tools)
		palette_mode_info(sbCtx,bs,b_data,av1Ctx);
	filter_intra_mode_info(sbCtx,bs,b_data,av1Ctx);
}
int frame::read_interintra_mode(int isCompound,SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	if (!b_data->skip_mode && seqHdr->enable_interintra_compound && !isCompound &&
		b_data->MiSize >= BLOCK_8X8 && b_data->MiSize <= BLOCK_32X32)
	{
		int ctx = Size_Group[ b_data->MiSize ] - 1;
		printf("decodeSymbol interintra\n");
		b_data->interintra = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Inter_Intra[ctx],3); // S()
		if (b_data->interintra)
		{
			printf("decodeSymbol interintra_mode\n");
			b_data->interintra_mode = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Inter_Intra_Mode[ctx],INTERINTRA_MODES + 1); //S()
			b_data->RefFrame[1] = INTRA_FRAME;
			b_data->AngleDeltaY = 0;
			b_data->AngleDeltaUV = 0;
			b_data->use_filter_intra = 0;
			printf("decodeSymbol wedge_interintra\n");
			b_data->wedge_interintra = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Wedge_Inter_Intra[b_data->MiSize],3); //S()
			if (b_data->wedge_interintra)
			{
				printf("decodeSymbol wedge_index\n");
				b_data->wedge_index = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Wedge_Index[b_data->MiSize],16 + 1); //S()
				b_data->wedge_sign = 0;
			}
		}
	}
	else
	{
		b_data->interintra = 0;
	}
}
int frame::read_motion_mode(int isCompound,SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if (b_data->skip_mode)
	{
		b_data->motion_mode = SIMPLE;
		return ERROR_CODE;
	}
	if (!frameHdr->is_motion_mode_switchable)
	{
		b_data->motion_mode = SIMPLE;
		return ERROR_CODE;
	}
	if (Min(Block_Width[b_data->MiSize],
			Block_Height[b_data->MiSize]) < 8)
	{
		b_data->motion_mode = SIMPLE;
		return ERROR_CODE;
	}
	if (!frameHdr->force_integer_mv &&
		(b_data->YMode == GLOBALMV || b_data->YMode == GLOBAL_GLOBALMV))
	{
		if (frameHdr->global_motion_params.GmType[b_data->RefFrame[0]] > TRANSLATION)
		{
			b_data->motion_mode = SIMPLE;
			return ERROR_CODE;
		}
	}
	if (isCompound || b_data->RefFrame[1] == INTRA_FRAME || !decode_instance->has_overlappable_candidates(b_data,av1Ctx))
	{
		b_data->motion_mode = SIMPLE;
		return ERROR_CODE;
	}
	decode_instance->find_warp_samples(sbCtx,bs,b_data,av1Ctx);
	if (frameHdr->force_integer_mv || av1Ctx->currentFrame->mvpCtx->NumSamples == 0 ||
		!frameHdr->allow_warped_motion || is_scaled(b_data->RefFrame[0],frameHdr->ref_frame_idx,av1Ctx->RefUpscaledWidth,
											av1Ctx->RefFrameHeight,frameHdr->si.FrameWidth,frameHdr->si.RenderHeight))
	{
		printf("decodeSymbol use_obmc\n");
		int use_obmc = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Use_Obmc[b_data->MiSize],3); // S()
		b_data->motion_mode = use_obmc ? OBMC : SIMPLE;
	}
	else
	{
		printf("decodeSymbol motion_mode\n");
		b_data->motion_mode = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Motion_Mode[b_data->MiSize],MOTION_MODES + 1); //S()
	}
}
int frame::read_compound_type(int isCompound,SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	b_data->comp_group_idx = 0;
	b_data->compound_idx = 1;
	if (b_data->skip_mode)
	{
		b_data->compound_type = COMPOUND_AVERAGE;
		return ERROR_CODE;
	}
	if (isCompound)
	{
		int n = Wedge_Bits[b_data->MiSize];
		if (seqHdr->enable_masked_compound)
		{
			int ctx = 0;
			if (b_data->AvailU)
			{
				if (!b_data->AboveSingle)
					ctx += av1Ctx->CompGroupIdxs[b_data->MiRow - 1][b_data->MiCol];
				else if (b_data->AboveRefFrame[0] == ALTREF_FRAME)
					ctx += 3;
			}
			if (b_data->AvailL)
			{
				if (!b_data->LeftSingle)
					ctx += av1Ctx->CompGroupIdxs[b_data->MiRow][b_data->MiCol - 1];
				else if (b_data->LeftRefFrame[0] == ALTREF_FRAME)
					ctx += 3;
			}
			ctx = Min(5, ctx);
			printf("decodeSymbol comp_group_idx\n");
			b_data->comp_group_idx = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Group_Idx[ctx],3); // S()
		}
		if (b_data->comp_group_idx == 0)
		{
			if (seqHdr->enable_jnt_comp)
			{

				int fwd = Abs(get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits ,frameHdr->OrderHints[b_data->RefFrame[0]], frameHdr->OrderHint));
				int bck = Abs(get_relative_dist(seqHdr->enable_order_hint,seqHdr->OrderHintBits ,frameHdr->OrderHints[b_data->RefFrame[1]], frameHdr->OrderHint));
				int ctx = (fwd == bck) ? 3 : 0;
				if (b_data->AvailU)
				{
					if (!b_data->AboveSingle)
						ctx += av1Ctx->CompoundIdxs[b_data->MiRow - 1][b_data->MiCol];
					else if (b_data->AboveRefFrame[0] == ALTREF_FRAME)
						ctx++;
				}
				if (b_data->AvailL)
				{
					if (!b_data->LeftSingle)
						ctx += av1Ctx->CompoundIdxs[b_data->MiRow][b_data->MiCol - 1];
					else if (b_data->LeftRefFrame[0] == ALTREF_FRAME)
						ctx++;
				}
				printf("decodeSymbol compound_idx\n");
				b_data->compound_idx = sb->decodeSymbol(sbCtx, bs, av1Ctx->tileSavedCdf.Compound_Idx[ctx], 3); // S()
				b_data->compound_type = b_data->compound_idx ? COMPOUND_AVERAGE : COMPOUND_DISTANCE;
			}
			else
			{
				b_data->compound_type = COMPOUND_AVERAGE;
			}
		}
		else
		{
			if (n == 0)
			{
				b_data->compound_type = COMPOUND_DIFFWTD;
			}
			else
			{
				printf("decodeSymbol compound_type\n");
				b_data->compound_type = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Compound_Type[b_data->MiSize],COMPOUND_TYPES + 1); // S()
			}
		}
		if (b_data->compound_type == COMPOUND_WEDGE)
		{
			printf("decodeSymbol wedge_index\n");
			b_data->wedge_index = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Wedge_Index[b_data->MiSize],16 + 1); // S()
			printf("read_literal wedge_sign\n");
			b_data->wedge_sign = sb->read_literal(sbCtx,bs,1);	 // L(1)
		}
		else if (b_data->compound_type == COMPOUND_DIFFWTD)
		{
			printf("read_literal mask_type\n");
			b_data->mask_type = sb->read_literal(sbCtx,bs,1); // L(1)
		}
	}
	else
	{
		if (b_data->interintra)
		{
			b_data->compound_type = b_data->wedge_interintra ? COMPOUND_WEDGE : COMPOUND_INTRA;
		}
		else
		{
			b_data->compound_type = COMPOUND_AVERAGE;
		}
	}
}
int frame::read_ref_frames(SymbolContext *sbCtx, bitSt *bs, BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if (b_data->skip_mode)
	{
		b_data->RefFrame[0] = frameHdr->SkipModeFrame[0];
		b_data->RefFrame[1] = frameHdr->SkipModeFrame[1];
	}
	else if (seg_instance->seg_feature_active(b_data->segment_id ,SEG_LVL_REF_FRAME,frameHdr))
	{
		b_data->RefFrame[0] = frameHdr->segmentation_params.FeatureData[b_data->segment_id][SEG_LVL_REF_FRAME];
		b_data->RefFrame[1] = NONE;
	}
	else if (seg_instance->seg_feature_active(b_data->segment_id,SEG_LVL_SKIP,frameHdr) ||
			 seg_instance->seg_feature_active(b_data->segment_id,SEG_LVL_GLOBALMV,frameHdr))
	{
		b_data->RefFrame[0] = LAST_FRAME;
		b_data->RefFrame[1] = NONE;
	}
	else
	{
		int bw4 = Num_4x4_Blocks_Wide[b_data->MiSize];
		int bh4 = Num_4x4_Blocks_High[b_data->MiSize];
		if (frameHdr->reference_select && (Min(bw4, bh4) >= 2)){
			int ctx;
			if (b_data->AvailU && b_data->AvailL)
			{
				if (b_data->AboveSingle && b_data->LeftSingle)
					ctx = check_backward(b_data->AboveRefFrame[0]) ^ check_backward(b_data->LeftRefFrame[0]);
				else if (b_data->AboveSingle)
					ctx = 2 + (check_backward(b_data->AboveRefFrame[0]) || b_data->AboveIntra);
				else if (b_data->LeftSingle)
					ctx = 2 + (check_backward(b_data->LeftRefFrame[0]) || b_data->LeftIntra);
				else
					ctx = 4;
			}
			else if (b_data->AvailU)
			{
				if (b_data->AboveSingle)
					ctx = check_backward(b_data->AboveRefFrame[0]);
				else
					ctx = 3;
			}
			else if (b_data->AvailL)
			{
				if (b_data->LeftSingle)
					ctx = check_backward(b_data->LeftRefFrame[0]);
				else
					ctx = 3;
			}
			else
			{
				ctx = 1;
			}
			printf("decodeSymbol comp_mode\n");
			b_data->comp_mode = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Mode[ctx],3); // S()
		}else{
			b_data->comp_mode = SINGLE_REFERENCE;
		}
		if (b_data->comp_mode == COMPOUND_REFERENCE)
		{
			int ctx;
			int above0 = b_data->AboveRefFrame[0];
			int above1 = b_data->AboveRefFrame[1];
			int left0 = b_data->LeftRefFrame[0];
			int left1 = b_data->LeftRefFrame[1];
			int aboveCompInter = b_data->AvailU && !b_data->AboveIntra && !b_data->AboveSingle;
			int leftCompInter = b_data->AvailL && !b_data->LeftIntra && !b_data->LeftSingle;
			int aboveUniComp = aboveCompInter && is_samedir_ref_pair(above0, above1);
			int leftUniComp = leftCompInter && is_samedir_ref_pair(left0, left1);
			if (b_data->AvailU && !b_data->AboveIntra && b_data->AvailL && !b_data->LeftIntra)
			{
				int samedir = is_samedir_ref_pair(above0, left0);
				if (!aboveCompInter && !leftCompInter)
				{
					ctx = 1 + 2 * samedir;
				}
				else if (!aboveCompInter)
				{
					if (!leftUniComp)
						ctx = 1;
					else
						ctx = 3 + samedir;
				}
				else if (!leftCompInter)
				{
					if (!aboveUniComp)
						ctx = 1;
					else
						ctx = 3 + samedir;
				}
				else
				{
					if (!aboveUniComp && !leftUniComp)
						ctx = 0;
					else if (!aboveUniComp || !leftUniComp)
						ctx = 2;
					else
						ctx = 3 + ((above0 == BWDREF_FRAME) == (left0 == BWDREF_FRAME));
				}
			}
			else if (b_data->AvailU && b_data->AvailL)
			{
				if (aboveCompInter)
					ctx = 1 + 2 * aboveUniComp;
				else if (leftCompInter)
					ctx = 1 + 2 * leftUniComp;
				else
					ctx = 2;
			}
			else if (aboveCompInter)
			{
				ctx = 4 * aboveUniComp;
			}
			else if (leftCompInter)
			{
				ctx = 4 * leftUniComp;
			}
			else
			{
				ctx = 2;
			}
			printf("decodeSymbol comp_ref_type\n");
			int comp_ref_type = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Ref_Type[ctx],3); // S()
			if (comp_ref_type == UNIDIR_COMP_REFERENCE)
			{
				int fwdCount = count_refs( LAST_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
				fwdCount += count_refs( LAST2_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				fwdCount += count_refs( LAST3_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				fwdCount += count_refs( GOLDEN_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				int bwdCount = count_refs( BWDREF_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				bwdCount += count_refs( ALTREF2_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				bwdCount += count_refs( ALTREF_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				ctx = ref_count_ctx( fwdCount, bwdCount );
				printf("decodeSymbol uni_comp_ref\n");
				int uni_comp_ref = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Uni_Comp_Ref[ctx][0],3); // S()
				if (uni_comp_ref)
				{
					b_data->RefFrame[0] = BWDREF_FRAME;
					b_data->RefFrame[1] = ALTREF_FRAME;
				}
				else
				{
					int last2Count = count_refs( LAST2_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
					int last3GoldCount = count_refs( LAST3_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame) +
									 count_refs( GOLDEN_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
					ctx = ref_count_ctx( last2Count, last3GoldCount );
					printf("decodeSymbol uni_comp_ref_p1\n");
					int uni_comp_ref_p1 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Uni_Comp_Ref[ctx][1],3); // S()
					if (uni_comp_ref_p1)
					{
						int last3Count = count_refs( LAST3_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
						int goldCount = count_refs( GOLDEN_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
						ctx = ref_count_ctx( last3Count, goldCount );
					printf("decodeSymbol uni_comp_ref_p2\n");
						int uni_comp_ref_p2 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Uni_Comp_Ref[ctx][2],3); // S()
						if (uni_comp_ref_p2)
						{
							b_data->RefFrame[0] = LAST_FRAME;
							b_data->RefFrame[1] = GOLDEN_FRAME;
						}
						else
						{
							b_data->RefFrame[0] = LAST_FRAME;
							b_data->RefFrame[1] = LAST3_FRAME;
						}
					}
					else
					{
						b_data->RefFrame[0] = LAST_FRAME;
						b_data->RefFrame[1] = LAST2_FRAME;
					}
				}
			}
			else
			{
				int last12Count = count_refs( LAST_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame ) + 
								count_refs( LAST2_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				int last3GoldCount = count_refs( LAST3_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame) + 
								count_refs( GOLDEN_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				ctx = ref_count_ctx( last12Count, last3GoldCount );
					printf("decodeSymbol comp_ref\n");
				int comp_ref = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Ref[ctx][0],3); // S()
				if (comp_ref == 0)
				{
					int lastCount = count_refs( LAST_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
					int last2Count = count_refs( LAST2_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
					ctx = ref_count_ctx( lastCount, last2Count );
					printf("decodeSymbol comp_ref_p1\n");
					int comp_ref_p1 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Ref[ctx][1],3); // S()
					b_data->RefFrame[0] = comp_ref_p1 ? LAST2_FRAME : LAST_FRAME;
				}
				else
				{
					int last3Count = count_refs( LAST3_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame  );
					int goldCount = count_refs( GOLDEN_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame  );
					ctx = ref_count_ctx( last3Count, goldCount );
					printf("decodeSymbol comp_ref_p2\n");
					int comp_ref_p2 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Ref[ctx][2],3); // S()
					b_data->RefFrame[0] = comp_ref_p2 ? GOLDEN_FRAME : LAST3_FRAME;
				}

				int brfarf2Count = count_refs( BWDREF_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame) + 
								count_refs( ALTREF2_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				int arfCount = count_refs( ALTREF_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
				ctx = ref_count_ctx( brfarf2Count, arfCount );
				printf("decodeSymbol comp_bwdref\n");
				int comp_bwdref = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Bwd_Ref[ctx][0],3); /// S()
				if (comp_bwdref == 0)
				{
					int brfCount = count_refs( BWDREF_FRAME,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame );
					int arf2Count = count_refs( ALTREF2_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
					ctx = ref_count_ctx( brfCount, arf2Count );
					printf("decodeSymbol comp_bwdref_p1\n");
					int comp_bwdref_p1 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Comp_Bwd_Ref[ctx][1],3); // S()
					b_data->RefFrame[1] = comp_bwdref_p1 ? ALTREF2_FRAME : BWDREF_FRAME;
				}
				else
				{
					b_data->RefFrame[1] = ALTREF_FRAME;
				}
			}
		}
		else
		{
			int ctx;
			int fwdCount = count_refs( LAST_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
			fwdCount += count_refs( LAST2_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
			fwdCount += count_refs( LAST3_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
			fwdCount += count_refs( GOLDEN_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
			int bwdCount = count_refs( BWDREF_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
			bwdCount += count_refs( ALTREF2_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
			bwdCount += count_refs( ALTREF_FRAME ,b_data->AvailU,b_data->AvailL,b_data->AboveRefFrame,b_data->LeftRefFrame);
			ctx = ref_count_ctx( fwdCount, bwdCount );
			printf("decodeSymbol single_ref_p1\n");
			int single_ref_p1 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Single_Ref[ctx][0],3); // S()
			if (single_ref_p1)
			{
				printf("decodeSymbol single_ref_p2\n");
				int single_ref_p2 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Single_Ref[ctx][1],3); // S()
				if (single_ref_p2 == 0)
				{
					printf("decodeSymbol single_ref_p6\n");
					int single_ref_p6 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Single_Ref[ctx][5],3); // S()
					b_data->RefFrame[0] = single_ref_p6 ? ALTREF2_FRAME : BWDREF_FRAME;
				}
				else
				{
					b_data->RefFrame[0] = ALTREF_FRAME;
				}
			}
			else
			{
				printf("decodeSymbol single_ref_p3\n");
				int single_ref_p3 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Single_Ref[ctx][2],3); // S()
				if (single_ref_p3)
				{
					printf("decodeSymbol single_ref_p5\n");
					int single_ref_p5 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Single_Ref[ctx][4],3); // S()
					b_data->RefFrame[0] = single_ref_p5 ? GOLDEN_FRAME : LAST3_FRAME;
				}
				else
				{
					printf("decodeSymbol single_ref_p4\n");
					int single_ref_p4 = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Single_Ref[ctx][3],3); // S()
					b_data->RefFrame[0] = single_ref_p4 ? LAST2_FRAME : LAST_FRAME;
				}
			}
			b_data->RefFrame[1] = NONE;
		}
	}
}
int frame::palette_tokens(SymbolContext *sbCtx, bitSt *bs, BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int blockHeight = Block_Height[b_data->MiSize];
	int blockWidth = Block_Width[b_data->MiSize];
	int onscreenHeight = Min(blockHeight, (frameHdr->MiRows - b_data->MiRow) * MI_SIZE);
	int onscreenWidth = Min(blockWidth, (frameHdr->MiCols - b_data->MiCol) * MI_SIZE);
	if (b_data->PaletteSizeY)
	{
		printf("readNS color_index_map_y\n");
		int color_index_map_y = sb->readNS(sbCtx,bs,b_data->PaletteSizeY); // NS(PaletteSizeY)
		b_data->ColorMapY = new  uint8_t*[blockHeight];
		for(int i = 0 ; i < blockHeight; i++){
			b_data->ColorMapY[i] = new uint8_t[blockWidth];
		}

		b_data->ColorMapY[0][0] = color_index_map_y;
		for (int i = 1; i < onscreenHeight + onscreenWidth - 1; i++)
		{
			for (int j = Min(i, onscreenWidth - 1);
				 j >= Max(0, i - onscreenHeight + 1); j--)
			{
				get_palette_color_context(b_data->ColorMapY, (i - j), j, b_data->PaletteSizeY,b_data);
				
				uint16_t *cdf;
				int ctx = Palette_Color_Context[ b_data->ColorContextHash ];
				switch(b_data->PaletteSizeY){
					case 2: cdf = av1Ctx->tileSavedCdf.Palette_Size_2_Y_Color[ctx]; break;
					case 3:	cdf = av1Ctx->tileSavedCdf.Palette_Size_3_Y_Color[ctx]; break;
					case 4:	cdf = av1Ctx->tileSavedCdf.Palette_Size_4_Y_Color[ctx]; break;
					case 5:	cdf = av1Ctx->tileSavedCdf.Palette_Size_5_Y_Color[ctx]; break;
					case 6:	cdf = av1Ctx->tileSavedCdf.Palette_Size_6_Y_Color[ctx]; break;
					case 7:	cdf = av1Ctx->tileSavedCdf.Palette_Size_7_Y_Color[ctx]; break;
					case 8:	cdf = av1Ctx->tileSavedCdf.Palette_Size_8_Y_Color[ctx]; break;
					default:
						break;
				}
				//这里的size计算 取了个巧
				printf("decodeSymbol palette_color_idx_y\n");
				int palette_color_idx_y =  sb->decodeSymbol(sbCtx,bs,cdf, b_data->PaletteSizeY + 1); // S()
				b_data->ColorMapY[i - j][j] = b_data->ColorOrder[palette_color_idx_y];
			}
		}
		for (int i = 0; i < onscreenHeight; i++)
		{
			for (int j = onscreenWidth; j < blockWidth; j++)
			{
				b_data->ColorMapY[i][j] = b_data->ColorMapY[i][onscreenWidth - 1];
			}
		}
		for (int i = onscreenHeight; i < blockHeight; i++)
		{
			for (int j = 0; j < blockWidth; j++)
			{
				b_data->ColorMapY[i][j] = b_data->ColorMapY[onscreenHeight - 1][j];
			}
		}
	}
	if (b_data->PaletteSizeUV)
	{
		printf("readNS color_index_map_uv\n");
		int color_index_map_uv = sb->readNS(sbCtx,bs,b_data->PaletteSizeUV); // NS(PaletteSizeUV)
		blockHeight = blockHeight >> seqHdr->color_config.subsampling_y;
		blockWidth = blockWidth >> seqHdr->color_config.subsampling_x;
		
		b_data->ColorMapUV = new  uint8_t*[blockHeight];
		for(int i = 0 ; i < blockHeight; i++){
			b_data->ColorMapUV[i] = new uint8_t[blockWidth];
		}

		b_data->ColorMapUV[0][0] = color_index_map_uv;

		onscreenHeight = onscreenHeight >> seqHdr->color_config.subsampling_y;
		onscreenWidth = onscreenWidth >> seqHdr->color_config.subsampling_x;
		if (blockWidth < 4)
		{
			blockWidth += 2;
			onscreenWidth += 2;
		}
		if (blockHeight < 4)
		{
			blockHeight += 2;
			onscreenHeight += 2;
		}
		for (int i = 1; i < onscreenHeight + onscreenWidth - 1; i++)
		{
			for (int j = Min(i, onscreenWidth - 1); j >= Max(0, i - onscreenHeight + 1); j--)
			{
				get_palette_color_context(b_data->ColorMapUV, (i - j), j, b_data->PaletteSizeUV,b_data);
				uint16_t *cdf;
				int ctx = Palette_Color_Context[ b_data->ColorContextHash ];
				switch(b_data->PaletteSizeY){
					case 2: cdf = av1Ctx->tileSavedCdf.Palette_Size_2_Uv_Color[ctx]; break;
					case 3:	cdf = av1Ctx->tileSavedCdf.Palette_Size_3_Uv_Color[ctx]; break;
					case 4:	cdf = av1Ctx->tileSavedCdf.Palette_Size_4_Uv_Color[ctx]; break;
					case 5:	cdf = av1Ctx->tileSavedCdf.Palette_Size_5_Uv_Color[ctx]; break;
					case 6:	cdf = av1Ctx->tileSavedCdf.Palette_Size_6_Uv_Color[ctx]; break;
					case 7:	cdf = av1Ctx->tileSavedCdf.Palette_Size_7_Uv_Color[ctx]; break;
					case 8:	cdf = av1Ctx->tileSavedCdf.Palette_Size_8_Uv_Color[ctx]; break;
					default:
						break;
				}
				printf("decodeSymbol palette_color_idx_uv\n");
				int palette_color_idx_uv = sb->decodeSymbol(sbCtx,bs,cdf, b_data->PaletteSizeY + 1); // S()
				b_data->ColorMapUV[i - j][j] = b_data->ColorOrder[palette_color_idx_uv];
			}
		}
		for (int i = 0; i < onscreenHeight; i++)
		{
			for (int j = onscreenWidth; j < blockWidth; j++)
			{
				b_data->ColorMapUV[i][j] = b_data->ColorMapUV[i][onscreenWidth - 1];
			}
		}
		for (int i = onscreenHeight; i < blockHeight; i++)
		{
			for (int j = 0; j < blockWidth; j++)
			{
				b_data->ColorMapUV[i][j] = b_data->ColorMapUV[onscreenHeight - 1][j];
			}
		}
	}
}
int frame::read_block_tx_size(SymbolContext *sbCtx, bitSt *bs,BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int bw4 = Num_4x4_Blocks_Wide[b_data->MiSize];
	int bh4 = Num_4x4_Blocks_High[b_data->MiSize];
	if (frameHdr->TxMode == TX_MODE_SELECT &&
		b_data->MiSize > BLOCK_4X4 && b_data->is_inter &&
		!b_data->skip && !b_data->Lossless)
	{
		printf("read_var_tx_size\n");
		int maxTxSz = Max_Tx_Size_Rect[b_data->MiSize];
		int txW4 = Tx_Width[maxTxSz] / MI_SIZE;
		int txH4 = Tx_Height[maxTxSz] / MI_SIZE;
		for (int row = b_data->MiRow; row < b_data->MiRow + bh4; row += txH4)
			for (int col = b_data->MiCol; col < b_data->MiCol + bw4; col += txW4)
				read_var_tx_size(row, col, maxTxSz, 0,sbCtx,bs,b_data,av1Ctx);
	}
	else
	{
		printf("read_tx_size\n");
		read_tx_size(!b_data->skip || !b_data->is_inter,sbCtx, bs, b_data,av1Ctx);
		printf("read_tx_size 2\n");
		for (int row = b_data->MiRow; row < b_data->MiRow + bh4; row++)
			for (int col = b_data->MiCol; col < b_data->MiCol + bw4; col++)
				av1Ctx->InterTxSizes[row][col] = b_data->TxSize;
	}
}
int frame::read_var_tx_size(int row,int col,int txSz,int depth,SymbolContext *sbCtx, bitSt *bs,BlockData *b_data, AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	if (row >= frameHdr->MiRows || col >= frameHdr->MiCols)
		return ERROR_CODE;
	int txfm_split;
	if (txSz == TX_4X4 || depth == MAX_VARTX_DEPTH)
	{
		txfm_split = 0;
	}
	else
	{
		int above = decode_instance->get_above_tx_width( row, col ,b_data,av1Ctx) < Tx_Width[ txSz ];
		int left = decode_instance->get_left_tx_height( row, col,b_data,av1Ctx ) < Tx_Height[ txSz ];
		int size = Min( 64, Max( Block_Width[ b_data->MiSize ], Block_Height[ b_data->MiSize ] ) );
		int maxTxSz = find_tx_size( size, size );
		int txSzSqrUp = Tx_Size_Sqr_Up[ txSz ];
		int ctx = (txSzSqrUp != maxTxSz) * 3 + (TX_SIZES - 1 - maxTxSz) * 6 + above + left;
		printf("decodeSymbol txfm_split\n");
		txfm_split = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Txfm_Split[ctx],3); // S()！！！
	}
	int w4 = Tx_Width[txSz] / MI_SIZE;
	int h4 = Tx_Height[txSz] / MI_SIZE;
	if (txfm_split)
	{
		int subTxSz = Split_Tx_Size[txSz];
		int stepW = Tx_Width[subTxSz] / MI_SIZE;
		int stepH = Tx_Height[subTxSz] / MI_SIZE;
		for (int i = 0; i < h4; i += stepH)
			for (int j = 0; j < w4; j += stepW)
				read_var_tx_size(row + i, col + j, subTxSz, depth + 1,
					 sbCtx, bs, b_data,  av1Ctx);
	}
	else
	{
		for (int i = 0; i < h4; i++)
			for (int j = 0; j < w4; j++)
				av1Ctx->InterTxSizes[row + i][col + j] = txSz;
		b_data->TxSize = txSz;
	}
}
int frame::read_tx_size(int allowSelect, SymbolContext *sbCtx, bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	//printf("read_tx_size 11\n");
	if (b_data->Lossless)
	{
		//printf("read_tx_size 12\n");
		b_data->TxSize = TX_4X4;
		return ERROR_CODE;
	}
	//printf("read_tx_size 13\n");
	int maxRectTxSize = Max_Tx_Size_Rect[b_data->MiSize];
	int maxTxDepth = Max_Tx_Depth[b_data->MiSize];
	b_data->TxSize = maxRectTxSize;
	printf(" b_data->TxSize  %d\n",b_data->TxSize );
	//printf("read_tx_size %d %d %d %d\n",b_data->MiSize ,BLOCK_4X4, allowSelect , frameHdr->TxMode);
	if (b_data->MiSize > BLOCK_4X4 && allowSelect && frameHdr->TxMode == TX_MODE_SELECT)
	{
		int ctx;
		int maxTxWidth = Tx_Width[maxRectTxSize];
		int maxTxHeight = Tx_Height[maxRectTxSize];
		int aboveW;
		int leftH;
		if (b_data->AvailU && av1Ctx->IsInters[b_data->MiRow - 1][b_data->MiCol])
		{
			aboveW = Block_Width[av1Ctx->MiSizes[b_data->MiRow - 1][b_data->MiCol]];
		}
		else if (b_data->AvailU)
		{
			aboveW = decode_instance->get_above_tx_width(b_data->MiRow, b_data->MiCol,b_data,av1Ctx);
		}
		else
		{
			aboveW = 0;
		}
		if (b_data->AvailL && av1Ctx->IsInters[b_data->MiRow][b_data->MiCol - 1])
		{
			leftH = Block_Height[av1Ctx->MiSizes[b_data->MiRow][b_data->MiCol - 1]];
		}
		else if (b_data->AvailL)
		{
			leftH = decode_instance->get_left_tx_height(b_data->MiRow, b_data->MiCol,b_data,av1Ctx);
		}
		else
		{
			leftH = 0;
		}
		ctx = (aboveW >= maxTxWidth) + (leftH >= maxTxHeight);

		uint16_t *cdf;
		switch (maxTxDepth)
		{
			case 2 : cdf = av1Ctx->tileSavedCdf.Tx_16x16[ctx]; break;
			case 3 : cdf = av1Ctx->tileSavedCdf.Tx_32x32[ctx]; break;
			case 4 : cdf = av1Ctx->tileSavedCdf.Tx_64x64[ctx]; break;
			default:
				cdf = av1Ctx->tileSavedCdf.Tx_8x8[ctx]; 
				break;
		}
		int size = maxTxDepth >= 2 ? MAX_TX_DEPTH + 2 : MAX_TX_DEPTH + 1;
		printf("decodeSymbol tx_depth\n");
		int tx_depth = sb->decodeSymbol(sbCtx,bs,cdf,size); // S()
		printf("sb tx_depth %d\n",tx_depth);
		for (int i = 0; i < tx_depth; i++)
			b_data->TxSize = Split_Tx_Size[b_data->TxSize];
	}
}

int frame::reset_block_context(int bw4, int bh4,SymbolContext *sbCtx, bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	for (int plane = 0; plane < 1 + 2 * b_data->HasChroma; plane++)
	{
		int subX = (plane > 0) ? seqHdr->color_config.subsampling_x : 0;
		int subY = (plane > 0) ? seqHdr->color_config.subsampling_y : 0;
		for (int i = b_data->MiCol >> subX; i < ((b_data->MiCol + bw4) >> subX); i++)
		{
			av1Ctx->AboveLevelContext[plane][i] = 0;
			av1Ctx->AboveDcContext[plane][i] = 0;
		}
		for (int i = b_data->MiRow >> subY; i < ((b_data->MiRow + bh4) >> subY); i++)
		{
			av1Ctx->LeftLevelContext[plane][i] = 0;
			av1Ctx->LeftDcContext[plane][i] = 0;
		}
	}
}
int frame::compute_prediction(SymbolContext *sbCtx, bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int sbMask = seqHdr->use_128x128_superblock ? 31 : 15;
	int subBlockMiRow = b_data->MiRow & sbMask;
	int subBlockMiCol = b_data->MiCol & sbMask;
	for (int plane = 0; plane < 1 + b_data->HasChroma * 2; plane++)
	{
		int planeSz = get_plane_residual_size(b_data->MiSize, plane,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y);
		int num4x4W = Num_4x4_Blocks_Wide[planeSz];
		int num4x4H = Num_4x4_Blocks_High[planeSz];
		int log2W = MI_SIZE_LOG2 + Mi_Width_Log2[planeSz];
		int log2H = MI_SIZE_LOG2 + Mi_Height_Log2[planeSz];
		int subX = (plane > 0) ? seqHdr->color_config.subsampling_x : 0;
		int subY = (plane > 0) ? seqHdr->color_config.subsampling_y : 0;
		int baseX = (b_data->MiCol >> subX) * MI_SIZE;
		int baseY = (b_data->MiRow >> subY) * MI_SIZE;
		int candRow = (b_data->MiRow >> subY) << subY;
		int candCol = (b_data->MiCol >> subX) << subX;
		int IsInterIntra = (b_data->is_inter && b_data-> RefFrame[1] == INTRA_FRAME);
		if (IsInterIntra)
		{
			int mode;
			if (b_data->interintra_mode == II_DC_PRED)
				mode = DC_PRED;
			else if (b_data->interintra_mode == II_V_PRED)
				mode = V_PRED;
			else if (b_data->interintra_mode == II_H_PRED)
				mode = H_PRED;
			else
				mode = SMOOTH_PRED;
			decode_instance->predict_intra(plane, baseX, baseY,
						  plane == 0 ? b_data->AvailL : b_data->AvailLChroma,
						  plane == 0 ? b_data->AvailU : b_data->AvailUChroma,
						  (*av1Ctx->BlockDecoded)[plane]
									  [(subBlockMiRow >> subY) - 1]
									  [(subBlockMiCol >> subX) + num4x4W],
						  (*av1Ctx->BlockDecoded)[plane]
									  [(subBlockMiRow >> subY) + num4x4H]
									  [(subBlockMiCol >> subX) - 1],
						  mode,
						  log2W, log2H,b_data,av1Ctx);
		}
		if (b_data->is_inter)
		{
			int predW = Block_Width[b_data->MiSize] >> subX;
			int predH = Block_Height[b_data->MiSize] >> subY;
			int someUseIntra = 0;
			for (int r = 0; r < (num4x4H << subY); r++)
				for (int c = 0; c < (num4x4W << subX); c++)
					if (av1Ctx->RefFrames[candRow + r][candCol + c][0] == INTRA_FRAME)
					someUseIntra = 1;
			if (someUseIntra)
			{
				predW = num4x4W * 4;
				predH = num4x4H * 4;
				candRow = b_data->MiRow;
				candCol = b_data->MiCol;
			}
			int r = 0;
			for (int y = 0; y < num4x4H * 4; y += predH)
			{
				int c = 0;
				for (int x = 0; x < num4x4W * 4; x += predW)
				{
					decode_instance->predict_inter(plane, baseX + x, baseY + y,
								  predW, predH,
								  candRow + r, candCol + c,IsInterIntra,b_data,av1Ctx);
					c++;
				}
				r++;
			}
		}
	}
}

int frame::needs_interp_filter(BlockData *b_data,AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	int large = (Min(Block_Width[b_data->MiSize], Block_Height[b_data->MiSize]) >= 8);
	if (b_data->skip_mode || b_data->motion_mode == LOCALWARP)
	{
		return 0;
	}
	else if (large && b_data->YMode == GLOBALMV)
	{
		return frameHdr->global_motion_params.GmType[b_data->RefFrame[0]] == TRANSLATION;
	}
	else if (large && b_data->YMode == GLOBAL_GLOBALMV)
	{
		return frameHdr->global_motion_params.GmType[b_data->RefFrame[0]] == TRANSLATION ||
			   frameHdr->global_motion_params.GmType[b_data->RefFrame[1]] == TRANSLATION;
	}
	else
	{
		return 1;
	}
}
int frame::get_palette_color_context(uint8_t **colorMap,int r,int c,int n,BlockData *b_data)
{
	int scores[PALETTE_COLORS];
	int neighbor;
	for (int i = 0; i < PALETTE_COLORS; i++)
	{
		scores[i] = 0;
		b_data->ColorOrder[i] = i;
	}
	if (c > 0)
	{
		neighbor = colorMap[r][c - 1];
		scores[neighbor] += 2;
	}
	if ((r > 0) && (c > 0))
	{
		neighbor = colorMap[r - 1][c - 1];
		scores[neighbor] += 1;
	}
	if (r > 0)
	{
		neighbor = colorMap[r - 1][c];
		scores[neighbor] += 2;
	}
	for (int i = 0; i < PALETTE_NUM_NEIGHBORS; i++)
	{
		int maxScore = scores[i];
		int maxIdx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (scores[j] > maxScore)
			{
				maxScore = scores[j];
				maxIdx = j;
			}
		}
		if (maxIdx != i)
		{
			maxScore = scores[maxIdx];
			int maxColorOrder = b_data->ColorOrder[maxIdx];
			for (int k = maxIdx; k > i; k--)
			{
				scores[k] = scores[k - 1];
				b_data->ColorOrder[k] = b_data->ColorOrder[k - 1];
			}
			scores[i] = maxScore;
			b_data->ColorOrder[i] = maxColorOrder;
		}
	}
	b_data->ColorContextHash = 0;
	for (int i = 0; i < PALETTE_NUM_NEIGHBORS; i++)
	{
		b_data->ColorContextHash += scores[i] * Palette_Color_Hash_Multipliers[i];
	}
}

int frame::clear_block_decoded_flags(int r, int c, int sbSize4, AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++)
	{
		int subX = (plane > 0) ? seqHdr->color_config.subsampling_x : 0;
		int subY = (plane > 0) ? seqHdr->color_config.subsampling_y : 0;
		int sbWidth4 = (av1Ctx->MiColEnd - c) >> subX;
		int sbHeight4 = (av1Ctx->MiRowEnd - r) >> subY;
		for (int y = -1; y <= (sbSize4 >> subY); y++)
			for (int x = -1; x <= (sbSize4 >> subX); x++)
			{
				if (y < 0 && x < sbWidth4)
					(*av1Ctx->BlockDecoded)[plane][y][x] = 1;
				else if (x < 0 && y < sbHeight4)
					(*av1Ctx->BlockDecoded)[plane][y][x] = 1;
				else
					(*av1Ctx->BlockDecoded)[plane][y][x] = 0;
			}
		(*av1Ctx->BlockDecoded)[plane][sbSize4 >> subY][-1] = 0;
	}
}
int frame::clear_cdef(int r, int c,AV1DecodeContext *av1Ctx)
{
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	av1Ctx->currentFrame->cdef_idx[r][c] = -1;
	if (seqHdr->use_128x128_superblock)
	{
		int cdefSize4 = Num_4x4_Blocks_Wide[BLOCK_64X64];
		av1Ctx->currentFrame->cdef_idx[r][c + cdefSize4] = -1;
		av1Ctx->currentFrame->cdef_idx[r + cdefSize4][c] = -1;
		av1Ctx->currentFrame->cdef_idx[r + cdefSize4][c + cdefSize4] = -1;
	}
}
int frame::read_lr(SymbolContext *sbCtx, bitSt *bs,int r,int c, int bSize,
			AV1DecodeContext *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	if (frameHdr->allow_intrabc)
	{
		return ERROR_CODE;
	}
	int w = Num_4x4_Blocks_Wide[bSize];
	int h = Num_4x4_Blocks_High[bSize];
	for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++)
	{
		if (frameHdr->lr_params.FrameRestorationType[plane] != RESTORE_NONE)
		{
			int subX = (plane == 0) ? 0 : seqHdr->color_config.subsampling_x;
			int subY = (plane == 0) ? 0 : seqHdr->color_config.subsampling_y;
			int unitSize = frameHdr->lr_params.LoopRestorationSize[plane];
			int unitRows = count_units_in_frame(unitSize, Round2(frameHdr->si.FrameHeight, subY));
			int unitCols = count_units_in_frame(unitSize, Round2(frameHdr->si.UpscaledWidth, subX));
			int unitRowStart = (r * (MI_SIZE >> subY) + unitSize - 1) / unitSize;
			int unitRowEnd = Min(unitRows, ((r + h) * (MI_SIZE >> subY) + unitSize - 1) / unitSize);
			int numerator,denominator;
			if (frameHdr->si.use_superres)
			{
				numerator = (MI_SIZE >> subX) * frameHdr->si.SuperresDenom;
				denominator = unitSize * SUPERRES_NUM;
			}
			else
			{
				numerator = MI_SIZE >> subX;
				denominator = unitSize;
			}
			int unitColStart = (c * numerator + denominator - 1) / denominator;
			int unitColEnd = Min(unitCols, ((c + w) * numerator +
										denominator - 1) /
										   denominator);
			for (int unitRow = unitRowStart; unitRow < unitRowEnd; unitRow++)
			{
				for (int unitCol = unitColStart; unitCol < unitColEnd; unitCol++)
				{
					read_lr_unit(sbCtx,bs, plane, unitRow, unitCol,av1Ctx);
				}
			}
		}
	}
}
int frame::read_lr_unit(SymbolContext *sbCtx, bitSt *bs,int plane,int unitRow,int unitCol,
					AV1DecodeContext  *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	sequenceHeader *seqHdr = &av1Ctx->seqHdr;
	int restoration_type;
	if (frameHdr->lr_params.FrameRestorationType[plane] == RESTORE_WIENER)
	{
		printf("decodeSymbol use_wiener\n");
		int use_wiener = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Use_Wiener ,2 + 1 ); // S()
		restoration_type = use_wiener ? RESTORE_WIENER : RESTORE_NONE;
	}
	else if (frameHdr->lr_params.FrameRestorationType[plane] == RESTORE_SGRPROJ)
	{
		printf("decodeSymbol use_sgrproj\n");
		int use_sgrproj = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Use_Sgrproj ,2 + 1 ); // S()
		restoration_type = use_sgrproj ? RESTORE_SGRPROJ : RESTORE_NONE;
	}
	else
	{
		printf("decodeSymbol restoration_type\n");
		restoration_type = sb->decodeSymbol(sbCtx,bs,av1Ctx->tileSavedCdf.Restoration_Type ,RESTORE_SWITCHABLE + 1 ); // S()
	}
	printf("restoration_type %d\n",restoration_type);
	av1Ctx->currentFrame->lrCtx->LrType[plane][unitRow][unitCol] = restoration_type;
	int v;
	if (restoration_type == RESTORE_WIENER)
	{
		for (int pass = 0; pass < 2; pass++)
		{
			int firstCoeff;
			if (plane)
			{
				firstCoeff = 1;
				av1Ctx->currentFrame->lrCtx->LrWiener[plane][unitRow][unitCol][pass][0] = 0;
			}
			else
			{
				firstCoeff = 0;
			}
			for (int j = firstCoeff; j < 3; j++)
			{
				int min = Wiener_Taps_Min[j];
				int max = Wiener_Taps_Max[j];
				int k = Wiener_Taps_K[j];
				v = sb->decode_signed_subexp_with_ref_bool(sbCtx,bs,
						min, max + 1, k, av1Ctx->RefLrWiener[plane][pass][j]);
				av1Ctx->currentFrame->lrCtx->LrWiener[plane][unitRow][unitCol][pass][j] = v;
				av1Ctx->RefLrWiener[plane][pass][j] = v;
			}
		}
	}
	else if (restoration_type == RESTORE_SGRPROJ)
	{
		printf("read_literal lr_sgr_set\n");
		int lr_sgr_set = sb->read_literal(sbCtx,bs,SGRPROJ_PARAMS_BITS); // L(SGRPROJ_PARAMS_BITS)
		av1Ctx->currentFrame->lrCtx->LrSgrSet[plane][unitRow][unitCol] = lr_sgr_set;
		for (int i = 0; i < 2; i++)
		{
			int radius = Sgr_Params[lr_sgr_set][i * 2];
			int min = Sgrproj_Xqd_Min[i];
			int max = Sgrproj_Xqd_Max[i];
			if (radius)
			{
				v = sb->decode_signed_subexp_with_ref_bool(sbCtx,bs,
						min, max + 1, SGRPROJ_PRJ_SUBEXP_K,
						av1Ctx->RefSgrXqd[plane][i]);
			}  
			else
			{
				int v = 0;
				if (i == 1)
				{
					v = Clip3(min, max, (1 << SGRPROJ_PRJ_BITS) - av1Ctx->RefSgrXqd[plane][0]);
				}
			}
			av1Ctx->currentFrame->lrCtx->LrSgrXqd[plane][unitRow][unitCol][i] = v;
			av1Ctx->RefSgrXqd[plane][i] = v;
		}
	}
}
int frame::clear_above_context(AV1DecodeContext  *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;

	for(int i = 0 ; i < 3 ; i ++){
		memset(av1Ctx->AboveLevelContext[i],0, frameHdr->MiCols * sizeof(int));
		memset(av1Ctx->AboveDcContext[i],0,frameHdr->MiCols * sizeof(int));	
	}

	memset(av1Ctx->AboveSegPredContext,0,frameHdr->MiCols * sizeof(int));

}
int frame::clear_left_context(AV1DecodeContext  *av1Ctx)
{
	frameHeader *frameHdr = &av1Ctx->frameHdr;
	for(int i = 0 ; i < 3 ; i ++){
		memset(av1Ctx->LeftLevelContext[i],0, frameHdr->MiRows * sizeof(int));
		memset(av1Ctx->LeftDcContext[i],0, frameHdr->MiRows * sizeof(int));
	}
	memset(av1Ctx->LeftSegPredContext,0,frameHdr->MiRows * sizeof(int));
}