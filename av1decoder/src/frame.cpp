#include "frame.h"
#include "segmentation.h"
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

	out->order_hint = readBits(bs, seqHdr->OrderHintBits);

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
	if (out->FrameIsIntra || out->refresh_frame_flags != (1 << NUM_REF_FRAMES) - 1)
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
			int hint = av1ctx->RefOrderHint[out->ref_frame_idx[i]];
			av1ctx->OrderHints[refFrame] = hint;
			if (!seqHdr->enable_order_hint)
			{
				out->RefFrameSignBias[refFrame] = 0;
			}
			else
			{
				out->RefFrameSignBias[refFrame] = get_relative_dist(seqHdr, hint, out->order_hint) > 0;
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
		// motion_field_estimation( )

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
	const int CodedLossless = 1;
	int segmentId;
	for (segmentId = 0; segmentId < MAX_SEGMENTS; segmentId++)
	{
		qindex = get_qindex(1, segmentId);
		LosslessArray[segmentId] = qindex == 0 && DeltaQYDc == 0 &&
								   DeltaQUAc == 0 && DeltaQUDc == 0 &&
								   DeltaQVAc == 0 && DeltaQVDc == 0;
		if (!LosslessArray[segmentId])
			CodedLossless = 0;
		if (using_qmatrix)
		{
			if (LosslessArray[segmentId])
			{
				SegQMLevel[0][segmentId] = 15;
				SegQMLevel[1][segmentId] = 15;
				SegQMLevel[2][segmentId] = 15;
			}
			else
			{
				SegQMLevel[0][segmentId] = qm_y;
				SegQMLevel[1][segmentId] = qm_u;
				SegQMLevel[2][segmentId] = qm_v;
			}
		}
	}
	AllLossless = CodedLossless && (FrameWidth == UpscaledWidth);

	return 0;
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

	int MiColStarts[sbCols];
	int MiRowStarts[sbRows];
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
			MiColStarts[i] = startSb << sbShift;
			i += 1;
		}
		MiColStarts[i] = frameHdr->MiCols;
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
			MiRowStarts[i] = startSb << sbShift;
			i += 1;
		}
		MiRowStarts[i] = frameHdr->MiRows;
		frameHdr->tile_info.TileRows = i;
	}
	else
	{
		int widestTileSb = 0;
		startSb = 0;
		int i;
		for (i = 0; startSb < sbCols; i++)
		{
			MiColStarts[i] = startSb << sbShift;
			const int maxWidth = Min(sbCols - startSb, maxTileWidthSb);
			frameHdr->tile_info.width_in_sbs = readns(bs, maxWidth);
			// const int sizeSb = width_in_sbs_minus_1 + 1;
			widestTileSb = Max(frameHdr->tile_info.width_in_sbs, widestTileSb);

			startSb += frameHdr->tile_info.width_in_sbs;
		}
		MiColStarts[i] = frameHdr->MiCols;
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
			MiRowStarts[i] = startSb << sbShift;
			const int maxHeight = Min(sbRows - startSb, maxTileHeightSb);
			frameHdr->tile_info.height_in_sbs = readns(bs, maxHeight);
			startSb += frameHdr->tile_info.height_in_sbs;
		}
		MiRowStarts[i] = frameHdr->MiRows;
		frameHdr->tile_info.TileRows = i;
		frameHdr->tile_info.TileRowsLog2 = tile_log2(1, frameHdr->tile_info.TileRows);
	}
	if (frameHdr->tile_info.TileColsLog2 > 0 || frameHdr->tile_info.TileRowsLog2 > 0)
	{
		frameHdr->tile_info.context_update_tile_id = readBits(bs,
															  frameHdr->tile_info.TileRowsLog2 + frameHdr->tile_info.TileColsLog2);

		frameHdr->tile_info.tile_size_bytes = readBits(bs, 2) + 1;
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
						if (Segmentation_Feature_Signed[j] == 1);
						{
							tmp = readsu(bs,1 + bitsToRead);// su(1 + bitsToRead);
							clippedValue = Clip3(-limit, limit, tmp);
						}
						else
						{
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
			frameHdr->delta_lf_params.delta_lf_res readBits(bs, 2);
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
	si->UpscaledWidth = si->FrameHeight;

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
