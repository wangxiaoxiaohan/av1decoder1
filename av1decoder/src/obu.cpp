#include "obu.h"
#include "assert.h"
#include "frame.h"

obu::obu()
{


}
void initSequenceHeader(sequenceHeader *out)
{
	ASSERT(out != NULL);
	
}
int obu::parseSequenceHeader(int sz,bitSt *bs,sequenceHeader *out)
{
	//initSequenceHeader(out);
	out->seq_profile = readBits(bs,3);
	out->still_picture = readOneBit(bs);
	out->reduced_still_picture_header = readOneBit(bs);

	printf("seq_profile %d\n",out->seq_profile);
	printf("still_picture %d\n",out->still_picture);

	printf("reduced_still_picture_header %d\n",out->reduced_still_picture_header);

	
	if(out->reduced_still_picture_header){
		out->timing_info_present_flag = 0;
		out->decoder_model_info_present_flag = 0;
		out->initial_display_delay_present_flag = 0;
		out->operating_points_cnt = 0;
		out->seqOperatingPoint[0].operating_point_idc = 0;
		out->seqOperatingPoint[0].seq_level_idx= 0;
		out->seqOperatingPoint[0].seq_tier = 0;
		out->seqOperatingPoint[0].decoder_model_present_for_this_op = 0;
		out->seqOperatingPoint[0].initial_display_delay_present_for_this_op = 0;
	}else{
		out->timing_info_present_flag = readOneBit(bs);
		if(out->timing_info_present_flag)
		{

			out->timing_info.num_units_in_display_tick = readBits(bs,32);
			out->timing_info.time_scale = readBits(bs,32);
			out->timing_info.equal_picture_interval = readOneBit(bs);
			out->timing_info.num_ticks_per_picture =  readUlvc(bs) + 1;
			out->decoder_model_info_present_flag = readOneBit(bs);
			if(out->decoder_model_info_present_flag)
			{
				out->decoder_model_info.buffer_delay_length = readBits(bs,5) + 1;
				out->decoder_model_info.num_units_in_decoding_tick = readBits(bs,32);
				out->decoder_model_info.buffer_removal_time_length = readBits(bs,5) + 1;
				out->decoder_model_info.frame_presentation_time_length = readBits(bs,5) + 1;
			}
		}else{
			out->decoder_model_info_present_flag = 0;
		}
		out->initial_display_delay_present_flag = readOneBit(bs);
		out->operating_points_cnt = readBits(bs,5)  + 1;
		printf("operating_points_cnt %d\n",out->operating_points_cnt);

		for(int i = 0 ; i < out->operating_points_cnt ; i++){
			out->seqOperatingPoint[i].operating_point_idc = readBits(bs,12);
			out->seqOperatingPoint[i].seq_level_idx = readBits(bs,5);

			printf("out->seqOperatingPoint[i].operating_point_idc %d\n",out->seqOperatingPoint[i].operating_point_idc);
			printf("out->seqOperatingPoint[i].seq_level_idx %d\n",out->seqOperatingPoint[i].seq_level_idx);
			if(out->seqOperatingPoint[i].seq_level_idx > 7){
				out->seqOperatingPoint[i].seq_tier = readOneBit(bs);
			}else{
				out->seqOperatingPoint[i].seq_tier = 0;
			}

			if ( out->decoder_model_info_present_flag ) {
				out->seqOperatingPoint[i].decoder_model_present_for_this_op = readOneBit(bs); 
				if ( out->seqOperatingPoint[i].decoder_model_present_for_this_op) {
					out->operating_parameters_infos[i].decoder_buffer_delay = readBits(bs,out->decoder_model_info.buffer_delay_length);
					out->operating_parameters_infos[i].encoder_buffer_delay = readBits(bs,out->decoder_model_info.buffer_delay_length);
					out->operating_parameters_infos[i].low_delay_mode_flag = readOneBit(bs);
				}
			} else {
				out->seqOperatingPoint[i].decoder_model_present_for_this_op = 0;
			}
			if(out->initial_display_delay_present_flag)
			{
				out->seqOperatingPoint[i].initial_display_delay_present_for_this_op = readOneBit(bs); 
				if(out->seqOperatingPoint[i].initial_display_delay_present_for_this_op)
				{
					out->seqOperatingPoint[i].initial_display_delay = readBits(bs,4) + 1;
				}
			}

		}

	}
	 
	out->frame_width_bits  = readBits(bs,4) + 1;
	out->frame_height_bits = readBits(bs,4) + 1;
	out->max_frame_width = readBits(bs,out->frame_width_bits) + 1;
	out->max_frame_height = readBits(bs,out->frame_height_bits) + 1;
	printf("frame_width_bits %d\n",out->frame_width_bits);
	printf("frame_height_bits %d\n",out->frame_height_bits);

	printf("max_frame_width %d\n",out->max_frame_width);
	printf("max_frame_height %d\n",out->max_frame_height);


	if(out->reduced_still_picture_header){
		out->frame_id_numbers_present_flag = 0;
	}else{
		out->frame_id_numbers_present_flag = readOneBit(bs);
	}
	if(out->frame_id_numbers_present_flag ){
		out->delta_frame_id_length = readBits(bs,4) + 2;
	 	out->additional_frame_id_length = readBits(bs,3) + 1;
	}

	out->use_128x128_superblock = readOneBit(bs);
	out->enable_filter_intra = readOneBit(bs);
	out->enable_intra_edge_filter = readOneBit(bs);
	
	if(out->reduced_still_picture_header){
		out->enable_interintra_compound = 0;
		out->enable_masked_compound = 0;
		out->enable_warped_motion = 0;
		out->enable_dual_filter = 0;
		out->enable_order_hint = 0;
		out->enable_jnt_comp = 0;
		out->enable_ref_frame_mvs = 0;
		out->seq_force_screen_content_tools = 0;
		out->seq_force_integer_mv = 0;
		out->OrderHintBits = 0;

	}else{
		out->enable_interintra_compound = readOneBit(bs);
		out->enable_masked_compound = readOneBit(bs);
		out->enable_warped_motion = readOneBit(bs);
		out->enable_dual_filter = readOneBit(bs);
		out->enable_order_hint = readOneBit(bs);
		if(out->enable_order_hint){
			out->enable_jnt_comp = readOneBit(bs);
			out->enable_ref_frame_mvs = readOneBit(bs);
		}else{
			out->enable_jnt_comp = 0;
			out->enable_ref_frame_mvs = 0;
		}
		out->seq_choose_screen_content_tools = readOneBit(bs);
		if(out->seq_choose_screen_content_tools){
			out->seq_force_screen_content_tools = SELECT_SCREEN_CONTENT_TOOLS;
		}else{
			out->seq_force_screen_content_tools = readOneBit(bs);
		}
		if(out->seq_force_screen_content_tools > 0){
			out->seq_choose_integer_mv = readOneBit(bs);
			if(out->seq_choose_integer_mv){
				out->seq_force_integer_mv = SELECT_INTEGER_MV;
			}else{
				out->seq_force_integer_mv = readOneBit(bs);
			}
		}else{
			out->seq_force_integer_mv = SELECT_INTEGER_MV;
		}
		if(out->enable_order_hint){
			out->OrderHintBits = readBits(bs,3) + 1;
		}
	}
	out->enable_superres = readOneBit(bs);
	out->enable_cdef = readOneBit(bs);
	out->enable_restoration = readOneBit(bs);
	//read ColorConfig;
	out->color_config.high_bitdepth = readOneBit(bs);
	if ( out->seq_profile == 2 && out->color_config.high_bitdepth ) {
		out->color_config.twelve_bit = readOneBit(bs);
		out->color_config.BitDepth = out->color_config.twelve_bit ? 12 : 10;
	} else if ( out->seq_profile <= 2 ) {
		out->color_config.BitDepth = out->color_config.high_bitdepth ? 10 : 8;
	}
	
	if ( out->seq_profile == 1 ) {
		out->color_config.mono_chrome = 0;
	} else {
		out->color_config.mono_chrome = readOneBit(bs);
	}

	out->color_config.NumPlanes = out->color_config.mono_chrome ? 1 : 3;
	out->color_config.color_description_present_flag = readOneBit(bs);
	if ( out->color_config.color_description_present_flag ) {
		out->color_config.color_primaries = readBits(bs,8);
		out->color_config.transfer_characteristics = readBits(bs,8);
		out->color_config.matrix_coefficients = readBits(bs,8);
	} else {
		out->color_config.color_primaries = CP_UNSPECIFIED;
		out->color_config.transfer_characteristics = TC_UNSPECIFIED;
		out->color_config.matrix_coefficients = MC_UNSPECIFIED;
	}

	if ( out->color_config.mono_chrome ) {
		out->color_config.color_range = readOneBit(bs);
		out->color_config.subsampling_x = 1;
		out->color_config.subsampling_y = 1;
		out->color_config.chroma_sample_position = CSP_UNKNOWN;
		out->color_config.separate_uv_delta_q = 0;
		return 0;//标记 !!!!!!!!!!!!!!!!!!
	} else if ( out->color_config.color_primaries == CP_BT_709 &&
		out->color_config.transfer_characteristics == TC_SRGB &&
		out->color_config.matrix_coefficients == MC_IDENTITY ) {
		out->color_config.color_range = 1;
		out->color_config.subsampling_x = 0;
		out->color_config.subsampling_y = 0;
	} else {
		out->color_config.color_range = readOneBit(bs);
		if ( out->seq_profile == 0 ) {
			out->color_config.subsampling_x = 1;
			out->color_config.subsampling_y = 1;

		} else if ( out->seq_profile == 1 ) {
			out->color_config.subsampling_x = 0;
			out->color_config.subsampling_y = 0;
		} else {
			if ( out->color_config.BitDepth == 12 ) {
				out->color_config.subsampling_x = readOneBit(bs);
			if ( out->color_config.subsampling_x )
				out->color_config.subsampling_y = readOneBit(bs);
			else
				out->color_config.subsampling_y = 0;
			} else {
				out->color_config.subsampling_x = 1;
				out->color_config.subsampling_y = 0;
			}
		}
		if ( out->color_config.subsampling_x && out->color_config.subsampling_y ) {
			out->color_config.chroma_sample_position = readBits(bs,2);
		}
	}

	out->film_grain_params_present = readOneBit(bs);
	
	return 0;
}


