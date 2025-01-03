#ifndef _COMMON_HEADER_
#define _COMMON_HEADER_

#include "common.h"
#include "cdf.h"
typedef void (*tx_add)(uint16_t *dst,int str,int16_t *coeff,int eob);
typedef struct obuHeader{
	uint8_t obu_type;
	uint8_t obu_extension_flag;
	uint8_t obu_has_size_field;
	uint8_t temporal_id;
	uint8_t spatial_id;
}obuHeader;

typedef struct sequenceHeader{
	uint8_t seq_profile;
	uint8_t still_picture;
	uint8_t reduced_still_picture_header;
	uint8_t timing_info_present_flag;
	uint8_t decoder_model_info_present_flag;
	uint8_t initial_display_delay_present_flag;
	uint8_t operating_points_cnt; //operating_points_cnt_minus_1 + 1;
	struct  {
        uint16_t operating_point_idc;
		uint8_t seq_level_idx;
        uint8_t seq_tier;	
        uint8_t decoder_model_present_for_this_op;
		uint8_t initial_display_delay_present_for_this_op;
		uint8_t initial_display_delay; //initial_display_delay_minus_1 + 1
    } seqOperatingPoint[MAX_OPERATING_POINTS];
	struct {
	  uint32_t num_units_in_display_tick;
	  uint32_t time_scale;
	  uint8_t equal_picture_interval;
	  uint32_t num_ticks_per_picture; // num_ticks_per_picture_minus_1 + 1;
 
	}timing_info;

	struct { 
		uint8_t buffer_delay_length; //buffer_delay_length_minus_1 + 1
		uint32_t num_units_in_decoding_tick;
		uint8_t buffer_removal_time_length; //buffer_removal_time_length_minus_1 + 1
		uint8_t frame_presentation_time_length; //frame_presentation_time_length_minus_1 + 1
	}decoder_model_info;
	//考虑这个是否和 seqOperatingPoint合并
	struct operating_parameters_info {
		uint32_t 	decoder_buffer_delay;
		uint32_t	encoder_buffer_delay;
		uint8_t	low_delay_mode_flag;
	}operating_parameters_infos[MAX_OPERATING_POINTS];

	uint16_t frame_width_bits ;//frame_width_bits_minus_1 + 1
	uint16_t frame_height_bits ;//frame_height_bits_minus_1 + 1
	uint16_t max_frame_width ;//max_frame_width_minus_1 + 1
	uint16_t max_frame_height ;//max_frame_height_minus_1 + 1
	uint8_t frame_id_numbers_present_flag;
	uint8_t delta_frame_id_length; //delta_frame_id_length_minus_2 + 2
	uint8_t additional_frame_id_length; //additional_frame_id_length_minus_1 + 1
	uint8_t use_128x128_superblock;
	uint8_t enable_filter_intra;
	uint8_t enable_intra_edge_filter;

	uint8_t enable_interintra_compound;
	uint8_t enable_masked_compound;
	uint8_t enable_warped_motion;
	uint8_t enable_dual_filter;
	uint8_t enable_order_hint;
	uint8_t enable_jnt_comp;
	uint8_t enable_ref_frame_mvs;
	uint8_t seq_choose_screen_content_tools;
	uint8_t seq_force_screen_content_tools;
	uint8_t seq_choose_integer_mv;
	uint8_t seq_force_integer_mv;
	uint8_t OrderHintBits; //order_hint_bits_minus_1 + 1
	
	uint8_t enable_superres;
	uint8_t enable_cdef;
	struct {
		uint8_t  high_bitdepth;
		uint8_t twelve_bit; //twelve_bit和high_bitdepth 还有seq_profile 一起决定了采样位深度
		//if ( seq_profile == 2 && high_bitdepth ) {
		//		twelve_bit f(1)
		//			BitDepth = twelve_bit ? 12 : 10
		//		} else if ( seq_profile <= 2 ) {
		//			BitDepth = high_bitdepth ? 10 : 8
		//		}
		uint8_t mono_chrome; //为1 表示没有色度(u,v) 只有亮度y，为0则y,u,v都有，按照spec seq_profile为1的时候没有这个语法元素
		uint8_t NumPlanes;
		uint8_t BitDepth;
		uint8_t color_description_present_flag; //指示接下来三语法元素是否存在，色彩相关参数 ，详情见spec 6.4.2
		uint8_t color_primaries;
		uint8_t transfer_characteristics;
		uint8_t matrix_coefficients; 
		
		uint8_t color_range; // 色彩范围，为0表示，yuv的值在16-235 之间，为1才是完整的8位 0 - 255
		uint8_t subsampling_x, subsampling_y;//决定色度抽样方式 6.4.2
		uint8_t chroma_sample_position; //指的是色度（chroma）分量的采样位置。  6.4.2
		uint8_t separate_uv_delta_q; // u,v 是否采用不同的量化参数
	
	} color_config;
	uint8_t enable_restoration;
	uint8_t film_grain_params_present;
}sequenceHeader;

