#include "frame.h"
#include "segmentation.h"
#include <string.h>

int frame::parseFrameHeader(int sz, bitSt *bs, AV1DecodeContext *av1ctx, sequenceHeader *seqHdr, obuHeader *obuheader, frameHeader *out)
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
			av1ctx->RefValid[i] = 0;
			//
			av1ctx->RefOrderHint[i] = 0;
		}

		for (int i = 0; i < REFS_PER_FRAME; i++)
		{
			av1ctx->OrderHints[LAST_FRAME + i] = 0;
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
				if (out->ref_order_hint[i] != av1ctx->RefOrderHint[i])
				{
					av1ctx->RefValid[i] = 0;
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
				// set_frame_refs() 7.8 todo
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
					out->si.UpscaledWidth = av1ctx->ref_frames[i]->si->UpscaledWidth;
					out->si.FrameWidth = out->si.UpscaledWidth;
					out->si.FrameHeight = av1ctx->ref_frames[i]->si->FrameHeight;	// RefFrameHeight[ ref_frame_idx[ i ] ]
					out->si.RenderWidth = av1ctx->ref_frames[i]->si->RenderWidth;	// RefRenderWidth[ ref_frame_idx[ i ] ]
					out->si.RenderHeight = av1ctx->ref_frames[i]->si->RenderHeight; // RefRenderHeight[ ref_frame_idx[ i ] ]
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
			int hint = av1ctx->RefOrderHint[out->ref_frame_idx[i]];
			av1ctx->OrderHints[refFrame] = hint;
			if (!seqHdr->enable_order_hint)
			{
				out->RefFrameSignBias[refFrame] = 0;
			}
			else
			{
				out->RefFrameSignBias[refFrame] = get_relative_dist(seqHdr, hint, out->OrderHint) > 0;
			}
		}
	}

	if (seqHdr->reduced_still_picture_header || out->disable_cdf_update)
		out->disable_frame_end_update_cdf = 1;
	else
		out->disable_frame_end_update_cdf = readOneBit(bs);

	if (out->primary_ref_frame == PRIMARY_REF_NONE)
	{
		// init_non_coeff_cdfs( )
		// setup_past_independence( )
	}
	else
	{
		// load_cdfs( ref_frame_idx[ primary_ref_frame ] )
		// load_previous( )
	}
	if (out->use_ref_frame_mvs == 1)
	{
		// motion_field_estimation( )
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
		// init_coeff_cdfs( )
	}
	else
	{
		// load_previous_segment_ids( )
	}
	out->CodedLossless = 1;
	int segmentId;
	for (segmentId = 0; segmentId < MAX_SEGMENTS; segmentId++)
	{
		int qindex = segmentation::Instance().get_qindex(1, segmentId,out);
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
	//cdef Params
	readCdefParams(bs,out,seqHdr);

	readLrParams(bs,out,seqHdr);


	if ( out->CodedLossless == 1 ) {
		out->TxMode = ONLY_4X4;
	} else {
		out->tx_mode_select  = readOneBit(bs);
		if ( out->tx_mode_select ) {
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

	readSkipModeParams(bs,out,av1ctx,seqHdr);

	if ( out->FrameIsIntra || out->error_resilient_mode || !seqHdr->enable_warped_motion)
		out->allow_warped_motion = 0;
	else
		out->allow_warped_motion = readOneBit(bs);
	out->reduced_tx_set = readOneBit(bs);

	//global_motion_params
	readGlobalMotionParams(bs, out);
	//film_grain_params
	
	readFilmGrainParams(bs,out,seqHdr);
	return sz - bs->offset;
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

	frameHdr->quantization_params.DeltaQYDc = read_delta_q(bs);
	if (seqHdr->color_config.NumPlanes > 1)
	{
		if (seqHdr->color_config.separate_uv_delta_q)
			frameHdr->quantization_params.diff_uv_delta = readOneBit(bs);
		else
			frameHdr->quantization_params.diff_uv_delta = 0;
		frameHdr->quantization_params.DeltaQUDc = read_delta_q(bs);
		frameHdr->quantization_params.DeltaQUAc = read_delta_q(bs);
		if (frameHdr->quantization_params.diff_uv_delta)
		{
			frameHdr->quantization_params.DeltaQVDc = read_delta_q(bs);
			frameHdr->quantization_params.DeltaQVAc = read_delta_q(bs);
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
	frameHdr->loop_filter_params.loop_filter_sharpness = readBits(bs, 6); // f(3)
	frameHdr->loop_filter_params.loop_filter_delta_enabled = readOneBit(bs); //f(1)
	if ( frameHdr->loop_filter_params.loop_filter_delta_enabled == 1 ) {
		frameHdr->loop_filter_params.loop_filter_delta_update = readOneBit(bs);// f(1)
			if ( frameHdr->loop_filter_params.loop_filter_delta_update == 1 ) {
				for (int i = 0; i < TOTAL_REFS_PER_FRAME; i++ ) {
					frameHdr->loop_filter_params.update_ref_delta[i] = readOneBit(bs);// f(1)
				if ( frameHdr->loop_filter_params.update_ref_delta[i] == 1 )
					frameHdr->loop_filter_params.loop_filter_ref_deltas[ i ] = readsu(bs, 1 + 6); //su(1+6)
			}
			for (int  i = 0; i < 2; i++ ) {
				frameHdr->loop_filter_params.update_mode_delta[i] = readOneBit(bs);//f(1)
				if ( frameHdr->loop_filter_params.update_mode_delta[i] == 1 )
					frameHdr->loop_filter_params.loop_filter_mode_deltas[ i ] = readsu(bs, 1 + 6);//su(1+6)
			}

		}
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
int frame::readSkipModeParams(bitSt *bs, frameHeader *frameHdr,AV1DecodeContext *av1ctx,sequenceHeader *seqHeader)
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
			refHint = av1ctx->RefOrderHint[ frameHdr->ref_frame_idx[ i ] ];
			if ( get_relative_dist( seqHeader, refHint, frameHdr->OrderHint ) < 0 ) {
				if ( forwardIdx < 0 ||get_relative_dist(seqHeader,  refHint, forwardHint) > 0 ) {
					forwardIdx = i;
					forwardHint = refHint;
				}
			} else if ( get_relative_dist(seqHeader,  refHint, frameHdr->OrderHint) > 0 ) {
				if ( backwardIdx < 0 || get_relative_dist(seqHeader,  refHint, backwardHint) < 0 ) {
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
				refHint = av1ctx->RefOrderHint[ frameHdr->ref_frame_idx[ i ] ];
				if ( get_relative_dist(seqHeader, refHint, forwardHint ) < 0 ) {
					if ( secondForwardIdx < 0 || get_relative_dist(seqHeader, refHint, secondForwardHint ) > 0 ) {
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

int frame::readFilmGrainParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHdr)
{
	if ( !seqHdr->film_grain_params_present ||(!frameHdr->show_frame && !frameHdr->showable_frame) ) {
		//reset_grain_params()
		return 0;
	}
	if ( !readOneBit(bs)/*apply_grain*/ ) {
		//reset_grain_params()
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
		//load_grain_params( film_grain_params_ref_idx );
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
int frame::get_relative_dist(sequenceHeader *seqHdr, int a, int b)
{
	if (!seqHdr->enable_order_hint)
		return 0;
	int diff = a - b;
	int m = 1 << (seqHdr->OrderHintBits - 1);
	diff = (diff & (m - 1)) - (diff & m);
	return diff;
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


int frame::decodeFrame(int sz, bitSt *bs, AV1DecodeContext *av1ctx){
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;

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
		TileData t_data;
		t_data.MiRowStart = frameHdr->tile_info.MiRowStarts[ tileRow ];
		t_data.MiRowEnd = frameHdr->tile_info.MiRowStarts[ tileRow + 1 ];
		t_data.MiColStart = frameHdr->tile_info.MiColStarts[ tileCol ];
		t_data.MiColEnd = frameHdr->tile_info.MiColStarts[ tileCol + 1 ];
	//	注意这个!!!! spec中有用，但是用到那个地方在 dav1d中，和libaom中又都没有用
		int CurrentQIndex = frameHdr->quantization_params.base_q_idx;
		//之所以 每个tile 进行一次 init_symbol 是因为tile内的所有语法元素和数据都是算术编码的，而tile层之上会有非算术编码的语法元素。
		//init_symbol( tileSize );
		SymbolContext symCtx;
		Symbol::Instance().initSymbol(&symCtx,bs,sz);
		decode_tile(&symCtx,bs,&t_data,av1ctx);
		//exit_symbol();
	}
	if ( tg_end == NumTiles - 1 ) {
		if ( !frameHdr->disable_frame_end_update_cdf ) {
			//frame_end_update_cdf( );
		}
		//decode_frame_wrapup( );
		av1ctx->SeenFrameHeader = 0;
	}

}
int frame::decode_tile(SymbolContext *sbCtx,bitSt *bs, TileData *t_data,AV1DecodeContext *av1ctx){
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;

	//clear_above_context( ).....
	for (int i = 0; i < FRAME_LF_COUNT; i++ )
		t_data->DeltaLF[ i ] = 0;
	for (int plane = 0; plane < seqHdr->color_config.NumPlanes; plane++ ) {
		for (int pass = 0; pass < 2; pass++ ) {
			t_data->RefSgrXqd[ plane ][ pass ] = Sgrproj_Xqd_Mid[ pass ];
			for (int i = 0; i < WIENER_COEFFS; i++ ) {
				t_data->RefLrWiener[ plane ][ pass ][ i ] = Wiener_Taps_Mid[ i ];
			}
		}
	}
	int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64;
	int sbSize4 = Num_4x4_Blocks_Wide[ sbSize ];

	for (int  r = t_data->MiRowStart; r < t_data->MiRowEnd; r += sbSize4 ) {
		//clear_left_context( )......！！！
		for (int  c = t_data->MiColStart; c < t_data->MiColEnd; c += sbSize4 ) {
			t_data->ReadDeltas = frameHdr->delta_q_params.delta_q_present;
			//clear_cdef( r, c );...........！！！！
			//clear_block_decoded_flags( r, c, sbSize4 );..........！！！
			//read_lr( r, c, sbSize );............！！！
			PartitionData b_data;
			decode_partition(sbCtx, bs , t_data,&b_data,r, c, sbSize ,av1ctx);
		}
	}

}

int frame::decode_partition(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,int r,int c,int bSize, AV1DecodeContext *av1ctx)
{
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;

	if (r >= frameHdr->MiRows || c >= frameHdr->MiCols)
		return 0;
	//是否有效，通过判断是否在帧内
	p_data->AvailU = is_inside(r - 1, c,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd);
	p_data->AvailL = is_inside(r, c - 1,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd);
	//当前块4*4数目
	int num4x4 = Num_4x4_Blocks_Wide[bSize] ;
	//
	int halfBlock4x4 = num4x4 >> 1 ;
	int quarterBlock4x4 = halfBlock4x4 >> 1 ;
	//当前块是否还有数据
	int hasRows = (r + halfBlock4x4) < frameHdr->MiRows;
	int hasCols = (c + halfBlock4x4) < frameHdr->MiCols ;

	int partition,split_or_horz,split_or_vert;
	Symbol sb = Symbol::Instance();

	uint16_t *partitionCdf;
	int bsl = Mi_Width_Log2[ bSize ];
	int above = p_data->AvailU && ( Mi_Width_Log2[ p_data->MiSizes[ r - 1 ][ c ] ] < bsl );
	int left = p_data->AvailL && ( Mi_Height_Log2[ p_data->MiSizes[ r ][ c - 1 ] ] < bsl );
	int ctx = left * 2 + above;

	if(bsl == 1)
		partitionCdf = av1ctx->cdfCtx->Partition_W8[ctx];
	else if(bsl == 2)
		partitionCdf = av1ctx->cdfCtx->Partition_W16[ctx];
	else if(bsl == 3)
		partitionCdf = av1ctx->cdfCtx->Partition_W32[ctx];
	else if(bsl == 4)
		partitionCdf = av1ctx->cdfCtx->Partition_W64[ctx];
	else if(bsl == 5)
		partitionCdf = av1ctx->cdfCtx->Partition_W128[ctx];


	if (bSize < BLOCK_8X8)
	{
		partition = PARTITION_NONE;
	}
	else if (hasRows && hasCols)
	{
		 //根据上边和左边的块来推出需要使用的cdf， 为什么MiSizes 还未初始化这里就在使用？
		 //在最左上角的时候AvailU AvailL都是0，自然  p_data->AvailU && 后面的就不会调了，就没有问题

		partition = sb.decodeSymbol(sbCtx,bs,partitionCdf,sizeof(partitionCdf)/sizeof(uint16_t));
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


		split_or_horz = sb.decodeSymbol(sbCtx,bs,cdf,3);
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
		split_or_vert = sb.decodeSymbol(sbCtx,bs,cdf,3);
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
		decode_block(r, c, subSize);
	}
	else if (partition == PARTITION_HORZ)
	{
		decode_block(r, c, subSize);
		if (hasRows)
			decode_block(r + halfBlock4x4, c, subSize);
	}
	else if (partition == PARTITION_VERT)
	{
		decode_block(r, c, subSize);
		if (hasCols)
			decode_block(r, c + halfBlock4x4, subSize);
	}
	else if (partition == PARTITION_SPLIT)
	{
		decode_partition(sbCtx,bs,t_data,p_data, r, c, subSize,av1ctx);
		decode_partition(sbCtx,bs,t_data,p_data,r, c + halfBlock4x4, subSize,av1ctx);
		decode_partition(sbCtx,bs,t_data,p_data,r + halfBlock4x4, c, subSize,av1ctx);
		decode_partition(sbCtx,bs,t_data,p_data,r + halfBlock4x4, c + halfBlock4x4, subSize,av1ctx);
	}
	else if (partition == PARTITION_HORZ_A)
	{
		decode_block(r, c, splitSize);
		decode_block(r, c + halfBlock4x4, splitSize);
		decode_block(r + halfBlock4x4, c, subSize);
	}
	else if (partition == PARTITION_HORZ_B)
	{
		decode_block(r, c, subSize);
		decode_block(r + halfBlock4x4, c, splitSize);
		decode_block(r + halfBlock4x4, c + halfBlock4x4, splitSize);
	}
	else if (partition == PARTITION_VERT_A)
	{
		decode_block(r, c, splitSize);
		decode_block(r + halfBlock4x4, c, splitSize);
		decode_block(r, c + halfBlock4x4, subSize);
	}
	else if (partition == PARTITION_VERT_B)
	{
		decode_block(r, c, subSize);
		decode_block(r, c + halfBlock4x4, splitSize);
		decode_block(r + halfBlock4x4, c + halfBlock4x4, splitSize);
	}
	else if (partition == PARTITION_HORZ_4)
	{
		decode_block(r + quarterBlock4x4 * 0, c, subSize);
		decode_block(r + quarterBlock4x4 * 1, c, subSize);
		decode_block(r + quarterBlock4x4 * 2, c, subSize) ;
		if (r + quarterBlock4x4 * 3 < frameHdr->MiRows)
			decode_block(r + quarterBlock4x4 * 3, c, subSize);
	}
	else
	{
		decode_block(r, c + quarterBlock4x4 * 0, subSize);
		decode_block(r, c + quarterBlock4x4 * 1, subSize);
		decode_block(r, c + quarterBlock4x4 * 2, subSize); 
		if (c + quarterBlock4x4 * 3 < frameHdr->MiCols)
			decode_block(r, c + quarterBlock4x4 * 3, subSize);
	}
}

int frame::decode_block(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,int r,int c,int subSize, AV1DecodeContext *av1ctx)
{
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;

	BlockData b_data;

	b_data.MiRow = r;
	b_data.MiCol = c;
	b_data.MiSize = subSize;
	int bw4 = Num_4x4_Blocks_Wide[subSize];
	int bh4 = Num_4x4_Blocks_High[subSize];	
	if (bh4 == 1 && seqHdr->color_config.subsampling_y && (b_data.MiRow & 1) == 0)
		b_data.HasChroma = 0 ;
	else if (bw4 == 1 && seqHdr->color_config.subsampling_x && (b_data.MiCol & 1) == 0)
		b_data.HasChroma = 0 ;
	else 
		b_data.HasChroma = seqHdr->color_config.NumPlanes > 1;
	b_data.AvailU = is_inside(r - 1, c,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd);
	b_data.AvailL = is_inside(r, c - 1,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd);
	b_data.AvailUChroma = b_data.AvailU;
	b_data.AvailLChroma = b_data.AvailL;
	if (b_data.HasChroma)
	{
		if (seqHdr->color_config.subsampling_y && bh4 == 1)
			b_data.AvailUChroma = is_inside(r - 2, c,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd);
		if (seqHdr->color_config.subsampling_x && bw4 == 1)
			b_data.AvailLChroma = is_inside(r, c - 2,t_data->MiColStart,t_data->MiColEnd,t_data->MiRowStart,t_data->MiRowEnd);
	}else {
		b_data.AvailUChroma = 0;
		b_data.AvailLChroma = 0;
	}

	mode_info(&b_data,av1ctx);
	palette_tokens();
	read_block_tx_size();	
	if (b_data.skip)
		reset_block_context(bw4, bh4);
	isCompound = RefFrame[1] > INTRA_FRAME;
	for (int y = 0; y < bh4; y++)
	{
		for (int x = 0; x < bw4; x++)
		{
			YModes[r + y][c + x] = YMode ;
			if (RefFrame[0] == INTRA_FRAME && HasChroma)
				UVModes[r + y][c + x] = UVMode ;
			for (int refList = 0; refList < 2; refList++)
				RefFrames[r + y][c + x][refList] = RefFrame[refList] ;
			if (is_inter)
			{
					if (!use_intrabc)
					{
						CompGroupIdxs[r + y][c + x] = comp_group_idx;
						CompoundIdxs[r + y][c + x] = compound_idx;
					}
					for (int dir = 0; dir < 2; dir++)
					{
						InterpFilters[r + y][c + x][dir] = interp_filter[dir];
					}
					for (int refList = 0; refList < 1 + isCompound; refList++)
					{
						Mvs[r + y][c + x][refList] = Mv[refList];
					}
			}
		}
	}
	compute_prediction();
	residual() ;
	for (int y = 0; y < bh4; y++)
	{
		for (int x = 0; x < bw4; x++)
		{
			IsInters[r + y][c + x] = is_inter;
			SkipModes[r + y][c + x] = skip_mode;
			Skips[r + y][c + x] = skip;
			TxSizes[r + y][c + x] = TxSize;
			MiSizes[r + y][c + x] = MiSize;
			SegmentIds[r + y][c + x] = segment_id;
			PaletteSizes[0][r + y][c + x] = PaletteSizeY;
			PaletteSizes[1][r + y][c + x] = PaletteSizeUV ;
			for (int i = 0; i < PaletteSizeY; i++)
				PaletteColors[0][r + y][c + x][i] = palette_colors_y[i] ;
			for (int i = 0; i < PaletteSizeUV; i++);
				PaletteColors[1][r + y][c + x][i] = palette_colors_u[i] ;
			for (int i = 0; i < FRAME_LF_COUNT; i++)
				DeltaLFs[r + y][c + x][i] = DeltaLF[i];
		}
	}
}
int frame::mode_info(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx){
	frameHeader *frameHdr = av1ctx->frameHdr;
	if ( frameHdr->FrameIsIntra ) 
		intra_frame_mode_info(b_data,av1ctx);
	else
		inter_frame_mode_info(b_data,av1ctx);

}
int frame::intra_frame_mode_info(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx ){
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;
	Symbol sb = Symbol::Instance();
	b_data->skip = 0 ;
	if (frameHdr->segmentation_params.SegIdPreSkip){
		//intra_segment_id();
		if ( frameHdr->segmentation_params.segmentation_enabled )
			read_segment_id(sbCtx,bs,t_data,p_data,b_data,av1ctx);
		else
			b_data->segment_id = 0;
		b_data->Lossless = frameHdr->segmentation_params.LosslessArray[ b_data->segment_id ];

	}
	b_data->skip_mode = 0 ;
	//read_skip() 
	if ( frameHdr->segmentation_params.SegIdPreSkip &&
		 segmentation::Instance().seg_feature_active( b_data->segment_id,SEG_LVL_SKIP, frameHdr) ) 
	{
		b_data->skip = 1;
	} else {
		int ctx = 0;
		if ( b_data->AvailU )
			ctx += p_data->Skips[ b_data->MiRow - 1 ][ b_data->MiCol ];
		if ( b_data->AvailL )
			ctx += p_data->Skips[ b_data->MiRow ][ b_data->MiCol - 1 ];

		b_data->skip =  sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Segment_Id[ctx],MAX_SEGMENTS + 1);//S()
	}


	if (!frameHdr->segmentation_params.SegIdPreSkip){
		//intra_segment_id()
		if ( frameHdr->segmentation_params.segmentation_enabled )
			read_segment_id(sbCtx,bs,t_data,p_data,b_data,av1ctx);
		else
			b_data->segment_id = 0;
		b_data->Lossless = frameHdr->segmentation_params.LosslessArray[ b_data->segment_id ];

	}
		
	read_cdef(sbCtx,bs,t_data,p_data,b_data,av1ctx);
	read_delta_qindex(sbCtx,bs,t_data,p_data,b_data,av1ctx);
	read_delta_lf(sbCtx,bs,t_data,p_data,b_data,av1ctx);
	t_data->ReadDeltas = 0 ;
	b_data->RefFrame[0] = INTRA_FRAME;
	b_data->RefFrame[1] = NONE ;

	if (frameHdr->allow_intrabc)
	{
		b_data->use_intrabc =  sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Intrabc,3);// S()
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
		//find_mv_stack(0);!!!!!!!!!!!!!!!!!
		assign_mv(0);
	}
	else
	{
		b_data->is_inter = 0 ;
	//	intra_frame_y_mode ;//S()
		int abovemode = Intra_Mode_Context[ b_data->AvailU ? p_data->YModes[ b_data->MiRow - 1 ][ b_data->MiCol ] : DC_PRED ];
		int leftmode = Intra_Mode_Context[ b_data->AvailL ? p_data->YModes[ b_data->MiRow ][ b_data->MiCol - 1] : DC_PRED ];
		b_data->YMode = sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Intra_Frame_Y_Mode[abovemode][leftmode],INTRA_MODES + );
		intra_angle_info_y() ;
		if (b_data->HasChroma)
		{
	

			uint16_t *uv_mode_cdf;
			if(b_data->Lossless && 
					BLOCK_4X4 == get_plane_residual_size( b_data->MiSize, 1 ,seqHdr->color_config.subsampling_x,seqHdr->color_config.subsampling_y)){
					uv_mode_cdf = av1ctx->cdfCtx->Uv_Mode_Cfl_Allowed[b_data->YMode];
			// Block_Width[ x ] is defined to be equal to 4 * Num_4x4_Blocks_Wide[ x ].
			//Block_Height[ x ] is defined to be equal to 4 * Num_4x4_Blocks_High[ x ].
			}else if(!b_data->Lossless && Max( 4 * Num_4x4_Blocks_Wide[ b_data->MiSize ], 4 * Num_4x4_Blocks_High[ b_data->MiSize ] ) <= 32){
					uv_mode_cdf = av1ctx->cdfCtx->Uv_Mode_Cfl_Allowed[b_data->YMode];

			}else{
					uv_mode_cdf = av1ctx->cdfCtx->Uv_Mode_Cfl_Not_Allowed[b_data->YMode];

			}
			//uv_mode ;//S()
			b_data->UVMode = sb.decodeSymbol(sbCtx,bs,uv_mode_cdf,sizeof(uv_mode_cdf)/sizeof(uint16_t));
			if (b_data->UVMode == UV_CFL_PRED){
				read_cfl_alphas();
			} 
			intra_angle_info_uv();
		}
		b_data->PaletteSizeY = 0 ;
		b_data->PaletteSizeUV = 0 ;
		if (b_data->MiSize >= BLOCK_8X8 &&
			4 * Num_4x4_Blocks_Wide[b_data->MiSize] <= 64 &&
			4 * Num_4x4_Blocks_High[b_data->MiSize] <= 64 &&
			frameHdr->allow_screen_content_tools){
				palette_mode_info();
			} 
			filter_intra_mode_info();
	}
	
}
int frame::inter_frame_mode_info(AV1DecodeContext *av1ctx ){


}
int frame::read_segment_id(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx){
	frameHeader *frameHdr = av1ctx->frameHdr;
	Symbol sb = Symbol::Instance();
	if (b_data->AvailU && b_data->AvailL)
		b_data->prevUL = p_data->SegmentIds[b_data->MiRow - 1][b_data->MiCol - 1];
	else 
		b_data->prevUL = -1 ;
	if (b_data->AvailU)
		b_data->prevU = p_data->SegmentIds[b_data->MiRow - 1][b_data->MiCol] ;
	else
		b_data->prevU = -1 ;
	if (b_data->AvailL)
		b_data->prevL = p_data->SegmentIds[b_data->MiRow][b_data->MiCol - 1] ;
	else 
		b_data->prevL = -1 ;

	if (b_data->prevU == -1)
		b_data->pred = (b_data->prevL == -1) ? 0 : b_data->prevL ;
	else if (b_data->prevL == -1) 
		b_data->pred = b_data->prevU ;
	else 
		b_data->pred = (b_data->prevUL == b_data->prevU) ? b_data->prevU : b_data->prevL; 

	if (b_data->skip)
	{
		b_data->segment_id = b_data->pred;
	}
	else
	{
		int ctx;
		if ( b_data->prevUL < 0 )
			ctx = 0;
		else if ( (b_data->prevUL == b_data->prevU) && (b_data->prevUL == b_data->prevL) )
			ctx = 2;
		else if ( (b_data->prevUL == b_data->prevU) || (b_data->prevUL == b_data->prevL) || (b_data->prevU == b_data->prevL) )
			ctx = 1;
		else
			ctx = 0;
		b_data->segment_id = sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Skip_Mode[ctx],3);//S() 
		neg_deinterleave( b_data->segment_id, b_data->pred,
						frameHdr->segmentation_params.LastActiveSegId + 1);
	}
}
int frame::read_cdef(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx){
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;
	Symbol sb = Symbol::Instance();
	if (b_data->skip || frameHdr->CodedLossless || !seqHdr->enable_cdef || frameHdr->allow_intrabc)
	{
		return;
	}
	int cdefSize4 = Num_4x4_Blocks_Wide[BLOCK_64X64] ;
	int cdefMask4 = ~(cdefSize4 - 1);
	int r = b_data->MiRow &cdefMask4;
	int c = b_data->MiCol & cdefMask4 ;
	if (t_data->cdef_idx[r][c] == -1)
	{
		t_data->cdef_idx[r][c] = sb.read_literal(sbCtx,bs,frameHdr->cdef_params.cdef_bits); //L(cdef_bits)
		int w4 = Num_4x4_Blocks_Wide[b_data->MiSize] ;
		int h4 = Num_4x4_Blocks_High[b_data->MiSize] ;
		for (int i = r; i < r + h4; i += cdefSize4)
		{
			for (int j = c; j < c + w4; j += cdefSize4)
			{
				t_data->cdef_idx[i][j] = t_data->cdef_idx[r][c];
			}
		}
	}
}
int frame::read_delta_qindex(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx)
{
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;
	Symbol sb = Symbol::Instance();
	int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64 ;
	if (b_data->MiSize == sbSize && b_data->skip) 
		return ;
	if (t_data->ReadDeltas)
	{
		b_data->delta_q_abs =  sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Delta_Q,DELTA_Q_SMALL + 2);//S() 
		if (b_data->delta_q_abs == DELTA_Q_SMALL)
		{
			b_data->delta_q_rem_bits = sb.read_literal(sbCtx,bs,3);//L(3)
			b_data->delta_q_rem_bits++ ;
			b_data->delta_q_abs_bits = sb.read_literal(sbCtx,bs,b_data->delta_q_rem_bits);//L(delta_q_rem_bits)
			b_data->delta_q_abs = b_data->delta_q_abs_bits + (1 << b_data->delta_q_rem_bits) + 1;
		}
		if (b_data->delta_q_abs)
		{
			b_data->delta_q_sign_bit = sb.read_literal(sbCtx,bs,1);//L(1)
			int reducedDeltaQIndex = b_data->delta_q_sign_bit ? -b_data->delta_q_abs : b_data->delta_q_abs ;
			t_data->CurrentQIndex = Clip3(1, 255, t_data->CurrentQIndex + (reducedDeltaQIndex << frameHdr->delta_q_params.delta_q_res));
		}
	}
}
int frame::read_delta_lf(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx)
{
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;
	Symbol sb = Symbol::Instance();
	int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64;

	if ( b_data->MiSize == sbSize && b_data->skip )
		return ;
	if (t_data->ReadDeltas && frameHdr->delta_lf_params.delta_lf_present)

	{
		int frameLfCount = 1 ;
		if (frameHdr->delta_lf_params.delta_lf_multi)
		{
			frameLfCount = (seqHdr->color_config.NumPlanes > 1) ? FRAME_LF_COUNT : (FRAME_LF_COUNT - 2);
		}
		for (int i = 0; i < frameLfCount; i++)
		{
			//这里的逻辑是delta_lf_multi 为1  则各个frameLf的 delta_lf_abs都不一样，他们都有自己的 symbol ctx
			//初始化的时候，他们都是从 Default_Delta_Lf_Cdf拷贝而来的，是一样的，如果需要update，则后面则是单独update了
			//就有可能不一样，所以要做区分
			if(frameHdr->delta_lf_params.delta_lf_multi)
				b_data->delta_lf_abs =  sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Delta_Lf_Muti[i],DELTA_LF_SMALL + 2); //S() 
			else
				b_data->delta_lf_abs =  sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Delta_Lf,DELTA_LF_SMALL + 2); //S() 

			int deltaLfAbs;
			if (b_data->delta_lf_abs == DELTA_LF_SMALL)
			{
				
				b_data->delta_lf_rem_bits = sb.read_literal(sbCtx,bs,3); //L(3)
				b_data->delta_lf_abs_bits = sb.read_literal(sbCtx,bs,b_data->delta_lf_rem_bits + 1); //L(n)
				deltaLfAbs = b_data->delta_lf_abs_bits + (1 << b_data->delta_lf_rem_bits) + 1;
			}
			else
			{
				deltaLfAbs = b_data->delta_lf_abs;
			}
			if (deltaLfAbs)
			{
				b_data->delta_lf_sign_bit = sb.read_literal(sbCtx,bs,1); //L(1)
				int reducedDeltaLfLevel = b_data->delta_lf_sign_bit ? -deltaLfAbs : deltaLfAbs;
				b_data->DeltaLF[i] = Clip3(-MAX_LOOP_FILTER, MAX_LOOP_FILTER, b_data->DeltaLF[i] + (reducedDeltaLfLevel << frameHdr->delta_lf_params.delta_lf_res));
			}
		}
	}
}
int frame::assign_mv(int isCompound,SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx)
{
	frameHeader *frameHdr = av1ctx->frameHdr;
	sequenceHeader *seqHdr = av1ctx->seqHdr;
	Symbol sb = Symbol::Instance();
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
		uint8_t PredMv[2][2];

		if (b_data->use_intrabc)
		{

			//PredMv[0] = b_data->RefStackMv[0][0];
			 memcpy(PredMv[0], b_data->RefStackMv[0][0], sizeof(PredMv[0]));
			if (PredMv[0][0] == 0 && PredMv[0][1] == 0)
			{
				//PredMv[0] = b_data->RefStackMv[1][0];
				memcpy(PredMv[0], b_data->RefStackMv[1][0], sizeof(PredMv[0]));
			}
			if (PredMv[0][0] == 0 && PredMv[0][1] == 0)
			{
				int sbSize = seqHdr->use_128x128_superblock ? BLOCK_128X128 : BLOCK_64X64 ;
				int sbSize4 = Num_4x4_Blocks_High[sbSize] ;
				if (b_data->MiRow - sbSize4 < t_data->MiRowStart)
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
			memcpy(PredMv[i], b_data->GlobalMvs[i], sizeof(PredMv[0]));
		}
		else
		{
			int pos = (compMode == NEARESTMV) ? 0 : b_data->RefMvIdx ;
			if (compMode == NEWMV && b_data->NumMvFound <= 1) 
				pos = 0 ;
			//PredMv[i] = b_data->RefStackMv[pos][i];
			memcpy(PredMv[i], b_data->RefStackMv[pos][i], sizeof(PredMv[i]));
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
			b_data->mv_joint = sb.decodeSymbol(sbCtx,bs,av1ctx->cdfCtx->Mv_Joint,DELTA_LF_SMALL + 2);//S()
			if ( b_data->mv_joint == MV_JOINT_HZVNZ || b_data->mv_joint == MV_JOINT_HNZVNZ )
				diffMv[ 0 ] = read_mv_component( 0 );
			if ( b_data->mv_joint == MV_JOINT_HNZVZ || b_data->mv_joint == MV_JOINT_HNZVNZ )
				diffMv[ 1 ] = read_mv_component( 1 );
			b_data->Mv[ i ][ 0 ] = PredMv[ i ][ 0 ] + diffMv[ 0 ];
			b_data->Mv[ i ][ 1 ] = PredMv[ i ][ 1 ] + diffMv[ 1 ];

		}
		else
		{
			//b_data->Mv[i] = PredMv[i];
			memcpy(b_data->Mv[i], PredMv[i], sizeof(b_data->Mv[i]));
		}
	}
}