int obu::parseObuInfo(FILE* fp,int fileOffset,uint8_t *buf,int sz,AV1DecodeContext *ctx)
{
	uint64_t total_size = 1;//obu header + exention header + obu_size

	uint8_t obu_header_buf;
    int ret = fseek(fp,fileOffset,SEEK_SET);
    ASSERT(!ret);
	fread(&obu_header_buf,1,1,fp);

    
    bitSt bs;
    initBitStream(&bs,&obu_header_buf);


	obuHeader obu_header;



    readOneBit(&bs);  //obu_forbidden_bit 解码器忽略
    obu_header.obu_type = readBits(&bs,4);
	//printf("obu_type %d\n",obu_type);
    obu_header.obu_extension_flag = readOneBit(&bs);
	//printf("obu_extension_flag %d\n",obu_extension_flag);
    obu_header.obu_has_size_field = readOneBit(&bs);
	//printf("obu_has_size_field %d\n",obu_has_size_field);
    readOneBit(&bs); //obu_reserved_1bit 解码器忽略


    if(obu_header.obu_extension_flag){
		uint8_t obu_extension_header;
		//fseek(fp,fileOffset + 1,SEEK_SET);
		//ASSERT(!ret);
		fread(&obu_extension_header,1,1,fp);
		initBitStream(&bs,&obu_extension_header); 
		
	
		obu_header.temporal_id = readBits(&bs,3);
		obu_header.spatial_id = readBits(&bs,2);
		readBits(&bs,3); //extension_header_reserved_3bits 解码器忽略
		total_size += 1;
	}

	uint8_t obu_size_buf[8];
	uint64_t obu_size;
	//!!!!!! 这里 fread 了8个字节之后 ，实际上obu_size 并没有 8个字节，
	// 又没有 seek回去 ，这就导致后面数据错了
	if(obu_header.obu_has_size_field){
		uint8_t obu_size_syntax_length;
		//fseek(fp,fileOffset + (obu_extension_flag ? 2 :1),SEEK_SET);
		//ASSERT(!ret);
		fread(obu_size_buf,8,1,fp);
		initBitStream(&bs,obu_size_buf);
		obu_size = readleb128(&bs,&obu_size_syntax_length);

		total_size += obu_size_syntax_length;

		// 上面读了8个字节,但是实际并没有那么长，这里往回退多读的字节
		fseek(fp,-(8 - obu_size_syntax_length),SEEK_CUR);
	}else{
		obu_size = sz - 1 - obu_header.obu_extension_flag;
	}

// read obu payload from file

	printf("obu_header.obu_type %d\n",obu_header.obu_type);
	printf("obu_size  %d\n",obu_size);

	uint8_t obubuffer[obu_size];
	fread(obubuffer,obu_size,1,fp);
	initBitStream(&bs,obubuffer);

	
	switch(obu_header.obu_type){
		case OBU_SEQUENCE_HEADER:
			if(!ctx->seqHdr){
				printf("ctx->seqHdr is null\n");
			}
			parseSequenceHeader(sz,&bs,ctx->seqHdr);
			break;
		case OBU_TEMPORAL_DELIMITER:
			ctx->SeenFrameHeader = 0;
			break;
		case OBU_FRAME:	//frame obu = frame header obu + tile group obu
		case OBU_FRAME_HEADER:
			if(ctx->SeenFrameHeader == 1){
				//copy frame header...
				//may no need to do anything... frameheader store in context;
				break;
			} else {
				ctx->SeenFrameHeader = 1;
				frame::Instance().parseFrameHeader(sz, &bs,ctx, ctx->seqHdr, &obu_header,&ctx->frameHdr);
				BitStreamAlign(&bs);//byte alignment
				if ( ctx->frameHdr.show_existing_frame ) {
					//decode_frame_wrapup();
					ctx->SeenFrameHeader = 0;
				} else {
					//TileNum = 0;
					ctx->SeenFrameHeader = 1;
				}
			}
			if(obu_header.obu_type == OBU_FRAME_HEADER) break;
		case OBU_TILE_GROUP:
			frame::Instance().decodeFrame(sz - bs.offset, &bs,ctx);
			break;
		case OBU_METADATA:
			break;
		case OBU_REDUNDANT_FRAME_HEADER:
			break;
		case OBU_TILE_LIST:
			break;
		case OBU_PADDING:
			break;
		default:
			break;
	}
	
    return total_size + obu_size;
}