typedef struct sizeInfo{
	uint16_t FrameWidth; // 
	uint16_t FrameHeight;
	uint8_t use_superres;
	uint16_t SuperresDenom; //use to coded_denom calculate;
	uint16_t UpscaledWidth;
	uint8_t render_and_frame_size_different;
	uint16_t RenderWidth;
	uint16_t RenderHeight;
}sizeInfo;

typedef struct frameHeader{
	uint8_t FrameIsIntra;
	uint8_t show_existing_frame;
	uint8_t frame_to_show_map_idx;
	uint32_t frame_presentation_time;
	uint8_t display_frame_id;
	uint8_t frame_type;
	uint8_t show_frame;
	uint8_t showable_frame;
	uint8_t error_resilient_mode;
	uint8_t disable_cdf_update;
	uint8_t allow_screen_content_tools;
	uint8_t force_integer_mv;
	uint8_t current_frame_id;
	uint8_t frame_size_override_flag;
	uint8_t OrderHint; //order_hint ,其实就是poc specifies OrderHintBits least significant bits of the expected output order for this frame.
	uint8_t	OrderHints[TOTAL_REFS_PER_FRAME]; //OrderHints specifies the expected output order for each reference frame.
	uint8_t primary_ref_frame;
	uint8_t buffer_removal_time_present_flag;
	struct frameHeaderOperatingPoint {
        uint32_t buffer_removal_time;
    } operating_points[MAX_OPERATING_POINTS];
	uint8_t refresh_frame_flags;
	uint8_t ref_order_hint[NUM_REF_FRAMES];

	sizeInfo si;
	uint8_t allow_intrabc;
	uint8_t frame_refs_short_signaling;
	uint8_t	last_frame_idx;
	uint8_t	gold_frame_idx;
	uint16_t ref_frame_idx[REFS_PER_FRAME];
	uint32_t delta_frame_id[REFS_PER_FRAME];//delta_frame_id_minus_1 + 1;
	uint32_t expectedFrameId[REFS_PER_FRAME];
	//uint8_t found_ref[REFS_PER_FRAME]; 后面的码流中并不需要，所以不加在结构体中了
	uint16_t MiCols,MiRows; //帧中 4*4的块的数目
	uint8_t allow_high_precision_mv;
	uint8_t is_filter_switchable;
	uint8_t	interpolation_filter;
	uint8_t is_motion_mode_switchable;
	uint8_t use_ref_frame_mvs;
	uint8_t RefFrameSignBias[REFS_PER_FRAME]; //参考帧方向 前/后;
	
	uint8_t disable_frame_end_update_cdf;
	struct {
		uint8_t minLog2TileCols,maxLog2TileCols,TileColsLog2, TileCols/*即tile 横向数目*/;
		uint8_t minLog2TileRows,maxLog2TileRows,TileRowsLog2,TileRows/*即tile 竖向数目	*/;
		uint8_t uniform_tile_spacing_flag; //为1表示帧内的 tile尺寸一样（除了边界的tile）
		uint8_t increment_tile_cols_log2; //用于计算 TileColsLog2 ，即tile 横向数目（以2为底的对数）
		uint8_t increment_tile_rows_log2; //用于计算 TileRowsLog2，即tile 竖向数目（以2为底的对数）
		uint16_t MiColStarts[MAX_TILE_COLS];//每个tile的横向起始位置，以4*4亮度采样块为单位
		uint16_t MiRowStarts[MAX_TILE_ROWS];//每个tile的纵向起始位置 以4*4亮度采样块为单位

		
		uint16_t width_in_sbs; // width_in_sbs_minus_1 + 1  tile宽度 以超级块为单位
		uint16_t height_in_sbs;// height_in_sbs_minus_1 _1  tile高度 以超级块为单位
		uint16_t context_update_tile_id; //哪个tile需要更新cdf 标记这里！！！！！ 一帧只能标记一个tile？
		uint8_t TileSizeBytes;//tile_size_bytes_minus_1 + 1 tilesize

	}tile_info;
	struct {
	    uint8_t base_q_idx;//后面几个语法元素的基准，这个也是Y分量的交流系数的量化参数
	    int8_t DeltaQYDc;//y分量的直流量化参数，基于base_q_idx
		int8_t DeltaQUDc, DeltaQUAc, DeltaQVDc, DeltaQVAc; //uv分量的直流 交流量化参数，基于base_q_idx
		uint8_t using_qmatrix; // 是否使用自定义量化矩阵
        uint8_t qm, qm_y, qm_u, qm_v;//量化参数矩阵等级
        
		uint8_t SegQMLevel[3][MAX_SEGMENTS];
	}quantization_params;
	struct {
		uint8_t segmentation_enabled;//图像分割（segmentation）是否开启
		uint8_t segmentation_update_map;//为1 segmentation map 将会在本帧更新，否则使用上一帧的
		uint8_t segmentation_temporal_update;//用于指示是否在当前帧中使用上一帧的分割数据进行更新。
		uint8_t segmentation_update_data;//为1表示分割参数将更新，否则表示使用上一帧的
		
		uint8_t FeatureEnabled[MAX_SEGMENTS][SEG_LVL_MAX];//从feature_enabled计算而来 ，为1表示每个段的feature_value将会编码
		int16_t FeatureData[MAX_SEGMENTS][SEG_LVL_MAX];// feature_value计算而来 ，每个段的具体数据，不是直接读的，需要查表，具体2参见spec 5.9.14


		uint8_t SegIdPreSkip;//它不是一个在码流中存在的语法元素，但是是解码必须的，为1表示在先读段id，再读skip相关语法，否则先读skip语法
		int8_t LastActiveSegId;//LastActiveSegId用于指示具有启用特征的最高分割ID编号。在解码段ID时，
		//这个值被用于只解码与使用的分割段相对应的选项.暂时没弄懂，标记！！！
		uint8_t qindex[MAX_SEGMENTS];
		uint8_t LosslessArray[MAX_SEGMENTS];

	}segmentation_params;
	struct  {
		uint8_t delta_q_present;//delta_q_res是否存在
		uint8_t delta_q_res;//qp值的 delata值 需要左移的位数
	}delta_q_params;
	struct  {
		uint8_t delta_lf_present;//下面两个是否存在
		uint8_t delta_lf_res; //loop filter delta 值需要左移的位数
		uint8_t delta_lf_multi; //为1表示亮度的水平、垂直边沿，色度u、v的边沿有独立的loop filter delta，为0则表示都一样
	}delta_lf_params;
	uint8_t CodedLossless;
	uint8_t AllLossless;
	struct  {
		uint8_t loop_filter_level[4]/*[y][y][u][v] 如果没有色度，则只有2个元素*/;//环路滤波等级
		uint8_t loop_filter_sharpness;//sharpness level
		uint8_t loop_filter_delta_enabled;//是否开启 loop filter delta;
		uint8_t loop_filter_delta_update;//为1表示 delta_lf_params在本帧会更新
		//uint8_t update_ref_delta[TOTAL_REFS_PER_FRAME];//为1表示接下来的loop_filter_ref_deltas存在
		int8_t loop_filter_ref_deltas[TOTAL_REFS_PER_FRAME];//相对于某个参考帧的loop filter 调整值
		//uint8_t update_mode_delta[2];//为1表示下面的loop_filter_mode_deltas存在
		int8_t loop_filter_mode_deltas[2];//对两种环路路滤波模式的调整值
	}loop_filter_params;
	struct  {
		uint8_t CdefDamping;//cdef阻尼值    CdefDamping = cdef_damping_minus_3 + 3,
		uint8_t cdef_bits; //cdef参数比特数
		uint8_t cdef_y_pri_strength[MAX_CDEF_STRENGTHS];//主亮度平滑参数
		uint8_t cdef_y_sec_strength[MAX_CDEF_STRENGTHS];//次亮度平滑参数
		uint8_t cdef_uv_pri_strength[MAX_CDEF_STRENGTHS];//主色度平滑参数
		uint8_t cdef_uv_sec_strength[MAX_CDEF_STRENGTHS];//次色度平滑参数
	}cdef_params;
	struct  {
		uint8_t lr_type[3]; //用于计算FrameRestorationType,也就是帧恢复模式，有一个对应关系，见 6.10.15；
		uint8_t UsesLr; //指示某个平面 是否 使用  loop restoration
		uint8_t lr_unit_shift; //亮度恢复 是否缩小一半
		uint8_t lr_unit_extra_shift; //亮度恢复是否再缩小一半
		uint8_t lr_uv_shift; //色度恢复是否缩小一半
		uint16_t LoopRestorationSize[3]; //某个平面  loop restoration unit的大小，单位是sample(什么sample？ 标记！！)
		uint8_t FrameRestorationType[3];
	}lr_params;
	struct  {
		uint8_t GmType[NUM_REF_FRAMES];
		uint8_t is_global;
		uint8_t is_rot_zoom;
		uint8_t is_translation;
		int gm_params[NUM_REF_FRAMES][6];
		int PrevGmParams[NUM_REF_FRAMES][6];
		
	}global_motion_params;
	struct {
		uint16_t grain_seed;
		uint8_t update_grain;
		uint8_t film_grain_params_ref_idx;
		uint8_t num_y_points;
		uint8_t point_y_value[14];
		uint8_t point_y_scaling[14];
		uint8_t point_cb_value[10];
		uint8_t point_cb_scaling[10];
		uint8_t point_cr_value[10];
		uint8_t point_cr_scaling[10];

		uint8_t chroma_scaling_from_luma;
		uint8_t num_cb_points ;
		uint8_t num_cr_points ;
		uint8_t grain_scaling; //grain_scaling_minus_8 + 8
		uint8_t ar_coeff_lag;
		uint8_t ar_coeffs_y_plus_128[24];
		uint8_t ar_coeffs_cb_plus_128[28];
		uint8_t ar_coeffs_cr_plus_128[28];
		uint8_t ar_coeff_shift; //ar_coeff_shift_minus_6  + 6
		uint8_t grain_scale_shift; 

		uint8_t cb_mult;
		uint8_t cb_luma_mult;
		uint16_t cb_offset; 

		uint8_t cr_mult;
		uint8_t cr_luma_mult;
		uint16_t cr_offset;

		uint8_t overlap_flag;
		uint8_t clip_to_restricted_range;
	}film_grain_params;
	//uint8_t tx_mode_select;
	uint8_t TxMode;
	uint8_t reference_select;

	uint8_t skipModeAllowed;
	uint8_t skip_mode_present;
	int8_t SkipModeFrame[2];
	
	uint8_t allow_warped_motion;//是否使用扭曲运动模式
	uint8_t reduced_tx_set;
}frameHeader;

typedef struct MVPredContext{
	uint8_t NewMvContext;
	uint8_t RefMvContext;
	uint8_t RefMvIdx;
	uint8_t RefIdCount[2];
	uint8_t RefDiffCount[2]; //参考帧的
	int RefIdMvs[2][16][2];
	int RefDiffMvs[2][16][2];
	int RefStackMv[8][2][2]; //consturct by find_mv_stack
	int WeightStack[MAX_REF_MV_STACK_SIZE];
	int DrlCtxStack[MAX_REF_MV_STACK_SIZE];

	int GlobalMvs[2][2];
	uint8_t NumMvFound;
	uint8_t NewMvCount;
	uint8_t FoundMatch;
	uint8_t TotalMatches;
	uint8_t CloseMatches;
	uint8_t ZeroMvContext;

	uint8_t NumSamples;
	uint8_t NumSamplesScanned;

}MVPredContext;
typedef struct BlockData{
	uint8_t HasChroma;
	uint8_t skip;
	uint8_t skip_mode;
	uint16_t MiRow; //block 在帧中起始位置 4* 4为单位
	uint16_t MiCol; //block 在帧中起始位置 4* 4为单位
	uint8_t MiSize; //block size/类型 看 em_SubSize
	uint8_t AvailU;
	uint8_t AvailL;
	uint8_t AvailUChroma;
	uint8_t AvailLChroma;

	int8_t segment_id;
	uint8_t Lossless;
	int8_t RefFrame[2];
	uint8_t use_intrabc;
	uint8_t is_inter;

	uint8_t YMode;
	uint8_t UVMode;
	uint8_t motion_mode;
	uint8_t compound_type;
	uint8_t interp_filter[2];
	int8_t AngleDeltaY;
	int8_t AngleDeltaUV;

	int8_t CflAlphaU;
	int8_t CflAlphaV;

// palette mode info
	uint8_t PaletteSizeY;
	uint16_t palette_colors_y[8];
	uint8_t PaletteSizeUV;
	uint16_t palette_colors_u[8];
	uint16_t palette_colors_v[8];
	uint16_t PaletteCache[8]; 

	uint8_t use_filter_intra;
	uint8_t filter_intra_mode;

	int8_t LeftRefFrame[2];
	int8_t AboveRefFrame[2];

	uint8_t comp_group_idx;
	uint8_t compound_idx;

	uint8_t mask_type;

	uint8_t AboveSingle;
	uint8_t LeftSingle;
	uint8_t AboveIntra;
	uint8_t LeftIntra;

	uint8_t interintra;
	uint8_t interintra_mode;
	uint8_t wedge_interintra;
	uint8_t wedge_index;
	uint8_t wedge_sign;

	//palette 调色板
	uint8_t has_palette_y;
	uint8_t has_palette_uv;
	uint8_t **ColorMapY;
	uint8_t **ColorMapUV;
	uint8_t ColorOrder[PALETTE_COLORS];
	uint8_t ColorContextHash;

	int8_t TxSize;

	int Mv[2][2]; //[ref][x/y]

 	//帧内预测
	Array16 *AboveRow; //块上边的样本，是像素值
	Array16 *LeftCol; //块左边的样本，是像素值

	//帧间预测
	uint16_t **Mask;
	int CandList[4][4];//第一维size 不大确定

	//量化
	//量化参数，一个块量化参数值小于 1024 个，通过 Default_Scan系列的数组映射出相应的 pos ,
	//pos 也小于 1024 分布 于整个块内
	int16_t Quant[1024]; //先直接拉满
	int16_t Dequant[32][32];//先直接拉满
	int16_t eob;

	//reconstruct 重建图像
	int PlaneTxType;
	
	//7.11.5
	int MaxLumaW;
	int MaxLumaH;
	MVPredContext mvpCtx;

}BlockData;
typedef struct LoopRestorationContext{
	
	uint16_t **LrFrame[3]; //经过LoopRestoration 之后的像素数据
	int16_t ****LrWiener[3];
	int16_t **LrType[3];
	int16_t **LrSgrSet[3];
	int16_t ***LrSgrXqd[3];	
	int PlaneEndX;   // 当前平面的水平边界
	int PlaneEndY;   // 当前平面的垂直边界
	int StripeStartY; // 当前partition的起始y坐标
	int StripeEndY;   // 当前partition的结束y坐标
}LoopRestorationContext;
typedef struct FilmGainContext{
	int LumaGrain[73][82];
	int CbGrain[38][44]; //负值？？？
	int CrGrain[38][44];
	int ScalingLut[3][256];
}FilmGainContext;
typedef struct MFMVContext{
	int **MfRefFrames;
	int ***MfMvs;
}MFMVContext;

typedef struct FrameContext{
	//sizeInfo si;
	frameHeader frameHdr;
	CDFArrays cdfCtx;
	CDFArrays tileSavedCdf;
	CDFArrays currentTileCdf;
	//int currentTileNum;
	uint16_t **CurrFrame[3];//经过预测重建 之后的像素数据(指解码完成之后，解码完成之前可能是无效数据)
	uint16_t **CdefFrame[3];//cdef 之后的数据
	uint16_t **UpscaledCdefFrame[3];
	uint16_t **UpscaledCurrFrame[3];
	LoopRestorationContext *lrCtx;
	uint16_t **OutY; //FilmGain 之前的所有过程都完成的数据
	uint16_t **OutU;
	uint16_t **OutV;
	FilmGainContext *fgCtx;
	MFMVContext *mfmvCtx;
	//MVPredContext *mvpCtx;
	int16_t **cdef_idx;
}FrameContext;

typedef struct AV1DecodeContext{
	FrameContext 	*ref_frames[NUM_REF_FRAMES];
	FrameContext *currentFrame;
	sequenceHeader seqHdr;
	frameHeader frameHdr;
	int decAlloced;

    //CDFArrays cdfCtxs[NUM_REF_FRAMES];
	//CDFArrays tileSavedCdf;

	uint8_t	RefValid[NUM_REF_FRAMES];
	uint8_t RefFrameId[NUM_REF_FRAMES];
	uint8_t	RefOrderHint[NUM_REF_FRAMES];
	Array16* RefUpscaledWidth;// size NUM_REF_FRAMES
	Array16* RefFrameWidth;// size NUM_REF_FRAMES
	Array16* RefFrameHeight;// size NUM_REF_FRAMES
	Array16* RefRenderWidth;// size NUM_REF_FRAMES
	Array16* RefRenderHeight;// size NUM_REF_FRAMES
	uint16_t RefMiCols[NUM_REF_FRAMES];
	uint16_t RefMiRows[NUM_REF_FRAMES];
	uint8_t RefFrameType[NUM_REF_FRAMES];
	uint8_t RefSubsamplingX[NUM_REF_FRAMES];
	uint8_t RefSubsamplingY[NUM_REF_FRAMES];
	uint8_t RefBitDepth[NUM_REF_FRAMES];
	uint8_t SavedOrderHints[NUM_REF_FRAMES][TOTAL_REFS_PER_FRAME];
	uint16_t **FrameStore[NUM_REF_FRAMES][3];
	int **SavedRefFrames[NUM_REF_FRAMES];
	int ***SavedMvs[NUM_REF_FRAMES];
	uint8_t SavedGmParams[NUM_REF_FRAMES][NUM_REF_FRAMES][8];
	uint8_t **SavedSegmentIds[NUM_REF_FRAMES];

	int InterPostRound ;//预测过程结束后的舍入量
	int InterRound0; //水平滤波后舍入量
	int InterRound1; //垂直滤波后舍入量


//tile 独立解码单元
	uint16_t MiRowStart;//当前tile在frame中 行的起始位置 以 4*4 为单位
	uint16_t MiRowEnd; //当前tile在frame中 行的结束位置 以 4*4 为单位
	uint16_t MiColStart;//当前tile在frame中 列的起始位置 以 4*4 为单位
	uint16_t MiColEnd;//当前tile在frame中 列的结束位置 以 4*4 为单位
	int16_t RefSgrXqd[3][2];
	int16_t RefLrWiener[3][2][3];
	uint8_t ReadDeltas;
	uint8_t CurrentQIndex;
	tArray8 *BlockDecoded; //标记已经解码的 4 * 4 块  
	uint8_t **LoopfilterTxSizes[3];
	int *AboveLevelContext[3];
	int *AboveDcContext[3];
	int *LeftLevelContext[3];
	int *LeftDcContext[3];
	int *AboveSegPredContext;
	int *LeftSegPredContext;
	int8_t DeltaLF[4];	

 // partition	 可以理解为 H264 中的 宏块，为固定大小（超级块的情况下为 128 * 128）?
 //否则 为 64 * 64 ,在这个区域内 再划分 block，block的大小则有很多种情况，与 hevc的ctu - cu关系类似了
 //都是以4 * 4 块为单位的
	uint8_t **YModes;
	uint8_t **UVModes;
	int ***RefFrames; //?
	uint8_t **CompGroupIdxs;
	uint8_t **CompoundIdxs;
	uint8_t ***InterpFilters;
	int ****Mvs; // [row][col][ref][x/y] 
	uint8_t **MiSizes; //以 4 * 4 块为单位，某个block的所有 4 * 4 块的值都一样
	int8_t **SegmentIds;
	uint8_t **IsInters;
	uint8_t **SkipModes;
	uint8_t **Skips;
	uint8_t **TxSizes;
	uint8_t **PaletteSizes[2];
	uint8_t ***PaletteColors[2];
	int8_t ***DeltaLFs;
	int8_t **InterTxSizes;
	uint8_t **TxTypes; //4 * 4 块为单位

	uint8_t SeenFrameHeader;
	int ***MotionFieldMvs[8];// [ref][y][x][x/y] 
	uint8_t **PrevSegmentIds;

	tx_add tx_adds[TX_SIZES_ALL][TX_TYPES];
	
}AV1DecodeContext;


#endif