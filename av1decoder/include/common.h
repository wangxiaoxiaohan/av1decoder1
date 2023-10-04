#ifndef _COMMON_
#define _COMMON_
#include "stdio.h"
#include "stdint.h"
enum tristate
{
	ONE = 0,
	TWO = 1,
	THREE = 2,
};
#define MAX_OPERATING_POINTS 32 // A.3.

#define MAX_CDEF_STRENGTHS 7

#define MAX_SEGMENTS 8
#define MAX_LOOP_FILTER 63

#define SEG_LVL_MAX 8 // 这个表示一个段内的 8个“feature”，(不是一个帧内最大8个段 ，这有另一个宏MAX_SEGMENTS 来表示)
// 每一个feature的index 用宏来表示，并说明功能，
// 比如下面的 SEG_LVL_REF_FRAME， SEG_LVL_GLOBALMV
#define SEG_LVL_REF_FRAME 5
#define SEG_LVL_GLOBALMV 7
#define SEG_LVL_ALT_Q 0
#define SEG_LVL_ALT_LF_Y_V 1
#define SEG_LVL_SKIP 6

#define SELECT_SCREEN_CONTENT_TOOLS 2
#define SELECT_INTEGER_MV 2

#define REFS_PER_FRAME 7
#define NUM_REF_FRAMES 8
#define TOTAL_REFS_PER_FRAME 8

#define PRIMARY_REF_NONE 7

#define SUPERRES_DENOM_BITS 3
#define SUPERRES_DENOM_MIN 9
#define SUPERRES_NUM 8

#define MAX_TILE_WIDTH 4096
#define MAX_TILE_AREA 4096 * 2304
#define MAX_TILE_ROWS 64
#define MAX_TILE_COLS 64

#define RESTORATION_TILESIZE_MAX 256

#define IDENTITY 0
#define TRANSLATION 1
#define ROTZOOM 2
#define AFFINE 3

#define WARPEDMODEL_PREC_BITS 16

#define GM_ABS_TRANS_ONLY_BITS 9
#define GM_ABS_ALPHA_BITS 12
#define GM_ABS_TRANS_BITS 12
#define GM_ALPHA_PREC_BITS 15
#define GM_TRANS_PREC_BITS 6
#define GM_TRANS_ONLY_PREC_BITS 3

#define FRAME_LF_COUNT 4
#define WIENER_COEFFS 3

#define BLOCK_SIZES 22
#define BLOCK_SIZE_GROUPS 4

#define INTRA_MODE_CONTEXTS 5
#define INTRA_MODES 13

#define UV_INTRA_MODES_CFL_NOT_ALLOWED 13
#define UV_INTRA_MODES_CFL_ALLOWED 14
#define DIRECTIONAL_MODES 8

#define MAX_ANGLE_DELTA 3

#define PARTITION_CONTEXTS 4

#define TX_SIZE_CONTEXTS 3
#define MAX_TX_DEPTH 2
#define TXFM_PARTITION_CONTEXTS 21

#define SEGMENT_ID_CONTEXTS 3
#define SEGMENT_ID_PREDICTED_CONTEXTS 3

#define MV_OFFSET_BITS 10

#define NEW_MV_CONTEXTS 6
#define ZERO_MV_CONTEXTS 2
#define MV_CONTEXTS 2
#define MV_INTRABC_CONTEXT 1
#define MV_JOINTS 4
#define MV_CLASSES 11

#define REF_MV_CONTEXTS 6
#define DRL_MODE_CONTEXTS 3

#define IS_INTER_CONTEXTS 4
#define COMP_INTER_CONTEXTS 5
#define SKIP_MODE_CONTEXTS 3
#define SKIP_CONTEXTS 3
#define REF_CONTEXTS 3
#define FWD_REFS 4
#define BWD_REFS 3
#define SINGLE_REFS 7
#define UNIDIR_COMP_REFS 4
#define COMPOUND_TYPES 2

#define COMPOUND_MODES 8
#define COMPOUND_MODE_CONTEXTS 8
#define INTERP_FILTERS 3
#define INTERP_FILTER_CONTEXTS 16
#define MOTION_MODES 3
#define CLASS0_SIZE 2

#define PALETTE_COLOR_CONTEXTS 5
#define PALETTE_MAX_COLOR_CONTEXT_HASH 8
#define PALETTE_BLOCK_SIZE_CONTEXTS 7
#define PALETTE_Y_MODE_CONTEXTS 3
#define PALETTE_UV_MODE_CONTEXTS 2
#define PALETTE_SIZES 7
#define PALETTE_COLORS 8
#define PALETTE_NUM_NEIGHBORS 3

#define COEFF_CDF_Q_CTXS 4
#define TX_SIZES 5
#define PLANE_TYPES 2

#define DELTA_Q_SMALL 3
#define DELTA_LF_SMALL 3
#define COMP_GROUP_IDX_CONTEXTS 6
#define COMPOUND_IDX_CONTEXTS 6
#define INTERINTRA_MODES 4

#define CFL_JOINT_SIGNS 8
#define CFL_ALPHABET_SIZE 16
#define CFL_ALPHA_CONTEXTS 6

#define COMP_REF_TYPE_CONTEXTS 5
#define COMP_INTER_CONTEXTS 5
#define TXB_SKIP_CONTEXTS 13
#define EOB_COEF_CONTEXTS 9
#define SIG_COEF_CONTEXTS 42

#define DC_SIGN_CONTEXTS 3
#define LEVEL_CONTEXTS 21
#define BR_CDF_SIZE 4
#define SIG_COEF_CONTEXTS_EOB 4

#define EC_PROB_SHIFT 6
#define EC_MIN_PROB 4

#define MI_SIZE 4

#define INTRABC_DELAY_PIXELS 256

#define MAX_REF_MV_STACK_SIZE 8
#define REF_CAT_LEVEL 640

#define TX_SIZES_ALL 19
#define MI_SIZE_LOG2 2
#define COMP_NEWMV_CTXS 5
#define REF_SCALE_SHIFT 14
#define MAX_VARTX_DEPTH 2

#define INTRA_FILTER_SCALE_BITS 4

#define INTRA_FILTER_MODES 5

#define INTRA_EDGE_KERNELS 3
#define INTRA_EDGE_TAPS 5

#define WARPEDMODEL_TRANS_CLAMP 1 << 23

#define WARPEDMODEL_NONDIAGAFFINE_CLAMP 1 << 13
#define WARPEDPIXEL_PREC_SHIFTS 1 << 6
#define WARPEDDIFF_PREC_BITS 10

#define DIV_LUT_NUM 257
#define DIV_LUT_PREC_BITS 14
#define DIV_LUT_BITS 8
#define MASK_MASTER_SIZE 64
#define MAX_SB_SIZE 128
#define MAX_FRAME_DISTANCE 31

#define SINPI_1_9 1321
#define SINPI_2_9 2482
#define SINPI_3_9 3344
#define SINPI_4_9 3803

#define SUPERRES_NUM 8
#define SUPERRES_DENOM_MIN 9
#define SUPERRES_DENOM_BITS 3
#define SUPERRES_FILTER_BITS 6
#define SUPERRES_FILTER_SHIFTS 1 << SUPERRES_FILTER_BITS
#define SUPERRES_FILTER_TAPS 8
#define SUPERRES_FILTER_OFFSET 3
#define SUPERRES_SCALE_BITS 14
#define SUPERRES_SCALE_MASK (1 << 14) - 1
#define SUPERRES_EXTRA_BITS 8
#define SGRPROJ_PARAMS_BITS 4
// 以下三种自定义 数组，支持访问 -1 下标。内部做了转换，-1实际上为第一个元素。总元素数量比构造传入的值是多一个的
// 一维数组性能较之普通数组损失在6-7层左右
// 二维数组性能一半左右
// 三维未测
#define INT_MIN 2147483647
#define MFMV_STACK_SIZE 3
#define MAX_OFFSET_WIDTH 8
#define MAX_OFFSET_HEIGHT 0
#define MV_BORDER 128

#define TX_SET_TYPES_INTRA 3
#define TX_SET_TYPES_INTER 4
#define TX_TYPES 16

#define TX_CLASS_2D 0
#define TX_CLASS_HORIZ 1
#define TX_CLASS_VERT 2
#define SIG_COEF_CONTEXTS_2D 26
#define SIG_REF_DIFF_OFFSET_NUM 5
#define NUM_BASE_LEVELS 2
#define COEFF_BASE_RANGE 12
#define LEAST_SQUARES_SAMPLES_MAX 8
#define ANGLE_STEP 3
#define FILTER_BITS 7
#define LS_MV_MAX 256
#define WARP_PARAM_REDUCE_BITS 6
#define SUBPEL_BITS 4
#define SUBPEL_MASK 15
#define SCALE_SUBPEL_BITS 10
#define WEDGE_TYPES 16

#define Block_Width 4 * Num_4x4_Blocks_Wide
#define Block_Height 4 * Num_4x4_Blocks_High

#define QM_TOTAL_SIZE 3344
typedef struct Array8
{
	uint8_t *data;
	uint8_t &operator[](int i)
	{
		return data[i + 1];
	}
	Array8(int size)
	{
		data = new uint8_t[size + 1];
	}
	~Array8()
	{
		delete[] data;
		data = NULL;
	}
};
typedef struct dArray8
{
	Array8 **data;
	uint16_t mSize1;
	Array8 &operator[](int i)
	{
		return *(data[i + 1]);
	}

	dArray8(int size1, int size2)
	{
		mSize1 = size1 + 1;
		data = new Array8 *[mSize1];
		for (int i = 0; i < mSize1; i++)
		{
			data[i] = new Array8(size2);
		}
	}
	~dArray8()
	{
		for (int i = 0; i < mSize1; i++)
		{
			delete data[i];
		}
		delete[] data;
		data = NULL;
	}
};
typedef struct tArray8
{
	dArray8 **data;
	uint16_t mSize1;
	dArray8 &operator[](int i)
	{
		return *(data[i + 1]);
	}

	tArray8(int size1, int size2, int size3)
	{
		mSize1 = size1 + 1;
		data = new dArray8 *[mSize1];
		for (int i = 0; i < mSize1; i++)
		{
			data[i] = new dArray8(size2, size3);
		}
	}
	~tArray8()
	{
		for (int i = 0; i < mSize1; i++)
		{
			delete data[i];
		}
		delete[] data;
		data = NULL;
	}
};

typedef struct Array16
{
	uint16_t *data;
	uint16_t &operator[](int i)
	{
		return data[i + 1];
	}
	Array16(int size)
	{
		data = new uint16_t[size + 1];
	}
	~Array16()
	{
		delete[] data;
		data = NULL;
	}
};
typedef struct dArray16
{
	Array16 **data;
	uint16_t mSize1;
	Array16 &operator[](int i)
	{
		return *(data[i + 1]);
	}

	dArray16(int size1, int size2)
	{
		mSize1 = size1 + 1;
		data = new Array16 *[mSize1];
		for (int i = 0; i < mSize1; i++)
		{
			data[i] = new Array16(size2);
		}
	}
	~dArray16()
	{
		for (int i = 0; i < mSize1; i++)
		{
			delete data[i];
		}
		delete[] data;
		data = NULL;
	}
};
typedef struct tArray16
{
	dArray16 **data;
	uint16_t mSize1;
	dArray16 &operator[](int i)
	{
		return *(data[i + 1]);
	}

	tArray16(int size1, int size2, int size3)
	{
		mSize1 = size1 + 1;
		data = new dArray16 *[mSize1];
		for (int i = 0; i < mSize1; i++)
		{
			data[i] = new dArray16(size2, size3);
		}
	}
	~tArray16()
	{
		for (int i = 0; i < mSize1; i++)
		{
			delete data[i];
		}
		delete[] data;
		data = NULL;
	}
};

typedef struct Array32
{
	uint32_t *data;
	uint32_t &operator[](int i)
	{
		return data[i + 1];
	}
	Array32(int size)
	{
		data = new uint32_t[size + 1];
	}
	~Array32()
	{
		delete[] data;
		data = NULL;
	}
};
typedef struct dArray32
{
	Array32 **data;
	uint32_t mSize1;
	Array32 &operator[](int i)
	{
		return *(data[i + 1]);
	}

	dArray32(int size1, int size2)
	{
		mSize1 = size1 + 1;
		data = new Array32 *[mSize1];
		for (int i = 0; i < mSize1; i++)
		{
			data[i] = new Array32(size2);
		}
	}
	~dArray32()
	{
		for (int i = 0; i < mSize1; i++)
		{
			delete data[i];
		}
		delete[] data;
		data = NULL;
	}
};
typedef struct tArray32
{
	dArray32 **data;
	uint32_t mSize1;
	dArray32 &operator[](int i)
	{
		return *(data[i + 1]);
	}

	tArray32(int size1, int size2, int size3)
	{
		mSize1 = size1 + 1;
		data = new dArray32 *[mSize1];
		for (int i = 0; i < mSize1; i++)
		{
			data[i] = new dArray32(size2, size3);
		}
	}
	~tArray32()
	{
		for (int i = 0; i < mSize1; i++)
		{
			delete data[i];
		}
		delete[] data;
		data = NULL;
	}
};

enum em_interpolation_filters
{
	EIGHTTAP = 0,
	EIGHTTAP_SMOOTH = 1,
	EIGHTTAP_SHARP = 2,
	BILINEAR = 3,
	SWITCHABLE = 4,
};
enum em_color_primaries
{
	CP_BT_709 = 1,		 // BT.709
	CP_UNSPECIFIED = 2,	 // Unspecified
	CP_BT_470_M = 4,	 // BT.470 System M (historical)
	CP_BT_470_B_G = 5,	 // BT.470 System B, G (historical)
	CP_BT_601 = 6,		 // BT.601
	CP_SMPTE_240 = 7,	 // SMPTE 240
	CP_GENERIC_FILM = 8, // Generic film (color filters using illuminant C)
	CP_BT_2020 = 9,		 // BT.2020, BT.2100
	CP_XYZ = 10,		 // SMPTE 428 (CIE 1921 XYZ)
	CP_SMPTE_431 = 11,	 // SMPTE RP 431-2
	CP_SMPTE_432 = 12,	 // SMPTE EG 432-1
	CP_EBU_3213 = 22,	 // EBU Tech. 3213-E
};
enum em_transfer_characteristics
{
	TC_RESERVED_0 = 0, // For future use
	TC_BT_709,		   // BT.709
	TC_UNSPECIFIED,	   // Unspecified
	TC_RESERVED_3,	   // For future use
	TC_BT_470_M,	   //  BT.470 System M (historical)
	TC_BT_470_B_G,	   // BT.470 System B, G (historical)
	TC_BT_601,		   // BT.601
	TC_SMPTE_240,	   // SMPTE 240 M
	TC_LINEAR,		   // Linear
	TC_LOG_100,		   // Logarithmic (100 : 1 range)
	TC_LOG_100_SQRT10, // Logarithmic (100 * Sqrt(10) : 1 range)
	TC_IEC_61966,	   // IEC 61966-2-4
	TC_BT_1361,		   // BT.1361
	TC_SRGB,		   // sRGB //or sYCC
	TC_BT_2020_10_BIT, // BT.2020 10-bit systems
	TC_BT_2020_12_BIT, // BT.2020 12-bit systems
	TC_SMPTE_2084,	   // SMPTE ST 2084, ITU BT.2100 PQ
	TC_SMPTE_428,	   // SMPTE ST 428
	TC_HLG,			   // BT.2100 HLG, ARIB STD-B67
};

enum em_matrix_coefficients
{
	MC_IDENTITY = 0, // Identity matrix
	MC_BT_709,		 // BT.709
	MC_UNSPECIFIED,	 // Unspecified
	MC_RESERVED_3,	 // For future use
	MC_FCC,			 // US FCC 73.628
	MC_BT_470_B_G,	 // BT.470 System B, G (historical)
	MC_BT_601,		 // BT.601
	MC_SMPTE_240,	 // SMPTE 240 M
	MC_SMPTE_YCGCO,	 // YCgCo
	MC_BT_2020_NCL,	 // BT.2020 non-constant luminance, BT.2100 YCbCr
	MC_BT_2020_CL,	 // BT.2020 constant luminance
	MC_SMPTE_2085,	 // SMPTE ST 2085 YDzDx
	MC_CHROMAT_NCL,	 // Chromaticity-derived non-constant luminance
	MC_CHROMAT_CL,	 // Chromaticity-derived constant luminance
	MC_ICTCP,		 // BT.2100 ICtCp

};
enum em_chroma_sample_position
{

	CSP_UNKNOWN = 0, // Unknown(in this case the source video transfer function must be ignaled outside the AV1 bitstream)
	CSP_VERTICAL,	 // Horizontally co-located with (0, 0) luma sample, vertical position in he middle between two luma samples
	CSP_COLOCATED,	 // co-located with (0, 0) luma sample
	CSP_RESERVED,

};

enum em_frame_type
{
	KEY_FRAME = 0,
	INTER_FRAME = 1,
	INTRA_ONLY_FRAME = 2,
	SWITCH_FRAME = 3
};
enum em_ref_frame_type
{
	NONE = -1,
	INTRA_FRAME = 0,
	LAST_FRAME,
	LAST2_FRAME,
	LAST3_FRAME,
	GOLDEN_FRAME,
	BWDREF_FRAME,
	ALTREF2_FRAME,
	ALTREF_FRAME,
};

enum obuType
{
	OBU_SEQUENCE_HEADER = 1,
	OBU_TEMPORAL_DELIMITER = 2,
	OBU_FRAME_HEADER = 3,
	OBU_TILE_GROUP = 4,
	OBU_METADATA = 5,
	OBU_FRAME = 6,
	OBU_REDUNDANT_FRAME_HEADER = 7,
	OBU_TILE_LIST = 8,
	OBU_PADDING = 15,
};
enum em_frame_restoration_type
{
	RESTORE_NONE = 0,
	RESTORE_WIENER = 1,
	RESTORE_SGRPROJ = 2,
	RESTORE_SWITCHABLE = 3
};

enum em_TxMode
{
	ONLY_4X4 = 0,
	TX_MODE_LARGEST = 1,
	TX_MODE_SELECT = 2
};
enum em_SubSize
{
	BLOCK_4X4 = 0,
	BLOCK_4X8 = 1,
	BLOCK_8X4 = 2,
	BLOCK_8X8 = 3,
	BLOCK_8X16 = 4,
	BLOCK_16X8 = 5,
	BLOCK_16X16 = 6,
	BLOCK_16X32 = 7,
	BLOCK_32X16 = 8,
	BLOCK_32X32 = 9,
	BLOCK_32X64 = 10,
	BLOCK_64X32 = 11,
	BLOCK_64X64 = 12,
	BLOCK_64X128 = 13,
	BLOCK_128X64 = 14,
	BLOCK_128X128 = 15,
	BLOCK_4X16 = 16,
	BLOCK_16X4 = 17,
	BLOCK_8X32 = 18,
	BLOCK_32X8 = 19,
	BLOCK_16X64 = 20,
	BLOCK_64X16 = 21,
	BLOCK_INVALID = 22
};
enum em_partition
{
	PARTITION_NONE = 0,
	PARTITION_HORZ,
	PARTITION_VERT,
	PARTITION_SPLIT,
	PARTITION_HORZ_A,
	PARTITION_HORZ_B,
	PARTITION_VERT_A,
	PARTITION_VERT_B,
	PARTITION_HORZ_4,
	PARTITION_VERT_4
};
enum em_intra_frame_y_mode
{
	DC_PRED = 0,
	V_PRED,
	H_PRED,
	D45_PRED,
	D135_PRED,
	D113_PRED,
	D157_PRED,
	D203_PRED,
	D67_PRED,
	SMOOTH_PRED,
	SMOOTH_V_PRED,
	SMOOTH_H_PRED,
	PAETH_PRED
};
enum em_motion_mode
{
	SIMPLE = 0,
	OBMC,
	LOCALWARP
};
enum em_compound_type
{
	COMPOUND_WEDGE = 0,
	COMPOUND_DIFFWTD,
	COMPOUND_AVERAGE,
	COMPOUND_INTRA,
	COMPOUND_DISTANCE
};
enum em_ymode
{
	NEARESTMV = 14,
	NEARMV,
	GLOBALMV,
	NEWMV,
	NEAREST_NEARESTMV,
	NEAR_NEARMV,
	NEAREST_NEWMV,
	NEW_NEARESTMV,
	NEAR_NEWMV,
	NEW_NEARMV,
	GLOBAL_GLOBALMV,
	NEW_NEWMV
};
enum em_mv_joint
{
	MV_JOINT_ZERO = 0,
	MV_JOINT_HNZVZ,
	MV_JOINT_HZVNZ,
	MV_JOINT_HNZVNZ
};
enum em_uv_mode
{
	DC_PRED = 0,
	V_PRED,
	H_PRED,
	D45_PRED,
	D135_PRED,
	D113_PRED,
	D157_PRED,
	D203_PRED,
	D67_PRED,
	SMOOTH_PRED,
	SMOOTH_V_PRED,
	SMOOTH_H_PRED,
	PAETH_PRED,
	UV_CFL_PRED
};
enum em_mv_class
{
	MV_CLASS_0 = 0,
	MV_CLASS_1,
	MV_CLASS_2,
	MV_CLASS_3,
	MV_CLASS_4,
	MV_CLASS_5,
	MV_CLASS_6,
	MV_CLASS_7,
	MV_CLASS_8,
	MV_CLASS_9,
	MV_CLASS_10
};

enum em_signU
{
	CFL_SIGN_ZERO = 0,
	CFL_SIGN_NEG,
	CFL_SIGN_POS,
};
enum em_comp_mode
{
	SINGLE_REFERENCE = 0,
	COMPOUND_REFERENCE
};
enum em_comp_ref_type
{
	UNIDIR_COMP_REFERENCE = 0, // Both reference frames from the same group
	BIDIR_COMP_REFERENCE	   // One from Group 1 and one from Group 2
};
enum em_TxSize
{
	TX_4X4 = 0,
	TX_8X8,
	TX_16X16,
	TX_32X32,
	TX_64X64,
	TX_4X8,
	TX_8X4,
	TX_8X16,
	TX_16X8,
	TX_16X32,
	TX_32X16,
	TX_32X64,
	TX_64X32,
	TX_4X16,
	TX_16X4,
	TX_8X32,
	TX_32X8,
	TX_16X64,
	TX_64X16,
};
enum em_interintra_mode
{
	II_DC_PRED = 0,
	II_V_PRED,
	II_H_PRED,
	II_SMOOTH_PRED,
};
enum em_wedge_direction_constants
{
	WEDGE_HORIZONTAL = 0,
	WEDGE_VERTICAL,
	WEDGE_OBLIQUE27,
	WEDGE_OBLIQUE63,
	WEDGE_OBLIQUE117,
	WEDGE_OBLIQUE153,
};
enum em_inverse_transform
{
	DCT_DCT = 0,
	ADST_DCT = 1,
	DCT_ADST = 2,
	ADST_ADST = 3,
	FLIPADST_DCT = 4,
	DCT_FLIPADST = 5,
	FLIPADST_FLIPADST = 6,
	ADST_FLIPADST = 7,
	FLIPADST_ADST = 8,
	IDTX = 9,
	V_DCT = 10,
	H_DCT = 11,
	V_ADST = 12,
	H_ADST = 13,
	V_FLIPADST = 14,
	H_FLIPADST = 15,
};
enum em_tx_set
{
	TX_SET_DCTONLY = 0,
	TX_SET_INTRA_1,
	TX_SET_INTRA_2,
	TX_SET_INTER_1,
	TX_SET_INTER_2,
	TX_SET_INTER_3,
};

const static uint8_t Remap_Lr_Type[4] = {
	RESTORE_NONE, RESTORE_SWITCHABLE, RESTORE_WIENER, RESTORE_SGRPROJ};
const static int8_t Wiener_Taps_Mid[3] = {
	3, -7, 15};
const static int8_t Sgrproj_Xqd_Mid[2] = {
	-32, 31};

const static int8_t Subsampled_Size[BLOCK_SIZES][2][2] = {
	{{BLOCK_4X4, BLOCK_4X4}, {BLOCK_4X4, BLOCK_4X4}},
	{{BLOCK_4X8, BLOCK_4X4}, {BLOCK_INVALID, BLOCK_4X4}},
	{{BLOCK_8X4, BLOCK_INVALID}, {BLOCK_4X4, BLOCK_4X4}},
	{{BLOCK_8X8, BLOCK_8X4}, {BLOCK_4X8, BLOCK_4X4}},
	{{BLOCK_8X16, BLOCK_8X8}, {BLOCK_INVALID, BLOCK_4X8}},
	{{BLOCK_16X8, BLOCK_INVALID}, {BLOCK_8X8, BLOCK_8X4}},
	{{BLOCK_16X16, BLOCK_16X8}, {BLOCK_8X16, BLOCK_8X8}},
	{{BLOCK_16X32, BLOCK_16X16}, {BLOCK_INVALID, BLOCK_8X16}},
	{{BLOCK_32X16, BLOCK_INVALID}, {BLOCK_16X16, BLOCK_16X8}},
	{{BLOCK_32X32, BLOCK_32X16}, {BLOCK_16X32, BLOCK_16X16}},
	{{BLOCK_32X64, BLOCK_32X32}, {BLOCK_INVALID, BLOCK_16X32}},
	{{BLOCK_64X32, BLOCK_INVALID}, {BLOCK_32X32, BLOCK_32X16}},
	{{BLOCK_64X64, BLOCK_64X32}, {BLOCK_32X64, BLOCK_32X32}},
	{{BLOCK_64X128, BLOCK_64X64}, {BLOCK_INVALID, BLOCK_32X64}},
	{{BLOCK_128X64, BLOCK_INVALID}, {BLOCK_64X64, BLOCK_64X32}},
	{{BLOCK_128X128, BLOCK_128X64}, {BLOCK_64X128, BLOCK_64X64}},
	{{BLOCK_4X16, BLOCK_4X8}, {BLOCK_INVALID, BLOCK_4X8}},
	{{BLOCK_16X4, BLOCK_INVALID}, {BLOCK_8X4, BLOCK_8X4}},
	{{BLOCK_8X32, BLOCK_8X16}, {BLOCK_INVALID, BLOCK_4X16}},
	{{BLOCK_32X8, BLOCK_INVALID}, {BLOCK_16X8, BLOCK_16X4}},
	{{BLOCK_16X64, BLOCK_16X32}, {BLOCK_INVALID, BLOCK_8X32}},
	{{BLOCK_64X16, BLOCK_INVALID}, {BLOCK_32X16, BLOCK_32X8}},
};
const static uint8_t Num_4x4_Blocks_Wide[BLOCK_SIZES] = {
	1, 1, 2, 2, 2, 4, 4, 4, 8, 8, 8,
	16, 16, 16, 32, 32, 1, 4, 2, 8, 4, 16};
const static uint8_t Num_4x4_Blocks_High[BLOCK_SIZES] = {
	1, 2, 1, 2, 4, 2, 4, 8, 4, 8, 16,
	8, 16, 32, 16, 32, 4, 1, 8, 2, 16, 4};
const static uint8_t Size_Group[BLOCK_SIZES] = {
	0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3,
	3, 3, 3, 3, 3, 0, 0, 1, 1, 2, 2};

const static uint8_t Mi_Width_Log2[BLOCK_SIZES] = {
	0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
	4, 4, 4, 5, 5, 0, 2, 1, 3, 2, 4};

const static uint8_t Mi_Height_Log2[BLOCK_SIZES] = {
	0, 1, 0, 1, 2, 1, 2, 3, 2, 3, 4,
	3, 4, 5, 4, 5, 2, 0, 3, 1, 4, 2};
const static uint8_t Intra_Mode_Context[INTRA_MODES] = {
	0, 1, 2, 3, 4, 4, 4, 4, 3, 0, 1, 2, 0};
const static uint8_t Ref_Frame_List[REFS_PER_FRAME - 2] = {
	LAST2_FRAME, LAST3_FRAME, BWDREF_FRAME, ALTREF2_FRAME, ALTREF_FRAME};
const static uint16_t Div_Mult[32] = {
	0, 16384, 8192, 5461, 4096, 3276, 2730, 2340, 2048, 1820, 1638,
	1489, 1365, 1260, 1170, 1092, 1024, 963, 910, 862, 819, 780,
	744, 712, 682, 655, 630, 606, 585, 564, 546, 528};
const static uint8_t Palette_Color_Context[PALETTE_MAX_COLOR_CONTEXT_HASH + 1] =
	{-1, -1, 0, -1, -1, 4, 3, 2, 1};
const static uint8_t Partition_Subsize[10][BLOCK_SIZES] = {
	{BLOCK_4X4,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_128X128,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X4,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_128X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_4X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X128,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_4X4,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X4,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_128X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X4,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_128X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_4X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X128,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_4X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X128,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X4,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_32X8,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_64X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID},
	{BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_4X16,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_8X32,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_16X64,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID,
	 BLOCK_INVALID, BLOCK_INVALID, BLOCK_INVALID}};

const static uint8_t Tx_Width[TX_SIZES_ALL] = {
	4, 8, 16, 32, 64, 4, 8, 8, 16, 16, 32, 32, 64, 4, 16, 8, 32, 16, 64};
const static uint8_t Tx_Height[TX_SIZES_ALL] = {
	4, 8, 16, 32, 64, 8, 4, 16, 8, 32, 16, 64, 32, 16, 4, 32, 8, 64, 16};
const static uint8_t Compound_Mode_Ctx_Map[3][COMP_NEWMV_CTXS] = {
	{0, 1, 1, 1, 1},
	{1, 2, 3, 4, 4},
	{4, 4, 5, 6, 7}};
const static uint8_t Wedge_Bits[BLOCK_SIZES] = {
	0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 0,
	0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0};
const static uint8_t Max_Tx_Size_Rect[BLOCK_SIZES] = {
	TX_4X4, TX_4X8, TX_8X4, TX_8X8,
	TX_8X16, TX_16X8, TX_16X16, TX_16X32,
	TX_32X16, TX_32X32, TX_32X64, TX_64X32,
	TX_64X64, TX_64X64, TX_64X64, TX_64X64,
	TX_4X16, TX_16X4, TX_8X32, TX_32X8,
	TX_16X64, TX_64X16};
const static uint8_t Split_Tx_Size[TX_SIZES_ALL] = {
	TX_4X4,
	TX_4X4,
	TX_8X8,
	TX_16X16,
	TX_32X32,
	TX_4X4,
	TX_4X4,
	TX_8X8,
	TX_8X8,
	TX_16X16,
	TX_16X16,
	TX_32X32,
	TX_32X32,
	TX_4X8,
	TX_8X4,
	TX_8X16,
	TX_16X8,
	TX_16X32,
	TX_32X16};
const static uint8_t Max_Tx_Depth[BLOCK_SIZES] = {
	0, 1, 1, 1,
	2, 2, 2, 3,
	3, 3, 4, 4,
	4, 4, 4, 4,
	2, 2, 3, 3,
	4, 4};

const static uint8_t Palette_Color_Hash_Multipliers[PALETTE_NUM_NEIGHBORS] = {1, 2, 2};

const static int8_t Intra_Filter_Taps[INTRA_FILTER_MODES][8][7] = {
	{
		{-6, 10, 0, 0, 0, 12, 0},
		{-5, 2, 10, 0, 0, 9, 0},
		{-3, 1, 1, 10, 0, 7, 0},
		{-3, 1, 1, 2, 10, 5, 0},
		{-4, 6, 0, 0, 0, 2, 12},
		{-3, 2, 6, 0, 0, 2, 9},
		{-3, 2, 2, 6, 0, 2, 7},
		{-3, 1, 2, 2, 6, 3, 5},
	},
	{
		{-10, 16, 0, 0, 0, 10, 0},
		{-6, 0, 16, 0, 0, 6, 0},
		{-4, 0, 0, 16, 0, 4, 0},
		{-2, 0, 0, 0, 16, 2, 0},
		{-10, 16, 0, 0, 0, 0, 10},
		{-6, 0, 16, 0, 0, 0, 6},
		{-4, 0, 0, 16, 0, 0, 4},
		{-2, 0, 0, 0, 16, 0, 2},
	},
	{
		{-8, 8, 0, 0, 0, 16, 0},
		{-8, 0, 8, 0, 0, 16, 0},
		{-8, 0, 0, 8, 0, 16, 0},
		{-8, 0, 0, 0, 8, 16, 0},
		{-4, 4, 0, 0, 0, 0, 16},
		{-4, 0, 4, 0, 0, 0, 16},
		{-4, 0, 0, 4, 0, 0, 16},
		{-4, 0, 0, 0, 4, 0, 16},
	},
	{
		{-2, 8, 0, 0, 0, 10, 0},
		{-1, 3, 8, 0, 0, 6, 0},
		{-1, 2, 3, 8, 0, 4, 0},
		{0, 1, 2, 3, 8, 2, 0},
		{-1, 4, 0, 0, 0, 3, 10},
		{-1, 3, 4, 0, 0, 4, 6},
		{-1, 2, 3, 4, 0, 4, 4},
		{-1, 2, 2, 3, 4, 3, 3},
	},
	{
		{-12, 14, 0, 0, 0, 14, 0},
		{-10, 0, 14, 0, 0, 12, 0},
		{-9, 0, 0, 14, 0, 11, 0},
		{-8, 0, 0, 0, 14, 10, 0},
		{-10, 12, 0, 0, 0, 0, 14},
		{-9, 1, 12, 0, 0, 0, 12},
		{-8, 0, 0, 12, 0, 1, 11},
		{-7, 0, 0, 1, 12, 1, 9},
	}};
const static uint8_t Intra_Edge_Kernel[INTRA_EDGE_KERNELS][INTRA_EDGE_TAPS] = {
	{0, 4, 8, 4, 0},
	{0, 5, 6, 5, 0},
	{2, 4, 4, 4, 2}};
const static uint16_t Div_Table[9] = {
	0, 840, 420, 280, 210, 168, 140, 120, 105};

const static uint8_t Sm_Weights_Tx_4x4[4] = {255, 149, 85, 64};
const static uint8_t Sm_Weights_Tx_8x8[8] = {255, 197, 146, 105, 73, 50, 37, 32};
const static uint8_t Sm_Weights_Tx_16x16[16] = {255, 225, 196, 170, 145, 123, 102, 84, 68, 54, 43, 33, 26, 20,
												17, 16};
const static uint8_t Sm_Weights_Tx_32x32[32] = {255, 240, 225, 210, 196, 182, 169, 157, 145, 133, 122, 111, 101, 92,
												83, 74,
												66, 59, 52, 45, 39, 34, 29, 25, 21, 17, 14, 12, 10, 9,
												8, 8};
const static uint8_t Sm_Weights_Tx_64x64[64] = {255, 248, 240, 233, 225, 218, 210, 203, 196, 189, 182, 176, 169, 163,
												156,
												150, 144, 138, 133, 127, 121, 116, 111, 106, 101, 96, 91, 86, 82, 77,
												73, 69,
												65, 61, 57, 54, 50, 47, 44, 41, 38, 35, 32, 29, 27, 25, 22, 20, 18, 16,
												15,
												13, 12, 10, 9, 8, 7, 6, 6, 5, 5, 4, 4, 4};

const static uint16_t Div_Lut[DIV_LUT_NUM] = {
	16384, 16320, 16257, 16194, 16132, 16070, 16009, 15948, 15888, 15828, 15768,
	15709, 15650, 15592, 15534, 15477, 15420, 15364, 15308, 15252, 15197, 15142,
	15087, 15033, 14980, 14926, 14873, 14821, 14769, 14717, 14665, 14614, 14564,
	14513, 14463, 14413, 14364, 14315, 14266, 14218, 14170, 14122, 14075, 14028,
	13981, 13935, 13888, 13843, 13797, 13752, 13707, 13662, 13618, 13574, 13530,
	13487, 13443, 13400, 13358, 13315, 13273, 13231, 13190, 13148, 13107, 13066,
	13026, 12985, 12945, 12906, 12866, 12827, 12788, 12749, 12710, 12672, 12633,
	12596, 12558, 12520, 12483, 12446, 12409, 12373, 12336, 12300, 12264, 12228,
	12193, 12157, 12122, 12087, 12053, 12018, 11984, 11950, 11916, 11882, 11848,
	11815, 11782, 11749, 11716, 11683, 11651, 11619, 11586, 11555, 11523, 11491,
	11460, 11429, 11398, 11367, 11336, 11305, 11275, 11245, 11215, 11185, 11155,
	11125, 11096, 11067, 11038, 11009, 10980, 10951, 10923, 10894, 10866, 10838,
	10810, 10782, 10755, 10727, 10700, 10673, 10645, 10618, 10592, 10565, 10538,
	10512, 10486, 10460, 10434, 10408, 10382, 10356, 10331, 10305, 10280, 10255,
	10230, 10205, 10180, 10156, 10131, 10107, 10082, 10058, 10034, 10010, 9986,
	9963, 9939, 9916, 9892, 9869, 9846, 9823, 9800, 9777, 9754, 9732,
	9709, 9687, 9664, 9642, 9620, 9598, 9576, 9554, 9533, 9511, 9489,
	9468, 9447, 9425, 9404, 9383, 9362, 9341, 9321, 9300, 9279, 9259,
	9239, 9218, 9198, 9178, 9158, 9138, 9118, 9098, 9079, 9059, 9039,
	9020, 9001, 8981, 8962, 8943, 8924, 8905, 8886, 8867, 8849, 8830,
	8812, 8793, 8775, 8756, 8738, 8720, 8702, 8684, 8666, 8648, 8630,
	8613, 8595, 8577, 8560, 8542, 8525, 8508, 8490, 8473, 8456, 8439,
	8422, 8405, 8389, 8372, 8355, 8339, 8322, 8306, 8289, 8273, 8257,
	8240, 8224, 8208, 8192};
const static int8_t Warped_Filters[WARPEDPIXEL_PREC_SHIFTS * 3 + 1][8] = {
	{0, 0, 127, 1, 0, 0, 0, 0}, {0, -1, 127, 2, 0, 0, 0, 0}, {1, -3, 127, 4, -1, 0, 0, 0}, {1, -4, 126, 6, -2, 1, 0, 0}, {1, -5, 126, 8, -3, 1, 0, 0}, {1, -6, 125, 11, -4, 1, 0, 0}, {1, -7, 124, 13, -4, 1, 0, 0}, {2, -8, 123, 15, -5, 1, 0, 0}, {2, -9, 122, 18, -6, 1, 0, 0}, {2, -10, 121, 20, -6, 1, 0, 0}, {2, -11, 120, 22, -7, 2, 0, 0}, {2, -12, 119, 25, -8, 2, 0, 0}, {3, -13, 117, 27, -8, 2, 0, 0}, {3, -13, 116, 29, -9, 2, 0, 0}, {3, -14, 114, 32, -10, 3, 0, 0}, {3, -15, 113, 35, -10, 2, 0, 0}, {3, -15, 111, 37, -11, 3, 0, 0}, {3, -16, 109, 40, -11, 3, 0, 0}, {3, -16, 108, 42, -12, 3, 0, 0}, {4, -17, 106, 45, -13, 3, 0, 0}, {4, -17, 104, 47, -13, 3, 0, 0}, {4, -17, 102, 50, -14, 3, 0, 0}, {4, -17, 100, 52, -14, 3, 0, 0}, {4, -18, 98, 55, -15, 4, 0, 0}, {4, -18, 96, 58, -15, 3, 0, 0}, {4, -18, 94, 60, -16, 4, 0, 0}, {4, -18, 91, 63, -16, 4, 0, 0}, {4, -18, 89, 65, -16, 4, 0, 0}, {4, -18, 87, 68, -17, 4, 0, 0}, {4, -18, 85, 70, -17, 4, 0, 0}, {4, -18, 82, 73, -17, 4, 0, 0}, {4, -18, 80, 75, -17, 4, 0, 0}, {4, -18, 78, 78, -18, 4, 0, 0}, {4, -17, 75, 80, -18, 4, 0, 0}, {4, -17, 73, 82, -18, 4, 0, 0}, {4, -17, 70, 85, -18, 4, 0, 0}, {4, -17, 68, 87, -18, 4, 0, 0}, {4, -16, 65, 89, -18, 4, 0, 0}, {4, -16, 63, 91, -18, 4, 0, 0}, {4, -16, 60, 94, -18, 4, 0, 0}, {3, -15, 58, 96, -18, 4, 0, 0}, {4, -15, 55, 98, -18, 4, 0, 0}, {3, -14, 52, 100, -17, 4, 0, 0}, {3, -14, 50, 102, -17, 4, 0, 0}, {3, -13, 47, 104, -17, 4, 0, 0}, {3, -13, 45, 106, -17, 4, 0, 0}, {3, -12, 42, 108, -16, 3, 0, 0}, {3, -11, 40, 109, -16, 3, 0, 0}, {3, -11, 37, 111, -15, 3, 0, 0}, {2, -10, 35, 113, -15, 3, 0, 0}, {3, -10, 32, 114, -14, 3, 0, 0}, {2, -9, 29, 116, -13, 3, 0, 0}, {2, -8, 27, 117, -13, 3, 0, 0}, {2, -8, 25, 119, -12, 2, 0, 0}, {2, -7, 22, 120, -11, 2, 0, 0}, {1, -6, 20, 121, -10, 2, 0, 0}, {1, -6, 18, 122, -9, 2, 0, 0}, {1, -5, 15, 123, -8, 2, 0, 0}, {1, -4, 13, 124, -7, 1, 0, 0}, {1, -4, 11, 125, -6, 1, 0, 0}, {1, -3, 8, 126, -5, 1, 0, 0}, {1, -2, 6, 126, -4, 1, 0, 0}, {0, -1, 4, 127, -3, 1, 0, 0}, {0, 0, 2, 127, -1, 0, 0, 0}, {0, 0, 0, 127, 1, 0, 0, 0}, {0, 0, -1, 127, 2, 0, 0, 0}, {0, 1, -3, 127, 4, -2, 1, 0}, {0, 1, -5, 127, 6, -2, 1, 0}, {0, 2, -6, 126, 8, -3, 1, 0}, {-1, 2, -7, 126, 11, -4, 2, -1}, {-1, 3, -8, 125, 13, -5, 2, -1}, {-1, 3, -10, 124, 16, -6, 3, -1}, {-1, 4, -11, 123, 18, -7, 3, -1}, {-1, 4, -12, 122, 20, -7, 3, -1}, {-1, 4, -13, 121, 23, -8, 3, -1}, {-2, 5, -14, 120, 25, -9, 4, -1}, {-1, 5, -15, 119, 27, -10, 4, -1}, {-1, 5, -16, 118, 30, -11, 4, -1}, {-2, 6, -17, 116, 33, -12, 5, -1}, {-2, 6, -17, 114, 35, -12, 5, -1}, {-2, 6, -18, 113, 38, -13, 5, -1}, {-2, 7, -19, 111, 41, -14, 6, -2}, {-2, 7, -19, 110, 43, -15, 6, -2}, {-2, 7, -20, 108, 46, -15, 6, -2}, {-2, 7, -20, 106, 49, -16, 6, -2}, {-2, 7, -21, 104, 51, -16, 7, -2}, {-2, 7, -21, 102, 54, -17, 7, -2}, {-2, 8, -21, 100, 56, -18, 7, -2}, {-2, 8, -22, 98, 59, -18, 7, -2}, {-2, 8, -22, 96, 62, -19, 7, -2}, {-2, 8, -22, 94, 64, -19, 7, -2}, {-2, 8, -22, 91, 67, -20, 8, -2}, {-2, 8, -22, 89, 69, -20, 8, -2}, {-2, 8, -22, 87, 72, -21, 8, -2}, {-2, 8, -21, 84, 74, -21, 8, -2}, {-2, 8, -22, 82, 77, -21, 8, -2}, {-2, 8, -21, 79, 79, -21, 8, -2}, {-2, 8, -21, 77, 82, -22, 8, -2}, {-2, 8, -21, 74, 84, -21, 8, -2}, {-2, 8, -21, 72, 87, -22, 8, -2}, {-2, 8, -20, 69, 89, -22, 8, -2}, {-2, 8, -20, 67, 91, -22, 8, -2}, {-2, 7, -19, 64, 94, -22, 8, -2}, {-2, 7, -19, 62, 96, -22, 8, -2}, {-2, 7, -18, 59, 98, -22, 8, -2}, {-2, 7, -18, 56, 100, -21, 8, -2}, {-2, 7, -17, 54, 102, -21, 7, -2}, {-2, 7, -16, 51, 104, -21, 7, -2}, {-2, 6, -16, 49, 106, -20, 7, -2}, {-2, 6, -15, 46, 108, -20, 7, -2}, {-2, 6, -15, 43, 110, -19, 7, -2}, {-2, 6, -14, 41, 111, -19, 7, -2}, {-1, 5, -13, 38, 113, -18, 6, -2}, {-1, 5, -12, 35, 114, -17, 6, -2}, {-1, 5, -12, 33, 116, -17, 6, -2}, {-1, 4, -11, 30, 118, -16, 5, -1}, {-1, 4, -10, 27, 119, -15, 5, -1}, {-1, 4, -9, 25, 120, -14, 5, -2}, {-1, 3, -8, 23, 121, -13, 4, -1}, {-1, 3, -7, 20, 122, -12, 4, -1}, {-1, 3, -7, 18, 123, -11, 4, -1}, {-1, 3, -6, 16, 124, -10, 3, -1}, {-1, 2, -5, 13, 125, -8, 3, -1}, {-1, 2, -4, 11, 126, -7, 2, -1}, {0, 1, -3, 8, 126, -6, 2, 0}, {0, 1, -2, 6, 127, -5, 1, 0}, {0, 1, -2, 4, 127, -3, 1, 0}, {0, 0, 0, 2, 127, -1, 0, 0}, {0, 0, 0, 1, 127, 0, 0, 0}, {0, 0, 0, -1, 127, 2, 0, 0}, {0, 0, 1, -3, 127, 4, -1, 0}, {0, 0, 1, -4, 126, 6, -2, 1}, {0, 0, 1, -5, 126, 8, -3, 1}, {0, 0, 1, -6, 125, 11, -4, 1}, {0, 0, 1, -7, 124, 13, -4, 1}, {0, 0, 2, -8, 123, 15, -5, 1}, {0, 0, 2, -9, 122, 18, -6, 1}, {0, 0, 2, -10, 121, 20, -6, 1}, {0, 0, 2, -11, 120, 22, -7, 2}, {0, 0, 2, -12, 119, 25, -8, 2}, {0, 0, 3, -13, 117, 27, -8, 2}, {0, 0, 3, -13, 116, 29, -9, 2}, {0, 0, 3, -14, 114, 32, -10, 3}, {0, 0, 3, -15, 113, 35, -10, 2}, {0, 0, 3, -15, 111, 37, -11, 3}, {0, 0, 3, -16, 109, 40, -11, 3}, {0, 0, 3, -16, 108, 42, -12, 3}, {0, 0, 4, -17, 106, 45, -13, 3}, {0, 0, 4, -17, 104, 47, -13, 3}, {0, 0, 4, -17, 102, 50, -14, 3}, {0, 0, 4, -17, 100, 52, -14, 3}, {0, 0, 4, -18, 98, 55, -15, 4}, {0, 0, 4, -18, 96, 58, -15, 3}, {0, 0, 4, -18, 94, 60, -16, 4}, {0, 0, 4, -18, 91, 63, -16, 4}, {0, 0, 4, -18, 89, 65, -16, 4}, {0, 0, 4, -18, 87, 68, -17, 4}, {0, 0, 4, -18, 85, 70, -17, 4}, {0, 0, 4, -18, 82, 73, -17, 4}, {0, 0, 4, -18, 80, 75, -17, 4}, {0, 0, 4, -18, 78, 78, -18, 4}, {0, 0, 4, -17, 75, 80, -18, 4}, {0, 0, 4, -17, 73, 82, -18, 4}, {0, 0, 4, -17, 70, 85, -18, 4}, {0, 0, 4, -17, 68, 87, -18, 4}, {0, 0, 4, -16, 65, 89, -18, 4}, {0, 0, 4, -16, 63, 91, -18, 4}, {0, 0, 4, -16, 60, 94, -18, 4}, {0, 0, 3, -15, 58, 96, -18, 4}, {0, 0, 4, -15, 55, 98, -18, 4}, {0, 0, 3, -14, 52, 100, -17, 4}, {0, 0, 3, -14, 50, 102, -17, 4}, {0, 0, 3, -13, 47, 104, -17, 4}, {0, 0, 3, -13, 45, 106, -17, 4}, {0, 0, 3, -12, 42, 108, -16, 3}, {0, 0, 3, -11, 40, 109, -16, 3}, {0, 0, 3, -11, 37, 111, -15, 3}, {0, 0, 2, -10, 35, 113, -15, 3}, {0, 0, 3, -10, 32, 114, -14, 3}, {0, 0, 2, -9, 29, 116, -13, 3}, {0, 0, 2, -8, 27, 117, -13, 3}, {0, 0, 2, -8, 25, 119, -12, 2}, {0, 0, 2, -7, 22, 120, -11, 2}, {0, 0, 1, -6, 20, 121, -10, 2}, {0, 0, 1, -6, 18, 122, -9, 2}, {0, 0, 1, -5, 15, 123, -8, 2}, {0, 0, 1, -4, 13, 124, -7, 1}, {0, 0, 1, -4, 11, 125, -6, 1}, {0, 0, 1, -3, 8, 126, -5, 1}, {0, 0, 1, -2, 6, 126, -4, 1}, {0, 0, 0, -1, 4, 127, -3, 1}, {0, 0, 0, 0, 2, 127, -1, 0}, {0, 0, 0, 0, 2, 127, -1, 0}};
const static int8_t Subpel_Filters[6][16][8] = {
	{{0, 0, 0, 128, 0, 0, 0, 0},
	 {0, 2, -6, 126, 8, -2, 0, 0},
	 {0, 2, -10, 122, 18, -4, 0, 0},
	 {0, 2, -12, 116, 28, -8, 2, 0},
	 {0, 2, -14, 110, 38, -10, 2, 0},
	 {0, 2, -14, 102, 48, -12, 2, 0},
	 {0, 2, -16, 94, 58, -12, 2, 0},
	 {0, 2, -14, 84, 66, -12, 2, 0},
	 {0, 2, -14, 76, 76, -14, 2, 0},
	 {0, 2, -12, 66, 84, -14, 2, 0},
	 {0, 2, -12, 58, 94, -16, 2, 0},
	 {0, 2, -12, 48, 102, -14, 2, 0},
	 {0, 2, -10, 38, 110, -14, 2, 0},
	 {0, 2, -8, 28, 116, -12, 2, 0},
	 {0, 0, -4, 18, 122, -10, 2, 0},
	 {0, 0, -2, 8, 126, -6, 2, 0}},
	{{0, 0, 0, 128, 0, 0, 0, 0},
	 {0, 2, 28, 62, 34, 2, 0, 0},
	 {0, 0, 26, 62, 36, 4, 0, 0},
	 {0, 0, 22, 62, 40, 4, 0, 0},
	 {0, 0, 20, 60, 42, 6, 0, 0},
	 {0, 0, 18, 58, 44, 8, 0, 0},
	 {0, 0, 16, 56, 46, 10, 0, 0},
	 {0, -2, 16, 54, 48, 12, 0, 0},
	 {0, -2, 14, 52, 52, 14, -2, 0},
	 {0, 0, 12, 48, 54, 16, -2, 0},
	 {0, 0, 10, 46, 56, 16, 0, 0},
	 {0, 0, 8, 44, 58, 18, 0, 0},
	 {0, 0, 6, 42, 60, 20, 0, 0},
	 {0, 0, 4, 40, 62, 22, 0, 0},
	 {0, 0, 4, 36, 62, 26, 0, 0},
	 {0, 0, 2, 34, 62, 28, 2, 0}},
	{{0, 0, 0, 128, 0, 0, 0, 0},
	 {-2, 2, -6, 126, 8, -2, 2, 0},
	 {-2, 6, -12, 124, 16, -6, 4, -2},
	 {-2, 8, -18, 120, 26, -10, 6, -2},
	 {-4, 10, -22, 116, 38, -14, 6, -2},
	 {-4, 10, -22, 108, 48, -18, 8, -2},
	 {-4, 10, -24, 100, 60, -20, 8, -2},
	 {-4, 10, -24, 90, 70, -22, 10, -2},
	 {-4, 12, -24, 80, 80, -24, 12, -4},
	 {-2, 10, -22, 70, 90, -24, 10, -4},
	 {-2, 8, -20, 60, 100, -24, 10, -4},
	 {-2, 8, -18, 48, 108, -22, 10, -4},

	 {-2, 6, -14, 38, 116, -22, 10, -4},
	 {-2, 6, -10, 26, 120, -18, 8, -2},
	 {-2, 4, -6, 16, 124, -12, 6, -2},
	 {0, 2, -2, 8, 126, -6, 2, -2}},
	{{0, 0, 0, 128, 0, 0, 0, 0},
	 {0, 0, 0, 120, 8, 0, 0, 0},
	 {0, 0, 0, 112, 16, 0, 0, 0},
	 {0, 0, 0, 104, 24, 0, 0, 0},
	 {0, 0, 0, 96, 32, 0, 0, 0},
	 {0, 0, 0, 88, 40, 0, 0, 0},
	 {0, 0, 0, 80, 48, 0, 0, 0},
	 {0, 0, 0, 72, 56, 0, 0, 0},
	 {0, 0, 0, 64, 64, 0, 0, 0},
	 {0, 0, 0, 56, 72, 0, 0, 0},
	 {0, 0, 0, 48, 80, 0, 0, 0},
	 {0, 0, 0, 40, 88, 0, 0, 0},
	 {0, 0, 0, 32, 96, 0, 0, 0},
	 {0, 0, 0, 24, 104, 0, 0, 0},
	 {0, 0, 0, 16, 112, 0, 0, 0},
	 {0, 0, 0, 8, 120, 0, 0, 0}},
	{{0, 0, 0, 128, 0, 0, 0, 0},
	 {0, 0, -4, 126, 8, -2, 0, 0},
	 {0, 0, -8, 122, 18, -4, 0, 0},
	 {0, 0, -10, 116, 28, -6, 0, 0},
	 {0, 0, -12, 110, 38, -8, 0, 0},
	 {0, 0, -12, 102, 48, -10, 0, 0},
	 {0, 0, -14, 94, 58, -10, 0, 0},
	 {0, 0, -12, 84, 66, -10, 0, 0},
	 {0, 0, -12, 76, 76, -12, 0, 0},
	 {0, 0, -10, 66, 84, -12, 0, 0},
	 {0, 0, -10, 58, 94, -14, 0, 0},
	 {0, 0, -10, 48, 102, -12, 0, 0},
	 {0, 0, -8, 38, 110, -12, 0, 0},
	 {0, 0, -6, 28, 116, -10, 0, 0},
	 {0, 0, -4, 18, 122, -8, 0, 0},
	 {0, 0, -2, 8, 126, -4, 0, 0}},
	{{0, 0, 0, 128, 0, 0, 0, 0},
	 {0, 0, 30, 62, 34, 2, 0, 0},
	 {0, 0, 26, 62, 36, 4, 0, 0},
	 {0, 0, 22, 62, 40, 4, 0, 0},
	 {0, 0, 20, 60, 42, 6, 0, 0},
	 {0, 0, 18, 58, 44, 8, 0, 0},
	 {0, 0, 16, 56, 46, 10, 0, 0},
	 {0, 0, 14, 54, 48, 12, 0, 0},

	 {0, 0, 12, 52, 52, 12, 0, 0},
	 {0, 0, 12, 48, 54, 14, 0, 0},
	 {0, 0, 10, 46, 56, 16, 0, 0},
	 {0, 0, 8, 44, 58, 18, 0, 0},
	 {0, 0, 6, 42, 60, 20, 0, 0},
	 {0, 0, 4, 40, 62, 22, 0, 0},
	 {0, 0, 4, 36, 62, 26, 0, 0},
	 {0, 0, 2, 34, 62, 30, 0, 0}}};

const static uint8_t Wedge_Codebook[3][16][3] = {
	{
		{WEDGE_OBLIQUE27, 4, 4},
		{WEDGE_OBLIQUE63, 4, 4},
		{WEDGE_OBLIQUE117, 4, 4},
		{WEDGE_OBLIQUE153, 4, 4},
		{WEDGE_HORIZONTAL, 4, 2},
		{WEDGE_HORIZONTAL, 4, 4},
		{WEDGE_HORIZONTAL, 4, 6},
		{WEDGE_VERTICAL, 4, 4},
		{WEDGE_OBLIQUE27, 4, 2},
		{WEDGE_OBLIQUE27, 4, 6},
		{WEDGE_OBLIQUE153, 4, 2},
		{WEDGE_OBLIQUE153, 4, 6},
		{WEDGE_OBLIQUE63, 2, 4},
		{WEDGE_OBLIQUE63, 6, 4},
		{WEDGE_OBLIQUE117, 2, 4},
		{WEDGE_OBLIQUE117, 6, 4},
	},
	{
		{WEDGE_OBLIQUE27, 4, 4},
		{WEDGE_OBLIQUE63, 4, 4},
		{WEDGE_OBLIQUE117, 4, 4},
		{WEDGE_OBLIQUE153, 4, 4},
		{WEDGE_VERTICAL, 2, 4},
		{WEDGE_VERTICAL, 4, 4},
		{WEDGE_VERTICAL, 6, 4},
		{WEDGE_HORIZONTAL, 4, 4},
		{WEDGE_OBLIQUE27, 4, 2},
		{WEDGE_OBLIQUE27, 4, 6},
		{WEDGE_OBLIQUE153, 4, 2},
		{WEDGE_OBLIQUE153, 4, 6},
		{WEDGE_OBLIQUE63, 2, 4},
		{WEDGE_OBLIQUE63, 6, 4},
		{WEDGE_OBLIQUE117, 2, 4},
		{WEDGE_OBLIQUE117, 6, 4},
	},
	{
		{WEDGE_OBLIQUE27, 4, 4},
		{WEDGE_OBLIQUE63, 4, 4},
		{WEDGE_OBLIQUE117, 4, 4},
		{WEDGE_OBLIQUE153, 4, 4},
		{WEDGE_HORIZONTAL, 4, 2},
		{WEDGE_HORIZONTAL, 4, 6},
		{WEDGE_VERTICAL, 2, 4},
		{WEDGE_VERTICAL, 6, 4},
		{WEDGE_OBLIQUE27, 4, 2},
		{WEDGE_OBLIQUE27, 4, 6},

		{WEDGE_OBLIQUE153, 4, 2},
		{WEDGE_OBLIQUE153, 4, 6},
		{WEDGE_OBLIQUE63, 2, 4},
		{WEDGE_OBLIQUE63, 6, 4},
		{WEDGE_OBLIQUE117, 2, 4},
		{WEDGE_OBLIQUE117, 6, 4},
	}};
const static uint8_t Wedge_Master_Oblique_Odd[MASK_MASTER_SIZE] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 18,
	37, 53, 60, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};
const static uint8_t Wedge_Master_Oblique_Even[MASK_MASTER_SIZE] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 11, 27,
	46, 58, 62, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};
const static uint8_t Wedge_Master_Vertical[MASK_MASTER_SIZE] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 7, 21,
	43, 57, 62, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};

const static uint8_t Ii_Weights_1d[MAX_SB_SIZE] = {
	60, 58, 56, 54, 52, 50, 48, 47, 45, 44, 42, 41, 39, 38, 37, 35, 34, 33, 32,
	31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 22, 21, 20, 19, 19, 18, 18, 17, 16,
	16, 15, 15, 14, 14, 13, 13, 12, 12, 12, 11, 11, 10, 10, 10, 9, 9, 9, 8,
	8, 8, 8, 7, 7, 7, 7, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 4, 4,
	4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const static uint8_t Quant_Dist_Weight[4][2] = {
	{2, 3}, {2, 5}, {2, 7}, {1, MAX_FRAME_DISTANCE}};
const static uint8_t Quant_Dist_Lookup[4][2] = {
	{9, 7}, {11, 5}, {12, 4}, {13, 3}};
const static uint8_t Obmc_Mask_2[2] = {45, 64};
const static uint8_t Obmc_Mask_4[4] = {39, 50, 59, 64};
const static uint8_t Obmc_Mask_8[8] = {36, 42, 48, 53, 57, 61, 64, 64};
const static uint8_t Obmc_Mask_16[16] = {34, 37, 40, 43, 46, 49, 52, 54,
										 56, 58, 60, 61, 64, 64, 64, 64};
const static uint8_t Obmc_Mask_32[32] = {33, 35, 36, 38, 40, 41, 43, 44,
										 45, 47, 48, 50, 51, 52, 53, 55,
										 56, 57, 58, 59, 60, 60, 61, 62,
										 64, 64, 64, 64, 64, 64, 64, 64};
const static uint16_t Dc_Qlookup[3][256] = {
	{4, 8, 8, 9, 10, 11, 12, 12, 13, 14, 15, 16,
	 17, 18, 19, 19, 20, 21, 22, 23, 24, 25, 26, 26,
	 27, 28, 29, 30, 31, 32, 32, 33, 34, 35, 36, 37,
	 38, 38, 39, 40, 41, 42, 43, 43, 44, 45, 46, 47,
	 48, 48, 49, 50, 51, 52, 53, 53, 54, 55, 56, 57,
	 57, 58, 59, 60, 61, 62, 62, 63, 64, 65, 66, 66,
	 67, 68, 69, 70, 70, 71, 72, 73, 74, 74, 75, 76,
	 77, 78, 78, 79, 80, 81, 81, 82, 83, 84, 85, 85,
	 87, 88, 90, 92, 93, 95, 96, 98, 99, 101, 102, 104,
	 105, 107, 108, 110, 111, 113, 114, 116, 117, 118, 120, 121,
	 123, 125, 127, 129, 131, 134, 136, 138, 140, 142, 144, 146,
	 148, 150, 152, 154, 156, 158, 161, 164, 166, 169, 172, 174,
	 177, 180, 182, 185, 187, 190, 192, 195, 199, 202, 205, 208,
	 211, 214, 217, 220, 223, 226, 230, 233, 237, 240, 243, 247,
	 250, 253, 257, 261, 265, 269, 272, 276, 280, 284, 288, 292,
	 296, 300, 304, 309, 313, 317, 322, 326, 330, 335, 340, 344,
	 349, 354, 359, 364, 369, 374, 379, 384, 389, 395, 400, 406,
	 411, 417, 423, 429, 435, 441, 447, 454, 461, 467, 475, 482,
	 489, 497, 505, 513, 522, 530, 539, 549, 559, 569, 579, 590,
	 602, 614, 626, 640, 654, 668, 684, 700, 717, 736, 755, 775,
	 796, 819, 843, 869, 896, 925, 955, 988, 1022, 1058, 1098, 1139,
	 1184, 1232, 1282, 1336},
	{4, 9, 10, 13, 15, 17, 20, 22, 25, 28, 31, 34,
	 37, 40, 43, 47, 50, 53, 57, 60, 64, 68, 71, 75,
	 78, 82, 86, 90, 93, 97, 101, 105, 109, 113, 116, 120,
	 124, 128, 132, 136, 140, 143, 147, 151, 155, 159, 163, 166,
	 170, 174, 178, 182, 185, 189, 193, 197, 200, 204, 208, 212,
	 215, 219, 223, 226, 230, 233, 237, 241, 244, 248, 251, 255,
	 259, 262, 266, 269, 273, 276, 280, 283, 287, 290, 293, 297,
	 300, 304, 307, 310, 314, 317, 321, 324, 327, 331, 334, 337,
	 343, 350, 356, 362, 369, 375, 381, 387, 394, 400, 406, 412,
	 418, 424, 430, 436, 442, 448, 454, 460, 466, 472, 478, 484,
	 490, 499, 507, 516, 525, 533, 542, 550, 559, 567, 576, 584,
	 592, 601, 609, 617, 625, 634, 644, 655, 666, 676, 687, 698,
	 708, 718, 729, 739, 749, 759, 770, 782, 795, 807, 819, 831,
	 844, 856, 868, 880, 891, 906, 920, 933, 947, 961, 975, 988,
	 1001, 1015, 1030, 1045, 1061, 1076, 1090, 1105, 1120, 1137, 1153, 1170,
	 1186, 1202, 1218, 1236, 1253, 1271, 1288, 1306, 1323, 1342, 1361, 1379,
	 1398, 1416, 1436, 1456, 1476, 1496, 1516, 1537, 1559, 1580, 1601, 1624,
	 1647, 1670, 1692, 1717, 1741, 1766, 1791, 1817, 1844, 1871, 1900, 1929,
	 1958, 1990, 2021, 2054, 2088, 2123, 2159, 2197, 2236, 2276, 2319, 2363,
	 2410, 2458, 2508, 2561, 2616, 2675, 2737, 2802, 2871, 2944, 3020, 3102,
	 3188, 3280, 3375, 3478, 3586, 3702, 3823, 3953, 4089, 4236, 4394, 4559,
	 4737, 4929, 5130, 5347},
	{4, 12, 18, 25, 33, 41, 50, 60,
	 70, 80, 91, 103, 115, 127, 140, 153,
	 166, 180, 194, 208, 222, 237, 251, 266,
	 281, 296, 312, 327, 343, 358, 374, 390,
	 405, 421, 437, 453, 469, 484, 500, 516,
	 532, 548, 564, 580, 596, 611, 627, 643,
	 659, 674, 690, 706, 721, 737, 752, 768,
	 783, 798, 814, 829, 844, 859, 874, 889,
	 904, 919, 934, 949, 964, 978, 993, 1008,
	 1022, 1037, 1051, 1065, 1080, 1094, 1108, 1122,
	 1136, 1151, 1165, 1179, 1192, 1206, 1220, 1234,
	 1248, 1261, 1275, 1288, 1302, 1315, 1329, 1342,
	 1368, 1393, 1419, 1444, 1469, 1494, 1519, 1544,
	 1569, 1594, 1618, 1643, 1668, 1692, 1717, 1741,
	 1765, 1789, 1814, 1838, 1862, 1885, 1909, 1933,
	 1957, 1992, 2027, 2061, 2096, 2130, 2165, 2199,
	 2233, 2267, 2300, 2334, 2367, 2400, 2434, 2467,
	 2499, 2532, 2575, 2618, 2661, 2704, 2746, 2788,
	 2830, 2872, 2913, 2954, 2995, 3036, 3076, 3127,
	 3177, 3226, 3275, 3324, 3373, 3421, 3469, 3517,
	 3565, 3621, 3677, 3733, 3788, 3843, 3897, 3951,
	 4005, 4058, 4119, 4181, 4241, 4301, 4361, 4420,
	 4479, 4546, 4612, 4677, 4742, 4807, 4871, 4942,
	 5013, 5083, 5153, 5222, 5291, 5367, 5442, 5517,
	 5591, 5665, 5745, 5825, 5905, 5984, 6063, 6149,
	 6234, 6319, 6404, 6495, 6587, 6678, 6769, 6867,
	 6966, 7064, 7163, 7269, 7376, 7483, 7599, 7715,
	 7832, 7958, 8085, 8214, 8352, 8492, 8635, 8788,
	 8945, 9104, 9275, 9450, 9639, 9832, 10031, 10245,
	 10465, 10702, 10946, 11210, 11482, 11776, 12081, 12409,
	 12750, 13118, 13501, 13913, 14343, 14807, 15290, 15812,
	 16356, 16943, 17575, 18237, 18949, 19718, 20521, 21387}};
const static uint16_t Ac_Qlookup[3][256] = {
	{4, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
	 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66,
	 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
	 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
	 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
	 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126,
	 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150,
	 152, 155, 158, 161, 164, 167, 170, 173, 176, 179, 182, 185,
	 188, 191, 194, 197, 200, 203, 207, 211, 215, 219, 223, 227,
	 231, 235, 239, 243, 247, 251, 255, 260, 265, 270, 275, 280,
	 285, 290, 295, 300, 305, 311, 317, 323, 329, 335, 341, 347,
	 353, 359, 366, 373, 380, 387, 394, 401, 408, 416, 424, 432,
	 440, 448, 456, 465, 474, 483, 492, 501, 510, 520, 530, 540,
	 550, 560, 571, 582, 593, 604, 615, 627, 639, 651, 663, 676,
	 689, 702, 715, 729, 743, 757, 771, 786, 801, 816, 832, 848,
	 864, 881, 898, 915, 933, 951, 969, 988, 1007, 1026, 1046, 1066,
	 1087, 1108, 1129, 1151, 1173, 1196, 1219, 1243, 1267, 1292, 1317, 1343,
	 1369, 1396, 1423, 1451, 1479, 1508, 1537, 1567, 1597, 1628, 1660, 1692,
	 1725, 1759, 1793, 1828},
	{4, 9, 11, 13, 16, 18, 21, 24, 27, 30, 33, 37,
	 40, 44, 48, 51, 55, 59, 63, 67, 71, 75, 79, 83,
	 88, 92, 96, 100, 105, 109, 114, 118, 122, 127, 131, 136,
	 140, 145, 149, 154, 158, 163, 168, 172, 177, 181, 186, 190,
	 195, 199, 204, 208, 213, 217, 222, 226, 231, 235, 240, 244,
	 249, 253, 258, 262, 267, 271, 275, 280, 284, 289, 293, 297,
	 302, 306, 311, 315, 319, 324, 328, 332, 337, 341, 345, 349,
	 354, 358, 362, 367, 371, 375, 379, 384, 388, 392, 396, 401,
	 409, 417, 425, 433, 441, 449, 458, 466, 474, 482, 490, 498,
	 506, 514, 523, 531, 539, 547, 555, 563, 571, 579, 588, 596,
	 604, 616, 628, 640, 652, 664, 676, 688, 700, 713, 725, 737,
	 749, 761, 773, 785, 797, 809, 825, 841, 857, 873, 889, 905,
	 922, 938, 954, 970, 986, 1002, 1018, 1038, 1058, 1078, 1098, 1118,
	 1138, 1158, 1178, 1198, 1218, 1242, 1266, 1290, 1314, 1338, 1362, 1386,
	 1411, 1435, 1463, 1491, 1519, 1547, 1575, 1603, 1631, 1663, 1695, 1727,
	 1759, 1791, 1823, 1859, 1895, 1931, 1967, 2003, 2039, 2079, 2119, 2159,
	 2199, 2239, 2283, 2327, 2371, 2415, 2459, 2507, 2555, 2603, 2651, 2703,
	 2755, 2807, 2859, 2915, 2971, 3027, 3083, 3143, 3203, 3263, 3327, 3391,
	 3455, 3523, 3591, 3659, 3731, 3803, 3876, 3952, 4028, 4104, 4184, 4264,
	 4348, 4432, 4516, 4604, 4692, 4784, 4876, 4972, 5068, 5168, 5268, 5372,
	 5476, 5584, 5692, 5804, 5916, 6032, 6148, 6268, 6388, 6512, 6640, 6768,
	 6900, 7036, 7172, 7312},
	{

		4, 13, 19, 27, 35, 44, 54, 64,
		75, 87, 99, 112, 126, 139, 154, 168,
		183, 199, 214, 230, 247, 263, 280, 297,
		314, 331, 349, 366, 384, 402, 420, 438,
		456, 475, 493, 511, 530, 548, 567, 586,
		604, 623, 642, 660, 679, 698, 716, 735,
		753, 772, 791, 809, 828, 846, 865, 884,
		902, 920, 939, 957, 976, 994, 1012, 1030,
		1049, 1067, 1085, 1103, 1121, 1139, 1157, 1175,
		1193, 1211, 1229, 1246, 1264, 1282, 1299, 1317,
		1335, 1352, 1370, 1387, 1405, 1422, 1440, 1457,
		1474, 1491, 1509, 1526, 1543, 1560, 1577, 1595,
		1627, 1660, 1693, 1725, 1758, 1791, 1824, 1856,
		1889, 1922, 1954, 1987, 2020, 2052, 2085, 2118,
		2150, 2183, 2216, 2248, 2281, 2313, 2346, 2378,
		2411, 2459, 2508, 2556, 2605, 2653, 2701, 2750,
		2798, 2847, 2895, 2943, 2992, 3040, 3088, 3137,
		3185, 3234, 3298, 3362, 3426, 3491, 3555, 3619,
		3684, 3748, 3812, 3876, 3941, 4005, 4069, 4149,
		4230, 4310, 4390, 4470, 4550, 4631, 4711, 4791,
		4871, 4967, 5064, 5160, 5256, 5352, 5448, 5544,
		5641, 5737, 5849, 5961, 6073, 6185, 6297, 6410,
		6522, 6650, 6778, 6906, 7034, 7162, 7290, 7435,
		7579, 7723, 7867, 8011, 8155, 8315, 8475, 8635,
		8795, 8956, 9132, 9308, 9484, 9660, 9836, 10028,
		10220, 10412, 10604, 10812, 11020, 11228, 11437, 11661,
		11885, 12109, 12333, 12573, 12813, 13053, 13309, 13565,
		13821, 14093, 14365, 14637, 14925, 15213, 15502, 15806,
		16110, 16414, 16734, 17054, 17390, 17726, 18062, 18414,
		18766, 19134, 19502, 19886, 20270, 20670, 21070, 21486,
		21902, 22334, 22766, 23214, 23662, 24126, 24590, 25070,
		25551, 26047, 26559, 27071, 27599, 28143, 28687, 29247}};

const static uint16_t Cos128_Lookup[65] = {
	4096, 4095, 4091, 4085, 4076, 4065, 4052, 4036,
	4017, 3996, 3973, 3948, 3920, 3889, 3857, 3822,
	3784, 3745, 3703, 3659, 3612, 3564, 3513, 3461,
	3406, 3349, 3290, 3229, 3166, 3102, 3035, 2967,
	2896, 2824, 2751, 2675, 2598, 2520, 2440, 2359,
	2276, 2191, 2106, 2019, 1931, 1842, 1751, 1660,
	1567, 1474, 1380, 1285, 1189, 1092, 995, 897,
	799, 700, 601, 501, 401, 301, 201, 101, 0};
const static uint8_t Transform_Row_Shift[TX_SIZES_ALL] = {
	0, 1, 2, 2, 2, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 2, 2, 2, 2};
const static uint8_t Cdef_Uv_Dir[2][2][8] = {
	{{0, 1, 2, 3, 4, 5, 6, 7},
	 {1, 2, 2, 2, 3, 4, 6, 0}},
	{{7, 0, 2, 4, 5, 6, 6, 6},
	 {0, 1, 2, 3, 4, 5, 6, 7}}};
const static uint8_t Cdef_Pri_Taps[2][2] = {
	{4, 2}, {3, 3}};
const static uint8_t Cdef_Sec_Taps[2][2] = {
	{2, 1}, {2, 1}};

const static int8_t Cdef_Directions[8][2][2] = {
	{{-1, 1}, {-2, 2}},
	{{0, 1}, {-1, 2}},
	{{0, 1}, {0, 2}},
	{{0, 1}, {1, 2}},
	{{1, 1}, {2, 2}},
	{{1, 0}, {2, 1}},
	{{1, 0}, {2, 0}},
	{{1, 0}, {2, -1}}};
const static int8_t Upscale_Filter[SUPERRES_FILTER_SHIFTS][SUPERRES_FILTER_TAPS] = {
	{0, 0, 0, 128, 0, 0, 0, 0},
	{0, 0, -1, 128, 2, -1, 0, 0},
	{0, 1, -3, 127, 4, -2, 1, 0},
	{0, 1, -4, 127, 6, -3, 1, 0},
	{0, 2, -6, 126, 8, -3, 1, 0},
	{0, 2, -7, 125, 11, -4, 1, 0},
	{-1, 2, -8, 125, 13, -5, 2, 0},
	{-1, 3, -9, 124, 15, -6, 2, 0},
	{-1, 3, -10, 123, 18, -6, 2, -1},
	{-1, 3, -11, 122, 20, -7, 3, -1},
	{-1, 4, -12, 121, 22, -8, 3, -1},
	{-1, 4, -13, 120, 25, -9, 3, -1},
	{-1, 4, -14, 118, 28, -9, 3, -1},
	{-1, 4, -15, 117, 30, -10, 4, -1},
	{-1, 5, -16, 116, 32, -11, 4, -1},
	{-1, 5, -16, 114, 35, -12, 4, -1},
	{-1, 5, -17, 112, 38, -12, 4, -1},
	{-1, 5, -18, 111, 40, -13, 5, -1},
	{-1, 5, -18, 109, 43, -14, 5, -1},
	{-1, 6, -19, 107, 45, -14, 5, -1},
	{-1, 6, -19, 105, 48, -15, 5, -1},
	{-1, 6, -19, 103, 51, -16, 5, -1},
	{-1, 6, -20, 101, 53, -16, 6, -1},
	{-1, 6, -20, 99, 56, -17, 6, -1},
	{-1, 6, -20, 97, 58, -17, 6, -1},
	{-1, 6, -20, 95, 61, -18, 6, -1},
	{-2, 7, -20, 93, 64, -18, 6, -2},
	{-2, 7, -20, 91, 66, -19, 6, -1},
	{-2, 7, -20, 88, 69, -19, 6, -1},
	{-2, 7, -20, 86, 71, -19, 6, -1},
	{-2, 7, -20, 84, 74, -20, 7, -2},
	{-2, 7, -20, 81, 76, -20, 7, -1},
	{-2, 7, -20, 79, 79, -20, 7, -2},
	{-1, 7, -20, 76, 81, -20, 7, -2},
	{-2, 7, -20, 74, 84, -20, 7, -2},
	{-1, 6, -19, 71, 86, -20, 7, -2},
	{-1, 6, -19, 69, 88, -20, 7, -2},
	{-1, 6, -19, 66, 91, -20, 7, -2},
	{-2, 6, -18, 64, 93, -20, 7, -2},
	{-1, 6, -18, 61, 95, -20, 6, -1},
	{-1, 6, -17, 58, 97, -20, 6, -1},
	{-1, 6, -17, 56, 99, -20, 6, -1},
	{-1, 6, -16, 53, 101, -20, 6, -1},
	{-1, 5, -16, 51, 103, -19, 6, -1},
	{-1, 5, -15, 48, 105, -19, 6, -1},
	{-1, 5, -14, 45, 107, -19, 6, -1},
	{-1, 5, -14, 43, 109, -18, 5, -1},
	{-1, 5, -13, 40, 111, -18, 5, -1},
	{-1, 4, -12, 38, 112, -17, 5, -1},
	{-1, 4, -12, 35, 114, -16, 5, -1},
	{-1, 4, -11, 32, 116, -16, 5, -1},
	{-1, 4, -10, 30, 117, -15, 4, -1},
	{-1, 3, -9, 28, 118, -14, 4, -1},
	{-1, 3, -9, 25, 120, -13, 4, -1},
	{-1, 3, -8, 22, 121, -12, 4, -1},
	{-1, 3, -7, 20, 122, -11, 3, -1},
	{-1, 2, -6, 18, 123, -10, 3, -1},
	{0, 2, -6, 15, 124, -9, 3, -1},
	{0, 2, -5, 13, 125, -8, 2, -1},
	{0, 1, -4, 11, 125, -7, 2, 0},
	{0, 1, -3, 8, 126, -6, 2, 0},
	{0, 1, -3, 6, 127, -4, 1, 0},
	{0, 1, -2, 4, 127, -3, 1, 0},
	{0, 0, -1, 2, 128, -1, 0, 0},
};

const static uint8_t Sgr_Params[(1 << SGRPROJ_PARAMS_BITS)][4] = {
	{2, 12, 1, 4}, {2, 15, 1, 6}, {2, 18, 1, 8}, {2, 21, 1, 9}, {2, 24, 1, 10}, {2, 29, 1, 11}, {2, 36, 1, 12}, {2, 45, 1, 13}, {2, 56, 1, 14}, {2, 68, 1, 15}, {0, 0, 1, 5}, {0, 0, 1, 8}, {0, 0, 1, 11}, {0, 0, 1, 14}, {2, 30, 0, 0}, {2, 75, 0, 0}};
const static uint8_t Tx_Width_Log2[TX_SIZES_ALL] = {
	2, 3, 4, 5, 6, 2, 3, 3, 4, 4, 5, 5, 6, 2, 4, 3, 5, 4, 6};

const static uint8_t Tx_Height_Log2[TX_SIZES_ALL] = {
	2, 3, 4, 5, 6, 3, 2, 4, 3, 5, 4, 6, 5, 4, 2, 5, 3, 6, 4};
const static uint8_t Tx_Size_Sqr[TX_SIZES_ALL] = {
	TX_4X4,
	TX_8X8,
	TX_16X16,
	TX_32X32,
	TX_64X64,
	TX_4X4,
	TX_4X4,
	TX_8X8,
	TX_8X8,
	TX_16X16,
	TX_16X16,
	TX_32X32,
	TX_32X32,
	TX_4X4,
	TX_4X4,
	TX_8X8,
	TX_8X8,
	TX_16X16,
	TX_16X16};
const static uint8_t Tx_Size_Sqr_Up[TX_SIZES_ALL] = {
	TX_4X4,
	TX_8X8,
	TX_16X16,
	TX_32X32,
	TX_64X64,
	TX_8X8,
	TX_8X8,
	TX_16X16,
	TX_16X16,
	TX_32X32,
	TX_32X32,
	TX_64X64,
	TX_64X64,
	TX_16X16,
	TX_16X16,
	TX_32X32,
	TX_32X32,
	TX_64X64,
	TX_64X64};
const static uint8_t Tx_Type_In_Set_Intra[TX_SET_TYPES_INTRA][TX_TYPES] = {
	{
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
	{
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
	},
	{
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
	}};
const static uint8_t Tx_Type_In_Set_Inter[TX_SET_TYPES_INTER][TX_TYPES] = {
	{
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
	{
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
	},
	{
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
	},
	{
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
	}};

const static uint16_t Default_Scan_4x4[16] = {
	0, 1, 4, 8,
	5, 2, 3, 6,
	9, 12, 13, 10,
	7, 11, 14, 15};
const static uint16_t Mcol_Scan_4x4[16] = {
	0, 4, 8, 12,
	1, 5, 9, 13,
	2, 6, 10, 14,
	3, 7, 11, 15};
const static uint16_t Mrow_Scan_4x4[16] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15};
const static uint16_t Default_Scan_4x8[32] = {
	0, 1, 4, 2, 5, 8, 3, 6, 9, 12, 7, 10, 13, 16, 11, 14,
	17, 20, 15, 18, 21, 24, 19, 22, 25, 28, 23, 26, 29, 27, 30, 31};
const static uint16_t Mcol_Scan_4x8[32] = {
	0, 4, 8, 12, 16, 20, 24, 28, 1, 5, 9, 13, 17, 21, 25, 29,
	2, 6, 10, 14, 18, 22, 26, 30, 3, 7, 11, 15, 19, 23, 27, 31};
const static uint16_t Mrow_Scan_4x8[32] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
const static uint16_t Default_Scan_8x4[32] = {
	0, 8, 1, 16, 9, 2, 24, 17, 10, 3, 25, 18, 11, 4, 26, 19,
	12, 5, 27, 20, 13, 6, 28, 21, 14, 7, 29, 22, 15, 30, 23, 31};
const static uint16_t Mcol_Scan_8x4[32] = {
	0, 8, 16, 24, 1, 9, 17, 25, 2, 10, 18, 26, 3, 11, 19, 27,
	4, 12, 20, 28, 5, 13, 21, 29, 6, 14, 22, 30, 7, 15, 23, 31};
const static uint16_t Mrow_Scan_8x4[32] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
const static uint16_t Default_Scan_8x8[64] = {
	0, 1, 8, 16, 9, 2, 3, 10,
	17, 24, 32, 25, 18, 11, 4, 5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13, 6, 7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63};
const static uint16_t Mcol_Scan_8x8[64] = {
	0, 8, 16, 24, 32, 40, 48, 56,
	1, 9, 17, 25, 33, 41, 49, 57,
	2, 10, 18, 26, 34, 42, 50, 58,
	3, 11, 19, 27, 35, 43, 51, 59,
	4, 12, 20, 28, 36, 44, 52, 60,
	5, 13, 21, 29, 37, 45, 53, 61,
	6, 14, 22, 30, 38, 46, 54, 62,
	7, 15, 23, 31, 39, 47, 55, 63};
const static uint16_t Mrow_Scan_8x8[64] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63};
const static uint16_t Default_Scan_8x16[128] = {
	0, 1, 8, 2, 9, 16, 3, 10, 17, 24, 4, 11, 18, 25, 32,
	5, 12, 19, 26, 33, 40, 6, 13, 20, 27, 34, 41, 48, 7, 14,
	21, 28, 35, 42, 49, 56, 15, 22, 29, 36, 43, 50, 57, 64, 23,
	30, 37, 44, 51, 58, 65, 72, 31, 38, 45, 52, 59, 66, 73, 80,
	39, 46, 53, 60, 67, 74, 81, 88, 47, 54, 61, 68, 75, 82, 89,
	96, 55, 62, 69, 76, 83, 90, 97, 104, 63, 70, 77, 84, 91, 98,
	105, 112, 71, 78, 85, 92, 99, 106, 113, 120, 79, 86, 93, 100, 107,
	114, 121, 87, 94, 101, 108, 115, 122, 95, 102, 109, 116, 123, 103, 110,
	117, 124, 111, 118, 125, 119, 126, 127};
const static uint16_t Mcol_Scan_8x16[128] = {
	0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120,
	1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105, 113, 121,
	2, 10, 18, 26, 34, 42, 50, 58, 66, 74, 82, 90, 98, 106, 114, 122,
	3, 11, 19, 27, 35, 43, 51, 59, 67, 75, 83, 91, 99, 107, 115, 123,
	4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84, 92, 100, 108, 116, 124,
	5, 13, 21, 29, 37, 45, 53, 61, 69, 77, 85, 93, 101, 109, 117, 125,
	6, 14, 22, 30, 38, 46, 54, 62, 70, 78, 86, 94, 102, 110, 118, 126,
	7, 15, 23, 31, 39, 47, 55, 63, 71, 79, 87, 95, 103, 111, 119, 127};
const static uint16_t Mrow_Scan_8x16[128] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104,
	105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, 123, 124, 125, 126, 127};
const static uint16_t Default_Scan_16x8[128] = {
	0, 16, 1, 32, 17, 2, 48, 33, 18, 3, 64, 49, 34, 19, 4, 80,
	65, 50, 35, 20, 5, 96, 81, 66, 51, 36, 21, 6, 112, 97, 82, 67,
	52, 37, 22, 7, 113, 98, 83, 68, 53, 38, 23, 8, 114, 99, 84, 69,
	54, 39, 24, 9, 115, 100, 85, 70, 55, 40, 25, 10, 116, 101, 86, 71,
	56, 41, 26, 11, 117, 102, 87, 72, 57, 42, 27, 12, 118, 103, 88, 73,
	58, 43, 28, 13, 119, 104, 89, 74, 59, 44, 29, 14, 120, 105, 90, 75,
	60, 45, 30, 15, 121, 106, 91, 76, 61, 46, 31, 122, 107, 92, 77, 62,
	47, 123, 108, 93, 78, 63, 124, 109, 94, 79, 125, 110, 95, 126, 111, 127};
const static uint16_t Mcol_Scan_16x8[128] = {
	0, 16, 32, 48, 64, 80, 96, 112, 1, 17, 33, 49, 65, 81, 97, 113,
	2, 18, 34, 50, 66, 82, 98, 114, 3, 19, 35, 51, 67, 83, 99, 115,
	4, 20, 36, 52, 68, 84, 100, 116, 5, 21, 37, 53, 69, 85, 101, 117,
	6, 22, 38, 54, 70, 86, 102, 118, 7, 23, 39, 55, 71, 87, 103, 119,
	8, 24, 40, 56, 72, 88, 104, 120, 9, 25, 41, 57, 73, 89, 105, 121,
	10, 26, 42, 58, 74, 90, 106, 122, 11, 27, 43, 59, 75, 91, 107, 123,
	12, 28, 44, 60, 76, 92, 108, 124, 13, 29, 45, 61, 77, 93, 109, 125,
	14, 30, 46, 62, 78, 94, 110, 126, 15, 31, 47, 63, 79, 95, 111, 127};
const static uint16_t Mrow_Scan_16x8[128] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104,
	105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, 123, 124, 125, 126, 127};
const static uint16_t Default_Scan_16x16[256] = {
	0, 1, 16, 32, 17, 2, 3, 18, 33, 48, 64, 49, 34, 19, 4, 5,
	20, 35, 50, 65, 80, 96, 81, 66, 51, 36, 21, 6, 7, 22, 37, 52,
	67, 82, 97, 112, 128, 113, 98, 83, 68, 53, 38, 23, 8, 9, 24, 39,
	54, 69, 84, 99, 114, 129, 144, 160, 145, 130, 115, 100, 85, 70, 55, 40,
	25, 10, 11, 26, 41, 56, 71, 86, 101, 116, 131, 146, 161, 176, 192, 177,
	162, 147, 132, 117, 102, 87, 72, 57, 42, 27, 12, 13, 28, 43, 58, 73,
	88, 103, 118, 133, 148, 163, 178, 193, 208, 224, 209, 194, 179, 164, 149, 134,
	119, 104, 89, 74, 59, 44, 29, 14, 15, 30, 45, 60, 75, 90, 105, 120,
	135, 150, 165, 180, 195, 210, 225, 240, 241, 226, 211, 196, 181, 166, 151, 136,
	121, 106, 91, 76, 61, 46, 31, 47, 62, 77, 92, 107, 122, 137, 152, 167,
	182, 197, 212, 227, 242, 243, 228, 213, 198, 183, 168, 153, 138, 123, 108, 93,
	78, 63, 79, 94, 109, 124, 139, 154, 169, 184, 199, 214, 229, 244, 245, 230,
	215, 200, 185, 170, 155, 140, 125, 110, 95, 111, 126, 141, 156, 171, 186, 201,
	216, 231, 246, 247, 232, 217, 202, 187, 172, 157, 142, 127, 143, 158, 173, 188,
	203, 218, 233, 248, 249, 234, 219, 204, 189, 174, 159, 175, 190, 205, 220, 235,
	250, 251, 236, 221, 206, 191, 207, 222, 237, 252, 253, 238, 223, 239, 254, 255};
const static uint16_t Mcol_Scan_16x16[256] = {
	0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240,
	1, 17, 33, 49, 65, 81, 97, 113, 129, 145, 161, 177, 193, 209, 225, 241,
	2, 18, 34, 50, 66, 82, 98, 114, 130, 146, 162, 178, 194, 210, 226, 242,
	3, 19, 35, 51, 67, 83, 99, 115, 131, 147, 163, 179, 195, 211, 227, 243,
	4, 20, 36, 52, 68, 84, 100, 116, 132, 148, 164, 180, 196, 212, 228, 244,
	5, 21, 37, 53, 69, 85, 101, 117, 133, 149, 165, 181, 197, 213, 229, 245,
	6, 22, 38, 54, 70, 86, 102, 118, 134, 150, 166, 182, 198, 214, 230, 246,
	7, 23, 39, 55, 71, 87, 103, 119, 135, 151, 167, 183, 199, 215, 231, 247,
	8, 24, 40, 56, 72, 88, 104, 120, 136, 152, 168, 184, 200, 216, 232, 248,
	9, 25, 41, 57, 73, 89, 105, 121, 137, 153, 169, 185, 201, 217, 233, 249,
	10, 26, 42, 58, 74, 90, 106, 122, 138, 154, 170, 186, 202, 218, 234, 250,
	11, 27, 43, 59, 75, 91, 107, 123, 139, 155, 171, 187, 203, 219, 235, 251,
	12, 28, 44, 60, 76, 92, 108, 124, 140, 156, 172, 188, 204, 220, 236, 252,
	13, 29, 45, 61, 77, 93, 109, 125, 141, 157, 173, 189, 205, 221, 237, 253,
	14, 30, 46, 62, 78, 94, 110, 126, 142, 158, 174, 190, 206, 222, 238, 254,
	15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239, 255};
const static uint16_t Mrow_Scan_16x16[256] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104,
	105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
	135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
	150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
	165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
	180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
	195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
	210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
	225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
	240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
	255};
const static uint16_t Default_Scan_16x32[512] = {
	0, 1, 16, 2, 17, 32, 3, 18, 33, 48, 4, 19, 34, 49, 64,
	5, 20, 35, 50, 65, 80, 6, 21, 36, 51, 66, 81, 96, 7, 22,
	37, 52, 67, 82, 97, 112, 8, 23, 38, 53, 68, 83, 98, 113, 128,
	9, 24, 39, 54, 69, 84, 99, 114, 129, 144, 10, 25, 40, 55, 70,
	85, 100, 115, 130, 145, 160, 11, 26, 41, 56, 71, 86, 101, 116, 131,
	146, 161, 176, 12, 27, 42, 57, 72, 87, 102, 117, 132, 147, 162, 177,
	192, 13, 28, 43, 58, 73, 88, 103, 118, 133, 148, 163, 178, 193, 208,
	14, 29, 44, 59, 74, 89, 104, 119, 134, 149, 164, 179, 194, 209, 224,
	15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225,
	240, 31, 46, 61, 76, 91, 106, 121, 136, 151, 166, 181, 196, 211, 226,
	241, 256, 47, 62, 77, 92, 107, 122, 137, 152, 167, 182, 197, 212, 227,
	242, 257, 272, 63, 78, 93, 108, 123, 138, 153, 168, 183, 198, 213, 228,
	243, 258, 273, 288, 79, 94, 109, 124, 139, 154, 169, 184, 199, 214, 229,
	244, 259, 274, 289, 304, 95, 110, 125, 140, 155, 170, 185, 200, 215, 230,
	245, 260, 275, 290, 305, 320, 111, 126, 141, 156, 171, 186, 201, 216, 231,
	246, 261, 276, 291, 306, 321, 336, 127, 142, 157, 172, 187, 202, 217, 232,
	247, 262, 277, 292, 307, 322, 337, 352, 143, 158, 173, 188, 203, 218, 233,
	248, 263, 278, 293, 308, 323, 338, 353, 368, 159, 174, 189, 204, 219, 234,
	249, 264, 279, 294, 309, 324, 339, 354, 369, 384, 175, 190, 205, 220, 235,
	250, 265, 280, 295, 310, 325, 340, 355, 370, 385, 400, 191, 206, 221, 236,
	251, 266, 281, 296, 311, 326, 341, 356, 371, 386, 401, 416, 207, 222, 237,
	252, 267, 282, 297, 312, 327, 342, 357, 372, 387, 402, 417, 432, 223, 238,
	253, 268, 283, 298, 313, 328, 343, 358, 373, 388, 403, 418, 433, 448, 239,
	254, 269, 284, 299, 314, 329, 344, 359, 374, 389, 404, 419, 434, 449, 464,
	255, 270, 285, 300, 315, 330, 345, 360, 375, 390, 405, 420, 435, 450, 465,
	480, 271, 286, 301, 316, 331, 346, 361, 376, 391, 406, 421, 436, 451, 466,
	481, 496, 287, 302, 317, 332, 347, 362, 377, 392, 407, 422, 437, 452, 467,
	482, 497, 303, 318, 333, 348, 363, 378, 393, 408, 423, 438, 453, 468, 483,
	498, 319, 334, 349, 364, 379, 394, 409, 424, 439, 454, 469, 484, 499, 335,
	350, 365, 380, 395, 410, 425, 440, 455, 470, 485, 500, 351, 366, 381, 396,
	411, 426, 441, 456, 471, 486, 501, 367, 382, 397, 412, 427, 442, 457, 472,
	487, 502, 383, 398, 413, 428, 443, 458, 473, 488, 503, 399, 414, 429, 444,
	459, 474, 489, 504, 415, 430, 445, 460, 475, 490, 505, 431, 446, 461, 476,
	491, 506, 447, 462, 477, 492, 507, 463, 478, 493, 508, 479, 494, 509, 495,
	510, 511};
const static uint16_t Default_Scan_32x16[512] = {
	0, 32, 1, 64, 33, 2, 96, 65, 34, 3, 128, 97, 66, 35, 4,
	160, 129, 98, 67, 36, 5, 192, 161, 130, 99, 68, 37, 6, 224, 193,
	162, 131, 100, 69, 38, 7, 256, 225, 194, 163, 132, 101, 70, 39, 8,
	288, 257, 226, 195, 164, 133, 102, 71, 40, 9, 320, 289, 258, 227, 196,
	165, 134, 103, 72, 41, 10, 352, 321, 290, 259, 228, 197, 166, 135, 104,
	73, 42, 11, 384, 353, 322, 291, 260, 229, 198, 167, 136, 105, 74, 43,
	12, 416, 385, 354, 323, 292, 261, 230, 199, 168, 137, 106, 75, 44, 13,
	448, 417, 386, 355, 324, 293, 262, 231, 200, 169, 138, 107, 76, 45, 14,
	480, 449, 418, 387, 356, 325, 294, 263, 232, 201, 170, 139, 108, 77, 46,
	15, 481, 450, 419, 388, 357, 326, 295, 264, 233, 202, 171, 140, 109, 78,
	47, 16, 482, 451, 420, 389, 358, 327, 296, 265, 234, 203, 172, 141, 110,
	79, 48, 17, 483, 452, 421, 390, 359, 328, 297, 266, 235, 204, 173, 142,
	111, 80, 49, 18, 484, 453, 422, 391, 360, 329, 298, 267, 236, 205, 174,
	143, 112, 81, 50, 19, 485, 454, 423, 392, 361, 330, 299, 268, 237, 206,
	175, 144, 113, 82, 51, 20, 486, 455, 424, 393, 362, 331, 300, 269, 238,
	207, 176, 145, 114, 83, 52, 21, 487, 456, 425, 394, 363, 332, 301, 270,
	239, 208, 177, 146, 115, 84, 53, 22, 488, 457, 426, 395, 364, 333, 302,
	271, 240, 209, 178, 147, 116, 85, 54, 23, 489, 458, 427, 396, 365, 334,
	303, 272, 241, 210, 179, 148, 117, 86, 55, 24, 490, 459, 428, 397, 366,
	335, 304, 273, 242, 211, 180, 149, 118, 87, 56, 25, 491, 460, 429, 398,
	367, 336, 305, 274, 243, 212, 181, 150, 119, 88, 57, 26, 492, 461, 430,
	399, 368, 337, 306, 275, 244, 213, 182, 151, 120, 89, 58, 27, 493, 462,
	431, 400, 369, 338, 307, 276, 245, 214, 183, 152, 121, 90, 59, 28, 494,
	463, 432, 401, 370, 339, 308, 277, 246, 215, 184, 153, 122, 91, 60, 29,
	495, 464, 433, 402, 371, 340, 309, 278, 247, 216, 185, 154, 123, 92, 61,
	30, 496, 465, 434, 403, 372, 341, 310, 279, 248, 217, 186, 155, 124, 93,
	62, 31, 497, 466, 435, 404, 373, 342, 311, 280, 249, 218, 187, 156, 125,
	94, 63, 498, 467, 436, 405, 374, 343, 312, 281, 250, 219, 188, 157, 126,
	95, 499, 468, 437, 406, 375, 344, 313, 282, 251, 220, 189, 158, 127, 500,
	469, 438, 407, 376, 345, 314, 283, 252, 221, 190, 159, 501, 470, 439, 408,
	377, 346, 315, 284, 253, 222, 191, 502, 471, 440, 409, 378, 347, 316, 285,
	254, 223, 503, 472, 441, 410, 379, 348, 317, 286, 255, 504, 473, 442, 411,
	380, 349, 318, 287, 505, 474, 443, 412, 381, 350, 319, 506, 475, 444, 413,
	382, 351, 507, 476, 445, 414, 383, 508, 477, 446, 415, 509, 478, 447, 510,
	479, 511};

const static uint16_t Default_Scan_32x32[1024] = {
	0, 1, 32, 64, 33, 2, 3, 34, 65, 96, 128, 97, 66,
	35, 4, 5, 36, 67, 98, 129, 160, 192, 161, 130, 99, 68,
	37, 6, 7, 38, 69, 100, 131, 162, 193, 224, 256, 225, 194,
	163, 132, 101, 70, 39, 8, 9, 40, 71, 102, 133, 164, 195,
	226, 257, 288, 320, 289, 258, 227, 196, 165, 134, 103, 72, 41,
	10, 11, 42, 73, 104, 135, 166, 197, 228, 259, 290, 321, 352,
	384, 353, 322, 291, 260, 229, 198, 167, 136, 105, 74, 43, 12,
	13, 44, 75, 106, 137, 168, 199, 230, 261, 292, 323, 354, 385,
	416, 448, 417, 386, 355, 324, 293, 262, 231, 200, 169, 138, 107,
	76, 45, 14, 15, 46, 77, 108, 139, 170, 201, 232, 263, 294,
	325, 356, 387, 418, 449, 480, 512, 481, 450, 419, 388, 357, 326,
	295, 264, 233, 202, 171, 140, 109, 78, 47, 16, 17, 48, 79,
	110, 141, 172, 203, 234, 265, 296, 327, 358, 389, 420, 451, 482,
	513, 544, 576, 545, 514, 483, 452, 421, 390, 359, 328, 297, 266,
	235, 204, 173, 142, 111, 80, 49, 18, 19, 50, 81, 112, 143,
	174, 205, 236, 267, 298, 329, 360, 391, 422, 453, 484, 515, 546,
	577, 608, 640, 609, 578, 547, 516, 485, 454, 423, 392, 361, 330,
	299, 268, 237, 206, 175, 144, 113, 82, 51, 20, 21, 52, 83,
	114, 145, 176, 207, 238, 269, 300, 331, 362, 393, 424, 455, 486,
	517, 548, 579, 610, 641, 672, 704, 673, 642, 611, 580, 549, 518,
	487, 456, 425, 394, 363, 332, 301, 270, 239, 208, 177, 146, 115,
	84, 53, 22, 23, 54, 85, 116, 147, 178, 209, 240, 271, 302,
	333, 364, 395, 426, 457, 488, 519, 550, 581, 612, 643, 674, 705,
	736, 768, 737, 706, 675, 644, 613, 582, 551, 520, 489, 458, 427,
	396, 365, 334, 303, 272, 241, 210, 179, 148, 117, 86, 55, 24,
	25, 56, 87, 118, 149, 180, 211, 242, 273, 304, 335, 366, 397,
	428, 459, 490, 521, 552, 583, 614, 645, 676, 707, 738, 769, 800,
	832, 801, 770, 739, 708, 677, 646, 615, 584, 553, 522, 491, 460,
	429, 398, 367, 336, 305, 274, 243, 212, 181, 150, 119, 88, 57,
	26, 27, 58, 89, 120, 151, 182, 213, 244, 275, 306, 337, 368,
	399, 430, 461, 492, 523, 554, 585, 616, 647, 678, 709, 740, 771,
	802, 833, 864, 896, 865, 834, 803, 772, 741, 710, 679, 648, 617,
	586, 555, 524, 493, 462, 431, 400, 369, 338, 307, 276, 245, 214,
	183, 152, 121, 90, 59, 28, 29, 60, 91, 122, 153, 184, 215,
	246, 277, 308, 339, 370, 401, 432, 463, 494, 525, 556, 587, 618,
	649, 680, 711, 742, 773, 804, 835, 866, 897, 928, 960, 929, 898,
	867, 836, 805, 774, 743, 712, 681, 650, 619, 588, 557, 526, 495,
	464, 433, 402, 371, 340, 309, 278, 247, 216, 185, 154, 123, 92,
	61, 30, 31, 62, 93, 124, 155, 186, 217, 248, 279, 310, 341,
	372, 403, 434, 465, 496, 527, 558, 589, 620, 651, 682, 713, 744,
	775, 806, 837, 868, 899, 930, 961, 992, 993, 962, 931, 900, 869,
	838, 807, 776, 745, 714, 683, 652, 621, 590, 559, 528, 497, 466,
	435, 404, 373, 342, 311, 280, 249, 218, 187, 156, 125, 94, 63,
	95, 126, 157, 188, 219, 250, 281, 312, 343, 374, 405, 436, 467,
	498, 529, 560, 591, 622, 653, 684, 715, 746, 777, 808, 839, 870,
	901, 932, 963, 994, 995, 964, 933, 902, 871, 840, 809, 778, 747,
	716, 685, 654, 623, 592, 561, 530, 499, 468, 437, 406, 375, 344,
	313, 282, 251, 220, 189, 158, 127, 159, 190, 221, 252, 283, 314,
	345, 376, 407, 438, 469, 500, 531, 562, 593, 624, 655, 686, 717,
	748, 779, 810, 841, 872, 903, 934, 965, 996, 997, 966, 935, 904,
	873, 842, 811, 780, 749, 718, 687, 656, 625, 594, 563, 532, 501,
	470, 439, 408, 377, 346, 315, 284, 253, 222, 191, 223, 254, 285,
	316, 347, 378, 409, 440, 471, 502, 533, 564, 595, 626, 657, 688,
	719, 750, 781, 812, 843, 874, 905, 936, 967, 998, 999, 968, 937,
	906, 875, 844, 813, 782, 751, 720, 689, 658, 627, 596, 565, 534,
	503, 472, 441, 410, 379, 348, 317, 286, 255, 287, 318, 349, 380,
	411, 442, 473, 504, 535, 566, 597, 628, 659, 690, 721, 752, 783,
	814, 845, 876, 907, 938, 969, 1000, 1001, 970, 939, 908, 877, 846,
	815, 784, 753, 722, 691, 660, 629, 598, 567, 536, 505, 474, 443,
	412, 381, 350, 319, 351, 382, 413, 444, 475, 506, 537, 568, 599,
	630, 661, 692, 723, 754, 785, 816, 847, 878, 909, 940, 971, 1002,
	1003, 972, 941, 910, 879, 848, 817, 786, 755, 724, 693, 662, 631,
	600, 569, 538, 507, 476, 445, 414, 383, 415, 446, 477, 508, 539,
	570, 601, 632, 663, 694, 725, 756, 787, 818, 849, 880, 911, 942,
	973, 1004, 1005, 974, 943, 912, 881, 850, 819, 788, 757, 726, 695,
	664, 633, 602, 571, 540, 509, 478, 447, 479, 510, 541, 572, 603,
	634, 665, 696, 727, 758, 789, 820, 851, 882, 913, 944, 975, 1006,
	1007, 976, 945, 914, 883, 852, 821, 790, 759, 728, 697, 666, 635,
	604, 573, 542, 511, 543, 574, 605, 636, 667, 698, 729, 760, 791,
	822, 853, 884, 915, 946, 977, 1008, 1009, 978, 947, 916, 885, 854,
	823, 792, 761, 730, 699, 668, 637, 606, 575, 607, 638, 669, 700,
	731, 762, 793, 824, 855, 886, 917, 948, 979, 1010, 1011, 980, 949,
	918, 887, 856, 825, 794, 763, 732, 701, 670, 639, 671, 702, 733,
	764, 795, 826, 857, 888, 919, 950, 981, 1012, 1013, 982, 951, 920,
	889, 858, 827, 796, 765, 734, 703, 735, 766, 797, 828, 859, 890,
	921, 952, 983, 1014, 1015, 984, 953, 922, 891, 860, 829, 798, 767,
	799, 830, 861, 892, 923, 954, 985, 1016, 1017, 986, 955, 924, 893,
	862, 831, 863, 894, 925, 956, 987, 1018, 1019, 988, 957, 926, 895,
	927, 958, 989, 1020, 1021, 990, 959, 991, 1022, 1023};
const static uint16_t Default_Scan_4x16[64] = {
	0, 1, 4, 2, 5, 8, 3, 6, 9, 12, 7, 10, 13, 16, 11, 14,
	17, 20, 15, 18, 21, 24, 19, 22, 25, 28, 23, 26, 29, 32, 27, 30,
	33, 36, 31, 34, 37, 40, 35, 38, 41, 44, 39, 42, 45, 48, 43, 46,
	49, 52, 47, 50, 53, 56, 51, 54, 57, 60, 55, 58, 61, 59, 62, 63};
const static uint16_t Mcol_Scan_4x16[64] = {
	0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
	1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61,
	2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62,
	3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63};

const static uint16_t Mrow_Scan_4x16[64] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
const static uint16_t Default_Scan_16x4[64] = {
	0, 16, 1, 32, 17, 2, 48, 33, 18, 3, 49, 34, 19, 4, 50, 35,
	20, 5, 51, 36, 21, 6, 52, 37, 22, 7, 53, 38, 23, 8, 54, 39,
	24, 9, 55, 40, 25, 10, 56, 41, 26, 11, 57, 42, 27, 12, 58, 43,
	28, 13, 59, 44, 29, 14, 60, 45, 30, 15, 61, 46, 31, 62, 47, 63};
const static uint16_t Mcol_Scan_16x4[64] = {
	0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,
	4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,
	8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,
	12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63};
const static uint16_t Mrow_Scan_16x4[64] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

const static uint16_t Default_Scan_8x32[256] = {
	0, 1, 8, 2, 9, 16, 3, 10, 17, 24, 4, 11, 18, 25, 32,
	5, 12, 19, 26, 33, 40, 6, 13, 20, 27, 34, 41, 48, 7, 14,
	21, 28, 35, 42, 49, 56, 15, 22, 29, 36, 43, 50, 57, 64, 23,
	30, 37, 44, 51, 58, 65, 72, 31, 38, 45, 52, 59, 66, 73, 80,
	39, 46, 53, 60, 67, 74, 81, 88, 47, 54, 61, 68, 75, 82, 89,
	96, 55, 62, 69, 76, 83, 90, 97, 104, 63, 70, 77, 84, 91, 98,
	105, 112, 71, 78, 85, 92, 99, 106, 113, 120, 79, 86, 93, 100, 107,
	114, 121, 128, 87, 94, 101, 108, 115, 122, 129, 136, 95, 102, 109, 116,
	123, 130, 137, 144, 103, 110, 117, 124, 131, 138, 145, 152, 111, 118, 125,
	132, 139, 146, 153, 160, 119, 126, 133, 140, 147, 154, 161, 168, 127, 134,
	141, 148, 155, 162, 169, 176, 135, 142, 149, 156, 163, 170, 177, 184, 143,
	150, 157, 164, 171, 178, 185, 192, 151, 158, 165, 172, 179, 186, 193, 200,
	159, 166, 173, 180, 187, 194, 201, 208, 167, 174, 181, 188, 195, 202, 209,
	216, 175, 182, 189, 196, 203, 210, 217, 224, 183, 190, 197, 204, 211, 218,
	225, 232, 191, 198, 205, 212, 219, 226, 233, 240, 199, 206, 213, 220, 227,
	234, 241, 248, 207, 214, 221, 228, 235, 242, 249, 215, 222, 229, 236, 243,
	250, 223, 230, 237, 244, 251, 231, 238, 245, 252, 239, 246, 253, 247, 254,
	255};
const static uint16_t Default_Scan_32x8[256] = {
	0, 32, 1, 64, 33, 2, 96, 65, 34, 3, 128, 97, 66, 35, 4,
	160, 129, 98, 67, 36, 5, 192, 161, 130, 99, 68, 37, 6, 224, 193,
	162, 131, 100, 69, 38, 7, 225, 194, 163, 132, 101, 70, 39, 8, 226,
	195, 164, 133, 102, 71, 40, 9, 227, 196, 165, 134, 103, 72, 41, 10,
	228, 197, 166, 135, 104, 73, 42, 11, 229, 198, 167, 136, 105, 74, 43,
	12, 230, 199, 168, 137, 106, 75, 44, 13, 231, 200, 169, 138, 107, 76,
	45, 14, 232, 201, 170, 139, 108, 77, 46, 15, 233, 202, 171, 140, 109,
	78, 47, 16, 234, 203, 172, 141, 110, 79, 48, 17, 235, 204, 173, 142,
	111, 80, 49, 18, 236, 205, 174, 143, 112, 81, 50, 19, 237, 206, 175,
	144, 113, 82, 51, 20, 238, 207, 176, 145, 114, 83, 52, 21, 239, 208,
	177, 146, 115, 84, 53, 22, 240, 209, 178, 147, 116, 85, 54, 23, 241,
	210, 179, 148, 117, 86, 55, 24, 242, 211, 180, 149, 118, 87, 56, 25,
	243, 212, 181, 150, 119, 88, 57, 26, 244, 213, 182, 151, 120, 89, 58,
	27, 245, 214, 183, 152, 121, 90, 59, 28, 246, 215, 184, 153, 122, 91,
	60, 29, 247, 216, 185, 154, 123, 92, 61, 30, 248, 217, 186, 155, 124,
	93, 62, 31, 249, 218, 187, 156, 125, 94, 63, 250, 219, 188, 157, 126,
	95, 251, 220, 189, 158, 127, 252, 221, 190, 159, 253, 222, 191, 254, 223,
	255};
const static uint8_t Coeff_Base_Pos_Ctx_Offset[3] = {
	SIG_COEF_CONTEXTS_2D,
	SIG_COEF_CONTEXTS_2D + 5,
	SIG_COEF_CONTEXTS_2D + 10};
const static uint8_t Mode_To_Txfm[UV_INTRA_MODES_CFL_ALLOWED] = {
	DCT_DCT,   // DC_PRED
	ADST_DCT,  // V_PRED
	DCT_ADST,  // H_PRED
	DCT_DCT,   // D45_PRED
	ADST_ADST, // D135_PRED
	ADST_DCT,  // D113_PRED
	DCT_ADST,  // D157_PRED
	DCT_ADST,  // D203_PRED
	ADST_DCT,  // D67_PRED
	ADST_ADST, // SMOOTH_PRED
	ADST_DCT,  // SMOOTH_V_PRED
	DCT_ADST,  // SMOOTH_H_PRED
	ADST_ADST, // PAETH_PRED
	DCT_DCT,   // UV_CFL_PRED
};
const static uint8_t Sig_Ref_Diff_Offset[3][SIG_REF_DIFF_OFFSET_NUM][2] = {
	{{0, 1}, {1, 0}, {1, 1}, {0, 2}, {2, 0}},
	{{0, 1}, {1, 0}, {0, 2}, {0, 3}, {0, 4}},
	{{0, 1}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}};

const static uint8_t Adjusted_Tx_Size[TX_SIZES_ALL] = {
	TX_4X4,
	TX_8X8,
	TX_16X16,
	TX_32X32,
	TX_32X32,
	TX_4X8,
	TX_8X4,
	TX_8X16,
	TX_16X8,
	TX_16X32,
	TX_32X16,
	TX_32X32,
	TX_32X32,
	TX_4X16,
	TX_16X4,
	TX_8X32,
	TX_32X8,
	TX_16X32,
	TX_32X16};

const static uint8_t Coeff_Base_Ctx_Offset[TX_SIZES_ALL][5][5] = {
	{{0, 1, 6, 6, 0},
	 {1, 6, 6, 21, 0},
	 {6, 6, 21, 21, 0},
	 {6, 21, 21, 21, 0},
	 {0, 0, 0, 0, 0}},
	{{0, 1, 6, 6, 21},
	 {1, 6, 6, 21, 21},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 1, 6, 6, 21},
	 {1, 6, 6, 21, 21},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 1, 6, 6, 21},
	 {1, 6, 6, 21, 21},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 1, 6, 6, 21},
	 {1, 6, 6, 21, 21},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 11, 11, 11, 0},
	 {11, 11, 11, 11, 0},
	 {6, 6, 21, 21, 0},
	 {6, 21, 21, 21, 0},
	 {21, 21, 21, 21, 0}},
	{{0, 16, 6, 6, 21},
	 {16, 16, 6, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21},
	 {0, 0, 0, 0, 0}},
	{{0, 11, 11, 11, 11},
	 {11, 11, 11, 11, 11},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 16, 6, 6, 21},
	 {16, 16, 6, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21}},
	{{0, 11, 11, 11, 11},
	 {11, 11, 11, 11, 11},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 16, 6, 6, 21},
	 {16, 16, 6, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21}},
	{{0, 11, 11, 11, 11},
	 {11, 11, 11, 11, 11},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 16, 6, 6, 21},
	 {16, 16, 6, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21}},
	{{0, 11, 11, 11, 0},
	 {11, 11, 11, 11, 0},
	 {6, 6, 21, 21, 0},
	 {6, 21, 21, 21, 0},
	 {21, 21, 21, 21, 0}},
	{{0, 16, 6, 6, 21},
	 {16, 16, 6, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21},
	 {0, 0, 0, 0, 0}},
	{{0, 11, 11, 11, 11},
	 {11, 11, 11, 11, 11},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 16, 6, 6, 21},
	 {16, 16, 6, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21}},
	{{0, 11, 11, 11, 11},
	 {11, 11, 11, 11, 11},
	 {6, 6, 21, 21, 21},
	 {6, 21, 21, 21, 21},
	 {21, 21, 21, 21, 21}},
	{{0, 16, 6, 6, 21},
	 {16, 16, 6, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21},
	 {16, 16, 21, 21, 21}}};

const static uint8_t Mag_Ref_Offset_With_Tx_Class[3][3][2] = {
	{{0, 1}, {1, 0}, {1, 1}},
	{{0, 1}, {1, 0}, {0, 2}},
	{{0, 1}, {1, 0}, {2, 0}}};
const static uint8_t Dr_Intra_Derivative[90] = {
	0, 0, 0, 1023, 0, 0, 547, 0, 0, 372, 0, 0, 0, 0,
	273, 0, 0, 215, 0, 0, 178, 0, 0, 151, 0, 0, 132, 0, 0,
	116, 0, 0, 102, 0, 0, 0, 90, 0, 0, 80, 0, 0, 71, 0, 0,
	64, 0, 0, 57, 0, 0, 51, 0, 0, 45, 0, 0, 0, 40, 0, 0,
	35, 0, 0, 31, 0, 0, 27, 0, 0, 23, 0, 0, 19, 0, 0,
	15, 0, 0, 0, 0, 11, 0, 0, 7, 0, 0, 3, 0, 0};

const static uint8_t Tx_Type_Intra_Inv_Set1[7] = {IDTX, DCT_DCT, V_DCT, H_DCT, ADST_ADST, ADST_DCT, DCT_ADST};
const static uint8_t Tx_Type_Intra_Inv_Set2[5] = {IDTX, DCT_DCT, ADST_ADST, ADST_DCT, DCT_ADST};
const static uint8_t Tx_Type_Inter_Inv_Set1[16] = {IDTX, V_DCT, H_DCT, V_ADST, H_ADST, V_FLIPADST, H_FLIPADST,
												   DCT_DCT, ADST_DCT, DCT_ADST, FLIPADST_DCT, DCT_FLIPADST, ADST_ADST,
												   FLIPADST_FLIPADST, ADST_FLIPADST, FLIPADST_ADST};
const static uint8_t Tx_Type_Inter_Inv_Set2[12] = {IDTX, V_DCT, H_DCT, DCT_DCT, ADST_DCT, DCT_ADST, FLIPADST_DCT,
												   DCT_FLIPADST, ADST_ADST, FLIPADST_FLIPADST, ADST_FLIPADST,
												   FLIPADST_ADST};
const static uint8_t Tx_Type_Inter_Inv_Set3[2] = {IDTX, DCT_DCT};

const static uint8_t Filter_Intra_Mode_To_Intra_Dir[INTRA_FILTER_MODES] = {
	DC_PRED, V_PRED, H_PRED, D157_PRED, DC_PRED};

const static uint8_t Mode_To_Angle[INTRA_MODES] = {0, 90, 180, 45, 135, 113, 157, 203, 67, 0, 0, 0, 0};

const static uint8_t Quantizer_Matrix[15][2][QM_TOTAL_SIZE] = {
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 43, 73, 97, 43, 67, 94, 110, 73, 94, 137, 150, 97, 110, 150, 200,
		 /* Size 8x8 */
		 32, 32, 38, 51, 68, 84, 95, 109, 32, 35, 40, 49, 63, 76, 89, 102, 38,
		 40, 54, 65, 78, 91, 98, 106, 51, 49, 65, 82, 97, 111, 113, 121, 68, 63,
		 78, 97, 117, 134, 138, 142, 84, 76, 91, 111, 134, 152, 159, 168, 95, 89,
		 98, 113, 138, 159, 183, 199, 109, 102, 106, 121, 142, 168, 199, 220,
		 /* Size 16x16 */
		 32, 31, 31, 34, 36, 44, 48, 59, 65, 80, 83, 91, 97, 104, 111, 119, 31,
		 32, 32, 33, 34, 41, 44, 54, 59, 72, 75, 83, 90, 97, 104, 112, 31, 32,
		 33, 35, 36, 42, 45, 54, 59, 71, 74, 81, 86, 93, 100, 107, 34, 33, 35,
		 39, 42, 47, 51, 58, 63, 74, 76, 81, 84, 90, 97, 105, 36, 34, 36, 42, 48,
		 54, 57, 64, 68, 79, 81, 88, 91, 96, 102, 105, 44, 41, 42, 47, 54, 63,
		 67, 75, 79, 90, 92, 95, 100, 102, 109, 112, 48, 44, 45, 51, 57, 67, 71,
		 80, 85, 96, 99, 107, 108, 111, 117, 120, 59, 54, 54, 58, 64, 75, 80, 92,
		 98, 110, 113, 115, 116, 122, 125, 130, 65, 59, 59, 63, 68, 79, 85, 98,
		 105, 118, 121, 127, 130, 134, 135, 140, 80, 72, 71, 74, 79, 90, 96, 110,
		 118, 134, 137, 140, 143, 144, 146, 152, 83, 75, 74, 76, 81, 92, 99, 113,
		 121, 137, 140, 151, 152, 155, 158, 165, 91, 83, 81, 81, 88, 95, 107,
		 115, 127, 140, 151, 159, 166, 169, 173, 179, 97, 90, 86, 84, 91, 100,
		 108, 116, 130, 143, 152, 166, 174, 182, 189, 193, 104, 97, 93, 90, 96,
		 102, 111, 122, 134, 144, 155, 169, 182, 191, 200, 210, 111, 104, 100,
		 97, 102, 109, 117, 125, 135, 146, 158, 173, 189, 200, 210, 220, 119,
		 112, 107, 105, 105, 112, 120, 130, 140, 152, 165, 179, 193, 210, 220,
		 231,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 32, 34, 35, 36, 39, 44, 46, 48, 54, 59, 62, 65, 71,
		 80, 81, 83, 88, 91, 94, 97, 101, 104, 107, 111, 115, 119, 123, 31, 32,
		 32, 32, 32, 32, 34, 34, 35, 38, 42, 44, 46, 51, 56, 59, 62, 68, 76, 77,
		 78, 84, 86, 89, 92, 95, 99, 102, 105, 109, 113, 116, 31, 32, 32, 32, 32,
		 32, 33, 34, 34, 37, 41, 42, 44, 49, 54, 56, 59, 65, 72, 73, 75, 80, 83,
		 86, 90, 93, 97, 101, 104, 108, 112, 116, 31, 32, 32, 32, 33, 33, 34, 35,
		 35, 38, 41, 43, 45, 49, 54, 56, 59, 64, 72, 73, 74, 79, 82, 85, 88, 91,
		 94, 97, 101, 104, 107, 111, 31, 32, 32, 33, 33, 34, 35, 36, 36, 39, 42,
		 44, 45, 50, 54, 56, 59, 64, 71, 72, 74, 78, 81, 84, 86, 89, 93, 96, 100,
		 104, 107, 111, 32, 32, 32, 33, 34, 35, 37, 37, 38, 40, 42, 44, 46, 49,
		 53, 55, 58, 63, 69, 70, 72, 76, 79, 82, 85, 89, 93, 96, 99, 102, 106,
		 109, 34, 34, 33, 34, 35, 37, 39, 41, 42, 45, 47, 49, 51, 54, 58, 60, 63,
		 68, 74, 75, 76, 80, 81, 82, 84, 87, 90, 93, 97, 101, 105, 110, 35, 34,
		 34, 35, 36, 37, 41, 43, 45, 47, 50, 52, 53, 57, 61, 63, 65, 70, 76, 77,
		 79, 82, 84, 86, 89, 91, 92, 93, 96, 100, 103, 107, 36, 35, 34, 35, 36,
		 38, 42, 45, 48, 50, 54, 55, 57, 60, 64, 66, 68, 73, 79, 80, 81, 85, 88,
		 90, 91, 93, 96, 99, 102, 103, 105, 107, 39, 38, 37, 38, 39, 40, 45, 47,
		 50, 54, 58, 59, 61, 65, 69, 71, 73, 78, 84, 85, 86, 91, 92, 92, 95, 98,
		 100, 101, 103, 106, 110, 114, 44, 42, 41, 41, 42, 42, 47, 50, 54, 58,
		 63, 65, 67, 71, 75, 77, 79, 84, 90, 91, 92, 95, 95, 97, 100, 101, 102,
		 105, 109, 111, 112, 114, 46, 44, 42, 43, 44, 44, 49, 52, 55, 59, 65, 67,
		 69, 74, 78, 80, 82, 87, 93, 94, 95, 98, 100, 103, 102, 105, 108, 110,
		 111, 113, 117, 121, 48, 46, 44, 45, 45, 46, 51, 53, 57, 61, 67, 69, 71,
		 76, 80, 83, 85, 90, 96, 97, 99, 103, 107, 105, 108, 111, 111, 113, 117,
		 119, 120, 122, 54, 51, 49, 49, 50, 49, 54, 57, 60, 65, 71, 74, 76, 82,
		 87, 89, 92, 97, 104, 105, 106, 111, 110, 111, 114, 113, 116, 120, 120,
		 121, 125, 130, 59, 56, 54, 54, 54, 53, 58, 61, 64, 69, 75, 78, 80, 87,
		 92, 95, 98, 103, 110, 111, 113, 115, 115, 119, 116, 120, 122, 122, 125,
		 129, 130, 130, 62, 59, 56, 56, 56, 55, 60, 63, 66, 71, 77, 80, 83, 89,
		 95, 98, 101, 107, 114, 115, 117, 119, 123, 121, 125, 126, 125, 129, 131,
		 131, 135, 140, 65, 62, 59, 59, 59, 58, 63, 65, 68, 73, 79, 82, 85, 92,
		 98, 101, 105, 111, 118, 119, 121, 126, 127, 128, 130, 130, 134, 133,
		 135, 140, 140, 140, 71, 68, 65, 64, 64, 63, 68, 70, 73, 78, 84, 87, 90,
		 97, 103, 107, 111, 117, 125, 126, 128, 134, 132, 136, 133, 138, 137,
		 140, 143, 142, 145, 150, 80, 76, 72, 72, 71, 69, 74, 76, 79, 84, 90, 93,
		 96, 104, 110, 114, 118, 125, 134, 135, 137, 139, 140, 139, 143, 142,
		 144, 146, 146, 151, 152, 151, 81, 77, 73, 73, 72, 70, 75, 77, 80, 85,
		 91, 94, 97, 105, 111, 115, 119, 126, 135, 137, 138, 144, 147, 146, 148,
		 149, 151, 150, 156, 155, 157, 163, 83, 78, 75, 74, 74, 72, 76, 79, 81,
		 86, 92, 95, 99, 106, 113, 117, 121, 128, 137, 138, 140, 147, 151, 156,
		 152, 157, 155, 161, 158, 162, 165, 164, 88, 84, 80, 79, 78, 76, 80, 82,
		 85, 91, 95, 98, 103, 111, 115, 119, 126, 134, 139, 144, 147, 152, 154,
		 158, 163, 159, 165, 163, 168, 168, 169, 176, 91, 86, 83, 82, 81, 79, 81,
		 84, 88, 92, 95, 100, 107, 110, 115, 123, 127, 132, 140, 147, 151, 154,
		 159, 161, 166, 171, 169, 173, 173, 176, 179, 177, 94, 89, 86, 85, 84,
		 82, 82, 86, 90, 92, 97, 103, 105, 111, 119, 121, 128, 136, 139, 146,
		 156, 158, 161, 166, 168, 174, 179, 178, 180, 183, 183, 190, 97, 92, 90,
		 88, 86, 85, 84, 89, 91, 95, 100, 102, 108, 114, 116, 125, 130, 133, 143,
		 148, 152, 163, 166, 168, 174, 176, 182, 187, 189, 188, 193, 191, 101,
		 95, 93, 91, 89, 89, 87, 91, 93, 98, 101, 105, 111, 113, 120, 126, 130,
		 138, 142, 149, 157, 159, 171, 174, 176, 183, 184, 191, 195, 199, 197,
		 204, 104, 99, 97, 94, 93, 93, 90, 92, 96, 100, 102, 108, 111, 116, 122,
		 125, 134, 137, 144, 151, 155, 165, 169, 179, 182, 184, 191, 193, 200,
		 204, 210, 206, 107, 102, 101, 97, 96, 96, 93, 93, 99, 101, 105, 110,
		 113, 120, 122, 129, 133, 140, 146, 150, 161, 163, 173, 178, 187, 191,
		 193, 200, 202, 210, 214, 222, 111, 105, 104, 101, 100, 99, 97, 96, 102,
		 103, 109, 111, 117, 120, 125, 131, 135, 143, 146, 156, 158, 168, 173,
		 180, 189, 195, 200, 202, 210, 212, 220, 224, 115, 109, 108, 104, 104,
		 102, 101, 100, 103, 106, 111, 113, 119, 121, 129, 131, 140, 142, 151,
		 155, 162, 168, 176, 183, 188, 199, 204, 210, 212, 220, 222, 230, 119,
		 113, 112, 107, 107, 106, 105, 103, 105, 110, 112, 117, 120, 125, 130,
		 135, 140, 145, 152, 157, 165, 169, 179, 183, 193, 197, 210, 214, 220,
		 222, 231, 232, 123, 116, 116, 111, 111, 109, 110, 107, 107, 114, 114,
		 121, 122, 130, 130, 140, 140, 150, 151, 163, 164, 176, 177, 190, 191,
		 204, 206, 222, 224, 230, 232, 242,
		 /* Size 4x8 */
		 32, 42, 75, 91, 33, 42, 69, 86, 37, 58, 84, 91, 49, 71, 103, 110, 65,
		 84, 125, 128, 80, 97, 142, 152, 91, 100, 145, 178, 104, 112, 146, 190,
		 /* Size 8x4 */
		 32, 33, 37, 49, 65, 80, 91, 104, 42, 42, 58, 71, 84, 97, 100, 112, 75,
		 69, 84, 103, 125, 142, 145, 146, 91, 86, 91, 110, 128, 152, 178, 190,
		 /* Size 8x16 */
		 32, 32, 36, 53, 65, 87, 93, 99, 31, 33, 34, 49, 59, 78, 86, 93, 32, 34,
		 36, 50, 59, 77, 82, 89, 34, 37, 42, 54, 63, 79, 80, 88, 36, 38, 48, 60,
		 68, 84, 86, 90, 44, 43, 53, 71, 79, 95, 94, 97, 48, 46, 56, 76, 85, 102,
		 105, 105, 58, 54, 63, 87, 98, 116, 112, 115, 65, 58, 68, 92, 105, 124,
		 122, 124, 79, 70, 79, 104, 118, 141, 135, 135, 82, 72, 81, 106, 121,
		 144, 149, 146, 91, 80, 88, 106, 130, 148, 162, 159, 97, 86, 94, 107,
		 128, 157, 167, 171, 103, 93, 98, 114, 131, 150, 174, 186, 110, 100, 101,
		 117, 138, 161, 183, 193, 118, 107, 105, 118, 136, 157, 182, 203,
		 /* Size 16x8 */
		 32, 31, 32, 34, 36, 44, 48, 58, 65, 79, 82, 91, 97, 103, 110, 118, 32,
		 33, 34, 37, 38, 43, 46, 54, 58, 70, 72, 80, 86, 93, 100, 107, 36, 34,
		 36, 42, 48, 53, 56, 63, 68, 79, 81, 88, 94, 98, 101, 105, 53, 49, 50,
		 54, 60, 71, 76, 87, 92, 104, 106, 106, 107, 114, 117, 118, 65, 59, 59,
		 63, 68, 79, 85, 98, 105, 118, 121, 130, 128, 131, 138, 136, 87, 78, 77,
		 79, 84, 95, 102, 116, 124, 141, 144, 148, 157, 150, 161, 157, 93, 86,
		 82, 80, 86, 94, 105, 112, 122, 135, 149, 162, 167, 174, 183, 182, 99,
		 93, 89, 88, 90, 97, 105, 115, 124, 135, 146, 159, 171, 186, 193, 203,
		 /* Size 16x32 */
		 32, 31, 32, 34, 36, 44, 53, 59, 65, 79, 87, 90, 93, 96, 99, 102, 31, 32,
		 32, 34, 35, 42, 51, 56, 62, 75, 82, 85, 88, 91, 94, 97, 31, 32, 33, 33,
		 34, 41, 49, 54, 59, 72, 78, 82, 86, 90, 93, 97, 31, 32, 33, 34, 35, 41,
		 49, 54, 59, 71, 78, 81, 84, 87, 90, 93, 32, 32, 34, 35, 36, 42, 50, 54,
		 59, 71, 77, 80, 82, 86, 89, 93, 32, 33, 35, 37, 38, 42, 49, 53, 58, 69,
		 75, 78, 82, 86, 89, 92, 34, 34, 37, 39, 42, 48, 54, 58, 63, 73, 79, 78,
		 80, 83, 88, 92, 35, 34, 37, 41, 45, 50, 57, 61, 65, 76, 82, 83, 84, 84,
		 87, 90, 36, 34, 38, 43, 48, 54, 60, 64, 68, 78, 84, 87, 86, 89, 90, 90,
		 39, 37, 40, 45, 50, 58, 65, 69, 73, 84, 89, 89, 91, 91, 93, 96, 44, 41,
		 43, 48, 53, 63, 71, 75, 79, 90, 95, 93, 94, 95, 97, 97, 46, 43, 44, 49,
		 55, 65, 73, 78, 82, 93, 98, 100, 98, 100, 99, 103, 48, 45, 46, 51, 56,
		 67, 76, 80, 85, 96, 102, 102, 105, 102, 105, 104, 53, 49, 50, 54, 60,
		 71, 82, 87, 92, 103, 109, 107, 107, 110, 107, 111, 58, 54, 54, 58, 63,
		 75, 87, 92, 98, 110, 116, 115, 112, 111, 115, 112, 61, 57, 56, 60, 66,
		 77, 89, 95, 101, 114, 120, 118, 119, 118, 116, 120, 65, 60, 58, 63, 68,
		 79, 92, 98, 105, 118, 124, 123, 122, 123, 124, 121, 71, 65, 63, 68, 73,
		 84, 97, 103, 111, 125, 132, 132, 130, 128, 127, 130, 79, 72, 70, 74, 79,
		 90, 104, 110, 118, 133, 141, 136, 135, 135, 135, 131, 81, 74, 71, 75,
		 80, 91, 105, 112, 119, 135, 142, 140, 140, 138, 139, 142, 82, 75, 72,
		 76, 81, 92, 106, 113, 121, 136, 144, 151, 149, 149, 146, 143, 88, 80,
		 77, 80, 85, 97, 108, 115, 126, 142, 149, 153, 153, 152, 152, 154, 91,
		 83, 80, 81, 88, 100, 106, 114, 130, 142, 148, 155, 162, 160, 159, 155,
		 94, 85, 83, 82, 91, 100, 105, 118, 131, 137, 153, 160, 165, 167, 166,
		 168, 97, 88, 86, 85, 94, 100, 107, 123, 128, 140, 157, 161, 167, 173,
		 171, 169, 100, 91, 89, 87, 97, 100, 111, 121, 127, 145, 152, 164, 173,
		 178, 182, 181, 103, 94, 93, 90, 98, 101, 114, 120, 131, 144, 150, 170,
		 174, 180, 186, 183, 107, 97, 96, 93, 100, 104, 117, 119, 136, 142, 155,
		 168, 177, 187, 191, 198, 110, 101, 100, 97, 101, 108, 117, 123, 138,
		 141, 161, 165, 183, 188, 193, 200, 114, 104, 104, 100, 103, 112, 117,
		 127, 137, 146, 159, 167, 185, 190, 201, 206, 118, 108, 107, 103, 105,
		 115, 118, 131, 136, 151, 157, 172, 182, 197, 203, 208, 122, 111, 111,
		 107, 107, 119, 119, 136, 136, 156, 156, 178, 179, 203, 204, 217,
		 /* Size 32x16 */
		 32, 31, 31, 31, 32, 32, 34, 35, 36, 39, 44, 46, 48, 53, 58, 61, 65, 71,
		 79, 81, 82, 88, 91, 94, 97, 100, 103, 107, 110, 114, 118, 122, 31, 32,
		 32, 32, 32, 33, 34, 34, 34, 37, 41, 43, 45, 49, 54, 57, 60, 65, 72, 74,
		 75, 80, 83, 85, 88, 91, 94, 97, 101, 104, 108, 111, 32, 32, 33, 33, 34,
		 35, 37, 37, 38, 40, 43, 44, 46, 50, 54, 56, 58, 63, 70, 71, 72, 77, 80,
		 83, 86, 89, 93, 96, 100, 104, 107, 111, 34, 34, 33, 34, 35, 37, 39, 41,
		 43, 45, 48, 49, 51, 54, 58, 60, 63, 68, 74, 75, 76, 80, 81, 82, 85, 87,
		 90, 93, 97, 100, 103, 107, 36, 35, 34, 35, 36, 38, 42, 45, 48, 50, 53,
		 55, 56, 60, 63, 66, 68, 73, 79, 80, 81, 85, 88, 91, 94, 97, 98, 100,
		 101, 103, 105, 107, 44, 42, 41, 41, 42, 42, 48, 50, 54, 58, 63, 65, 67,
		 71, 75, 77, 79, 84, 90, 91, 92, 97, 100, 100, 100, 100, 101, 104, 108,
		 112, 115, 119, 53, 51, 49, 49, 50, 49, 54, 57, 60, 65, 71, 73, 76, 82,
		 87, 89, 92, 97, 104, 105, 106, 108, 106, 105, 107, 111, 114, 117, 117,
		 117, 118, 119, 59, 56, 54, 54, 54, 53, 58, 61, 64, 69, 75, 78, 80, 87,
		 92, 95, 98, 103, 110, 112, 113, 115, 114, 118, 123, 121, 120, 119, 123,
		 127, 131, 136, 65, 62, 59, 59, 59, 58, 63, 65, 68, 73, 79, 82, 85, 92,
		 98, 101, 105, 111, 118, 119, 121, 126, 130, 131, 128, 127, 131, 136,
		 138, 137, 136, 136, 79, 75, 72, 71, 71, 69, 73, 76, 78, 84, 90, 93, 96,
		 103, 110, 114, 118, 125, 133, 135, 136, 142, 142, 137, 140, 145, 144,
		 142, 141, 146, 151, 156, 87, 82, 78, 78, 77, 75, 79, 82, 84, 89, 95, 98,
		 102, 109, 116, 120, 124, 132, 141, 142, 144, 149, 148, 153, 157, 152,
		 150, 155, 161, 159, 157, 156, 90, 85, 82, 81, 80, 78, 78, 83, 87, 89,
		 93, 100, 102, 107, 115, 118, 123, 132, 136, 140, 151, 153, 155, 160,
		 161, 164, 170, 168, 165, 167, 172, 178, 93, 88, 86, 84, 82, 82, 80, 84,
		 86, 91, 94, 98, 105, 107, 112, 119, 122, 130, 135, 140, 149, 153, 162,
		 165, 167, 173, 174, 177, 183, 185, 182, 179, 96, 91, 90, 87, 86, 86, 83,
		 84, 89, 91, 95, 100, 102, 110, 111, 118, 123, 128, 135, 138, 149, 152,
		 160, 167, 173, 178, 180, 187, 188, 190, 197, 203, 99, 94, 93, 90, 89,
		 89, 88, 87, 90, 93, 97, 99, 105, 107, 115, 116, 124, 127, 135, 139, 146,
		 152, 159, 166, 171, 182, 186, 191, 193, 201, 203, 204, 102, 97, 97, 93,
		 93, 92, 92, 90, 90, 96, 97, 103, 104, 111, 112, 120, 121, 130, 131, 142,
		 143, 154, 155, 168, 169, 181, 183, 198, 200, 206, 208, 217,
		 /* Size 4x16 */
		 31, 44, 79, 96, 32, 41, 72, 90, 32, 42, 71, 86, 34, 48, 73, 83, 34, 54,
		 78, 89, 41, 63, 90, 95, 45, 67, 96, 102, 54, 75, 110, 111, 60, 79, 118,
		 123, 72, 90, 133, 135, 75, 92, 136, 149, 83, 100, 142, 160, 88, 100,
		 140, 173, 94, 101, 144, 180, 101, 108, 141, 188, 108, 115, 151, 197,
		 /* Size 16x4 */
		 31, 32, 32, 34, 34, 41, 45, 54, 60, 72, 75, 83, 88, 94, 101, 108, 44,
		 41, 42, 48, 54, 63, 67, 75, 79, 90, 92, 100, 100, 101, 108, 115, 79, 72,
		 71, 73, 78, 90, 96, 110, 118, 133, 136, 142, 140, 144, 141, 151, 96, 90,
		 86, 83, 89, 95, 102, 111, 123, 135, 149, 160, 173, 180, 188, 197,
		 /* Size 8x32 */
		 32, 32, 36, 53, 65, 87, 93, 99, 31, 32, 35, 51, 62, 82, 88, 94, 31, 33,
		 34, 49, 59, 78, 86, 93, 31, 33, 35, 49, 59, 78, 84, 90, 32, 34, 36, 50,
		 59, 77, 82, 89, 32, 35, 38, 49, 58, 75, 82, 89, 34, 37, 42, 54, 63, 79,
		 80, 88, 35, 37, 45, 57, 65, 82, 84, 87, 36, 38, 48, 60, 68, 84, 86, 90,
		 39, 40, 50, 65, 73, 89, 91, 93, 44, 43, 53, 71, 79, 95, 94, 97, 46, 44,
		 55, 73, 82, 98, 98, 99, 48, 46, 56, 76, 85, 102, 105, 105, 53, 50, 60,
		 82, 92, 109, 107, 107, 58, 54, 63, 87, 98, 116, 112, 115, 61, 56, 66,
		 89, 101, 120, 119, 116, 65, 58, 68, 92, 105, 124, 122, 124, 71, 63, 73,
		 97, 111, 132, 130, 127, 79, 70, 79, 104, 118, 141, 135, 135, 81, 71, 80,
		 105, 119, 142, 140, 139, 82, 72, 81, 106, 121, 144, 149, 146, 88, 77,
		 85, 108, 126, 149, 153, 152, 91, 80, 88, 106, 130, 148, 162, 159, 94,
		 83, 91, 105, 131, 153, 165, 166, 97, 86, 94, 107, 128, 157, 167, 171,
		 100, 89, 97, 111, 127, 152, 173, 182, 103, 93, 98, 114, 131, 150, 174,
		 186, 107, 96, 100, 117, 136, 155, 177, 191, 110, 100, 101, 117, 138,
		 161, 183, 193, 114, 104, 103, 117, 137, 159, 185, 201, 118, 107, 105,
		 118, 136, 157, 182, 203, 122, 111, 107, 119, 136, 156, 179, 204,
		 /* Size 32x8 */
		 32, 31, 31, 31, 32, 32, 34, 35, 36, 39, 44, 46, 48, 53, 58, 61, 65, 71,
		 79, 81, 82, 88, 91, 94, 97, 100, 103, 107, 110, 114, 118, 122, 32, 32,
		 33, 33, 34, 35, 37, 37, 38, 40, 43, 44, 46, 50, 54, 56, 58, 63, 70, 71,
		 72, 77, 80, 83, 86, 89, 93, 96, 100, 104, 107, 111, 36, 35, 34, 35, 36,
		 38, 42, 45, 48, 50, 53, 55, 56, 60, 63, 66, 68, 73, 79, 80, 81, 85, 88,
		 91, 94, 97, 98, 100, 101, 103, 105, 107, 53, 51, 49, 49, 50, 49, 54, 57,
		 60, 65, 71, 73, 76, 82, 87, 89, 92, 97, 104, 105, 106, 108, 106, 105,
		 107, 111, 114, 117, 117, 117, 118, 119, 65, 62, 59, 59, 59, 58, 63, 65,
		 68, 73, 79, 82, 85, 92, 98, 101, 105, 111, 118, 119, 121, 126, 130, 131,
		 128, 127, 131, 136, 138, 137, 136, 136, 87, 82, 78, 78, 77, 75, 79, 82,
		 84, 89, 95, 98, 102, 109, 116, 120, 124, 132, 141, 142, 144, 149, 148,
		 153, 157, 152, 150, 155, 161, 159, 157, 156, 93, 88, 86, 84, 82, 82, 80,
		 84, 86, 91, 94, 98, 105, 107, 112, 119, 122, 130, 135, 140, 149, 153,
		 162, 165, 167, 173, 174, 177, 183, 185, 182, 179, 99, 94, 93, 90, 89,
		 89, 88, 87, 90, 93, 97, 99, 105, 107, 115, 116, 124, 127, 135, 139, 146,
		 152, 159, 166, 171, 182, 186, 191, 193, 201, 203, 204},
		{/* Chroma */
		 /* Size 4x4 */
		 35, 46, 57, 66, 46, 60, 69, 71, 57, 69, 90, 90, 66, 71, 90, 109,
		 /* Size 8x8 */
		 31, 38, 47, 50, 57, 63, 67, 71, 38, 47, 46, 47, 52, 57, 62, 67, 47, 46,
		 54, 57, 61, 66, 67, 68, 50, 47, 57, 66, 72, 77, 75, 75, 57, 52, 61, 72,
		 82, 88, 86, 84, 63, 57, 66, 77, 88, 96, 95, 95, 67, 62, 67, 75, 86, 95,
		 104, 107, 71, 67, 68, 75, 84, 95, 107, 113,
		 /* Size 16x16 */
		 32, 30, 33, 41, 49, 49, 50, 54, 57, 63, 65, 68, 70, 72, 74, 76, 30, 32,
		 35, 42, 46, 45, 46, 49, 52, 57, 58, 62, 64, 67, 70, 72, 33, 35, 39, 45,
		 47, 45, 46, 49, 51, 56, 57, 60, 62, 64, 66, 69, 41, 42, 45, 48, 50, 49,
		 50, 52, 53, 57, 58, 59, 60, 61, 64, 67, 49, 46, 47, 50, 53, 53, 54, 55,
		 56, 60, 61, 64, 64, 65, 66, 66, 49, 45, 45, 49, 53, 58, 60, 62, 63, 67,
		 68, 67, 69, 68, 70, 70, 50, 46, 46, 50, 54, 60, 61, 65, 67, 71, 71, 74,
		 73, 73, 74, 74, 54, 49, 49, 52, 55, 62, 65, 71, 73, 78, 79, 78, 77, 78,
		 78, 78, 57, 52, 51, 53, 56, 63, 67, 73, 76, 82, 83, 84, 84, 84, 82, 83,
		 63, 57, 56, 57, 60, 67, 71, 78, 82, 89, 90, 90, 89, 88, 87, 88, 65, 58,
		 57, 58, 61, 68, 71, 79, 83, 90, 91, 94, 93, 93, 92, 93, 68, 62, 60, 59,
		 64, 67, 74, 78, 84, 90, 94, 98, 99, 98, 98, 98, 70, 64, 62, 60, 64, 69,
		 73, 77, 84, 89, 93, 99, 102, 103, 104, 104, 72, 67, 64, 61, 65, 68, 73,
		 78, 84, 88, 93, 98, 103, 106, 108, 109, 74, 70, 66, 64, 66, 70, 74, 78,
		 82, 87, 92, 98, 104, 108, 111, 112, 76, 72, 69, 67, 66, 70, 74, 78, 83,
		 88, 93, 98, 104, 109, 112, 116,
		 /* Size 32x32 */
		 32, 31, 30, 32, 33, 36, 41, 45, 49, 48, 49, 50, 50, 52, 54, 56, 57, 60,
		 63, 64, 65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 78, 31, 31, 31, 33,
		 34, 38, 42, 45, 47, 47, 47, 47, 48, 50, 52, 53, 54, 57, 60, 61, 61, 63,
		 64, 65, 66, 67, 68, 69, 70, 71, 72, 74, 30, 31, 32, 33, 35, 40, 42, 44,
		 46, 45, 45, 45, 46, 47, 49, 51, 52, 54, 57, 58, 58, 61, 62, 63, 64, 66,
		 67, 68, 70, 71, 72, 74, 32, 33, 33, 35, 37, 41, 43, 45, 47, 46, 45, 46,
		 46, 47, 49, 50, 51, 54, 57, 57, 58, 60, 61, 62, 63, 64, 65, 66, 67, 68,
		 69, 70, 33, 34, 35, 37, 39, 43, 45, 46, 47, 46, 45, 46, 46, 47, 49, 50,
		 51, 53, 56, 57, 57, 59, 60, 61, 62, 63, 64, 65, 66, 68, 69, 70, 36, 38,
		 40, 41, 43, 47, 47, 47, 48, 46, 45, 46, 46, 47, 48, 49, 50, 52, 54, 55,
		 55, 57, 58, 59, 61, 62, 64, 65, 66, 67, 68, 69, 41, 42, 42, 43, 45, 47,
		 48, 49, 50, 49, 49, 49, 50, 50, 52, 52, 53, 55, 57, 58, 58, 60, 59, 59,
		 60, 61, 61, 63, 64, 66, 67, 69, 45, 45, 44, 45, 46, 47, 49, 50, 51, 51,
		 51, 51, 52, 52, 53, 54, 55, 57, 59, 59, 60, 61, 61, 62, 63, 63, 63, 63,
		 63, 64, 65, 66, 49, 47, 46, 47, 47, 48, 50, 51, 53, 53, 53, 54, 54, 54,
		 55, 56, 56, 58, 60, 61, 61, 63, 64, 64, 64, 64, 65, 66, 66, 66, 66, 66,
		 48, 47, 45, 46, 46, 46, 49, 51, 53, 54, 55, 56, 56, 57, 58, 59, 60, 61,
		 63, 64, 64, 66, 66, 65, 66, 67, 67, 67, 67, 68, 69, 70, 49, 47, 45, 45,
		 45, 45, 49, 51, 53, 55, 58, 59, 60, 61, 62, 63, 63, 65, 67, 67, 68, 69,
		 67, 68, 69, 68, 68, 69, 70, 70, 70, 70, 50, 47, 45, 46, 46, 46, 49, 51,
		 54, 56, 59, 60, 60, 62, 64, 64, 65, 67, 69, 69, 70, 70, 71, 71, 70, 70,
		 71, 71, 71, 71, 72, 74, 50, 48, 46, 46, 46, 46, 50, 52, 54, 56, 60, 60,
		 61, 63, 65, 66, 67, 68, 71, 71, 71, 73, 74, 72, 73, 74, 73, 73, 74, 74,
		 74, 74, 52, 50, 47, 47, 47, 47, 50, 52, 54, 57, 61, 62, 63, 66, 68, 69,
		 70, 72, 75, 75, 75, 77, 75, 75, 76, 75, 75, 76, 75, 75, 76, 77, 54, 52,
		 49, 49, 49, 48, 52, 53, 55, 58, 62, 64, 65, 68, 71, 72, 73, 75, 78, 78,
		 79, 79, 78, 79, 77, 78, 78, 77, 78, 79, 78, 78, 56, 53, 51, 50, 50, 49,
		 52, 54, 56, 59, 63, 64, 66, 69, 72, 73, 75, 77, 80, 80, 81, 81, 82, 80,
		 81, 81, 79, 81, 80, 79, 81, 82, 57, 54, 52, 51, 51, 50, 53, 55, 56, 60,
		 63, 65, 67, 70, 73, 75, 76, 79, 82, 82, 83, 85, 84, 83, 84, 83, 84, 82,
		 82, 84, 83, 82, 60, 57, 54, 54, 53, 52, 55, 57, 58, 61, 65, 67, 68, 72,
		 75, 77, 79, 82, 85, 85, 86, 88, 86, 87, 85, 86, 85, 85, 86, 84, 85, 86,
		 63, 60, 57, 57, 56, 54, 57, 59, 60, 63, 67, 69, 71, 75, 78, 80, 82, 85,
		 89, 89, 90, 90, 90, 89, 89, 88, 88, 88, 87, 88, 88, 87, 64, 61, 58, 57,
		 57, 55, 58, 59, 61, 64, 67, 69, 71, 75, 78, 80, 82, 85, 89, 90, 91, 92,
		 93, 92, 92, 91, 91, 90, 91, 90, 90, 92, 65, 61, 58, 58, 57, 55, 58, 60,
		 61, 64, 68, 70, 71, 75, 79, 81, 83, 86, 90, 91, 91, 94, 94, 96, 93, 94,
		 93, 94, 92, 93, 93, 92, 67, 63, 61, 60, 59, 57, 60, 61, 63, 66, 69, 70,
		 73, 77, 79, 81, 85, 88, 90, 92, 94, 96, 96, 97, 98, 95, 97, 95, 96, 95,
		 95, 96, 68, 64, 62, 61, 60, 58, 59, 61, 64, 66, 67, 71, 74, 75, 78, 82,
		 84, 86, 90, 93, 94, 96, 98, 98, 99, 100, 98, 99, 98, 98, 98, 97, 69, 65,
		 63, 62, 61, 59, 59, 62, 64, 65, 68, 71, 72, 75, 79, 80, 83, 87, 89, 92,
		 96, 97, 98, 100, 100, 101, 102, 101, 101, 101, 100, 102, 70, 66, 64, 63,
		 62, 61, 60, 63, 64, 66, 69, 70, 73, 76, 77, 81, 84, 85, 89, 92, 93, 98,
		 99, 100, 102, 102, 103, 104, 104, 103, 104, 102, 71, 67, 66, 64, 63, 62,
		 61, 63, 64, 67, 68, 70, 74, 75, 78, 81, 83, 86, 88, 91, 94, 95, 100,
		 101, 102, 104, 104, 105, 106, 107, 105, 107, 72, 68, 67, 65, 64, 64, 61,

		 63, 65, 67, 68, 71, 73, 75, 78, 79, 84, 85, 88, 91, 93, 97, 98, 102,
		 103, 104, 106, 106, 108, 108, 109, 107, 73, 69, 68, 66, 65, 65, 63, 63,
		 66, 67, 69, 71, 73, 76, 77, 81, 82, 85, 88, 90, 94, 95, 99, 101, 104,
		 105, 106, 109, 108, 110, 111, 112, 74, 70, 70, 67, 66, 66, 64, 63, 66,
		 67, 70, 71, 74, 75, 78, 80, 82, 86, 87, 91, 92, 96, 98, 101, 104, 106,
		 108, 108, 111, 111, 112, 113, 75, 71, 71, 68, 68, 67, 66, 64, 66, 68,
		 70, 71, 74, 75, 79, 79, 84, 84, 88, 90, 93, 95, 98, 101, 103, 107, 108,
		 110, 111, 113, 113, 115, 76, 72, 72, 69, 69, 68, 67, 65, 66, 69, 70, 72,
		 74, 76, 78, 81, 83, 85, 88, 90, 93, 95, 98, 100, 104, 105, 109, 111,
		 112, 113, 116, 115, 78, 74, 74, 70, 70, 69, 69, 66, 66, 70, 70, 74, 74,
		 77, 78, 82, 82, 86, 87, 92, 92, 96, 97, 102, 102, 107, 107, 112, 113,
		 115, 115, 118,
		 /* Size 4x8 */
		 31, 47, 60, 66, 40, 45, 54, 61, 46, 56, 64, 64, 48, 61, 75, 73, 54, 65,
		 85, 82, 61, 69, 92, 92, 64, 68, 90, 102, 68, 71, 87, 105,
		 /* Size 8x4 */
		 31, 40, 46, 48, 54, 61, 64, 68, 47, 45, 56, 61, 65, 69, 68, 71, 60, 54,
		 64, 75, 85, 92, 90, 87, 66, 61, 64, 73, 82, 92, 102, 105,
		 /* Size 8x16 */
		 32, 37, 48, 52, 57, 66, 68, 71, 30, 40, 46, 48, 52, 60, 63, 66, 33, 43,
		 47, 47, 51, 59, 60, 63, 42, 47, 50, 50, 53, 60, 59, 62, 49, 48, 53, 54,
		 57, 62, 62, 62, 49, 46, 53, 61, 64, 69, 66, 66, 50, 46, 54, 64, 67, 73,
		 72, 70, 54, 49, 55, 68, 73, 80, 76, 75, 57, 50, 56, 70, 76, 84, 80, 79,
		 63, 55, 60, 75, 82, 92, 87, 84, 64, 56, 61, 75, 83, 93, 93, 89, 68, 59,
		 64, 74, 86, 94, 98, 94, 70, 62, 66, 73, 83, 96, 99, 98, 72, 64, 66, 75,
		 83, 92, 101, 104, 74, 67, 66, 74, 84, 94, 103, 106, 76, 69, 67, 73, 82,
		 91, 101, 109,
		 /* Size 16x8 */
		 32, 30, 33, 42, 49, 49, 50, 54, 57, 63, 64, 68, 70, 72, 74, 76, 37, 40,
		 43, 47, 48, 46, 46, 49, 50, 55, 56, 59, 62, 64, 67, 69, 48, 46, 47, 50,
		 53, 53, 54, 55, 56, 60, 61, 64, 66, 66, 66, 67, 52, 48, 47, 50, 54, 61,
		 64, 68, 70, 75, 75, 74, 73, 75, 74, 73, 57, 52, 51, 53, 57, 64, 67, 73,
		 76, 82, 83, 86, 83, 83, 84, 82, 66, 60, 59, 60, 62, 69, 73, 80, 84, 92,
		 93, 94, 96, 92, 94, 91, 68, 63, 60, 59, 62, 66, 72, 76, 80, 87, 93, 98,
		 99, 101, 103, 101, 71, 66, 63, 62, 62, 66, 70, 75, 79, 84, 89, 94, 98,
		 104, 106, 109,
		 /* Size 16x32 */
		 32, 31, 37, 42, 48, 49, 52, 54, 57, 63, 66, 67, 68, 69, 71, 72, 31, 31,
		 38, 42, 47, 47, 50, 52, 54, 60, 63, 64, 65, 66, 67, 68, 30, 32, 40, 42,
		 46, 45, 48, 50, 52, 57, 60, 62, 63, 65, 66, 68, 32, 34, 41, 44, 46, 45,
		 48, 49, 51, 57, 59, 61, 62, 63, 64, 65, 33, 36, 43, 45, 47, 46, 47, 49,
		 51, 56, 59, 60, 60, 62, 63, 65, 37, 40, 47, 47, 47, 45, 47, 48, 50, 54,
		 57, 58, 60, 61, 62, 63, 42, 43, 47, 48, 50, 49, 50, 52, 53, 57, 60, 58,
		 59, 60, 62, 63, 45, 44, 47, 49, 51, 51, 52, 54, 55, 59, 61, 61, 61, 60,
		 61, 61, 49, 46, 48, 50, 53, 53, 54, 55, 57, 60, 62, 63, 62, 63, 62, 62,
		 48, 46, 47, 50, 53, 56, 57, 59, 60, 64, 66, 65, 65, 64, 64, 65, 49, 45,
		 46, 49, 53, 58, 61, 62, 64, 67, 69, 67, 66, 66, 66, 65, 49, 46, 46, 49,
		 53, 59, 62, 64, 65, 69, 71, 70, 68, 68, 67, 68, 50, 46, 46, 50, 54, 59,
		 64, 65, 67, 71, 73, 72, 72, 70, 70, 69, 52, 48, 47, 50, 54, 61, 66, 68,
		 71, 75, 77, 74, 73, 73, 71, 72, 54, 50, 49, 52, 55, 62, 68, 71, 73, 78,

		 80, 78, 76, 74, 75, 73, 55, 51, 49, 52, 56, 63, 69, 72, 75, 80, 82, 80,
		 79, 78, 76, 77, 57, 52, 50, 53, 56, 64, 70, 73, 76, 82, 84, 82, 80, 80,
		 79, 77, 60, 54, 52, 55, 58, 65, 72, 75, 79, 85, 88, 86, 84, 82, 81, 81,
		 63, 57, 55, 58, 60, 67, 75, 78, 82, 89, 92, 88, 87, 85, 84, 81, 64, 58,
		 55, 58, 61, 68, 75, 78, 82, 89, 92, 90, 89, 87, 86, 86, 64, 59, 56, 58,
		 61, 68, 75, 79, 83, 90, 93, 95, 93, 91, 89, 87, 67, 61, 58, 60, 63, 69,
		 76, 79, 85, 92, 95, 96, 94, 92, 91, 91, 68, 62, 59, 60, 64, 71, 74, 78,
		 86, 91, 94, 96, 98, 96, 94, 91, 69, 62, 60, 60, 65, 70, 72, 79, 85, 88,
		 95, 98, 99, 98, 97, 96, 70, 63, 62, 60, 66, 69, 73, 81, 83, 89, 96, 97,
		 99, 101, 98, 97, 71, 64, 63, 61, 67, 68, 74, 79, 82, 90, 93, 98, 102,
		 102, 102, 101, 72, 65, 64, 62, 66, 68, 75, 78, 83, 89, 92, 100, 101,
		 103, 104, 102, 73, 66, 65, 63, 66, 69, 75, 76, 84, 87, 93, 98, 102, 105,
		 106, 107, 74, 67, 67, 64, 66, 70, 74, 77, 84, 86, 94, 96, 103, 105, 106,
		 107, 75, 68, 68, 65, 66, 71, 74, 78, 83, 87, 93, 96, 103, 105, 109, 109,
		 76, 69, 69, 66, 67, 72, 73, 80, 82, 88, 91, 97, 101, 107, 109, 110, 77,
		 70, 70, 67, 67, 73, 73, 81, 81, 90, 90, 99, 99, 108, 108, 113,
		 /* Size 32x16 */
		 32, 31, 30, 32, 33, 37, 42, 45, 49, 48, 49, 49, 50, 52, 54, 55, 57, 60,
		 63, 64, 64, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 31, 31, 32, 34,
		 36, 40, 43, 44, 46, 46, 45, 46, 46, 48, 50, 51, 52, 54, 57, 58, 59, 61,
		 62, 62, 63, 64, 65, 66, 67, 68, 69, 70, 37, 38, 40, 41, 43, 47, 47, 47,
		 48, 47, 46, 46, 46, 47, 49, 49, 50, 52, 55, 55, 56, 58, 59, 60, 62, 63,
		 64, 65, 67, 68, 69, 70, 42, 42, 42, 44, 45, 47, 48, 49, 50, 50, 49, 49,
		 50, 50, 52, 52, 53, 55, 58, 58, 58, 60, 60, 60, 60, 61, 62, 63, 64, 65,
		 66, 67, 48, 47, 46, 46, 47, 47, 50, 51, 53, 53, 53, 53, 54, 54, 55, 56,
		 56, 58, 60, 61, 61, 63, 64, 65, 66, 67, 66, 66, 66, 66, 67, 67, 49, 47,
		 45, 45, 46, 45, 49, 51, 53, 56, 58, 59, 59, 61, 62, 63, 64, 65, 67, 68,
		 68, 69, 71, 70, 69, 68, 68, 69, 70, 71, 72, 73, 52, 50, 48, 48, 47, 47,
		 50, 52, 54, 57, 61, 62, 64, 66, 68, 69, 70, 72, 75, 75, 75, 76, 74, 72,
		 73, 74, 75, 75, 74, 74, 73, 73, 54, 52, 50, 49, 49, 48, 52, 54, 55, 59,
		 62, 64, 65, 68, 71, 72, 73, 75, 78, 78, 79, 79, 78, 79, 81, 79, 78, 76,
		 77, 78, 80, 81, 57, 54, 52, 51, 51, 50, 53, 55, 57, 60, 64, 65, 67, 71,
		 73, 75, 76, 79, 82, 82, 83, 85, 86, 85, 83, 82, 83, 84, 84, 83, 82, 81,
		 63, 60, 57, 57, 56, 54, 57, 59, 60, 64, 67, 69, 71, 75, 78, 80, 82, 85,
		 89, 89, 90, 92, 91, 88, 89, 90, 89, 87, 86, 87, 88, 90, 66, 63, 60, 59,
		 59, 57, 60, 61, 62, 66, 69, 71, 73, 77, 80, 82, 84, 88, 92, 92, 93, 95,
		 94, 95, 96, 93, 92, 93, 94, 93, 91, 90, 67, 64, 62, 61, 60, 58, 58, 61,
		 63, 65, 67, 70, 72, 74, 78, 80, 82, 86, 88, 90, 95, 96, 96, 98, 97, 98,
		 100, 98, 96, 96, 97, 99, 68, 65, 63, 62, 60, 60, 59, 61, 62, 65, 66, 68,
		 72, 73, 76, 79, 80, 84, 87, 89, 93, 94, 98, 99, 99, 102, 101, 102, 103,
		 103, 101, 99, 69, 66, 65, 63, 62, 61, 60, 60, 63, 64, 66, 68, 70, 73,
		 74, 78, 80, 82, 85, 87, 91, 92, 96, 98, 101, 102, 103, 105, 105, 105,
		 107, 108, 71, 67, 66, 64, 63, 62, 62, 61, 62, 64, 66, 67, 70, 71, 75,
		 76, 79, 81, 84, 86, 89, 91, 94, 97, 98, 102, 104, 106, 106, 109, 109,
		 108, 72, 68, 68, 65, 65, 63, 63, 61, 62, 65, 65, 68, 69, 72, 73, 77, 77,
		 81, 81, 86, 87, 91, 91, 96, 97, 101, 102, 107, 107, 109, 110, 113,
		 /* Size 4x16 */
		 31, 49, 63, 69, 32, 45, 57, 65, 36, 46, 56, 62, 43, 49, 57, 60, 46, 53,
		 60, 63, 45, 58, 67, 66, 46, 59, 71, 70, 50, 62, 78, 74, 52, 64, 82, 80,
		 57, 67, 89, 85, 59, 68, 90, 91, 62, 71, 91, 96, 63, 69, 89, 101, 65, 68,

		 89, 103, 67, 70, 86, 105, 69, 72, 88, 107,
		 /* Size 16x4 */
		 31, 32, 36, 43, 46, 45, 46, 50, 52, 57, 59, 62, 63, 65, 67, 69, 49, 45,
		 46, 49, 53, 58, 59, 62, 64, 67, 68, 71, 69, 68, 70, 72, 63, 57, 56, 57,
		 60, 67, 71, 78, 82, 89, 90, 91, 89, 89, 86, 88, 69, 65, 62, 60, 63, 66,
		 70, 74, 80, 85, 91, 96, 101, 103, 105, 107,
		 /* Size 8x32 */
		 32, 37, 48, 52, 57, 66, 68, 71, 31, 38, 47, 50, 54, 63, 65, 67, 30, 40,
		 46, 48, 52, 60, 63, 66, 32, 41, 46, 48, 51, 59, 62, 64, 33, 43, 47, 47,
		 51, 59, 60, 63, 37, 47, 47, 47, 50, 57, 60, 62, 42, 47, 50, 50, 53, 60,
		 59, 62, 45, 47, 51, 52, 55, 61, 61, 61, 49, 48, 53, 54, 57, 62, 62, 62,
		 48, 47, 53, 57, 60, 66, 65, 64, 49, 46, 53, 61, 64, 69, 66, 66, 49, 46,
		 53, 62, 65, 71, 68, 67, 50, 46, 54, 64, 67, 73, 72, 70, 52, 47, 54, 66,
		 71, 77, 73, 71, 54, 49, 55, 68, 73, 80, 76, 75, 55, 49, 56, 69, 75, 82,
		 79, 76, 57, 50, 56, 70, 76, 84, 80, 79, 60, 52, 58, 72, 79, 88, 84, 81,
		 63, 55, 60, 75, 82, 92, 87, 84, 64, 55, 61, 75, 82, 92, 89, 86, 64, 56,
		 61, 75, 83, 93, 93, 89, 67, 58, 63, 76, 85, 95, 94, 91, 68, 59, 64, 74,
		 86, 94, 98, 94, 69, 60, 65, 72, 85, 95, 99, 97, 70, 62, 66, 73, 83, 96,
		 99, 98, 71, 63, 67, 74, 82, 93, 102, 102, 72, 64, 66, 75, 83, 92, 101,
		 104, 73, 65, 66, 75, 84, 93, 102, 106, 74, 67, 66, 74, 84, 94, 103, 106,
		 75, 68, 66, 74, 83, 93, 103, 109, 76, 69, 67, 73, 82, 91, 101, 109, 77,
		 70, 67, 73, 81, 90, 99, 108,
		 /* Size 32x8 */
		 32, 31, 30, 32, 33, 37, 42, 45, 49, 48, 49, 49, 50, 52, 54, 55, 57, 60,
		 63, 64, 64, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 37, 38, 40, 41,
		 43, 47, 47, 47, 48, 47, 46, 46, 46, 47, 49, 49, 50, 52, 55, 55, 56, 58,
		 59, 60, 62, 63, 64, 65, 67, 68, 69, 70, 48, 47, 46, 46, 47, 47, 50, 51,
		 53, 53, 53, 53, 54, 54, 55, 56, 56, 58, 60, 61, 61, 63, 64, 65, 66, 67,
		 66, 66, 66, 66, 67, 67, 52, 50, 48, 48, 47, 47, 50, 52, 54, 57, 61, 62,
		 64, 66, 68, 69, 70, 72, 75, 75, 75, 76, 74, 72, 73, 74, 75, 75, 74, 74,
		 73, 73, 57, 54, 52, 51, 51, 50, 53, 55, 57, 60, 64, 65, 67, 71, 73, 75,
		 76, 79, 82, 82, 83, 85, 86, 85, 83, 82, 83, 84, 84, 83, 82, 81, 66, 63,
		 60, 59, 59, 57, 60, 61, 62, 66, 69, 71, 73, 77, 80, 82, 84, 88, 92, 92,
		 93, 95, 94, 95, 96, 93, 92, 93, 94, 93, 91, 90, 68, 65, 63, 62, 60, 60,
		 59, 61, 62, 65, 66, 68, 72, 73, 76, 79, 80, 84, 87, 89, 93, 94, 98, 99,
		 99, 102, 101, 102, 103, 103, 101, 99, 71, 67, 66, 64, 63, 62, 62, 61,
		 62, 64, 66, 67, 70, 71, 75, 76, 79, 81, 84, 86, 89, 91, 94, 97, 98, 102,
		 104, 106, 106, 109, 109, 108},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 41, 69, 92, 41, 63, 88, 103, 69, 88, 127, 140, 92, 103, 140, 184,
		 /* Size 8x8 */
		 32, 32, 37, 47, 62, 78, 90, 102, 32, 35, 39, 46, 58, 72, 84, 96, 37, 39,
		 51, 60, 71, 84, 93, 100, 47, 46, 60, 73, 87, 100, 106, 113, 62, 58, 71,
		 87, 105, 121, 129, 132, 78, 72, 84, 100, 121, 140, 148, 155, 90, 84, 93,
		 106, 129, 148, 169, 183, 102, 96, 100, 113, 132, 155, 183, 201,
		 /* Size 16x16 */
		 32, 31, 31, 32, 36, 39, 47, 54, 61, 71, 80, 86, 92, 98, 104, 111, 31,

		 32, 32, 33, 34, 37, 44, 50, 56, 65, 73, 79, 85, 91, 98, 105, 31, 32, 33,
		 34, 36, 39, 45, 50, 56, 64, 71, 77, 82, 88, 94, 100, 32, 33, 34, 36, 40,
		 42, 47, 51, 57, 65, 71, 76, 80, 85, 91, 98, 36, 34, 36, 40, 48, 50, 56,
		 60, 65, 73, 79, 84, 86, 90, 95, 98, 39, 37, 39, 42, 50, 54, 60, 65, 70,
		 78, 84, 89, 95, 96, 102, 105, 47, 44, 45, 47, 56, 60, 69, 75, 81, 89,
		 95, 100, 102, 104, 109, 112, 54, 50, 50, 51, 60, 65, 75, 82, 89, 97,
		 104, 109, 110, 114, 117, 121, 61, 56, 56, 57, 65, 70, 81, 89, 97, 106,
		 113, 119, 122, 126, 125, 130, 71, 65, 64, 65, 73, 78, 89, 97, 106, 117,
		 125, 131, 134, 134, 136, 141, 80, 73, 71, 71, 79, 84, 95, 104, 113, 125,
		 134, 140, 142, 145, 146, 152, 86, 79, 77, 76, 84, 89, 100, 109, 119,
		 131, 140, 147, 154, 157, 160, 165, 92, 85, 82, 80, 86, 95, 102, 110,
		 122, 134, 142, 154, 162, 168, 174, 178, 98, 91, 88, 85, 90, 96, 104,
		 114, 126, 134, 145, 157, 168, 176, 184, 193, 104, 98, 94, 91, 95, 102,
		 109, 117, 125, 136, 146, 160, 174, 184, 193, 201, 111, 105, 100, 98, 98,
		 105, 112, 121, 130, 141, 152, 165, 178, 193, 201, 210,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 32, 32, 34, 36, 38, 39, 44, 47, 49, 54, 59, 61, 65,
		 71, 76, 80, 83, 86, 89, 92, 95, 98, 101, 104, 108, 111, 114, 31, 32, 32,
		 32, 32, 32, 33, 34, 35, 37, 38, 42, 45, 47, 51, 56, 58, 62, 68, 72, 76,
		 78, 82, 85, 88, 90, 93, 96, 99, 102, 105, 109, 31, 32, 32, 32, 32, 32,
		 33, 33, 34, 36, 37, 41, 44, 46, 50, 54, 56, 60, 65, 70, 73, 76, 79, 82,
		 85, 88, 91, 95, 98, 101, 105, 109, 31, 32, 32, 32, 32, 33, 33, 34, 35,
		 36, 38, 41, 44, 45, 49, 54, 56, 59, 65, 69, 72, 75, 78, 81, 84, 86, 89,
		 92, 95, 98, 101, 104, 31, 32, 32, 32, 33, 34, 34, 35, 36, 38, 39, 42,
		 45, 46, 50, 54, 56, 59, 64, 68, 71, 74, 77, 79, 82, 85, 88, 91, 94, 97,
		 100, 104, 32, 32, 32, 33, 34, 35, 36, 37, 38, 39, 40, 42, 45, 46, 49,
		 53, 55, 58, 63, 66, 69, 72, 74, 78, 81, 84, 87, 90, 93, 96, 99, 102, 32,
		 33, 33, 33, 34, 36, 36, 38, 40, 41, 42, 44, 47, 48, 51, 55, 57, 60, 65,
		 68, 71, 73, 76, 78, 80, 82, 85, 88, 91, 95, 98, 102, 34, 34, 33, 34, 35,
		 37, 38, 39, 42, 44, 45, 47, 50, 51, 54, 58, 60, 63, 68, 71, 74, 76, 79,
		 82, 85, 86, 87, 88, 90, 93, 96, 99, 36, 35, 34, 35, 36, 38, 40, 42, 48,
		 50, 50, 54, 56, 57, 60, 64, 65, 68, 73, 76, 79, 81, 84, 86, 86, 88, 90,
		 93, 95, 97, 98, 100, 38, 37, 36, 36, 38, 39, 41, 44, 50, 51, 52, 56, 58,
		 60, 63, 67, 68, 71, 76, 79, 82, 84, 87, 87, 90, 93, 94, 95, 96, 100,
		 103, 106, 39, 38, 37, 38, 39, 40, 42, 45, 50, 52, 54, 58, 60, 62, 65,
		 69, 70, 73, 78, 81, 84, 86, 89, 92, 95, 95, 96, 99, 102, 104, 105, 106,
		 44, 42, 41, 41, 42, 42, 44, 47, 54, 56, 58, 63, 66, 68, 71, 75, 77, 79,
		 84, 88, 90, 92, 95, 97, 97, 99, 102, 103, 103, 106, 109, 113, 47, 45,
		 44, 44, 45, 45, 47, 50, 56, 58, 60, 66, 69, 71, 75, 79, 81, 84, 89, 92,
		 95, 97, 100, 100, 102, 105, 104, 106, 109, 111, 112, 113, 49, 47, 46,
		 45, 46, 46, 48, 51, 57, 60, 62, 68, 71, 73, 77, 81, 83, 87, 92, 95, 98,
		 100, 103, 105, 107, 106, 109, 112, 112, 113, 117, 120, 54, 51, 50, 49,
		 50, 49, 51, 54, 60, 63, 65, 71, 75, 77, 82, 87, 89, 92, 97, 101, 104,
		 106, 109, 112, 110, 113, 114, 114, 117, 121, 121, 121, 59, 56, 54, 54,
		 54, 53, 55, 58, 64, 67, 69, 75, 79, 81, 87, 92, 94, 98, 103, 107, 110,
		 113, 116, 114, 117, 118, 117, 121, 122, 122, 125, 129, 61, 58, 56, 56,
		 56, 55, 57, 60, 65, 68, 70, 77, 81, 83, 89, 94, 97, 101, 106, 110, 113,
		 116, 119, 120, 122, 121, 126, 124, 125, 130, 130, 130, 65, 62, 60, 59,
		 59, 58, 60, 63, 68, 71, 73, 79, 84, 87, 92, 98, 101, 105, 111, 115, 118,
		 121, 124, 128, 125, 129, 128, 131, 133, 132, 135, 139, 71, 68, 65, 65,

		 64, 63, 65, 68, 73, 76, 78, 84, 89, 92, 97, 103, 106, 111, 117, 122,
		 125, 128, 131, 131, 134, 132, 134, 136, 136, 140, 141, 140, 76, 72, 70,
		 69, 68, 66, 68, 71, 76, 79, 81, 88, 92, 95, 101, 107, 110, 115, 122,
		 127, 130, 133, 136, 136, 138, 139, 141, 140, 145, 143, 146, 151, 80, 76,
		 73, 72, 71, 69, 71, 74, 79, 82, 84, 90, 95, 98, 104, 110, 113, 118, 125,
		 130, 134, 137, 140, 146, 142, 146, 145, 149, 146, 150, 152, 151, 83, 78,
		 76, 75, 74, 72, 73, 76, 81, 84, 86, 92, 97, 100, 106, 113, 116, 121,
		 128, 133, 137, 140, 144, 147, 152, 148, 154, 151, 156, 155, 156, 162,
		 86, 82, 79, 78, 77, 74, 76, 79, 84, 87, 89, 95, 100, 103, 109, 116, 119,
		 124, 131, 136, 140, 144, 147, 150, 154, 159, 157, 160, 160, 162, 165,
		 162, 89, 85, 82, 81, 79, 78, 78, 82, 86, 87, 92, 97, 100, 105, 112, 114,
		 120, 128, 131, 136, 146, 147, 150, 155, 156, 161, 166, 165, 167, 169,
		 169, 175, 92, 88, 85, 84, 82, 81, 80, 85, 86, 90, 95, 97, 102, 107, 110,
		 117, 122, 125, 134, 138, 142, 152, 154, 156, 162, 163, 168, 173, 174,
		 174, 178, 176, 95, 90, 88, 86, 85, 84, 82, 86, 88, 93, 95, 99, 105, 106,
		 113, 118, 121, 129, 132, 139, 146, 148, 159, 161, 163, 169, 170, 176,
		 180, 183, 181, 187, 98, 93, 91, 89, 88, 87, 85, 87, 90, 94, 96, 102,
		 104, 109, 114, 117, 126, 128, 134, 141, 145, 154, 157, 166, 168, 170,
		 176, 178, 184, 188, 193, 188, 101, 96, 95, 92, 91, 90, 88, 88, 93, 95,
		 99, 103, 106, 112, 114, 121, 124, 131, 136, 140, 149, 151, 160, 165,
		 173, 176, 178, 184, 186, 192, 196, 203, 104, 99, 98, 95, 94, 93, 91, 90,
		 95, 96, 102, 103, 109, 112, 117, 122, 125, 133, 136, 145, 146, 156, 160,
		 167, 174, 180, 184, 186, 193, 194, 201, 204, 108, 102, 101, 98, 97, 96,
		 95, 93, 97, 100, 104, 106, 111, 113, 121, 122, 130, 132, 140, 143, 150,
		 155, 162, 169, 174, 183, 188, 192, 194, 201, 202, 210, 111, 105, 105,
		 101, 100, 99, 98, 96, 98, 103, 105, 109, 112, 117, 121, 125, 130, 135,
		 141, 146, 152, 156, 165, 169, 178, 181, 193, 196, 201, 202, 210, 211,
		 114, 109, 109, 104, 104, 102, 102, 99, 100, 106, 106, 113, 113, 120,
		 121, 129, 130, 139, 140, 151, 151, 162, 162, 175, 176, 187, 188, 203,
		 204, 210, 211, 219,
		 /* Size 4x8 */
		 32, 42, 69, 88, 33, 42, 64, 83, 36, 56, 77, 88, 46, 67, 93, 105, 60, 79,
		 112, 122, 75, 92, 130, 144, 86, 95, 136, 167, 98, 105, 136, 177,
		 /* Size 8x4 */
		 32, 33, 36, 46, 60, 75, 86, 98, 42, 42, 56, 67, 79, 92, 95, 105, 69, 64,
		 77, 93, 112, 130, 136, 136, 88, 83, 88, 105, 122, 144, 167, 177,
		 /* Size 8x16 */
		 32, 32, 36, 47, 65, 79, 90, 96, 31, 32, 35, 44, 60, 72, 84, 90, 32, 34,
		 36, 45, 59, 71, 80, 87, 32, 35, 40, 47, 60, 71, 78, 85, 36, 37, 48, 56,
		 68, 78, 83, 87, 39, 40, 50, 60, 73, 84, 91, 94, 47, 45, 56, 69, 84, 95,
		 101, 101, 53, 50, 60, 75, 92, 103, 108, 110, 61, 56, 65, 81, 100, 113,
		 116, 118, 71, 64, 73, 89, 111, 125, 129, 129, 79, 70, 79, 95, 118, 133,
		 142, 138, 86, 76, 84, 100, 124, 140, 153, 150, 92, 82, 89, 101, 121,
		 148, 157, 161, 98, 88, 93, 108, 124, 141, 163, 174, 104, 94, 95, 110,
		 129, 151, 171, 181, 110, 100, 98, 111, 127, 147, 169, 188,
		 /* Size 16x8 */
		 32, 31, 32, 32, 36, 39, 47, 53, 61, 71, 79, 86, 92, 98, 104, 110, 32,
		 32, 34, 35, 37, 40, 45, 50, 56, 64, 70, 76, 82, 88, 94, 100, 36, 35, 36,
		 40, 48, 50, 56, 60, 65, 73, 79, 84, 89, 93, 95, 98, 47, 44, 45, 47, 56,
		 60, 69, 75, 81, 89, 95, 100, 101, 108, 110, 111, 65, 60, 59, 60, 68, 73,

		 84, 92, 100, 111, 118, 124, 121, 124, 129, 127, 79, 72, 71, 71, 78, 84,
		 95, 103, 113, 125, 133, 140, 148, 141, 151, 147, 90, 84, 80, 78, 83, 91,
		 101, 108, 116, 129, 142, 153, 157, 163, 171, 169, 96, 90, 87, 85, 87,
		 94, 101, 110, 118, 129, 138, 150, 161, 174, 181, 188,
		 /* Size 16x32 */
		 32, 31, 32, 32, 36, 44, 47, 53, 65, 73, 79, 87, 90, 93, 96, 99, 31, 32,
		 32, 33, 35, 42, 45, 51, 62, 69, 75, 83, 86, 88, 91, 94, 31, 32, 32, 33,
		 35, 41, 44, 49, 60, 67, 72, 80, 84, 87, 90, 94, 31, 32, 33, 33, 35, 41,
		 44, 49, 59, 66, 71, 79, 82, 84, 87, 90, 32, 32, 34, 34, 36, 42, 45, 50,
		 59, 65, 71, 78, 80, 83, 87, 90, 32, 33, 35, 36, 38, 42, 45, 49, 58, 64,
		 69, 76, 80, 83, 86, 88, 32, 33, 35, 36, 40, 44, 47, 51, 60, 66, 71, 76,
		 78, 81, 85, 89, 34, 34, 36, 38, 42, 48, 50, 54, 63, 69, 73, 80, 82, 81,
		 84, 86, 36, 34, 37, 40, 48, 54, 56, 60, 68, 74, 78, 84, 83, 86, 87, 87,
		 38, 36, 39, 41, 49, 56, 58, 63, 71, 77, 81, 86, 88, 88, 90, 93, 39, 37,
		 40, 42, 50, 58, 60, 65, 73, 79, 84, 90, 91, 92, 94, 93, 44, 41, 42, 45,
		 53, 63, 66, 71, 79, 85, 90, 96, 94, 96, 96, 99, 47, 44, 45, 47, 56, 66,
		 69, 75, 84, 90, 95, 99, 101, 98, 101, 99, 49, 46, 47, 48, 57, 67, 71,
		 77, 86, 93, 97, 103, 103, 105, 102, 106, 53, 49, 50, 51, 60, 71, 75, 82,
		 92, 99, 103, 111, 108, 107, 110, 107, 58, 54, 54, 55, 63, 75, 79, 87,
		 98, 105, 110, 114, 114, 113, 111, 115, 61, 56, 56, 57, 65, 77, 81, 89,
		 100, 107, 113, 118, 116, 117, 118, 116, 65, 60, 59, 60, 68, 79, 84, 92,
		 105, 112, 118, 126, 124, 122, 121, 124, 71, 65, 64, 65, 73, 84, 89, 97,
		 111, 119, 125, 130, 129, 129, 129, 125, 76, 69, 68, 69, 76, 88, 92, 101,
		 115, 123, 130, 134, 134, 131, 132, 135, 79, 72, 70, 71, 79, 90, 95, 104,
		 118, 127, 133, 143, 142, 141, 138, 136, 82, 75, 73, 74, 81, 92, 97, 106,
		 121, 130, 136, 146, 145, 144, 144, 145, 86, 78, 76, 77, 84, 95, 100,
		 109, 124, 133, 140, 147, 153, 151, 150, 146, 89, 81, 79, 78, 87, 95, 99,
		 112, 124, 130, 145, 152, 156, 157, 156, 158, 92, 84, 82, 80, 89, 95,
		 101, 116, 121, 132, 148, 151, 157, 163, 161, 159, 95, 86, 85, 83, 92,
		 95, 105, 114, 120, 136, 143, 155, 163, 167, 171, 170, 98, 89, 88, 85,
		 93, 95, 108, 113, 124, 136, 141, 160, 163, 169, 174, 171, 101, 92, 91,
		 88, 94, 98, 110, 112, 128, 133, 146, 158, 166, 175, 179, 185, 104, 95,
		 94, 91, 95, 101, 110, 115, 129, 132, 151, 154, 171, 175, 181, 186, 107,
		 98, 97, 94, 96, 105, 110, 119, 128, 136, 149, 156, 173, 177, 188, 192,
		 110, 101, 100, 97, 98, 108, 111, 123, 127, 141, 147, 161, 169, 183, 188,
		 193, 114, 104, 104, 100, 100, 111, 111, 126, 127, 145, 145, 166, 166,
		 189, 190, 201,
		 /* Size 32x16 */
		 32, 31, 31, 31, 32, 32, 32, 34, 36, 38, 39, 44, 47, 49, 53, 58, 61, 65,
		 71, 76, 79, 82, 86, 89, 92, 95, 98, 101, 104, 107, 110, 114, 31, 32, 32,
		 32, 32, 33, 33, 34, 34, 36, 37, 41, 44, 46, 49, 54, 56, 60, 65, 69, 72,
		 75, 78, 81, 84, 86, 89, 92, 95, 98, 101, 104, 32, 32, 32, 33, 34, 35,
		 35, 36, 37, 39, 40, 42, 45, 47, 50, 54, 56, 59, 64, 68, 70, 73, 76, 79,
		 82, 85, 88, 91, 94, 97, 100, 104, 32, 33, 33, 33, 34, 36, 36, 38, 40,
		 41, 42, 45, 47, 48, 51, 55, 57, 60, 65, 69, 71, 74, 77, 78, 80, 83, 85,
		 88, 91, 94, 97, 100, 36, 35, 35, 35, 36, 38, 40, 42, 48, 49, 50, 53, 56,
		 57, 60, 63, 65, 68, 73, 76, 79, 81, 84, 87, 89, 92, 93, 94, 95, 96, 98,
		 100, 44, 42, 41, 41, 42, 42, 44, 48, 54, 56, 58, 63, 66, 67, 71, 75, 77,
		 79, 84, 88, 90, 92, 95, 95, 95, 95, 95, 98, 101, 105, 108, 111, 47, 45,
		 44, 44, 45, 45, 47, 50, 56, 58, 60, 66, 69, 71, 75, 79, 81, 84, 89, 92,

		 95, 97, 100, 99, 101, 105, 108, 110, 110, 110, 111, 111, 53, 51, 49, 49,
		 50, 49, 51, 54, 60, 63, 65, 71, 75, 77, 82, 87, 89, 92, 97, 101, 104,
		 106, 109, 112, 116, 114, 113, 112, 115, 119, 123, 126, 65, 62, 60, 59,
		 59, 58, 60, 63, 68, 71, 73, 79, 84, 86, 92, 98, 100, 105, 111, 115, 118,
		 121, 124, 124, 121, 120, 124, 128, 129, 128, 127, 127, 73, 69, 67, 66,
		 65, 64, 66, 69, 74, 77, 79, 85, 90, 93, 99, 105, 107, 112, 119, 123,
		 127, 130, 133, 130, 132, 136, 136, 133, 132, 136, 141, 145, 79, 75, 72,
		 71, 71, 69, 71, 73, 78, 81, 84, 90, 95, 97, 103, 110, 113, 118, 125,
		 130, 133, 136, 140, 145, 148, 143, 141, 146, 151, 149, 147, 145, 87, 83,
		 80, 79, 78, 76, 76, 80, 84, 86, 90, 96, 99, 103, 111, 114, 118, 126,
		 130, 134, 143, 146, 147, 152, 151, 155, 160, 158, 154, 156, 161, 166,
		 90, 86, 84, 82, 80, 80, 78, 82, 83, 88, 91, 94, 101, 103, 108, 114, 116,
		 124, 129, 134, 142, 145, 153, 156, 157, 163, 163, 166, 171, 173, 169,
		 166, 93, 88, 87, 84, 83, 83, 81, 81, 86, 88, 92, 96, 98, 105, 107, 113,
		 117, 122, 129, 131, 141, 144, 151, 157, 163, 167, 169, 175, 175, 177,
		 183, 189, 96, 91, 90, 87, 87, 86, 85, 84, 87, 90, 94, 96, 101, 102, 110,
		 111, 118, 121, 129, 132, 138, 144, 150, 156, 161, 171, 174, 179, 181,
		 188, 188, 190, 99, 94, 94, 90, 90, 88, 89, 86, 87, 93, 93, 99, 99, 106,
		 107, 115, 116, 124, 125, 135, 136, 145, 146, 158, 159, 170, 171, 185,
		 186, 192, 193, 201,
		 /* Size 4x16 */
		 31, 44, 73, 93, 32, 41, 67, 87, 32, 42, 65, 83, 33, 44, 66, 81, 34, 54,
		 74, 86, 37, 58, 79, 92, 44, 66, 90, 98, 49, 71, 99, 107, 56, 77, 107,
		 117, 65, 84, 119, 129, 72, 90, 127, 141, 78, 95, 133, 151, 84, 95, 132,
		 163, 89, 95, 136, 169, 95, 101, 132, 175, 101, 108, 141, 183,
		 /* Size 16x4 */
		 31, 32, 32, 33, 34, 37, 44, 49, 56, 65, 72, 78, 84, 89, 95, 101, 44, 41,
		 42, 44, 54, 58, 66, 71, 77, 84, 90, 95, 95, 95, 101, 108, 73, 67, 65,
		 66, 74, 79, 90, 99, 107, 119, 127, 133, 132, 136, 132, 141, 93, 87, 83,
		 81, 86, 92, 98, 107, 117, 129, 141, 151, 163, 169, 175, 183,
		 /* Size 8x32 */
		 32, 32, 36, 47, 65, 79, 90, 96, 31, 32, 35, 45, 62, 75, 86, 91, 31, 32,
		 35, 44, 60, 72, 84, 90, 31, 33, 35, 44, 59, 71, 82, 87, 32, 34, 36, 45,
		 59, 71, 80, 87, 32, 35, 38, 45, 58, 69, 80, 86, 32, 35, 40, 47, 60, 71,
		 78, 85, 34, 36, 42, 50, 63, 73, 82, 84, 36, 37, 48, 56, 68, 78, 83, 87,
		 38, 39, 49, 58, 71, 81, 88, 90, 39, 40, 50, 60, 73, 84, 91, 94, 44, 42,
		 53, 66, 79, 90, 94, 96, 47, 45, 56, 69, 84, 95, 101, 101, 49, 47, 57,
		 71, 86, 97, 103, 102, 53, 50, 60, 75, 92, 103, 108, 110, 58, 54, 63, 79,
		 98, 110, 114, 111, 61, 56, 65, 81, 100, 113, 116, 118, 65, 59, 68, 84,
		 105, 118, 124, 121, 71, 64, 73, 89, 111, 125, 129, 129, 76, 68, 76, 92,
		 115, 130, 134, 132, 79, 70, 79, 95, 118, 133, 142, 138, 82, 73, 81, 97,
		 121, 136, 145, 144, 86, 76, 84, 100, 124, 140, 153, 150, 89, 79, 87, 99,
		 124, 145, 156, 156, 92, 82, 89, 101, 121, 148, 157, 161, 95, 85, 92,
		 105, 120, 143, 163, 171, 98, 88, 93, 108, 124, 141, 163, 174, 101, 91,
		 94, 110, 128, 146, 166, 179, 104, 94, 95, 110, 129, 151, 171, 181, 107,
		 97, 96, 110, 128, 149, 173, 188, 110, 100, 98, 111, 127, 147, 169, 188,
		 114, 104, 100, 111, 127, 145, 166, 190,
		 /* Size 32x8 */
		 32, 31, 31, 31, 32, 32, 32, 34, 36, 38, 39, 44, 47, 49, 53, 58, 61, 65,
		 71, 76, 79, 82, 86, 89, 92, 95, 98, 101, 104, 107, 110, 114, 32, 32, 32,

		 33, 34, 35, 35, 36, 37, 39, 40, 42, 45, 47, 50, 54, 56, 59, 64, 68, 70,
		 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 104, 36, 35, 35, 35, 36, 38,
		 40, 42, 48, 49, 50, 53, 56, 57, 60, 63, 65, 68, 73, 76, 79, 81, 84, 87,
		 89, 92, 93, 94, 95, 96, 98, 100, 47, 45, 44, 44, 45, 45, 47, 50, 56, 58,
		 60, 66, 69, 71, 75, 79, 81, 84, 89, 92, 95, 97, 100, 99, 101, 105, 108,
		 110, 110, 110, 111, 111, 65, 62, 60, 59, 59, 58, 60, 63, 68, 71, 73, 79,
		 84, 86, 92, 98, 100, 105, 111, 115, 118, 121, 124, 124, 121, 120, 124,
		 128, 129, 128, 127, 127, 79, 75, 72, 71, 71, 69, 71, 73, 78, 81, 84, 90,
		 95, 97, 103, 110, 113, 118, 125, 130, 133, 136, 140, 145, 148, 143, 141,
		 146, 151, 149, 147, 145, 90, 86, 84, 82, 80, 80, 78, 82, 83, 88, 91, 94,
		 101, 103, 108, 114, 116, 124, 129, 134, 142, 145, 153, 156, 157, 163,
		 163, 166, 171, 173, 169, 166, 96, 91, 90, 87, 87, 86, 85, 84, 87, 90,
		 94, 96, 101, 102, 110, 111, 118, 121, 129, 132, 138, 144, 150, 156, 161,
		 171, 174, 179, 181, 188, 188, 190},
		{/* Chroma */
		 /* Size 4x4 */
		 33, 45, 56, 64, 45, 58, 66, 69, 56, 66, 86, 87, 64, 69, 87, 105,
		 /* Size 8x8 */
		 31, 38, 47, 48, 54, 61, 66, 69, 38, 47, 47, 46, 50, 55, 61, 65, 47, 47,
		 53, 55, 58, 63, 65, 66, 48, 46, 55, 62, 67, 72, 73, 73, 54, 50, 58, 67,
		 76, 83, 84, 82, 61, 55, 63, 72, 83, 91, 92, 92, 66, 61, 65, 73, 84, 92,
		 101, 103, 69, 65, 66, 73, 82, 92, 103, 109,
		 /* Size 16x16 */
		 32, 30, 33, 38, 49, 48, 50, 52, 55, 60, 63, 66, 68, 70, 72, 74, 30, 31,
		 35, 41, 46, 46, 46, 48, 51, 55, 58, 60, 63, 65, 68, 70, 33, 35, 39, 44,
		 47, 46, 46, 47, 50, 53, 56, 58, 60, 62, 65, 67, 38, 41, 44, 47, 49, 48,
		 47, 48, 50, 53, 55, 58, 58, 60, 62, 65, 49, 46, 47, 49, 53, 53, 54, 54,
		 56, 58, 60, 62, 62, 63, 64, 64, 48, 46, 46, 48, 53, 54, 56, 57, 59, 61,
		 63, 65, 67, 66, 68, 68, 50, 46, 46, 47, 54, 56, 61, 63, 65, 68, 70, 72,
		 71, 71, 72, 72, 52, 48, 47, 48, 54, 57, 63, 66, 69, 72, 75, 76, 75, 76,
		 76, 76, 55, 51, 50, 50, 56, 59, 65, 69, 73, 77, 79, 81, 81, 81, 80, 80,
		 60, 55, 53, 53, 58, 61, 68, 72, 77, 82, 85, 87, 87, 85, 84, 85, 63, 58,
		 56, 55, 60, 63, 70, 75, 79, 85, 89, 91, 91, 90, 89, 90, 66, 60, 58, 58,
		 62, 65, 72, 76, 81, 87, 91, 94, 96, 95, 95, 95, 68, 63, 60, 58, 62, 67,
		 71, 75, 81, 87, 91, 96, 99, 100, 100, 100, 70, 65, 62, 60, 63, 66, 71,
		 76, 81, 85, 90, 95, 100, 103, 104, 105, 72, 68, 65, 62, 64, 68, 72, 76,
		 80, 84, 89, 95, 100, 104, 107, 108, 74, 70, 67, 65, 64, 68, 72, 76, 80,
		 85, 90, 95, 100, 105, 108, 111,
		 /* Size 32x32 */
		 32, 31, 30, 31, 33, 36, 38, 41, 49, 49, 48, 49, 50, 51, 52, 54, 55, 57,
		 60, 62, 63, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 31, 31, 31, 32,
		 34, 38, 40, 42, 47, 47, 47, 47, 48, 48, 50, 52, 53, 54, 57, 59, 60, 61,
		 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 30, 31, 31, 32, 35, 39, 41, 42,
		 46, 46, 46, 45, 46, 47, 48, 50, 51, 52, 55, 57, 58, 59, 60, 62, 63, 64,
		 65, 67, 68, 69, 70, 71, 31, 32, 32, 33, 36, 40, 41, 43, 46, 46, 45, 45,
		 46, 46, 47, 49, 50, 51, 54, 56, 57, 58, 59, 61, 62, 63, 63, 64, 65, 66,
		 67, 68, 33, 34, 35, 36, 39, 43, 44, 45, 47, 46, 46, 45, 46, 47, 47, 49,
		 50, 51, 53, 55, 56, 57, 58, 59, 60, 61, 62, 63, 65, 66, 67, 68, 36, 38,
		 39, 40, 43, 47, 47, 47, 48, 47, 46, 45, 46, 46, 47, 48, 49, 50, 52, 53,
		 54, 55, 56, 58, 59, 61, 62, 63, 64, 65, 66, 66, 38, 40, 41, 41, 44, 47,
		 47, 48, 49, 48, 48, 47, 47, 47, 48, 49, 50, 51, 53, 54, 55, 56, 58, 58,
		 58, 59, 60, 61, 62, 64, 65, 66, 41, 42, 42, 43, 45, 47, 48, 48, 50, 50,
		 49, 49, 50, 50, 50, 52, 52, 53, 55, 56, 57, 58, 59, 60, 61, 61, 61, 61,
		 62, 63, 63, 64, 49, 47, 46, 46, 47, 48, 49, 50, 53, 53, 53, 53, 54, 54,
		 54, 55, 56, 56, 58, 59, 60, 61, 62, 63, 62, 62, 63, 64, 64, 64, 64, 64,
		 49, 47, 46, 46, 46, 47, 48, 50, 53, 53, 54, 55, 55, 55, 56, 57, 58, 58,
		 60, 61, 62, 63, 64, 64, 64, 65, 65, 65, 65, 66, 67, 68, 48, 47, 46, 45,
		 46, 46, 48, 49, 53, 54, 54, 55, 56, 56, 57, 58, 59, 60, 61, 63, 63, 64,
		 65, 66, 67, 66, 66, 67, 68, 68, 68, 68, 49, 47, 45, 45, 45, 45, 47, 49,
		 53, 55, 55, 58, 59, 60, 61, 62, 63, 63, 65, 66, 67, 68, 69, 69, 68, 68,
		 69, 69, 69, 69, 70, 71, 50, 48, 46, 46, 46, 46, 47, 50, 54, 55, 56, 59,
		 61, 61, 63, 64, 65, 66, 68, 69, 70, 71, 72, 71, 71, 72, 71, 71, 72, 72,
		 72, 71, 51, 48, 47, 46, 47, 46, 47, 50, 54, 55, 56, 60, 61, 62, 64, 66,
		 66, 67, 69, 70, 71, 72, 73, 73, 74, 73, 73, 74, 73, 73, 74, 75, 52, 50,
		 48, 47, 47, 47, 48, 50, 54, 56, 57, 61, 63, 64, 66, 68, 69, 70, 72, 74,
		 75, 75, 76, 77, 75, 76, 76, 75, 76, 77, 76, 75, 54, 52, 50, 49, 49, 48,
		 49, 52, 55, 57, 58, 62, 64, 66, 68, 71, 72, 73, 75, 77, 78, 79, 80, 78,
		 79, 78, 77, 78, 78, 77, 78, 79, 55, 53, 51, 50, 50, 49, 50, 52, 56, 58,
		 59, 63, 65, 66, 69, 72, 73, 74, 77, 78, 79, 80, 81, 81, 81, 80, 81, 80,
		 80, 81, 80, 79, 57, 54, 52, 51, 51, 50, 51, 53, 56, 58, 60, 63, 66, 67,
		 70, 73, 74, 76, 79, 80, 82, 83, 84, 85, 83, 84, 83, 83, 83, 82, 82, 83,
		 60, 57, 55, 54, 53, 52, 53, 55, 58, 60, 61, 65, 68, 69, 72, 75, 77, 79,
		 82, 84, 85, 86, 87, 86, 87, 85, 85, 85, 84, 86, 85, 84, 62, 59, 57, 56,
		 55, 53, 54, 56, 59, 61, 63, 66, 69, 70, 74, 77, 78, 80, 84, 86, 87, 88,
		 90, 89, 89, 88, 88, 87, 88, 87, 87, 88, 63, 60, 58, 57, 56, 54, 55, 57,
		 60, 62, 63, 67, 70, 71, 75, 78, 79, 82, 85, 87, 89, 90, 91, 93, 91, 91,
		 90, 91, 89, 90, 90, 89, 65, 61, 59, 58, 57, 55, 56, 58, 61, 63, 64, 68,
		 71, 72, 75, 79, 80, 83, 86, 88, 90, 91, 93, 94, 95, 92, 94, 92, 93, 92,
		 91, 93, 66, 63, 60, 59, 58, 56, 58, 59, 62, 64, 65, 69, 72, 73, 76, 80,
		 81, 84, 87, 90, 91, 93, 94, 95, 96, 97, 95, 95, 95, 95, 95, 93, 67, 64,
		 62, 61, 59, 58, 58, 60, 63, 64, 66, 69, 71, 73, 77, 78, 81, 85, 86, 89,
		 93, 94, 95, 97, 97, 98, 99, 97, 97, 97, 96, 98, 68, 65, 63, 62, 60, 59,
		 58, 61, 62, 64, 67, 68, 71, 74, 75, 79, 81, 83, 87, 89, 91, 95, 96, 97,
		 99, 98, 100, 100, 100, 99, 100, 98, 69, 66, 64, 63, 61, 61, 59, 61, 62,
		 65, 66, 68, 72, 73, 76, 78, 80, 84, 85, 88, 91, 92, 97, 98, 98, 101,
		 100, 102, 102, 103, 101, 102, 70, 67, 65, 63, 62, 62, 60, 61, 63, 65,
		 66, 69, 71, 73, 76, 77, 81, 83, 85, 88, 90, 94, 95, 99, 100, 100, 103,
		 102, 104, 104, 105, 103, 71, 67, 67, 64, 63, 63, 61, 61, 64, 65, 67, 69,
		 71, 74, 75, 78, 80, 83, 85, 87, 91, 92, 95, 97, 100, 102, 102, 105, 104,
		 106, 106, 108, 72, 68, 68, 65, 65, 64, 62, 62, 64, 65, 68, 69, 72, 73,
		 76, 78, 80, 83, 84, 88, 89, 93, 95, 97, 100, 102, 104, 104, 107, 106,
		 108, 108, 73, 69, 69, 66, 66, 65, 64, 63, 64, 66, 68, 69, 72, 73, 77,
		 77, 81, 82, 86, 87, 90, 92, 95, 97, 99, 103, 104, 106, 106, 109, 108,
		 110, 74, 70, 70, 67, 67, 66, 65, 63, 64, 67, 68, 70, 72, 74, 76, 78, 80,
		 82, 85, 87, 90, 91, 95, 96, 100, 101, 105, 106, 108, 108, 111, 110, 75,
		 71, 71, 68, 68, 66, 66, 64, 64, 68, 68, 71, 71, 75, 75, 79, 79, 83, 84,
		 88, 89, 93, 93, 98, 98, 102, 103, 108, 108, 110, 110, 113,
		 /* Size 4x8 */
		 31, 47, 57, 65, 40, 45, 52, 61, 46, 55, 61, 63, 47, 60, 70, 72, 52, 64,
		 79, 81, 59, 68, 87, 90, 63, 66, 88, 99, 66, 69, 85, 102,
		 /* Size 8x4 */
		 31, 40, 46, 47, 52, 59, 63, 66, 47, 45, 55, 60, 64, 68, 66, 69, 57, 52,
		 61, 70, 79, 87, 88, 85, 65, 61, 63, 72, 81, 90, 99, 102,
		 /* Size 8x16 */
		 32, 35, 48, 50, 57, 63, 68, 70, 30, 38, 46, 46, 52, 58, 63, 65, 33, 41,
		 47, 46, 51, 56, 60, 63, 39, 46, 48, 47, 51, 55, 58, 61, 49, 48, 53, 54,
		 57, 60, 61, 61, 48, 46, 53, 56, 60, 64, 65, 65, 50, 46, 54, 61, 66, 70,
		 71, 69, 52, 47, 54, 63, 71, 75, 75, 74, 55, 49, 56, 65, 74, 79, 79, 78,
		 60, 53, 58, 68, 79, 85, 85, 82, 63, 55, 60, 70, 82, 89, 91, 87, 66, 58,
		 62, 72, 84, 91, 95, 91, 68, 60, 64, 71, 81, 94, 97, 96, 70, 62, 65, 73,
		 81, 89, 98, 101, 72, 65, 65, 72, 82, 92, 100, 103, 74, 67, 65, 71, 79,
		 89, 98, 105,
		 /* Size 16x8 */
		 32, 30, 33, 39, 49, 48, 50, 52, 55, 60, 63, 66, 68, 70, 72, 74, 35, 38,
		 41, 46, 48, 46, 46, 47, 49, 53, 55, 58, 60, 62, 65, 67, 48, 46, 47, 48,
		 53, 53, 54, 54, 56, 58, 60, 62, 64, 65, 65, 65, 50, 46, 46, 47, 54, 56,
		 61, 63, 65, 68, 70, 72, 71, 73, 72, 71, 57, 52, 51, 51, 57, 60, 66, 71,
		 74, 79, 82, 84, 81, 81, 82, 79, 63, 58, 56, 55, 60, 64, 70, 75, 79, 85,
		 89, 91, 94, 89, 92, 89, 68, 63, 60, 58, 61, 65, 71, 75, 79, 85, 91, 95,
		 97, 98, 100, 98, 70, 65, 63, 61, 61, 65, 69, 74, 78, 82, 87, 91, 96,
		 101, 103, 105,
		 /* Size 16x32 */
		 32, 31, 35, 38, 48, 49, 50, 52, 57, 61, 63, 67, 68, 69, 70, 71, 31, 31,
		 37, 40, 47, 47, 48, 50, 54, 57, 60, 63, 64, 65, 66, 67, 30, 32, 38, 40,
		 46, 45, 46, 48, 52, 55, 58, 61, 63, 64, 65, 67, 31, 33, 38, 41, 46, 45,
		 46, 48, 52, 55, 57, 60, 61, 62, 63, 64, 33, 36, 41, 44, 47, 46, 46, 47,
		 51, 54, 56, 59, 60, 61, 63, 64, 37, 40, 45, 47, 47, 45, 46, 47, 50, 52,
		 54, 57, 59, 61, 62, 62, 39, 41, 46, 47, 48, 47, 47, 48, 51, 54, 55, 57,
		 58, 59, 61, 62, 42, 43, 46, 48, 50, 49, 50, 50, 53, 56, 57, 60, 60, 59,
		 60, 60, 49, 46, 48, 49, 53, 53, 54, 54, 57, 59, 60, 63, 61, 62, 61, 61,
		 48, 46, 47, 48, 53, 55, 55, 56, 58, 61, 62, 64, 64, 63, 63, 64, 48, 46,
		 46, 48, 53, 56, 56, 57, 60, 62, 64, 66, 65, 65, 65, 64, 49, 45, 45, 47,
		 53, 58, 59, 61, 64, 66, 67, 69, 67, 67, 66, 67, 50, 46, 46, 48, 54, 59,
		 61, 63, 66, 68, 70, 71, 71, 68, 69, 67, 51, 47, 47, 48, 54, 60, 61, 64,
		 68, 70, 71, 73, 72, 72, 70, 71, 52, 48, 47, 48, 54, 61, 63, 66, 71, 73,
		 75, 77, 75, 73, 74, 71, 54, 50, 49, 50, 55, 62, 65, 68, 73, 76, 78, 79,
		 78, 76, 74, 75, 55, 51, 49, 50, 56, 63, 65, 69, 74, 77, 79, 81, 79, 78,
		 78, 75, 57, 52, 50, 51, 56, 64, 66, 70, 76, 79, 82, 85, 83, 81, 79, 79,
		 60, 54, 53, 53, 58, 65, 68, 72, 79, 82, 85, 87, 85, 84, 82, 80, 62, 56,
		 54, 55, 60, 66, 69, 74, 81, 84, 87, 88, 87, 85, 84, 84, 63, 57, 55, 56,
		 60, 67, 70, 75, 82, 86, 89, 92, 91, 89, 87, 84, 64, 59, 56, 57, 61, 68,
		 71, 75, 83, 87, 90, 93, 92, 90, 89, 89, 66, 60, 58, 58, 62, 69, 72, 76,
		 84, 88, 91, 94, 95, 93, 91, 89, 67, 61, 59, 58, 63, 68, 71, 78, 83, 86,
		 93, 96, 96, 96, 94, 94, 68, 62, 60, 59, 64, 67, 71, 79, 81, 86, 94, 95,
		 97, 98, 96, 94, 69, 63, 61, 60, 65, 66, 72, 77, 80, 88, 91, 96, 99, 99,
		 100, 98, 70, 64, 62, 60, 65, 66, 73, 76, 81, 87, 89, 97, 98, 100, 101,
		 99, 71, 65, 64, 61, 65, 67, 73, 74, 82, 85, 90, 95, 99, 102, 103, 104,
		 72, 65, 65, 62, 65, 68, 72, 75, 82, 83, 92, 93, 100, 102, 103, 104, 73,
		 66, 66, 63, 65, 69, 72, 76, 81, 85, 90, 93, 100, 102, 105, 106, 74, 67,
		 67, 64, 65, 70, 71, 77, 79, 86, 89, 94, 98, 103, 105, 106, 75, 68, 68,
		 65, 65, 71, 71, 78, 78, 87, 87, 96, 96, 105, 105, 109,
		 /* Size 32x16 */
		 32, 31, 30, 31, 33, 37, 39, 42, 49, 48, 48, 49, 50, 51, 52, 54, 55, 57,
		 60, 62, 63, 64, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 31, 31, 32, 33,
		 36, 40, 41, 43, 46, 46, 46, 45, 46, 47, 48, 50, 51, 52, 54, 56, 57, 59,
		 60, 61, 62, 63, 64, 65, 65, 66, 67, 68, 35, 37, 38, 38, 41, 45, 46, 46,
		 48, 47, 46, 45, 46, 47, 47, 49, 49, 50, 53, 54, 55, 56, 58, 59, 60, 61,
		 62, 64, 65, 66, 67, 68, 38, 40, 40, 41, 44, 47, 47, 48, 49, 48, 48, 47,
		 48, 48, 48, 50, 50, 51, 53, 55, 56, 57, 58, 58, 59, 60, 60, 61, 62, 63,
		 64, 65, 48, 47, 46, 46, 47, 47, 48, 50, 53, 53, 53, 53, 54, 54, 54, 55,
		 56, 56, 58, 60, 60, 61, 62, 63, 64, 65, 65, 65, 65, 65, 65, 65, 49, 47,
		 45, 45, 46, 45, 47, 49, 53, 55, 56, 58, 59, 60, 61, 62, 63, 64, 65, 66,
		 67, 68, 69, 68, 67, 66, 66, 67, 68, 69, 70, 71, 50, 48, 46, 46, 46, 46,
		 47, 50, 54, 55, 56, 59, 61, 61, 63, 65, 65, 66, 68, 69, 70, 71, 72, 71,
		 71, 72, 73, 73, 72, 72, 71, 71, 52, 50, 48, 48, 47, 47, 48, 50, 54, 56,
		 57, 61, 63, 64, 66, 68, 69, 70, 72, 74, 75, 75, 76, 78, 79, 77, 76, 74,
		 75, 76, 77, 78, 57, 54, 52, 52, 51, 50, 51, 53, 57, 58, 60, 64, 66, 68,
		 71, 73, 74, 76, 79, 81, 82, 83, 84, 83, 81, 80, 81, 82, 82, 81, 79, 78,
		 61, 57, 55, 55, 54, 52, 54, 56, 59, 61, 62, 66, 68, 70, 73, 76, 77, 79,
		 82, 84, 86, 87, 88, 86, 86, 88, 87, 85, 83, 85, 86, 87, 63, 60, 58, 57,
		 56, 54, 55, 57, 60, 62, 64, 67, 70, 71, 75, 78, 79, 82, 85, 87, 89, 90,
		 91, 93, 94, 91, 89, 90, 92, 90, 89, 87, 67, 63, 61, 60, 59, 57, 57, 60,
		 63, 64, 66, 69, 71, 73, 77, 79, 81, 85, 87, 88, 92, 93, 94, 96, 95, 96,
		 97, 95, 93, 93, 94, 96, 68, 64, 63, 61, 60, 59, 58, 60, 61, 64, 65, 67,
		 71, 72, 75, 78, 79, 83, 85, 87, 91, 92, 95, 96, 97, 99, 98, 99, 100,
		 100, 98, 96, 69, 65, 64, 62, 61, 61, 59, 59, 62, 63, 65, 67, 68, 72, 73,
		 76, 78, 81, 84, 85, 89, 90, 93, 96, 98, 99, 100, 102, 102, 102, 103,
		 105, 70, 66, 65, 63, 63, 62, 61, 60, 61, 63, 65, 66, 69, 70, 74, 74, 78,
		 79, 82, 84, 87, 89, 91, 94, 96, 100, 101, 103, 103, 105, 105, 105, 71,
		 67, 67, 64, 64, 62, 62, 60, 61, 64, 64, 67, 67, 71, 71, 75, 75, 79, 80,
		 84, 84, 89, 89, 94, 94, 98, 99, 104, 104, 106, 106, 109,
		 /* Size 4x16 */
		 31, 49, 61, 69, 32, 45, 55, 64, 36, 46, 54, 61, 41, 47, 54, 59, 46, 53,
		 59, 62, 46, 56, 62, 65, 46, 59, 68, 68, 48, 61, 73, 73, 51, 63, 77, 78,
		 54, 65, 82, 84, 57, 67, 86, 89, 60, 69, 88, 93, 62, 67, 86, 98, 64, 66,
		 87, 100, 65, 68, 83, 102, 67, 70, 86, 103,
		 /* Size 16x4 */
		 31, 32, 36, 41, 46, 46, 46, 48, 51, 54, 57, 60, 62, 64, 65, 67, 49, 45,
		 46, 47, 53, 56, 59, 61, 63, 65, 67, 69, 67, 66, 68, 70, 61, 55, 54, 54,
		 59, 62, 68, 73, 77, 82, 86, 88, 86, 87, 83, 86, 69, 64, 61, 59, 62, 65,
		 68, 73, 78, 84, 89, 93, 98, 100, 102, 103,
		 /* Size 8x32 */
		 32, 35, 48, 50, 57, 63, 68, 70, 31, 37, 47, 48, 54, 60, 64, 66, 30, 38,
		 46, 46, 52, 58, 63, 65, 31, 38, 46, 46, 52, 57, 61, 63, 33, 41, 47, 46,
		 51, 56, 60, 63, 37, 45, 47, 46, 50, 54, 59, 62, 39, 46, 48, 47, 51, 55,
		 58, 61, 42, 46, 50, 50, 53, 57, 60, 60, 49, 48, 53, 54, 57, 60, 61, 61,
		 48, 47, 53, 55, 58, 62, 64, 63, 48, 46, 53, 56, 60, 64, 65, 65, 49, 45,
		 53, 59, 64, 67, 67, 66, 50, 46, 54, 61, 66, 70, 71, 69, 51, 47, 54, 61,
		 68, 71, 72, 70, 52, 47, 54, 63, 71, 75, 75, 74, 54, 49, 55, 65, 73, 78,
		 78, 74, 55, 49, 56, 65, 74, 79, 79, 78, 57, 50, 56, 66, 76, 82, 83, 79,
		 60, 53, 58, 68, 79, 85, 85, 82, 62, 54, 60, 69, 81, 87, 87, 84, 63, 55,
		 60, 70, 82, 89, 91, 87, 64, 56, 61, 71, 83, 90, 92, 89, 66, 58, 62, 72,
		 84, 91, 95, 91, 67, 59, 63, 71, 83, 93, 96, 94, 68, 60, 64, 71, 81, 94,
		 97, 96, 69, 61, 65, 72, 80, 91, 99, 100, 70, 62, 65, 73, 81, 89, 98,
		 101, 71, 64, 65, 73, 82, 90, 99, 103, 72, 65, 65, 72, 82, 92, 100, 103,
		 73, 66, 65, 72, 81, 90, 100, 105, 74, 67, 65, 71, 79, 89, 98, 105, 75,
		 68, 65, 71, 78, 87, 96, 105,
		 /* Size 32x8 */
		 32, 31, 30, 31, 33, 37, 39, 42, 49, 48, 48, 49, 50, 51, 52, 54, 55, 57,
		 60, 62, 63, 64, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 35, 37, 38, 38,
		 41, 45, 46, 46, 48, 47, 46, 45, 46, 47, 47, 49, 49, 50, 53, 54, 55, 56,
		 58, 59, 60, 61, 62, 64, 65, 66, 67, 68, 48, 47, 46, 46, 47, 47, 48, 50,
		 53, 53, 53, 53, 54, 54, 54, 55, 56, 56, 58, 60, 60, 61, 62, 63, 64, 65,
		 65, 65, 65, 65, 65, 65, 50, 48, 46, 46, 46, 46, 47, 50, 54, 55, 56, 59,
		 61, 61, 63, 65, 65, 66, 68, 69, 70, 71, 72, 71, 71, 72, 73, 73, 72, 72,
		 71, 71, 57, 54, 52, 52, 51, 50, 51, 53, 57, 58, 60, 64, 66, 68, 71, 73,
		 74, 76, 79, 81, 82, 83, 84, 83, 81, 80, 81, 82, 82, 81, 79, 78, 63, 60,
		 58, 57, 56, 54, 55, 57, 60, 62, 64, 67, 70, 71, 75, 78, 79, 82, 85, 87,
		 89, 90, 91, 93, 94, 91, 89, 90, 92, 90, 89, 87, 68, 64, 63, 61, 60, 59,
		 58, 60, 61, 64, 65, 67, 71, 72, 75, 78, 79, 83, 85, 87, 91, 92, 95, 96,
		 97, 99, 98, 99, 100, 100, 98, 96, 70, 66, 65, 63, 63, 62, 61, 60, 61,
		 63, 65, 66, 69, 70, 74, 74, 78, 79, 82, 84, 87, 89, 91, 94, 96, 100,
		 101, 103, 103, 105, 105, 105},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 38, 63, 86, 38, 56, 78, 97, 63, 78, 113, 130, 86, 97, 130, 169,
		 /* Size 8x8 */
		 32, 32, 35, 46, 57, 76, 85, 96, 32, 34, 37, 45, 54, 70, 79, 90, 35, 37,
		 48, 56, 64, 79, 87, 93, 46, 45, 56, 70, 80, 96, 100, 105, 57, 54, 64,
		 80, 93, 111, 121, 122, 76, 70, 79, 96, 111, 134, 138, 144, 85, 79, 87,
		 100, 121, 138, 156, 168, 96, 90, 93, 105, 122, 144, 168, 184,
		 /* Size 16x16 */
		 32, 31, 31, 32, 34, 39, 44, 49, 58, 65, 71, 81, 87, 93, 98, 104, 31, 32,
		 32, 32, 34, 38, 41, 46, 54, 60, 66, 75, 81, 86, 92, 98, 31, 32, 33, 34,
		 36, 39, 42, 46, 53, 59, 64, 73, 78, 83, 88, 94, 32, 32, 34, 35, 37, 40,
		 42, 46, 52, 58, 63, 71, 75, 80, 86, 92, 34, 34, 36, 37, 42, 47, 50, 53,
		 59, 65, 70, 77, 82, 85, 89, 92, 39, 38, 39, 40, 47, 54, 58, 62, 68, 73,
		 78, 85, 90, 90, 96, 98, 44, 41, 42, 42, 50, 58, 63, 68, 74, 79, 84, 91,
		 96, 98, 102, 104, 49, 46, 46, 46, 53, 62, 68, 73, 81, 87, 92, 99, 103,
		 107, 109, 112, 58, 54, 53, 52, 59, 68, 74, 81, 90, 97, 102, 110, 114,
		 118, 117, 121, 65, 60, 59, 58, 65, 73, 79, 87, 97, 105, 111, 120, 125,
		 125, 126, 130, 71, 66, 64, 63, 70, 78, 84, 92, 102, 111, 117, 127, 133,
		 134, 136, 141, 81, 75, 73, 71, 77, 85, 91, 99, 110, 120, 127, 137, 143,
		 145, 148, 152, 87, 81, 78, 75, 82, 90, 96, 103, 114, 125, 133, 143, 150,
		 156, 160, 163, 93, 86, 83, 80, 85, 90, 98, 107, 118, 125, 134, 145, 156,
		 163, 169, 177, 98, 92, 88, 86, 89, 96, 102, 109, 117, 126, 136, 148,
		 160, 169, 176, 184, 104, 98, 94, 92, 92, 98, 104, 112, 121, 130, 141,
		 152, 163, 177, 184, 191,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 32, 32, 34, 34, 36, 39, 41, 44, 48, 49, 54, 58, 59,
		 65, 69, 71, 80, 81, 83, 87, 90, 93, 95, 98, 101, 104, 107, 31, 32, 32,
		 32, 32, 32, 32, 34, 34, 35, 38, 39, 42, 46, 47, 51, 55, 57, 62, 66, 68,
		 76, 77, 78, 83, 85, 88, 90, 93, 96, 99, 101, 31, 32, 32, 32, 32, 32, 32,
		 33, 34, 34, 38, 39, 41, 45, 46, 50, 54, 55, 60, 64, 66, 73, 75, 76, 81,
		 83, 86, 89, 92, 95, 98, 101, 31, 32, 32, 32, 32, 32, 32, 33, 34, 34, 37,
		 38, 41, 44, 45, 49, 53, 54, 59, 63, 65, 72, 74, 75, 79, 81, 84, 86, 89,
		 91, 94, 97, 31, 32, 32, 32, 33, 33, 34, 35, 36, 36, 39, 40, 42, 45, 46,
		 50, 53, 54, 59, 63, 64, 71, 73, 74, 78, 80, 83, 85, 88, 91, 94, 97, 32,
		 32, 32, 32, 33, 34, 34, 36, 36, 37, 40, 40, 42, 45, 46, 49, 53, 54, 58,
		 62, 63, 70, 72, 73, 77, 79, 82, 85, 87, 90, 92, 95, 32, 32, 32, 32, 34,
		 34, 35, 37, 37, 38, 40, 41, 42, 45, 46, 49, 52, 54, 58, 61, 63, 69, 71,
		 72, 75, 78, 80, 83, 86, 89, 92, 95, 34, 34, 33, 33, 35, 36, 37, 39, 41,
		 42, 45, 46, 47, 50, 51, 54, 57, 59, 63, 66, 68, 74, 75, 76, 80, 81, 82,
		 83, 85, 87, 90, 93, 34, 34, 34, 34, 36, 36, 37, 41, 42, 45, 47, 48, 50,
		 53, 53, 56, 59, 61, 65, 68, 70, 76, 77, 78, 82, 83, 85, 88, 89, 90, 92,
		 93, 36, 35, 34, 34, 36, 37, 38, 42, 45, 48, 50, 51, 54, 56, 57, 60, 63,
		 64, 68, 71, 73, 79, 80, 81, 85, 87, 89, 89, 90, 93, 96, 99, 39, 38, 38,
		 37, 39, 40, 40, 45, 47, 50, 54, 55, 58, 61, 62, 65, 68, 69, 73, 76, 78,
		 84, 85, 86, 90, 89, 90, 93, 96, 97, 98, 99, 41, 39, 39, 38, 40, 40, 41,
		 46, 48, 51, 55, 56, 59, 62, 63, 67, 70, 71, 75, 78, 80, 86, 87, 88, 91,
		 93, 96, 97, 97, 99, 102, 105, 44, 42, 41, 41, 42, 42, 42, 47, 50, 54,
		 58, 59, 63, 66, 68, 71, 74, 75, 79, 83, 84, 90, 91, 92, 96, 98, 98, 99,
		 102, 104, 104, 105, 48, 46, 45, 44, 45, 45, 45, 50, 53, 56, 61, 62, 66,
		 70, 71, 76, 79, 80, 85, 88, 90, 96, 97, 98, 101, 100, 102, 105, 105,
		 105, 109, 112, 49, 47, 46, 45, 46, 46, 46, 51, 53, 57, 62, 63, 68, 71,
		 73, 77, 81, 82, 87, 90, 92, 98, 99, 100, 103, 106, 107, 106, 109, 112,
		 112, 112, 54, 51, 50, 49, 50, 49, 49, 54, 56, 60, 65, 67, 71, 76, 77,
		 82, 86, 87, 92, 96, 97, 104, 105, 106, 110, 110, 109, 113, 114, 113,
		 116, 120, 58, 55, 54, 53, 53, 53, 52, 57, 59, 63, 68, 70, 74, 79, 81,
		 86, 90, 91, 97, 100, 102, 109, 110, 111, 114, 114, 118, 116, 117, 121,
		 121, 120, 59, 57, 55, 54, 54, 54, 54, 59, 61, 64, 69, 71, 75, 80, 82,
		 87, 91, 93, 99, 102, 104, 111, 112, 113, 117, 121, 120, 122, 124, 122,
		 125, 129, 65, 62, 60, 59, 59, 58, 58, 63, 65, 68, 73, 75, 79, 85, 87,
		 92, 97, 99, 105, 109, 111, 118, 120, 121, 125, 124, 125, 127, 126, 130,
		 130, 129, 69, 66, 64, 63, 63, 62, 61, 66, 68, 71, 76, 78, 83, 88, 90,
		 96, 100, 102, 109, 113, 115, 123, 125, 126, 129, 130, 131, 130, 134,
		 133, 135, 139, 71, 68, 66, 65, 64, 63, 63, 68, 70, 73, 78, 80, 84, 90,
		 92, 97, 102, 104, 111, 115, 117, 125, 127, 128, 133, 136, 134, 139, 136,
		 139, 141, 140, 80, 76, 73, 72, 71, 70, 69, 74, 76, 79, 84, 86, 90, 96,
		 98, 104, 109, 111, 118, 123, 125, 134, 136, 137, 142, 138, 143, 140,
		 144, 144, 144, 149, 81, 77, 75, 74, 73, 72, 71, 75, 77, 80, 85, 87, 91,
		 97, 99, 105, 110, 112, 120, 125, 127, 136, 137, 139, 143, 148, 145, 148,
		 148, 150, 152, 149, 83, 78, 76, 75, 74, 73, 72, 76, 78, 81, 86, 88, 92,
		 98, 100, 106, 111, 113, 121, 126, 128, 137, 139, 140, 145, 149, 153,
		 153, 154, 155, 155, 161, 87, 83, 81, 79, 78, 77, 75, 80, 82, 85, 90, 91,
		 96, 101, 103, 110, 114, 117, 125, 129, 133, 142, 143, 145, 150, 151,
		 156, 159, 160, 160, 163, 161, 90, 85, 83, 81, 80, 79, 78, 81, 83, 87,
		 89, 93, 98, 100, 106, 110, 114, 121, 124, 130, 136, 138, 148, 149, 151,
		 156, 157, 162, 166, 168, 166, 172, 93, 88, 86, 84, 83, 82, 80, 82, 85,
		 89, 90, 96, 98, 102, 107, 109, 118, 120, 125, 131, 134, 143, 145, 153,
		 156, 157, 163, 164, 169, 172, 177, 172, 95, 90, 89, 86, 85, 85, 83, 83,
		 88, 89, 93, 97, 99, 105, 106, 113, 116, 122, 127, 130, 139, 140, 148,
		 153, 159, 162, 164, 169, 170, 176, 179, 185, 98, 93, 92, 89, 88, 87, 86,
		 85, 89, 90, 96, 97, 102, 105, 109, 114, 117, 124, 126, 134, 136, 144,
		 148, 154, 160, 166, 169, 170, 176, 177, 184, 186, 101, 96, 95, 91, 91,
		 90, 89, 87, 90, 93, 97, 99, 104, 105, 112, 113, 121, 122, 130, 133, 139,
		 144, 150, 155, 160, 168, 172, 176, 177, 184, 185, 191, 104, 99, 98, 94,
		 94, 92, 92, 90, 92, 96, 98, 102, 104, 109, 112, 116, 121, 125, 130, 135,
		 141, 144, 152, 155, 163, 166, 177, 179, 184, 185, 191, 192, 107, 101,
		 101, 97, 97, 95, 95, 93, 93, 99, 99, 105, 105, 112, 112, 120, 120, 129,
		 129, 139, 140, 149, 149, 161, 161, 172, 172, 185, 186, 191, 192, 199,
		 /* Size 4x8 */
		 32, 38, 62, 86, 32, 40, 58, 80, 34, 51, 68, 85, 44, 61, 85, 101, 54, 69,
		 98, 117, 72, 84, 118, 136, 82, 89, 129, 157, 92, 98, 127, 165,
		 /* Size 8x4 */
		 32, 32, 34, 44, 54, 72, 82, 92, 38, 40, 51, 61, 69, 84, 89, 98, 62, 58,
		 68, 85, 98, 118, 129, 127, 86, 80, 85, 101, 117, 136, 157, 165,
		 /* Size 8x16 */
		 32, 32, 36, 44, 58, 79, 88, 93, 31, 32, 35, 41, 54, 73, 81, 88, 32, 33,
		 36, 42, 53, 71, 78, 84, 32, 34, 38, 42, 52, 69, 76, 82, 34, 36, 44, 50,
		 59, 75, 81, 84, 39, 39, 50, 58, 68, 84, 88, 90, 44, 42, 53, 63, 74, 90,
		 97, 97, 49, 46, 57, 67, 81, 97, 104, 105, 57, 53, 63, 74, 90, 108, 111,
		 113, 65, 59, 68, 79, 97, 118, 123, 122, 71, 64, 73, 84, 102, 125, 135,
		 131, 81, 72, 80, 91, 110, 135, 145, 141, 87, 77, 85, 96, 114, 140, 148,
		 151, 92, 83, 88, 102, 117, 133, 153, 163, 98, 88, 89, 103, 121, 141,
		 160, 169, 103, 94, 92, 103, 119, 137, 158, 175,
		 /* Size 16x8 */
		 32, 31, 32, 32, 34, 39, 44, 49, 57, 65, 71, 81, 87, 92, 98, 103, 32, 32,
		 33, 34, 36, 39, 42, 46, 53, 59, 64, 72, 77, 83, 88, 94, 36, 35, 36, 38,
		 44, 50, 53, 57, 63, 68, 73, 80, 85, 88, 89, 92, 44, 41, 42, 42, 50, 58,
		 63, 67, 74, 79, 84, 91, 96, 102, 103, 103, 58, 54, 53, 52, 59, 68, 74,
		 81, 90, 97, 102, 110, 114, 117, 121, 119, 79, 73, 71, 69, 75, 84, 90,
		 97, 108, 118, 125, 135, 140, 133, 141, 137, 88, 81, 78, 76, 81, 88, 97,
		 104, 111, 123, 135, 145, 148, 153, 160, 158, 93, 88, 84, 82, 84, 90, 97,
		 105, 113, 122, 131, 141, 151, 163, 169, 175,
		 /* Size 16x32 */
		 32, 31, 32, 32, 36, 39, 44, 53, 58, 65, 79, 81, 88, 90, 93, 96, 31, 32,
		 32, 32, 35, 38, 42, 51, 55, 62, 75, 77, 83, 86, 88, 91, 31, 32, 32, 32,
		 35, 38, 41, 50, 54, 60, 73, 75, 81, 84, 88, 91, 31, 32, 32, 33, 34, 37,
		 41, 49, 53, 59, 72, 74, 79, 82, 84, 87, 32, 32, 33, 34, 36, 39, 42, 50,
		 53, 59, 71, 72, 78, 81, 84, 87, 32, 32, 34, 34, 37, 40, 42, 49, 53, 58,
		 70, 71, 77, 80, 83, 85, 32, 33, 34, 35, 38, 40, 42, 49, 52, 58, 69, 70,
		 76, 78, 82, 86, 34, 34, 35, 37, 42, 45, 48, 54, 57, 63, 73, 75, 79, 79,
		 81, 83, 34, 34, 36, 37, 44, 47, 50, 56, 59, 65, 75, 77, 81, 83, 84, 84,
		 36, 34, 37, 38, 48, 51, 54, 60, 63, 68, 78, 80, 85, 85, 86, 89, 39, 37,
		 39, 40, 50, 54, 58, 65, 68, 73, 84, 85, 88, 89, 90, 89, 40, 38, 40, 41,
		 51, 55, 59, 67, 70, 75, 85, 87, 91, 92, 92, 95, 44, 41, 42, 43, 53, 58,
		 63, 71, 74, 79, 90, 91, 97, 94, 97, 95, 47, 44, 45, 46, 56, 61, 66, 75,
		 79, 85, 95, 97, 99, 101, 98, 102, 49, 46, 46, 47, 57, 62, 67, 77, 81,
		 86, 97, 99, 104, 102, 105, 102, 53, 49, 50, 50, 60, 65, 71, 82, 86, 92,
		 103, 105, 109, 108, 106, 110, 57, 53, 53, 53, 63, 68, 74, 86, 90, 97,
		 108, 110, 111, 112, 113, 110, 59, 54, 54, 54, 64, 69, 75, 87, 91, 98,
		 111, 112, 119, 117, 115, 118, 65, 60, 59, 58, 68, 73, 79, 92, 97, 105,
		 118, 119, 123, 123, 122, 119, 69, 63, 62, 62, 71, 76, 83, 96, 100, 109,
		 122, 124, 127, 125, 125, 128, 71, 65, 64, 63, 73, 78, 84, 97, 102, 111,
		 125, 127, 135, 134, 131, 129, 79, 72, 71, 70, 79, 84, 90, 104, 109, 118,
		 133, 135, 137, 136, 136, 137, 81, 74, 72, 71, 80, 85, 91, 105, 110, 120,
		 135, 137, 145, 143, 141, 138, 82, 75, 73, 72, 81, 86, 92, 106, 111, 121,
		 136, 139, 147, 148, 147, 149, 87, 79, 77, 76, 85, 90, 96, 110, 114, 125,
		 140, 143, 148, 154, 151, 149, 90, 82, 80, 78, 87, 89, 99, 108, 113, 129,
		 135, 146, 153, 157, 160, 159, 92, 84, 83, 81, 88, 90, 102, 106, 117,
		 128, 133, 150, 153, 158, 163, 160, 95, 87, 85, 83, 88, 92, 103, 105,
		 120, 125, 137, 148, 155, 164, 168, 173, 98, 89, 88, 85, 89, 95, 103,
		 108, 121, 124, 141, 144, 160, 164, 169, 174, 100, 92, 91, 88, 90, 98,
		 103, 111, 120, 127, 139, 146, 161, 165, 175, 179, 103, 94, 94, 90, 92,
		 101, 103, 114, 119, 131, 137, 150, 158, 170, 175, 180, 106, 97, 97, 93,
		 93, 104, 104, 118, 118, 135, 135, 154, 155, 175, 176, 187,
		 /* Size 32x16 */
		 32, 31, 31, 31, 32, 32, 32, 34, 34, 36, 39, 40, 44, 47, 49, 53, 57, 59,
		 65, 69, 71, 79, 81, 82, 87, 90, 92, 95, 98, 100, 103, 106, 31, 32, 32,
		 32, 32, 32, 33, 34, 34, 34, 37, 38, 41, 44, 46, 49, 53, 54, 60, 63, 65,
		 72, 74, 75, 79, 82, 84, 87, 89, 92, 94, 97, 32, 32, 32, 32, 33, 34, 34,
		 35, 36, 37, 39, 40, 42, 45, 46, 50, 53, 54, 59, 62, 64, 71, 72, 73, 77,
		 80, 83, 85, 88, 91, 94, 97, 32, 32, 32, 33, 34, 34, 35, 37, 37, 38, 40,
		 41, 43, 46, 47, 50, 53, 54, 58, 62, 63, 70, 71, 72, 76, 78, 81, 83, 85,
		 88, 90, 93, 36, 35, 35, 34, 36, 37, 38, 42, 44, 48, 50, 51, 53, 56, 57,
		 60, 63, 64, 68, 71, 73, 79, 80, 81, 85, 87, 88, 88, 89, 90, 92, 93, 39,
		 38, 38, 37, 39, 40, 40, 45, 47, 51, 54, 55, 58, 61, 62, 65, 68, 69, 73,
		 76, 78, 84, 85, 86, 90, 89, 90, 92, 95, 98, 101, 104, 44, 42, 41, 41,
		 42, 42, 42, 48, 50, 54, 58, 59, 63, 66, 67, 71, 74, 75, 79, 83, 84, 90,
		 91, 92, 96, 99, 102, 103, 103, 103, 103, 104, 53, 51, 50, 49, 50, 49,
		 49, 54, 56, 60, 65, 67, 71, 75, 77, 82, 86, 87, 92, 96, 97, 104, 105,
		 106, 110, 108, 106, 105, 108, 111, 114, 118, 58, 55, 54, 53, 53, 53, 52,
		 57, 59, 63, 68, 70, 74, 79, 81, 86, 90, 91, 97, 100, 102, 109, 110, 111,
		 114, 113, 117, 120, 121, 120, 119, 118, 65, 62, 60, 59, 59, 58, 58, 63,
		 65, 68, 73, 75, 79, 85, 86, 92, 97, 98, 105, 109, 111, 118, 120, 121,
		 125, 129, 128, 125, 124, 127, 131, 135, 79, 75, 73, 72, 71, 70, 69, 73,
		 75, 78, 84, 85, 90, 95, 97, 103, 108, 111, 118, 122, 125, 133, 135, 136,
		 140, 135, 133, 137, 141, 139, 137, 135, 81, 77, 75, 74, 72, 71, 70, 75,
		 77, 80, 85, 87, 91, 97, 99, 105, 110, 112, 119, 124, 127, 135, 137, 139,
		 143, 146, 150, 148, 144, 146, 150, 154, 88, 83, 81, 79, 78, 77, 76, 79,
		 81, 85, 88, 91, 97, 99, 104, 109, 111, 119, 123, 127, 135, 137, 145,
		 147, 148, 153, 153, 155, 160, 161, 158, 155, 90, 86, 84, 82, 81, 80, 78,
		 79, 83, 85, 89, 92, 94, 101, 102, 108, 112, 117, 123, 125, 134, 136,
		 143, 148, 154, 157, 158, 164, 164, 165, 170, 175, 93, 88, 88, 84, 84,
		 83, 82, 81, 84, 86, 90, 92, 97, 98, 105, 106, 113, 115, 122, 125, 131,
		 136, 141, 147, 151, 160, 163, 168, 169, 175, 175, 176, 96, 91, 91, 87,
		 87, 85, 86, 83, 84, 89, 89, 95, 95, 102, 102, 110, 110, 118, 119, 128,
		 129, 137, 138, 149, 149, 159, 160, 173, 174, 179, 180, 187,
		 /* Size 4x16 */
		 31, 39, 65, 90, 32, 38, 60, 84, 32, 39, 59, 81, 33, 40, 58, 78, 34, 47,
		 65, 83, 37, 54, 73, 89, 41, 58, 79, 94, 46, 62, 86, 102, 53, 68, 97,
		 112, 60, 73, 105, 123, 65, 78, 111, 134, 74, 85, 120, 143, 79, 90, 125,
		 154, 84, 90, 128, 158, 89, 95, 124, 164, 94, 101, 131, 170,
		 /* Size 16x4 */
		 31, 32, 32, 33, 34, 37, 41, 46, 53, 60, 65, 74, 79, 84, 89, 94, 39, 38,
		 39, 40, 47, 54, 58, 62, 68, 73, 78, 85, 90, 90, 95, 101, 65, 60, 59, 58,
		 65, 73, 79, 86, 97, 105, 111, 120, 125, 128, 124, 131, 90, 84, 81, 78,
		 83, 89, 94, 102, 112, 123, 134, 143, 154, 158, 164, 170,
		 /* Size 8x32 */
		 32, 32, 36, 44, 58, 79, 88, 93, 31, 32, 35, 42, 55, 75, 83, 88, 31, 32,
		 35, 41, 54, 73, 81, 88, 31, 32, 34, 41, 53, 72, 79, 84, 32, 33, 36, 42,
		 53, 71, 78, 84, 32, 34, 37, 42, 53, 70, 77, 83, 32, 34, 38, 42, 52, 69,
		 76, 82, 34, 35, 42, 48, 57, 73, 79, 81, 34, 36, 44, 50, 59, 75, 81, 84,
		 36, 37, 48, 54, 63, 78, 85, 86, 39, 39, 50, 58, 68, 84, 88, 90, 40, 40,
		 51, 59, 70, 85, 91, 92, 44, 42, 53, 63, 74, 90, 97, 97, 47, 45, 56, 66,
		 79, 95, 99, 98, 49, 46, 57, 67, 81, 97, 104, 105, 53, 50, 60, 71, 86,
		 103, 109, 106, 57, 53, 63, 74, 90, 108, 111, 113, 59, 54, 64, 75, 91,
		 111, 119, 115, 65, 59, 68, 79, 97, 118, 123, 122, 69, 62, 71, 83, 100,
		 122, 127, 125, 71, 64, 73, 84, 102, 125, 135, 131, 79, 71, 79, 90, 109,
		 133, 137, 136, 81, 72, 80, 91, 110, 135, 145, 141, 82, 73, 81, 92, 111,
		 136, 147, 147, 87, 77, 85, 96, 114, 140, 148, 151, 90, 80, 87, 99, 113,
		 135, 153, 160, 92, 83, 88, 102, 117, 133, 153, 163, 95, 85, 88, 103,
		 120, 137, 155, 168, 98, 88, 89, 103, 121, 141, 160, 169, 100, 91, 90,
		 103, 120, 139, 161, 175, 103, 94, 92, 103, 119, 137, 158, 175, 106, 97,
		 93, 104, 118, 135, 155, 176,
		 /* Size 32x8 */
		 32, 31, 31, 31, 32, 32, 32, 34, 34, 36, 39, 40, 44, 47, 49, 53, 57, 59,
		 65, 69, 71, 79, 81, 82, 87, 90, 92, 95, 98, 100, 103, 106, 32, 32, 32,
		 32, 33, 34, 34, 35, 36, 37, 39, 40, 42, 45, 46, 50, 53, 54, 59, 62, 64,
		 71, 72, 73, 77, 80, 83, 85, 88, 91, 94, 97, 36, 35, 35, 34, 36, 37, 38,
		 42, 44, 48, 50, 51, 53, 56, 57, 60, 63, 64, 68, 71, 73, 79, 80, 81, 85,
		 87, 88, 88, 89, 90, 92, 93, 44, 42, 41, 41, 42, 42, 42, 48, 50, 54, 58,
		 59, 63, 66, 67, 71, 74, 75, 79, 83, 84, 90, 91, 92, 96, 99, 102, 103,
		 103, 103, 103, 104, 58, 55, 54, 53, 53, 53, 52, 57, 59, 63, 68, 70, 74,
		 79, 81, 86, 90, 91, 97, 100, 102, 109, 110, 111, 114, 113, 117, 120,
		 121, 120, 119, 118, 79, 75, 73, 72, 71, 70, 69, 73, 75, 78, 84, 85, 90,
		 95, 97, 103, 108, 111, 118, 122, 125, 133, 135, 136, 140, 135, 133, 137,
		 141, 139, 137, 135, 88, 83, 81, 79, 78, 77, 76, 79, 81, 85, 88, 91, 97,
		 99, 104, 109, 111, 119, 123, 127, 135, 137, 145, 147, 148, 153, 153,
		 155, 160, 161, 158, 155, 93, 88, 88, 84, 84, 83, 82, 81, 84, 86, 90, 92,
		 97, 98, 105, 106, 113, 115, 122, 125, 131, 136, 141, 147, 151, 160, 163,
		 168, 169, 175, 175, 176},
		{/* Chroma */
		 /* Size 4x4 */
		 32, 45, 53, 63, 45, 55, 62, 67, 53, 62, 80, 84, 63, 67, 84, 101,
		 /* Size 8x8 */
		 31, 36, 47, 48, 52, 60, 64, 67, 36, 43, 47, 46, 49, 55, 59, 63, 47, 47,
		 53, 54, 55, 60, 63, 64, 48, 46, 54, 61, 65, 70, 71, 71, 52, 49, 55, 65,
		 71, 78, 81, 79, 60, 55, 60, 70, 78, 89, 89, 89, 64, 59, 63, 71, 81, 89,
		 97, 99, 67, 63, 64, 71, 79, 89, 99, 104,
		 /* Size 16x16 */
		 32, 30, 33, 36, 44, 48, 49, 51, 54, 57, 60, 64, 67, 68, 70, 72, 30, 31,
		 35, 39, 44, 46, 46, 47, 50, 53, 55, 59, 61, 64, 66, 68, 33, 35, 39, 43,
		 46, 46, 45, 47, 49, 51, 53, 57, 59, 61, 63, 65, 36, 39, 43, 47, 47, 46,
		 45, 46, 48, 50, 52, 55, 57, 58, 61, 63, 44, 44, 46, 47, 50, 51, 51, 51,
		 53, 54, 56, 59, 61, 61, 63, 62, 48, 46, 46, 46, 51, 54, 55, 56, 58, 60,
		 61, 64, 65, 64, 66, 66, 49, 46, 45, 45, 51, 55, 58, 60, 62, 63, 65, 68,
		 69, 69, 69, 69, 51, 47, 47, 46, 51, 56, 60, 62, 65, 67, 69, 72, 73, 74,
		 73, 73, 54, 50, 49, 48, 53, 58, 62, 65, 70, 73, 75, 78, 79, 79, 77, 77,
		 57, 53, 51, 50, 54, 60, 63, 67, 73, 76, 79, 82, 84, 83, 82, 82, 60, 55,
		 53, 52, 56, 61, 65, 69, 75, 79, 82, 86, 88, 87, 86, 87, 64, 59, 57, 55,
		 59, 64, 68, 72, 78, 82, 86, 90, 93, 92, 91, 92, 67, 61, 59, 57, 61, 65,
		 69, 73, 79, 84, 88, 93, 95, 96, 96, 96, 68, 64, 61, 58, 61, 64, 69, 74,
		 79, 83, 87, 92, 96, 99, 100, 101, 70, 66, 63, 61, 63, 66, 69, 73, 77,
		 82, 86, 91, 96, 100, 103, 104, 72, 68, 65, 63, 62, 66, 69, 73, 77, 82,
		 87, 92, 96, 101, 104, 106,
		 /* Size 32x32 */
		 32, 31, 30, 30, 33, 35, 36, 41, 44, 49, 48, 48, 49, 50, 51, 52, 54, 55,
		 57, 59, 60, 63, 64, 65, 67, 68, 68, 69, 70, 71, 72, 73, 31, 31, 31, 31,
		 34, 36, 38, 42, 44, 47, 47, 47, 47, 48, 48, 50, 51, 52, 54, 56, 57, 60,
		 61, 61, 63, 64, 65, 66, 67, 67, 68, 69, 30, 31, 31, 31, 35, 37, 39, 42,
		 44, 47, 46, 46, 46, 47, 47, 48, 50, 51, 53, 54, 55, 58, 59, 60, 61, 63,
		 64, 65, 66, 67, 68, 69, 30, 31, 31, 32, 35, 37, 40, 42, 44, 46, 45, 45,
		 45, 46, 46, 47, 49, 50, 52, 53, 54, 57, 58, 58, 60, 61, 62, 63, 63, 64,
		 65, 66, 33, 34, 35, 35, 39, 41, 43, 45, 46, 47, 46, 46, 45, 46, 47, 47,
		 49, 49, 51, 53, 53, 56, 57, 57, 59, 60, 61, 62, 63, 64, 65, 66, 35, 36,
		 37, 37, 41, 43, 45, 46, 46, 47, 46, 46, 45, 46, 46, 47, 48, 49, 50, 52,
		 53, 55, 56, 56, 58, 59, 60, 61, 62, 63, 64, 64, 36, 38, 39, 40, 43, 45,
		 47, 47, 47, 48, 46, 46, 45, 46, 46, 47, 48, 48, 50, 51, 52, 54, 55, 55,
		 57, 58, 58, 59, 61, 62, 63, 64, 41, 42, 42, 42, 45, 46, 47, 48, 49, 50,
		 49, 49, 49, 50, 50, 50, 51, 52, 53, 54, 55, 57, 58, 58, 60, 60, 59, 59,
		 60, 61, 61, 62, 44, 44, 44, 44, 46, 46, 47, 49, 50, 51, 51, 51, 51, 51,
		 51, 52, 53, 53, 54, 56, 56, 59, 59, 59, 61, 61, 61, 62, 63, 62, 62, 62,
		 49, 47, 47, 46, 47, 47, 48, 50, 51, 53, 53, 53, 53, 54, 54, 54, 55, 55,
		 56, 58, 58, 60, 61, 61, 63, 63, 64, 63, 63, 64, 65, 66, 48, 47, 46, 45,
		 46, 46, 46, 49, 51, 53, 54, 54, 55, 56, 56, 57, 58, 59, 60, 61, 61, 63,
		 64, 64, 65, 65, 64, 65, 66, 66, 66, 66, 48, 47, 46, 45, 46, 46, 46, 49,
		 51, 53, 54, 55, 56, 57, 57, 58, 59, 60, 61, 62, 63, 65, 65, 65, 66, 67,
		 68, 67, 67, 67, 68, 69, 49, 47, 46, 45, 45, 45, 45, 49, 51, 53, 55, 56,
		 58, 59, 60, 61, 62, 62, 63, 65, 65, 67, 68, 68, 69, 70, 69, 69, 69, 70,
		 69, 69, 50, 48, 47, 46, 46, 46, 46, 50, 51, 54, 56, 57, 59, 61, 62, 63,
		 64, 65, 66, 68, 68, 70, 71, 71, 72, 71, 71, 72, 71, 71, 71, 72, 51, 48,
		 47, 46, 47, 46, 46, 50, 51, 54, 56, 57, 60, 62, 62, 64, 65, 66, 67, 69,
		 69, 71, 72, 72, 73, 74, 74, 72, 73, 74, 73, 73, 52, 50, 48, 47, 47, 47,
		 47, 50, 52, 54, 57, 58, 61, 63, 64, 66, 68, 68, 70, 72, 72, 75, 75, 75,
		 77, 76, 75, 76, 76, 74, 75, 76, 54, 51, 50, 49, 49, 48, 48, 51, 53, 55,
		 58, 59, 62, 64, 65, 68, 70, 70, 73, 74, 75, 77, 78, 78, 79, 78, 79, 78,
		 77, 78, 77, 77, 55, 52, 51, 50, 49, 49, 48, 52, 53, 55, 59, 60, 62, 65,
		 66, 68, 70, 71, 73, 75, 76, 78, 79, 79, 80, 81, 80, 80, 81, 79, 79, 81,
		 57, 54, 53, 52, 51, 50, 50, 53, 54, 56, 60, 61, 63, 66, 67, 70, 73, 73,
		 76, 78, 79, 82, 82, 83, 84, 83, 83, 83, 82, 83, 82, 81, 59, 56, 54, 53,
		 53, 52, 51, 54, 56, 58, 61, 62, 65, 68, 69, 72, 74, 75, 78, 80, 81, 84,
		 85, 85, 86, 86, 86, 84, 85, 84, 84, 85, 60, 57, 55, 54, 53, 53, 52, 55,
		 56, 58, 61, 63, 65, 68, 69, 72, 75, 76, 79, 81, 82, 85, 86, 86, 88, 88,
		 87, 88, 86, 87, 87, 85, 63, 60, 58, 57, 56, 55, 54, 57, 59, 60, 63, 65,
		 67, 70, 71, 75, 77, 78, 82, 84, 85, 89, 89, 90, 92, 89, 91, 89, 90, 89,
		 88, 89, 64, 61, 59, 58, 57, 56, 55, 58, 59, 61, 64, 65, 68, 71, 72, 75,
		 78, 79, 82, 85, 86, 89, 90, 91, 93, 94, 92, 92, 91, 91, 92, 90, 65, 61,
		 60, 58, 57, 56, 55, 58, 59, 61, 64, 65, 68, 71, 72, 75, 78, 79, 83, 85,
		 86, 90, 91, 91, 93, 94, 95, 94, 94, 94, 93, 94, 67, 63, 61, 60, 59, 58,
		 57, 60, 61, 63, 65, 66, 69, 72, 73, 77, 79, 80, 84, 86, 88, 92, 93, 93,
		 95, 95, 96, 97, 96, 95, 96, 94, 68, 64, 63, 61, 60, 59, 58, 60, 61, 63,
		 65, 67, 70, 71, 74, 76, 78, 81, 83, 86, 88, 89, 94, 94, 95, 97, 97, 98,
		 99, 99, 97, 99, 68, 65, 64, 62, 61, 60, 58, 59, 61, 64, 64, 68, 69, 71,
		 74, 75, 79, 80, 83, 86, 87, 91, 92, 95, 96, 97, 99, 99, 100, 100, 101,
		 99, 69, 66, 65, 63, 62, 61, 59, 59, 62, 63, 65, 67, 69, 72, 72, 76, 78,
		 80, 83, 84, 88, 89, 92, 94, 97, 98, 99, 101, 100, 102, 102, 104, 70, 67,
		 66, 63, 63, 62, 61, 60, 63, 63, 66, 67, 69, 71, 73, 76, 77, 81, 82, 85,
		 86, 90, 91, 94, 96, 99, 100, 100, 103, 102, 104, 104, 71, 67, 67, 64,
		 64, 63, 62, 61, 62, 64, 66, 67, 70, 71, 74, 74, 78, 79, 83, 84, 87, 89,
		 91, 94, 95, 99, 100, 102, 102, 104, 104, 106, 72, 68, 68, 65, 65, 64,
		 63, 61, 62, 65, 66, 68, 69, 71, 73, 75, 77, 79, 82, 84, 87, 88, 92, 93,
		 96, 97, 101, 102, 104, 104, 106, 106, 73, 69, 69, 66, 66, 64, 64, 62,
		 62, 66, 66, 69, 69, 72, 73, 76, 77, 81, 81, 85, 85, 89, 90, 94, 94, 99,
		 99, 104, 104, 106, 106, 108,
		 /* Size 4x8 */
		 31, 47, 54, 64, 38, 46, 50, 60, 46, 53, 57, 62, 46, 56, 66, 71, 50, 59,
		 74, 79, 57, 64, 82, 88, 61, 65, 85, 97, 65, 67, 82, 99,
		 /* Size 8x4 */
		 31, 38, 46, 46, 50, 57, 61, 65, 47, 46, 53, 56, 59, 64, 65, 67, 54, 50,
		 57, 66, 74, 82, 85, 82, 64, 60, 62, 71, 79, 88, 97, 99,
		 /* Size 8x16 */
		 32, 34, 48, 49, 54, 63, 67, 69, 31, 36, 46, 46, 50, 58, 62, 65, 33, 40,
		 47, 46, 49, 56, 59, 62, 37, 44, 47, 45, 48, 54, 57, 60, 44, 46, 51, 51,
		 53, 59, 60, 61, 48, 46, 53, 56, 58, 64, 64, 64, 49, 45, 53, 58, 62, 67,
		 70, 68, 51, 47, 54, 60, 65, 71, 73, 72, 54, 49, 55, 62, 70, 77, 77, 76,
		 57, 51, 56, 64, 73, 82, 83, 81, 60, 53, 58, 65, 75, 85, 89, 85, 64, 57,
		 61, 68, 78, 89, 93, 89, 66, 59, 63, 69, 79, 91, 94, 93, 68, 61, 63, 71,
		 79, 87, 96, 98, 70, 63, 63, 70, 80, 89, 97, 100, 72, 65, 63, 69, 77, 86,
		 95, 102,
		 /* Size 16x8 */
		 32, 31, 33, 37, 44, 48, 49, 51, 54, 57, 60, 64, 66, 68, 70, 72, 34, 36,
		 40, 44, 46, 46, 45, 47, 49, 51, 53, 57, 59, 61, 63, 65, 48, 46, 47, 47,
		 51, 53, 53, 54, 55, 56, 58, 61, 63, 63, 63, 63, 49, 46, 46, 45, 51, 56,
		 58, 60, 62, 64, 65, 68, 69, 71, 70, 69, 54, 50, 49, 48, 53, 58, 62, 65,
		 70, 73, 75, 78, 79, 79, 80, 77, 63, 58, 56, 54, 59, 64, 67, 71, 77, 82,
		 85, 89, 91, 87, 89, 86, 67, 62, 59, 57, 60, 64, 70, 73, 77, 83, 89, 93,

		 94, 96, 97, 95, 69, 65, 62, 60, 61, 64, 68, 72, 76, 81, 85, 89, 93, 98,
		 100, 102,
		 /* Size 16x32 */
		 32, 31, 34, 37, 48, 48, 49, 52, 54, 57, 63, 64, 67, 68, 69, 69, 31, 31,
		 35, 38, 47, 47, 47, 50, 51, 54, 60, 61, 63, 64, 65, 66, 31, 32, 36, 39,
		 46, 46, 46, 48, 50, 53, 58, 59, 62, 63, 65, 66, 30, 32, 36, 40, 46, 45,
		 45, 48, 49, 52, 57, 58, 60, 61, 62, 63, 33, 36, 40, 43, 47, 46, 46, 47,
		 49, 51, 56, 57, 59, 60, 62, 63, 35, 38, 42, 45, 47, 46, 45, 47, 48, 50,
		 55, 56, 58, 60, 61, 61, 37, 40, 44, 47, 47, 46, 45, 47, 48, 50, 54, 55,
		 57, 58, 60, 61, 42, 43, 45, 47, 50, 50, 49, 50, 51, 53, 57, 58, 59, 58,
		 59, 59, 44, 44, 46, 47, 51, 51, 51, 52, 53, 54, 59, 59, 60, 61, 61, 60,
		 49, 46, 47, 48, 53, 53, 53, 54, 55, 57, 60, 61, 63, 62, 62, 63, 48, 46,
		 46, 47, 53, 54, 56, 57, 58, 60, 64, 64, 64, 64, 64, 63, 48, 45, 46, 46,
		 53, 55, 56, 58, 59, 61, 65, 65, 66, 66, 65, 66, 49, 45, 45, 46, 53, 56,
		 58, 61, 62, 64, 67, 68, 70, 67, 68, 66, 50, 46, 46, 46, 54, 56, 59, 63,
		 65, 66, 70, 71, 70, 71, 68, 70, 51, 47, 47, 47, 54, 57, 60, 64, 65, 68,
		 71, 72, 73, 71, 72, 70, 52, 48, 47, 47, 54, 57, 61, 66, 68, 71, 75, 75,
		 76, 75, 73, 73, 54, 49, 49, 48, 55, 58, 62, 68, 70, 73, 77, 78, 77, 77,
		 76, 74, 54, 50, 49, 49, 55, 59, 62, 68, 70, 74, 78, 79, 81, 79, 77, 78,
		 57, 52, 51, 50, 56, 60, 64, 70, 73, 76, 82, 82, 83, 82, 81, 78, 59, 54,
		 52, 52, 58, 61, 65, 72, 74, 78, 84, 85, 85, 83, 82, 82, 60, 54, 53, 52,
		 58, 62, 65, 72, 75, 79, 85, 86, 89, 87, 85, 82, 63, 57, 56, 55, 60, 64,
		 67, 75, 77, 82, 89, 90, 90, 88, 87, 86, 64, 58, 57, 55, 61, 64, 68, 75,
		 78, 82, 89, 90, 93, 91, 89, 87, 64, 59, 57, 56, 61, 65, 68, 75, 78, 83,
		 90, 91, 94, 93, 92, 91, 66, 60, 59, 57, 63, 66, 69, 77, 79, 84, 91, 93,
		 94, 95, 93, 91, 67, 61, 60, 58, 63, 65, 70, 75, 78, 85, 88, 93, 96, 97,
		 97, 95, 68, 62, 61, 59, 63, 64, 71, 74, 79, 84, 87, 94, 96, 97, 98, 96,
		 69, 63, 62, 60, 63, 65, 71, 72, 80, 82, 88, 93, 96, 99, 100, 101, 70,
		 64, 63, 60, 63, 66, 70, 73, 80, 81, 89, 90, 97, 99, 100, 101, 71, 65,
		 64, 61, 63, 67, 70, 74, 78, 82, 88, 90, 97, 99, 102, 103, 72, 65, 65,
		 62, 63, 68, 69, 75, 77, 83, 86, 92, 95, 100, 102, 103, 73, 66, 66, 63,
		 63, 69, 69, 76, 76, 84, 84, 93, 93, 101, 101, 105,
		 /* Size 32x16 */
		 32, 31, 31, 30, 33, 35, 37, 42, 44, 49, 48, 48, 49, 50, 51, 52, 54, 54,
		 57, 59, 60, 63, 64, 64, 66, 67, 68, 69, 70, 71, 72, 73, 31, 31, 32, 32,
		 36, 38, 40, 43, 44, 46, 46, 45, 45, 46, 47, 48, 49, 50, 52, 54, 54, 57,
		 58, 59, 60, 61, 62, 63, 64, 65, 65, 66, 34, 35, 36, 36, 40, 42, 44, 45,
		 46, 47, 46, 46, 45, 46, 47, 47, 49, 49, 51, 52, 53, 56, 57, 57, 59, 60,
		 61, 62, 63, 64, 65, 66, 37, 38, 39, 40, 43, 45, 47, 47, 47, 48, 47, 46,
		 46, 46, 47, 47, 48, 49, 50, 52, 52, 55, 55, 56, 57, 58, 59, 60, 60, 61,
		 62, 63, 48, 47, 46, 46, 47, 47, 47, 50, 51, 53, 53, 53, 53, 54, 54, 54,
		 55, 55, 56, 58, 58, 60, 61, 61, 63, 63, 63, 63, 63, 63, 63, 63, 48, 47,
		 46, 45, 46, 46, 46, 50, 51, 53, 54, 55, 56, 56, 57, 57, 58, 59, 60, 61,
		 62, 64, 64, 65, 66, 65, 64, 65, 66, 67, 68, 69, 49, 47, 46, 45, 46, 45,
		 45, 49, 51, 53, 56, 56, 58, 59, 60, 61, 62, 62, 64, 65, 65, 67, 68, 68,
		 69, 70, 71, 71, 70, 70, 69, 69, 52, 50, 48, 48, 47, 47, 47, 50, 52, 54,
		 57, 58, 61, 63, 64, 66, 68, 68, 70, 72, 72, 75, 75, 75, 77, 75, 74, 72,
		 73, 74, 75, 76, 54, 51, 50, 49, 49, 48, 48, 51, 53, 55, 58, 59, 62, 65,
		 65, 68, 70, 70, 73, 74, 75, 77, 78, 78, 79, 78, 79, 80, 80, 78, 77, 76,
		 57, 54, 53, 52, 51, 50, 50, 53, 54, 57, 60, 61, 64, 66, 68, 71, 73, 74,

		 76, 78, 79, 82, 82, 83, 84, 85, 84, 82, 81, 82, 83, 84, 63, 60, 58, 57,
		 56, 55, 54, 57, 59, 60, 64, 65, 67, 70, 71, 75, 77, 78, 82, 84, 85, 89,
		 89, 90, 91, 88, 87, 88, 89, 88, 86, 84, 64, 61, 59, 58, 57, 56, 55, 58,
		 59, 61, 64, 65, 68, 71, 72, 75, 78, 79, 82, 85, 86, 90, 90, 91, 93, 93,
		 94, 93, 90, 90, 92, 93, 67, 63, 62, 60, 59, 58, 57, 59, 60, 63, 64, 66,
		 70, 70, 73, 76, 77, 81, 83, 85, 89, 90, 93, 94, 94, 96, 96, 96, 97, 97,
		 95, 93, 68, 64, 63, 61, 60, 60, 58, 58, 61, 62, 64, 66, 67, 71, 71, 75,
		 77, 79, 82, 83, 87, 88, 91, 93, 95, 97, 97, 99, 99, 99, 100, 101, 69,
		 65, 65, 62, 62, 61, 60, 59, 61, 62, 64, 65, 68, 68, 72, 73, 76, 77, 81,
		 82, 85, 87, 89, 92, 93, 97, 98, 100, 100, 102, 102, 101, 69, 66, 66, 63,
		 63, 61, 61, 59, 60, 63, 63, 66, 66, 70, 70, 73, 74, 78, 78, 82, 82, 86,
		 87, 91, 91, 95, 96, 101, 101, 103, 103, 105,
		 /* Size 4x16 */
		 31, 48, 57, 68, 32, 46, 53, 63, 36, 46, 51, 60, 40, 46, 50, 58, 44, 51,
		 54, 61, 46, 54, 60, 64, 45, 56, 64, 67, 47, 57, 68, 71, 49, 58, 73, 77,
		 52, 60, 76, 82, 54, 62, 79, 87, 58, 64, 82, 91, 60, 66, 84, 95, 62, 64,
		 84, 97, 64, 66, 81, 99, 65, 68, 83, 100,
		 /* Size 16x4 */
		 31, 32, 36, 40, 44, 46, 45, 47, 49, 52, 54, 58, 60, 62, 64, 65, 48, 46,
		 46, 46, 51, 54, 56, 57, 58, 60, 62, 64, 66, 64, 66, 68, 57, 53, 51, 50,
		 54, 60, 64, 68, 73, 76, 79, 82, 84, 84, 81, 83, 68, 63, 60, 58, 61, 64,
		 67, 71, 77, 82, 87, 91, 95, 97, 99, 100,
		 /* Size 8x32 */
		 32, 34, 48, 49, 54, 63, 67, 69, 31, 35, 47, 47, 51, 60, 63, 65, 31, 36,
		 46, 46, 50, 58, 62, 65, 30, 36, 46, 45, 49, 57, 60, 62, 33, 40, 47, 46,
		 49, 56, 59, 62, 35, 42, 47, 45, 48, 55, 58, 61, 37, 44, 47, 45, 48, 54,
		 57, 60, 42, 45, 50, 49, 51, 57, 59, 59, 44, 46, 51, 51, 53, 59, 60, 61,
		 49, 47, 53, 53, 55, 60, 63, 62, 48, 46, 53, 56, 58, 64, 64, 64, 48, 46,
		 53, 56, 59, 65, 66, 65, 49, 45, 53, 58, 62, 67, 70, 68, 50, 46, 54, 59,
		 65, 70, 70, 68, 51, 47, 54, 60, 65, 71, 73, 72, 52, 47, 54, 61, 68, 75,
		 76, 73, 54, 49, 55, 62, 70, 77, 77, 76, 54, 49, 55, 62, 70, 78, 81, 77,
		 57, 51, 56, 64, 73, 82, 83, 81, 59, 52, 58, 65, 74, 84, 85, 82, 60, 53,
		 58, 65, 75, 85, 89, 85, 63, 56, 60, 67, 77, 89, 90, 87, 64, 57, 61, 68,
		 78, 89, 93, 89, 64, 57, 61, 68, 78, 90, 94, 92, 66, 59, 63, 69, 79, 91,
		 94, 93, 67, 60, 63, 70, 78, 88, 96, 97, 68, 61, 63, 71, 79, 87, 96, 98,
		 69, 62, 63, 71, 80, 88, 96, 100, 70, 63, 63, 70, 80, 89, 97, 100, 71,
		 64, 63, 70, 78, 88, 97, 102, 72, 65, 63, 69, 77, 86, 95, 102, 73, 66,
		 63, 69, 76, 84, 93, 101,
		 /* Size 32x8 */
		 32, 31, 31, 30, 33, 35, 37, 42, 44, 49, 48, 48, 49, 50, 51, 52, 54, 54,
		 57, 59, 60, 63, 64, 64, 66, 67, 68, 69, 70, 71, 72, 73, 34, 35, 36, 36,
		 40, 42, 44, 45, 46, 47, 46, 46, 45, 46, 47, 47, 49, 49, 51, 52, 53, 56,
		 57, 57, 59, 60, 61, 62, 63, 64, 65, 66, 48, 47, 46, 46, 47, 47, 47, 50,
		 51, 53, 53, 53, 53, 54, 54, 54, 55, 55, 56, 58, 58, 60, 61, 61, 63, 63,
		 63, 63, 63, 63, 63, 63, 49, 47, 46, 45, 46, 45, 45, 49, 51, 53, 56, 56,
		 58, 59, 60, 61, 62, 62, 64, 65, 65, 67, 68, 68, 69, 70, 71, 71, 70, 70,
		 69, 69, 54, 51, 50, 49, 49, 48, 48, 51, 53, 55, 58, 59, 62, 65, 65, 68,
		 70, 70, 73, 74, 75, 77, 78, 78, 79, 78, 79, 80, 80, 78, 77, 76, 63, 60,
		 58, 57, 56, 55, 54, 57, 59, 60, 64, 65, 67, 70, 71, 75, 77, 78, 82, 84,
		 85, 89, 89, 90, 91, 88, 87, 88, 89, 88, 86, 84, 67, 63, 62, 60, 59, 58,

		 57, 59, 60, 63, 64, 66, 70, 70, 73, 76, 77, 81, 83, 85, 89, 90, 93, 94,
		 94, 96, 96, 96, 97, 97, 95, 93, 69, 65, 65, 62, 62, 61, 60, 59, 61, 62,
		 64, 65, 68, 68, 72, 73, 76, 77, 81, 82, 85, 87, 89, 92, 93, 97, 98, 100,
		 100, 102, 102, 101},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 37, 58, 81, 37, 54, 72, 91, 58, 72, 102, 121, 81, 91, 121, 156,
		 /* Size 8x8 */
		 32, 32, 35, 42, 53, 68, 78, 90, 32, 33, 36, 42, 51, 64, 74, 84, 35, 36,
		 46, 52, 60, 72, 80, 87, 42, 42, 52, 63, 73, 84, 92, 98, 53, 51, 60, 73,
		 86, 100, 109, 114, 68, 64, 72, 84, 100, 117, 128, 133, 78, 74, 80, 92,
		 109, 128, 140, 155, 90, 84, 87, 98, 114, 133, 155, 168,
		 /* Size 16x16 */
		 32, 31, 31, 32, 34, 36, 41, 47, 54, 59, 65, 74, 82, 87, 92, 97, 31, 32,
		 32, 32, 34, 35, 39, 45, 50, 55, 61, 69, 76, 81, 87, 92, 31, 32, 33, 33,
		 35, 36, 40, 44, 49, 54, 59, 67, 73, 78, 83, 88, 32, 32, 33, 35, 37, 38,
		 41, 45, 49, 53, 58, 65, 71, 75, 80, 86, 34, 34, 35, 37, 39, 42, 46, 50,
		 54, 58, 63, 70, 76, 80, 84, 85, 36, 35, 36, 38, 42, 48, 52, 56, 60, 64,
		 68, 75, 80, 85, 90, 91, 41, 39, 40, 41, 46, 52, 57, 62, 67, 71, 75, 83,
		 88, 92, 95, 97, 47, 45, 44, 45, 50, 56, 62, 69, 75, 79, 84, 91, 97, 100,
		 102, 104, 54, 50, 49, 49, 54, 60, 67, 75, 82, 87, 92, 100, 106, 110,
		 109, 112, 59, 55, 54, 53, 58, 64, 71, 79, 87, 92, 98, 106, 112, 117,
		 117, 121, 65, 61, 59, 58, 63, 68, 75, 84, 92, 98, 105, 114, 120, 125,
		 126, 130, 74, 69, 67, 65, 70, 75, 83, 91, 100, 106, 114, 123, 131, 135,
		 137, 140, 82, 76, 73, 71, 76, 80, 88, 97, 106, 112, 120, 131, 139, 144,
		 148, 150, 87, 81, 78, 75, 80, 85, 92, 100, 110, 117, 125, 135, 144, 150,
		 155, 162, 92, 87, 83, 80, 84, 90, 95, 102, 109, 117, 126, 137, 148, 155,
		 162, 168, 97, 92, 88, 86, 85, 91, 97, 104, 112, 121, 130, 140, 150, 162,
		 168, 174,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 32, 32, 34, 35, 36, 39, 41, 44, 47, 48, 54, 56,
		 59, 64, 65, 71, 74, 80, 82, 83, 87, 90, 92, 95, 97, 100, 31, 32, 32, 32,
		 32, 32, 32, 33, 34, 35, 35, 38, 40, 42, 45, 46, 51, 53, 56, 61, 62, 68,
		 71, 76, 78, 78, 83, 85, 88, 90, 92, 95, 31, 32, 32, 32, 32, 32, 32, 33,
		 34, 34, 35, 38, 39, 42, 45, 45, 50, 52, 55, 60, 61, 67, 69, 74, 76, 77,
		 81, 84, 87, 89, 92, 95, 31, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 37,
		 38, 41, 44, 44, 49, 51, 54, 58, 59, 65, 68, 72, 74, 75, 79, 81, 84, 86,
		 88, 90, 31, 32, 32, 32, 33, 33, 33, 34, 35, 36, 36, 39, 40, 42, 44, 45,
		 49, 51, 54, 58, 59, 64, 67, 71, 73, 74, 78, 80, 83, 85, 88, 90, 31, 32,
		 32, 32, 33, 33, 34, 34, 35, 36, 36, 39, 40, 42, 45, 45, 50, 51, 54, 58,
		 59, 64, 67, 71, 73, 74, 78, 80, 82, 84, 86, 89, 32, 32, 32, 32, 33, 34,
		 35, 36, 37, 38, 38, 40, 41, 42, 45, 46, 49, 51, 53, 57, 58, 63, 65, 69,
		 71, 72, 75, 78, 80, 83, 86, 89, 32, 33, 33, 33, 34, 34, 36, 36, 38, 39,
		 40, 42, 43, 44, 47, 47, 51, 53, 55, 59, 60, 65, 67, 71, 73, 73, 77, 78,
		 80, 82, 84, 86, 34, 34, 34, 33, 35, 35, 37, 38, 39, 42, 42, 45, 46, 47,
		 50, 51, 54, 56, 58, 62, 63, 68, 70, 74, 76, 76, 80, 82, 84, 85, 85, 86,
		 35, 35, 34, 34, 36, 36, 38, 39, 42, 46, 47, 49, 50, 52, 55, 55, 59, 60,
		 62, 66, 67, 72, 74, 78, 79, 80, 83, 84, 85, 87, 90, 92, 36, 35, 35, 34,
		 36, 36, 38, 40, 42, 47, 48, 50, 52, 54, 56, 57, 60, 61, 64, 67, 68, 73,
		 75, 79, 80, 81, 85, 87, 90, 91, 91, 92, 39, 38, 38, 37, 39, 39, 40, 42,
		 45, 49, 50, 54, 55, 58, 60, 61, 65, 66, 69, 72, 73, 78, 80, 84, 86, 86,
		 90, 91, 91, 92, 95, 97, 41, 40, 39, 38, 40, 40, 41, 43, 46, 50, 52, 55,
		 57, 60, 62, 63, 67, 69, 71, 75, 75, 80, 83, 86, 88, 89, 92, 93, 95, 97,
		 97, 98, 44, 42, 42, 41, 42, 42, 42, 44, 47, 52, 54, 58, 60, 63, 66, 67,
		 71, 73, 75, 79, 79, 84, 86, 90, 92, 92, 96, 98, 98, 98, 101, 104, 47,
		 45, 45, 44, 44, 45, 45, 47, 50, 55, 56, 60, 62, 66, 69, 70, 75, 77, 79,
		 83, 84, 89, 91, 95, 97, 97, 100, 99, 102, 105, 104, 104, 48, 46, 45, 44,
		 45, 45, 46, 47, 51, 55, 57, 61, 63, 67, 70, 71, 76, 78, 80, 84, 85, 90,
		 93, 96, 98, 99, 102, 106, 106, 105, 108, 111, 54, 51, 50, 49, 49, 50,
		 49, 51, 54, 59, 60, 65, 67, 71, 75, 76, 82, 84, 87, 91, 92, 97, 100,
		 104, 106, 106, 110, 108, 109, 112, 112, 111, 56, 53, 52, 51, 51, 51, 51,
		 53, 56, 60, 61, 66, 69, 73, 77, 78, 84, 86, 89, 93, 94, 100, 102, 106,
		 108, 109, 112, 113, 115, 114, 116, 119, 59, 56, 55, 54, 54, 54, 53, 55,
		 58, 62, 64, 69, 71, 75, 79, 80, 87, 89, 92, 97, 98, 103, 106, 110, 112,
		 113, 117, 118, 117, 121, 121, 119, 64, 61, 60, 58, 58, 58, 57, 59, 62,
		 66, 67, 72, 75, 79, 83, 84, 91, 93, 97, 102, 103, 109, 112, 116, 118,
		 119, 122, 121, 125, 123, 125, 128, 65, 62, 61, 59, 59, 59, 58, 60, 63,
		 67, 68, 73, 75, 79, 84, 85, 92, 94, 98, 103, 105, 111, 114, 118, 120,
		 121, 125, 129, 126, 129, 130, 129, 71, 68, 67, 65, 64, 64, 63, 65, 68,
		 72, 73, 78, 80, 84, 89, 90, 97, 100, 103, 109, 111, 117, 120, 125, 127,
		 128, 133, 130, 134, 133, 133, 137, 74, 71, 69, 68, 67, 67, 65, 67, 70,
		 74, 75, 80, 83, 86, 91, 93, 100, 102, 106, 112, 114, 120, 123, 128, 131,
		 131, 135, 137, 137, 138, 140, 137, 80, 76, 74, 72, 71, 71, 69, 71, 74,
		 78, 79, 84, 86, 90, 95, 96, 104, 106, 110, 116, 118, 125, 128, 134, 136,
		 137, 142, 141, 142, 143, 143, 147, 82, 78, 76, 74, 73, 73, 71, 73, 76,
		 79, 80, 86, 88, 92, 97, 98, 106, 108, 112, 118, 120, 127, 131, 136, 139,
		 139, 144, 147, 148, 147, 150, 148, 83, 78, 77, 75, 74, 74, 72, 73, 76,
		 80, 81, 86, 89, 92, 97, 99, 106, 109, 113, 119, 121, 128, 131, 137, 139,
		 140, 145, 150, 152, 155, 152, 157, 87, 83, 81, 79, 78, 78, 75, 77, 80,
		 83, 85, 90, 92, 96, 100, 102, 110, 112, 117, 122, 125, 133, 135, 142,
		 144, 145, 150, 151, 155, 158, 162, 158, 90, 85, 84, 81, 80, 80, 78, 78,
		 82, 84, 87, 91, 93, 98, 99, 106, 108, 113, 118, 121, 129, 130, 137, 141,
		 147, 150, 151, 156, 156, 161, 164, 169, 92, 88, 87, 84, 83, 82, 80, 80,
		 84, 85, 90, 91, 95, 98, 102, 106, 109, 115, 117, 125, 126, 134, 137,
		 142, 148, 152, 155, 156, 162, 162, 168, 170, 95, 90, 89, 86, 85, 84, 83,
		 82, 85, 87, 91, 92, 97, 98, 105, 105, 112, 114, 121, 123, 129, 133, 138,
		 143, 147, 155, 158, 161, 162, 168, 168, 174, 97, 92, 92, 88, 88, 86, 86,
		 84, 85, 90, 91, 95, 97, 101, 104, 108, 112, 116, 121, 125, 130, 133,
		 140, 143, 150, 152, 162, 164, 168, 168, 174, 175, 100, 95, 95, 90, 90,
		 89, 89, 86, 86, 92, 92, 97, 98, 104, 104, 111, 111, 119, 119, 128, 129,
		 137, 137, 147, 148, 157, 158, 169, 170, 174, 175, 181,
		 /* Size 4x8 */
		 32, 35, 59, 83, 32, 36, 57, 78, 34, 47, 65, 82, 41, 53, 78, 97, 51, 61,
		 92, 111, 65, 73, 108, 129, 75, 81, 117, 148, 86, 92, 119, 154,
		 /* Size 8x4 */
		 32, 32, 34, 41, 51, 65, 75, 86, 35, 36, 47, 53, 61, 73, 81, 92, 59, 57,
		 65, 78, 92, 108, 117, 119, 83, 78, 82, 97, 111, 129, 148, 154,
		 /* Size 8x16 */
		 32, 31, 35, 44, 53, 65, 82, 90, 31, 32, 34, 41, 50, 61, 76, 85, 31, 33,
		 35, 42, 49, 59, 73, 81, 32, 34, 37, 42, 49, 58, 71, 79, 34, 35, 41, 48,
		 54, 63, 76, 81, 36, 36, 46, 54, 60, 68, 80, 87, 41, 40, 49, 60, 67, 76,
		 88, 93, 47, 44, 53, 66, 75, 84, 97, 101, 53, 50, 57, 71, 82, 92, 106,
		 108, 58, 54, 61, 75, 87, 98, 112, 116, 65, 59, 66, 79, 92, 105, 120,
		 124, 74, 67, 73, 86, 100, 113, 131, 134, 82, 73, 79, 92, 105, 120, 139,
		 142, 87, 78, 83, 96, 110, 125, 144, 153, 92, 83, 84, 97, 114, 132, 150,
		 157, 97, 88, 86, 97, 111, 128, 147, 163,
		 /* Size 16x8 */
		 32, 31, 31, 32, 34, 36, 41, 47, 53, 58, 65, 74, 82, 87, 92, 97, 31, 32,
		 33, 34, 35, 36, 40, 44, 50, 54, 59, 67, 73, 78, 83, 88, 35, 34, 35, 37,
		 41, 46, 49, 53, 57, 61, 66, 73, 79, 83, 84, 86, 44, 41, 42, 42, 48, 54,
		 60, 66, 71, 75, 79, 86, 92, 96, 97, 97, 53, 50, 49, 49, 54, 60, 67, 75,
		 82, 87, 92, 100, 105, 110, 114, 111, 65, 61, 59, 58, 63, 68, 76, 84, 92,
		 98, 105, 113, 120, 125, 132, 128, 82, 76, 73, 71, 76, 80, 88, 97, 106,
		 112, 120, 131, 139, 144, 150, 147, 90, 85, 81, 79, 81, 87, 93, 101, 108,
		 116, 124, 134, 142, 153, 157, 163,
		 /* Size 16x32 */
		 32, 31, 31, 32, 35, 36, 44, 47, 53, 62, 65, 79, 82, 88, 90, 93, 31, 32,
		 32, 32, 35, 35, 42, 45, 51, 59, 62, 75, 78, 83, 86, 88, 31, 32, 32, 32,
		 34, 35, 41, 45, 50, 58, 61, 74, 76, 82, 85, 88, 31, 32, 32, 33, 34, 34,
		 41, 44, 49, 57, 59, 72, 74, 79, 82, 84, 31, 32, 33, 34, 35, 36, 42, 44,
		 49, 57, 59, 71, 73, 79, 81, 84, 32, 32, 33, 34, 36, 36, 42, 45, 50, 57,
		 59, 71, 73, 78, 80, 82, 32, 33, 34, 35, 37, 38, 42, 45, 49, 56, 58, 69,
		 71, 76, 79, 83, 32, 33, 34, 36, 39, 40, 44, 47, 51, 58, 60, 71, 73, 76,
		 78, 80, 34, 34, 35, 37, 41, 42, 48, 50, 54, 61, 63, 73, 76, 81, 81, 80,
		 35, 34, 36, 38, 45, 47, 52, 55, 59, 65, 67, 77, 79, 82, 83, 86, 36, 34,
		 36, 38, 46, 48, 54, 56, 60, 66, 68, 78, 80, 85, 87, 86, 39, 37, 39, 40,
		 48, 50, 58, 60, 65, 71, 73, 84, 86, 89, 88, 91, 41, 39, 40, 41, 49, 51,
		 60, 62, 67, 74, 76, 86, 88, 91, 93, 91, 44, 41, 42, 43, 51, 53, 63, 66,
		 71, 78, 79, 90, 92, 97, 94, 97, 47, 44, 44, 45, 53, 56, 66, 69, 75, 82,
		 84, 95, 97, 98, 101, 98, 48, 45, 45, 46, 54, 56, 67, 70, 76, 83, 85, 96,
		 98, 104, 101, 105, 53, 49, 50, 50, 57, 60, 71, 75, 82, 90, 92, 103, 106,
		 107, 108, 105, 55, 51, 51, 51, 59, 61, 72, 77, 84, 92, 94, 106, 108,
		 111, 110, 112, 58, 54, 54, 54, 61, 63, 75, 79, 87, 95, 98, 110, 112,
		 117, 116, 113, 63, 58, 58, 57, 65, 67, 78, 83, 91, 100, 103, 116, 118,
		 119, 119, 121, 65, 60, 59, 58, 66, 68, 79, 84, 92, 102, 105, 118, 120,
		 127, 124, 122, 71, 65, 64, 63, 71, 73, 84, 89, 97, 108, 111, 125, 127,
		 129, 129, 130, 74, 68, 67, 66, 73, 75, 86, 91, 100, 110, 113, 128, 131,
		 135, 134, 130, 79, 72, 71, 70, 77, 79, 90, 95, 104, 115, 118, 133, 136,
		 140, 139, 140, 82, 75, 73, 72, 79, 81, 92, 97, 105, 117, 120, 136, 139,
		 145, 142, 140, 82, 75, 74, 72, 79, 81, 92, 97, 106, 117, 121, 136, 139,
		 148, 150, 149, 87, 79, 78, 76, 83, 85, 96, 100, 110, 120, 125, 141, 144,
		 148, 153, 150, 89, 82, 81, 78, 83, 87, 97, 99, 113, 118, 128, 139, 145,
		 153, 157, 161, 92, 84, 83, 80, 84, 89, 97, 101, 114, 116, 132, 135, 150,
		 153, 157, 162, 94, 86, 85, 82, 85, 92, 97, 104, 112, 119, 130, 136, 151,
		 154, 163, 166, 97, 88, 88, 85, 86, 94, 97, 107, 111, 123, 128, 140, 147,
		 159, 163, 167, 99, 91, 91, 87, 87, 97, 97, 110, 110, 126, 126, 144, 144,
		 163, 163, 173,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 32, 32, 32, 34, 35, 36, 39, 41, 44, 47, 48, 53, 55,
		 58, 63, 65, 71, 74, 79, 82, 82, 87, 89, 92, 94, 97, 99, 31, 32, 32, 32,
		 32, 32, 33, 33, 34, 34, 34, 37, 39, 41, 44, 45, 49, 51, 54, 58, 60, 65,
		 68, 72, 75, 75, 79, 82, 84, 86, 88, 91, 31, 32, 32, 32, 33, 33, 34, 34,
		 35, 36, 36, 39, 40, 42, 44, 45, 50, 51, 54, 58, 59, 64, 67, 71, 73, 74,
		 78, 81, 83, 85, 88, 91, 32, 32, 32, 33, 34, 34, 35, 36, 37, 38, 38, 40,
		 41, 43, 45, 46, 50, 51, 54, 57, 58, 63, 66, 70, 72, 72, 76, 78, 80, 82,
		 85, 87, 35, 35, 34, 34, 35, 36, 37, 39, 41, 45, 46, 48, 49, 51, 53, 54,
		 57, 59, 61, 65, 66, 71, 73, 77, 79, 79, 83, 83, 84, 85, 86, 87, 36, 35,
		 35, 34, 36, 36, 38, 40, 42, 47, 48, 50, 51, 53, 56, 56, 60, 61, 63, 67,
		 68, 73, 75, 79, 81, 81, 85, 87, 89, 92, 94, 97, 44, 42, 41, 41, 42, 42,
		 42, 44, 48, 52, 54, 58, 60, 63, 66, 67, 71, 72, 75, 78, 79, 84, 86, 90,
		 92, 92, 96, 97, 97, 97, 97, 97, 47, 45, 45, 44, 44, 45, 45, 47, 50, 55,
		 56, 60, 62, 66, 69, 70, 75, 77, 79, 83, 84, 89, 91, 95, 97, 97, 100, 99,
		 101, 104, 107, 110, 53, 51, 50, 49, 49, 50, 49, 51, 54, 59, 60, 65, 67,
		 71, 75, 76, 82, 84, 87, 91, 92, 97, 100, 104, 105, 106, 110, 113, 114,
		 112, 111, 110, 62, 59, 58, 57, 57, 57, 56, 58, 61, 65, 66, 71, 74, 78,
		 82, 83, 90, 92, 95, 100, 102, 108, 110, 115, 117, 117, 120, 118, 116,
		 119, 123, 126, 65, 62, 61, 59, 59, 59, 58, 60, 63, 67, 68, 73, 76, 79,
		 84, 85, 92, 94, 98, 103, 105, 111, 113, 118, 120, 121, 125, 128, 132,
		 130, 128, 126, 79, 75, 74, 72, 71, 71, 69, 71, 73, 77, 78, 84, 86, 90,
		 95, 96, 103, 106, 110, 116, 118, 125, 128, 133, 136, 136, 141, 139, 135,
		 136, 140, 144, 82, 78, 76, 74, 73, 73, 71, 73, 76, 79, 80, 86, 88, 92,
		 97, 98, 106, 108, 112, 118, 120, 127, 131, 136, 139, 139, 144, 145, 150,
		 151, 147, 144, 88, 83, 82, 79, 79, 78, 76, 76, 81, 82, 85, 89, 91, 97,
		 98, 104, 107, 111, 117, 119, 127, 129, 135, 140, 145, 148, 148, 153,
		 153, 154, 159, 163, 90, 86, 85, 82, 81, 80, 79, 78, 81, 83, 87, 88, 93,
		 94, 101, 101, 108, 110, 116, 119, 124, 129, 134, 139, 142, 150, 153,
		 157, 157, 163, 163, 163, 93, 88, 88, 84, 84, 82, 83, 80, 80, 86, 86, 91,
		 91, 97, 98, 105, 105, 112, 113, 121, 122, 130, 130, 140, 140, 149, 150,
		 161, 162, 166, 167, 173,
		 /* Size 4x16 */
		 31, 36, 62, 88, 32, 35, 58, 82, 32, 36, 57, 79, 33, 38, 56, 76, 34, 42,
		 61, 81, 34, 48, 66, 85, 39, 51, 74, 91, 44, 56, 82, 98, 49, 60, 90, 107,
		 54, 63, 95, 117, 60, 68, 102, 127, 68, 75, 110, 135, 75, 81, 117, 145,
		 79, 85, 120, 148, 84, 89, 116, 153, 88, 94, 123, 159,
		 /* Size 16x4 */
		 31, 32, 32, 33, 34, 34, 39, 44, 49, 54, 60, 68, 75, 79, 84, 88, 36, 35,
		 36, 38, 42, 48, 51, 56, 60, 63, 68, 75, 81, 85, 89, 94, 62, 58, 57, 56,
		 61, 66, 74, 82, 90, 95, 102, 110, 117, 120, 116, 123, 88, 82, 79, 76,
		 81, 85, 91, 98, 107, 117, 127, 135, 145, 148, 153, 159,
		 /* Size 8x32 */
		 32, 31, 35, 44, 53, 65, 82, 90, 31, 32, 35, 42, 51, 62, 78, 86, 31, 32,
		 34, 41, 50, 61, 76, 85, 31, 32, 34, 41, 49, 59, 74, 82, 31, 33, 35, 42,
		 49, 59, 73, 81, 32, 33, 36, 42, 50, 59, 73, 80, 32, 34, 37, 42, 49, 58,
		 71, 79, 32, 34, 39, 44, 51, 60, 73, 78, 34, 35, 41, 48, 54, 63, 76, 81,
		 35, 36, 45, 52, 59, 67, 79, 83, 36, 36, 46, 54, 60, 68, 80, 87, 39, 39,
		 48, 58, 65, 73, 86, 88, 41, 40, 49, 60, 67, 76, 88, 93, 44, 42, 51, 63,
		 71, 79, 92, 94, 47, 44, 53, 66, 75, 84, 97, 101, 48, 45, 54, 67, 76, 85,
		 98, 101, 53, 50, 57, 71, 82, 92, 106, 108, 55, 51, 59, 72, 84, 94, 108,
		 110, 58, 54, 61, 75, 87, 98, 112, 116, 63, 58, 65, 78, 91, 103, 118,
		 119, 65, 59, 66, 79, 92, 105, 120, 124, 71, 64, 71, 84, 97, 111, 127,
		 129, 74, 67, 73, 86, 100, 113, 131, 134, 79, 71, 77, 90, 104, 118, 136,
		 139, 82, 73, 79, 92, 105, 120, 139, 142, 82, 74, 79, 92, 106, 121, 139,
		 150, 87, 78, 83, 96, 110, 125, 144, 153, 89, 81, 83, 97, 113, 128, 145,
		 157, 92, 83, 84, 97, 114, 132, 150, 157, 94, 85, 85, 97, 112, 130, 151,
		 163, 97, 88, 86, 97, 111, 128, 147, 163, 99, 91, 87, 97, 110, 126, 144,
		 163,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 32, 32, 32, 34, 35, 36, 39, 41, 44, 47, 48, 53, 55,
		 58, 63, 65, 71, 74, 79, 82, 82, 87, 89, 92, 94, 97, 99, 31, 32, 32, 32,
		 33, 33, 34, 34, 35, 36, 36, 39, 40, 42, 44, 45, 50, 51, 54, 58, 59, 64,
		 67, 71, 73, 74, 78, 81, 83, 85, 88, 91, 35, 35, 34, 34, 35, 36, 37, 39,
		 41, 45, 46, 48, 49, 51, 53, 54, 57, 59, 61, 65, 66, 71, 73, 77, 79, 79,
		 83, 83, 84, 85, 86, 87, 44, 42, 41, 41, 42, 42, 42, 44, 48, 52, 54, 58,
		 60, 63, 66, 67, 71, 72, 75, 78, 79, 84, 86, 90, 92, 92, 96, 97, 97, 97,
		 97, 97, 53, 51, 50, 49, 49, 50, 49, 51, 54, 59, 60, 65, 67, 71, 75, 76,
		 82, 84, 87, 91, 92, 97, 100, 104, 105, 106, 110, 113, 114, 112, 111,
		 110, 65, 62, 61, 59, 59, 59, 58, 60, 63, 67, 68, 73, 76, 79, 84, 85, 92,
		 94, 98, 103, 105, 111, 113, 118, 120, 121, 125, 128, 132, 130, 128, 126,
		 82, 78, 76, 74, 73, 73, 71, 73, 76, 79, 80, 86, 88, 92, 97, 98, 106,
		 108, 112, 118, 120, 127, 131, 136, 139, 139, 144, 145, 150, 151, 147,
		 144, 90, 86, 85, 82, 81, 80, 79, 78, 81, 83, 87, 88, 93, 94, 101, 101,
		 108, 110, 116, 119, 124, 129, 134, 139, 142, 150, 153, 157, 157, 163,
		 163, 163},
		{/* Chroma */
		 /* Size 4x4 */
		 32, 45, 51, 61, 45, 54, 59, 65, 51, 59, 75, 81, 61, 65, 81, 97,
		 /* Size 8x8 */
		 31, 34, 46, 47, 50, 57, 61, 65, 34, 39, 47, 45, 48, 53, 57, 61, 46, 47,
		 52, 52, 54, 58, 61, 62, 47, 45, 52, 58, 62, 65, 68, 68, 50, 48, 54, 62,
		 68, 73, 77, 76, 57, 53, 58, 65, 73, 82, 86, 86, 61, 57, 61, 68, 77, 86,
		 91, 95, 65, 61, 62, 68, 76, 86, 95, 100,
		 /* Size 16x16 */
		 32, 31, 33, 36, 41, 49, 49, 50, 52, 54, 57, 61, 64, 67, 68, 70, 31, 31,
		 34, 39, 42, 47, 46, 47, 49, 51, 53, 57, 60, 62, 64, 66, 33, 34, 37, 42,
		 44, 47, 46, 46, 47, 49, 51, 55, 57, 59, 61, 63, 36, 39, 42, 47, 47, 48,
		 46, 46, 47, 48, 50, 53, 55, 57, 59, 61, 41, 42, 44, 47, 48, 50, 49, 50,
		 50, 52, 53, 56, 58, 60, 61, 60, 49, 47, 47, 48, 50, 53, 53, 54, 54, 55,
		 56, 59, 61, 63, 64, 64, 49, 46, 46, 46, 49, 53, 55, 57, 59, 60, 61, 64,
		 66, 67, 67, 67, 50, 47, 46, 46, 50, 54, 57, 61, 63, 64, 66, 69, 70, 72,
		 71, 71, 52, 49, 47, 47, 50, 54, 59, 63, 66, 68, 70, 73, 75, 77, 75, 75,
		 54, 51, 49, 48, 52, 55, 60, 64, 68, 71, 73, 76, 79, 80, 79, 79, 57, 53,
		 51, 50, 53, 56, 61, 66, 70, 73, 76, 80, 82, 84, 83, 84, 61, 57, 55, 53,
		 56, 59, 64, 69, 73, 76, 80, 84, 87, 89, 88, 88, 64, 60, 57, 55, 58, 61,
		 66, 70, 75, 79, 82, 87, 91, 93, 93, 93, 67, 62, 59, 57, 60, 63, 67, 72,
		 77, 80, 84, 89, 93, 95, 96, 97, 68, 64, 61, 59, 61, 64, 67, 71, 75, 79,
		 83, 88, 93, 96, 99, 100, 70, 66, 63, 61, 60, 64, 67, 71, 75, 79, 84, 88,
		 93, 97, 100, 102,
		 /* Size 32x32 */
		 32, 31, 31, 30, 33, 33, 36, 38, 41, 47, 49, 48, 49, 49, 50, 50, 52, 53,
		 54, 56, 57, 60, 61, 63, 64, 65, 67, 67, 68, 69, 70, 71, 31, 31, 31, 31,
		 34, 34, 38, 40, 42, 46, 47, 47, 47, 47, 48, 48, 50, 50, 52, 54, 54, 57,
		 58, 60, 61, 61, 63, 64, 65, 65, 66, 67, 31, 31, 31, 31, 34, 35, 39, 40,
		 42, 46, 47, 46, 46, 46, 47, 47, 49, 50, 51, 53, 53, 56, 57, 59, 60, 60,
		 62, 63, 64, 65, 66, 67, 30, 31, 31, 32, 34, 35, 40, 41, 42, 45, 46, 45,
		 45, 45, 46, 46, 47, 48, 49, 51, 52, 54, 55, 57, 58, 58, 60, 61, 62, 62,
		 63, 64, 33, 34, 34, 34, 37, 38, 42, 43, 44, 46, 47, 46, 46, 45, 46, 46,
		 47, 48, 49, 51, 51, 53, 55, 56, 57, 57, 59, 60, 61, 62, 63, 64, 33, 34,
		 35, 35, 38, 39, 43, 44, 45, 47, 47, 46, 46, 45, 46, 46, 47, 48, 49, 51,
		 51, 53, 54, 56, 57, 57, 59, 60, 60, 61, 62, 62, 36, 38, 39, 40, 42, 43,
		 47, 47, 47, 47, 48, 46, 46, 45, 46, 46, 47, 47, 48, 49, 50, 52, 53, 54,
		 55, 55, 57, 58, 59, 60, 61, 62, 38, 40, 40, 41, 43, 44, 47, 47, 48, 48,
		 49, 48, 47, 47, 47, 47, 48, 49, 49, 51, 51, 53, 54, 55, 56, 56, 58, 58,
		 58, 59, 60, 60, 41, 42, 42, 42, 44, 45, 47, 48, 48, 50, 50, 49, 49, 49,
		 50, 50, 50, 51, 52, 53, 53, 55, 56, 57, 58, 58, 60, 61, 61, 61, 60, 60,
		 47, 46, 46, 45, 46, 47, 47, 48, 50, 52, 52, 52, 52, 52, 53, 53, 53, 54,
		 55, 55, 56, 58, 58, 60, 60, 61, 62, 61, 61, 62, 63, 64, 49, 47, 47, 46,
		 47, 47, 48, 49, 50, 52, 53, 53, 53, 53, 54, 54, 54, 55, 55, 56, 56, 58,
		 59, 60, 61, 61, 63, 63, 64, 64, 64, 64, 48, 47, 46, 45, 46, 46, 46, 48,
		 49, 52, 53, 54, 55, 55, 56, 56, 57, 58, 58, 59, 60, 61, 62, 63, 64, 64,
		 66, 65, 65, 65, 66, 67, 49, 47, 46, 45, 46, 46, 46, 47, 49, 52, 53, 55,
		 55, 57, 57, 58, 59, 59, 60, 61, 61, 63, 64, 65, 66, 66, 67, 67, 67, 68,
		 67, 67, 49, 47, 46, 45, 45, 45, 45, 47, 49, 52, 53, 55, 57, 58, 59, 60,
		 61, 62, 62, 63, 63, 65, 66, 67, 68, 68, 69, 70, 69, 68, 69, 70, 50, 48,
		 47, 46, 46, 46, 46, 47, 50, 53, 54, 56, 57, 59, 61, 61, 63, 64, 64, 66,
		 66, 68, 69, 70, 70, 71, 72, 70, 71, 72, 71, 70, 50, 48, 47, 46, 46, 46,
		 46, 47, 50, 53, 54, 56, 58, 60, 61, 61, 63, 64, 65, 66, 67, 68, 69, 71,
		 71, 71, 73, 74, 73, 72, 73, 74, 52, 50, 49, 47, 47, 47, 47, 48, 50, 53,
		 54, 57, 59, 61, 63, 63, 66, 67, 68, 70, 70, 72, 73, 75, 75, 75, 77, 75,
		 75, 76, 75, 74, 53, 50, 50, 48, 48, 48, 47, 49, 51, 54, 55, 58, 59, 62,
		 64, 64, 67, 68, 69, 71, 71, 73, 74, 76, 77, 77, 78, 78, 78, 76, 77, 78,
		 54, 52, 51, 49, 49, 49, 48, 49, 52, 55, 55, 58, 60, 62, 64, 65, 68, 69,
		 71, 73, 73, 75, 76, 78, 79, 79, 80, 80, 79, 80, 79, 78, 56, 54, 53, 51,
		 51, 51, 49, 51, 53, 55, 56, 59, 61, 63, 66, 66, 70, 71, 73, 75, 76, 78,
		 79, 81, 82, 82, 83, 81, 83, 81, 81, 82, 57, 54, 53, 52, 51, 51, 50, 51,
		 53, 56, 56, 60, 61, 63, 66, 67, 70, 71, 73, 76, 76, 79, 80, 82, 82, 83,
		 84, 85, 83, 84, 84, 82, 60, 57, 56, 54, 53, 53, 52, 53, 55, 58, 58, 61,
		 63, 65, 68, 68, 72, 73, 75, 78, 79, 82, 83, 85, 86, 86, 88, 86, 87, 86,
		 85, 86, 61, 58, 57, 55, 55, 54, 53, 54, 56, 58, 59, 62, 64, 66, 69, 69,
		 73, 74, 76, 79, 80, 83, 84, 86, 87, 88, 89, 89, 88, 88, 88, 86, 63, 60,
		 59, 57, 56, 56, 54, 55, 57, 60, 60, 63, 65, 67, 70, 71, 75, 76, 78, 81,
		 82, 85, 86, 89, 90, 90, 92, 91, 91, 90, 89, 91, 64, 61, 60, 58, 57, 57,
		 55, 56, 58, 60, 61, 64, 66, 68, 70, 71, 75, 77, 79, 82, 82, 86, 87, 90,
		 91, 91, 93, 93, 93, 92, 93, 91, 65, 61, 60, 58, 57, 57, 55, 56, 58, 61,
		 61, 64, 66, 68, 71, 71, 75, 77, 79, 82, 83, 86, 88, 90, 91, 91, 93, 94,
		 95, 95, 93, 95, 67, 63, 62, 60, 59, 59, 57, 58, 60, 62, 63, 66, 67, 69,
		 72, 73, 77, 78, 80, 83, 84, 88, 89, 92, 93, 93, 95, 95, 96, 96, 97, 95,
		 67, 64, 63, 61, 60, 60, 58, 58, 61, 61, 63, 65, 67, 70, 70, 74, 75, 78,
		 80, 81, 85, 86, 89, 91, 93, 94, 95, 97, 97, 98, 98, 100, 68, 65, 64, 62,
		 61, 60, 59, 58, 61, 61, 64, 65, 67, 69, 71, 73, 75, 78, 79, 83, 83, 87,
		 88, 91, 93, 95, 96, 97, 99, 98, 100, 100, 69, 65, 65, 62, 62, 61, 60,
		 59, 61, 62, 64, 65, 68, 68, 72, 72, 76, 76, 80, 81, 84, 86, 88, 90, 92,
		 95, 96, 98, 98, 100, 100, 101, 70, 66, 66, 63, 63, 62, 61, 60, 60, 63,
		 64, 66, 67, 69, 71, 73, 75, 77, 79, 81, 84, 85, 88, 89, 93, 93, 97, 98,
		 100, 100, 102, 101, 71, 67, 67, 64, 64, 62, 62, 60, 60, 64, 64, 67, 67,
		 70, 70, 74, 74, 78, 78, 82, 82, 86, 86, 91, 91, 95, 95, 100, 100, 101,
		 101, 104,
		 /* Size 4x8 */
		 31, 47, 53, 63, 36, 47, 50, 59, 46, 52, 55, 61, 45, 53, 63, 70, 49, 55,
		 71, 77, 54, 58, 77, 86, 59, 61, 81, 94, 63, 65, 80, 95,
		 /* Size 8x4 */
		 31, 36, 46, 45, 49, 54, 59, 63, 47, 47, 52, 53, 55, 58, 61, 65, 53, 50,
		 55, 63, 71, 77, 81, 80, 63, 59, 61, 70, 77, 86, 94, 95,
		 /* Size 8x16 */
		 32, 33, 45, 49, 52, 57, 64, 68, 31, 34, 45, 46, 49, 53, 60, 64, 33, 37,
		 46, 45, 47, 51, 57, 61, 37, 43, 47, 45, 47, 50, 55, 59, 42, 44, 49, 49,
		 50, 53, 58, 60, 49, 47, 52, 53, 54, 57, 61, 63, 48, 46, 51, 57, 59, 61,
		 66, 67, 50, 46, 52, 59, 63, 66, 71, 71, 52, 47, 53, 61, 66, 71, 75, 74,
		 54, 49, 54, 62, 68, 73, 79, 79, 57, 51, 55, 64, 70, 76, 83, 83, 61, 55,
		 58, 66, 73, 80, 87, 87, 64, 57, 60, 68, 75, 83, 91, 91, 66, 59, 61, 69,
		 77, 84, 93, 95, 68, 61, 61, 68, 77, 86, 94, 97, 70, 63, 61, 67, 75, 83,
		 92, 98,
		 /* Size 16x8 */
		 32, 31, 33, 37, 42, 49, 48, 50, 52, 54, 57, 61, 64, 66, 68, 70, 33, 34,
		 37, 43, 44, 47, 46, 46, 47, 49, 51, 55, 57, 59, 61, 63, 45, 45, 46, 47,
		 49, 52, 51, 52, 53, 54, 55, 58, 60, 61, 61, 61, 49, 46, 45, 45, 49, 53,
		 57, 59, 61, 62, 64, 66, 68, 69, 68, 67, 52, 49, 47, 47, 50, 54, 59, 63,
		 66, 68, 70, 73, 75, 77, 77, 75, 57, 53, 51, 50, 53, 57, 61, 66, 71, 73,
		 76, 80, 83, 84, 86, 83, 64, 60, 57, 55, 58, 61, 66, 71, 75, 79, 83, 87,
		 91, 93, 94, 92, 68, 64, 61, 59, 60, 63, 67, 71, 74, 79, 83, 87, 91, 95,
		 97, 98,
		 /* Size 16x32 */
		 32, 31, 33, 37, 45, 48, 49, 50, 52, 56, 57, 63, 64, 67, 68, 68, 31, 31,
		 34, 38, 45, 47, 47, 48, 50, 53, 54, 60, 61, 63, 64, 65, 31, 32, 34, 39,
		 45, 46, 46, 47, 49, 52, 53, 59, 60, 62, 64, 65, 30, 32, 35, 40, 44, 46,
		 45, 46, 48, 51, 52, 57, 58, 60, 61, 62, 33, 35, 37, 42, 46, 47, 45, 46,
		 47, 50, 51, 56, 57, 60, 61, 62, 33, 36, 38, 43, 46, 47, 46, 46, 47, 50,
		 51, 56, 57, 59, 60, 60, 37, 40, 43, 47, 47, 47, 45, 46, 47, 49, 50, 54,
		 55, 57, 59, 61, 39, 41, 43, 47, 48, 48, 47, 47, 48, 50, 51, 55, 56, 57,
		 58, 59, 42, 43, 44, 47, 49, 50, 49, 50, 50, 53, 53, 57, 58, 60, 60, 59,
		 47, 46, 46, 48, 51, 52, 53, 53, 53, 55, 56, 60, 61, 61, 61, 62, 49, 46,
		 47, 48, 52, 53, 53, 54, 54, 56, 57, 60, 61, 63, 63, 62, 48, 46, 46, 47,
		 51, 53, 56, 56, 57, 59, 60, 64, 64, 65, 64, 65, 48, 45, 46, 46, 51, 53,
		 57, 57, 59, 61, 61, 65, 66, 66, 67, 65, 49, 45, 45, 46, 51, 53, 58, 59,
		 61, 63, 64, 67, 68, 70, 67, 68, 50, 46, 46, 46, 52, 54, 59, 61, 63, 65,
		 66, 70, 71, 70, 71, 68, 50, 46, 46, 46, 52, 54, 59, 61, 64, 66, 67, 71,
		 71, 73, 71, 72, 52, 48, 47, 47, 53, 54, 61, 63, 66, 70, 71, 75, 75, 75,
		 74, 72, 53, 49, 48, 48, 53, 55, 61, 64, 67, 71, 72, 76, 77, 77, 75, 76,
		 54, 50, 49, 49, 54, 55, 62, 65, 68, 72, 73, 78, 79, 80, 79, 76, 56, 51,
		 51, 50, 55, 56, 63, 66, 70, 74, 76, 81, 82, 81, 80, 80, 57, 52, 51, 50,
		 55, 56, 64, 66, 70, 75, 76, 82, 83, 85, 83, 80, 60, 54, 54, 52, 57, 58,
		 65, 68, 72, 77, 79, 85, 86, 86, 85, 84, 61, 56, 55, 53, 58, 59, 66, 69,
		 73, 79, 80, 86, 87, 89, 87, 84, 63, 57, 56, 55, 59, 60, 67, 70, 75, 80,
		 82, 89, 90, 91, 89, 89, 64, 58, 57, 56, 60, 61, 68, 71, 75, 81, 83, 90,
		 91, 93, 91, 89, 64, 59, 58, 56, 60, 61, 68, 71, 75, 81, 83, 90, 91, 94,
		 94, 93, 66, 60, 59, 57, 61, 63, 69, 72, 77, 82, 84, 92, 93, 94, 95, 93,
		 67, 61, 60, 58, 61, 63, 69, 70, 78, 80, 85, 90, 93, 96, 97, 97, 68, 62,
		 61, 59, 61, 64, 68, 71, 77, 79, 86, 88, 94, 96, 97, 98, 69, 63, 62, 59,
		 61, 65, 68, 72, 76, 80, 85, 88, 94, 95, 99, 99, 70, 63, 63, 60, 61, 66,
		 67, 73, 75, 81, 83, 89, 92, 97, 98, 99, 70, 64, 64, 61, 61, 67, 67, 74,
		 74, 82, 82, 90, 90, 98, 98, 102,
		 /* Size 32x16 */
		 32, 31, 31, 30, 33, 33, 37, 39, 42, 47, 49, 48, 48, 49, 50, 50, 52, 53,
		 54, 56, 57, 60, 61, 63, 64, 64, 66, 67, 68, 69, 70, 70, 31, 31, 32, 32,
		 35, 36, 40, 41, 43, 46, 46, 46, 45, 45, 46, 46, 48, 49, 50, 51, 52, 54,
		 56, 57, 58, 59, 60, 61, 62, 63, 63, 64, 33, 34, 34, 35, 37, 38, 43, 43,
		 44, 46, 47, 46, 46, 45, 46, 46, 47, 48, 49, 51, 51, 54, 55, 56, 57, 58,
		 59, 60, 61, 62, 63, 64, 37, 38, 39, 40, 42, 43, 47, 47, 47, 48, 48, 47,
		 46, 46, 46, 46, 47, 48, 49, 50, 50, 52, 53, 55, 56, 56, 57, 58, 59, 59,
		 60, 61, 45, 45, 45, 44, 46, 46, 47, 48, 49, 51, 52, 51, 51, 51, 52, 52,
		 53, 53, 54, 55, 55, 57, 58, 59, 60, 60, 61, 61, 61, 61, 61, 61, 48, 47,
		 46, 46, 47, 47, 47, 48, 50, 52, 53, 53, 53, 53, 54, 54, 54, 55, 55, 56,
		 56, 58, 59, 60, 61, 61, 63, 63, 64, 65, 66, 67, 49, 47, 46, 45, 45, 46,
		 45, 47, 49, 53, 53, 56, 57, 58, 59, 59, 61, 61, 62, 63, 64, 65, 66, 67,
		 68, 68, 69, 69, 68, 68, 67, 67, 50, 48, 47, 46, 46, 46, 46, 47, 50, 53,
		 54, 56, 57, 59, 61, 61, 63, 64, 65, 66, 66, 68, 69, 70, 71, 71, 72, 70,
		 71, 72, 73, 74, 52, 50, 49, 48, 47, 47, 47, 48, 50, 53, 54, 57, 59, 61,
		 63, 64, 66, 67, 68, 70, 70, 72, 73, 75, 75, 75, 77, 78, 77, 76, 75, 74,
		 56, 53, 52, 51, 50, 50, 49, 50, 53, 55, 56, 59, 61, 63, 65, 66, 70, 71,
		 72, 74, 75, 77, 79, 80, 81, 81, 82, 80, 79, 80, 81, 82, 57, 54, 53, 52,
		 51, 51, 50, 51, 53, 56, 57, 60, 61, 64, 66, 67, 71, 72, 73, 76, 76, 79,
		 80, 82, 83, 83, 84, 85, 86, 85, 83, 82, 63, 60, 59, 57, 56, 56, 54, 55,
		 57, 60, 60, 64, 65, 67, 70, 71, 75, 76, 78, 81, 82, 85, 86, 89, 90, 90,
		 92, 90, 88, 88, 89, 90, 64, 61, 60, 58, 57, 57, 55, 56, 58, 61, 61, 64,
		 66, 68, 71, 71, 75, 77, 79, 82, 83, 86, 87, 90, 91, 91, 93, 93, 94, 94,
		 92, 90, 67, 63, 62, 60, 60, 59, 57, 57, 60, 61, 63, 65, 66, 70, 70, 73,
		 75, 77, 80, 81, 85, 86, 89, 91, 93, 94, 94, 96, 96, 95, 97, 98, 68, 64,
		 64, 61, 61, 60, 59, 58, 60, 61, 63, 64, 67, 67, 71, 71, 74, 75, 79, 80,
		 83, 85, 87, 89, 91, 94, 95, 97, 97, 99, 98, 98, 68, 65, 65, 62, 62, 60,
		 61, 59, 59, 62, 62, 65, 65, 68, 68, 72, 72, 76, 76, 80, 80, 84, 84, 89,
		 89, 93, 93, 97, 98, 99, 99, 102,
		 /* Size 4x16 */
		 31, 48, 56, 67, 32, 46, 52, 62, 35, 47, 50, 60, 40, 47, 49, 57, 43, 50,
		 53, 60, 46, 53, 56, 63, 45, 53, 61, 66, 46, 54, 65, 70, 48, 54, 70, 75,
		 50, 55, 72, 80, 52, 56, 75, 85, 56, 59, 79, 89, 58, 61, 81, 93, 60, 63,
		 82, 94, 62, 64, 79, 96, 63, 66, 81, 97,
		 /* Size 16x4 */
		 31, 32, 35, 40, 43, 46, 45, 46, 48, 50, 52, 56, 58, 60, 62, 63, 48, 46,
		 47, 47, 50, 53, 53, 54, 54, 55, 56, 59, 61, 63, 64, 66, 56, 52, 50, 49,
		 53, 56, 61, 65, 70, 72, 75, 79, 81, 82, 79, 81, 67, 62, 60, 57, 60, 63,
		 66, 70, 75, 80, 85, 89, 93, 94, 96, 97,
		 /* Size 8x32 */
		 32, 33, 45, 49, 52, 57, 64, 68, 31, 34, 45, 47, 50, 54, 61, 64, 31, 34,
		 45, 46, 49, 53, 60, 64, 30, 35, 44, 45, 48, 52, 58, 61, 33, 37, 46, 45,
		 47, 51, 57, 61, 33, 38, 46, 46, 47, 51, 57, 60, 37, 43, 47, 45, 47, 50,
		 55, 59, 39, 43, 48, 47, 48, 51, 56, 58, 42, 44, 49, 49, 50, 53, 58, 60,
		 47, 46, 51, 53, 53, 56, 61, 61, 49, 47, 52, 53, 54, 57, 61, 63, 48, 46,
		 51, 56, 57, 60, 64, 64, 48, 46, 51, 57, 59, 61, 66, 67, 49, 45, 51, 58,
		 61, 64, 68, 67, 50, 46, 52, 59, 63, 66, 71, 71, 50, 46, 52, 59, 64, 67,
		 71, 71, 52, 47, 53, 61, 66, 71, 75, 74, 53, 48, 53, 61, 67, 72, 77, 75,
		 54, 49, 54, 62, 68, 73, 79, 79, 56, 51, 55, 63, 70, 76, 82, 80, 57, 51,
		 55, 64, 70, 76, 83, 83, 60, 54, 57, 65, 72, 79, 86, 85, 61, 55, 58, 66,
		 73, 80, 87, 87, 63, 56, 59, 67, 75, 82, 90, 89, 64, 57, 60, 68, 75, 83,
		 91, 91, 64, 58, 60, 68, 75, 83, 91, 94, 66, 59, 61, 69, 77, 84, 93, 95,
		 67, 60, 61, 69, 78, 85, 93, 97, 68, 61, 61, 68, 77, 86, 94, 97, 69, 62,
		 61, 68, 76, 85, 94, 99, 70, 63, 61, 67, 75, 83, 92, 98, 70, 64, 61, 67,
		 74, 82, 90, 98,
		 /* Size 32x8 */
		 32, 31, 31, 30, 33, 33, 37, 39, 42, 47, 49, 48, 48, 49, 50, 50, 52, 53,
		 54, 56, 57, 60, 61, 63, 64, 64, 66, 67, 68, 69, 70, 70, 33, 34, 34, 35,
		 37, 38, 43, 43, 44, 46, 47, 46, 46, 45, 46, 46, 47, 48, 49, 51, 51, 54,
		 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 45, 45, 45, 44, 46, 46, 47, 48,
		 49, 51, 52, 51, 51, 51, 52, 52, 53, 53, 54, 55, 55, 57, 58, 59, 60, 60,
		 61, 61, 61, 61, 61, 61, 49, 47, 46, 45, 45, 46, 45, 47, 49, 53, 53, 56,
		 57, 58, 59, 59, 61, 61, 62, 63, 64, 65, 66, 67, 68, 68, 69, 69, 68, 68,
		 67, 67, 52, 50, 49, 48, 47, 47, 47, 48, 50, 53, 54, 57, 59, 61, 63, 64,
		 66, 67, 68, 70, 70, 72, 73, 75, 75, 75, 77, 78, 77, 76, 75, 74, 57, 54,
		 53, 52, 51, 51, 50, 51, 53, 56, 57, 60, 61, 64, 66, 67, 71, 72, 73, 76,
		 76, 79, 80, 82, 83, 83, 84, 85, 86, 85, 83, 82, 64, 61, 60, 58, 57, 57,
		 55, 56, 58, 61, 61, 64, 66, 68, 71, 71, 75, 77, 79, 82, 83, 86, 87, 90,
		 91, 91, 93, 93, 94, 94, 92, 90, 68, 64, 64, 61, 61, 60, 59, 58, 60, 61,
		 63, 64, 67, 67, 71, 71, 74, 75, 79, 80, 83, 85, 87, 89, 91, 94, 95, 97,
		 97, 99, 98, 98},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 34, 53, 75, 34, 49, 64, 81, 53, 64, 91, 112, 75, 81, 112, 140,
		 /* Size 8x8 */
		 32, 32, 34, 39, 50, 62, 76, 84, 32, 33, 35, 40, 48, 59, 71, 79, 34, 35,
		 39, 46, 53, 63, 74, 81, 39, 40, 46, 56, 65, 75, 86, 92, 50, 48, 53, 65,
		 78, 90, 101, 106, 62, 59, 63, 75, 90, 105, 118, 123, 76, 71, 74, 86,
		 101, 118, 134, 142, 84, 79, 81, 92, 106, 123, 142, 153,
		 /* Size 16x16 */
		 32, 31, 31, 32, 33, 36, 39, 44, 48, 54, 59, 66, 74, 81, 86, 91, 31, 32,
		 32, 32, 33, 35, 38, 42, 46, 51, 56, 63, 70, 77, 81, 86, 31, 32, 32, 33,
		 34, 35, 38, 41, 45, 49, 54, 60, 67, 73, 77, 82, 32, 32, 33, 34, 36, 37,
		 40, 42, 45, 49, 53, 59, 66, 71, 75, 80, 33, 33, 34, 36, 38, 42, 44, 46,
		 50, 53, 57, 63, 69, 74, 78, 80, 36, 35, 35, 37, 42, 48, 50, 54, 57, 60,
		 64, 69, 75, 80, 84, 85, 39, 38, 38, 40, 44, 50, 54, 58, 61, 65, 69, 74,
		 80, 85, 89, 91, 44, 42, 41, 42, 46, 54, 58, 63, 67, 71, 75, 80, 86, 91,
		 95, 97, 48, 46, 45, 45, 50, 57, 61, 67, 71, 76, 80, 86, 93, 98, 101,
		 104, 54, 51, 49, 49, 53, 60, 65, 71, 76, 82, 87, 93, 100, 105, 109, 112,
		 59, 56, 54, 53, 57, 64, 69, 75, 80, 87, 92, 99, 106, 112, 116, 120, 66,
		 63, 60, 59, 63, 69, 74, 80, 86, 93, 99, 107, 115, 121, 125, 129, 74, 70,
		 67, 66, 69, 75, 80, 86, 93, 100, 106, 115, 123, 130, 135, 138, 81, 77,
		 73, 71, 74, 80, 85, 91, 98, 105, 112, 121, 130, 137, 142, 148, 86, 81,
		 77, 75, 78, 84, 89, 95, 101, 109, 116, 125, 135, 142, 147, 153, 91, 86,
		 82, 80, 80, 85, 91, 97, 104, 112, 120, 129, 138, 148, 153, 159,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 32, 32, 33, 34, 36, 36, 39, 41, 44, 46, 48, 52,
		 54, 58, 59, 65, 66, 71, 74, 80, 81, 83, 86, 89, 91, 93, 31, 32, 32, 32,
		 32, 32, 32, 32, 33, 34, 35, 35, 38, 39, 42, 44, 46, 50, 51, 56, 56, 62,
		 63, 68, 71, 76, 77, 78, 82, 84, 86, 88, 31, 32, 32, 32, 32, 32, 32, 32,
		 33, 34, 35, 35, 38, 39, 42, 44, 46, 49, 51, 55, 56, 61, 63, 67, 70, 75,
		 77, 78, 81, 84, 86, 88, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34,
		 37, 38, 41, 42, 44, 48, 49, 53, 54, 59, 60, 65, 68, 72, 74, 75, 78, 80,
		 82, 84, 31, 32, 32, 32, 32, 33, 33, 33, 34, 34, 35, 35, 38, 39, 41, 43,
		 45, 48, 49, 53, 54, 59, 60, 65, 67, 72, 73, 74, 77, 80, 82, 84, 31, 32,
		 32, 32, 33, 33, 33, 34, 35, 35, 36, 36, 39, 40, 42, 44, 45, 48, 50, 53,
		 54, 59, 60, 64, 67, 71, 73, 74, 77, 79, 81, 83, 32, 32, 32, 32, 33, 33,
		 34, 35, 36, 36, 37, 38, 40, 40, 42, 44, 45, 48, 49, 53, 53, 58, 59, 63,
		 66, 70, 71, 72, 75, 78, 80, 83, 32, 32, 32, 32, 33, 34, 35, 35, 36, 37,
		 38, 38, 40, 41, 42, 44, 46, 48, 49, 53, 53, 58, 59, 63, 65, 69, 71, 72,
		 74, 77, 79, 80, 33, 33, 33, 33, 34, 35, 36, 36, 38, 39, 42, 42, 44, 45,
		 46, 48, 50, 52, 53, 57, 57, 62, 63, 67, 69, 73, 74, 75, 78, 79, 80, 81,
		 34, 34, 34, 33, 34, 35, 36, 37, 39, 39, 42, 43, 45, 46, 47, 49, 51, 53,
		 54, 58, 58, 63, 64, 68, 70, 74, 75, 76, 79, 81, 84, 86, 36, 35, 35, 34,
		 35, 36, 37, 38, 42, 42, 48, 48, 50, 51, 54, 55, 57, 59, 60, 63, 64, 68,
		 69, 73, 75, 79, 80, 81, 84, 85, 85, 86, 36, 35, 35, 34, 35, 36, 38, 38,
		 42, 43, 48, 49, 51, 52, 54, 55, 57, 59, 60, 64, 64, 68, 69, 73, 75, 79,
		 80, 81, 84, 86, 88, 91, 39, 38, 38, 37, 38, 39, 40, 40, 44, 45, 50, 51,
		 54, 55, 58, 59, 61, 64, 65, 68, 69, 73, 74, 78, 80, 84, 85, 86, 89, 91,
		 91, 91, 41, 39, 39, 38, 39, 40, 40, 41, 45, 46, 51, 52, 55, 56, 59, 61,
		 63, 65, 67, 70, 70, 75, 76, 80, 82, 86, 87, 88, 91, 92, 94, 96, 44, 42,
		 42, 41, 41, 42, 42, 42, 46, 47, 54, 54, 58, 59, 63, 65, 67, 70, 71, 75,
		 75, 79, 80, 84, 86, 90, 91, 92, 95, 97, 97, 97, 46, 44, 44, 42, 43, 44,
		 44, 44, 48, 49, 55, 55, 59, 61, 65, 67, 69, 72, 74, 77, 78, 82, 83, 87,
		 89, 93, 94, 95, 98, 98, 100, 103, 48, 46, 46, 44, 45, 45, 45, 46, 50,
		 51, 57, 57, 61, 63, 67, 69, 71, 74, 76, 80, 80, 85, 86, 90, 93, 96, 98,
		 99, 101, 104, 104, 103, 52, 50, 49, 48, 48, 48, 48, 48, 52, 53, 59, 59,
		 64, 65, 70, 72, 74, 78, 80, 84, 85, 90, 91, 95, 97, 101, 103, 104, 106,
		 106, 107, 110, 54, 51, 51, 49, 49, 50, 49, 49, 53, 54, 60, 60, 65, 67,
		 71, 74, 76, 80, 82, 86, 87, 92, 93, 97, 100, 104, 105, 106, 109, 112,
		 112, 110, 58, 56, 55, 53, 53, 53, 53, 53, 57, 58, 63, 64, 68, 70, 75,
		 77, 80, 84, 86, 91, 91, 97, 98, 103, 105, 110, 111, 112, 115, 114, 115,
		 118, 59, 56, 56, 54, 54, 54, 53, 53, 57, 58, 64, 64, 69, 70, 75, 78, 80,
		 85, 87, 91, 92, 98, 99, 103, 106, 110, 112, 113, 116, 119, 120, 119, 65,
		 62, 61, 59, 59, 59, 58, 58, 62, 63, 68, 68, 73, 75, 79, 82, 85, 90, 92,
		 97, 98, 105, 106, 111, 114, 118, 120, 121, 124, 123, 123, 126, 66, 63,
		 63, 60, 60, 60, 59, 59, 63, 64, 69, 69, 74, 76, 80, 83, 86, 91, 93, 98,
		 99, 106, 107, 112, 115, 119, 121, 122, 125, 128, 129, 126, 71, 68, 67,
		 65, 65, 64, 63, 63, 67, 68, 73, 73, 78, 80, 84, 87, 90, 95, 97, 103,
		 103, 111, 112, 117, 120, 125, 127, 128, 131, 132, 132, 135, 74, 71, 70,
		 68, 67, 67, 66, 65, 69, 70, 75, 75, 80, 82, 86, 89, 93, 97, 100, 105,
		 106, 114, 115, 120, 123, 128, 130, 131, 135, 135, 138, 136, 80, 76, 75,
		 72, 72, 71, 70, 69, 73, 74, 79, 79, 84, 86, 90, 93, 96, 101, 104, 110,
		 110, 118, 119, 125, 128, 134, 136, 137, 140, 142, 140, 144, 81, 77, 77,
		 74, 73, 73, 71, 71, 74, 75, 80, 80, 85, 87, 91, 94, 98, 103, 105, 111,
		 112, 120, 121, 127, 130, 136, 137, 139, 142, 145, 148, 144, 83, 78, 78,
		 75, 74, 74, 72, 72, 75, 76, 81, 81, 86, 88, 92, 95, 99, 104, 106, 112,
		 113, 121, 122, 128, 131, 137, 139, 140, 144, 148, 150, 155, 86, 82, 81,
		 78, 77, 77, 75, 74, 78, 79, 84, 84, 89, 91, 95, 98, 101, 106, 109, 115,
		 116, 124, 125, 131, 135, 140, 142, 144, 147, 149, 153, 155, 89, 84, 84,
		 80, 80, 79, 78, 77, 79, 81, 85, 86, 91, 92, 97, 98, 104, 106, 112, 114,
		 119, 123, 128, 132, 135, 142, 145, 148, 149, 153, 154, 159, 91, 86, 86,
		 82, 82, 81, 80, 79, 80, 84, 85, 88, 91, 94, 97, 100, 104, 107, 112, 115,
		 120, 123, 129, 132, 138, 140, 148, 150, 153, 154, 159, 159, 93, 88, 88,
		 84, 84, 83, 83, 80, 81, 86, 86, 91, 91, 96, 97, 103, 103, 110, 110, 118,
		 119, 126, 126, 135, 136, 144, 144, 155, 155, 159, 159, 164,
		 /* Size 4x8 */
		 32, 35, 51, 77, 32, 36, 50, 72, 34, 42, 54, 75, 38, 51, 67, 87, 48, 59,
		 80, 103, 60, 68, 92, 119, 72, 79, 104, 135, 81, 86, 112, 144,
		 /* Size 8x4 */
		 32, 32, 34, 38, 48, 60, 72, 81, 35, 36, 42, 51, 59, 68, 79, 86, 51, 50,
		 54, 67, 80, 92, 104, 112, 77, 72, 75, 87, 103, 119, 135, 144,
		 /* Size 8x16 */
		 32, 31, 33, 40, 51, 65, 79, 87, 31, 32, 33, 39, 49, 61, 74, 82, 31, 32,
		 34, 38, 47, 59, 71, 79, 32, 33, 36, 40, 48, 58, 69, 77, 33, 34, 38, 44,
		 52, 62, 72, 78, 36, 35, 42, 51, 58, 68, 78, 84, 39, 38, 44, 54, 63, 73,
		 84, 89, 44, 41, 46, 59, 69, 79, 90, 96, 48, 45, 50, 62, 74, 85, 96, 103,
		 53, 49, 53, 66, 79, 92, 103, 111, 58, 54, 57, 70, 84, 98, 110, 118, 66,
		 60, 63, 75, 90, 106, 119, 126, 74, 67, 69, 81, 97, 113, 128, 134, 81,
		 73, 75, 86, 102, 120, 135, 143, 86, 78, 78, 90, 106, 124, 140, 147, 91,
		 82, 80, 90, 103, 119, 137, 151,
		 /* Size 16x8 */
		 32, 31, 31, 32, 33, 36, 39, 44, 48, 53, 58, 66, 74, 81, 86, 91, 31, 32,
		 32, 33, 34, 35, 38, 41, 45, 49, 54, 60, 67, 73, 78, 82, 33, 33, 34, 36,
		 38, 42, 44, 46, 50, 53, 57, 63, 69, 75, 78, 80, 40, 39, 38, 40, 44, 51,
		 54, 59, 62, 66, 70, 75, 81, 86, 90, 90, 51, 49, 47, 48, 52, 58, 63, 69,
		 74, 79, 84, 90, 97, 102, 106, 103, 65, 61, 59, 58, 62, 68, 73, 79, 85,
		 92, 98, 106, 113, 120, 124, 119, 79, 74, 71, 69, 72, 78, 84, 90, 96,
		 103, 110, 119, 128, 135, 140, 137, 87, 82, 79, 77, 78, 84, 89, 96, 103,
		 111, 118, 126, 134, 143, 147, 151,
		 /* Size 16x32 */
		 32, 31, 31, 32, 33, 36, 40, 44, 51, 53, 65, 66, 79, 81, 87, 90, 31, 32,
		 32, 32, 33, 35, 39, 42, 49, 51, 62, 63, 75, 77, 83, 85, 31, 32, 32, 32,
		 33, 35, 39, 42, 49, 51, 61, 62, 74, 76, 82, 85, 31, 32, 32, 33, 33, 34,
		 38, 41, 47, 49, 59, 60, 72, 74, 79, 81, 31, 32, 32, 33, 34, 35, 38, 41,
		 47, 49, 59, 60, 71, 73, 79, 81, 32, 32, 33, 34, 35, 36, 39, 42, 48, 50,
		 59, 60, 71, 72, 78, 80, 32, 32, 33, 35, 36, 37, 40, 42, 48, 49, 58, 59,
		 69, 71, 77, 80, 32, 33, 33, 35, 36, 38, 41, 42, 48, 49, 58, 59, 69, 70,
		 75, 77, 33, 33, 34, 36, 38, 41, 44, 46, 52, 53, 62, 63, 72, 74, 78, 78,
		 34, 34, 34, 37, 39, 42, 45, 48, 53, 54, 63, 64, 73, 75, 80, 83, 36, 34,
		 35, 38, 42, 48, 51, 54, 58, 60, 68, 69, 78, 80, 84, 83, 36, 35, 35, 38,
		 42, 48, 51, 54, 59, 60, 68, 69, 79, 80, 85, 87, 39, 37, 38, 40, 44, 50,
		 54, 58, 63, 65, 73, 74, 84, 85, 89, 88, 40, 38, 39, 41, 45, 51, 56, 59,
		 65, 67, 75, 76, 85, 87, 90, 93, 44, 41, 41, 43, 46, 53, 59, 63, 69, 71,
		 79, 80, 90, 91, 96, 93, 46, 43, 43, 44, 48, 55, 60, 65, 72, 73, 82, 83,
		 93, 94, 97, 100, 48, 45, 45, 46, 50, 56, 62, 67, 74, 76, 85, 86, 96, 98,
		 103, 100, 52, 48, 48, 49, 52, 59, 65, 70, 78, 80, 90, 91, 101, 103, 105,
		 107, 53, 49, 49, 50, 53, 60, 66, 71, 79, 82, 92, 93, 103, 105, 111, 107,
		 58, 53, 53, 53, 57, 63, 69, 74, 83, 86, 97, 98, 109, 111, 113, 115, 58,
		 54, 54, 54, 57, 63, 70, 75, 84, 87, 98, 99, 110, 112, 118, 115, 65, 60,
		 59, 58, 62, 68, 74, 79, 89, 92, 105, 106, 118, 119, 122, 123, 66, 61,
		 60, 59, 63, 69, 75, 80, 90, 93, 106, 107, 119, 121, 126, 123, 71, 65,
		 65, 63, 67, 73, 79, 84, 94, 97, 111, 112, 125, 127, 131, 132, 74, 68,
		 67, 66, 69, 75, 81, 86, 97, 100, 113, 115, 128, 130, 134, 132, 79, 72,
		 72, 70, 73, 79, 85, 90, 101, 104, 118, 119, 133, 135, 141, 140, 81, 74,
		 73, 71, 75, 80, 86, 91, 102, 105, 120, 121, 135, 137, 143, 140, 82, 75,
		 74, 72, 75, 81, 87, 92, 103, 106, 121, 122, 136, 139, 147, 151, 86, 78,
		 78, 75, 78, 84, 90, 95, 106, 109, 124, 125, 140, 142, 147, 151, 88, 81,
		 80, 77, 80, 86, 90, 98, 105, 112, 122, 127, 140, 144, 152, 155, 91, 83,
		 82, 79, 80, 88, 90, 100, 103, 114, 119, 130, 137, 148, 151, 155, 93, 85,
		 85, 81, 81, 90, 90, 102, 103, 117, 117, 134, 134, 151, 152, 160,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 32, 32, 32, 33, 34, 36, 36, 39, 40, 44, 46, 48, 52,
		 53, 58, 58, 65, 66, 71, 74, 79, 81, 82, 86, 88, 91, 93, 31, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 35, 37, 38, 41, 43, 45, 48, 49, 53, 54, 60,
		 61, 65, 68, 72, 74, 75, 78, 81, 83, 85, 31, 32, 32, 32, 32, 33, 33, 33,
		 34, 34, 35, 35, 38, 39, 41, 43, 45, 48, 49, 53, 54, 59, 60, 65, 67, 72,
		 73, 74, 78, 80, 82, 85, 32, 32, 32, 33, 33, 34, 35, 35, 36, 37, 38, 38,
		 40, 41, 43, 44, 46, 49, 50, 53, 54, 58, 59, 63, 66, 70, 71, 72, 75, 77,
		 79, 81, 33, 33, 33, 33, 34, 35, 36, 36, 38, 39, 42, 42, 44, 45, 46, 48,
		 50, 52, 53, 57, 57, 62, 63, 67, 69, 73, 75, 75, 78, 80, 80, 81, 36, 35,
		 35, 34, 35, 36, 37, 38, 41, 42, 48, 48, 50, 51, 53, 55, 56, 59, 60, 63,
		 63, 68, 69, 73, 75, 79, 80, 81, 84, 86, 88, 90, 40, 39, 39, 38, 38, 39,
		 40, 41, 44, 45, 51, 51, 54, 56, 59, 60, 62, 65, 66, 69, 70, 74, 75, 79,
		 81, 85, 86, 87, 90, 90, 90, 90, 44, 42, 42, 41, 41, 42, 42, 42, 46, 48,
		 54, 54, 58, 59, 63, 65, 67, 70, 71, 74, 75, 79, 80, 84, 86, 90, 91, 92,
		 95, 98, 100, 102, 51, 49, 49, 47, 47, 48, 48, 48, 52, 53, 58, 59, 63,
		 65, 69, 72, 74, 78, 79, 83, 84, 89, 90, 94, 97, 101, 102, 103, 106, 105,
		 103, 103, 53, 51, 51, 49, 49, 50, 49, 49, 53, 54, 60, 60, 65, 67, 71,
		 73, 76, 80, 82, 86, 87, 92, 93, 97, 100, 104, 105, 106, 109, 112, 114,
		 117, 65, 62, 61, 59, 59, 59, 58, 58, 62, 63, 68, 68, 73, 75, 79, 82, 85,
		 90, 92, 97, 98, 105, 106, 111, 113, 118, 120, 121, 124, 122, 119, 117,
		 66, 63, 62, 60, 60, 60, 59, 59, 63, 64, 69, 69, 74, 76, 80, 83, 86, 91,
		 93, 98, 99, 106, 107, 112, 115, 119, 121, 122, 125, 127, 130, 134, 79,
		 75, 74, 72, 71, 71, 69, 69, 72, 73, 78, 79, 84, 85, 90, 93, 96, 101,
		 103, 109, 110, 118, 119, 125, 128, 133, 135, 136, 140, 140, 137, 134,
		 81, 77, 76, 74, 73, 72, 71, 70, 74, 75, 80, 80, 85, 87, 91, 94, 98, 103,
		 105, 111, 112, 119, 121, 127, 130, 135, 137, 139, 142, 144, 148, 151,
		 87, 83, 82, 79, 79, 78, 77, 75, 78, 80, 84, 85, 89, 90, 96, 97, 103,
		 105, 111, 113, 118, 122, 126, 131, 134, 141, 143, 147, 147, 152, 151,
		 152, 90, 85, 85, 81, 81, 80, 80, 77, 78, 83, 83, 87, 88, 93, 93, 100,
		 100, 107, 107, 115, 115, 123, 123, 132, 132, 140, 140, 151, 151, 155,
		 155, 160,
		 /* Size 4x16 */
		 31, 36, 53, 81, 32, 35, 51, 76, 32, 35, 49, 73, 32, 37, 49, 71, 33, 41,
		 53, 74, 34, 48, 60, 80, 37, 50, 65, 85, 41, 53, 71, 91, 45, 56, 76, 98,
		 49, 60, 82, 105, 54, 63, 87, 112, 61, 69, 93, 121, 68, 75, 100, 130, 74,
		 80, 105, 137, 78, 84, 109, 142, 83, 88, 114, 148,
		 /* Size 16x4 */
		 31, 32, 32, 32, 33, 34, 37, 41, 45, 49, 54, 61, 68, 74, 78, 83, 36, 35,
		 35, 37, 41, 48, 50, 53, 56, 60, 63, 69, 75, 80, 84, 88, 53, 51, 49, 49,
		 53, 60, 65, 71, 76, 82, 87, 93, 100, 105, 109, 114, 81, 76, 73, 71, 74,
		 80, 85, 91, 98, 105, 112, 121, 130, 137, 142, 148,
		 /* Size 8x32 */
		 32, 31, 33, 40, 51, 65, 79, 87, 31, 32, 33, 39, 49, 62, 75, 83, 31, 32,
		 33, 39, 49, 61, 74, 82, 31, 32, 33, 38, 47, 59, 72, 79, 31, 32, 34, 38,
		 47, 59, 71, 79, 32, 33, 35, 39, 48, 59, 71, 78, 32, 33, 36, 40, 48, 58,
		 69, 77, 32, 33, 36, 41, 48, 58, 69, 75, 33, 34, 38, 44, 52, 62, 72, 78,
		 34, 34, 39, 45, 53, 63, 73, 80, 36, 35, 42, 51, 58, 68, 78, 84, 36, 35,
		 42, 51, 59, 68, 79, 85, 39, 38, 44, 54, 63, 73, 84, 89, 40, 39, 45, 56,
		 65, 75, 85, 90, 44, 41, 46, 59, 69, 79, 90, 96, 46, 43, 48, 60, 72, 82,
		 93, 97, 48, 45, 50, 62, 74, 85, 96, 103, 52, 48, 52, 65, 78, 90, 101,
		 105, 53, 49, 53, 66, 79, 92, 103, 111, 58, 53, 57, 69, 83, 97, 109, 113,
		 58, 54, 57, 70, 84, 98, 110, 118, 65, 59, 62, 74, 89, 105, 118, 122, 66,
		 60, 63, 75, 90, 106, 119, 126, 71, 65, 67, 79, 94, 111, 125, 131, 74,
		 67, 69, 81, 97, 113, 128, 134, 79, 72, 73, 85, 101, 118, 133, 141, 81,
		 73, 75, 86, 102, 120, 135, 143, 82, 74, 75, 87, 103, 121, 136, 147, 86,
		 78, 78, 90, 106, 124, 140, 147, 88, 80, 80, 90, 105, 122, 140, 152, 91,
		 82, 80, 90, 103, 119, 137, 151, 93, 85, 81, 90, 103, 117, 134, 152,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 32, 32, 32, 33, 34, 36, 36, 39, 40, 44, 46, 48, 52,
		 53, 58, 58, 65, 66, 71, 74, 79, 81, 82, 86, 88, 91, 93, 31, 32, 32, 32,
		 32, 33, 33, 33, 34, 34, 35, 35, 38, 39, 41, 43, 45, 48, 49, 53, 54, 59,
		 60, 65, 67, 72, 73, 74, 78, 80, 82, 85, 33, 33, 33, 33, 34, 35, 36, 36,
		 38, 39, 42, 42, 44, 45, 46, 48, 50, 52, 53, 57, 57, 62, 63, 67, 69, 73,
		 75, 75, 78, 80, 80, 81, 40, 39, 39, 38, 38, 39, 40, 41, 44, 45, 51, 51,
		 54, 56, 59, 60, 62, 65, 66, 69, 70, 74, 75, 79, 81, 85, 86, 87, 90, 90,
		 90, 90, 51, 49, 49, 47, 47, 48, 48, 48, 52, 53, 58, 59, 63, 65, 69, 72,
		 74, 78, 79, 83, 84, 89, 90, 94, 97, 101, 102, 103, 106, 105, 103, 103,
		 65, 62, 61, 59, 59, 59, 58, 58, 62, 63, 68, 68, 73, 75, 79, 82, 85, 90,
		 92, 97, 98, 105, 106, 111, 113, 118, 120, 121, 124, 122, 119, 117, 79,
		 75, 74, 72, 71, 71, 69, 69, 72, 73, 78, 79, 84, 85, 90, 93, 96, 101,
		 103, 109, 110, 118, 119, 125, 128, 133, 135, 136, 140, 140, 137, 134,
		 87, 83, 82, 79, 79, 78, 77, 75, 78, 80, 84, 85, 89, 90, 96, 97, 103,
		 105, 111, 113, 118, 122, 126, 131, 134, 141, 143, 147, 147, 152, 151,
		 152},
		{/* Chroma */
		 /* Size 4x4 */
		 32, 46, 49, 58, 46, 53, 55, 62, 49, 55, 70, 78, 58, 62, 78, 91,
		 /* Size 8x8 */
		 31, 34, 42, 47, 49, 54, 60, 64, 34, 39, 45, 46, 47, 51, 56, 59, 42, 45,
		 48, 49, 50, 53, 57, 60, 47, 46, 49, 55, 58, 61, 65, 66, 49, 47, 50, 58,
		 65, 69, 73, 74, 54, 51, 53, 61, 69, 76, 82, 83, 60, 56, 57, 65, 73, 82,
		 89, 92, 64, 59, 60, 66, 74, 83, 92, 96,
		 /* Size 16x16 */
		 32, 31, 31, 35, 40, 49, 48, 49, 50, 52, 54, 57, 61, 64, 66, 68, 31, 31,
		 32, 37, 41, 47, 47, 46, 48, 49, 51, 54, 57, 60, 62, 64, 31, 32, 34, 39,
		 43, 46, 46, 45, 46, 47, 49, 52, 55, 57, 59, 61, 35, 37, 39, 44, 46, 47,
		 46, 45, 46, 47, 48, 51, 53, 56, 57, 59, 40, 41, 43, 46, 48, 50, 49, 48,
		 49, 49, 51, 53, 55, 57, 59, 59, 49, 47, 46, 47, 50, 53, 53, 53, 54, 54,
		 55, 57, 59, 61, 62, 62, 48, 47, 46, 46, 49, 53, 54, 55, 56, 57, 58, 60,
		 62, 64, 65, 65, 49, 46, 45, 45, 48, 53, 55, 58, 60, 61, 62, 64, 66, 68,
		 69, 69, 50, 48, 46, 46, 49, 54, 56, 60, 61, 63, 65, 67, 69, 71, 72, 72,
		 52, 49, 47, 47, 49, 54, 57, 61, 63, 66, 68, 71, 73, 75, 76, 77, 54, 51,
		 49, 48, 51, 55, 58, 62, 65, 68, 71, 74, 76, 78, 80, 81, 57, 54, 52, 51,
		 53, 57, 60, 64, 67, 71, 74, 77, 80, 83, 84, 85, 61, 57, 55, 53, 55, 59,
		 62, 66, 69, 73, 76, 80, 84, 87, 89, 89, 64, 60, 57, 56, 57, 61, 64, 68,
		 71, 75, 78, 83, 87, 90, 92, 94, 66, 62, 59, 57, 59, 62, 65, 69, 72, 76,
		 80, 84, 89, 92, 94, 96, 68, 64, 61, 59, 59, 62, 65, 69, 72, 77, 81, 85,
		 89, 94, 96, 98,
		 /* Size 32x32 */
		 32, 31, 31, 30, 31, 33, 35, 36, 40, 41, 49, 49, 48, 48, 49, 50, 50, 52,
		 52, 54, 54, 57, 57, 60, 61, 63, 64, 65, 66, 67, 68, 69, 31, 31, 31, 31,
		 32, 34, 37, 38, 41, 42, 47, 47, 47, 47, 47, 47, 48, 49, 50, 52, 52, 54,
		 55, 57, 58, 60, 61, 61, 63, 64, 64, 65, 31, 31, 31, 31, 32, 35, 37, 39,
		 41, 42, 47, 47, 47, 46, 46, 47, 48, 49, 49, 51, 51, 54, 54, 56, 57, 59,
		 60, 61, 62, 63, 64, 65, 30, 31, 31, 32, 33, 35, 38, 40, 42, 42, 46, 46,
		 45, 45, 45, 45, 46, 47, 47, 49, 49, 52, 52, 54, 55, 57, 58, 58, 60, 61,
		 61, 62, 31, 32, 32, 33, 34, 37, 39, 41, 43, 43, 46, 46, 46, 45, 45, 46,
		 46, 47, 47, 49, 49, 51, 52, 54, 55, 57, 57, 58, 59, 60, 61, 62, 33, 34,
		 35, 35, 37, 39, 41, 43, 44, 45, 47, 47, 46, 46, 45, 46, 46, 47, 47, 49,
		 49, 51, 51, 53, 54, 56, 57, 57, 58, 59, 60, 61, 35, 37, 37, 38, 39, 41,
		 44, 46, 46, 46, 47, 47, 46, 46, 45, 46, 46, 47, 47, 48, 48, 50, 51, 52,
		 53, 55, 56, 56, 57, 58, 59, 61, 36, 38, 39, 40, 41, 43, 46, 47, 47, 47,
		 48, 47, 46, 46, 45, 46, 46, 46, 47, 48, 48, 50, 50, 52, 53, 54, 55, 55,
		 56, 57, 58, 58, 40, 41, 41, 42, 43, 44, 46, 47, 48, 48, 50, 49, 49, 49,
		 48, 49, 49, 49, 49, 51, 51, 52, 53, 54, 55, 57, 57, 58, 59, 59, 59, 59,
		 41, 42, 42, 42, 43, 45, 46, 47, 48, 48, 50, 50, 49, 49, 49, 49, 50, 50,
		 50, 52, 52, 53, 53, 55, 56, 57, 58, 58, 59, 60, 61, 62, 49, 47, 47, 46,
		 46, 47, 47, 48, 50, 50, 53, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 56,
		 57, 58, 59, 60, 61, 61, 62, 62, 62, 62, 49, 47, 47, 46, 46, 47, 47, 47,
		 49, 50, 53, 53, 53, 53, 54, 54, 54, 54, 54, 55, 56, 57, 57, 59, 59, 61,
		 61, 62, 63, 63, 64, 65, 48, 47, 47, 45, 46, 46, 46, 46, 49, 49, 53, 53,
		 54, 54, 55, 56, 56, 57, 57, 58, 58, 60, 60, 61, 62, 63, 64, 64, 65, 66,
		 65, 65, 48, 47, 46, 45, 45, 46, 46, 46, 49, 49, 53, 53, 54, 55, 56, 57,

		 57, 58, 58, 59, 60, 61, 61, 63, 63, 65, 65, 65, 66, 66, 67, 68, 49, 47,
		 46, 45, 45, 45, 45, 45, 48, 49, 53, 54, 55, 56, 58, 59, 60, 61, 61, 62,
		 62, 63, 64, 65, 66, 67, 68, 68, 69, 70, 69, 68, 50, 47, 47, 45, 46, 46,
		 46, 46, 49, 49, 54, 54, 56, 57, 59, 60, 60, 62, 62, 63, 64, 65, 65, 67,
		 68, 69, 69, 70, 70, 70, 71, 71, 50, 48, 48, 46, 46, 46, 46, 46, 49, 50,
		 54, 54, 56, 57, 60, 60, 61, 63, 63, 65, 65, 67, 67, 68, 69, 71, 71, 71,
		 72, 73, 72, 71, 52, 49, 49, 47, 47, 47, 47, 46, 49, 50, 54, 54, 57, 58,
		 61, 62, 63, 65, 65, 67, 67, 69, 70, 71, 72, 73, 74, 74, 75, 74, 74, 75,
		 52, 50, 49, 47, 47, 47, 47, 47, 49, 50, 54, 54, 57, 58, 61, 62, 63, 65,
		 66, 68, 68, 70, 71, 72, 73, 75, 75, 75, 76, 77, 77, 75, 54, 52, 51, 49,
		 49, 49, 48, 48, 51, 52, 55, 55, 58, 59, 62, 63, 65, 67, 68, 70, 70, 73,
		 73, 75, 76, 78, 78, 78, 79, 78, 78, 79, 54, 52, 51, 49, 49, 49, 48, 48,
		 51, 52, 55, 56, 58, 60, 62, 64, 65, 67, 68, 70, 71, 73, 74, 75, 76, 78,
		 78, 79, 80, 81, 81, 79, 57, 54, 54, 52, 51, 51, 50, 50, 52, 53, 56, 57,
		 60, 61, 63, 65, 67, 69, 70, 73, 73, 76, 77, 79, 80, 82, 82, 83, 84, 83,
		 82, 83, 57, 55, 54, 52, 52, 51, 51, 50, 53, 53, 57, 57, 60, 61, 64, 65,
		 67, 70, 71, 73, 74, 77, 77, 79, 80, 82, 83, 83, 84, 85, 85, 83, 60, 57,
		 56, 54, 54, 53, 52, 52, 54, 55, 58, 59, 61, 63, 65, 67, 68, 71, 72, 75,
		 75, 79, 79, 82, 83, 85, 86, 86, 87, 87, 86, 87, 61, 58, 57, 55, 55, 54,
		 53, 53, 55, 56, 59, 59, 62, 63, 66, 68, 69, 72, 73, 76, 76, 80, 80, 83,
		 84, 86, 87, 88, 89, 89, 89, 87, 63, 60, 59, 57, 57, 56, 55, 54, 57, 57,
		 60, 61, 63, 65, 67, 69, 71, 73, 75, 78, 78, 82, 82, 85, 86, 89, 89, 90,
		 91, 92, 90, 91, 64, 61, 60, 58, 57, 57, 56, 55, 57, 58, 61, 61, 64, 65,
		 68, 69, 71, 74, 75, 78, 78, 82, 83, 86, 87, 89, 90, 91, 92, 93, 94, 91,
		 65, 61, 61, 58, 58, 57, 56, 55, 58, 58, 61, 62, 64, 65, 68, 70, 71, 74,
		 75, 78, 79, 83, 83, 86, 88, 90, 91, 91, 93, 94, 94, 96, 66, 63, 62, 60,
		 59, 58, 57, 56, 59, 59, 62, 63, 65, 66, 69, 70, 72, 75, 76, 79, 80, 84,
		 84, 87, 89, 91, 92, 93, 94, 94, 96, 96, 67, 64, 63, 61, 60, 59, 58, 57,
		 59, 60, 62, 63, 66, 66, 70, 70, 73, 74, 77, 78, 81, 83, 85, 87, 89, 92,
		 93, 94, 94, 96, 96, 97, 68, 64, 64, 61, 61, 60, 59, 58, 59, 61, 62, 64,
		 65, 67, 69, 71, 72, 74, 77, 78, 81, 82, 85, 86, 89, 90, 94, 94, 96, 96,
		 98, 97, 69, 65, 65, 62, 62, 61, 61, 58, 59, 62, 62, 65, 65, 68, 68, 71,
		 71, 75, 75, 79, 79, 83, 83, 87, 87, 91, 91, 96, 96, 97, 97, 99,
		 /* Size 4x8 */
		 31, 47, 50, 61, 36, 47, 47, 57, 43, 50, 50, 58, 45, 53, 58, 65, 47, 54,
		 66, 74, 52, 56, 70, 82, 57, 60, 75, 90, 61, 63, 77, 93,
		 /* Size 8x4 */
		 31, 36, 43, 45, 47, 52, 57, 61, 47, 47, 50, 53, 54, 56, 60, 63, 50, 47,
		 50, 58, 66, 70, 75, 77, 61, 57, 58, 65, 74, 82, 90, 93,
		 /* Size 8x16 */
		 32, 32, 40, 49, 51, 57, 63, 67, 31, 33, 41, 47, 49, 54, 59, 63, 31, 35,
		 43, 46, 47, 51, 57, 60, 35, 39, 46, 46, 47, 50, 55, 58, 41, 43, 48, 49,
		 49, 52, 57, 59, 49, 47, 50, 53, 54, 57, 60, 62, 48, 46, 49, 54, 57, 60,
		 64, 65, 49, 45, 48, 56, 61, 64, 67, 69, 50, 46, 49, 57, 63, 67, 71, 73,
		 52, 48, 50, 58, 65, 71, 75, 77, 54, 50, 51, 59, 67, 73, 78, 81, 57, 52,
		 53, 61, 69, 77, 82, 85, 61, 55, 56, 63, 72, 80, 86, 88, 64, 58, 58, 65,
		 73, 82, 89, 92, 66, 59, 59, 66, 75, 84, 91, 94, 68, 61, 59, 65, 72, 81,
		 89, 95,
		 /* Size 16x8 */
		 32, 31, 31, 35, 41, 49, 48, 49, 50, 52, 54, 57, 61, 64, 66, 68, 32, 33,
		 35, 39, 43, 47, 46, 45, 46, 48, 50, 52, 55, 58, 59, 61, 40, 41, 43, 46,
		 48, 50, 49, 48, 49, 50, 51, 53, 56, 58, 59, 59, 49, 47, 46, 46, 49, 53,
		 54, 56, 57, 58, 59, 61, 63, 65, 66, 65, 51, 49, 47, 47, 49, 54, 57, 61,
		 63, 65, 67, 69, 72, 73, 75, 72, 57, 54, 51, 50, 52, 57, 60, 64, 67, 71,
		 73, 77, 80, 82, 84, 81, 63, 59, 57, 55, 57, 60, 64, 67, 71, 75, 78, 82,
		 86, 89, 91, 89, 67, 63, 60, 58, 59, 62, 65, 69, 73, 77, 81, 85, 88, 92,
		 94, 95,
		 /* Size 16x32 */
		 32, 31, 32, 37, 40, 48, 49, 49, 51, 52, 57, 58, 63, 64, 67, 67, 31, 31,
		 33, 38, 41, 47, 47, 47, 49, 50, 54, 55, 60, 61, 63, 64, 31, 31, 33, 38,
		 41, 47, 47, 47, 49, 49, 54, 54, 59, 60, 63, 64, 30, 32, 33, 40, 42, 46,
		 45, 45, 47, 48, 52, 52, 57, 58, 60, 61, 31, 33, 35, 41, 43, 46, 46, 45,
		 47, 48, 51, 52, 57, 57, 60, 61, 33, 36, 37, 43, 44, 47, 46, 46, 47, 47,
		 51, 52, 56, 57, 59, 60, 35, 38, 39, 45, 46, 47, 46, 45, 47, 47, 50, 51,
		 55, 56, 58, 60, 37, 40, 41, 47, 47, 47, 46, 45, 46, 47, 50, 50, 54, 55,
		 57, 58, 41, 42, 43, 47, 48, 49, 49, 48, 49, 50, 52, 53, 57, 57, 59, 58,
		 42, 43, 43, 47, 48, 50, 49, 49, 50, 50, 53, 54, 57, 58, 60, 61, 49, 46,
		 47, 48, 50, 53, 53, 53, 54, 54, 57, 57, 60, 61, 62, 61, 49, 46, 47, 48,
		 50, 53, 53, 54, 54, 55, 57, 57, 61, 61, 63, 64, 48, 46, 46, 47, 49, 53,
		 54, 56, 57, 57, 60, 60, 64, 64, 65, 64, 48, 45, 46, 46, 49, 53, 55, 56,
		 58, 58, 61, 61, 65, 65, 66, 67, 49, 45, 45, 46, 48, 53, 56, 58, 61, 61,
		 64, 64, 67, 68, 69, 67, 49, 46, 46, 46, 49, 53, 57, 59, 62, 62, 65, 66,
		 69, 69, 70, 70, 50, 46, 46, 46, 49, 54, 57, 59, 63, 64, 67, 67, 71, 71,
		 73, 71, 51, 47, 47, 47, 49, 54, 58, 61, 64, 66, 69, 70, 73, 74, 74, 74,
		 52, 48, 48, 47, 50, 54, 58, 61, 65, 66, 71, 71, 75, 75, 77, 74, 54, 50,
		 49, 48, 51, 55, 59, 62, 67, 68, 73, 73, 77, 78, 78, 78, 54, 50, 50, 49,
		 51, 55, 59, 62, 67, 68, 73, 74, 78, 78, 81, 78, 57, 52, 52, 50, 52, 56,
		 60, 64, 69, 70, 76, 77, 82, 82, 83, 82, 57, 52, 52, 51, 53, 57, 61, 64,
		 69, 71, 77, 77, 82, 83, 85, 82, 60, 54, 54, 52, 55, 58, 62, 65, 71, 72,
		 79, 79, 85, 86, 87, 86, 61, 56, 55, 53, 56, 59, 63, 66, 72, 73, 80, 81,
		 86, 87, 88, 86, 63, 57, 57, 55, 57, 60, 64, 67, 73, 75, 82, 82, 89, 90,
		 92, 90, 64, 58, 58, 55, 58, 61, 65, 68, 73, 75, 82, 83, 89, 90, 92, 90,
		 64, 59, 58, 56, 58, 61, 65, 68, 74, 75, 83, 83, 90, 91, 94, 95, 66, 60,
		 59, 57, 59, 62, 66, 69, 75, 76, 84, 85, 91, 92, 94, 95, 67, 61, 60, 58,
		 59, 63, 66, 70, 74, 77, 82, 85, 91, 93, 96, 96, 68, 62, 61, 58, 59, 64,
		 65, 71, 72, 78, 81, 86, 89, 94, 95, 96, 68, 62, 62, 59, 59, 65, 65, 71,
		 71, 79, 79, 87, 87, 95, 95, 98,
		 /* Size 32x16 */
		 32, 31, 31, 30, 31, 33, 35, 37, 41, 42, 49, 49, 48, 48, 49, 49, 50, 51,
		 52, 54, 54, 57, 57, 60, 61, 63, 64, 64, 66, 67, 68, 68, 31, 31, 31, 32,
		 33, 36, 38, 40, 42, 43, 46, 46, 46, 45, 45, 46, 46, 47, 48, 50, 50, 52,
		 52, 54, 56, 57, 58, 59, 60, 61, 62, 62, 32, 33, 33, 33, 35, 37, 39, 41,
		 43, 43, 47, 47, 46, 46, 45, 46, 46, 47, 48, 49, 50, 52, 52, 54, 55, 57,
		 58, 58, 59, 60, 61, 62, 37, 38, 38, 40, 41, 43, 45, 47, 47, 47, 48, 48,
		 47, 46, 46, 46, 46, 47, 47, 48, 49, 50, 51, 52, 53, 55, 55, 56, 57, 58,
		 58, 59, 40, 41, 41, 42, 43, 44, 46, 47, 48, 48, 50, 50, 49, 49, 48, 49,
		 49, 49, 50, 51, 51, 52, 53, 55, 56, 57, 58, 58, 59, 59, 59, 59, 48, 47,
		 47, 46, 46, 47, 47, 47, 49, 50, 53, 53, 53, 53, 53, 53, 54, 54, 54, 55,
		 55, 56, 57, 58, 59, 60, 61, 61, 62, 63, 64, 65, 49, 47, 47, 45, 46, 46,
		 46, 46, 49, 49, 53, 53, 54, 55, 56, 57, 57, 58, 58, 59, 59, 60, 61, 62,
		 63, 64, 65, 65, 66, 66, 65, 65, 49, 47, 47, 45, 45, 46, 45, 45, 48, 49,
		 53, 54, 56, 56, 58, 59, 59, 61, 61, 62, 62, 64, 64, 65, 66, 67, 68, 68,
		 69, 70, 71, 71, 51, 49, 49, 47, 47, 47, 47, 46, 49, 50, 54, 54, 57, 58,
		 61, 62, 63, 64, 65, 67, 67, 69, 69, 71, 72, 73, 73, 74, 75, 74, 72, 71,
		 52, 50, 49, 48, 48, 47, 47, 47, 50, 50, 54, 55, 57, 58, 61, 62, 64, 66,
		 66, 68, 68, 70, 71, 72, 73, 75, 75, 75, 76, 77, 78, 79, 57, 54, 54, 52,
		 51, 51, 50, 50, 52, 53, 57, 57, 60, 61, 64, 65, 67, 69, 71, 73, 73, 76,
		 77, 79, 80, 82, 82, 83, 84, 82, 81, 79, 58, 55, 54, 52, 52, 52, 51, 50,
		 53, 54, 57, 57, 60, 61, 64, 66, 67, 70, 71, 73, 74, 77, 77, 79, 81, 82,
		 83, 83, 85, 85, 86, 87, 63, 60, 59, 57, 57, 56, 55, 54, 57, 57, 60, 61,
		 64, 65, 67, 69, 71, 73, 75, 77, 78, 82, 82, 85, 86, 89, 89, 90, 91, 91,
		 89, 87, 64, 61, 60, 58, 57, 57, 56, 55, 57, 58, 61, 61, 64, 65, 68, 69,
		 71, 74, 75, 78, 78, 82, 83, 86, 87, 90, 90, 91, 92, 93, 94, 95, 67, 63,
		 63, 60, 60, 59, 58, 57, 59, 60, 62, 63, 65, 66, 69, 70, 73, 74, 77, 78,
		 81, 83, 85, 87, 88, 92, 92, 94, 94, 96, 95, 95, 67, 64, 64, 61, 61, 60,
		 60, 58, 58, 61, 61, 64, 64, 67, 67, 70, 71, 74, 74, 78, 78, 82, 82, 86,
		 86, 90, 90, 95, 95, 96, 96, 98,
		 /* Size 4x16 */
		 31, 48, 52, 64, 31, 47, 49, 60, 33, 46, 48, 57, 38, 47, 47, 56, 42, 49,
		 50, 57, 46, 53, 54, 61, 46, 53, 57, 64, 45, 53, 61, 68, 46, 54, 64, 71,
		 48, 54, 66, 75, 50, 55, 68, 78, 52, 57, 71, 83, 56, 59, 73, 87, 58, 61,
		 75, 90, 60, 62, 76, 92, 62, 64, 78, 94,
		 /* Size 16x4 */
		 31, 31, 33, 38, 42, 46, 46, 45, 46, 48, 50, 52, 56, 58, 60, 62, 48, 47,
		 46, 47, 49, 53, 53, 53, 54, 54, 55, 57, 59, 61, 62, 64, 52, 49, 48, 47,
		 50, 54, 57, 61, 64, 66, 68, 71, 73, 75, 76, 78, 64, 60, 57, 56, 57, 61,
		 64, 68, 71, 75, 78, 83, 87, 90, 92, 94,
		 /* Size 8x32 */
		 32, 32, 40, 49, 51, 57, 63, 67, 31, 33, 41, 47, 49, 54, 60, 63, 31, 33,
		 41, 47, 49, 54, 59, 63, 30, 33, 42, 45, 47, 52, 57, 60, 31, 35, 43, 46,
		 47, 51, 57, 60, 33, 37, 44, 46, 47, 51, 56, 59, 35, 39, 46, 46, 47, 50,
		 55, 58, 37, 41, 47, 46, 46, 50, 54, 57, 41, 43, 48, 49, 49, 52, 57, 59,
		 42, 43, 48, 49, 50, 53, 57, 60, 49, 47, 50, 53, 54, 57, 60, 62, 49, 47,
		 50, 53, 54, 57, 61, 63, 48, 46, 49, 54, 57, 60, 64, 65, 48, 46, 49, 55,
		 58, 61, 65, 66, 49, 45, 48, 56, 61, 64, 67, 69, 49, 46, 49, 57, 62, 65,
		 69, 70, 50, 46, 49, 57, 63, 67, 71, 73, 51, 47, 49, 58, 64, 69, 73, 74,
		 52, 48, 50, 58, 65, 71, 75, 77, 54, 49, 51, 59, 67, 73, 77, 78, 54, 50,
		 51, 59, 67, 73, 78, 81, 57, 52, 52, 60, 69, 76, 82, 83, 57, 52, 53, 61,
		 69, 77, 82, 85, 60, 54, 55, 62, 71, 79, 85, 87, 61, 55, 56, 63, 72, 80,
		 86, 88, 63, 57, 57, 64, 73, 82, 89, 92, 64, 58, 58, 65, 73, 82, 89, 92,
		 64, 58, 58, 65, 74, 83, 90, 94, 66, 59, 59, 66, 75, 84, 91, 94, 67, 60,
		 59, 66, 74, 82, 91, 96, 68, 61, 59, 65, 72, 81, 89, 95, 68, 62, 59, 65,
		 71, 79, 87, 95,
		 /* Size 32x8 */
		 32, 31, 31, 30, 31, 33, 35, 37, 41, 42, 49, 49, 48, 48, 49, 49, 50, 51,
		 52, 54, 54, 57, 57, 60, 61, 63, 64, 64, 66, 67, 68, 68, 32, 33, 33, 33,
		 35, 37, 39, 41, 43, 43, 47, 47, 46, 46, 45, 46, 46, 47, 48, 49, 50, 52,
		 52, 54, 55, 57, 58, 58, 59, 60, 61, 62, 40, 41, 41, 42, 43, 44, 46, 47,
		 48, 48, 50, 50, 49, 49, 48, 49, 49, 49, 50, 51, 51, 52, 53, 55, 56, 57,
		 58, 58, 59, 59, 59, 59, 49, 47, 47, 45, 46, 46, 46, 46, 49, 49, 53, 53,
		 54, 55, 56, 57, 57, 58, 58, 59, 59, 60, 61, 62, 63, 64, 65, 65, 66, 66,
		 65, 65, 51, 49, 49, 47, 47, 47, 47, 46, 49, 50, 54, 54, 57, 58, 61, 62,
		 63, 64, 65, 67, 67, 69, 69, 71, 72, 73, 73, 74, 75, 74, 72, 71, 57, 54,
		 54, 52, 51, 51, 50, 50, 52, 53, 57, 57, 60, 61, 64, 65, 67, 69, 71, 73,
		 73, 76, 77, 79, 80, 82, 82, 83, 84, 82, 81, 79, 63, 60, 59, 57, 57, 56,
		 55, 54, 57, 57, 60, 61, 64, 65, 67, 69, 71, 73, 75, 77, 78, 82, 82, 85,
		 86, 89, 89, 90, 91, 91, 89, 87, 67, 63, 63, 60, 60, 59, 58, 57, 59, 60,
		 62, 63, 65, 66, 69, 70, 73, 74, 77, 78, 81, 83, 85, 87, 88, 92, 92, 94,
		 94, 96, 95, 95},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 34, 49, 72, 34, 48, 60, 79, 49, 60, 82, 104, 72, 79, 104, 134,
		 /* Size 8x8 */
		 32, 32, 34, 38, 46, 56, 68, 78, 32, 33, 35, 39, 45, 54, 64, 74, 34, 35,
		 39, 45, 51, 58, 68, 76, 38, 39, 45, 54, 61, 69, 78, 86, 46, 45, 51, 61,
		 71, 80, 90, 99, 56, 54, 58, 69, 80, 92, 103, 113, 68, 64, 68, 78, 90,
		 103, 117, 128, 78, 74, 76, 86, 99, 113, 128, 140,
		 /* Size 16x16 */
		 32, 31, 31, 31, 32, 34, 36, 39, 44, 48, 54, 59, 65, 71, 80, 83, 31, 32,
		 32, 32, 32, 34, 35, 38, 42, 46, 51, 56, 62, 68, 76, 78, 31, 32, 32, 32,
		 32, 33, 34, 37, 41, 44, 49, 54, 59, 65, 72, 75, 31, 32, 32, 33, 34, 35,
		 36, 39, 42, 45, 50, 54, 59, 64, 71, 74, 32, 32, 32, 34, 35, 37, 38, 40,
		 42, 46, 49, 53, 58, 63, 69, 72, 34, 34, 33, 35, 37, 39, 42, 45, 47, 51,
		 54, 58, 63, 68, 74, 76, 36, 35, 34, 36, 38, 42, 48, 50, 54, 57, 60, 64,
		 68, 73, 79, 81, 39, 38, 37, 39, 40, 45, 50, 54, 58, 61, 65, 69, 73, 78,
		 84, 86, 44, 42, 41, 42, 42, 47, 54, 58, 63, 67, 71, 75, 79, 84, 90, 92,
		 48, 46, 44, 45, 46, 51, 57, 61, 67, 71, 76, 80, 85, 90, 96, 99, 54, 51,
		 49, 50, 49, 54, 60, 65, 71, 76, 82, 87, 92, 97, 104, 106, 59, 56, 54,
		 54, 53, 58, 64, 69, 75, 80, 87, 92, 98, 103, 110, 113, 65, 62, 59, 59,
		 58, 63, 68, 73, 79, 85, 92, 98, 105, 111, 118, 121, 71, 68, 65, 64, 63,
		 68, 73, 78, 84, 90, 97, 103, 111, 117, 125, 128, 80, 76, 72, 71, 69, 74,
		 79, 84, 90, 96, 104, 110, 118, 125, 134, 137, 83, 78, 75, 74, 72, 76,
		 81, 86, 92, 99, 106, 113, 121, 128, 137, 140,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 34, 34, 36, 36, 39, 39, 44, 44, 48,
		 48, 54, 54, 59, 59, 65, 65, 71, 71, 80, 80, 83, 83, 87, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 34, 34, 35, 35, 38, 38, 42, 42, 46, 46, 51, 51, 56,
		 56, 62, 62, 68, 68, 76, 76, 78, 78, 83, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 34, 34, 35, 35, 38, 38, 42, 42, 46, 46, 51, 51, 56, 56, 62, 62, 68,
		 68, 76, 76, 78, 78, 83, 31, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34,
		 34, 37, 37, 41, 41, 44, 44, 49, 49, 54, 54, 59, 59, 65, 65, 72, 72, 75,
		 75, 79, 31, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 37, 37, 41,
		 41, 44, 44, 49, 49, 54, 54, 59, 59, 65, 65, 72, 72, 75, 75, 79, 31, 32,
		 32, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 39, 39, 42, 42, 45, 45, 50,
		 50, 54, 54, 59, 59, 64, 64, 71, 71, 74, 74, 77, 31, 32, 32, 32, 32, 33,
		 33, 34, 34, 35, 35, 36, 36, 39, 39, 42, 42, 45, 45, 50, 50, 54, 54, 59,
		 59, 64, 64, 71, 71, 74, 74, 77, 32, 32, 32, 32, 32, 34, 34, 35, 35, 37,
		 37, 38, 38, 40, 40, 42, 42, 46, 46, 49, 49, 53, 53, 58, 58, 63, 63, 69,
		 69, 72, 72, 75, 32, 32, 32, 32, 32, 34, 34, 35, 35, 37, 37, 38, 38, 40,
		 40, 42, 42, 46, 46, 49, 49, 53, 53, 58, 58, 63, 63, 69, 69, 72, 72, 75,
		 34, 34, 34, 33, 33, 35, 35, 37, 37, 39, 39, 42, 42, 45, 45, 47, 47, 51,
		 51, 54, 54, 58, 58, 63, 63, 68, 68, 74, 74, 76, 76, 80, 34, 34, 34, 33,
		 33, 35, 35, 37, 37, 39, 39, 42, 42, 45, 45, 47, 47, 51, 51, 54, 54, 58,
		 58, 63, 63, 68, 68, 74, 74, 76, 76, 80, 36, 35, 35, 34, 34, 36, 36, 38,
		 38, 42, 42, 48, 48, 50, 50, 54, 54, 57, 57, 60, 60, 64, 64, 68, 68, 73,
		 73, 79, 79, 81, 81, 84, 36, 35, 35, 34, 34, 36, 36, 38, 38, 42, 42, 48,
		 48, 50, 50, 54, 54, 57, 57, 60, 60, 64, 64, 68, 68, 73, 73, 79, 79, 81,
		 81, 84, 39, 38, 38, 37, 37, 39, 39, 40, 40, 45, 45, 50, 50, 54, 54, 58,
		 58, 61, 61, 65, 65, 69, 69, 73, 73, 78, 78, 84, 84, 86, 86, 90, 39, 38,
		 38, 37, 37, 39, 39, 40, 40, 45, 45, 50, 50, 54, 54, 58, 58, 61, 61, 65,
		 65, 69, 69, 73, 73, 78, 78, 84, 84, 86, 86, 90, 44, 42, 42, 41, 41, 42,
		 42, 42, 42, 47, 47, 54, 54, 58, 58, 63, 63, 67, 67, 71, 71, 75, 75, 79,
		 79, 84, 84, 90, 90, 92, 92, 96, 44, 42, 42, 41, 41, 42, 42, 42, 42, 47,
		 47, 54, 54, 58, 58, 63, 63, 67, 67, 71, 71, 75, 75, 79, 79, 84, 84, 90,
		 90, 92, 92, 96, 48, 46, 46, 44, 44, 45, 45, 46, 46, 51, 51, 57, 57, 61,
		 61, 67, 67, 71, 71, 76, 76, 80, 80, 85, 85, 90, 90, 96, 96, 99, 99, 102,
		 48, 46, 46, 44, 44, 45, 45, 46, 46, 51, 51, 57, 57, 61, 61, 67, 67, 71,
		 71, 76, 76, 80, 80, 85, 85, 90, 90, 96, 96, 99, 99, 102, 54, 51, 51, 49,
		 49, 50, 50, 49, 49, 54, 54, 60, 60, 65, 65, 71, 71, 76, 76, 82, 82, 87,
		 87, 92, 92, 97, 97, 104, 104, 106, 106, 109, 54, 51, 51, 49, 49, 50, 50,
		 49, 49, 54, 54, 60, 60, 65, 65, 71, 71, 76, 76, 82, 82, 87, 87, 92, 92,
		 97, 97, 104, 104, 106, 106, 109, 59, 56, 56, 54, 54, 54, 54, 53, 53, 58,
		 58, 64, 64, 69, 69, 75, 75, 80, 80, 87, 87, 92, 92, 98, 98, 103, 103,
		 110, 110, 113, 113, 116, 59, 56, 56, 54, 54, 54, 54, 53, 53, 58, 58, 64,
		 64, 69, 69, 75, 75, 80, 80, 87, 87, 92, 92, 98, 98, 103, 103, 110, 110,
		 113, 113, 116, 65, 62, 62, 59, 59, 59, 59, 58, 58, 63, 63, 68, 68, 73,
		 73, 79, 79, 85, 85, 92, 92, 98, 98, 105, 105, 111, 111, 118, 118, 121,
		 121, 124, 65, 62, 62, 59, 59, 59, 59, 58, 58, 63, 63, 68, 68, 73, 73,
		 79, 79, 85, 85, 92, 92, 98, 98, 105, 105, 111, 111, 118, 118, 121, 121,
		 124, 71, 68, 68, 65, 65, 64, 64, 63, 63, 68, 68, 73, 73, 78, 78, 84, 84,
		 90, 90, 97, 97, 103, 103, 111, 111, 117, 117, 125, 125, 128, 128, 132,
		 71, 68, 68, 65, 65, 64, 64, 63, 63, 68, 68, 73, 73, 78, 78, 84, 84, 90,
		 90, 97, 97, 103, 103, 111, 111, 117, 117, 125, 125, 128, 128, 132, 80,
		 76, 76, 72, 72, 71, 71, 69, 69, 74, 74, 79, 79, 84, 84, 90, 90, 96, 96,
		 104, 104, 110, 110, 118, 118, 125, 125, 134, 134, 137, 137, 141, 80, 76,
		 76, 72, 72, 71, 71, 69, 69, 74, 74, 79, 79, 84, 84, 90, 90, 96, 96, 104,
		 104, 110, 110, 118, 118, 125, 125, 134, 134, 137, 137, 141, 83, 78, 78,
		 75, 75, 74, 74, 72, 72, 76, 76, 81, 81, 86, 86, 92, 92, 99, 99, 106,
		 106, 113, 113, 121, 121, 128, 128, 137, 137, 140, 140, 144, 83, 78, 78,
		 75, 75, 74, 74, 72, 72, 76, 76, 81, 81, 86, 86, 92, 92, 99, 99, 106,
		 106, 113, 113, 121, 121, 128, 128, 137, 137, 140, 140, 144, 87, 83, 83,
		 79, 79, 77, 77, 75, 75, 80, 80, 84, 84, 90, 90, 96, 96, 102, 102, 109,
		 109, 116, 116, 124, 124, 132, 132, 141, 141, 144, 144, 149,
		 /* Size 4x8 */
		 32, 35, 51, 75, 32, 36, 50, 71, 34, 42, 54, 73, 37, 50, 65, 84, 45, 56,
		 76, 96, 54, 63, 87, 110, 65, 73, 97, 125, 75, 81, 106, 136,
		 /* Size 8x4 */
		 32, 32, 34, 37, 45, 54, 65, 75, 35, 36, 42, 50, 56, 63, 73, 81, 51, 50,
		 54, 65, 76, 87, 97, 106, 75, 71, 73, 84, 96, 110, 125, 136,
		 /* Size 8x16 */
		 32, 31, 32, 36, 44, 53, 65, 79, 31, 32, 32, 35, 42, 51, 62, 75, 31, 32,
		 33, 34, 41, 49, 59, 72, 32, 32, 34, 36, 42, 50, 59, 71, 32, 33, 35, 38,
		 42, 49, 58, 69, 34, 34, 37, 42, 48, 54, 63, 73, 36, 34, 38, 48, 54, 60,
		 68, 78, 39, 37, 40, 50, 58, 65, 73, 84, 44, 41, 43, 53, 63, 71, 79, 90,
		 48, 45, 46, 56, 67, 76, 85, 96, 53, 49, 50, 60, 71, 82, 92, 103, 58, 54,
		 54, 63, 75, 87, 98, 110, 65, 60, 58, 68, 79, 92, 105, 118, 71, 65, 63,
		 73, 84, 97, 111, 125, 79, 72, 70, 79, 90, 104, 118, 133, 82, 75, 72, 81,
		 92, 106, 121, 136,
		 /* Size 16x8 */
		 32, 31, 31, 32, 32, 34, 36, 39, 44, 48, 53, 58, 65, 71, 79, 82, 31, 32,
		 32, 32, 33, 34, 34, 37, 41, 45, 49, 54, 60, 65, 72, 75, 32, 32, 33, 34,
		 35, 37, 38, 40, 43, 46, 50, 54, 58, 63, 70, 72, 36, 35, 34, 36, 38, 42,
		 48, 50, 53, 56, 60, 63, 68, 73, 79, 81, 44, 42, 41, 42, 42, 48, 54, 58,
		 63, 67, 71, 75, 79, 84, 90, 92, 53, 51, 49, 50, 49, 54, 60, 65, 71, 76,
		 82, 87, 92, 97, 104, 106, 65, 62, 59, 59, 58, 63, 68, 73, 79, 85, 92,
		 98, 105, 111, 118, 121, 79, 75, 72, 71, 69, 73, 78, 84, 90, 96, 103,
		 110, 118, 125, 133, 136,
		 /* Size 16x32 */
		 32, 31, 31, 32, 32, 36, 36, 44, 44, 53, 53, 65, 65, 79, 79, 87, 31, 32,
		 32, 32, 32, 35, 35, 42, 42, 51, 51, 62, 62, 75, 75, 82, 31, 32, 32, 32,
		 32, 35, 35, 42, 42, 51, 51, 62, 62, 75, 75, 82, 31, 32, 32, 33, 33, 34,
		 34, 41, 41, 49, 49, 59, 59, 72, 72, 78, 31, 32, 32, 33, 33, 34, 34, 41,
		 41, 49, 49, 59, 59, 72, 72, 78, 32, 32, 32, 34, 34, 36, 36, 42, 42, 50,
		 50, 59, 59, 71, 71, 77, 32, 32, 32, 34, 34, 36, 36, 42, 42, 50, 50, 59,
		 59, 71, 71, 77, 32, 33, 33, 35, 35, 38, 38, 42, 42, 49, 49, 58, 58, 69,
		 69, 75, 32, 33, 33, 35, 35, 38, 38, 42, 42, 49, 49, 58, 58, 69, 69, 75,
		 34, 34, 34, 37, 37, 42, 42, 48, 48, 54, 54, 63, 63, 73, 73, 79, 34, 34,
		 34, 37, 37, 42, 42, 48, 48, 54, 54, 63, 63, 73, 73, 79, 36, 34, 34, 38,
		 38, 48, 48, 54, 54, 60, 60, 68, 68, 78, 78, 84, 36, 34, 34, 38, 38, 48,
		 48, 54, 54, 60, 60, 68, 68, 78, 78, 84, 39, 37, 37, 40, 40, 50, 50, 58,
		 58, 65, 65, 73, 73, 84, 84, 89, 39, 37, 37, 40, 40, 50, 50, 58, 58, 65,
		 65, 73, 73, 84, 84, 89, 44, 41, 41, 43, 43, 53, 53, 63, 63, 71, 71, 79,
		 79, 90, 90, 95, 44, 41, 41, 43, 43, 53, 53, 63, 63, 71, 71, 79, 79, 90,
		 90, 95, 48, 45, 45, 46, 46, 56, 56, 67, 67, 76, 76, 85, 85, 96, 96, 102,
		 48, 45, 45, 46, 46, 56, 56, 67, 67, 76, 76, 85, 85, 96, 96, 102, 53, 49,
		 49, 50, 50, 60, 60, 71, 71, 82, 82, 92, 92, 103, 103, 109, 53, 49, 49,
		 50, 50, 60, 60, 71, 71, 82, 82, 92, 92, 103, 103, 109, 58, 54, 54, 54,
		 54, 63, 63, 75, 75, 87, 87, 98, 98, 110, 110, 116, 58, 54, 54, 54, 54,
		 63, 63, 75, 75, 87, 87, 98, 98, 110, 110, 116, 65, 60, 60, 58, 58, 68,
		 68, 79, 79, 92, 92, 105, 105, 118, 118, 124, 65, 60, 60, 58, 58, 68, 68,
		 79, 79, 92, 92, 105, 105, 118, 118, 124, 71, 65, 65, 63, 63, 73, 73, 84,
		 84, 97, 97, 111, 111, 125, 125, 132, 71, 65, 65, 63, 63, 73, 73, 84, 84,
		 97, 97, 111, 111, 125, 125, 132, 79, 72, 72, 70, 70, 79, 79, 90, 90,
		 104, 104, 118, 118, 133, 133, 141, 79, 72, 72, 70, 70, 79, 79, 90, 90,
		 104, 104, 118, 118, 133, 133, 141, 82, 75, 75, 72, 72, 81, 81, 92, 92,
		 106, 106, 121, 121, 136, 136, 144, 82, 75, 75, 72, 72, 81, 81, 92, 92,
		 106, 106, 121, 121, 136, 136, 144, 87, 79, 79, 76, 76, 84, 84, 96, 96,
		 109, 109, 124, 124, 141, 141, 149,

		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 36, 36, 39, 39, 44, 44, 48,
		 48, 53, 53, 58, 58, 65, 65, 71, 71, 79, 79, 82, 82, 87, 31, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 34, 34, 37, 37, 41, 41, 45, 45, 49, 49, 54,
		 54, 60, 60, 65, 65, 72, 72, 75, 75, 79, 31, 32, 32, 32, 32, 32, 32, 33,
		 33, 34, 34, 34, 34, 37, 37, 41, 41, 45, 45, 49, 49, 54, 54, 60, 60, 65,
		 65, 72, 72, 75, 75, 79, 32, 32, 32, 33, 33, 34, 34, 35, 35, 37, 37, 38,
		 38, 40, 40, 43, 43, 46, 46, 50, 50, 54, 54, 58, 58, 63, 63, 70, 70, 72,
		 72, 76, 32, 32, 32, 33, 33, 34, 34, 35, 35, 37, 37, 38, 38, 40, 40, 43,
		 43, 46, 46, 50, 50, 54, 54, 58, 58, 63, 63, 70, 70, 72, 72, 76, 36, 35,
		 35, 34, 34, 36, 36, 38, 38, 42, 42, 48, 48, 50, 50, 53, 53, 56, 56, 60,
		 60, 63, 63, 68, 68, 73, 73, 79, 79, 81, 81, 84, 36, 35, 35, 34, 34, 36,
		 36, 38, 38, 42, 42, 48, 48, 50, 50, 53, 53, 56, 56, 60, 60, 63, 63, 68,
		 68, 73, 73, 79, 79, 81, 81, 84, 44, 42, 42, 41, 41, 42, 42, 42, 42, 48,
		 48, 54, 54, 58, 58, 63, 63, 67, 67, 71, 71, 75, 75, 79, 79, 84, 84, 90,
		 90, 92, 92, 96, 44, 42, 42, 41, 41, 42, 42, 42, 42, 48, 48, 54, 54, 58,
		 58, 63, 63, 67, 67, 71, 71, 75, 75, 79, 79, 84, 84, 90, 90, 92, 92, 96,
		 53, 51, 51, 49, 49, 50, 50, 49, 49, 54, 54, 60, 60, 65, 65, 71, 71, 76,
		 76, 82, 82, 87, 87, 92, 92, 97, 97, 104, 104, 106, 106, 109, 53, 51, 51,
		 49, 49, 50, 50, 49, 49, 54, 54, 60, 60, 65, 65, 71, 71, 76, 76, 82, 82,
		 87, 87, 92, 92, 97, 97, 104, 104, 106, 106, 109, 65, 62, 62, 59, 59, 59,
		 59, 58, 58, 63, 63, 68, 68, 73, 73, 79, 79, 85, 85, 92, 92, 98, 98, 105,
		 105, 111, 111, 118, 118, 121, 121, 124, 65, 62, 62, 59, 59, 59, 59, 58,
		 58, 63, 63, 68, 68, 73, 73, 79, 79, 85, 85, 92, 92, 98, 98, 105, 105,
		 111, 111, 118, 118, 121, 121, 124, 79, 75, 75, 72, 72, 71, 71, 69, 69,
		 73, 73, 78, 78, 84, 84, 90, 90, 96, 96, 103, 103, 110, 110, 118, 118,
		 125, 125, 133, 133, 136, 136, 141, 79, 75, 75, 72, 72, 71, 71, 69, 69,
		 73, 73, 78, 78, 84, 84, 90, 90, 96, 96, 103, 103, 110, 110, 118, 118,
		 125, 125, 133, 133, 136, 136, 141, 87, 82, 82, 78, 78, 77, 77, 75, 75,
		 79, 79, 84, 84, 89, 89, 95, 95, 102, 102, 109, 109, 116, 116, 124, 124,
		 132, 132, 141, 141, 144, 144, 149,
		 /* Size 4x16 */
		 31, 36, 53, 79, 32, 35, 51, 75, 32, 34, 49, 72, 32, 36, 50, 71, 33, 38,
		 49, 69, 34, 42, 54, 73, 34, 48, 60, 78, 37, 50, 65, 84, 41, 53, 71, 90,
		 45, 56, 76, 96, 49, 60, 82, 103, 54, 63, 87, 110, 60, 68, 92, 118, 65,
		 73, 97, 125, 72, 79, 104, 133, 75, 81, 106, 136,
		 /* Size 16x4 */
		 31, 32, 32, 32, 33, 34, 34, 37, 41, 45, 49, 54, 60, 65, 72, 75, 36, 35,
		 34, 36, 38, 42, 48, 50, 53, 56, 60, 63, 68, 73, 79, 81, 53, 51, 49, 50,
		 49, 54, 60, 65, 71, 76, 82, 87, 92, 97, 104, 106, 79, 75, 72, 71, 69,
		 73, 78, 84, 90, 96, 103, 110, 118, 125, 133, 136,
		 /* Size 8x32 */
		 32, 31, 32, 36, 44, 53, 65, 79, 31, 32, 32, 35, 42, 51, 62, 75, 31, 32,
		 32, 35, 42, 51, 62, 75, 31, 32, 33, 34, 41, 49, 59, 72, 31, 32, 33, 34,
		 41, 49, 59, 72, 32, 32, 34, 36, 42, 50, 59, 71, 32, 32, 34, 36, 42, 50,
		 59, 71, 32, 33, 35, 38, 42, 49, 58, 69, 32, 33, 35, 38, 42, 49, 58, 69,
		 34, 34, 37, 42, 48, 54, 63, 73, 34, 34, 37, 42, 48, 54, 63, 73, 36, 34,
		 38, 48, 54, 60, 68, 78, 36, 34, 38, 48, 54, 60, 68, 78, 39, 37, 40, 50,
		 58, 65, 73, 84, 39, 37, 40, 50, 58, 65, 73, 84, 44, 41, 43, 53, 63, 71,
		 79, 90, 44, 41, 43, 53, 63, 71, 79, 90, 48, 45, 46, 56, 67, 76, 85, 96,
		 48, 45, 46, 56, 67, 76, 85, 96, 53, 49, 50, 60, 71, 82, 92, 103, 53, 49,
		 50, 60, 71, 82, 92, 103, 58, 54, 54, 63, 75, 87, 98, 110, 58, 54, 54,
		 63, 75, 87, 98, 110, 65, 60, 58, 68, 79, 92, 105, 118, 65, 60, 58, 68,
		 79, 92, 105, 118, 71, 65, 63, 73, 84, 97, 111, 125, 71, 65, 63, 73, 84,
		 97, 111, 125, 79, 72, 70, 79, 90, 104, 118, 133, 79, 72, 70, 79, 90,
		 104, 118, 133, 82, 75, 72, 81, 92, 106, 121, 136, 82, 75, 72, 81, 92,
		 106, 121, 136, 87, 79, 76, 84, 96, 109, 124, 141,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 36, 36, 39, 39, 44, 44, 48,
		 48, 53, 53, 58, 58, 65, 65, 71, 71, 79, 79, 82, 82, 87, 31, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 34, 34, 37, 37, 41, 41, 45, 45, 49, 49, 54,
		 54, 60, 60, 65, 65, 72, 72, 75, 75, 79, 32, 32, 32, 33, 33, 34, 34, 35,
		 35, 37, 37, 38, 38, 40, 40, 43, 43, 46, 46, 50, 50, 54, 54, 58, 58, 63,
		 63, 70, 70, 72, 72, 76, 36, 35, 35, 34, 34, 36, 36, 38, 38, 42, 42, 48,
		 48, 50, 50, 53, 53, 56, 56, 60, 60, 63, 63, 68, 68, 73, 73, 79, 79, 81,
		 81, 84, 44, 42, 42, 41, 41, 42, 42, 42, 42, 48, 48, 54, 54, 58, 58, 63,
		 63, 67, 67, 71, 71, 75, 75, 79, 79, 84, 84, 90, 90, 92, 92, 96, 53, 51,
		 51, 49, 49, 50, 50, 49, 49, 54, 54, 60, 60, 65, 65, 71, 71, 76, 76, 82,
		 82, 87, 87, 92, 92, 97, 97, 104, 104, 106, 106, 109, 65, 62, 62, 59, 59,
		 59, 59, 58, 58, 63, 63, 68, 68, 73, 73, 79, 79, 85, 85, 92, 92, 98, 98,
		 105, 105, 111, 111, 118, 118, 121, 121, 124, 79, 75, 75, 72, 72, 71, 71,
		 69, 69, 73, 73, 78, 78, 84, 84, 90, 90, 96, 96, 103, 103, 110, 110, 118,
		 118, 125, 125, 133, 133, 136, 136, 141},
		{/* Chroma */
		 /* Size 4x4 */
		 32, 46, 47, 57, 46, 53, 54, 60, 47, 54, 66, 75, 57, 60, 75, 89,
		 /* Size 8x8 */
		 31, 34, 42, 47, 48, 52, 57, 61, 34, 39, 45, 46, 46, 49, 53, 57, 42, 45,
		 48, 49, 50, 52, 55, 58, 47, 46, 49, 54, 56, 58, 61, 64, 48, 46, 50, 56,
		 61, 65, 68, 71, 52, 49, 52, 58, 65, 71, 75, 79, 57, 53, 55, 61, 68, 75,
		 82, 86, 61, 57, 58, 64, 71, 79, 86, 91,
		 /* Size 16x16 */
		 32, 31, 30, 33, 36, 41, 49, 48, 49, 50, 52, 54, 57, 60, 63, 65, 31, 31,
		 31, 34, 38, 42, 47, 47, 47, 48, 50, 52, 54, 57, 60, 61, 30, 31, 32, 35,
		 40, 42, 46, 45, 45, 46, 47, 49, 52, 54, 57, 58, 33, 34, 35, 39, 43, 45,
		 47, 46, 45, 46, 47, 49, 51, 53, 56, 57, 36, 38, 40, 43, 47, 47, 48, 46,
		 45, 46, 47, 48, 50, 52, 54, 55, 41, 42, 42, 45, 47, 48, 50, 49, 49, 50,
		 50, 52, 53, 55, 57, 58, 49, 47, 46, 47, 48, 50, 53, 53, 53, 54, 54, 55,
		 56, 58, 60, 61, 48, 47, 45, 46, 46, 49, 53, 54, 55, 56, 57, 58, 60, 61,
		 63, 64, 49, 47, 45, 45, 45, 49, 53, 55, 58, 60, 61, 62, 63, 65, 67, 68,
		 50, 48, 46, 46, 46, 50, 54, 56, 60, 61, 63, 65, 67, 68, 71, 71, 52, 50,
		 47, 47, 47, 50, 54, 57, 61, 63, 66, 68, 70, 72, 75, 75, 54, 52, 49, 49,
		 48, 52, 55, 58, 62, 65, 68, 71, 73, 75, 78, 79, 57, 54, 52, 51, 50, 53,
		 56, 60, 63, 67, 70, 73, 76, 79, 82, 83, 60, 57, 54, 53, 52, 55, 58, 61,
		 65, 68, 72, 75, 79, 82, 85, 86, 63, 60, 57, 56, 54, 57, 60, 63, 67, 71,
		 75, 78, 82, 85, 89, 90, 65, 61, 58, 57, 55, 58, 61, 64, 68, 71, 75, 79,
		 83, 86, 90, 91,
		 /* Size 32x32 */
		 32, 31, 31, 30, 30, 33, 33, 36, 36, 41, 41, 49, 49, 48, 48, 49, 49, 50,
		 50, 52, 52, 54, 54, 57, 57, 60, 60, 63, 63, 65, 65, 67, 31, 31, 31, 31,
		 31, 34, 34, 38, 38, 42, 42, 47, 47, 47, 47, 47, 47, 48, 48, 50, 50, 52,
		 52, 54, 54, 57, 57, 60, 60, 61, 61, 63, 31, 31, 31, 31, 31, 34, 34, 38,
		 38, 42, 42, 47, 47, 47, 47, 47, 47, 48, 48, 50, 50, 52, 52, 54, 54, 57,
		 57, 60, 60, 61, 61, 63, 30, 31, 31, 32, 32, 35, 35, 40, 40, 42, 42, 46,
		 46, 45, 45, 45, 45, 46, 46, 47, 47, 49, 49, 52, 52, 54, 54, 57, 57, 58,
		 58, 60, 30, 31, 31, 32, 32, 35, 35, 40, 40, 42, 42, 46, 46, 45, 45, 45,
		 45, 46, 46, 47, 47, 49, 49, 52, 52, 54, 54, 57, 57, 58, 58, 60, 33, 34,
		 34, 35, 35, 39, 39, 43, 43, 45, 45, 47, 47, 46, 46, 45, 45, 46, 46, 47,
		 47, 49, 49, 51, 51, 53, 53, 56, 56, 57, 57, 59, 33, 34, 34, 35, 35, 39,
		 39, 43, 43, 45, 45, 47, 47, 46, 46, 45, 45, 46, 46, 47, 47, 49, 49, 51,
		 51, 53, 53, 56, 56, 57, 57, 59, 36, 38, 38, 40, 40, 43, 43, 47, 47, 47,
		 47, 48, 48, 46, 46, 45, 45, 46, 46, 47, 47, 48, 48, 50, 50, 52, 52, 54,
		 54, 55, 55, 57, 36, 38, 38, 40, 40, 43, 43, 47, 47, 47, 47, 48, 48, 46,
		 46, 45, 45, 46, 46, 47, 47, 48, 48, 50, 50, 52, 52, 54, 54, 55, 55, 57,
		 41, 42, 42, 42, 42, 45, 45, 47, 47, 48, 48, 50, 50, 49, 49, 49, 49, 50,
		 50, 50, 50, 52, 52, 53, 53, 55, 55, 57, 57, 58, 58, 60, 41, 42, 42, 42,
		 42, 45, 45, 47, 47, 48, 48, 50, 50, 49, 49, 49, 49, 50, 50, 50, 50, 52,
		 52, 53, 53, 55, 55, 57, 57, 58, 58, 60, 49, 47, 47, 46, 46, 47, 47, 48,
		 48, 50, 50, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 56, 56, 58,
		 58, 60, 60, 61, 61, 62, 49, 47, 47, 46, 46, 47, 47, 48, 48, 50, 50, 53,
		 53, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 56, 56, 58, 58, 60, 60, 61,
		 61, 62, 48, 47, 47, 45, 45, 46, 46, 46, 46, 49, 49, 53, 53, 54, 54, 55,
		 55, 56, 56, 57, 57, 58, 58, 60, 60, 61, 61, 63, 63, 64, 64, 66, 48, 47,
		 47, 45, 45, 46, 46, 46, 46, 49, 49, 53, 53, 54, 54, 55, 55, 56, 56, 57,
		 57, 58, 58, 60, 60, 61, 61, 63, 63, 64, 64, 66, 49, 47, 47, 45, 45, 45,
		 45, 45, 45, 49, 49, 53, 53, 55, 55, 58, 58, 60, 60, 61, 61, 62, 62, 63,
		 63, 65, 65, 67, 67, 68, 68, 69, 49, 47, 47, 45, 45, 45, 45, 45, 45, 49,
		 49, 53, 53, 55, 55, 58, 58, 60, 60, 61, 61, 62, 62, 63, 63, 65, 65, 67,
		 67, 68, 68, 69, 50, 48, 48, 46, 46, 46, 46, 46, 46, 50, 50, 54, 54, 56,
		 56, 60, 60, 61, 61, 63, 63, 65, 65, 67, 67, 68, 68, 71, 71, 71, 71, 72,
		 50, 48, 48, 46, 46, 46, 46, 46, 46, 50, 50, 54, 54, 56, 56, 60, 60, 61,
		 61, 63, 63, 65, 65, 67, 67, 68, 68, 71, 71, 71, 71, 72, 52, 50, 50, 47,
		 47, 47, 47, 47, 47, 50, 50, 54, 54, 57, 57, 61, 61, 63, 63, 66, 66, 68,
		 68, 70, 70, 72, 72, 75, 75, 75, 75, 76, 52, 50, 50, 47, 47, 47, 47, 47,
		 47, 50, 50, 54, 54, 57, 57, 61, 61, 63, 63, 66, 66, 68, 68, 70, 70, 72,
		 72, 75, 75, 75, 75, 76, 54, 52, 52, 49, 49, 49, 49, 48, 48, 52, 52, 55,
		 55, 58, 58, 62, 62, 65, 65, 68, 68, 71, 71, 73, 73, 75, 75, 78, 78, 79,
		 79, 80, 54, 52, 52, 49, 49, 49, 49, 48, 48, 52, 52, 55, 55, 58, 58, 62,
		 62, 65, 65, 68, 68, 71, 71, 73, 73, 75, 75, 78, 78, 79, 79, 80, 57, 54,
		 54, 52, 52, 51, 51, 50, 50, 53, 53, 56, 56, 60, 60, 63, 63, 67, 67, 70,
		 70, 73, 73, 76, 76, 79, 79, 82, 82, 83, 83, 84, 57, 54, 54, 52, 52, 51,
		 51, 50, 50, 53, 53, 56, 56, 60, 60, 63, 63, 67, 67, 70, 70, 73, 73, 76,
		 76, 79, 79, 82, 82, 83, 83, 84, 60, 57, 57, 54, 54, 53, 53, 52, 52, 55,
		 55, 58, 58, 61, 61, 65, 65, 68, 68, 72, 72, 75, 75, 79, 79, 82, 82, 85,
		 85, 86, 86, 88, 60, 57, 57, 54, 54, 53, 53, 52, 52, 55, 55, 58, 58, 61,
		 61, 65, 65, 68, 68, 72, 72, 75, 75, 79, 79, 82, 82, 85, 85, 86, 86, 88,
		 63, 60, 60, 57, 57, 56, 56, 54, 54, 57, 57, 60, 60, 63, 63, 67, 67, 71,
		 71, 75, 75, 78, 78, 82, 82, 85, 85, 89, 89, 90, 90, 92, 63, 60, 60, 57,
		 57, 56, 56, 54, 54, 57, 57, 60, 60, 63, 63, 67, 67, 71, 71, 75, 75, 78,
		 78, 82, 82, 85, 85, 89, 89, 90, 90, 92, 65, 61, 61, 58, 58, 57, 57, 55,
		 55, 58, 58, 61, 61, 64, 64, 68, 68, 71, 71, 75, 75, 79, 79, 83, 83, 86,
		 86, 90, 90, 91, 91, 93, 65, 61, 61, 58, 58, 57, 57, 55, 55, 58, 58, 61,
		 61, 64, 64, 68, 68, 71, 71, 75, 75, 79, 79, 83, 83, 86, 86, 90, 90, 91,
		 91, 93, 67, 63, 63, 60, 60, 59, 59, 57, 57, 60, 60, 62, 62, 66, 66, 69,
		 69, 72, 72, 76, 76, 80, 80, 84, 84, 88, 88, 92, 92, 93, 93, 95,
		 /* Size 4x8 */
		 31, 47, 50, 60, 36, 47, 47, 56, 43, 50, 50, 57, 46, 53, 57, 64, 46, 54,
		 64, 71, 50, 55, 68, 78, 54, 58, 72, 85, 59, 61, 75, 90,
		 /* Size 8x4 */
		 31, 36, 43, 46, 46, 50, 54, 59, 47, 47, 50, 53, 54, 55, 58, 61, 50, 47,
		 50, 57, 64, 68, 72, 75, 60, 56, 57, 64, 71, 78, 85, 90,
		 /* Size 8x16 */
		 32, 31, 37, 48, 49, 52, 57, 63, 31, 31, 38, 47, 47, 50, 54, 60, 30, 32,
		 40, 46, 45, 48, 52, 57, 33, 36, 43, 47, 46, 47, 51, 56, 37, 40, 47, 47,
		 45, 47, 50, 54, 42, 43, 47, 50, 49, 50, 53, 57, 49, 46, 48, 53, 53, 54,
		 57, 60, 48, 46, 47, 53, 56, 57, 60, 64, 49, 45, 46, 53, 58, 61, 64, 67,
		 50, 46, 46, 54, 59, 64, 67, 71, 52, 48, 47, 54, 61, 66, 71, 75, 54, 50,
		 49, 55, 62, 68, 73, 78, 57, 52, 50, 56, 64, 70, 76, 82, 60, 54, 52, 58,
		 65, 72, 79, 85, 63, 57, 55, 60, 67, 75, 82, 89, 64, 59, 56, 61, 68, 75,
		 83, 90,
		 /* Size 16x8 */
		 32, 31, 30, 33, 37, 42, 49, 48, 49, 50, 52, 54, 57, 60, 63, 64, 31, 31,
		 32, 36, 40, 43, 46, 46, 45, 46, 48, 50, 52, 54, 57, 59, 37, 38, 40, 43,
		 47, 47, 48, 47, 46, 46, 47, 49, 50, 52, 55, 56, 48, 47, 46, 47, 47, 50,
		 53, 53, 53, 54, 54, 55, 56, 58, 60, 61, 49, 47, 45, 46, 45, 49, 53, 56,
		 58, 59, 61, 62, 64, 65, 67, 68, 52, 50, 48, 47, 47, 50, 54, 57, 61, 64,
		 66, 68, 70, 72, 75, 75, 57, 54, 52, 51, 50, 53, 57, 60, 64, 67, 71, 73,
		 76, 79, 82, 83, 63, 60, 57, 56, 54, 57, 60, 64, 67, 71, 75, 78, 82, 85,
		 89, 90,
		 /* Size 16x32 */
		 32, 31, 31, 37, 37, 48, 48, 49, 49, 52, 52, 57, 57, 63, 63, 66, 31, 31,
		 31, 38, 38, 47, 47, 47, 47, 50, 50, 54, 54, 60, 60, 63, 31, 31, 31, 38,
		 38, 47, 47, 47, 47, 50, 50, 54, 54, 60, 60, 63, 30, 32, 32, 40, 40, 46,
		 46, 45, 45, 48, 48, 52, 52, 57, 57, 60, 30, 32, 32, 40, 40, 46, 46, 45,
		 45, 48, 48, 52, 52, 57, 57, 60, 33, 36, 36, 43, 43, 47, 47, 46, 46, 47,
		 47, 51, 51, 56, 56, 59, 33, 36, 36, 43, 43, 47, 47, 46, 46, 47, 47, 51,
		 51, 56, 56, 59, 37, 40, 40, 47, 47, 47, 47, 45, 45, 47, 47, 50, 50, 54,
		 54, 57, 37, 40, 40, 47, 47, 47, 47, 45, 45, 47, 47, 50, 50, 54, 54, 57,
		 42, 43, 43, 47, 47, 50, 50, 49, 49, 50, 50, 53, 53, 57, 57, 60, 42, 43,
		 43, 47, 47, 50, 50, 49, 49, 50, 50, 53, 53, 57, 57, 60, 49, 46, 46, 48,
		 48, 53, 53, 53, 53, 54, 54, 57, 57, 60, 60, 62, 49, 46, 46, 48, 48, 53,
		 53, 53, 53, 54, 54, 57, 57, 60, 60, 62, 48, 46, 46, 47, 47, 53, 53, 56,
		 56, 57, 57, 60, 60, 64, 64, 66, 48, 46, 46, 47, 47, 53, 53, 56, 56, 57,
		 57, 60, 60, 64, 64, 66, 49, 45, 45, 46, 46, 53, 53, 58, 58, 61, 61, 64,
		 64, 67, 67, 69, 49, 45, 45, 46, 46, 53, 53, 58, 58, 61, 61, 64, 64, 67,
		 67, 69, 50, 46, 46, 46, 46, 54, 54, 59, 59, 64, 64, 67, 67, 71, 71, 73,
		 50, 46, 46, 46, 46, 54, 54, 59, 59, 64, 64, 67, 67, 71, 71, 73, 52, 48,
		 48, 47, 47, 54, 54, 61, 61, 66, 66, 71, 71, 75, 75, 77, 52, 48, 48, 47,
		 47, 54, 54, 61, 61, 66, 66, 71, 71, 75, 75, 77, 54, 50, 50, 49, 49, 55,
		 55, 62, 62, 68, 68, 73, 73, 78, 78, 80, 54, 50, 50, 49, 49, 55, 55, 62,
		 62, 68, 68, 73, 73, 78, 78, 80, 57, 52, 52, 50, 50, 56, 56, 64, 64, 70,
		 70, 76, 76, 82, 82, 84, 57, 52, 52, 50, 50, 56, 56, 64, 64, 70, 70, 76,
		 76, 82, 82, 84, 60, 54, 54, 52, 52, 58, 58, 65, 65, 72, 72, 79, 79, 85,
		 85, 88, 60, 54, 54, 52, 52, 58, 58, 65, 65, 72, 72, 79, 79, 85, 85, 88,
		 63, 57, 57, 55, 55, 60, 60, 67, 67, 75, 75, 82, 82, 89, 89, 92, 63, 57,
		 57, 55, 55, 60, 60, 67, 67, 75, 75, 82, 82, 89, 89, 92, 64, 59, 59, 56,
		 56, 61, 61, 68, 68, 75, 75, 83, 83, 90, 90, 93, 64, 59, 59, 56, 56, 61,
		 61, 68, 68, 75, 75, 83, 83, 90, 90, 93, 66, 60, 60, 57, 57, 63, 63, 69,
		 69, 77, 77, 84, 84, 92, 92, 95,
		 /* Size 32x16 */
		 32, 31, 31, 30, 30, 33, 33, 37, 37, 42, 42, 49, 49, 48, 48, 49, 49, 50,
		 50, 52, 52, 54, 54, 57, 57, 60, 60, 63, 63, 64, 64, 66, 31, 31, 31, 32,
		 32, 36, 36, 40, 40, 43, 43, 46, 46, 46, 46, 45, 45, 46, 46, 48, 48, 50,
		 50, 52, 52, 54, 54, 57, 57, 59, 59, 60, 31, 31, 31, 32, 32, 36, 36, 40,
		 40, 43, 43, 46, 46, 46, 46, 45, 45, 46, 46, 48, 48, 50, 50, 52, 52, 54,
		 54, 57, 57, 59, 59, 60, 37, 38, 38, 40, 40, 43, 43, 47, 47, 47, 47, 48,
		 48, 47, 47, 46, 46, 46, 46, 47, 47, 49, 49, 50, 50, 52, 52, 55, 55, 56,
		 56, 57, 37, 38, 38, 40, 40, 43, 43, 47, 47, 47, 47, 48, 48, 47, 47, 46,
		 46, 46, 46, 47, 47, 49, 49, 50, 50, 52, 52, 55, 55, 56, 56, 57, 48, 47,
		 47, 46, 46, 47, 47, 47, 47, 50, 50, 53, 53, 53, 53, 53, 53, 54, 54, 54,
		 54, 55, 55, 56, 56, 58, 58, 60, 60, 61, 61, 63, 48, 47, 47, 46, 46, 47,
		 47, 47, 47, 50, 50, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 56,
		 56, 58, 58, 60, 60, 61, 61, 63, 49, 47, 47, 45, 45, 46, 46, 45, 45, 49,
		 49, 53, 53, 56, 56, 58, 58, 59, 59, 61, 61, 62, 62, 64, 64, 65, 65, 67,
		 67, 68, 68, 69, 49, 47, 47, 45, 45, 46, 46, 45, 45, 49, 49, 53, 53, 56,
		 56, 58, 58, 59, 59, 61, 61, 62, 62, 64, 64, 65, 65, 67, 67, 68, 68, 69,
		 52, 50, 50, 48, 48, 47, 47, 47, 47, 50, 50, 54, 54, 57, 57, 61, 61, 64,
		 64, 66, 66, 68, 68, 70, 70, 72, 72, 75, 75, 75, 75, 77, 52, 50, 50, 48,
		 48, 47, 47, 47, 47, 50, 50, 54, 54, 57, 57, 61, 61, 64, 64, 66, 66, 68,
		 68, 70, 70, 72, 72, 75, 75, 75, 75, 77, 57, 54, 54, 52, 52, 51, 51, 50,
		 50, 53, 53, 57, 57, 60, 60, 64, 64, 67, 67, 71, 71, 73, 73, 76, 76, 79,
		 79, 82, 82, 83, 83, 84, 57, 54, 54, 52, 52, 51, 51, 50, 50, 53, 53, 57,
		 57, 60, 60, 64, 64, 67, 67, 71, 71, 73, 73, 76, 76, 79, 79, 82, 82, 83,
		 83, 84, 63, 60, 60, 57, 57, 56, 56, 54, 54, 57, 57, 60, 60, 64, 64, 67,
		 67, 71, 71, 75, 75, 78, 78, 82, 82, 85, 85, 89, 89, 90, 90, 92, 63, 60,
		 60, 57, 57, 56, 56, 54, 54, 57, 57, 60, 60, 64, 64, 67, 67, 71, 71, 75,
		 75, 78, 78, 82, 82, 85, 85, 89, 89, 90, 90, 92, 66, 63, 63, 60, 60, 59,
		 59, 57, 57, 60, 60, 62, 62, 66, 66, 69, 69, 73, 73, 77, 77, 80, 80, 84,
		 84, 88, 88, 92, 92, 93, 93, 95,
		 /* Size 4x16 */
		 31, 48, 52, 63, 31, 47, 50, 60, 32, 46, 48, 57, 36, 47, 47, 56, 40, 47,
		 47, 54, 43, 50, 50, 57, 46, 53, 54, 60, 46, 53, 57, 64, 45, 53, 61, 67,
		 46, 54, 64, 71, 48, 54, 66, 75, 50, 55, 68, 78, 52, 56, 70, 82, 54, 58,
		 72, 85, 57, 60, 75, 89, 59, 61, 75, 90,
		 /* Size 16x4 */
		 31, 31, 32, 36, 40, 43, 46, 46, 45, 46, 48, 50, 52, 54, 57, 59, 48, 47,
		 46, 47, 47, 50, 53, 53, 53, 54, 54, 55, 56, 58, 60, 61, 52, 50, 48, 47,
		 47, 50, 54, 57, 61, 64, 66, 68, 70, 72, 75, 75, 63, 60, 57, 56, 54, 57,
		 60, 64, 67, 71, 75, 78, 82, 85, 89, 90,
		 /* Size 8x32 */
		 32, 31, 37, 48, 49, 52, 57, 63, 31, 31, 38, 47, 47, 50, 54, 60, 31, 31,
		 38, 47, 47, 50, 54, 60, 30, 32, 40, 46, 45, 48, 52, 57, 30, 32, 40, 46,
		 45, 48, 52, 57, 33, 36, 43, 47, 46, 47, 51, 56, 33, 36, 43, 47, 46, 47,
		 51, 56, 37, 40, 47, 47, 45, 47, 50, 54, 37, 40, 47, 47, 45, 47, 50, 54,
		 42, 43, 47, 50, 49, 50, 53, 57, 42, 43, 47, 50, 49, 50, 53, 57, 49, 46,
		 48, 53, 53, 54, 57, 60, 49, 46, 48, 53, 53, 54, 57, 60, 48, 46, 47, 53,
		 56, 57, 60, 64, 48, 46, 47, 53, 56, 57, 60, 64, 49, 45, 46, 53, 58, 61,
		 64, 67, 49, 45, 46, 53, 58, 61, 64, 67, 50, 46, 46, 54, 59, 64, 67, 71,
		 50, 46, 46, 54, 59, 64, 67, 71, 52, 48, 47, 54, 61, 66, 71, 75, 52, 48,
		 47, 54, 61, 66, 71, 75, 54, 50, 49, 55, 62, 68, 73, 78, 54, 50, 49, 55,
		 62, 68, 73, 78, 57, 52, 50, 56, 64, 70, 76, 82, 57, 52, 50, 56, 64, 70,
		 76, 82, 60, 54, 52, 58, 65, 72, 79, 85, 60, 54, 52, 58, 65, 72, 79, 85,
		 63, 57, 55, 60, 67, 75, 82, 89, 63, 57, 55, 60, 67, 75, 82, 89, 64, 59,
		 56, 61, 68, 75, 83, 90, 64, 59, 56, 61, 68, 75, 83, 90, 66, 60, 57, 63,
		 69, 77, 84, 92,
		 /* Size 32x8 */
		 32, 31, 31, 30, 30, 33, 33, 37, 37, 42, 42, 49, 49, 48, 48, 49, 49, 50,
		 50, 52, 52, 54, 54, 57, 57, 60, 60, 63, 63, 64, 64, 66, 31, 31, 31, 32,
		 32, 36, 36, 40, 40, 43, 43, 46, 46, 46, 46, 45, 45, 46, 46, 48, 48, 50,
		 50, 52, 52, 54, 54, 57, 57, 59, 59, 60, 37, 38, 38, 40, 40, 43, 43, 47,
		 47, 47, 47, 48, 48, 47, 47, 46, 46, 46, 46, 47, 47, 49, 49, 50, 50, 52,
		 52, 55, 55, 56, 56, 57, 48, 47, 47, 46, 46, 47, 47, 47, 47, 50, 50, 53,
		 53, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 56, 56, 58, 58, 60, 60, 61,
		 61, 63, 49, 47, 47, 45, 45, 46, 46, 45, 45, 49, 49, 53, 53, 56, 56, 58,
		 58, 59, 59, 61, 61, 62, 62, 64, 64, 65, 65, 67, 67, 68, 68, 69, 52, 50,
		 50, 48, 48, 47, 47, 47, 47, 50, 50, 54, 54, 57, 57, 61, 61, 64, 64, 66,
		 66, 68, 68, 70, 70, 72, 72, 75, 75, 75, 75, 77, 57, 54, 54, 52, 52, 51,
		 51, 50, 50, 53, 53, 57, 57, 60, 60, 64, 64, 67, 67, 71, 71, 73, 73, 76,
		 76, 79, 79, 82, 82, 83, 83, 84, 63, 60, 60, 57, 57, 56, 56, 54, 54, 57,
		 57, 60, 60, 64, 64, 67, 67, 71, 71, 75, 75, 78, 78, 82, 82, 85, 85, 89,
		 89, 90, 90, 92},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 33, 45, 62, 33, 39, 51, 64, 45, 51, 71, 87, 62, 64, 87, 108,
		 /* Size 8x8 */
		 31, 32, 32, 35, 42, 51, 59, 69, 32, 32, 33, 35, 41, 49, 56, 65, 32, 33,
		 35, 38, 43, 49, 56, 64, 35, 35, 38, 48, 54, 59, 66, 73, 42, 41, 43, 54,
		 63, 71, 77, 85, 51, 49, 49, 59, 71, 81, 89, 97, 59, 56, 56, 66, 77, 89,
		 98, 108, 69, 65, 64, 73, 85, 97, 108, 119,
		 /* Size 16x16 */
		 32, 31, 31, 31, 32, 34, 35, 38, 41, 45, 48, 54, 59, 65, 71, 80, 31, 32,
		 32, 32, 32, 34, 35, 37, 40, 43, 46, 51, 56, 62, 68, 76, 31, 32, 32, 32,
		 32, 33, 34, 36, 38, 41, 44, 49, 54, 59, 65, 72, 31, 32, 32, 33, 34, 35,
		 36, 38, 40, 42, 45, 50, 54, 59, 64, 71, 32, 32, 32, 34, 35, 37, 38, 39,
		 41, 43, 46, 49, 53, 58, 63, 69, 34, 34, 33, 35, 37, 39, 42, 44, 46, 48,
		 51, 54, 58, 63, 68, 74, 35, 35, 34, 36, 38, 42, 46, 48, 50, 53, 55, 59,
		 62, 67, 72, 78, 38, 37, 36, 38, 39, 44, 48, 51, 54, 57, 59, 63, 67, 71,
		 76, 82, 41, 40, 38, 40, 41, 46, 50, 54, 57, 60, 63, 67, 71, 75, 80, 86,
		 45, 43, 41, 42, 43, 48, 53, 57, 60, 65, 68, 72, 76, 81, 85, 91, 48, 46,
		 44, 45, 46, 51, 55, 59, 63, 68, 71, 76, 80, 85, 90, 96, 54, 51, 49, 50,
		 49, 54, 59, 63, 67, 72, 76, 82, 87, 92, 97, 104, 59, 56, 54, 54, 53, 58,
		 62, 67, 71, 76, 80, 87, 92, 98, 103, 110, 65, 62, 59, 59, 58, 63, 67,
		 71, 75, 81, 85, 92, 98, 105, 111, 118, 71, 68, 65, 64, 63, 68, 72, 76,
		 80, 85, 90, 97, 103, 111, 117, 125, 80, 76, 72, 71, 69, 74, 78, 82, 86,
		 91, 96, 104, 110, 118, 125, 134,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 34, 34, 35, 36, 38, 39, 41, 44,
		 45, 48, 48, 53, 54, 57, 59, 62, 65, 67, 71, 72, 80, 80, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 34, 34, 35, 35, 37, 38, 40, 42, 43, 46, 46, 51,
		 52, 55, 56, 59, 62, 64, 68, 69, 76, 76, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 34, 34, 35, 35, 37, 38, 40, 42, 43, 46, 46, 51, 51, 55, 56, 59,
		 62, 64, 68, 69, 76, 76, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 34, 34, 36, 38, 39, 41, 42, 45, 45, 49, 50, 53, 54, 57, 60, 62, 66, 66,
		 73, 73, 31, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 36, 37,
		 38, 41, 41, 44, 44, 49, 49, 52, 54, 56, 59, 61, 65, 65, 72, 72, 31, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 35, 35, 37, 38, 39, 41, 42, 45,
		 45, 49, 49, 52, 54, 56, 59, 61, 64, 65, 72, 72, 31, 32, 32, 32, 32, 33,
		 33, 33, 34, 34, 35, 35, 36, 36, 38, 39, 40, 42, 42, 45, 45, 49, 50, 52,
		 54, 56, 59, 60, 64, 65, 71, 71, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34,
		 35, 35, 36, 37, 38, 39, 40, 42, 43, 45, 45, 49, 49, 52, 54, 56, 59, 60,
		 64, 64, 70, 70, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 37, 37, 38, 38,
		 39, 40, 41, 42, 43, 46, 46, 49, 49, 52, 53, 55, 58, 59, 63, 63, 69, 69,
		 32, 32, 32, 32, 33, 33, 34, 34, 35, 35, 37, 37, 38, 38, 40, 41, 41, 43,
		 43, 46, 46, 49, 50, 52, 54, 56, 58, 60, 63, 64, 70, 70, 34, 34, 34, 33,
		 33, 34, 35, 35, 37, 37, 39, 39, 42, 42, 44, 45, 46, 47, 48, 51, 51, 54,
		 54, 57, 58, 60, 63, 64, 68, 68, 74, 74, 34, 34, 34, 33, 33, 34, 35, 35,
		 37, 37, 39, 39, 42, 42, 44, 45, 46, 47, 48, 51, 51, 54, 54, 57, 58, 60,
		 63, 64, 68, 68, 74, 74, 35, 35, 35, 34, 34, 35, 36, 36, 38, 38, 42, 42,
		 46, 47, 48, 49, 50, 52, 53, 55, 55, 58, 59, 61, 62, 64, 67, 68, 72, 72,
		 78, 78, 36, 35, 35, 34, 34, 35, 36, 37, 38, 38, 42, 42, 47, 48, 50, 50,
		 52, 54, 54, 57, 57, 59, 60, 62, 64, 66, 68, 69, 73, 73, 79, 79, 38, 37,
		 37, 36, 36, 37, 38, 38, 39, 40, 44, 44, 48, 50, 51, 52, 54, 56, 57, 59,
		 59, 62, 63, 65, 67, 69, 71, 72, 76, 76, 82, 82, 39, 38, 38, 38, 37, 38,
		 39, 39, 40, 41, 45, 45, 49, 50, 52, 54, 55, 58, 58, 61, 61, 64, 65, 67,
		 69, 71, 73, 74, 78, 78, 84, 84, 41, 40, 40, 39, 38, 39, 40, 40, 41, 41,
		 46, 46, 50, 52, 54, 55, 57, 60, 60, 63, 63, 67, 67, 70, 71, 73, 75, 77,
		 80, 81, 86, 86, 44, 42, 42, 41, 41, 41, 42, 42, 42, 43, 47, 47, 52, 54,
		 56, 58, 60, 63, 64, 67, 67, 71, 71, 74, 75, 77, 79, 81, 84, 85, 90, 90,
		 45, 43, 43, 42, 41, 42, 42, 43, 43, 43, 48, 48, 53, 54, 57, 58, 60, 64,
		 65, 68, 68, 72, 72, 75, 76, 78, 81, 82, 85, 86, 91, 91, 48, 46, 46, 45,
		 44, 45, 45, 45, 46, 46, 51, 51, 55, 57, 59, 61, 63, 67, 68, 71, 71, 75,
		 76, 79, 80, 83, 85, 87, 90, 91, 96, 96, 48, 46, 46, 45, 44, 45, 45, 45,
		 46, 46, 51, 51, 55, 57, 59, 61, 63, 67, 68, 71, 71, 75, 76, 79, 80, 83,
		 85, 87, 90, 91, 96, 96, 53, 51, 51, 49, 49, 49, 49, 49, 49, 49, 54, 54,
		 58, 59, 62, 64, 67, 71, 72, 75, 75, 81, 81, 85, 86, 89, 91, 93, 97, 97,
		 103, 103, 54, 52, 51, 50, 49, 49, 50, 49, 49, 50, 54, 54, 59, 60, 63,
		 65, 67, 71, 72, 76, 76, 81, 82, 85, 87, 89, 92, 94, 97, 98, 104, 104,
		 57, 55, 55, 53, 52, 52, 52, 52, 52, 52, 57, 57, 61, 62, 65, 67, 70, 74,
		 75, 79, 79, 85, 85, 89, 90, 93, 96, 98, 102, 102, 108, 108, 59, 56, 56,
		 54, 54, 54, 54, 54, 53, 54, 58, 58, 62, 64, 67, 69, 71, 75, 76, 80, 80,
		 86, 87, 90, 92, 95, 98, 99, 103, 104, 110, 110, 62, 59, 59, 57, 56, 56,
		 56, 56, 55, 56, 60, 60, 64, 66, 69, 71, 73, 77, 78, 83, 83, 89, 89, 93,
		 95, 98, 101, 103, 107, 108, 114, 114, 65, 62, 62, 60, 59, 59, 59, 59,
		 58, 58, 63, 63, 67, 68, 71, 73, 75, 79, 81, 85, 85, 91, 92, 96, 98, 101,
		 105, 106, 111, 111, 118, 118, 67, 64, 64, 62, 61, 61, 60, 60, 59, 60,
		 64, 64, 68, 69, 72, 74, 77, 81, 82, 87, 87, 93, 94, 98, 99, 103, 106,
		 108, 113, 113, 120, 120, 71, 68, 68, 66, 65, 64, 64, 64, 63, 63, 68, 68,
		 72, 73, 76, 78, 80, 84, 85, 90, 90, 97, 97, 102, 103, 107, 111, 113,
		 117, 118, 125, 125, 72, 69, 69, 66, 65, 65, 65, 64, 63, 64, 68, 68, 72,
		 73, 76, 78, 81, 85, 86, 91, 91, 97, 98, 102, 104, 108, 111, 113, 118,
		 119, 126, 126, 80, 76, 76, 73, 72, 72, 71, 70, 69, 70, 74, 74, 78, 79,
		 82, 84, 86, 90, 91, 96, 96, 103, 104, 108, 110, 114, 118, 120, 125, 126,
		 134, 134, 80, 76, 76, 73, 72, 72, 71, 70, 69, 70, 74, 74, 78, 79, 82,
		 84, 86, 90, 91, 96, 96, 103, 104, 108, 110, 114, 118, 120, 125, 126,
		 134, 134,
		 /* Size 4x8 */
		 32, 34, 43, 62, 32, 34, 42, 59, 33, 37, 44, 58, 35, 43, 54, 68, 41, 48,
		 64, 79, 49, 54, 71, 91, 57, 60, 78, 101, 66, 68, 86, 111,
		 /* Size 8x4 */
		 32, 32, 33, 35, 41, 49, 57, 66, 34, 34, 37, 43, 48, 54, 60, 68, 43, 42,
		 44, 54, 64, 71, 78, 86, 62, 59, 58, 68, 79, 91, 101, 111,
		 /* Size 8x16 */
		 32, 31, 32, 36, 44, 53, 62, 73, 31, 32, 32, 35, 42, 51, 59, 69, 31, 32,
		 33, 34, 41, 49, 57, 66, 32, 32, 34, 36, 42, 50, 57, 65, 32, 33, 35, 38,
		 42, 49, 56, 64, 34, 34, 37, 42, 48, 54, 61, 69, 35, 34, 38, 47, 52, 59,
		 65, 73, 38, 36, 40, 49, 56, 63, 69, 77, 41, 39, 41, 51, 60, 67, 74, 81,
		 44, 42, 43, 54, 64, 72, 79, 86, 48, 45, 46, 56, 67, 76, 83, 91, 53, 49,
		 50, 60, 71, 82, 90, 99, 58, 54, 54, 63, 75, 87, 95, 105, 65, 60, 58, 68,
		 79, 92, 102, 112, 71, 65, 63, 73, 84, 97, 108, 119, 79, 72, 70, 79, 90,
		 104, 115, 127,
		 /* Size 16x8 */
		 32, 31, 31, 32, 32, 34, 35, 38, 41, 44, 48, 53, 58, 65, 71, 79, 31, 32,
		 32, 32, 33, 34, 34, 36, 39, 42, 45, 49, 54, 60, 65, 72, 32, 32, 33, 34,
		 35, 37, 38, 40, 41, 43, 46, 50, 54, 58, 63, 70, 36, 35, 34, 36, 38, 42,
		 47, 49, 51, 54, 56, 60, 63, 68, 73, 79, 44, 42, 41, 42, 42, 48, 52, 56,
		 60, 64, 67, 71, 75, 79, 84, 90, 53, 51, 49, 50, 49, 54, 59, 63, 67, 72,
		 76, 82, 87, 92, 97, 104, 62, 59, 57, 57, 56, 61, 65, 69, 74, 79, 83, 90,
		 95, 102, 108, 115, 73, 69, 66, 65, 64, 69, 73, 77, 81, 86, 91, 99, 105,
		 112, 119, 127,
		 /* Size 16x32 */
		 32, 31, 31, 32, 32, 34, 36, 38, 44, 44, 53, 53, 62, 65, 73, 79, 31, 32,
		 32, 32, 32, 34, 35, 37, 42, 43, 51, 51, 60, 62, 70, 75, 31, 32, 32, 32,
		 32, 34, 35, 37, 42, 43, 51, 51, 59, 62, 69, 75, 31, 32, 32, 32, 32, 33,
		 35, 36, 41, 42, 50, 50, 58, 60, 67, 73, 31, 32, 32, 32, 33, 33, 34, 36,
		 41, 41, 49, 49, 57, 59, 66, 72, 31, 32, 32, 33, 33, 34, 35, 37, 41, 42,
		 49, 49, 57, 59, 66, 71, 32, 32, 32, 33, 34, 35, 36, 38, 42, 43, 50, 50,
		 57, 59, 65, 71, 32, 32, 32, 34, 34, 35, 37, 38, 42, 43, 49, 49, 56, 59,
		 65, 70, 32, 32, 33, 34, 35, 37, 38, 39, 42, 43, 49, 49, 56, 58, 64, 69,
		 32, 33, 33, 34, 35, 37, 39, 40, 43, 44, 50, 50, 56, 58, 64, 69, 34, 34,
		 34, 36, 37, 39, 42, 44, 48, 48, 54, 54, 61, 63, 69, 73, 34, 34, 34, 36,
		 37, 39, 42, 44, 48, 48, 54, 54, 61, 63, 69, 73, 35, 34, 34, 37, 38, 42,
		 47, 48, 52, 53, 59, 59, 65, 67, 73, 77, 36, 35, 34, 37, 38, 43, 48, 49,
		 54, 54, 60, 60, 66, 68, 74, 78, 38, 36, 36, 38, 40, 44, 49, 51, 56, 57,
		 63, 63, 69, 71, 77, 81, 39, 38, 37, 40, 40, 45, 50, 52, 58, 58, 65, 65,
		 71, 73, 79, 84, 41, 39, 39, 41, 41, 46, 51, 54, 60, 60, 67, 67, 74, 76,
		 81, 86, 44, 41, 41, 42, 43, 48, 53, 56, 63, 64, 71, 71, 78, 79, 85, 90,
		 44, 42, 42, 43, 43, 48, 54, 56, 64, 64, 72, 72, 79, 81, 86, 91, 48, 45,
		 45, 46, 46, 51, 56, 59, 67, 67, 76, 76, 83, 85, 91, 96, 48, 45, 45, 46,
		 46, 51, 56, 59, 67, 67, 76, 76, 83, 85, 91, 96, 53, 49, 49, 49, 49, 54,
		 59, 62, 71, 71, 81, 81, 89, 91, 98, 103, 53, 50, 49, 50, 50, 54, 60, 63,
		 71, 72, 82, 82, 90, 92, 99, 103, 57, 53, 52, 52, 52, 57, 62, 65, 74, 75,
		 85, 85, 94, 96, 103, 108, 58, 54, 54, 54, 54, 58, 63, 67, 75, 76, 87,
		 87, 95, 98, 105, 110, 61, 57, 57, 56, 56, 60, 66, 69, 77, 78, 89, 89,
		 98, 101, 108, 114, 65, 60, 60, 59, 58, 63, 68, 71, 79, 80, 92, 92, 102,
		 105, 112, 118, 67, 62, 61, 60, 60, 64, 69, 72, 81, 82, 94, 94, 103, 106,
		 114, 120, 71, 66, 65, 64, 63, 68, 73, 76, 84, 85, 97, 97, 108, 111, 119,
		 125, 72, 66, 66, 64, 64, 68, 73, 76, 85, 86, 98, 98, 108, 111, 119, 125,
		 79, 73, 72, 71, 70, 74, 79, 82, 90, 91, 104, 104, 115, 118, 127, 133,
		 79, 73, 72, 71, 70, 74, 79, 82, 90, 91, 104, 104, 115, 118, 127, 133,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 35, 36, 38, 39, 41, 44,
		 44, 48, 48, 53, 53, 57, 58, 61, 65, 67, 71, 72, 79, 79, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 34, 34, 34, 35, 36, 38, 39, 41, 42, 45, 45, 49,
		 50, 53, 54, 57, 60, 62, 66, 66, 73, 73, 31, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 34, 34, 34, 34, 36, 37, 39, 41, 42, 45, 45, 49, 49, 52, 54, 57,
		 60, 61, 65, 66, 72, 72, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 36, 36,
		 37, 37, 38, 40, 41, 42, 43, 46, 46, 49, 50, 52, 54, 56, 59, 60, 64, 64,
		 71, 71, 32, 32, 32, 32, 33, 33, 34, 34, 35, 35, 37, 37, 38, 38, 40, 40,
		 41, 43, 43, 46, 46, 49, 50, 52, 54, 56, 58, 60, 63, 64, 70, 70, 34, 34,
		 34, 33, 33, 34, 35, 35, 37, 37, 39, 39, 42, 43, 44, 45, 46, 48, 48, 51,
		 51, 54, 54, 57, 58, 60, 63, 64, 68, 68, 74, 74, 36, 35, 35, 35, 34, 35,
		 36, 37, 38, 39, 42, 42, 47, 48, 49, 50, 51, 53, 54, 56, 56, 59, 60, 62,
		 63, 66, 68, 69, 73, 73, 79, 79, 38, 37, 37, 36, 36, 37, 38, 38, 39, 40,
		 44, 44, 48, 49, 51, 52, 54, 56, 56, 59, 59, 62, 63, 65, 67, 69, 71, 72,
		 76, 76, 82, 82, 44, 42, 42, 41, 41, 41, 42, 42, 42, 43, 48, 48, 52, 54,
		 56, 58, 60, 63, 64, 67, 67, 71, 71, 74, 75, 77, 79, 81, 84, 85, 90, 90,
		 44, 43, 43, 42, 41, 42, 43, 43, 43, 44, 48, 48, 53, 54, 57, 58, 60, 64,
		 64, 67, 67, 71, 72, 75, 76, 78, 80, 82, 85, 86, 91, 91, 53, 51, 51, 50,
		 49, 49, 50, 49, 49, 50, 54, 54, 59, 60, 63, 65, 67, 71, 72, 76, 76, 81,
		 82, 85, 87, 89, 92, 94, 97, 98, 104, 104, 53, 51, 51, 50, 49, 49, 50,
		 49, 49, 50, 54, 54, 59, 60, 63, 65, 67, 71, 72, 76, 76, 81, 82, 85, 87,
		 89, 92, 94, 97, 98, 104, 104, 62, 60, 59, 58, 57, 57, 57, 56, 56, 56,
		 61, 61, 65, 66, 69, 71, 74, 78, 79, 83, 83, 89, 90, 94, 95, 98, 102,
		 103, 108, 108, 115, 115, 65, 62, 62, 60, 59, 59, 59, 59, 58, 58, 63, 63,
		 67, 68, 71, 73, 76, 79, 81, 85, 85, 91, 92, 96, 98, 101, 105, 106, 111,
		 111, 118, 118, 73, 70, 69, 67, 66, 66, 65, 65, 64, 64, 69, 69, 73, 74,
		 77, 79, 81, 85, 86, 91, 91, 98, 99, 103, 105, 108, 112, 114, 119, 119,
		 127, 127, 79, 75, 75, 73, 72, 71, 71, 70, 69, 69, 73, 73, 77, 78, 81,
		 84, 86, 90, 91, 96, 96, 103, 103, 108, 110, 114, 118, 120, 125, 125,
		 133, 133,
		 /* Size 4x16 */
		 31, 34, 44, 65, 32, 34, 43, 62, 32, 33, 41, 59, 32, 35, 43, 59, 32, 37,
		 43, 58, 34, 39, 48, 63, 34, 42, 53, 67, 36, 44, 57, 71, 39, 46, 60, 76,
		 42, 48, 64, 81, 45, 51, 67, 85, 50, 54, 72, 92, 54, 58, 76, 98, 60, 63,
		 80, 105, 66, 68, 85, 111, 73, 74, 91, 118,
		 /* Size 16x4 */
		 31, 32, 32, 32, 32, 34, 34, 36, 39, 42, 45, 50, 54, 60, 66, 73, 34, 34,
		 33, 35, 37, 39, 42, 44, 46, 48, 51, 54, 58, 63, 68, 74, 44, 43, 41, 43,
		 43, 48, 53, 57, 60, 64, 67, 72, 76, 80, 85, 91, 65, 62, 59, 59, 58, 63,
		 67, 71, 76, 81, 85, 92, 98, 105, 111, 118,
		 /* Size 8x32 */
		 32, 31, 32, 36, 44, 53, 62, 73, 31, 32, 32, 35, 42, 51, 60, 70, 31, 32,
		 32, 35, 42, 51, 59, 69, 31, 32, 32, 35, 41, 50, 58, 67, 31, 32, 33, 34,
		 41, 49, 57, 66, 31, 32, 33, 35, 41, 49, 57, 66, 32, 32, 34, 36, 42, 50,
		 57, 65, 32, 32, 34, 37, 42, 49, 56, 65, 32, 33, 35, 38, 42, 49, 56, 64,
		 32, 33, 35, 39, 43, 50, 56, 64, 34, 34, 37, 42, 48, 54, 61, 69, 34, 34,
		 37, 42, 48, 54, 61, 69, 35, 34, 38, 47, 52, 59, 65, 73, 36, 34, 38, 48,
		 54, 60, 66, 74, 38, 36, 40, 49, 56, 63, 69, 77, 39, 37, 40, 50, 58, 65,
		 71, 79, 41, 39, 41, 51, 60, 67, 74, 81, 44, 41, 43, 53, 63, 71, 78, 85,
		 44, 42, 43, 54, 64, 72, 79, 86, 48, 45, 46, 56, 67, 76, 83, 91, 48, 45,
		 46, 56, 67, 76, 83, 91, 53, 49, 49, 59, 71, 81, 89, 98, 53, 49, 50, 60,
		 71, 82, 90, 99, 57, 52, 52, 62, 74, 85, 94, 103, 58, 54, 54, 63, 75, 87,
		 95, 105, 61, 57, 56, 66, 77, 89, 98, 108, 65, 60, 58, 68, 79, 92, 102,
		 112, 67, 61, 60, 69, 81, 94, 103, 114, 71, 65, 63, 73, 84, 97, 108, 119,
		 72, 66, 64, 73, 85, 98, 108, 119, 79, 72, 70, 79, 90, 104, 115, 127, 79,
		 72, 70, 79, 90, 104, 115, 127,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 35, 36, 38, 39, 41, 44,
		 44, 48, 48, 53, 53, 57, 58, 61, 65, 67, 71, 72, 79, 79, 31, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 34, 34, 34, 34, 36, 37, 39, 41, 42, 45, 45, 49,
		 49, 52, 54, 57, 60, 61, 65, 66, 72, 72, 32, 32, 32, 32, 33, 33, 34, 34,
		 35, 35, 37, 37, 38, 38, 40, 40, 41, 43, 43, 46, 46, 49, 50, 52, 54, 56,
		 58, 60, 63, 64, 70, 70, 36, 35, 35, 35, 34, 35, 36, 37, 38, 39, 42, 42,
		 47, 48, 49, 50, 51, 53, 54, 56, 56, 59, 60, 62, 63, 66, 68, 69, 73, 73,
		 79, 79, 44, 42, 42, 41, 41, 41, 42, 42, 42, 43, 48, 48, 52, 54, 56, 58,
		 60, 63, 64, 67, 67, 71, 71, 74, 75, 77, 79, 81, 84, 85, 90, 90, 53, 51,
		 51, 50, 49, 49, 50, 49, 49, 50, 54, 54, 59, 60, 63, 65, 67, 71, 72, 76,
		 76, 81, 82, 85, 87, 89, 92, 94, 97, 98, 104, 104, 62, 60, 59, 58, 57,
		 57, 57, 56, 56, 56, 61, 61, 65, 66, 69, 71, 74, 78, 79, 83, 83, 89, 90,
		 94, 95, 98, 102, 103, 108, 108, 115, 115, 73, 70, 69, 67, 66, 66, 65,
		 65, 64, 64, 69, 69, 73, 74, 77, 79, 81, 85, 86, 91, 91, 98, 99, 103,
		 105, 108, 112, 114, 119, 119, 127, 127},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 42, 47, 53, 42, 48, 50, 54, 47, 50, 61, 67, 53, 54, 67, 78,
		 /* Size 8x8 */
		 31, 32, 38, 48, 47, 50, 53, 57, 32, 35, 42, 47, 45, 47, 50, 54, 38, 42,
		 47, 48, 45, 47, 49, 52, 48, 47, 48, 53, 53, 54, 56, 58, 47, 45, 45, 53,
		 58, 61, 63, 65, 50, 47, 47, 54, 61, 66, 69, 72, 53, 50, 49, 56, 63, 69,
		 73, 77, 57, 54, 52, 58, 65, 72, 77, 82,
		 /* Size 16x16 */
		 32, 31, 30, 33, 36, 41, 47, 49, 49, 49, 50, 52, 54, 57, 60, 63, 31, 31,
		 31, 34, 38, 42, 46, 47, 47, 47, 48, 50, 52, 54, 57, 60, 30, 31, 32, 35,
		 40, 42, 45, 46, 45, 45, 46, 47, 49, 52, 54, 57, 33, 34, 35, 39, 43, 45,
		 47, 46, 46, 45, 46, 47, 49, 51, 53, 56, 36, 38, 40, 43, 47, 47, 47, 47,
		 46, 45, 46, 47, 48, 50, 52, 54, 41, 42, 42, 45, 47, 48, 50, 50, 49, 49,
		 50, 50, 52, 53, 55, 57, 47, 46, 45, 47, 47, 50, 52, 52, 52, 52, 53, 53,
		 55, 56, 58, 60, 49, 47, 46, 46, 47, 50, 52, 53, 54, 55, 55, 56, 57, 58,
		 60, 62, 49, 47, 45, 46, 46, 49, 52, 54, 55, 57, 58, 59, 60, 61, 63, 65,
		 49, 47, 45, 45, 45, 49, 52, 55, 57, 59, 60, 61, 63, 64, 66, 68, 50, 48,
		 46, 46, 46, 50, 53, 55, 58, 60, 61, 63, 65, 67, 68, 71, 52, 50, 47, 47,
		 47, 50, 53, 56, 59, 61, 63, 66, 68, 70, 72, 75, 54, 52, 49, 49, 48, 52,
		 55, 57, 60, 63, 65, 68, 71, 73, 75, 78, 57, 54, 52, 51, 50, 53, 56, 58,
		 61, 64, 67, 70, 73, 76, 79, 82, 60, 57, 54, 53, 52, 55, 58, 60, 63, 66,
		 68, 72, 75, 79, 82, 85, 63, 60, 57, 56, 54, 57, 60, 62, 65, 68, 71, 75,
		 78, 82, 85, 89,
		 /* Size 32x32 */
		 32, 31, 31, 30, 30, 32, 33, 34, 36, 37, 41, 41, 47, 49, 49, 48, 49, 49,
		 49, 50, 50, 52, 52, 54, 54, 56, 57, 58, 60, 60, 63, 63, 31, 31, 31, 31,
		 31, 32, 34, 35, 38, 38, 42, 42, 46, 48, 47, 47, 47, 47, 47, 48, 48, 50,
		 50, 51, 52, 53, 54, 55, 57, 57, 60, 60, 31, 31, 31, 31, 31, 33, 34, 35,
		 38, 39, 42, 42, 46, 47, 47, 47, 47, 47, 47, 48, 48, 49, 50, 51, 52, 53,
		 54, 55, 57, 57, 60, 60, 30, 31, 31, 31, 31, 33, 35, 36, 39, 40, 42, 42,
		 46, 47, 46, 46, 46, 45, 46, 47, 47, 48, 48, 50, 50, 51, 52, 53, 55, 55,
		 58, 58, 30, 31, 31, 31, 32, 33, 35, 36, 40, 40, 42, 42, 45, 46, 46, 45,
		 45, 45, 45, 46, 46, 47, 47, 49, 49, 51, 52, 52, 54, 54, 57, 57, 32, 32,
		 33, 33, 33, 35, 37, 38, 41, 42, 43, 43, 46, 47, 46, 46, 45, 45, 45, 46,
		 46, 47, 47, 49, 49, 50, 51, 52, 54, 54, 57, 57, 33, 34, 34, 35, 35, 37,
		 39, 40, 43, 43, 45, 45, 47, 47, 46, 46, 46, 45, 45, 46, 46, 47, 47, 49,
		 49, 50, 51, 52, 53, 54, 56, 56, 34, 35, 35, 36, 36, 38, 40, 41, 44, 44,
		 45, 45, 47, 47, 47, 46, 46, 45, 45, 46, 46, 47, 47, 48, 49, 50, 51, 51,
		 53, 53, 55, 55, 36, 38, 38, 39, 40, 41, 43, 44, 47, 47, 47, 47, 47, 48,
		 47, 46, 46, 45, 45, 46, 46, 46, 47, 48, 48, 49, 50, 50, 52, 52, 54, 54,
		 37, 38, 39, 40, 40, 42, 43, 44, 47, 47, 47, 47, 48, 48, 47, 47, 46, 45,
		 46, 46, 46, 47, 47, 48, 48, 49, 50, 51, 52, 52, 55, 55, 41, 42, 42, 42,
		 42, 43, 45, 45, 47, 47, 48, 48, 50, 50, 50, 49, 49, 49, 49, 50, 50, 50,
		 50, 51, 52, 52, 53, 54, 55, 55, 57, 57, 41, 42, 42, 42, 42, 43, 45, 45,
		 47, 47, 48, 48, 50, 50, 50, 49, 49, 49, 49, 50, 50, 50, 50, 51, 52, 52,
		 53, 54, 55, 55, 57, 57, 47, 46, 46, 46, 45, 46, 47, 47, 47, 48, 50, 50,
		 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 54, 55, 55, 56, 56, 58, 58,
		 60, 60, 49, 48, 47, 47, 46, 47, 47, 47, 48, 48, 50, 50, 52, 53, 53, 53,
		 53, 53, 53, 54, 54, 54, 54, 55, 55, 56, 56, 57, 58, 58, 60, 60, 49, 47,
		 47, 46, 46, 46, 46, 47, 47, 47, 50, 50, 52, 53, 53, 54, 54, 55, 55, 55,
		 55, 56, 56, 57, 57, 58, 58, 59, 60, 60, 62, 62, 48, 47, 47, 46, 45, 46,
		 46, 46, 46, 47, 49, 49, 52, 53, 54, 54, 55, 55, 56, 56, 56, 57, 57, 58,
		 58, 59, 60, 60, 61, 62, 63, 63, 49, 47, 47, 46, 45, 45, 46, 46, 46, 46,
		 49, 49, 52, 53, 54, 55, 55, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 62,
		 63, 63, 65, 65, 49, 47, 47, 45, 45, 45, 45, 45, 45, 45, 49, 49, 52, 53,
		 55, 55, 57, 58, 59, 60, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 67, 67,
		 49, 47, 47, 46, 45, 45, 45, 45, 45, 46, 49, 49, 52, 53, 55, 56, 57, 59,
		 59, 60, 60, 61, 61, 62, 63, 63, 64, 65, 66, 66, 68, 68, 50, 48, 48, 47,
		 46, 46, 46, 46, 46, 46, 50, 50, 53, 54, 55, 56, 58, 60, 60, 61, 61, 63,
		 63, 65, 65, 66, 67, 67, 68, 69, 71, 71, 50, 48, 48, 47, 46, 46, 46, 46,
		 46, 46, 50, 50, 53, 54, 55, 56, 58, 60, 60, 61, 61, 63, 63, 65, 65, 66,
		 67, 67, 68, 69, 71, 71, 52, 50, 49, 48, 47, 47, 47, 47, 46, 47, 50, 50,
		 53, 54, 56, 57, 59, 61, 61, 63, 63, 66, 66, 67, 68, 69, 70, 71, 72, 72,
		 74, 74, 52, 50, 50, 48, 47, 47, 47, 47, 47, 47, 50, 50, 53, 54, 56, 57,
		 59, 61, 61, 63, 63, 66, 66, 68, 68, 69, 70, 71, 72, 73, 75, 75, 54, 51,
		 51, 50, 49, 49, 49, 48, 48, 48, 51, 51, 54, 55, 57, 58, 60, 62, 62, 65,
		 65, 67, 68, 69, 70, 71, 72, 73, 74, 75, 77, 77, 54, 52, 52, 50, 49, 49,
		 49, 49, 48, 48, 52, 52, 55, 55, 57, 58, 60, 62, 63, 65, 65, 68, 68, 70,
		 71, 72, 73, 74, 75, 76, 78, 78, 56, 53, 53, 51, 51, 50, 50, 50, 49, 49,
		 52, 52, 55, 56, 58, 59, 61, 63, 63, 66, 66, 69, 69, 71, 72, 73, 75, 75,
		 77, 77, 80, 80, 57, 54, 54, 52, 52, 51, 51, 51, 50, 50, 53, 53, 56, 56,
		 58, 60, 61, 63, 64, 67, 67, 70, 70, 72, 73, 75, 76, 77, 79, 79, 82, 82,
		 58, 55, 55, 53, 52, 52, 52, 51, 50, 51, 54, 54, 56, 57, 59, 60, 62, 64,
		 65, 67, 67, 71, 71, 73, 74, 75, 77, 78, 80, 80, 83, 83, 60, 57, 57, 55,
		 54, 54, 53, 53, 52, 52, 55, 55, 58, 58, 60, 61, 63, 65, 66, 68, 68, 72,
		 72, 74, 75, 77, 79, 80, 82, 82, 85, 85, 60, 57, 57, 55, 54, 54, 54, 53,
		 52, 52, 55, 55, 58, 58, 60, 62, 63, 65, 66, 69, 69, 72, 73, 75, 76, 77,
		 79, 80, 82, 82, 85, 85, 63, 60, 60, 58, 57, 57, 56, 55, 54, 55, 57, 57,
		 60, 60, 62, 63, 65, 67, 68, 71, 71, 74, 75, 77, 78, 80, 82, 83, 85, 85,
		 89, 89, 63, 60, 60, 58, 57, 57, 56, 55, 54, 55, 57, 57, 60, 60, 62, 63,
		 65, 67, 68, 71, 71, 74, 75, 77, 78, 80, 82, 83, 85, 85, 89, 89,
		 /* Size 4x8 */
		 31, 42, 47, 54, 33, 44, 45, 51, 40, 47, 46, 50, 47, 50, 54, 57, 45, 49,
		 59, 64, 48, 50, 61, 70, 51, 52, 63, 75, 55, 55, 66, 79,
		 /* Size 8x4 */
		 31, 33, 40, 47, 45, 48, 51, 55, 42, 44, 47, 50, 49, 50, 52, 55, 47, 45,
		 46, 54, 59, 61, 63, 66, 54, 51, 50, 57, 64, 70, 75, 79,
		 /* Size 8x16 */
		 32, 31, 37, 48, 49, 52, 56, 61, 31, 31, 38, 47, 47, 50, 53, 57, 30, 32,
		 40, 46, 45, 48, 51, 55, 33, 36, 43, 47, 46, 47, 50, 54, 37, 40, 47, 47,
		 45, 47, 49, 52, 42, 43, 47, 50, 49, 50, 53, 56, 47, 46, 48, 52, 53, 53,
		 55, 58, 48, 46, 47, 53, 55, 56, 58, 61, 48, 45, 46, 53, 57, 59, 61, 63,
		 49, 45, 46, 53, 58, 62, 64, 66, 50, 46, 46, 54, 59, 64, 66, 69, 52, 48,
		 47, 54, 61, 66, 70, 73, 54, 50, 49, 55, 62, 68, 72, 76, 57, 52, 50, 56,
		 64, 70, 75, 79, 60, 54, 52, 58, 65, 72, 77, 82, 63, 57, 55, 60, 67, 75,
		 80, 86,
		 /* Size 16x8 */
		 32, 31, 30, 33, 37, 42, 47, 48, 48, 49, 50, 52, 54, 57, 60, 63, 31, 31,
		 32, 36, 40, 43, 46, 46, 45, 45, 46, 48, 50, 52, 54, 57, 37, 38, 40, 43,
		 47, 47, 48, 47, 46, 46, 46, 47, 49, 50, 52, 55, 48, 47, 46, 47, 47, 50,
		 52, 53, 53, 53, 54, 54, 55, 56, 58, 60, 49, 47, 45, 46, 45, 49, 53, 55,
		 57, 58, 59, 61, 62, 64, 65, 67, 52, 50, 48, 47, 47, 50, 53, 56, 59, 62,
		 64, 66, 68, 70, 72, 75, 56, 53, 51, 50, 49, 53, 55, 58, 61, 64, 66, 70,
		 72, 75, 77, 80, 61, 57, 55, 54, 52, 56, 58, 61, 63, 66, 69, 73, 76, 79,
		 82, 86,

		 /* Size 16x32 */
		 32, 31, 31, 35, 37, 42, 48, 48, 49, 49, 52, 52, 56, 57, 61, 63, 31, 31,
		 31, 36, 38, 42, 47, 47, 47, 47, 50, 50, 54, 54, 58, 60, 31, 31, 31, 36,
		 38, 42, 47, 47, 47, 47, 50, 50, 53, 54, 57, 60, 30, 32, 32, 37, 39, 42,
		 46, 46, 46, 46, 48, 48, 52, 52, 56, 58, 30, 32, 32, 37, 40, 42, 46, 46,
		 45, 45, 48, 48, 51, 52, 55, 57, 32, 33, 34, 39, 41, 44, 46, 46, 45, 45,
		 48, 48, 51, 51, 54, 57, 33, 35, 36, 40, 43, 45, 47, 46, 46, 46, 47, 47,
		 50, 51, 54, 56, 34, 37, 37, 42, 44, 45, 47, 47, 45, 46, 47, 47, 50, 51,
		 53, 55, 37, 40, 40, 45, 47, 47, 47, 47, 45, 46, 47, 47, 49, 50, 52, 54,
		 37, 40, 40, 45, 47, 47, 48, 47, 46, 46, 47, 47, 49, 50, 53, 55, 42, 43,
		 43, 46, 47, 48, 50, 50, 49, 49, 50, 50, 53, 53, 56, 57, 42, 43, 43, 46,
		 47, 48, 50, 50, 49, 49, 50, 50, 53, 53, 56, 57, 47, 46, 46, 47, 48, 50,
		 52, 52, 53, 53, 53, 53, 55, 56, 58, 60, 49, 47, 46, 47, 48, 50, 53, 53,
		 53, 54, 54, 54, 56, 57, 59, 60, 48, 46, 46, 47, 47, 50, 53, 53, 55, 55,
		 56, 56, 58, 58, 61, 62, 48, 46, 46, 46, 47, 50, 53, 54, 56, 56, 57, 57,
		 59, 60, 62, 64, 48, 46, 45, 46, 46, 49, 53, 54, 57, 57, 59, 59, 61, 61,
		 63, 65, 49, 45, 45, 45, 46, 49, 53, 55, 58, 59, 61, 61, 63, 64, 66, 67,
		 49, 46, 45, 46, 46, 49, 53, 55, 58, 59, 62, 62, 64, 64, 66, 68, 50, 47,
		 46, 46, 46, 50, 54, 55, 59, 60, 64, 64, 66, 67, 69, 71, 50, 47, 46, 46,
		 46, 50, 54, 55, 59, 60, 64, 64, 66, 67, 69, 71, 52, 48, 48, 47, 47, 50,
		 54, 56, 61, 61, 66, 66, 69, 70, 72, 74, 52, 48, 48, 47, 47, 50, 54, 56,
		 61, 61, 66, 66, 70, 71, 73, 75, 53, 50, 49, 48, 48, 51, 55, 57, 62, 62,
		 68, 68, 71, 72, 75, 77, 54, 50, 50, 49, 49, 52, 55, 57, 62, 63, 68, 68,
		 72, 73, 76, 78, 55, 51, 51, 50, 49, 52, 56, 58, 63, 63, 69, 69, 74, 75,
		 78, 80, 57, 52, 52, 51, 50, 53, 56, 58, 64, 64, 70, 70, 75, 76, 79, 82,
		 58, 53, 53, 51, 51, 54, 57, 59, 64, 65, 71, 71, 76, 77, 80, 83, 60, 55,
		 54, 53, 52, 55, 58, 60, 65, 66, 72, 72, 77, 79, 82, 85, 60, 55, 55, 53,
		 53, 55, 59, 60, 65, 66, 73, 73, 78, 79, 83, 85, 63, 58, 57, 56, 55, 58,
		 60, 62, 67, 68, 75, 75, 80, 82, 86, 89, 63, 58, 57, 56, 55, 58, 60, 62,
		 67, 68, 75, 75, 80, 82, 86, 89,
		 /* Size 32x16 */
		 32, 31, 31, 30, 30, 32, 33, 34, 37, 37, 42, 42, 47, 49, 48, 48, 48, 49,
		 49, 50, 50, 52, 52, 53, 54, 55, 57, 58, 60, 60, 63, 63, 31, 31, 31, 32,
		 32, 33, 35, 37, 40, 40, 43, 43, 46, 47, 46, 46, 46, 45, 46, 47, 47, 48,
		 48, 50, 50, 51, 52, 53, 55, 55, 58, 58, 31, 31, 31, 32, 32, 34, 36, 37,
		 40, 40, 43, 43, 46, 46, 46, 46, 45, 45, 45, 46, 46, 48, 48, 49, 50, 51,
		 52, 53, 54, 55, 57, 57, 35, 36, 36, 37, 37, 39, 40, 42, 45, 45, 46, 46,
		 47, 47, 47, 46, 46, 45, 46, 46, 46, 47, 47, 48, 49, 50, 51, 51, 53, 53,
		 56, 56, 37, 38, 38, 39, 40, 41, 43, 44, 47, 47, 47, 47, 48, 48, 47, 47,
		 46, 46, 46, 46, 46, 47, 47, 48, 49, 49, 50, 51, 52, 53, 55, 55, 42, 42,
		 42, 42, 42, 44, 45, 45, 47, 47, 48, 48, 50, 50, 50, 50, 49, 49, 49, 50,
		 50, 50, 50, 51, 52, 52, 53, 54, 55, 55, 58, 58, 48, 47, 47, 46, 46, 46,
		 47, 47, 47, 48, 50, 50, 52, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 55,
		 55, 56, 56, 57, 58, 59, 60, 60, 48, 47, 47, 46, 46, 46, 46, 47, 47, 47,
		 50, 50, 52, 53, 53, 54, 54, 55, 55, 55, 55, 56, 56, 57, 57, 58, 58, 59,
		 60, 60, 62, 62, 49, 47, 47, 46, 45, 45, 46, 45, 45, 46, 49, 49, 53, 53,
		 55, 56, 57, 58, 58, 59, 59, 61, 61, 62, 62, 63, 64, 64, 65, 65, 67, 67,
		 49, 47, 47, 46, 45, 45, 46, 46, 46, 46, 49, 49, 53, 54, 55, 56, 57, 59,
		 59, 60, 60, 61, 61, 62, 63, 63, 64, 65, 66, 66, 68, 68, 52, 50, 50, 48,
		 48, 48, 47, 47, 47, 47, 50, 50, 53, 54, 56, 57, 59, 61, 62, 64, 64, 66,

		 66, 68, 68, 69, 70, 71, 72, 73, 75, 75, 52, 50, 50, 48, 48, 48, 47, 47,
		 47, 47, 50, 50, 53, 54, 56, 57, 59, 61, 62, 64, 64, 66, 66, 68, 68, 69,
		 70, 71, 72, 73, 75, 75, 56, 54, 53, 52, 51, 51, 50, 50, 49, 49, 53, 53,
		 55, 56, 58, 59, 61, 63, 64, 66, 66, 69, 70, 71, 72, 74, 75, 76, 77, 78,
		 80, 80, 57, 54, 54, 52, 52, 51, 51, 51, 50, 50, 53, 53, 56, 57, 58, 60,
		 61, 64, 64, 67, 67, 70, 71, 72, 73, 75, 76, 77, 79, 79, 82, 82, 61, 58,
		 57, 56, 55, 54, 54, 53, 52, 53, 56, 56, 58, 59, 61, 62, 63, 66, 66, 69,
		 69, 72, 73, 75, 76, 78, 79, 80, 82, 83, 86, 86, 63, 60, 60, 58, 57, 57,
		 56, 55, 54, 55, 57, 57, 60, 60, 62, 64, 65, 67, 68, 71, 71, 74, 75, 77,
		 78, 80, 82, 83, 85, 85, 89, 89,
		 /* Size 4x16 */
		 31, 42, 49, 57, 31, 42, 47, 54, 32, 42, 45, 52, 35, 45, 46, 51, 40, 47,
		 46, 50, 43, 48, 49, 53, 46, 50, 53, 56, 46, 50, 55, 58, 46, 49, 57, 61,
		 46, 49, 59, 64, 47, 50, 60, 67, 48, 50, 61, 71, 50, 52, 63, 73, 52, 53,
		 64, 76, 55, 55, 66, 79, 58, 58, 68, 82,
		 /* Size 16x4 */
		 31, 31, 32, 35, 40, 43, 46, 46, 46, 46, 47, 48, 50, 52, 55, 58, 42, 42,
		 42, 45, 47, 48, 50, 50, 49, 49, 50, 50, 52, 53, 55, 58, 49, 47, 45, 46,
		 46, 49, 53, 55, 57, 59, 60, 61, 63, 64, 66, 68, 57, 54, 52, 51, 50, 53,
		 56, 58, 61, 64, 67, 71, 73, 76, 79, 82,
		 /* Size 8x32 */
		 32, 31, 37, 48, 49, 52, 56, 61, 31, 31, 38, 47, 47, 50, 54, 58, 31, 31,
		 38, 47, 47, 50, 53, 57, 30, 32, 39, 46, 46, 48, 52, 56, 30, 32, 40, 46,
		 45, 48, 51, 55, 32, 34, 41, 46, 45, 48, 51, 54, 33, 36, 43, 47, 46, 47,
		 50, 54, 34, 37, 44, 47, 45, 47, 50, 53, 37, 40, 47, 47, 45, 47, 49, 52,
		 37, 40, 47, 48, 46, 47, 49, 53, 42, 43, 47, 50, 49, 50, 53, 56, 42, 43,
		 47, 50, 49, 50, 53, 56, 47, 46, 48, 52, 53, 53, 55, 58, 49, 46, 48, 53,
		 53, 54, 56, 59, 48, 46, 47, 53, 55, 56, 58, 61, 48, 46, 47, 53, 56, 57,
		 59, 62, 48, 45, 46, 53, 57, 59, 61, 63, 49, 45, 46, 53, 58, 61, 63, 66,
		 49, 45, 46, 53, 58, 62, 64, 66, 50, 46, 46, 54, 59, 64, 66, 69, 50, 46,
		 46, 54, 59, 64, 66, 69, 52, 48, 47, 54, 61, 66, 69, 72, 52, 48, 47, 54,
		 61, 66, 70, 73, 53, 49, 48, 55, 62, 68, 71, 75, 54, 50, 49, 55, 62, 68,
		 72, 76, 55, 51, 49, 56, 63, 69, 74, 78, 57, 52, 50, 56, 64, 70, 75, 79,
		 58, 53, 51, 57, 64, 71, 76, 80, 60, 54, 52, 58, 65, 72, 77, 82, 60, 55,
		 53, 59, 65, 73, 78, 83, 63, 57, 55, 60, 67, 75, 80, 86, 63, 57, 55, 60,
		 67, 75, 80, 86,
		 /* Size 32x8 */
		 32, 31, 31, 30, 30, 32, 33, 34, 37, 37, 42, 42, 47, 49, 48, 48, 48, 49,
		 49, 50, 50, 52, 52, 53, 54, 55, 57, 58, 60, 60, 63, 63, 31, 31, 31, 32,
		 32, 34, 36, 37, 40, 40, 43, 43, 46, 46, 46, 46, 45, 45, 45, 46, 46, 48,
		 48, 49, 50, 51, 52, 53, 54, 55, 57, 57, 37, 38, 38, 39, 40, 41, 43, 44,
		 47, 47, 47, 47, 48, 48, 47, 47, 46, 46, 46, 46, 46, 47, 47, 48, 49, 49,
		 50, 51, 52, 53, 55, 55, 48, 47, 47, 46, 46, 46, 47, 47, 47, 48, 50, 50,
		 52, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 56, 56, 57, 58, 59,
		 60, 60, 49, 47, 47, 46, 45, 45, 46, 45, 45, 46, 49, 49, 53, 53, 55, 56,
		 57, 58, 58, 59, 59, 61, 61, 62, 62, 63, 64, 64, 65, 65, 67, 67, 52, 50,
		 50, 48, 48, 48, 47, 47, 47, 47, 50, 50, 53, 54, 56, 57, 59, 61, 62, 64,
		 64, 66, 66, 68, 68, 69, 70, 71, 72, 73, 75, 75, 56, 54, 53, 52, 51, 51,
		 50, 50, 49, 49, 53, 53, 55, 56, 58, 59, 61, 63, 64, 66, 66, 69, 70, 71,
		 72, 74, 75, 76, 77, 78, 80, 80, 61, 58, 57, 56, 55, 54, 54, 53, 52, 53,

		 56, 56, 58, 59, 61, 62, 63, 66, 66, 69, 69, 72, 73, 75, 76, 78, 79, 80,
		 82, 83, 86, 86},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 33, 42, 55, 33, 38, 46, 57, 42, 46, 63, 75, 55, 57, 75, 92,
		 /* Size 8x8 */
		 31, 32, 32, 34, 38, 46, 52, 63, 32, 32, 32, 34, 37, 44, 49, 59, 32, 32,
		 35, 37, 40, 45, 49, 58, 34, 34, 37, 42, 47, 52, 56, 65, 38, 37, 40, 47,
		 54, 60, 65, 73, 46, 44, 45, 52, 60, 69, 75, 84, 52, 49, 49, 56, 65, 75,
		 82, 92, 63, 59, 58, 65, 73, 84, 92, 105,
		 /* Size 16x16 */
		 32, 31, 31, 31, 32, 32, 34, 36, 38, 41, 44, 48, 54, 58, 61, 65, 31, 32,
		 32, 32, 32, 32, 34, 35, 38, 40, 42, 46, 51, 55, 58, 62, 31, 32, 32, 32,
		 32, 32, 33, 34, 37, 38, 41, 44, 49, 53, 56, 59, 31, 32, 32, 33, 33, 33,
		 35, 36, 38, 40, 42, 45, 49, 53, 56, 59, 32, 32, 32, 33, 34, 34, 36, 37,
		 39, 40, 42, 45, 49, 53, 55, 59, 32, 32, 32, 33, 34, 35, 37, 38, 40, 41,
		 42, 46, 49, 52, 55, 58, 34, 34, 33, 35, 36, 37, 39, 42, 44, 46, 47, 51,
		 54, 57, 60, 63, 36, 35, 34, 36, 37, 38, 42, 48, 50, 52, 54, 57, 60, 63,
		 65, 68, 38, 38, 37, 38, 39, 40, 44, 50, 52, 54, 57, 60, 64, 67, 69, 72,
		 41, 40, 38, 40, 40, 41, 46, 52, 54, 57, 60, 63, 67, 70, 73, 75, 44, 42,
		 41, 42, 42, 42, 47, 54, 57, 60, 63, 67, 71, 74, 77, 79, 48, 46, 44, 45,
		 45, 46, 51, 57, 60, 63, 67, 71, 76, 79, 82, 85, 54, 51, 49, 49, 49, 49,
		 54, 60, 64, 67, 71, 76, 82, 86, 89, 92, 58, 55, 53, 53, 53, 52, 57, 63,
		 67, 70, 74, 79, 86, 90, 93, 97, 61, 58, 56, 56, 55, 55, 60, 65, 69, 73,
		 77, 82, 89, 93, 97, 101, 65, 62, 59, 59, 59, 58, 63, 68, 72, 75, 79, 85,
		 92, 97, 101, 105,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 33, 34, 34, 36, 36, 38, 39,
		 41, 44, 44, 47, 48, 50, 54, 54, 58, 59, 61, 65, 65, 70, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 38, 38, 40, 42, 42, 46,
		 47, 49, 52, 52, 56, 57, 59, 63, 63, 67, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 34, 34, 35, 35, 38, 38, 40, 42, 42, 45, 46, 48, 51, 51,
		 55, 56, 58, 62, 62, 67, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 34, 34, 35, 35, 37, 38, 39, 42, 42, 45, 45, 47, 50, 50, 54, 55, 57, 61,
		 61, 65, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34,
		 37, 37, 38, 41, 41, 44, 44, 46, 49, 49, 53, 54, 56, 59, 59, 64, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 37, 37, 38, 41,
		 41, 44, 44, 46, 49, 49, 53, 54, 56, 59, 59, 64, 31, 32, 32, 32, 32, 32,
		 33, 33, 33, 33, 33, 34, 35, 35, 36, 36, 38, 39, 40, 42, 42, 44, 45, 47,
		 49, 49, 53, 54, 56, 59, 59, 63, 31, 32, 32, 32, 32, 32, 33, 33, 33, 34,
		 34, 35, 35, 36, 36, 36, 38, 39, 40, 42, 42, 45, 45, 47, 50, 50, 53, 54,
		 56, 59, 59, 63, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 35, 36, 36,
		 37, 37, 39, 39, 40, 42, 42, 45, 45, 47, 49, 49, 53, 54, 55, 59, 59, 63,
		 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 40, 40,
		 41, 42, 42, 45, 46, 47, 49, 49, 52, 53, 55, 58, 58, 62, 32, 32, 32, 32,
		 32, 32, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 40, 40, 41, 42, 42, 45,
		 46, 47, 49, 49, 52, 53, 55, 58, 58, 62, 33, 33, 33, 33, 33, 33, 34, 35,
		 35, 36, 36, 38, 39, 40, 42, 42, 43, 44, 45, 46, 46, 49, 50, 51, 53, 53,

		 56, 57, 59, 62, 62, 66, 34, 34, 34, 34, 33, 33, 35, 35, 36, 37, 37, 39,
		 39, 41, 42, 42, 44, 45, 46, 47, 47, 50, 51, 52, 54, 54, 57, 58, 60, 63,
		 63, 67, 34, 34, 34, 34, 34, 34, 35, 36, 36, 37, 37, 40, 41, 42, 45, 45,
		 46, 47, 48, 50, 50, 52, 53, 54, 56, 56, 59, 60, 62, 65, 65, 69, 36, 35,
		 35, 35, 34, 34, 36, 36, 37, 38, 38, 42, 42, 45, 48, 48, 50, 50, 52, 54,
		 54, 56, 57, 58, 60, 60, 63, 64, 65, 68, 68, 72, 36, 35, 35, 35, 34, 34,
		 36, 36, 37, 38, 38, 42, 42, 45, 48, 48, 50, 50, 52, 54, 54, 56, 57, 58,
		 60, 60, 63, 64, 65, 68, 68, 72, 38, 38, 38, 37, 37, 37, 38, 38, 39, 40,
		 40, 43, 44, 46, 50, 50, 52, 53, 54, 57, 57, 59, 60, 61, 64, 64, 67, 68,
		 69, 72, 72, 76, 39, 38, 38, 38, 37, 37, 39, 39, 39, 40, 40, 44, 45, 47,
		 50, 50, 53, 54, 55, 58, 58, 60, 61, 62, 65, 65, 68, 69, 70, 73, 73, 77,
		 41, 40, 40, 39, 38, 38, 40, 40, 40, 41, 41, 45, 46, 48, 52, 52, 54, 55,
		 57, 60, 60, 62, 63, 65, 67, 67, 70, 71, 73, 75, 75, 79, 44, 42, 42, 42,
		 41, 41, 42, 42, 42, 42, 42, 46, 47, 50, 54, 54, 57, 58, 60, 63, 63, 66,
		 67, 68, 71, 71, 74, 75, 77, 79, 79, 83, 44, 42, 42, 42, 41, 41, 42, 42,
		 42, 42, 42, 46, 47, 50, 54, 54, 57, 58, 60, 63, 63, 66, 67, 68, 71, 71,
		 74, 75, 77, 79, 79, 83, 47, 46, 45, 45, 44, 44, 44, 45, 45, 45, 45, 49,
		 50, 52, 56, 56, 59, 60, 62, 66, 66, 69, 70, 72, 75, 75, 78, 79, 81, 84,
		 84, 88, 48, 47, 46, 45, 44, 44, 45, 45, 45, 46, 46, 50, 51, 53, 57, 57,
		 60, 61, 63, 67, 67, 70, 71, 73, 76, 76, 79, 80, 82, 85, 85, 89, 50, 49,
		 48, 47, 46, 46, 47, 47, 47, 47, 47, 51, 52, 54, 58, 58, 61, 62, 65, 68,
		 68, 72, 73, 75, 78, 78, 82, 83, 85, 88, 88, 92, 54, 52, 51, 50, 49, 49,
		 49, 50, 49, 49, 49, 53, 54, 56, 60, 60, 64, 65, 67, 71, 71, 75, 76, 78,
		 82, 82, 86, 87, 89, 92, 92, 96, 54, 52, 51, 50, 49, 49, 49, 50, 49, 49,
		 49, 53, 54, 56, 60, 60, 64, 65, 67, 71, 71, 75, 76, 78, 82, 82, 86, 87,
		 89, 92, 92, 96, 58, 56, 55, 54, 53, 53, 53, 53, 53, 52, 52, 56, 57, 59,
		 63, 63, 67, 68, 70, 74, 74, 78, 79, 82, 86, 86, 90, 91, 93, 97, 97, 101,
		 59, 57, 56, 55, 54, 54, 54, 54, 54, 53, 53, 57, 58, 60, 64, 64, 68, 69,
		 71, 75, 75, 79, 80, 83, 87, 87, 91, 92, 94, 98, 98, 102, 61, 59, 58, 57,
		 56, 56, 56, 56, 55, 55, 55, 59, 60, 62, 65, 65, 69, 70, 73, 77, 77, 81,
		 82, 85, 89, 89, 93, 94, 97, 101, 101, 105, 65, 63, 62, 61, 59, 59, 59,
		 59, 59, 58, 58, 62, 63, 65, 68, 68, 72, 73, 75, 79, 79, 84, 85, 88, 92,
		 92, 97, 98, 101, 105, 105, 109, 65, 63, 62, 61, 59, 59, 59, 59, 59, 58,
		 58, 62, 63, 65, 68, 68, 72, 73, 75, 79, 79, 84, 85, 88, 92, 92, 97, 98,
		 101, 105, 105, 109, 70, 67, 67, 65, 64, 64, 63, 63, 63, 62, 62, 66, 67,
		 69, 72, 72, 76, 77, 79, 83, 83, 88, 89, 92, 96, 96, 101, 102, 105, 109,
		 109, 114,
		 /* Size 4x8 */
		 32, 32, 42, 56, 32, 33, 41, 53, 32, 35, 42, 52, 34, 37, 50, 59, 38, 40,
		 58, 68, 44, 45, 66, 78, 50, 50, 71, 86, 61, 58, 79, 97,
		 /* Size 8x4 */
		 32, 32, 32, 34, 38, 44, 50, 61, 32, 33, 35, 37, 40, 45, 50, 58, 42, 41,
		 42, 50, 58, 66, 71, 79, 56, 53, 52, 59, 68, 78, 86, 97,
		 /* Size 8x16 */
		 32, 31, 32, 35, 39, 44, 53, 65, 31, 32, 32, 35, 38, 42, 51, 62, 31, 32,
		 33, 34, 37, 41, 49, 59, 31, 32, 34, 35, 38, 42, 49, 59, 32, 32, 34, 36,
		 39, 42, 49, 58, 32, 33, 35, 37, 40, 42, 49, 58, 34, 34, 37, 41, 44, 48,
		 54, 63, 36, 34, 38, 46, 50, 54, 60, 68, 38, 37, 40, 47, 52, 57, 64, 72,
		 41, 39, 41, 49, 54, 60, 67, 76, 44, 41, 43, 51, 57, 63, 71, 79, 48, 45,
		 46, 54, 60, 67, 76, 85, 53, 49, 50, 57, 64, 71, 82, 92, 57, 53, 53, 60,

		 67, 74, 86, 97, 61, 56, 56, 63, 69, 77, 89, 100, 65, 60, 58, 66, 72, 79,
		 92, 105,
		 /* Size 16x8 */
		 32, 31, 31, 31, 32, 32, 34, 36, 38, 41, 44, 48, 53, 57, 61, 65, 31, 32,
		 32, 32, 32, 33, 34, 34, 37, 39, 41, 45, 49, 53, 56, 60, 32, 32, 33, 34,
		 34, 35, 37, 38, 40, 41, 43, 46, 50, 53, 56, 58, 35, 35, 34, 35, 36, 37,
		 41, 46, 47, 49, 51, 54, 57, 60, 63, 66, 39, 38, 37, 38, 39, 40, 44, 50,
		 52, 54, 57, 60, 64, 67, 69, 72, 44, 42, 41, 42, 42, 42, 48, 54, 57, 60,
		 63, 67, 71, 74, 77, 79, 53, 51, 49, 49, 49, 49, 54, 60, 64, 67, 71, 76,
		 82, 86, 89, 92, 65, 62, 59, 59, 58, 58, 63, 68, 72, 76, 79, 85, 92, 97,
		 100, 105,
		 /* Size 16x32 */
		 32, 31, 31, 31, 32, 32, 35, 36, 39, 44, 44, 51, 53, 58, 65, 65, 31, 32,
		 32, 32, 32, 32, 35, 35, 38, 42, 42, 49, 52, 56, 63, 63, 31, 32, 32, 32,
		 32, 32, 35, 35, 38, 42, 42, 49, 51, 55, 62, 62, 31, 32, 32, 32, 32, 32,
		 34, 35, 37, 41, 41, 48, 50, 54, 61, 61, 31, 32, 32, 32, 33, 33, 34, 34,
		 37, 41, 41, 47, 49, 53, 59, 59, 31, 32, 32, 32, 33, 33, 34, 34, 37, 41,
		 41, 47, 49, 53, 59, 59, 31, 32, 32, 33, 34, 34, 35, 36, 38, 42, 42, 48,
		 49, 53, 59, 59, 32, 32, 32, 33, 34, 34, 36, 36, 38, 42, 42, 48, 50, 53,
		 59, 59, 32, 32, 32, 33, 34, 34, 36, 37, 39, 42, 42, 48, 49, 53, 58, 58,
		 32, 32, 33, 34, 35, 35, 37, 38, 40, 42, 42, 48, 49, 52, 58, 58, 32, 32,
		 33, 34, 35, 35, 37, 38, 40, 42, 42, 48, 49, 52, 58, 58, 33, 33, 33, 35,
		 36, 36, 40, 41, 43, 46, 46, 52, 53, 56, 62, 62, 34, 34, 34, 35, 37, 37,
		 41, 42, 44, 48, 48, 53, 54, 57, 63, 63, 34, 34, 34, 35, 37, 37, 43, 44,
		 46, 50, 50, 55, 56, 59, 65, 65, 36, 35, 34, 36, 38, 38, 46, 48, 50, 54,
		 54, 58, 60, 63, 68, 68, 36, 35, 34, 36, 38, 38, 46, 48, 50, 54, 54, 58,
		 60, 63, 68, 68, 38, 37, 37, 38, 40, 40, 47, 50, 52, 57, 57, 62, 64, 67,
		 72, 72, 39, 38, 37, 39, 40, 40, 48, 50, 53, 58, 58, 63, 65, 68, 73, 73,
		 41, 39, 39, 40, 41, 41, 49, 51, 54, 60, 60, 66, 67, 70, 76, 76, 44, 41,
		 41, 42, 43, 43, 51, 53, 57, 63, 63, 69, 71, 74, 79, 79, 44, 41, 41, 42,
		 43, 43, 51, 53, 57, 63, 63, 69, 71, 74, 79, 79, 47, 44, 44, 44, 45, 45,
		 53, 56, 59, 66, 66, 73, 75, 78, 84, 84, 48, 45, 45, 45, 46, 46, 54, 56,
		 60, 67, 67, 74, 76, 79, 85, 85, 50, 47, 46, 47, 47, 47, 55, 58, 61, 68,
		 68, 76, 78, 82, 88, 88, 53, 50, 49, 50, 50, 50, 57, 60, 64, 71, 71, 79,
		 82, 86, 92, 92, 53, 50, 49, 50, 50, 50, 57, 60, 64, 71, 71, 79, 82, 86,
		 92, 92, 57, 54, 53, 53, 53, 53, 60, 63, 67, 74, 74, 83, 86, 90, 97, 97,
		 58, 55, 54, 54, 54, 54, 61, 63, 68, 75, 75, 84, 87, 91, 98, 98, 61, 57,
		 56, 56, 56, 56, 63, 65, 69, 77, 77, 86, 89, 93, 100, 100, 65, 61, 60,
		 59, 58, 58, 66, 68, 72, 79, 79, 89, 92, 97, 105, 105, 65, 61, 60, 59,
		 58, 58, 66, 68, 72, 79, 79, 89, 92, 97, 105, 105, 70, 65, 64, 63, 62,
		 62, 70, 72, 76, 83, 83, 93, 96, 101, 109, 109,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 33, 34, 34, 36, 36, 38, 39,
		 41, 44, 44, 47, 48, 50, 53, 53, 57, 58, 61, 65, 65, 70, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 37, 38, 39, 41, 41, 44,
		 45, 47, 50, 50, 54, 55, 57, 61, 61, 65, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 34, 34, 34, 34, 37, 37, 39, 41, 41, 44, 45, 46, 49, 49,
		 53, 54, 56, 60, 60, 64, 31, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 35,
		 35, 35, 36, 36, 38, 39, 40, 42, 42, 44, 45, 47, 50, 50, 53, 54, 56, 59,
		 59, 63, 32, 32, 32, 32, 33, 33, 34, 34, 34, 35, 35, 36, 37, 37, 38, 38,

		 40, 40, 41, 43, 43, 45, 46, 47, 50, 50, 53, 54, 56, 58, 58, 62, 32, 32,
		 32, 32, 33, 33, 34, 34, 34, 35, 35, 36, 37, 37, 38, 38, 40, 40, 41, 43,
		 43, 45, 46, 47, 50, 50, 53, 54, 56, 58, 58, 62, 35, 35, 35, 34, 34, 34,
		 35, 36, 36, 37, 37, 40, 41, 43, 46, 46, 47, 48, 49, 51, 51, 53, 54, 55,
		 57, 57, 60, 61, 63, 66, 66, 70, 36, 35, 35, 35, 34, 34, 36, 36, 37, 38,
		 38, 41, 42, 44, 48, 48, 50, 50, 51, 53, 53, 56, 56, 58, 60, 60, 63, 63,
		 65, 68, 68, 72, 39, 38, 38, 37, 37, 37, 38, 38, 39, 40, 40, 43, 44, 46,
		 50, 50, 52, 53, 54, 57, 57, 59, 60, 61, 64, 64, 67, 68, 69, 72, 72, 76,
		 44, 42, 42, 41, 41, 41, 42, 42, 42, 42, 42, 46, 48, 50, 54, 54, 57, 58,
		 60, 63, 63, 66, 67, 68, 71, 71, 74, 75, 77, 79, 79, 83, 44, 42, 42, 41,
		 41, 41, 42, 42, 42, 42, 42, 46, 48, 50, 54, 54, 57, 58, 60, 63, 63, 66,
		 67, 68, 71, 71, 74, 75, 77, 79, 79, 83, 51, 49, 49, 48, 47, 47, 48, 48,
		 48, 48, 48, 52, 53, 55, 58, 58, 62, 63, 66, 69, 69, 73, 74, 76, 79, 79,
		 83, 84, 86, 89, 89, 93, 53, 52, 51, 50, 49, 49, 49, 50, 49, 49, 49, 53,
		 54, 56, 60, 60, 64, 65, 67, 71, 71, 75, 76, 78, 82, 82, 86, 87, 89, 92,
		 92, 96, 58, 56, 55, 54, 53, 53, 53, 53, 53, 52, 52, 56, 57, 59, 63, 63,
		 67, 68, 70, 74, 74, 78, 79, 82, 86, 86, 90, 91, 93, 97, 97, 101, 65, 63,
		 62, 61, 59, 59, 59, 59, 58, 58, 58, 62, 63, 65, 68, 68, 72, 73, 76, 79,
		 79, 84, 85, 88, 92, 92, 97, 98, 100, 105, 105, 109, 65, 63, 62, 61, 59,
		 59, 59, 59, 58, 58, 58, 62, 63, 65, 68, 68, 72, 73, 76, 79, 79, 84, 85,
		 88, 92, 92, 97, 98, 100, 105, 105, 109,
		 /* Size 4x16 */
		 31, 32, 44, 58, 32, 32, 42, 55, 32, 33, 41, 53, 32, 34, 42, 53, 32, 34,
		 42, 53, 32, 35, 42, 52, 34, 37, 48, 57, 35, 38, 54, 63, 37, 40, 57, 67,
		 39, 41, 60, 70, 41, 43, 63, 74, 45, 46, 67, 79, 50, 50, 71, 86, 54, 53,
		 74, 90, 57, 56, 77, 93, 61, 58, 79, 97,
		 /* Size 16x4 */
		 31, 32, 32, 32, 32, 32, 34, 35, 37, 39, 41, 45, 50, 54, 57, 61, 32, 32,
		 33, 34, 34, 35, 37, 38, 40, 41, 43, 46, 50, 53, 56, 58, 44, 42, 41, 42,
		 42, 42, 48, 54, 57, 60, 63, 67, 71, 74, 77, 79, 58, 55, 53, 53, 53, 52,
		 57, 63, 67, 70, 74, 79, 86, 90, 93, 97,
		 /* Size 8x32 */
		 32, 31, 32, 35, 39, 44, 53, 65, 31, 32, 32, 35, 38, 42, 52, 63, 31, 32,
		 32, 35, 38, 42, 51, 62, 31, 32, 32, 34, 37, 41, 50, 61, 31, 32, 33, 34,
		 37, 41, 49, 59, 31, 32, 33, 34, 37, 41, 49, 59, 31, 32, 34, 35, 38, 42,
		 49, 59, 32, 32, 34, 36, 38, 42, 50, 59, 32, 32, 34, 36, 39, 42, 49, 58,
		 32, 33, 35, 37, 40, 42, 49, 58, 32, 33, 35, 37, 40, 42, 49, 58, 33, 33,
		 36, 40, 43, 46, 53, 62, 34, 34, 37, 41, 44, 48, 54, 63, 34, 34, 37, 43,
		 46, 50, 56, 65, 36, 34, 38, 46, 50, 54, 60, 68, 36, 34, 38, 46, 50, 54,
		 60, 68, 38, 37, 40, 47, 52, 57, 64, 72, 39, 37, 40, 48, 53, 58, 65, 73,
		 41, 39, 41, 49, 54, 60, 67, 76, 44, 41, 43, 51, 57, 63, 71, 79, 44, 41,
		 43, 51, 57, 63, 71, 79, 47, 44, 45, 53, 59, 66, 75, 84, 48, 45, 46, 54,
		 60, 67, 76, 85, 50, 46, 47, 55, 61, 68, 78, 88, 53, 49, 50, 57, 64, 71,
		 82, 92, 53, 49, 50, 57, 64, 71, 82, 92, 57, 53, 53, 60, 67, 74, 86, 97,
		 58, 54, 54, 61, 68, 75, 87, 98, 61, 56, 56, 63, 69, 77, 89, 100, 65, 60,
		 58, 66, 72, 79, 92, 105, 65, 60, 58, 66, 72, 79, 92, 105, 70, 64, 62,
		 70, 76, 83, 96, 109,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 33, 34, 34, 36, 36, 38, 39,
		 41, 44, 44, 47, 48, 50, 53, 53, 57, 58, 61, 65, 65, 70, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 37, 37, 39, 41, 41, 44,
		 45, 46, 49, 49, 53, 54, 56, 60, 60, 64, 32, 32, 32, 32, 33, 33, 34, 34,
		 34, 35, 35, 36, 37, 37, 38, 38, 40, 40, 41, 43, 43, 45, 46, 47, 50, 50,
		 53, 54, 56, 58, 58, 62, 35, 35, 35, 34, 34, 34, 35, 36, 36, 37, 37, 40,
		 41, 43, 46, 46, 47, 48, 49, 51, 51, 53, 54, 55, 57, 57, 60, 61, 63, 66,
		 66, 70, 39, 38, 38, 37, 37, 37, 38, 38, 39, 40, 40, 43, 44, 46, 50, 50,
		 52, 53, 54, 57, 57, 59, 60, 61, 64, 64, 67, 68, 69, 72, 72, 76, 44, 42,
		 42, 41, 41, 41, 42, 42, 42, 42, 42, 46, 48, 50, 54, 54, 57, 58, 60, 63,
		 63, 66, 67, 68, 71, 71, 74, 75, 77, 79, 79, 83, 53, 52, 51, 50, 49, 49,
		 49, 50, 49, 49, 49, 53, 54, 56, 60, 60, 64, 65, 67, 71, 71, 75, 76, 78,
		 82, 82, 86, 87, 89, 92, 92, 96, 65, 63, 62, 61, 59, 59, 59, 59, 58, 58,
		 58, 62, 63, 65, 68, 68, 72, 73, 76, 79, 79, 84, 85, 88, 92, 92, 97, 98,
		 100, 105, 105, 109},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 41, 46, 51, 41, 48, 48, 51, 46, 48, 58, 62, 51, 51, 62, 71,
		 /* Size 8x8 */
		 31, 31, 38, 44, 47, 48, 50, 55, 31, 32, 40, 44, 45, 46, 47, 52, 38, 40,
		 47, 47, 46, 46, 47, 50, 44, 44, 47, 50, 51, 51, 52, 54, 47, 45, 46, 51,
		 54, 56, 57, 60, 48, 46, 46, 51, 56, 61, 63, 66, 50, 47, 47, 52, 57, 63,
		 66, 70, 55, 52, 50, 54, 60, 66, 70, 76,
		 /* Size 16x16 */
		 32, 31, 30, 33, 34, 36, 41, 49, 48, 49, 49, 50, 52, 54, 55, 57, 31, 31,
		 31, 34, 36, 38, 42, 47, 47, 47, 47, 48, 50, 51, 53, 54, 30, 31, 32, 34,
		 37, 40, 42, 46, 45, 45, 45, 46, 47, 49, 50, 52, 33, 34, 34, 37, 40, 42,
		 44, 47, 46, 46, 45, 46, 47, 49, 50, 51, 34, 36, 37, 40, 42, 45, 46, 47,
		 46, 46, 45, 46, 47, 48, 49, 50, 36, 38, 40, 42, 45, 47, 47, 48, 47, 46,
		 45, 46, 47, 48, 49, 50, 41, 42, 42, 44, 46, 47, 48, 50, 50, 49, 49, 50,
		 50, 51, 52, 53, 49, 47, 46, 47, 47, 48, 50, 53, 53, 53, 53, 54, 54, 55,
		 56, 56, 48, 47, 45, 46, 46, 47, 50, 53, 54, 54, 55, 56, 57, 58, 58, 59,
		 49, 47, 45, 46, 46, 46, 49, 53, 54, 55, 57, 58, 59, 60, 60, 61, 49, 47,
		 45, 45, 45, 45, 49, 53, 55, 57, 58, 60, 61, 62, 63, 63, 50, 48, 46, 46,
		 46, 46, 50, 54, 56, 58, 60, 61, 63, 65, 66, 67, 52, 50, 47, 47, 47, 47,
		 50, 54, 57, 59, 61, 63, 66, 68, 69, 70, 54, 51, 49, 49, 48, 48, 51, 55,
		 58, 60, 62, 65, 68, 70, 71, 73, 55, 53, 50, 50, 49, 49, 52, 56, 58, 60,
		 63, 66, 69, 71, 73, 74, 57, 54, 52, 51, 50, 50, 53, 56, 59, 61, 63, 67,
		 70, 73, 74, 76,
		 /* Size 32x32 */
		 32, 31, 31, 31, 30, 30, 33, 33, 34, 36, 36, 40, 41, 44, 49, 49, 48, 48,
		 49, 49, 49, 50, 50, 51, 52, 52, 54, 54, 55, 57, 57, 59, 31, 31, 31, 31,
		 31, 31, 33, 34, 36, 38, 38, 41, 42, 44, 48, 48, 47, 47, 47, 47, 47, 48,
		 49, 49, 50, 50, 52, 52, 53, 55, 55, 57, 31, 31, 31, 31, 31, 31, 34, 34,
		 36, 38, 38, 41, 42, 44, 47, 47, 47, 47, 47, 47, 47, 48, 48, 49, 50, 50,
		 51, 52, 53, 54, 54, 56, 31, 31, 31, 31, 31, 31, 34, 35, 36, 39, 39, 41,
		 42, 44, 47, 47, 46, 46, 46, 46, 46, 47, 47, 48, 49, 49, 50, 51, 52, 53,
		 53, 55, 30, 31, 31, 31, 32, 32, 34, 35, 37, 40, 40, 42, 42, 44, 46, 46,
		 45, 45, 45, 45, 45, 46, 46, 47, 47, 47, 49, 49, 50, 52, 52, 54, 30, 31,
		 31, 31, 32, 32, 34, 35, 37, 40, 40, 42, 42, 44, 46, 46, 45, 45, 45, 45,
		 45, 46, 46, 47, 47, 47, 49, 49, 50, 52, 52, 54, 33, 33, 34, 34, 34, 34,
		 37, 38, 40, 42, 42, 44, 44, 45, 47, 47, 46, 46, 46, 45, 45, 46, 46, 47,

		 47, 47, 49, 49, 50, 51, 51, 53, 33, 34, 34, 35, 35, 35, 38, 39, 40, 43,
		 43, 44, 45, 46, 47, 47, 46, 46, 46, 45, 45, 46, 46, 47, 47, 47, 49, 49,
		 50, 51, 51, 53, 34, 36, 36, 36, 37, 37, 40, 40, 42, 45, 45, 45, 46, 46,
		 47, 47, 46, 46, 46, 45, 45, 46, 46, 47, 47, 47, 48, 49, 49, 50, 50, 52,
		 36, 38, 38, 39, 40, 40, 42, 43, 45, 47, 47, 47, 47, 47, 48, 48, 47, 46,
		 46, 45, 45, 46, 46, 46, 47, 47, 48, 48, 49, 50, 50, 51, 36, 38, 38, 39,
		 40, 40, 42, 43, 45, 47, 47, 47, 47, 47, 48, 48, 47, 46, 46, 45, 45, 46,
		 46, 46, 47, 47, 48, 48, 49, 50, 50, 51, 40, 41, 41, 41, 42, 42, 44, 44,
		 45, 47, 47, 48, 48, 49, 50, 50, 49, 49, 49, 48, 48, 49, 49, 49, 49, 49,
		 51, 51, 51, 52, 52, 54, 41, 42, 42, 42, 42, 42, 44, 45, 46, 47, 47, 48,
		 48, 49, 50, 50, 50, 49, 49, 49, 49, 50, 50, 50, 50, 50, 51, 52, 52, 53,
		 53, 55, 44, 44, 44, 44, 44, 44, 45, 46, 46, 47, 47, 49, 49, 50, 51, 51,
		 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 53, 53, 54, 54, 54, 56, 49, 48,
		 47, 47, 46, 46, 47, 47, 47, 48, 48, 50, 50, 51, 53, 53, 53, 53, 53, 53,
		 53, 54, 54, 54, 54, 54, 55, 55, 56, 56, 56, 58, 49, 48, 47, 47, 46, 46,
		 47, 47, 47, 48, 48, 50, 50, 51, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54,
		 54, 54, 55, 55, 56, 56, 56, 58, 48, 47, 47, 46, 45, 45, 46, 46, 46, 47,
		 47, 49, 50, 51, 53, 53, 54, 54, 54, 55, 55, 56, 56, 56, 57, 57, 58, 58,
		 58, 59, 59, 60, 48, 47, 47, 46, 45, 45, 46, 46, 46, 46, 46, 49, 49, 51,
		 53, 53, 54, 54, 55, 55, 55, 56, 56, 57, 57, 57, 58, 58, 59, 60, 60, 61,
		 49, 47, 47, 46, 45, 45, 46, 46, 46, 46, 46, 49, 49, 51, 53, 53, 54, 55,
		 55, 57, 57, 57, 58, 58, 59, 59, 60, 60, 60, 61, 61, 63, 49, 47, 47, 46,
		 45, 45, 45, 45, 45, 45, 45, 48, 49, 51, 53, 53, 55, 55, 57, 58, 58, 59,
		 60, 60, 61, 61, 62, 62, 63, 63, 63, 65, 49, 47, 47, 46, 45, 45, 45, 45,
		 45, 45, 45, 48, 49, 51, 53, 53, 55, 55, 57, 58, 58, 59, 60, 60, 61, 61,
		 62, 62, 63, 63, 63, 65, 50, 48, 48, 47, 46, 46, 46, 46, 46, 46, 46, 49,
		 50, 51, 54, 54, 56, 56, 57, 59, 59, 61, 61, 62, 63, 63, 64, 64, 65, 66,
		 66, 67, 50, 49, 48, 47, 46, 46, 46, 46, 46, 46, 46, 49, 50, 51, 54, 54,
		 56, 56, 58, 60, 60, 61, 61, 62, 63, 63, 65, 65, 66, 67, 67, 68, 51, 49,
		 49, 48, 47, 47, 47, 47, 47, 46, 46, 49, 50, 51, 54, 54, 56, 57, 58, 60,
		 60, 62, 62, 63, 65, 65, 66, 66, 67, 68, 68, 70, 52, 50, 50, 49, 47, 47,
		 47, 47, 47, 47, 47, 49, 50, 52, 54, 54, 57, 57, 59, 61, 61, 63, 63, 65,
		 66, 66, 68, 68, 69, 70, 70, 72, 52, 50, 50, 49, 47, 47, 47, 47, 47, 47,
		 47, 49, 50, 52, 54, 54, 57, 57, 59, 61, 61, 63, 63, 65, 66, 66, 68, 68,
		 69, 70, 70, 72, 54, 52, 51, 50, 49, 49, 49, 49, 48, 48, 48, 51, 51, 53,
		 55, 55, 58, 58, 60, 62, 62, 64, 65, 66, 68, 68, 70, 70, 71, 73, 73, 74,
		 54, 52, 52, 51, 49, 49, 49, 49, 49, 48, 48, 51, 52, 53, 55, 55, 58, 58,
		 60, 62, 62, 64, 65, 66, 68, 68, 70, 71, 72, 73, 73, 75, 55, 53, 53, 52,
		 50, 50, 50, 50, 49, 49, 49, 51, 52, 54, 56, 56, 58, 59, 60, 63, 63, 65,
		 66, 67, 69, 69, 71, 72, 73, 74, 74, 76, 57, 55, 54, 53, 52, 52, 51, 51,
		 50, 50, 50, 52, 53, 54, 56, 56, 59, 60, 61, 63, 63, 66, 67, 68, 70, 70,
		 73, 73, 74, 76, 76, 78, 57, 55, 54, 53, 52, 52, 51, 51, 50, 50, 50, 52,
		 53, 54, 56, 56, 59, 60, 61, 63, 63, 66, 67, 68, 70, 70, 73, 73, 74, 76,
		 76, 78, 59, 57, 56, 55, 54, 54, 53, 53, 52, 51, 51, 54, 55, 56, 58, 58,
		 60, 61, 63, 65, 65, 67, 68, 70, 72, 72, 74, 75, 76, 78, 78, 80,
		 /* Size 4x8 */
		 31, 38, 47, 52, 32, 40, 45, 49, 39, 47, 45, 48, 44, 47, 51, 53, 46, 47,
		 56, 58, 47, 46, 59, 64, 48, 47, 61, 68, 53, 50, 64, 73,
		 /* Size 8x4 */
		 31, 32, 39, 44, 46, 47, 48, 53, 38, 40, 47, 47, 47, 46, 47, 50, 47, 45,

		 45, 51, 56, 59, 61, 64, 52, 49, 48, 53, 58, 64, 68, 73,
		 /* Size 8x16 */
		 32, 31, 37, 45, 48, 49, 52, 57, 31, 31, 38, 45, 47, 47, 50, 54, 30, 32,
		 40, 44, 45, 45, 48, 52, 33, 35, 42, 46, 46, 45, 47, 51, 35, 37, 44, 46,
		 46, 45, 47, 51, 37, 40, 47, 47, 47, 45, 47, 50, 42, 43, 47, 49, 50, 49,
		 50, 53, 49, 46, 48, 52, 53, 53, 54, 57, 48, 46, 47, 51, 54, 55, 57, 59,
		 48, 45, 46, 51, 54, 57, 59, 61, 49, 45, 46, 51, 55, 58, 61, 64, 50, 46,
		 46, 52, 56, 59, 64, 67, 52, 48, 47, 53, 57, 61, 66, 71, 54, 49, 48, 54,
		 58, 62, 68, 73, 55, 51, 49, 54, 58, 63, 69, 74, 57, 52, 50, 55, 59, 64,
		 70, 76,
		 /* Size 16x8 */
		 32, 31, 30, 33, 35, 37, 42, 49, 48, 48, 49, 50, 52, 54, 55, 57, 31, 31,
		 32, 35, 37, 40, 43, 46, 46, 45, 45, 46, 48, 49, 51, 52, 37, 38, 40, 42,
		 44, 47, 47, 48, 47, 46, 46, 46, 47, 48, 49, 50, 45, 45, 44, 46, 46, 47,
		 49, 52, 51, 51, 51, 52, 53, 54, 54, 55, 48, 47, 45, 46, 46, 47, 50, 53,
		 54, 54, 55, 56, 57, 58, 58, 59, 49, 47, 45, 45, 45, 45, 49, 53, 55, 57,
		 58, 59, 61, 62, 63, 64, 52, 50, 48, 47, 47, 47, 50, 54, 57, 59, 61, 64,
		 66, 68, 69, 70, 57, 54, 52, 51, 51, 50, 53, 57, 59, 61, 64, 67, 71, 73,
		 74, 76,
		 /* Size 16x32 */
		 32, 31, 31, 33, 37, 37, 45, 48, 48, 49, 49, 51, 52, 54, 57, 57, 31, 31,
		 31, 34, 38, 38, 45, 47, 47, 47, 47, 50, 50, 52, 55, 55, 31, 31, 31, 34,
		 38, 38, 45, 47, 47, 47, 47, 49, 50, 51, 54, 54, 31, 31, 32, 34, 39, 39,
		 45, 46, 46, 46, 46, 48, 49, 51, 53, 53, 30, 32, 32, 35, 40, 40, 44, 46,
		 45, 45, 45, 47, 48, 49, 52, 52, 30, 32, 32, 35, 40, 40, 44, 46, 45, 45,
		 45, 47, 48, 49, 52, 52, 33, 34, 35, 37, 42, 42, 46, 47, 46, 45, 45, 47,
		 47, 49, 51, 51, 33, 35, 36, 38, 43, 43, 46, 47, 46, 46, 46, 47, 47, 49,
		 51, 51, 35, 37, 37, 40, 44, 44, 46, 47, 46, 45, 45, 47, 47, 48, 51, 51,
		 37, 39, 40, 43, 47, 47, 47, 47, 47, 45, 45, 46, 47, 48, 50, 50, 37, 39,
		 40, 43, 47, 47, 47, 47, 47, 45, 45, 46, 47, 48, 50, 50, 41, 42, 42, 44,
		 47, 47, 49, 49, 49, 48, 48, 49, 50, 51, 52, 52, 42, 42, 43, 44, 47, 47,
		 49, 50, 50, 49, 49, 50, 50, 51, 53, 53, 44, 44, 44, 45, 47, 47, 50, 51,
		 51, 51, 51, 52, 52, 53, 54, 54, 49, 47, 46, 47, 48, 48, 52, 53, 53, 53,
		 53, 54, 54, 55, 57, 57, 49, 47, 46, 47, 48, 48, 52, 53, 53, 53, 53, 54,
		 54, 55, 57, 57, 48, 46, 46, 46, 47, 47, 51, 53, 54, 55, 55, 56, 57, 58,
		 59, 59, 48, 46, 46, 46, 47, 47, 51, 53, 54, 56, 56, 57, 57, 58, 60, 60,
		 48, 46, 45, 46, 46, 46, 51, 53, 54, 57, 57, 58, 59, 60, 61, 61, 49, 46,
		 45, 45, 46, 46, 51, 53, 55, 58, 58, 61, 61, 62, 64, 64, 49, 46, 45, 45,
		 46, 46, 51, 53, 55, 58, 58, 61, 61, 62, 64, 64, 50, 47, 46, 46, 46, 46,
		 52, 54, 56, 59, 59, 62, 63, 64, 66, 66, 50, 47, 46, 46, 46, 46, 52, 54,
		 56, 59, 59, 63, 64, 65, 67, 67, 51, 48, 47, 47, 47, 47, 52, 54, 56, 60,
		 60, 64, 65, 66, 68, 68, 52, 48, 48, 47, 47, 47, 53, 54, 57, 61, 61, 65,
		 66, 68, 71, 71, 52, 48, 48, 47, 47, 47, 53, 54, 57, 61, 61, 65, 66, 68,
		 71, 71, 54, 50, 49, 49, 48, 48, 54, 55, 58, 62, 62, 67, 68, 70, 73, 73,
		 54, 51, 50, 49, 49, 49, 54, 55, 58, 62, 62, 67, 68, 70, 73, 73, 55, 51,
		 51, 50, 49, 49, 54, 56, 58, 63, 63, 68, 69, 71, 74, 74, 57, 53, 52, 51,
		 50, 50, 55, 56, 59, 64, 64, 69, 70, 73, 76, 76, 57, 53, 52, 51, 50, 50,
		 55, 56, 59, 64, 64, 69, 70, 73, 76, 76, 59, 55, 54, 53, 52, 52, 57, 58,
		 61, 65, 65, 70, 72, 74, 78, 78,
		 /* Size 32x16 */

		 32, 31, 31, 31, 30, 30, 33, 33, 35, 37, 37, 41, 42, 44, 49, 49, 48, 48,
		 48, 49, 49, 50, 50, 51, 52, 52, 54, 54, 55, 57, 57, 59, 31, 31, 31, 31,
		 32, 32, 34, 35, 37, 39, 39, 42, 42, 44, 47, 47, 46, 46, 46, 46, 46, 47,
		 47, 48, 48, 48, 50, 51, 51, 53, 53, 55, 31, 31, 31, 32, 32, 32, 35, 36,
		 37, 40, 40, 42, 43, 44, 46, 46, 46, 46, 45, 45, 45, 46, 46, 47, 48, 48,
		 49, 50, 51, 52, 52, 54, 33, 34, 34, 34, 35, 35, 37, 38, 40, 43, 43, 44,
		 44, 45, 47, 47, 46, 46, 46, 45, 45, 46, 46, 47, 47, 47, 49, 49, 50, 51,
		 51, 53, 37, 38, 38, 39, 40, 40, 42, 43, 44, 47, 47, 47, 47, 47, 48, 48,
		 47, 47, 46, 46, 46, 46, 46, 47, 47, 47, 48, 49, 49, 50, 50, 52, 37, 38,
		 38, 39, 40, 40, 42, 43, 44, 47, 47, 47, 47, 47, 48, 48, 47, 47, 46, 46,
		 46, 46, 46, 47, 47, 47, 48, 49, 49, 50, 50, 52, 45, 45, 45, 45, 44, 44,
		 46, 46, 46, 47, 47, 49, 49, 50, 52, 52, 51, 51, 51, 51, 51, 52, 52, 52,
		 53, 53, 54, 54, 54, 55, 55, 57, 48, 47, 47, 46, 46, 46, 47, 47, 47, 47,
		 47, 49, 50, 51, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 55, 55,
		 56, 56, 56, 58, 48, 47, 47, 46, 45, 45, 46, 46, 46, 47, 47, 49, 50, 51,
		 53, 53, 54, 54, 54, 55, 55, 56, 56, 56, 57, 57, 58, 58, 58, 59, 59, 61,
		 49, 47, 47, 46, 45, 45, 45, 46, 45, 45, 45, 48, 49, 51, 53, 53, 55, 56,
		 57, 58, 58, 59, 59, 60, 61, 61, 62, 62, 63, 64, 64, 65, 49, 47, 47, 46,
		 45, 45, 45, 46, 45, 45, 45, 48, 49, 51, 53, 53, 55, 56, 57, 58, 58, 59,
		 59, 60, 61, 61, 62, 62, 63, 64, 64, 65, 51, 50, 49, 48, 47, 47, 47, 47,
		 47, 46, 46, 49, 50, 52, 54, 54, 56, 57, 58, 61, 61, 62, 63, 64, 65, 65,
		 67, 67, 68, 69, 69, 70, 52, 50, 50, 49, 48, 48, 47, 47, 47, 47, 47, 50,
		 50, 52, 54, 54, 57, 57, 59, 61, 61, 63, 64, 65, 66, 66, 68, 68, 69, 70,
		 70, 72, 54, 52, 51, 51, 49, 49, 49, 49, 48, 48, 48, 51, 51, 53, 55, 55,
		 58, 58, 60, 62, 62, 64, 65, 66, 68, 68, 70, 70, 71, 73, 73, 74, 57, 55,
		 54, 53, 52, 52, 51, 51, 51, 50, 50, 52, 53, 54, 57, 57, 59, 60, 61, 64,
		 64, 66, 67, 68, 71, 71, 73, 73, 74, 76, 76, 78, 57, 55, 54, 53, 52, 52,
		 51, 51, 51, 50, 50, 52, 53, 54, 57, 57, 59, 60, 61, 64, 64, 66, 67, 68,
		 71, 71, 73, 73, 74, 76, 76, 78,
		 /* Size 4x16 */
		 31, 37, 49, 54, 31, 38, 47, 51, 32, 40, 45, 49, 34, 42, 45, 49, 37, 44,
		 45, 48, 39, 47, 45, 48, 42, 47, 49, 51, 47, 48, 53, 55, 46, 47, 55, 58,
		 46, 46, 57, 60, 46, 46, 58, 62, 47, 46, 59, 65, 48, 47, 61, 68, 50, 48,
		 62, 70, 51, 49, 63, 71, 53, 50, 64, 73,
		 /* Size 16x4 */
		 31, 31, 32, 34, 37, 39, 42, 47, 46, 46, 46, 47, 48, 50, 51, 53, 37, 38,
		 40, 42, 44, 47, 47, 48, 47, 46, 46, 46, 47, 48, 49, 50, 49, 47, 45, 45,
		 45, 45, 49, 53, 55, 57, 58, 59, 61, 62, 63, 64, 54, 51, 49, 49, 48, 48,
		 51, 55, 58, 60, 62, 65, 68, 70, 71, 73,
		 /* Size 8x32 */
		 32, 31, 37, 45, 48, 49, 52, 57, 31, 31, 38, 45, 47, 47, 50, 55, 31, 31,
		 38, 45, 47, 47, 50, 54, 31, 32, 39, 45, 46, 46, 49, 53, 30, 32, 40, 44,
		 45, 45, 48, 52, 30, 32, 40, 44, 45, 45, 48, 52, 33, 35, 42, 46, 46, 45,
		 47, 51, 33, 36, 43, 46, 46, 46, 47, 51, 35, 37, 44, 46, 46, 45, 47, 51,
		 37, 40, 47, 47, 47, 45, 47, 50, 37, 40, 47, 47, 47, 45, 47, 50, 41, 42,
		 47, 49, 49, 48, 50, 52, 42, 43, 47, 49, 50, 49, 50, 53, 44, 44, 47, 50,
		 51, 51, 52, 54, 49, 46, 48, 52, 53, 53, 54, 57, 49, 46, 48, 52, 53, 53,
		 54, 57, 48, 46, 47, 51, 54, 55, 57, 59, 48, 46, 47, 51, 54, 56, 57, 60,
		 48, 45, 46, 51, 54, 57, 59, 61, 49, 45, 46, 51, 55, 58, 61, 64, 49, 45,
		 46, 51, 55, 58, 61, 64, 50, 46, 46, 52, 56, 59, 63, 66, 50, 46, 46, 52,

		 56, 59, 64, 67, 51, 47, 47, 52, 56, 60, 65, 68, 52, 48, 47, 53, 57, 61,
		 66, 71, 52, 48, 47, 53, 57, 61, 66, 71, 54, 49, 48, 54, 58, 62, 68, 73,
		 54, 50, 49, 54, 58, 62, 68, 73, 55, 51, 49, 54, 58, 63, 69, 74, 57, 52,
		 50, 55, 59, 64, 70, 76, 57, 52, 50, 55, 59, 64, 70, 76, 59, 54, 52, 57,
		 61, 65, 72, 78,
		 /* Size 32x8 */
		 32, 31, 31, 31, 30, 30, 33, 33, 35, 37, 37, 41, 42, 44, 49, 49, 48, 48,
		 48, 49, 49, 50, 50, 51, 52, 52, 54, 54, 55, 57, 57, 59, 31, 31, 31, 32,
		 32, 32, 35, 36, 37, 40, 40, 42, 43, 44, 46, 46, 46, 46, 45, 45, 45, 46,
		 46, 47, 48, 48, 49, 50, 51, 52, 52, 54, 37, 38, 38, 39, 40, 40, 42, 43,
		 44, 47, 47, 47, 47, 47, 48, 48, 47, 47, 46, 46, 46, 46, 46, 47, 47, 47,
		 48, 49, 49, 50, 50, 52, 45, 45, 45, 45, 44, 44, 46, 46, 46, 47, 47, 49,
		 49, 50, 52, 52, 51, 51, 51, 51, 51, 52, 52, 52, 53, 53, 54, 54, 54, 55,
		 55, 57, 48, 47, 47, 46, 45, 45, 46, 46, 46, 47, 47, 49, 50, 51, 53, 53,
		 54, 54, 54, 55, 55, 56, 56, 56, 57, 57, 58, 58, 58, 59, 59, 61, 49, 47,
		 47, 46, 45, 45, 45, 46, 45, 45, 45, 48, 49, 51, 53, 53, 55, 56, 57, 58,
		 58, 59, 59, 60, 61, 61, 62, 62, 63, 64, 64, 65, 52, 50, 50, 49, 48, 48,
		 47, 47, 47, 47, 47, 50, 50, 52, 54, 54, 57, 57, 59, 61, 61, 63, 64, 65,
		 66, 66, 68, 68, 69, 70, 70, 72, 57, 55, 54, 53, 52, 52, 51, 51, 51, 50,
		 50, 52, 53, 54, 57, 57, 59, 60, 61, 64, 64, 66, 67, 68, 71, 71, 73, 73,
		 74, 76, 76, 78},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 32, 38, 51, 32, 35, 40, 49, 38, 40, 54, 64, 51, 49, 64, 81,
		 /* Size 8x8 */
		 31, 32, 32, 34, 35, 41, 47, 53, 32, 32, 32, 33, 34, 40, 44, 50, 32, 32,
		 34, 35, 37, 41, 45, 51, 34, 33, 35, 39, 42, 47, 51, 55, 35, 34, 37, 42,
		 48, 53, 57, 61, 41, 40, 41, 47, 53, 60, 65, 70, 47, 44, 45, 51, 57, 65,
		 71, 77, 53, 50, 51, 55, 61, 70, 77, 85,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 32, 32, 34, 36, 38, 39, 44, 47, 49, 54, 59, 31, 32,
		 32, 32, 32, 32, 33, 34, 35, 37, 38, 42, 45, 47, 51, 56, 31, 32, 32, 32,
		 32, 32, 33, 33, 34, 36, 37, 41, 44, 46, 50, 54, 31, 32, 32, 32, 32, 33,
		 33, 34, 35, 36, 38, 41, 44, 45, 49, 54, 31, 32, 32, 32, 33, 34, 34, 35,
		 36, 38, 39, 42, 45, 46, 50, 54, 32, 32, 32, 33, 34, 35, 36, 37, 38, 39,
		 40, 42, 45, 46, 49, 53, 32, 33, 33, 33, 34, 36, 36, 38, 40, 41, 42, 44,
		 47, 48, 51, 55, 34, 34, 33, 34, 35, 37, 38, 39, 42, 44, 45, 47, 50, 51,
		 54, 58, 36, 35, 34, 35, 36, 38, 40, 42, 48, 50, 50, 54, 56, 57, 60, 64,
		 38, 37, 36, 36, 38, 39, 41, 44, 50, 51, 52, 56, 58, 60, 63, 67, 39, 38,
		 37, 38, 39, 40, 42, 45, 50, 52, 54, 58, 60, 62, 65, 69, 44, 42, 41, 41,
		 42, 42, 44, 47, 54, 56, 58, 63, 66, 68, 71, 75, 47, 45, 44, 44, 45, 45,
		 47, 50, 56, 58, 60, 66, 69, 71, 75, 79, 49, 47, 46, 45, 46, 46, 48, 51,
		 57, 60, 62, 68, 71, 73, 77, 81, 54, 51, 50, 49, 50, 49, 51, 54, 60, 63,
		 65, 71, 75, 77, 82, 87, 59, 56, 54, 54, 54, 53, 55, 58, 64, 67, 69, 75,
		 79, 81, 87, 92,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 35, 36, 36,
		 38, 39, 39, 42, 44, 44, 47, 48, 49, 53, 54, 55, 59, 59, 31, 31, 31, 31,

		 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 35, 35, 37, 39, 39, 41,
		 43, 43, 46, 47, 48, 51, 52, 53, 57, 57, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 34, 34, 34, 35, 35, 37, 38, 38, 41, 42, 43, 45, 46,
		 47, 51, 51, 53, 56, 56, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 34, 34, 34, 35, 35, 37, 38, 38, 41, 42, 42, 45, 46, 47, 51, 51, 52,
		 56, 56, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34,
		 34, 34, 36, 37, 37, 40, 41, 41, 44, 45, 46, 49, 50, 51, 54, 54, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 36, 37,
		 37, 40, 41, 41, 44, 44, 45, 49, 49, 50, 54, 54, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35, 35, 36, 38, 38, 40, 41, 41,
		 44, 45, 45, 49, 49, 50, 54, 54, 31, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 34, 34, 34, 35, 35, 35, 36, 36, 38, 39, 39, 41, 42, 42, 44, 45, 46, 49,
		 50, 51, 54, 54, 31, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35,
		 35, 36, 36, 36, 38, 39, 39, 41, 42, 42, 45, 45, 46, 49, 50, 51, 54, 54,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 37, 37,
		 38, 39, 39, 41, 42, 42, 45, 45, 46, 49, 49, 51, 54, 54, 32, 32, 32, 32,
		 32, 32, 33, 34, 34, 34, 35, 35, 36, 37, 37, 37, 38, 38, 39, 40, 40, 42,
		 42, 43, 45, 46, 46, 49, 49, 50, 53, 53, 32, 32, 32, 32, 32, 32, 33, 34,
		 34, 34, 35, 35, 36, 37, 37, 37, 38, 38, 39, 40, 40, 42, 42, 43, 45, 46,
		 46, 49, 49, 50, 53, 53, 32, 33, 33, 33, 33, 33, 33, 34, 34, 35, 36, 36,
		 36, 38, 38, 39, 40, 40, 41, 42, 42, 44, 44, 45, 47, 47, 48, 51, 51, 52,
		 55, 55, 34, 34, 34, 34, 33, 33, 34, 35, 35, 35, 37, 37, 38, 39, 39, 41,
		 42, 42, 44, 45, 45, 47, 47, 48, 50, 51, 51, 54, 54, 55, 58, 58, 34, 34,
		 34, 34, 33, 33, 34, 35, 35, 35, 37, 37, 38, 39, 39, 41, 42, 42, 44, 45,
		 45, 47, 47, 48, 50, 51, 51, 54, 54, 55, 58, 58, 35, 34, 34, 34, 34, 34,
		 34, 35, 36, 36, 37, 37, 39, 41, 41, 43, 45, 45, 47, 47, 47, 49, 50, 51,
		 53, 53, 54, 57, 57, 58, 61, 61, 36, 35, 35, 35, 34, 34, 35, 36, 36, 37,
		 38, 38, 40, 42, 42, 45, 48, 48, 50, 50, 50, 53, 54, 54, 56, 57, 57, 59,
		 60, 61, 64, 64, 36, 35, 35, 35, 34, 34, 35, 36, 36, 37, 38, 38, 40, 42,
		 42, 45, 48, 48, 50, 50, 50, 53, 54, 54, 56, 57, 57, 59, 60, 61, 64, 64,
		 38, 37, 37, 37, 36, 36, 36, 38, 38, 38, 39, 39, 41, 44, 44, 47, 50, 50,
		 51, 52, 52, 55, 56, 56, 58, 59, 60, 62, 63, 64, 67, 67, 39, 39, 38, 38,
		 37, 37, 38, 39, 39, 39, 40, 40, 42, 45, 45, 47, 50, 50, 52, 54, 54, 56,
		 58, 58, 60, 61, 62, 64, 65, 66, 69, 69, 39, 39, 38, 38, 37, 37, 38, 39,
		 39, 39, 40, 40, 42, 45, 45, 47, 50, 50, 52, 54, 54, 56, 58, 58, 60, 61,
		 62, 64, 65, 66, 69, 69, 42, 41, 41, 41, 40, 40, 40, 41, 41, 41, 42, 42,
		 44, 47, 47, 49, 53, 53, 55, 56, 56, 60, 61, 62, 64, 65, 66, 69, 69, 70,
		 73, 73, 44, 43, 42, 42, 41, 41, 41, 42, 42, 42, 42, 42, 44, 47, 47, 50,
		 54, 54, 56, 58, 58, 61, 63, 64, 66, 67, 68, 71, 71, 72, 75, 75, 44, 43,
		 43, 42, 41, 41, 41, 42, 42, 42, 43, 43, 45, 48, 48, 51, 54, 54, 56, 58,
		 58, 62, 64, 64, 66, 67, 68, 71, 72, 73, 76, 76, 47, 46, 45, 45, 44, 44,
		 44, 44, 45, 45, 45, 45, 47, 50, 50, 53, 56, 56, 58, 60, 60, 64, 66, 66,
		 69, 70, 71, 74, 75, 76, 79, 79, 48, 47, 46, 46, 45, 44, 45, 45, 45, 45,
		 46, 46, 47, 51, 51, 53, 57, 57, 59, 61, 61, 65, 67, 67, 70, 71, 72, 75,
		 76, 77, 80, 80, 49, 48, 47, 47, 46, 45, 45, 46, 46, 46, 46, 46, 48, 51,
		 51, 54, 57, 57, 60, 62, 62, 66, 68, 68, 71, 72, 73, 77, 77, 78, 81, 81,
		 53, 51, 51, 51, 49, 49, 49, 49, 49, 49, 49, 49, 51, 54, 54, 57, 59, 59,
		 62, 64, 64, 69, 71, 71, 74, 75, 77, 81, 81, 83, 86, 86, 54, 52, 51, 51,
		 50, 49, 49, 50, 50, 49, 49, 49, 51, 54, 54, 57, 60, 60, 63, 65, 65, 69,
		 71, 72, 75, 76, 77, 81, 82, 83, 87, 87, 55, 53, 53, 52, 51, 50, 50, 51,

		 51, 51, 50, 50, 52, 55, 55, 58, 61, 61, 64, 66, 66, 70, 72, 73, 76, 77,
		 78, 83, 83, 85, 88, 88, 59, 57, 56, 56, 54, 54, 54, 54, 54, 54, 53, 53,
		 55, 58, 58, 61, 64, 64, 67, 69, 69, 73, 75, 76, 79, 80, 81, 86, 87, 88,
		 92, 92, 59, 57, 56, 56, 54, 54, 54, 54, 54, 54, 53, 53, 55, 58, 58, 61,
		 64, 64, 67, 69, 69, 73, 75, 76, 79, 80, 81, 86, 87, 88, 92, 92,
		 /* Size 4x8 */
		 32, 32, 37, 52, 32, 33, 36, 49, 32, 34, 38, 49, 34, 37, 44, 54, 35, 38,
		 49, 60, 40, 42, 55, 69, 46, 46, 59, 76, 52, 51, 64, 83,
		 /* Size 8x4 */
		 32, 32, 32, 34, 35, 40, 46, 52, 32, 33, 34, 37, 38, 42, 46, 51, 37, 36,
		 38, 44, 49, 55, 59, 64, 52, 49, 49, 54, 60, 69, 76, 83,
		 /* Size 8x16 */
		 32, 31, 32, 32, 36, 44, 47, 53, 31, 32, 32, 33, 35, 42, 45, 51, 31, 32,
		 32, 33, 35, 41, 44, 49, 31, 32, 33, 33, 35, 41, 44, 49, 32, 32, 34, 34,
		 36, 42, 45, 50, 32, 33, 35, 36, 38, 42, 45, 49, 32, 33, 35, 36, 40, 44,
		 47, 51, 34, 34, 36, 38, 42, 48, 50, 54, 36, 34, 37, 40, 48, 54, 56, 60,
		 38, 36, 39, 41, 49, 56, 58, 63, 39, 37, 40, 42, 50, 58, 60, 65, 44, 41,
		 42, 45, 53, 63, 66, 71, 47, 44, 45, 47, 56, 66, 69, 75, 49, 46, 47, 48,
		 57, 67, 71, 77, 53, 49, 50, 51, 60, 71, 75, 82, 58, 54, 54, 55, 63, 75,
		 79, 87,
		 /* Size 16x8 */
		 32, 31, 31, 31, 32, 32, 32, 34, 36, 38, 39, 44, 47, 49, 53, 58, 31, 32,
		 32, 32, 32, 33, 33, 34, 34, 36, 37, 41, 44, 46, 49, 54, 32, 32, 32, 33,
		 34, 35, 35, 36, 37, 39, 40, 42, 45, 47, 50, 54, 32, 33, 33, 33, 34, 36,
		 36, 38, 40, 41, 42, 45, 47, 48, 51, 55, 36, 35, 35, 35, 36, 38, 40, 42,
		 48, 49, 50, 53, 56, 57, 60, 63, 44, 42, 41, 41, 42, 42, 44, 48, 54, 56,
		 58, 63, 66, 67, 71, 75, 47, 45, 44, 44, 45, 45, 47, 50, 56, 58, 60, 66,
		 69, 71, 75, 79, 53, 51, 49, 49, 50, 49, 51, 54, 60, 63, 65, 71, 75, 77,
		 82, 87,
		 /* Size 16x32 */
		 32, 31, 31, 31, 32, 32, 32, 35, 36, 38, 44, 44, 47, 53, 53, 59, 31, 32,
		 32, 32, 32, 32, 33, 35, 35, 37, 43, 43, 46, 52, 52, 57, 31, 32, 32, 32,
		 32, 32, 33, 35, 35, 37, 42, 42, 45, 51, 51, 56, 31, 32, 32, 32, 32, 32,
		 33, 35, 35, 37, 42, 42, 45, 51, 51, 56, 31, 32, 32, 32, 32, 32, 33, 34,
		 35, 36, 41, 41, 44, 49, 49, 54, 31, 32, 32, 32, 32, 33, 33, 34, 34, 36,
		 41, 41, 44, 49, 49, 54, 31, 32, 32, 32, 33, 33, 33, 35, 35, 36, 41, 41,
		 44, 49, 49, 54, 32, 32, 32, 32, 33, 34, 34, 36, 36, 38, 42, 42, 45, 49,
		 49, 54, 32, 32, 32, 33, 34, 34, 34, 36, 36, 38, 42, 42, 45, 50, 50, 54,
		 32, 32, 32, 33, 34, 34, 35, 37, 37, 38, 42, 42, 45, 49, 49, 54, 32, 32,
		 33, 33, 35, 35, 36, 38, 38, 39, 42, 42, 45, 49, 49, 53, 32, 32, 33, 33,
		 35, 35, 36, 38, 38, 39, 42, 42, 45, 49, 49, 53, 32, 33, 33, 33, 35, 36,
		 36, 39, 40, 41, 44, 44, 47, 51, 51, 55, 34, 34, 34, 34, 36, 37, 38, 42,
		 42, 44, 48, 48, 50, 54, 54, 58, 34, 34, 34, 34, 36, 37, 38, 42, 42, 44,
		 48, 48, 50, 54, 54, 58, 35, 34, 34, 34, 37, 37, 39, 44, 45, 46, 50, 50,
		 53, 57, 57, 61, 36, 35, 34, 35, 37, 38, 40, 47, 48, 49, 54, 54, 56, 60,
		 60, 64, 36, 35, 34, 35, 37, 38, 40, 47, 48, 49, 54, 54, 56, 60, 60, 64,
		 38, 37, 36, 37, 39, 40, 41, 48, 49, 51, 56, 56, 58, 63, 63, 67, 39, 38,
		 37, 38, 40, 40, 42, 49, 50, 52, 58, 58, 60, 65, 65, 69, 39, 38, 37, 38,
		 40, 40, 42, 49, 50, 52, 58, 58, 60, 65, 65, 69, 42, 40, 40, 40, 42, 42,
		 44, 51, 52, 55, 61, 61, 64, 69, 69, 73, 44, 42, 41, 41, 42, 43, 45, 52,

		 53, 56, 63, 63, 66, 71, 71, 75, 44, 42, 41, 41, 43, 43, 45, 52, 54, 56,
		 63, 63, 66, 72, 72, 76, 47, 45, 44, 44, 45, 45, 47, 54, 56, 58, 66, 66,
		 69, 75, 75, 79, 48, 46, 45, 45, 46, 46, 48, 55, 56, 59, 67, 67, 70, 76,
		 76, 80, 49, 47, 46, 46, 47, 47, 48, 56, 57, 60, 67, 67, 71, 77, 77, 81,
		 53, 50, 49, 49, 49, 49, 51, 58, 59, 62, 71, 71, 74, 81, 81, 86, 53, 51,
		 49, 49, 50, 50, 51, 59, 60, 63, 71, 71, 75, 82, 82, 87, 55, 52, 51, 51,
		 51, 51, 53, 60, 61, 64, 72, 72, 76, 83, 83, 88, 58, 55, 54, 54, 54, 54,
		 55, 62, 63, 67, 75, 75, 79, 87, 87, 92, 58, 55, 54, 54, 54, 54, 55, 62,
		 63, 67, 75, 75, 79, 87, 87, 92,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 34, 34, 35, 36, 36,
		 38, 39, 39, 42, 44, 44, 47, 48, 49, 53, 53, 55, 58, 58, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 35, 35, 37, 38, 38, 40,
		 42, 42, 45, 46, 47, 50, 51, 52, 55, 55, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 36, 37, 37, 40, 41, 41, 44, 45,
		 46, 49, 49, 51, 54, 54, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33,
		 33, 34, 34, 34, 35, 35, 37, 38, 38, 40, 41, 41, 44, 45, 46, 49, 49, 51,
		 54, 54, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
		 37, 37, 39, 40, 40, 42, 42, 43, 45, 46, 47, 49, 50, 51, 54, 54, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 34, 35, 35, 36, 37, 37, 37, 38, 38, 40, 40,
		 40, 42, 43, 43, 45, 46, 47, 49, 50, 51, 54, 54, 32, 33, 33, 33, 33, 33,
		 33, 34, 34, 35, 36, 36, 36, 38, 38, 39, 40, 40, 41, 42, 42, 44, 45, 45,
		 47, 48, 48, 51, 51, 53, 55, 55, 35, 35, 35, 35, 34, 34, 35, 36, 36, 37,
		 38, 38, 39, 42, 42, 44, 47, 47, 48, 49, 49, 51, 52, 52, 54, 55, 56, 58,
		 59, 60, 62, 62, 36, 35, 35, 35, 35, 34, 35, 36, 36, 37, 38, 38, 40, 42,
		 42, 45, 48, 48, 49, 50, 50, 52, 53, 54, 56, 56, 57, 59, 60, 61, 63, 63,
		 38, 37, 37, 37, 36, 36, 36, 38, 38, 38, 39, 39, 41, 44, 44, 46, 49, 49,
		 51, 52, 52, 55, 56, 56, 58, 59, 60, 62, 63, 64, 67, 67, 44, 43, 42, 42,
		 41, 41, 41, 42, 42, 42, 42, 42, 44, 48, 48, 50, 54, 54, 56, 58, 58, 61,
		 63, 63, 66, 67, 67, 71, 71, 72, 75, 75, 44, 43, 42, 42, 41, 41, 41, 42,
		 42, 42, 42, 42, 44, 48, 48, 50, 54, 54, 56, 58, 58, 61, 63, 63, 66, 67,
		 67, 71, 71, 72, 75, 75, 47, 46, 45, 45, 44, 44, 44, 45, 45, 45, 45, 45,
		 47, 50, 50, 53, 56, 56, 58, 60, 60, 64, 66, 66, 69, 70, 71, 74, 75, 76,
		 79, 79, 53, 52, 51, 51, 49, 49, 49, 49, 50, 49, 49, 49, 51, 54, 54, 57,
		 60, 60, 63, 65, 65, 69, 71, 72, 75, 76, 77, 81, 82, 83, 87, 87, 53, 52,
		 51, 51, 49, 49, 49, 49, 50, 49, 49, 49, 51, 54, 54, 57, 60, 60, 63, 65,
		 65, 69, 71, 72, 75, 76, 77, 81, 82, 83, 87, 87, 59, 57, 56, 56, 54, 54,
		 54, 54, 54, 54, 53, 53, 55, 58, 58, 61, 64, 64, 67, 69, 69, 73, 75, 76,
		 79, 80, 81, 86, 87, 88, 92, 92,
		 /* Size 4x16 */
		 31, 32, 38, 53, 32, 32, 37, 51, 32, 32, 36, 49, 32, 33, 36, 49, 32, 34,
		 38, 50, 32, 35, 39, 49, 33, 36, 41, 51, 34, 37, 44, 54, 35, 38, 49, 60,
		 37, 40, 51, 63, 38, 40, 52, 65, 42, 43, 56, 71, 45, 45, 58, 75, 47, 47,
		 60, 77, 51, 50, 63, 82, 55, 54, 67, 87,
		 /* Size 16x4 */
		 31, 32, 32, 32, 32, 32, 33, 34, 35, 37, 38, 42, 45, 47, 51, 55, 32, 32,
		 32, 33, 34, 35, 36, 37, 38, 40, 40, 43, 45, 47, 50, 54, 38, 37, 36, 36,
		 38, 39, 41, 44, 49, 51, 52, 56, 58, 60, 63, 67, 53, 51, 49, 49, 50, 49,
		 51, 54, 60, 63, 65, 71, 75, 77, 82, 87,
		 /* Size 8x32 */
		 32, 31, 32, 32, 36, 44, 47, 53, 31, 32, 32, 33, 35, 43, 46, 52, 31, 32,
		 32, 33, 35, 42, 45, 51, 31, 32, 32, 33, 35, 42, 45, 51, 31, 32, 32, 33,
		 35, 41, 44, 49, 31, 32, 32, 33, 34, 41, 44, 49, 31, 32, 33, 33, 35, 41,
		 44, 49, 32, 32, 33, 34, 36, 42, 45, 49, 32, 32, 34, 34, 36, 42, 45, 50,
		 32, 32, 34, 35, 37, 42, 45, 49, 32, 33, 35, 36, 38, 42, 45, 49, 32, 33,
		 35, 36, 38, 42, 45, 49, 32, 33, 35, 36, 40, 44, 47, 51, 34, 34, 36, 38,
		 42, 48, 50, 54, 34, 34, 36, 38, 42, 48, 50, 54, 35, 34, 37, 39, 45, 50,
		 53, 57, 36, 34, 37, 40, 48, 54, 56, 60, 36, 34, 37, 40, 48, 54, 56, 60,
		 38, 36, 39, 41, 49, 56, 58, 63, 39, 37, 40, 42, 50, 58, 60, 65, 39, 37,
		 40, 42, 50, 58, 60, 65, 42, 40, 42, 44, 52, 61, 64, 69, 44, 41, 42, 45,
		 53, 63, 66, 71, 44, 41, 43, 45, 54, 63, 66, 72, 47, 44, 45, 47, 56, 66,
		 69, 75, 48, 45, 46, 48, 56, 67, 70, 76, 49, 46, 47, 48, 57, 67, 71, 77,
		 53, 49, 49, 51, 59, 71, 74, 81, 53, 49, 50, 51, 60, 71, 75, 82, 55, 51,
		 51, 53, 61, 72, 76, 83, 58, 54, 54, 55, 63, 75, 79, 87, 58, 54, 54, 55,
		 63, 75, 79, 87,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 34, 34, 35, 36, 36,
		 38, 39, 39, 42, 44, 44, 47, 48, 49, 53, 53, 55, 58, 58, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 36, 37, 37, 40,
		 41, 41, 44, 45, 46, 49, 49, 51, 54, 54, 32, 32, 32, 32, 32, 32, 33, 33,
		 34, 34, 35, 35, 35, 36, 36, 37, 37, 37, 39, 40, 40, 42, 42, 43, 45, 46,
		 47, 49, 50, 51, 54, 54, 32, 33, 33, 33, 33, 33, 33, 34, 34, 35, 36, 36,
		 36, 38, 38, 39, 40, 40, 41, 42, 42, 44, 45, 45, 47, 48, 48, 51, 51, 53,
		 55, 55, 36, 35, 35, 35, 35, 34, 35, 36, 36, 37, 38, 38, 40, 42, 42, 45,
		 48, 48, 49, 50, 50, 52, 53, 54, 56, 56, 57, 59, 60, 61, 63, 63, 44, 43,
		 42, 42, 41, 41, 41, 42, 42, 42, 42, 42, 44, 48, 48, 50, 54, 54, 56, 58,
		 58, 61, 63, 63, 66, 67, 67, 71, 71, 72, 75, 75, 47, 46, 45, 45, 44, 44,
		 44, 45, 45, 45, 45, 45, 47, 50, 50, 53, 56, 56, 58, 60, 60, 64, 66, 66,
		 69, 70, 71, 74, 75, 76, 79, 79, 53, 52, 51, 51, 49, 49, 49, 49, 50, 49,
		 49, 49, 51, 54, 54, 57, 60, 60, 63, 65, 65, 69, 71, 72, 75, 76, 77, 81,
		 82, 83, 87, 87},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 38, 47, 49, 38, 47, 46, 46, 47, 46, 54, 57, 49, 46, 57, 66,
		 /* Size 8x8 */
		 31, 31, 35, 42, 48, 47, 49, 51, 31, 32, 36, 42, 46, 45, 46, 48, 35, 36,
		 41, 45, 47, 45, 46, 48, 42, 42, 45, 48, 50, 49, 50, 51, 48, 46, 47, 50,
		 53, 53, 54, 54, 47, 45, 45, 49, 53, 57, 59, 60, 49, 46, 46, 50, 54, 59,
		 61, 64, 51, 48, 48, 51, 54, 60, 64, 68,
		 /* Size 16x16 */
		 32, 31, 30, 31, 33, 36, 38, 41, 49, 49, 48, 49, 50, 51, 52, 54, 31, 31,
		 31, 32, 34, 38, 40, 42, 47, 47, 47, 47, 48, 48, 50, 52, 30, 31, 31, 32,
		 35, 39, 41, 42, 46, 46, 46, 45, 46, 47, 48, 50, 31, 32, 32, 33, 36, 40,
		 41, 43, 46, 46, 45, 45, 46, 46, 47, 49, 33, 34, 35, 36, 39, 43, 44, 45,
		 47, 46, 46, 45, 46, 47, 47, 49, 36, 38, 39, 40, 43, 47, 47, 47, 48, 47,
		 46, 45, 46, 46, 47, 48, 38, 40, 41, 41, 44, 47, 47, 48, 49, 48, 48, 47,
		 47, 47, 48, 49, 41, 42, 42, 43, 45, 47, 48, 48, 50, 50, 49, 49, 50, 50,
		 50, 52, 49, 47, 46, 46, 47, 48, 49, 50, 53, 53, 53, 53, 54, 54, 54, 55,
		 49, 47, 46, 46, 46, 47, 48, 50, 53, 53, 54, 55, 55, 55, 56, 57, 48, 47,
		 46, 45, 46, 46, 48, 49, 53, 54, 54, 55, 56, 56, 57, 58, 49, 47, 45, 45,
		 45, 45, 47, 49, 53, 55, 55, 58, 59, 60, 61, 62, 50, 48, 46, 46, 46, 46,
		 47, 50, 54, 55, 56, 59, 61, 61, 63, 64, 51, 48, 47, 46, 47, 46, 47, 50,
		 54, 55, 56, 60, 61, 62, 64, 66, 52, 50, 48, 47, 47, 47, 48, 50, 54, 56,
		 57, 61, 63, 64, 66, 68, 54, 52, 50, 49, 49, 48, 49, 52, 55, 57, 58, 62,
		 64, 66, 68, 71,
		 /* Size 32x32 */
		 32, 31, 31, 31, 30, 30, 31, 33, 33, 34, 36, 36, 38, 41, 41, 45, 49, 49,
		 49, 48, 48, 49, 49, 49, 50, 50, 51, 52, 52, 53, 54, 54, 31, 31, 31, 31,
		 31, 31, 31, 34, 34, 35, 38, 38, 39, 42, 42, 45, 48, 48, 47, 47, 47, 47,
		 47, 47, 49, 49, 49, 50, 50, 51, 53, 53, 31, 31, 31, 31, 31, 31, 32, 34,
		 34, 35, 38, 38, 40, 42, 42, 45, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48,
		 48, 49, 50, 50, 52, 52, 31, 31, 31, 31, 31, 31, 32, 34, 34, 36, 38, 38,
		 40, 42, 42, 45, 47, 47, 47, 47, 47, 47, 46, 47, 48, 48, 48, 49, 49, 50,
		 52, 52, 30, 31, 31, 31, 31, 31, 32, 35, 35, 36, 39, 39, 41, 42, 42, 44,
		 46, 46, 46, 46, 46, 45, 45, 45, 46, 47, 47, 48, 48, 48, 50, 50, 30, 31,
		 31, 31, 31, 32, 32, 35, 35, 36, 40, 40, 41, 42, 42, 44, 46, 46, 46, 45,
		 45, 45, 45, 45, 46, 46, 46, 47, 47, 48, 49, 49, 31, 31, 32, 32, 32, 32,
		 33, 35, 36, 37, 40, 40, 41, 43, 43, 44, 46, 46, 46, 45, 45, 45, 45, 45,
		 46, 46, 46, 47, 47, 48, 49, 49, 33, 34, 34, 34, 35, 35, 35, 38, 38, 40,
		 43, 43, 43, 44, 44, 46, 47, 47, 46, 46, 46, 45, 45, 45, 46, 46, 47, 47,
		 47, 48, 49, 49, 33, 34, 34, 34, 35, 35, 36, 38, 39, 40, 43, 43, 44, 45,
		 45, 46, 47, 47, 46, 46, 46, 45, 45, 45, 46, 46, 47, 47, 47, 48, 49, 49,
		 34, 35, 35, 36, 36, 36, 37, 40, 40, 41, 44, 44, 45, 45, 45, 46, 47, 47,
		 47, 46, 46, 45, 45, 45, 46, 46, 46, 47, 47, 48, 49, 49, 36, 38, 38, 38,
		 39, 40, 40, 43, 43, 44, 47, 47, 47, 47, 47, 47, 48, 48, 47, 46, 46, 45,
		 45, 45, 46, 46, 46, 46, 47, 47, 48, 48, 36, 38, 38, 38, 39, 40, 40, 43,
		 43, 44, 47, 47, 47, 47, 47, 47, 48, 48, 47, 46, 46, 45, 45, 45, 46, 46,
		 46, 46, 47, 47, 48, 48, 38, 39, 40, 40, 41, 41, 41, 43, 44, 45, 47, 47,
		 47, 48, 48, 48, 49, 49, 48, 48, 48, 47, 47, 47, 47, 47, 47, 48, 48, 48,
		 49, 49, 41, 42, 42, 42, 42, 42, 43, 44, 45, 45, 47, 47, 48, 48, 48, 49,
		 50, 50, 50, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 51, 52, 52, 41, 42,
		 42, 42, 42, 42, 43, 44, 45, 45, 47, 47, 48, 48, 48, 49, 50, 50, 50, 49,
		 49, 49, 49, 49, 50, 50, 50, 50, 50, 51, 52, 52, 45, 45, 45, 45, 44, 44,
		 44, 46, 46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 51, 51, 51, 51, 51, 51,
		 52, 52, 52, 52, 52, 52, 53, 53, 49, 48, 47, 47, 46, 46, 46, 47, 47, 47,
		 48, 48, 49, 50, 50, 51, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54,
		 54, 54, 55, 55, 49, 48, 47, 47, 46, 46, 46, 47, 47, 47, 48, 48, 49, 50,
		 50, 51, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 55, 55,
		 49, 47, 47, 47, 46, 46, 46, 46, 46, 47, 47, 47, 48, 50, 50, 51, 53, 53,
		 53, 54, 54, 54, 55, 55, 55, 55, 55, 56, 56, 56, 57, 57, 48, 47, 47, 47,
		 46, 45, 45, 46, 46, 46, 46, 46, 48, 49, 49, 51, 53, 53, 54, 54, 54, 55,
		 55, 56, 56, 56, 56, 57, 57, 58, 58, 58, 48, 47, 47, 47, 46, 45, 45, 46,
		 46, 46, 46, 46, 48, 49, 49, 51, 53, 53, 54, 54, 54, 55, 55, 56, 56, 56,
		 56, 57, 57, 58, 58, 58, 49, 47, 47, 47, 45, 45, 45, 45, 45, 45, 45, 45,
		 47, 49, 49, 51, 53, 53, 54, 55, 55, 57, 57, 58, 58, 59, 59, 60, 60, 60,
		 61, 61, 49, 47, 47, 46, 45, 45, 45, 45, 45, 45, 45, 45, 47, 49, 49, 51,
		 53, 53, 55, 55, 55, 57, 58, 58, 59, 60, 60, 61, 61, 61, 62, 62, 49, 47,
		 47, 47, 45, 45, 45, 45, 45, 45, 45, 45, 47, 49, 49, 51, 53, 53, 55, 56,
		 56, 58, 58, 59, 59, 60, 60, 61, 61, 62, 63, 63, 50, 49, 48, 48, 46, 46,
		 46, 46, 46, 46, 46, 46, 47, 50, 50, 52, 54, 54, 55, 56, 56, 58, 59, 59,
		 61, 61, 61, 63, 63, 63, 64, 64, 50, 49, 48, 48, 47, 46, 46, 46, 46, 46,
		 46, 46, 47, 50, 50, 52, 54, 54, 55, 56, 56, 59, 60, 60, 61, 61, 62, 63,
		 63, 64, 65, 65, 51, 49, 48, 48, 47, 46, 46, 47, 47, 46, 46, 46, 47, 50,
		 50, 52, 54, 54, 55, 56, 56, 59, 60, 60, 61, 62, 62, 64, 64, 64, 66, 66,
		 52, 50, 49, 49, 48, 47, 47, 47, 47, 47, 46, 46, 48, 50, 50, 52, 54, 54,
		 56, 57, 57, 60, 61, 61, 63, 63, 64, 66, 66, 67, 68, 68, 52, 50, 50, 49,
		 48, 47, 47, 47, 47, 47, 47, 47, 48, 50, 50, 52, 54, 54, 56, 57, 57, 60,
		 61, 61, 63, 63, 64, 66, 66, 67, 68, 68, 53, 51, 50, 50, 48, 48, 48, 48,
		 48, 48, 47, 47, 48, 51, 51, 52, 54, 54, 56, 58, 58, 60, 61, 62, 63, 64,
		 64, 67, 67, 68, 69, 69, 54, 53, 52, 52, 50, 49, 49, 49, 49, 49, 48, 48,
		 49, 52, 52, 53, 55, 55, 57, 58, 58, 61, 62, 63, 64, 65, 66, 68, 68, 69,
		 71, 71, 54, 53, 52, 52, 50, 49, 49, 49, 49, 49, 48, 48, 49, 52, 52, 53,
		 55, 55, 57, 58, 58, 61, 62, 63, 64, 65, 66, 68, 68, 69, 71, 71,
		 /* Size 4x8 */
		 31, 38, 47, 50, 31, 40, 46, 48, 36, 44, 47, 47, 42, 47, 50, 50, 47, 48,
		 53, 54, 46, 46, 54, 60, 48, 46, 55, 64, 50, 48, 56, 67,
		 /* Size 8x4 */
		 31, 31, 36, 42, 47, 46, 48, 50, 38, 40, 44, 47, 48, 46, 46, 48, 47, 46,
		 47, 50, 53, 54, 55, 56, 50, 48, 47, 50, 54, 60, 64, 67,
		 /* Size 8x16 */
		 32, 31, 35, 38, 48, 49, 50, 52, 31, 31, 37, 40, 47, 47, 48, 50, 30, 32,
		 38, 40, 46, 45, 46, 48, 31, 33, 38, 41, 46, 45, 46, 48, 33, 36, 41, 44,
		 47, 46, 46, 47, 37, 40, 45, 47, 47, 45, 46, 47, 39, 41, 46, 47, 48, 47,
		 47, 48, 42, 43, 46, 48, 50, 49, 50, 50, 49, 46, 48, 49, 53, 53, 54, 54,
		 48, 46, 47, 48, 53, 55, 55, 56, 48, 46, 46, 48, 53, 56, 56, 57, 49, 45,
		 45, 47, 53, 58, 59, 61, 50, 46, 46, 48, 54, 59, 61, 63, 51, 47, 47, 48,
		 54, 60, 61, 64, 52, 48, 47, 48, 54, 61, 63, 66, 54, 50, 49, 50, 55, 62,
		 65, 68,
		 /* Size 16x8 */
		 32, 31, 30, 31, 33, 37, 39, 42, 49, 48, 48, 49, 50, 51, 52, 54, 31, 31,
		 32, 33, 36, 40, 41, 43, 46, 46, 46, 45, 46, 47, 48, 50, 35, 37, 38, 38,
		 41, 45, 46, 46, 48, 47, 46, 45, 46, 47, 47, 49, 38, 40, 40, 41, 44, 47,
		 47, 48, 49, 48, 48, 47, 48, 48, 48, 50, 48, 47, 46, 46, 47, 47, 48, 50,
		 53, 53, 53, 53, 54, 54, 54, 55, 49, 47, 45, 45, 46, 45, 47, 49, 53, 55,
		 56, 58, 59, 60, 61, 62, 50, 48, 46, 46, 46, 46, 47, 50, 54, 55, 56, 59,
		 61, 61, 63, 65, 52, 50, 48, 48, 47, 47, 48, 50, 54, 56, 57, 61, 63, 64,
		 66, 68,
		 /* Size 16x32 */
		 32, 31, 31, 31, 35, 37, 38, 47, 48, 48, 49, 49, 50, 52, 52, 54, 31, 31,
		 31, 32, 36, 38, 39, 46, 47, 47, 48, 48, 49, 50, 50, 53, 31, 31, 31, 32,
		 37, 38, 40, 46, 47, 47, 47, 47, 48, 50, 50, 52, 31, 31, 31, 32, 37, 38,
		 40, 46, 47, 47, 47, 47, 48, 50, 50, 52, 30, 31, 32, 32, 38, 39, 40, 45,
		 46, 46, 45, 45, 46, 48, 48, 50, 30, 31, 32, 33, 38, 40, 41, 45, 46, 46,
		 45, 45, 46, 48, 48, 50, 31, 32, 33, 33, 38, 40, 41, 45, 46, 46, 45, 45,
		 46, 48, 48, 50, 33, 35, 35, 36, 41, 43, 43, 46, 47, 46, 45, 45, 46, 47,
		 47, 49, 33, 35, 36, 36, 41, 43, 44, 46, 47, 46, 46, 46, 46, 47, 47, 49,
		 34, 36, 37, 37, 42, 44, 45, 47, 47, 47, 45, 45, 46, 47, 47, 49, 37, 39,
		 40, 41, 45, 47, 47, 47, 47, 47, 45, 45, 46, 47, 47, 48, 37, 39, 40, 41,
		 45, 47, 47, 47, 47, 47, 45, 45, 46, 47, 47, 48, 39, 40, 41, 42, 46, 47,
		 47, 48, 48, 48, 47, 47, 47, 48, 48, 50, 42, 42, 43, 43, 46, 47, 48, 50,
		 50, 50, 49, 49, 50, 50, 50, 52, 42, 42, 43, 43, 46, 47, 48, 50, 50, 50,
		 49, 49, 50, 50, 50, 52, 45, 45, 44, 45, 47, 47, 48, 51, 51, 51, 51, 51,
		 52, 52, 52, 54, 49, 47, 46, 47, 48, 48, 49, 52, 53, 53, 53, 53, 54, 54,
		 54, 55, 49, 47, 46, 47, 48, 48, 49, 52, 53, 53, 53, 53, 54, 54, 54, 55,
		 48, 47, 46, 46, 47, 47, 48, 52, 53, 53, 55, 55, 55, 56, 56, 57, 48, 46,
		 46, 46, 46, 47, 48, 52, 53, 54, 56, 56, 56, 57, 57, 59, 48, 46, 46, 46,
		 46, 47, 48, 52, 53, 54, 56, 56, 56, 57, 57, 59, 49, 46, 45, 45, 46, 46,
		 47, 52, 53, 54, 57, 57, 58, 60, 60, 61, 49, 46, 45, 45, 45, 46, 47, 52,
		 53, 55, 58, 58, 59, 61, 61, 62, 49, 46, 45, 45, 46, 46, 47, 52, 53, 55,
		 58, 58, 60, 61, 61, 63, 50, 47, 46, 46, 46, 46, 48, 53, 54, 55, 59, 59,
		 61, 63, 63, 65, 50, 48, 46, 46, 46, 46, 48, 53, 54, 55, 59, 59, 61, 64,
		 64, 65, 51, 48, 47, 47, 47, 47, 48, 53, 54, 55, 60, 60, 61, 64, 64, 66,
		 52, 49, 48, 48, 47, 47, 48, 53, 54, 56, 61, 61, 63, 66, 66, 68, 52, 49,
		 48, 48, 47, 47, 48, 53, 54, 56, 61, 61, 63, 66, 66, 68, 53, 50, 48, 48,
		 48, 48, 49, 54, 54, 56, 61, 61, 63, 67, 67, 69, 54, 51, 50, 50, 49, 49,
		 50, 55, 55, 57, 62, 62, 65, 68, 68, 71, 54, 51, 50, 50, 49, 49, 50, 55,
		 55, 57, 62, 62, 65, 68, 68, 71,
		 /* Size 32x16 */
		 32, 31, 31, 31, 30, 30, 31, 33, 33, 34, 37, 37, 39, 42, 42, 45, 49, 49,
		 48, 48, 48, 49, 49, 49, 50, 50, 51, 52, 52, 53, 54, 54, 31, 31, 31, 31,
		 31, 31, 32, 35, 35, 36, 39, 39, 40, 42, 42, 45, 47, 47, 47, 46, 46, 46,
		 46, 46, 47, 48, 48, 49, 49, 50, 51, 51, 31, 31, 31, 31, 32, 32, 33, 35,
		 36, 37, 40, 40, 41, 43, 43, 44, 46, 46, 46, 46, 46, 45, 45, 45, 46, 46,
		 47, 48, 48, 48, 50, 50, 31, 32, 32, 32, 32, 33, 33, 36, 36, 37, 41, 41,
		 42, 43, 43, 45, 47, 47, 46, 46, 46, 45, 45, 45, 46, 46, 47, 48, 48, 48,
		 50, 50, 35, 36, 37, 37, 38, 38, 38, 41, 41, 42, 45, 45, 46, 46, 46, 47,
		 48, 48, 47, 46, 46, 46, 45, 46, 46, 46, 47, 47, 47, 48, 49, 49, 37, 38,
		 38, 38, 39, 40, 40, 43, 43, 44, 47, 47, 47, 47, 47, 47, 48, 48, 47, 47,
		 47, 46, 46, 46, 46, 46, 47, 47, 47, 48, 49, 49, 38, 39, 40, 40, 40, 41,
		 41, 43, 44, 45, 47, 47, 47, 48, 48, 48, 49, 49, 48, 48, 48, 47, 47, 47,
		 48, 48, 48, 48, 48, 49, 50, 50, 47, 46, 46, 46, 45, 45, 45, 46, 46, 47,
		 47, 47, 48, 50, 50, 51, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53,
		 53, 54, 55, 55, 48, 47, 47, 47, 46, 46, 46, 47, 47, 47, 47, 47, 48, 50,
		 50, 51, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 55, 55,
		 48, 47, 47, 47, 46, 46, 46, 46, 46, 47, 47, 47, 48, 50, 50, 51, 53, 53,
		 53, 54, 54, 54, 55, 55, 55, 55, 55, 56, 56, 56, 57, 57, 49, 48, 47, 47,
		 45, 45, 45, 45, 46, 45, 45, 45, 47, 49, 49, 51, 53, 53, 55, 56, 56, 57,
		 58, 58, 59, 59, 60, 61, 61, 61, 62, 62, 49, 48, 47, 47, 45, 45, 45, 45,
		 46, 45, 45, 45, 47, 49, 49, 51, 53, 53, 55, 56, 56, 57, 58, 58, 59, 59,
		 60, 61, 61, 61, 62, 62, 50, 49, 48, 48, 46, 46, 46, 46, 46, 46, 46, 46,
		 47, 50, 50, 52, 54, 54, 55, 56, 56, 58, 59, 60, 61, 61, 61, 63, 63, 63,
		 65, 65, 52, 50, 50, 50, 48, 48, 48, 47, 47, 47, 47, 47, 48, 50, 50, 52,
		 54, 54, 56, 57, 57, 60, 61, 61, 63, 64, 64, 66, 66, 67, 68, 68, 52, 50,
		 50, 50, 48, 48, 48, 47, 47, 47, 47, 47, 48, 50, 50, 52, 54, 54, 56, 57,
		 57, 60, 61, 61, 63, 64, 64, 66, 66, 67, 68, 68, 54, 53, 52, 52, 50, 50,
		 50, 49, 49, 49, 48, 48, 50, 52, 52, 54, 55, 55, 57, 59, 59, 61, 62, 63,
		 65, 65, 66, 68, 68, 69, 71, 71,
		 /* Size 4x16 */
		 31, 37, 48, 52, 31, 38, 47, 50, 31, 39, 46, 48, 32, 40, 46, 48, 35, 43,
		 46, 47, 39, 47, 47, 47, 40, 47, 48, 48, 42, 47, 50, 50, 47, 48, 53, 54,
		 47, 47, 53, 56, 46, 47, 54, 57, 46, 46, 55, 61, 47, 46, 55, 63, 48, 47,
		 55, 64, 49, 47, 56, 66, 51, 49, 57, 68,
		 /* Size 16x4 */
		 31, 31, 31, 32, 35, 39, 40, 42, 47, 47, 46, 46, 47, 48, 49, 51, 37, 38,
		 39, 40, 43, 47, 47, 47, 48, 47, 47, 46, 46, 47, 47, 49, 48, 47, 46, 46,
		 46, 47, 48, 50, 53, 53, 54, 55, 55, 55, 56, 57, 52, 50, 48, 48, 47, 47,
		 48, 50, 54, 56, 57, 61, 63, 64, 66, 68,
		 /* Size 8x32 */
		 32, 31, 35, 38, 48, 49, 50, 52, 31, 31, 36, 39, 47, 48, 49, 50, 31, 31,
		 37, 40, 47, 47, 48, 50, 31, 31, 37, 40, 47, 47, 48, 50, 30, 32, 38, 40,
		 46, 45, 46, 48, 30, 32, 38, 41, 46, 45, 46, 48, 31, 33, 38, 41, 46, 45,
		 46, 48, 33, 35, 41, 43, 47, 45, 46, 47, 33, 36, 41, 44, 47, 46, 46, 47,
		 34, 37, 42, 45, 47, 45, 46, 47, 37, 40, 45, 47, 47, 45, 46, 47, 37, 40,
		 45, 47, 47, 45, 46, 47, 39, 41, 46, 47, 48, 47, 47, 48, 42, 43, 46, 48,
		 50, 49, 50, 50, 42, 43, 46, 48, 50, 49, 50, 50, 45, 44, 47, 48, 51, 51,
		 52, 52, 49, 46, 48, 49, 53, 53, 54, 54, 49, 46, 48, 49, 53, 53, 54, 54,
		 48, 46, 47, 48, 53, 55, 55, 56, 48, 46, 46, 48, 53, 56, 56, 57, 48, 46,
		 46, 48, 53, 56, 56, 57, 49, 45, 46, 47, 53, 57, 58, 60, 49, 45, 45, 47,
		 53, 58, 59, 61, 49, 45, 46, 47, 53, 58, 60, 61, 50, 46, 46, 48, 54, 59,
		 61, 63, 50, 46, 46, 48, 54, 59, 61, 64, 51, 47, 47, 48, 54, 60, 61, 64,
		 52, 48, 47, 48, 54, 61, 63, 66, 52, 48, 47, 48, 54, 61, 63, 66, 53, 48,
		 48, 49, 54, 61, 63, 67, 54, 50, 49, 50, 55, 62, 65, 68, 54, 50, 49, 50,
		 55, 62, 65, 68,
		 /* Size 32x8 */
		 32, 31, 31, 31, 30, 30, 31, 33, 33, 34, 37, 37, 39, 42, 42, 45, 49, 49,
		 48, 48, 48, 49, 49, 49, 50, 50, 51, 52, 52, 53, 54, 54, 31, 31, 31, 31,
		 32, 32, 33, 35, 36, 37, 40, 40, 41, 43, 43, 44, 46, 46, 46, 46, 46, 45,
		 45, 45, 46, 46, 47, 48, 48, 48, 50, 50, 35, 36, 37, 37, 38, 38, 38, 41,
		 41, 42, 45, 45, 46, 46, 46, 47, 48, 48, 47, 46, 46, 46, 45, 46, 46, 46,
		 47, 47, 47, 48, 49, 49, 38, 39, 40, 40, 40, 41, 41, 43, 44, 45, 47, 47,
		 47, 48, 48, 48, 49, 49, 48, 48, 48, 47, 47, 47, 48, 48, 48, 48, 48, 49,
		 50, 50, 48, 47, 47, 47, 46, 46, 46, 47, 47, 47, 47, 47, 48, 50, 50, 51,
		 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 55, 55, 49, 48,
		 47, 47, 45, 45, 45, 45, 46, 45, 45, 45, 47, 49, 49, 51, 53, 53, 55, 56,
		 56, 57, 58, 58, 59, 59, 60, 61, 61, 61, 62, 62, 50, 49, 48, 48, 46, 46,
		 46, 46, 46, 46, 46, 46, 47, 50, 50, 52, 54, 54, 55, 56, 56, 58, 59, 60,
		 61, 61, 61, 63, 63, 63, 65, 65, 52, 50, 50, 50, 48, 48, 48, 47, 47, 47,
		 47, 47, 48, 50, 50, 52, 54, 54, 56, 57, 57, 60, 61, 61, 63, 64, 64, 66,
		 66, 67, 68, 68},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 32, 35, 43, 32, 34, 37, 43, 35, 37, 48, 54, 43, 43, 54, 65,
		 /* Size 8x8 */
		 31, 31, 32, 32, 34, 37, 43, 47, 31, 32, 32, 32, 34, 36, 41, 44, 32, 32,
		 33, 34, 35, 38, 42, 45, 32, 32, 34, 35, 37, 39, 42, 46, 34, 34, 35, 37,
		 41, 45, 49, 52, 37, 36, 38, 39, 45, 51, 56, 59, 43, 41, 42, 42, 49, 56,
		 63, 67, 47, 44, 45, 46, 52, 59, 67, 71,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 32, 32, 34, 35, 36, 39, 41, 44, 47, 48, 31, 32,
		 32, 32, 32, 32, 32, 33, 34, 35, 35, 38, 40, 42, 45, 46, 31, 32, 32, 32,
		 32, 32, 32, 33, 34, 34, 35, 38, 39, 42, 45, 45, 31, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 34, 37, 38, 41, 44, 44, 31, 32, 32, 32, 33, 33, 33, 34,
		 35, 36, 36, 39, 40, 42, 44, 45, 31, 32, 32, 32, 33, 33, 34, 34, 35, 36,
		 36, 39, 40, 42, 45, 45, 32, 32, 32, 32, 33, 34, 35, 36, 37, 38, 38, 40,
		 41, 42, 45, 46, 32, 33, 33, 33, 34, 34, 36, 36, 38, 39, 40, 42, 43, 44,
		 47, 47, 34, 34, 34, 33, 35, 35, 37, 38, 39, 42, 42, 45, 46, 47, 50, 51,
		 35, 35, 34, 34, 36, 36, 38, 39, 42, 46, 47, 49, 50, 52, 55, 55, 36, 35,
		 35, 34, 36, 36, 38, 40, 42, 47, 48, 50, 52, 54, 56, 57, 39, 38, 38, 37,
		 39, 39, 40, 42, 45, 49, 50, 54, 55, 58, 60, 61, 41, 40, 39, 38, 40, 40,
		 41, 43, 46, 50, 52, 55, 57, 60, 62, 63, 44, 42, 42, 41, 42, 42, 42, 44,
		 47, 52, 54, 58, 60, 63, 66, 67, 47, 45, 45, 44, 44, 45, 45, 47, 50, 55,
		 56, 60, 62, 66, 69, 70, 48, 46, 45, 44, 45, 45, 46, 47, 51, 55, 57, 61,
		 63, 67, 70, 71,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 34,
		 35, 36, 36, 38, 39, 39, 41, 44, 44, 45, 47, 48, 48, 51, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 35, 35, 35, 37,
		 39, 39, 40, 43, 43, 44, 46, 47, 47, 50, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 35, 35, 35, 37, 38, 38, 40, 42,
		 42, 43, 45, 46, 46, 49, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 34, 34, 34, 35, 35, 35, 37, 38, 38, 40, 42, 42, 43, 45, 46,
		 46, 49, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34,
		 34, 34, 34, 35, 35, 36, 38, 38, 39, 42, 42, 42, 45, 45, 45, 48, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34,
		 34, 36, 37, 37, 38, 41, 41, 41, 44, 44, 44, 47, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 36, 37, 37,
		 38, 41, 41, 41, 44, 44, 44, 47, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 36, 38, 38, 39, 41, 41, 42,
		 44, 45, 45, 47, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33,
		 34, 35, 35, 35, 36, 36, 36, 37, 39, 39, 40, 42, 42, 42, 44, 45, 45, 48,
		 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35, 35, 35,
		 36, 36, 36, 38, 39, 39, 40, 42, 42, 42, 45, 45, 45, 48, 31, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 38,
		 39, 39, 40, 42, 42, 42, 45, 45, 45, 48, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 39, 40, 40, 41, 42,
		 42, 43, 45, 45, 45, 48, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 35,
		 35, 35, 36, 37, 37, 37, 38, 38, 38, 39, 40, 40, 41, 42, 42, 43, 45, 46,
		 46, 48, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 35, 35, 35, 36, 37,
		 37, 37, 38, 38, 38, 39, 40, 40, 41, 42, 42, 43, 45, 46, 46, 48, 32, 33,
		 33, 33, 33, 33, 33, 33, 34, 34, 34, 35, 36, 36, 36, 38, 38, 38, 39, 40,
		 40, 41, 42, 42, 43, 44, 44, 45, 47, 47, 47, 50, 34, 34, 34, 34, 34, 33,
		 33, 34, 35, 35, 35, 36, 37, 37, 38, 39, 39, 40, 42, 42, 42, 44, 45, 45,
		 46, 47, 47, 48, 50, 51, 51, 53, 34, 34, 34, 34, 34, 33, 33, 34, 35, 35,
		 35, 36, 37, 37, 38, 39, 39, 40, 42, 42, 42, 44, 45, 45, 46, 47, 47, 48,
		 50, 51, 51, 53, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 36, 37, 37,
		 38, 40, 40, 41, 43, 44, 44, 45, 46, 46, 47, 49, 49, 49, 51, 52, 52, 54,
		 35, 35, 35, 35, 34, 34, 34, 34, 36, 36, 36, 37, 38, 38, 39, 42, 42, 43,
		 46, 47, 47, 48, 49, 49, 50, 52, 52, 53, 55, 55, 55, 57, 36, 35, 35, 35,
		 35, 34, 34, 35, 36, 36, 36, 37, 38, 38, 40, 42, 42, 44, 47, 48, 48, 50,
		 50, 50, 52, 54, 54, 54, 56, 57, 57, 58, 36, 35, 35, 35, 35, 34, 34, 35,
		 36, 36, 36, 37, 38, 38, 40, 42, 42, 44, 47, 48, 48, 50, 50, 50, 52, 54,
		 54, 54, 56, 57, 57, 58, 38, 37, 37, 37, 36, 36, 36, 36, 37, 38, 38, 39,
		 39, 39, 41, 44, 44, 45, 48, 50, 50, 51, 52, 52, 54, 56, 56, 57, 58, 59,
		 59, 61, 39, 39, 38, 38, 38, 37, 37, 38, 39, 39, 39, 40, 40, 40, 42, 45,
		 45, 46, 49, 50, 50, 52, 54, 54, 55, 58, 58, 58, 60, 61, 61, 63, 39, 39,
		 38, 38, 38, 37, 37, 38, 39, 39, 39, 40, 40, 40, 42, 45, 45, 46, 49, 50,
		 50, 52, 54, 54, 55, 58, 58, 58, 60, 61, 61, 63, 41, 40, 40, 40, 39, 38,
		 38, 39, 40, 40, 40, 41, 41, 41, 43, 46, 46, 47, 50, 52, 52, 54, 55, 55,
		 57, 60, 60, 60, 62, 63, 63, 66, 44, 43, 42, 42, 42, 41, 41, 41, 42, 42,
		 42, 42, 42, 42, 44, 47, 47, 49, 52, 54, 54, 56, 58, 58, 60, 63, 63, 64,
		 66, 67, 67, 69, 44, 43, 42, 42, 42, 41, 41, 41, 42, 42, 42, 42, 42, 42,
		 44, 47, 47, 49, 52, 54, 54, 56, 58, 58, 60, 63, 63, 64, 66, 67, 67, 69,
		 45, 44, 43, 43, 42, 41, 41, 42, 42, 42, 42, 43, 43, 43, 45, 48, 48, 49,
		 53, 54, 54, 57, 58, 58, 60, 64, 64, 65, 67, 68, 68, 70, 47, 46, 45, 45,
		 45, 44, 44, 44, 44, 45, 45, 45, 45, 45, 47, 50, 50, 51, 55, 56, 56, 58,
		 60, 60, 62, 66, 66, 67, 69, 70, 70, 73, 48, 47, 46, 46, 45, 44, 44, 45,
		 45, 45, 45, 45, 46, 46, 47, 51, 51, 52, 55, 57, 57, 59, 61, 61, 63, 67,
		 67, 68, 70, 71, 71, 74, 48, 47, 46, 46, 45, 44, 44, 45, 45, 45, 45, 45,
		 46, 46, 47, 51, 51, 52, 55, 57, 57, 59, 61, 61, 63, 67, 67, 68, 70, 71,
		 71, 74, 51, 50, 49, 49, 48, 47, 47, 47, 48, 48, 48, 48, 48, 48, 50, 53,
		 53, 54, 57, 58, 58, 61, 63, 63, 66, 69, 69, 70, 73, 74, 74, 77,
		 /* Size 4x8 */
		 31, 32, 35, 43, 32, 33, 34, 41, 32, 34, 36, 42, 32, 35, 38, 42, 34, 37,
		 43, 49, 37, 40, 49, 56, 42, 43, 53, 63, 46, 46, 56, 67,
		 /* Size 8x4 */
		 31, 32, 32, 32, 34, 37, 42, 46, 32, 33, 34, 35, 37, 40, 43, 46, 35, 34,
		 36, 38, 43, 49, 53, 56, 43, 41, 42, 42, 49, 56, 63, 67,
		 /* Size 8x16 */
		 32, 31, 31, 32, 35, 36, 44, 47, 31, 32, 32, 32, 35, 35, 42, 45, 31, 32,
		 32, 32, 34, 35, 41, 45, 31, 32, 32, 33, 34, 34, 41, 44, 31, 32, 33, 34,
		 35, 36, 42, 44, 32, 32, 33, 34, 36, 36, 42, 45, 32, 33, 34, 35, 37, 38,
		 42, 45, 32, 33, 34, 36, 39, 40, 44, 47, 34, 34, 35, 37, 41, 42, 48, 50,
		 35, 34, 36, 38, 45, 47, 52, 55, 36, 34, 36, 38, 46, 48, 54, 56, 39, 37,
		 39, 40, 48, 50, 58, 60, 41, 39, 40, 41, 49, 51, 60, 62, 44, 41, 42, 43,
		 51, 53, 63, 66, 47, 44, 44, 45, 53, 56, 66, 69, 48, 45, 45, 46, 54, 56,
		 67, 70,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 32, 32, 32, 34, 35, 36, 39, 41, 44, 47, 48, 31, 32,
		 32, 32, 32, 32, 33, 33, 34, 34, 34, 37, 39, 41, 44, 45, 31, 32, 32, 32,
		 33, 33, 34, 34, 35, 36, 36, 39, 40, 42, 44, 45, 32, 32, 32, 33, 34, 34,
		 35, 36, 37, 38, 38, 40, 41, 43, 45, 46, 35, 35, 34, 34, 35, 36, 37, 39,
		 41, 45, 46, 48, 49, 51, 53, 54, 36, 35, 35, 34, 36, 36, 38, 40, 42, 47,
		 48, 50, 51, 53, 56, 56, 44, 42, 41, 41, 42, 42, 42, 44, 48, 52, 54, 58,
		 60, 63, 66, 67, 47, 45, 45, 44, 44, 45, 45, 47, 50, 55, 56, 60, 62, 66,
		 69, 70,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 32, 32, 32, 35, 36, 36, 40, 44, 44, 47, 53, 31, 31,
		 32, 32, 32, 32, 32, 33, 35, 35, 35, 39, 43, 43, 46, 52, 31, 32, 32, 32,

		 32, 32, 32, 33, 35, 35, 35, 39, 42, 42, 45, 51, 31, 32, 32, 32, 32, 32,
		 32, 33, 35, 35, 35, 39, 42, 42, 45, 51, 31, 32, 32, 32, 32, 32, 32, 33,
		 34, 35, 35, 39, 41, 41, 45, 50, 31, 32, 32, 32, 32, 33, 33, 33, 34, 34,
		 34, 38, 41, 41, 44, 49, 31, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 38,
		 41, 41, 44, 49, 31, 32, 32, 32, 32, 33, 33, 33, 34, 35, 35, 38, 41, 41,
		 44, 49, 31, 32, 32, 32, 33, 34, 34, 34, 35, 36, 36, 39, 42, 42, 44, 49,
		 32, 32, 32, 32, 33, 34, 34, 34, 36, 36, 36, 39, 42, 42, 45, 50, 32, 32,
		 32, 32, 33, 34, 34, 34, 36, 36, 36, 39, 42, 42, 45, 50, 32, 32, 32, 32,
		 33, 35, 35, 35, 37, 37, 37, 40, 42, 42, 45, 49, 32, 32, 33, 33, 34, 35,
		 35, 36, 37, 38, 38, 41, 42, 42, 45, 49, 32, 32, 33, 33, 34, 35, 35, 36,
		 37, 38, 38, 41, 42, 42, 45, 49, 32, 33, 33, 33, 34, 36, 36, 36, 39, 40,
		 40, 42, 44, 44, 47, 51, 34, 34, 34, 34, 35, 37, 37, 38, 41, 42, 42, 45,
		 48, 48, 50, 54, 34, 34, 34, 34, 35, 37, 37, 38, 41, 42, 42, 45, 48, 48,
		 50, 54, 34, 34, 34, 34, 35, 37, 37, 38, 42, 43, 43, 46, 49, 49, 51, 55,
		 35, 35, 34, 34, 36, 38, 38, 39, 45, 47, 47, 50, 52, 52, 55, 59, 36, 35,
		 34, 34, 36, 38, 38, 40, 46, 48, 48, 51, 54, 54, 56, 60, 36, 35, 34, 34,
		 36, 38, 38, 40, 46, 48, 48, 51, 54, 54, 56, 60, 38, 37, 36, 36, 37, 40,
		 40, 41, 47, 49, 49, 53, 56, 56, 58, 63, 39, 38, 37, 37, 39, 40, 40, 42,
		 48, 50, 50, 54, 58, 58, 60, 65, 39, 38, 37, 37, 39, 40, 40, 42, 48, 50,
		 50, 54, 58, 58, 60, 65, 41, 40, 39, 39, 40, 41, 41, 43, 49, 51, 51, 56,
		 60, 60, 62, 67, 44, 42, 41, 41, 42, 43, 43, 45, 51, 53, 53, 59, 63, 63,
		 66, 71, 44, 42, 41, 41, 42, 43, 43, 45, 51, 53, 53, 59, 63, 63, 66, 71,
		 44, 43, 42, 42, 42, 43, 43, 45, 51, 54, 54, 59, 64, 64, 67, 72, 47, 45,
		 44, 44, 44, 45, 45, 47, 53, 56, 56, 61, 66, 66, 69, 75, 48, 46, 45, 45,
		 45, 46, 46, 48, 54, 56, 56, 62, 67, 67, 70, 76, 48, 46, 45, 45, 45, 46,
		 46, 48, 54, 56, 56, 62, 67, 67, 70, 76, 51, 49, 47, 47, 48, 48, 48, 50,
		 56, 58, 58, 64, 69, 69, 73, 79,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 34, 34, 34,
		 35, 36, 36, 38, 39, 39, 41, 44, 44, 44, 47, 48, 48, 51, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 35, 35, 35, 37,
		 38, 38, 40, 42, 42, 43, 45, 46, 46, 49, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 34, 36, 37, 37, 39, 41,
		 41, 42, 44, 45, 45, 47, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 33, 34, 34, 34, 34, 34, 34, 36, 37, 37, 39, 41, 41, 42, 44, 45,
		 45, 47, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35,
		 35, 35, 36, 36, 36, 37, 39, 39, 40, 42, 42, 42, 44, 45, 45, 48, 32, 32,
		 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 37, 37, 37, 38, 38,
		 38, 40, 40, 40, 41, 43, 43, 43, 45, 46, 46, 48, 32, 32, 32, 32, 32, 33,
		 33, 33, 34, 34, 34, 35, 35, 35, 36, 37, 37, 37, 38, 38, 38, 40, 40, 40,
		 41, 43, 43, 43, 45, 46, 46, 48, 32, 33, 33, 33, 33, 33, 33, 33, 34, 34,
		 34, 35, 36, 36, 36, 38, 38, 38, 39, 40, 40, 41, 42, 42, 43, 45, 45, 45,
		 47, 48, 48, 50, 35, 35, 35, 35, 34, 34, 34, 34, 35, 36, 36, 37, 37, 37,
		 39, 41, 41, 42, 45, 46, 46, 47, 48, 48, 49, 51, 51, 51, 53, 54, 54, 56,
		 36, 35, 35, 35, 35, 34, 34, 35, 36, 36, 36, 37, 38, 38, 40, 42, 42, 43,
		 47, 48, 48, 49, 50, 50, 51, 53, 53, 54, 56, 56, 56, 58, 36, 35, 35, 35,
		 35, 34, 34, 35, 36, 36, 36, 37, 38, 38, 40, 42, 42, 43, 47, 48, 48, 49,
		 50, 50, 51, 53, 53, 54, 56, 56, 56, 58, 40, 39, 39, 39, 39, 38, 38, 38,
		 39, 39, 39, 40, 41, 41, 42, 45, 45, 46, 50, 51, 51, 53, 54, 54, 56, 59,
		 59, 59, 61, 62, 62, 64, 44, 43, 42, 42, 41, 41, 41, 41, 42, 42, 42, 42,

		 42, 42, 44, 48, 48, 49, 52, 54, 54, 56, 58, 58, 60, 63, 63, 64, 66, 67,
		 67, 69, 44, 43, 42, 42, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 44, 48,
		 48, 49, 52, 54, 54, 56, 58, 58, 60, 63, 63, 64, 66, 67, 67, 69, 47, 46,
		 45, 45, 45, 44, 44, 44, 44, 45, 45, 45, 45, 45, 47, 50, 50, 51, 55, 56,
		 56, 58, 60, 60, 62, 66, 66, 67, 69, 70, 70, 73, 53, 52, 51, 51, 50, 49,
		 49, 49, 49, 50, 50, 49, 49, 49, 51, 54, 54, 55, 59, 60, 60, 63, 65, 65,
		 67, 71, 71, 72, 75, 76, 76, 79,
		 /* Size 4x16 */
		 31, 32, 36, 44, 32, 32, 35, 42, 32, 32, 35, 41, 32, 33, 34, 41, 32, 34,
		 36, 42, 32, 34, 36, 42, 32, 35, 38, 42, 33, 36, 40, 44, 34, 37, 42, 48,
		 35, 38, 47, 52, 35, 38, 48, 54, 38, 40, 50, 58, 40, 41, 51, 60, 42, 43,
		 53, 63, 45, 45, 56, 66, 46, 46, 56, 67,
		 /* Size 16x4 */
		 31, 32, 32, 32, 32, 32, 32, 33, 34, 35, 35, 38, 40, 42, 45, 46, 32, 32,
		 32, 33, 34, 34, 35, 36, 37, 38, 38, 40, 41, 43, 45, 46, 36, 35, 35, 34,
		 36, 36, 38, 40, 42, 47, 48, 50, 51, 53, 56, 56, 44, 42, 41, 41, 42, 42,
		 42, 44, 48, 52, 54, 58, 60, 63, 66, 67,
		 /* Size 8x32 */
		 32, 31, 31, 32, 35, 36, 44, 47, 31, 32, 32, 32, 35, 35, 43, 46, 31, 32,
		 32, 32, 35, 35, 42, 45, 31, 32, 32, 32, 35, 35, 42, 45, 31, 32, 32, 32,
		 34, 35, 41, 45, 31, 32, 32, 33, 34, 34, 41, 44, 31, 32, 32, 33, 34, 34,
		 41, 44, 31, 32, 32, 33, 34, 35, 41, 44, 31, 32, 33, 34, 35, 36, 42, 44,
		 32, 32, 33, 34, 36, 36, 42, 45, 32, 32, 33, 34, 36, 36, 42, 45, 32, 32,
		 33, 35, 37, 37, 42, 45, 32, 33, 34, 35, 37, 38, 42, 45, 32, 33, 34, 35,
		 37, 38, 42, 45, 32, 33, 34, 36, 39, 40, 44, 47, 34, 34, 35, 37, 41, 42,
		 48, 50, 34, 34, 35, 37, 41, 42, 48, 50, 34, 34, 35, 37, 42, 43, 49, 51,
		 35, 34, 36, 38, 45, 47, 52, 55, 36, 34, 36, 38, 46, 48, 54, 56, 36, 34,
		 36, 38, 46, 48, 54, 56, 38, 36, 37, 40, 47, 49, 56, 58, 39, 37, 39, 40,
		 48, 50, 58, 60, 39, 37, 39, 40, 48, 50, 58, 60, 41, 39, 40, 41, 49, 51,
		 60, 62, 44, 41, 42, 43, 51, 53, 63, 66, 44, 41, 42, 43, 51, 53, 63, 66,
		 44, 42, 42, 43, 51, 54, 64, 67, 47, 44, 44, 45, 53, 56, 66, 69, 48, 45,
		 45, 46, 54, 56, 67, 70, 48, 45, 45, 46, 54, 56, 67, 70, 51, 47, 48, 48,
		 56, 58, 69, 73,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 34, 34, 34,
		 35, 36, 36, 38, 39, 39, 41, 44, 44, 44, 47, 48, 48, 51, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 34, 36,
		 37, 37, 39, 41, 41, 42, 44, 45, 45, 47, 31, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 39, 39, 40, 42,
		 42, 42, 44, 45, 45, 48, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35,
		 35, 35, 36, 37, 37, 37, 38, 38, 38, 40, 40, 40, 41, 43, 43, 43, 45, 46,
		 46, 48, 35, 35, 35, 35, 34, 34, 34, 34, 35, 36, 36, 37, 37, 37, 39, 41,
		 41, 42, 45, 46, 46, 47, 48, 48, 49, 51, 51, 51, 53, 54, 54, 56, 36, 35,
		 35, 35, 35, 34, 34, 35, 36, 36, 36, 37, 38, 38, 40, 42, 42, 43, 47, 48,
		 48, 49, 50, 50, 51, 53, 53, 54, 56, 56, 56, 58, 44, 43, 42, 42, 41, 41,
		 41, 41, 42, 42, 42, 42, 42, 42, 44, 48, 48, 49, 52, 54, 54, 56, 58, 58,
		 60, 63, 63, 64, 66, 67, 67, 69, 47, 46, 45, 45, 45, 44, 44, 44, 44, 45,
		 45, 45, 45, 45, 47, 50, 50, 51, 55, 56, 56, 58, 60, 60, 62, 66, 66, 67,
		 69, 70, 70, 73},
		{/* Chroma */

		 /* Size 4x4 */
		 31, 37, 47, 47, 37, 44, 47, 45, 47, 47, 53, 53, 47, 45, 53, 59,
		 /* Size 8x8 */
		 31, 31, 34, 37, 43, 48, 47, 49, 31, 32, 35, 40, 43, 46, 45, 46, 34, 35,
		 39, 43, 45, 46, 45, 46, 37, 40, 43, 47, 47, 47, 45, 46, 43, 43, 45, 47,
		 49, 50, 50, 50, 48, 46, 46, 47, 50, 53, 55, 55, 47, 45, 45, 45, 50, 55,
		 58, 60, 49, 46, 46, 46, 50, 55, 60, 61,
		 /* Size 16x16 */
		 32, 31, 31, 30, 33, 33, 36, 38, 41, 47, 49, 48, 49, 49, 50, 50, 31, 31,
		 31, 31, 34, 34, 38, 40, 42, 46, 47, 47, 47, 47, 48, 48, 31, 31, 31, 31,
		 34, 35, 39, 40, 42, 46, 47, 46, 46, 46, 47, 47, 30, 31, 31, 32, 34, 35,
		 40, 41, 42, 45, 46, 45, 45, 45, 46, 46, 33, 34, 34, 34, 37, 38, 42, 43,
		 44, 46, 47, 46, 46, 45, 46, 46, 33, 34, 35, 35, 38, 39, 43, 44, 45, 47,
		 47, 46, 46, 45, 46, 46, 36, 38, 39, 40, 42, 43, 47, 47, 47, 47, 48, 46,
		 46, 45, 46, 46, 38, 40, 40, 41, 43, 44, 47, 47, 48, 48, 49, 48, 47, 47,
		 47, 47, 41, 42, 42, 42, 44, 45, 47, 48, 48, 50, 50, 49, 49, 49, 50, 50,
		 47, 46, 46, 45, 46, 47, 47, 48, 50, 52, 52, 52, 52, 52, 53, 53, 49, 47,
		 47, 46, 47, 47, 48, 49, 50, 52, 53, 53, 53, 53, 54, 54, 48, 47, 46, 45,
		 46, 46, 46, 48, 49, 52, 53, 54, 55, 55, 56, 56, 49, 47, 46, 45, 46, 46,
		 46, 47, 49, 52, 53, 55, 55, 57, 57, 58, 49, 47, 46, 45, 45, 45, 45, 47,
		 49, 52, 53, 55, 57, 58, 59, 60, 50, 48, 47, 46, 46, 46, 46, 47, 50, 53,
		 54, 56, 57, 59, 61, 61, 50, 48, 47, 46, 46, 46, 46, 47, 50, 53, 54, 56,
		 58, 60, 61, 61,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 30, 30, 31, 33, 33, 33, 35, 36, 36, 38, 41, 41, 43,
		 47, 49, 49, 49, 48, 48, 49, 49, 49, 49, 50, 50, 50, 51, 31, 31, 31, 31,
		 31, 31, 31, 31, 33, 34, 34, 36, 37, 37, 39, 42, 42, 43, 47, 48, 48, 48,
		 47, 47, 47, 47, 47, 48, 49, 49, 49, 50, 31, 31, 31, 31, 31, 31, 31, 32,
		 34, 34, 34, 37, 38, 38, 40, 42, 42, 43, 46, 47, 47, 47, 47, 47, 47, 47,
		 47, 47, 48, 48, 48, 49, 31, 31, 31, 31, 31, 31, 31, 32, 34, 34, 34, 37,
		 38, 38, 40, 42, 42, 43, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48,
		 48, 49, 31, 31, 31, 31, 31, 31, 31, 32, 34, 35, 35, 37, 39, 39, 40, 42,
		 42, 43, 46, 47, 47, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 48, 30, 31,
		 31, 31, 31, 32, 32, 32, 34, 35, 35, 38, 40, 40, 41, 42, 42, 43, 45, 46,
		 46, 46, 45, 45, 45, 45, 45, 45, 46, 46, 46, 47, 30, 31, 31, 31, 31, 32,
		 32, 32, 34, 35, 35, 38, 40, 40, 41, 42, 42, 43, 45, 46, 46, 46, 45, 45,
		 45, 45, 45, 45, 46, 46, 46, 47, 31, 31, 32, 32, 32, 32, 32, 33, 35, 36,
		 36, 38, 40, 40, 41, 43, 43, 43, 46, 46, 46, 46, 45, 45, 45, 45, 45, 45,
		 46, 46, 46, 47, 33, 33, 34, 34, 34, 34, 34, 35, 37, 38, 38, 41, 42, 42,
		 43, 44, 44, 45, 46, 47, 47, 46, 46, 46, 46, 45, 45, 45, 46, 46, 46, 47,
		 33, 34, 34, 34, 35, 35, 35, 36, 38, 39, 39, 41, 43, 43, 44, 45, 45, 45,
		 47, 47, 47, 46, 46, 46, 46, 45, 45, 45, 46, 46, 46, 47, 33, 34, 34, 34,
		 35, 35, 35, 36, 38, 39, 39, 41, 43, 43, 44, 45, 45, 45, 47, 47, 47, 46,
		 46, 46, 46, 45, 45, 45, 46, 46, 46, 47, 35, 36, 37, 37, 37, 38, 38, 38,
		 41, 41, 41, 44, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 46, 46, 46, 45,
		 45, 45, 46, 46, 46, 47, 36, 37, 38, 38, 39, 40, 40, 40, 42, 43, 43, 46,
		 47, 47, 47, 47, 47, 47, 47, 48, 48, 47, 46, 46, 46, 45, 45, 45, 46, 46,
		 46, 46, 36, 37, 38, 38, 39, 40, 40, 40, 42, 43, 43, 46, 47, 47, 47, 47,
		 47, 47, 47, 48, 48, 47, 46, 46, 46, 45, 45, 45, 46, 46, 46, 46, 38, 39,
		 40, 40, 40, 41, 41, 41, 43, 44, 44, 46, 47, 47, 47, 48, 48, 48, 48, 49,

		 49, 48, 48, 48, 47, 47, 47, 47, 47, 47, 47, 48, 41, 42, 42, 42, 42, 42,
		 42, 43, 44, 45, 45, 46, 47, 47, 48, 48, 48, 49, 50, 50, 50, 50, 49, 49,
		 49, 49, 49, 49, 50, 50, 50, 50, 41, 42, 42, 42, 42, 42, 42, 43, 44, 45,
		 45, 46, 47, 47, 48, 48, 48, 49, 50, 50, 50, 50, 49, 49, 49, 49, 49, 49,
		 50, 50, 50, 50, 43, 43, 43, 43, 43, 43, 43, 43, 45, 45, 45, 46, 47, 47,
		 48, 49, 49, 49, 50, 51, 51, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51,
		 47, 47, 46, 46, 46, 45, 45, 46, 46, 47, 47, 47, 47, 47, 48, 50, 50, 50,
		 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 49, 48, 47, 47,
		 47, 46, 46, 46, 47, 47, 47, 47, 48, 48, 49, 50, 50, 51, 52, 53, 53, 53,
		 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 49, 48, 47, 47, 47, 46, 46, 46,
		 47, 47, 47, 47, 48, 48, 49, 50, 50, 51, 52, 53, 53, 53, 53, 53, 53, 53,
		 53, 53, 54, 54, 54, 54, 49, 48, 47, 47, 46, 46, 46, 46, 46, 46, 46, 47,
		 47, 47, 48, 50, 50, 50, 52, 53, 53, 53, 54, 54, 54, 55, 55, 55, 55, 55,
		 55, 56, 48, 47, 47, 47, 46, 45, 45, 45, 46, 46, 46, 46, 46, 46, 48, 49,
		 49, 50, 52, 53, 53, 54, 54, 54, 55, 55, 55, 56, 56, 56, 56, 57, 48, 47,
		 47, 47, 46, 45, 45, 45, 46, 46, 46, 46, 46, 46, 48, 49, 49, 50, 52, 53,
		 53, 54, 54, 54, 55, 55, 55, 56, 56, 56, 56, 57, 49, 47, 47, 47, 46, 45,
		 45, 45, 46, 46, 46, 46, 46, 46, 47, 49, 49, 50, 52, 53, 53, 54, 55, 55,
		 55, 57, 57, 57, 57, 58, 58, 58, 49, 47, 47, 47, 46, 45, 45, 45, 45, 45,
		 45, 45, 45, 45, 47, 49, 49, 50, 52, 53, 53, 55, 55, 55, 57, 58, 58, 59,
		 59, 60, 60, 60, 49, 47, 47, 47, 46, 45, 45, 45, 45, 45, 45, 45, 45, 45,
		 47, 49, 49, 50, 52, 53, 53, 55, 55, 55, 57, 58, 58, 59, 59, 60, 60, 60,
		 49, 48, 47, 47, 46, 45, 45, 45, 45, 45, 45, 45, 45, 45, 47, 49, 49, 50,
		 52, 53, 53, 55, 56, 56, 57, 59, 59, 59, 60, 60, 60, 61, 50, 49, 48, 48,
		 47, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 50, 50, 50, 53, 54, 54, 55,
		 56, 56, 57, 59, 59, 60, 61, 61, 61, 62, 50, 49, 48, 48, 47, 46, 46, 46,
		 46, 46, 46, 46, 46, 46, 47, 50, 50, 50, 53, 54, 54, 55, 56, 56, 58, 60,
		 60, 60, 61, 61, 61, 63, 50, 49, 48, 48, 47, 46, 46, 46, 46, 46, 46, 46,
		 46, 46, 47, 50, 50, 50, 53, 54, 54, 55, 56, 56, 58, 60, 60, 60, 61, 61,
		 61, 63, 51, 50, 49, 49, 48, 47, 47, 47, 47, 47, 47, 47, 46, 46, 48, 50,
		 50, 51, 53, 54, 54, 56, 57, 57, 58, 60, 60, 61, 62, 63, 63, 64,
		 /* Size 4x8 */
		 31, 38, 47, 48, 31, 40, 46, 45, 35, 43, 47, 46, 39, 47, 47, 45, 43, 47,
		 50, 50, 47, 47, 53, 55, 46, 46, 53, 58, 48, 46, 54, 59,
		 /* Size 8x4 */
		 31, 31, 35, 39, 43, 47, 46, 48, 38, 40, 43, 47, 47, 47, 46, 46, 47, 46,
		 47, 47, 50, 53, 53, 54, 48, 45, 46, 45, 50, 55, 58, 59,
		 /* Size 8x16 */
		 32, 31, 33, 37, 45, 48, 49, 50, 31, 31, 34, 38, 45, 47, 47, 48, 31, 32,
		 34, 39, 45, 46, 46, 47, 30, 32, 35, 40, 44, 46, 45, 46, 33, 35, 37, 42,
		 46, 47, 45, 46, 33, 36, 38, 43, 46, 47, 46, 46, 37, 40, 43, 47, 47, 47,
		 45, 46, 39, 41, 43, 47, 48, 48, 47, 47, 42, 43, 44, 47, 49, 50, 49, 50,
		 47, 46, 46, 48, 51, 52, 53, 53, 49, 46, 47, 48, 52, 53, 53, 54, 48, 46,
		 46, 47, 51, 53, 56, 56, 48, 45, 46, 46, 51, 53, 57, 57, 49, 45, 45, 46,
		 51, 53, 58, 59, 50, 46, 46, 46, 52, 54, 59, 61, 50, 46, 46, 46, 52, 54,
		 59, 61,
		 /* Size 16x8 */
		 32, 31, 31, 30, 33, 33, 37, 39, 42, 47, 49, 48, 48, 49, 50, 50, 31, 31,
		 32, 32, 35, 36, 40, 41, 43, 46, 46, 46, 45, 45, 46, 46, 33, 34, 34, 35,
		 37, 38, 43, 43, 44, 46, 47, 46, 46, 45, 46, 46, 37, 38, 39, 40, 42, 43,

		 47, 47, 47, 48, 48, 47, 46, 46, 46, 46, 45, 45, 45, 44, 46, 46, 47, 48,
		 49, 51, 52, 51, 51, 51, 52, 52, 48, 47, 46, 46, 47, 47, 47, 48, 50, 52,
		 53, 53, 53, 53, 54, 54, 49, 47, 46, 45, 45, 46, 45, 47, 49, 53, 53, 56,
		 57, 58, 59, 59, 50, 48, 47, 46, 46, 46, 46, 47, 50, 53, 54, 56, 57, 59,
		 61, 61,
		 /* Size 16x32 */
		 32, 31, 31, 31, 33, 37, 37, 38, 45, 48, 48, 49, 49, 49, 50, 52, 31, 31,
		 31, 31, 33, 38, 38, 39, 45, 47, 47, 48, 48, 48, 49, 51, 31, 31, 31, 31,
		 34, 38, 38, 40, 45, 47, 47, 47, 47, 47, 48, 50, 31, 31, 31, 31, 34, 38,
		 38, 40, 45, 47, 47, 47, 47, 47, 48, 50, 31, 31, 32, 32, 34, 39, 39, 40,
		 45, 46, 46, 46, 46, 46, 47, 49, 30, 31, 32, 32, 35, 40, 40, 41, 44, 46,
		 46, 45, 45, 45, 46, 48, 30, 31, 32, 32, 35, 40, 40, 41, 44, 46, 46, 45,
		 45, 45, 46, 48, 31, 32, 33, 33, 35, 40, 40, 41, 45, 46, 46, 45, 45, 45,
		 46, 48, 33, 34, 35, 35, 37, 42, 42, 43, 46, 47, 47, 46, 45, 45, 46, 47,
		 33, 35, 36, 36, 38, 43, 43, 44, 46, 47, 47, 46, 46, 46, 46, 47, 33, 35,
		 36, 36, 38, 43, 43, 44, 46, 47, 47, 46, 46, 46, 46, 47, 35, 37, 38, 38,
		 41, 45, 45, 46, 47, 47, 47, 46, 45, 45, 46, 47, 37, 39, 40, 40, 43, 47,
		 47, 47, 47, 47, 47, 46, 45, 45, 46, 47, 37, 39, 40, 40, 43, 47, 47, 47,
		 47, 47, 47, 46, 45, 45, 46, 47, 39, 40, 41, 41, 43, 47, 47, 47, 48, 48,
		 48, 47, 47, 47, 47, 48, 42, 42, 43, 43, 44, 47, 47, 48, 49, 50, 50, 49,
		 49, 49, 50, 50, 42, 42, 43, 43, 44, 47, 47, 48, 49, 50, 50, 49, 49, 49,
		 50, 50, 43, 43, 43, 43, 45, 47, 47, 48, 50, 50, 50, 50, 50, 50, 50, 51,
		 47, 46, 46, 46, 46, 48, 48, 48, 51, 52, 52, 52, 53, 53, 53, 53, 49, 47,
		 46, 46, 47, 48, 48, 49, 52, 53, 53, 53, 53, 53, 54, 54, 49, 47, 46, 46,
		 47, 48, 48, 49, 52, 53, 53, 53, 53, 53, 54, 54, 48, 47, 46, 46, 46, 47,
		 47, 48, 52, 53, 53, 54, 55, 55, 55, 56, 48, 47, 46, 46, 46, 47, 47, 48,
		 51, 53, 53, 54, 56, 56, 56, 57, 48, 47, 46, 46, 46, 47, 47, 48, 51, 53,
		 53, 54, 56, 56, 56, 57, 48, 47, 45, 45, 46, 46, 46, 47, 51, 53, 53, 55,
		 57, 57, 57, 59, 49, 46, 45, 45, 45, 46, 46, 47, 51, 53, 53, 56, 58, 58,
		 59, 61, 49, 46, 45, 45, 45, 46, 46, 47, 51, 53, 53, 56, 58, 58, 59, 61,
		 49, 47, 45, 45, 45, 46, 46, 47, 52, 53, 53, 56, 58, 58, 60, 62, 50, 48,
		 46, 46, 46, 46, 46, 48, 52, 54, 54, 57, 59, 59, 61, 63, 50, 48, 46, 46,
		 46, 46, 46, 48, 52, 54, 54, 57, 59, 59, 61, 64, 50, 48, 46, 46, 46, 46,
		 46, 48, 52, 54, 54, 57, 59, 59, 61, 64, 51, 49, 47, 47, 47, 47, 47, 48,
		 52, 54, 54, 58, 60, 60, 62, 65,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 30, 30, 31, 33, 33, 33, 35, 37, 37, 39, 42, 42, 43,
		 47, 49, 49, 48, 48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 31, 31, 31, 31,
		 31, 31, 31, 32, 34, 35, 35, 37, 39, 39, 40, 42, 42, 43, 46, 47, 47, 47,
		 47, 47, 47, 46, 46, 47, 48, 48, 48, 49, 31, 31, 31, 31, 32, 32, 32, 33,
		 35, 36, 36, 38, 40, 40, 41, 43, 43, 43, 46, 46, 46, 46, 46, 46, 45, 45,
		 45, 45, 46, 46, 46, 47, 31, 31, 31, 31, 32, 32, 32, 33, 35, 36, 36, 38,
		 40, 40, 41, 43, 43, 43, 46, 46, 46, 46, 46, 46, 45, 45, 45, 45, 46, 46,
		 46, 47, 33, 33, 34, 34, 34, 35, 35, 35, 37, 38, 38, 41, 43, 43, 43, 44,
		 44, 45, 46, 47, 47, 46, 46, 46, 46, 45, 45, 45, 46, 46, 46, 47, 37, 38,
		 38, 38, 39, 40, 40, 40, 42, 43, 43, 45, 47, 47, 47, 47, 47, 47, 48, 48,
		 48, 47, 47, 47, 46, 46, 46, 46, 46, 46, 46, 47, 37, 38, 38, 38, 39, 40,
		 40, 40, 42, 43, 43, 45, 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 47, 47,
		 46, 46, 46, 46, 46, 46, 46, 47, 38, 39, 40, 40, 40, 41, 41, 41, 43, 44,
		 44, 46, 47, 47, 47, 48, 48, 48, 48, 49, 49, 48, 48, 48, 47, 47, 47, 47,

		 48, 48, 48, 48, 45, 45, 45, 45, 45, 44, 44, 45, 46, 46, 46, 47, 47, 47,
		 48, 49, 49, 50, 51, 52, 52, 52, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52,
		 48, 47, 47, 47, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 48, 50, 50, 50,
		 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 48, 47, 47, 47,
		 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 48, 50, 50, 50, 52, 53, 53, 53,
		 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 49, 48, 47, 47, 46, 45, 45, 45,
		 46, 46, 46, 46, 46, 46, 47, 49, 49, 50, 52, 53, 53, 54, 54, 54, 55, 56,
		 56, 56, 57, 57, 57, 58, 49, 48, 47, 47, 46, 45, 45, 45, 45, 46, 46, 45,
		 45, 45, 47, 49, 49, 50, 53, 53, 53, 55, 56, 56, 57, 58, 58, 58, 59, 59,
		 59, 60, 49, 48, 47, 47, 46, 45, 45, 45, 45, 46, 46, 45, 45, 45, 47, 49,
		 49, 50, 53, 53, 53, 55, 56, 56, 57, 58, 58, 58, 59, 59, 59, 60, 50, 49,
		 48, 48, 47, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 50, 50, 50, 53, 54,
		 54, 55, 56, 56, 57, 59, 59, 60, 61, 61, 61, 62, 52, 51, 50, 50, 49, 48,
		 48, 48, 47, 47, 47, 47, 47, 47, 48, 50, 50, 51, 53, 54, 54, 56, 57, 57,
		 59, 61, 61, 62, 63, 64, 64, 65,
		 /* Size 4x16 */
		 31, 37, 48, 49, 31, 38, 47, 47, 31, 39, 46, 46, 31, 40, 46, 45, 34, 42,
		 47, 45, 35, 43, 47, 46, 39, 47, 47, 45, 40, 47, 48, 47, 42, 47, 50, 49,
		 46, 48, 52, 53, 47, 48, 53, 53, 47, 47, 53, 56, 47, 46, 53, 57, 46, 46,
		 53, 58, 48, 46, 54, 59, 48, 46, 54, 59,
		 /* Size 16x4 */
		 31, 31, 31, 31, 34, 35, 39, 40, 42, 46, 47, 47, 47, 46, 48, 48, 37, 38,
		 39, 40, 42, 43, 47, 47, 47, 48, 48, 47, 46, 46, 46, 46, 48, 47, 46, 46,
		 47, 47, 47, 48, 50, 52, 53, 53, 53, 53, 54, 54, 49, 47, 46, 45, 45, 46,
		 45, 47, 49, 53, 53, 56, 57, 58, 59, 59,
		 /* Size 8x32 */
		 32, 31, 33, 37, 45, 48, 49, 50, 31, 31, 33, 38, 45, 47, 48, 49, 31, 31,
		 34, 38, 45, 47, 47, 48, 31, 31, 34, 38, 45, 47, 47, 48, 31, 32, 34, 39,
		 45, 46, 46, 47, 30, 32, 35, 40, 44, 46, 45, 46, 30, 32, 35, 40, 44, 46,
		 45, 46, 31, 33, 35, 40, 45, 46, 45, 46, 33, 35, 37, 42, 46, 47, 45, 46,
		 33, 36, 38, 43, 46, 47, 46, 46, 33, 36, 38, 43, 46, 47, 46, 46, 35, 38,
		 41, 45, 47, 47, 45, 46, 37, 40, 43, 47, 47, 47, 45, 46, 37, 40, 43, 47,
		 47, 47, 45, 46, 39, 41, 43, 47, 48, 48, 47, 47, 42, 43, 44, 47, 49, 50,
		 49, 50, 42, 43, 44, 47, 49, 50, 49, 50, 43, 43, 45, 47, 50, 50, 50, 50,
		 47, 46, 46, 48, 51, 52, 53, 53, 49, 46, 47, 48, 52, 53, 53, 54, 49, 46,
		 47, 48, 52, 53, 53, 54, 48, 46, 46, 47, 52, 53, 55, 55, 48, 46, 46, 47,
		 51, 53, 56, 56, 48, 46, 46, 47, 51, 53, 56, 56, 48, 45, 46, 46, 51, 53,
		 57, 57, 49, 45, 45, 46, 51, 53, 58, 59, 49, 45, 45, 46, 51, 53, 58, 59,
		 49, 45, 45, 46, 52, 53, 58, 60, 50, 46, 46, 46, 52, 54, 59, 61, 50, 46,
		 46, 46, 52, 54, 59, 61, 50, 46, 46, 46, 52, 54, 59, 61, 51, 47, 47, 47,
		 52, 54, 60, 62,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 30, 30, 31, 33, 33, 33, 35, 37, 37, 39, 42, 42, 43,
		 47, 49, 49, 48, 48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 31, 31, 31, 31,
		 32, 32, 32, 33, 35, 36, 36, 38, 40, 40, 41, 43, 43, 43, 46, 46, 46, 46,
		 46, 46, 45, 45, 45, 45, 46, 46, 46, 47, 33, 33, 34, 34, 34, 35, 35, 35,
		 37, 38, 38, 41, 43, 43, 43, 44, 44, 45, 46, 47, 47, 46, 46, 46, 46, 45,
		 45, 45, 46, 46, 46, 47, 37, 38, 38, 38, 39, 40, 40, 40, 42, 43, 43, 45,
		 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 47, 47, 46, 46, 46, 46, 46, 46,
		 46, 47, 45, 45, 45, 45, 45, 44, 44, 45, 46, 46, 46, 47, 47, 47, 48, 49,

		 49, 50, 51, 52, 52, 52, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 48, 47,
		 47, 47, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 48, 50, 50, 50, 52, 53,
		 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 49, 48, 47, 47, 46, 45,
		 45, 45, 45, 46, 46, 45, 45, 45, 47, 49, 49, 50, 53, 53, 53, 55, 56, 56,
		 57, 58, 58, 58, 59, 59, 59, 60, 50, 49, 48, 48, 47, 46, 46, 46, 46, 46,
		 46, 46, 46, 46, 47, 50, 50, 50, 53, 54, 54, 55, 56, 56, 57, 59, 59, 60,
		 61, 61, 61, 62},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 32, 34, 38, 32, 33, 35, 39, 34, 35, 39, 45, 38, 39, 45, 54,
		 /* Size 8x8 */
		 31, 31, 32, 32, 33, 34, 37, 41, 31, 32, 32, 32, 33, 34, 36, 39, 32, 32,
		 32, 33, 34, 35, 37, 40, 32, 32, 33, 34, 35, 36, 38, 41, 33, 33, 34, 35,
		 37, 39, 41, 44, 34, 34, 35, 36, 39, 43, 46, 49, 37, 36, 37, 38, 41, 46,
		 51, 54, 41, 39, 40, 41, 44, 49, 54, 58,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 34, 34, 36, 36, 39, 39, 44, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 34, 34, 35, 35, 38, 38, 42, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 34, 34, 35, 35, 38, 38, 42, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 37, 37, 41, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 34, 37, 37, 41, 31, 32, 32, 32, 32, 33, 33, 34, 34, 35,
		 35, 36, 36, 39, 39, 42, 31, 32, 32, 32, 32, 33, 33, 34, 34, 35, 35, 36,
		 36, 39, 39, 42, 32, 32, 32, 32, 32, 34, 34, 35, 35, 37, 37, 38, 38, 40,
		 40, 42, 32, 32, 32, 32, 32, 34, 34, 35, 35, 37, 37, 38, 38, 40, 40, 42,
		 34, 34, 34, 33, 33, 35, 35, 37, 37, 39, 39, 42, 42, 45, 45, 47, 34, 34,
		 34, 33, 33, 35, 35, 37, 37, 39, 39, 42, 42, 45, 45, 47, 36, 35, 35, 34,
		 34, 36, 36, 38, 38, 42, 42, 48, 48, 50, 50, 54, 36, 35, 35, 34, 34, 36,
		 36, 38, 38, 42, 42, 48, 48, 50, 50, 54, 39, 38, 38, 37, 37, 39, 39, 40,
		 40, 45, 45, 50, 50, 54, 54, 58, 39, 38, 38, 37, 37, 39, 39, 40, 40, 45,
		 45, 50, 50, 54, 54, 58, 44, 42, 42, 41, 41, 42, 42, 42, 42, 47, 47, 54,
		 54, 58, 58, 63,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 33,
		 34, 34, 34, 35, 36, 36, 36, 37, 39, 39, 39, 41, 44, 44, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 34,
		 35, 35, 35, 37, 39, 39, 39, 41, 43, 43, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 34, 35, 35, 35, 37,
		 38, 38, 38, 40, 42, 42, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 34, 34, 34, 34, 35, 35, 35, 37, 38, 38, 38, 40,
		 42, 42, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 34, 34, 34, 34, 35, 35, 35, 37, 38, 38, 38, 40, 42, 42, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34,
		 34, 34, 35, 35, 35, 36, 38, 38, 38, 39, 41, 41, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34,
		 34, 36, 37, 37, 37, 39, 41, 41, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 36, 37, 37,
		 37, 39, 41, 41, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 36, 37, 37, 37, 39, 41, 41,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 34,
		 34, 34, 34, 35, 35, 35, 35, 37, 38, 38, 38, 40, 41, 41, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 36,
		 36, 36, 36, 38, 39, 39, 39, 40, 42, 42, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 36, 36, 36, 36, 38,
		 39, 39, 39, 40, 42, 42, 31, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 33, 33, 34, 34, 34, 34, 35, 35, 35, 36, 36, 36, 36, 38, 39, 39, 39, 40,
		 42, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34,
		 34, 35, 36, 36, 36, 36, 37, 37, 37, 38, 40, 40, 40, 41, 42, 42, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 34, 35, 35, 35, 36, 37, 37,
		 37, 37, 38, 38, 38, 39, 40, 40, 40, 41, 42, 42, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 34, 34, 34, 34, 35, 35, 35, 36, 37, 37, 37, 37, 38, 38,
		 38, 39, 40, 40, 40, 41, 42, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 34, 34, 34, 34, 35, 35, 35, 36, 37, 37, 37, 37, 38, 38, 38, 39, 40, 40,
		 40, 41, 42, 42, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 35,
		 36, 36, 36, 37, 38, 38, 38, 39, 40, 40, 40, 41, 42, 42, 42, 44, 45, 45,
		 34, 34, 34, 34, 34, 34, 33, 33, 33, 34, 35, 35, 35, 36, 37, 37, 37, 38,
		 39, 39, 39, 41, 42, 42, 42, 44, 45, 45, 45, 46, 47, 47, 34, 34, 34, 34,
		 34, 34, 33, 33, 33, 34, 35, 35, 35, 36, 37, 37, 37, 38, 39, 39, 39, 41,
		 42, 42, 42, 44, 45, 45, 45, 46, 47, 47, 34, 34, 34, 34, 34, 34, 33, 33,
		 33, 34, 35, 35, 35, 36, 37, 37, 37, 38, 39, 39, 39, 41, 42, 42, 42, 44,
		 45, 45, 45, 46, 47, 47, 35, 34, 34, 34, 34, 34, 34, 34, 34, 35, 36, 36,
		 36, 36, 37, 37, 37, 39, 41, 41, 41, 43, 45, 45, 45, 46, 47, 47, 47, 49,
		 50, 50, 36, 35, 35, 35, 35, 35, 34, 34, 34, 35, 36, 36, 36, 37, 38, 38,
		 38, 40, 42, 42, 42, 45, 48, 48, 48, 49, 50, 50, 50, 52, 54, 54, 36, 35,
		 35, 35, 35, 35, 34, 34, 34, 35, 36, 36, 36, 37, 38, 38, 38, 40, 42, 42,
		 42, 45, 48, 48, 48, 49, 50, 50, 50, 52, 54, 54, 36, 35, 35, 35, 35, 35,
		 34, 34, 34, 35, 36, 36, 36, 37, 38, 38, 38, 40, 42, 42, 42, 45, 48, 48,
		 48, 49, 50, 50, 50, 52, 54, 54, 37, 37, 37, 37, 37, 36, 36, 36, 36, 37,
		 38, 38, 38, 38, 39, 39, 39, 41, 44, 44, 44, 46, 49, 49, 49, 51, 52, 52,
		 52, 54, 56, 56, 39, 39, 38, 38, 38, 38, 37, 37, 37, 38, 39, 39, 39, 40,
		 40, 40, 40, 42, 45, 45, 45, 47, 50, 50, 50, 52, 54, 54, 54, 56, 58, 58,
		 39, 39, 38, 38, 38, 38, 37, 37, 37, 38, 39, 39, 39, 40, 40, 40, 40, 42,
		 45, 45, 45, 47, 50, 50, 50, 52, 54, 54, 54, 56, 58, 58, 39, 39, 38, 38,
		 38, 38, 37, 37, 37, 38, 39, 39, 39, 40, 40, 40, 40, 42, 45, 45, 45, 47,
		 50, 50, 50, 52, 54, 54, 54, 56, 58, 58, 41, 41, 40, 40, 40, 39, 39, 39,
		 39, 40, 40, 40, 40, 41, 41, 41, 41, 44, 46, 46, 46, 49, 52, 52, 52, 54,
		 56, 56, 56, 58, 60, 60, 44, 43, 42, 42, 42, 41, 41, 41, 41, 41, 42, 42,
		 42, 42, 42, 42, 42, 45, 47, 47, 47, 50, 54, 54, 54, 56, 58, 58, 58, 60,
		 63, 63, 44, 43, 42, 42, 42, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42,
		 42, 45, 47, 47, 47, 50, 54, 54, 54, 56, 58, 58, 58, 60, 63, 63,
		 /* Size 4x8 */
		 31, 32, 34, 39, 32, 32, 34, 38, 32, 33, 34, 38, 32, 33, 36, 40, 33, 34,
		 38, 42, 34, 36, 41, 47, 37, 38, 44, 52, 40, 40, 46, 56,
		 /* Size 8x4 */
		 31, 32, 32, 32, 33, 34, 37, 40, 32, 32, 33, 33, 34, 36, 38, 40, 34, 34,
		 34, 36, 38, 41, 44, 46, 39, 38, 38, 40, 42, 47, 52, 56,
		 /* Size 8x16 */
		 32, 31, 31, 32, 32, 36, 36, 44, 31, 32, 32, 32, 32, 35, 35, 42, 31, 32,
		 32, 32, 32, 35, 35, 42, 31, 32, 32, 33, 33, 34, 34, 41, 31, 32, 32, 33,
		 33, 34, 34, 41, 32, 32, 32, 34, 34, 36, 36, 42, 32, 32, 32, 34, 34, 36,
		 36, 42, 32, 33, 33, 35, 35, 38, 38, 42, 32, 33, 33, 35, 35, 38, 38, 42,
		 34, 34, 34, 37, 37, 42, 42, 48, 34, 34, 34, 37, 37, 42, 42, 48, 36, 34,
		 34, 38, 38, 48, 48, 54, 36, 34, 34, 38, 38, 48, 48, 54, 39, 37, 37, 40,
		 40, 50, 50, 58, 39, 37, 37, 40, 40, 50, 50, 58, 44, 41, 41, 43, 43, 53,
		 53, 63,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 32, 32, 32, 32, 34, 34, 36, 36, 39, 39, 44, 31, 32,
		 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 34, 37, 37, 41, 31, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 34, 34, 37, 37, 41, 32, 32, 32, 33, 33, 34,
		 34, 35, 35, 37, 37, 38, 38, 40, 40, 43, 32, 32, 32, 33, 33, 34, 34, 35,
		 35, 37, 37, 38, 38, 40, 40, 43, 36, 35, 35, 34, 34, 36, 36, 38, 38, 42,
		 42, 48, 48, 50, 50, 53, 36, 35, 35, 34, 34, 36, 36, 38, 38, 42, 42, 48,
		 48, 50, 50, 53, 44, 42, 42, 41, 41, 42, 42, 42, 42, 48, 48, 54, 54, 58,
		 58, 63,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 32, 32, 32, 32, 34, 36, 36, 36, 39, 44, 44, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 34, 35, 35, 35, 39, 43, 43, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 34, 35, 35, 35, 38, 42, 42, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 34, 35, 35, 35, 38, 42, 42, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 34, 35, 35, 35, 38, 42, 42, 31, 32, 32, 32, 32, 32, 32, 32, 32, 34,
		 35, 35, 35, 38, 41, 41, 31, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34,
		 34, 37, 41, 41, 31, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 37,
		 41, 41, 31, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 37, 41, 41,
		 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 35, 35, 35, 38, 41, 41, 32, 32,
		 32, 32, 32, 33, 34, 34, 34, 35, 36, 36, 36, 39, 42, 42, 32, 32, 32, 32,
		 32, 33, 34, 34, 34, 35, 36, 36, 36, 39, 42, 42, 32, 32, 32, 32, 32, 33,
		 34, 34, 34, 35, 36, 36, 36, 39, 42, 42, 32, 32, 32, 32, 32, 33, 34, 34,
		 34, 36, 37, 37, 37, 40, 42, 42, 32, 32, 33, 33, 33, 34, 35, 35, 35, 37,
		 38, 38, 38, 40, 42, 42, 32, 32, 33, 33, 33, 34, 35, 35, 35, 37, 38, 38,
		 38, 40, 42, 42, 32, 32, 33, 33, 33, 34, 35, 35, 35, 37, 38, 38, 38, 40,
		 42, 42, 33, 33, 33, 33, 33, 34, 36, 36, 36, 38, 40, 40, 40, 42, 45, 45,
		 34, 34, 34, 34, 34, 35, 37, 37, 37, 39, 42, 42, 42, 45, 48, 48, 34, 34,
		 34, 34, 34, 35, 37, 37, 37, 39, 42, 42, 42, 45, 48, 48, 34, 34, 34, 34,
		 34, 35, 37, 37, 37, 39, 42, 42, 42, 45, 48, 48, 35, 34, 34, 34, 34, 36,
		 37, 37, 37, 41, 45, 45, 45, 47, 50, 50, 36, 35, 34, 34, 34, 36, 38, 38,
		 38, 43, 48, 48, 48, 51, 54, 54, 36, 35, 34, 34, 34, 36, 38, 38, 38, 43,
		 48, 48, 48, 51, 54, 54, 36, 35, 34, 34, 34, 36, 38, 38, 38, 43, 48, 48,
		 48, 51, 54, 54, 37, 37, 36, 36, 36, 38, 39, 39, 39, 44, 49, 49, 49, 52,
		 56, 56, 39, 38, 37, 37, 37, 39, 40, 40, 40, 45, 50, 50, 50, 54, 58, 58,
		 39, 38, 37, 37, 37, 39, 40, 40, 40, 45, 50, 50, 50, 54, 58, 58, 39, 38,
		 37, 37, 37, 39, 40, 40, 40, 45, 50, 50, 50, 54, 58, 58, 41, 40, 39, 39,
		 39, 40, 42, 42, 42, 46, 52, 52, 52, 56, 60, 60, 44, 42, 41, 41, 41, 42,
		 43, 43, 43, 48, 53, 53, 53, 58, 63, 63, 44, 42, 41, 41, 41, 42, 43, 43,
		 43, 48, 53, 53, 53, 58, 63, 63,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33,
		 34, 34, 34, 35, 36, 36, 36, 37, 39, 39, 39, 41, 44, 44, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 34,
		 35, 35, 35, 37, 38, 38, 38, 40, 42, 42, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 36,
		 37, 37, 37, 39, 41, 41, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 36, 37, 37, 37, 39,
		 41, 41, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 33, 33, 34, 34, 34, 34, 34, 34, 34, 36, 37, 37, 37, 39, 41, 41, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35,
		 35, 36, 36, 36, 36, 38, 39, 39, 39, 40, 42, 42, 32, 32, 32, 32, 32, 32,
		 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 36, 37, 37, 37, 37, 38, 38,
		 38, 39, 40, 40, 40, 42, 43, 43, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33,
		 34, 34, 34, 34, 35, 35, 35, 36, 37, 37, 37, 37, 38, 38, 38, 39, 40, 40,
		 40, 42, 43, 43, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34,
		 35, 35, 35, 36, 37, 37, 37, 37, 38, 38, 38, 39, 40, 40, 40, 42, 43, 43,
		 34, 34, 34, 34, 34, 34, 33, 33, 33, 34, 35, 35, 35, 36, 37, 37, 37, 38,
		 39, 39, 39, 41, 43, 43, 43, 44, 45, 45, 45, 46, 48, 48, 36, 35, 35, 35,
		 35, 35, 34, 34, 34, 35, 36, 36, 36, 37, 38, 38, 38, 40, 42, 42, 42, 45,
		 48, 48, 48, 49, 50, 50, 50, 52, 53, 53, 36, 35, 35, 35, 35, 35, 34, 34,
		 34, 35, 36, 36, 36, 37, 38, 38, 38, 40, 42, 42, 42, 45, 48, 48, 48, 49,
		 50, 50, 50, 52, 53, 53, 36, 35, 35, 35, 35, 35, 34, 34, 34, 35, 36, 36,
		 36, 37, 38, 38, 38, 40, 42, 42, 42, 45, 48, 48, 48, 49, 50, 50, 50, 52,
		 53, 53, 39, 39, 38, 38, 38, 38, 37, 37, 37, 38, 39, 39, 39, 40, 40, 40,
		 40, 42, 45, 45, 45, 47, 51, 51, 51, 52, 54, 54, 54, 56, 58, 58, 44, 43,
		 42, 42, 42, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 45, 48, 48,
		 48, 50, 54, 54, 54, 56, 58, 58, 58, 60, 63, 63, 44, 43, 42, 42, 42, 41,
		 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 45, 48, 48, 48, 50, 54, 54,
		 54, 56, 58, 58, 58, 60, 63, 63,
		 /* Size 4x16 */
		 31, 32, 34, 39, 32, 32, 34, 38, 32, 32, 34, 38, 32, 32, 33, 37, 32, 32,
		 33, 37, 32, 33, 35, 39, 32, 33, 35, 39, 32, 34, 37, 40, 32, 34, 37, 40,
		 34, 35, 39, 45, 34, 35, 39, 45, 35, 36, 43, 51, 35, 36, 43, 51, 38, 39,
		 45, 54, 38, 39, 45, 54, 42, 42, 48, 58,
		 /* Size 16x4 */
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34, 35, 35, 38, 38, 42, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 39, 39, 42, 34, 34, 34, 33,
		 33, 35, 35, 37, 37, 39, 39, 43, 43, 45, 45, 48, 39, 38, 38, 37, 37, 39,
		 39, 40, 40, 45, 45, 51, 51, 54, 54, 58,
		 /* Size 8x32 */
		 32, 31, 31, 32, 32, 36, 36, 44, 31, 31, 31, 32, 32, 35, 35, 43, 31, 32,
		 32, 32, 32, 35, 35, 42, 31, 32, 32, 32, 32, 35, 35, 42, 31, 32, 32, 32,
		 32, 35, 35, 42, 31, 32, 32, 32, 32, 35, 35, 41, 31, 32, 32, 33, 33, 34,
		 34, 41, 31, 32, 32, 33, 33, 34, 34, 41, 31, 32, 32, 33, 33, 34, 34, 41,
		 31, 32, 32, 33, 33, 35, 35, 41, 32, 32, 32, 34, 34, 36, 36, 42, 32, 32,
		 32, 34, 34, 36, 36, 42, 32, 32, 32, 34, 34, 36, 36, 42, 32, 32, 32, 34,
		 34, 37, 37, 42, 32, 33, 33, 35, 35, 38, 38, 42, 32, 33, 33, 35, 35, 38,
		 38, 42, 32, 33, 33, 35, 35, 38, 38, 42, 33, 33, 33, 36, 36, 40, 40, 45,
		 34, 34, 34, 37, 37, 42, 42, 48, 34, 34, 34, 37, 37, 42, 42, 48, 34, 34,
		 34, 37, 37, 42, 42, 48, 35, 34, 34, 37, 37, 45, 45, 50, 36, 34, 34, 38,
		 38, 48, 48, 54, 36, 34, 34, 38, 38, 48, 48, 54, 36, 34, 34, 38, 38, 48,
		 48, 54, 37, 36, 36, 39, 39, 49, 49, 56, 39, 37, 37, 40, 40, 50, 50, 58,
		 39, 37, 37, 40, 40, 50, 50, 58, 39, 37, 37, 40, 40, 50, 50, 58, 41, 39,
		 39, 42, 42, 52, 52, 60, 44, 41, 41, 43, 43, 53, 53, 63, 44, 41, 41, 43,

		 43, 53, 53, 63,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33,
		 34, 34, 34, 35, 36, 36, 36, 37, 39, 39, 39, 41, 44, 44, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34,
		 34, 34, 34, 36, 37, 37, 37, 39, 41, 41, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 36,
		 37, 37, 37, 39, 41, 41, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34,
		 34, 34, 35, 35, 35, 36, 37, 37, 37, 37, 38, 38, 38, 39, 40, 40, 40, 42,
		 43, 43, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35,
		 35, 36, 37, 37, 37, 37, 38, 38, 38, 39, 40, 40, 40, 42, 43, 43, 36, 35,
		 35, 35, 35, 35, 34, 34, 34, 35, 36, 36, 36, 37, 38, 38, 38, 40, 42, 42,
		 42, 45, 48, 48, 48, 49, 50, 50, 50, 52, 53, 53, 36, 35, 35, 35, 35, 35,
		 34, 34, 34, 35, 36, 36, 36, 37, 38, 38, 38, 40, 42, 42, 42, 45, 48, 48,
		 48, 49, 50, 50, 50, 52, 53, 53, 44, 43, 42, 42, 42, 41, 41, 41, 41, 41,
		 42, 42, 42, 42, 42, 42, 42, 45, 48, 48, 48, 50, 54, 54, 54, 56, 58, 58,
		 58, 60, 63, 63},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 34, 42, 47, 34, 39, 45, 46, 42, 45, 48, 49, 47, 46, 49, 54,
		 /* Size 8x8 */
		 31, 31, 32, 35, 39, 45, 48, 48, 31, 31, 33, 37, 41, 44, 46, 46, 32, 33,
		 35, 39, 42, 45, 46, 45, 35, 37, 39, 43, 45, 47, 47, 46, 39, 41, 42, 45,
		 47, 48, 48, 47, 45, 44, 45, 47, 48, 50, 51, 51, 48, 46, 46, 47, 48, 51,
		 53, 54, 48, 46, 45, 46, 47, 51, 54, 56,
		 /* Size 16x16 */
		 32, 31, 31, 30, 30, 33, 33, 36, 36, 41, 41, 49, 49, 48, 48, 49, 31, 31,
		 31, 31, 31, 34, 34, 38, 38, 42, 42, 47, 47, 47, 47, 47, 31, 31, 31, 31,
		 31, 34, 34, 38, 38, 42, 42, 47, 47, 47, 47, 47, 30, 31, 31, 32, 32, 35,
		 35, 40, 40, 42, 42, 46, 46, 45, 45, 45, 30, 31, 31, 32, 32, 35, 35, 40,
		 40, 42, 42, 46, 46, 45, 45, 45, 33, 34, 34, 35, 35, 39, 39, 43, 43, 45,
		 45, 47, 47, 46, 46, 45, 33, 34, 34, 35, 35, 39, 39, 43, 43, 45, 45, 47,
		 47, 46, 46, 45, 36, 38, 38, 40, 40, 43, 43, 47, 47, 47, 47, 48, 48, 46,
		 46, 45, 36, 38, 38, 40, 40, 43, 43, 47, 47, 47, 47, 48, 48, 46, 46, 45,
		 41, 42, 42, 42, 42, 45, 45, 47, 47, 48, 48, 50, 50, 49, 49, 49, 41, 42,
		 42, 42, 42, 45, 45, 47, 47, 48, 48, 50, 50, 49, 49, 49, 49, 47, 47, 46,
		 46, 47, 47, 48, 48, 50, 50, 53, 53, 53, 53, 53, 49, 47, 47, 46, 46, 47,
		 47, 48, 48, 50, 50, 53, 53, 53, 53, 53, 48, 47, 47, 45, 45, 46, 46, 46,
		 46, 49, 49, 53, 53, 54, 54, 55, 48, 47, 47, 45, 45, 46, 46, 46, 46, 49,
		 49, 53, 53, 54, 54, 55, 49, 47, 47, 45, 45, 45, 45, 45, 45, 49, 49, 53,
		 53, 55, 55, 58,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 30, 30, 30, 32, 33, 33, 33, 35, 36, 36, 36, 39,
		 41, 41, 41, 45, 49, 49, 49, 49, 48, 48, 48, 49, 49, 49, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 34, 34, 34, 35, 37, 37, 37, 39, 42, 42, 42, 45,
		 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 33, 34, 34, 34, 36, 38, 38, 38, 40, 42, 42, 42, 45, 47, 47, 47, 47,
		 47, 47, 47, 47, 47, 47, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 34,
		 34, 36, 38, 38, 38, 40, 42, 42, 42, 45, 47, 47, 47, 47, 47, 47, 47, 47,
		 47, 47, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 34, 34, 36, 38, 38,

		 38, 40, 42, 42, 42, 45, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 33, 35, 35, 35, 37, 39, 39, 39, 41, 42, 42,
		 42, 44, 47, 47, 47, 46, 46, 46, 46, 46, 46, 46, 30, 31, 31, 31, 31, 31,
		 32, 32, 32, 33, 35, 35, 35, 37, 40, 40, 40, 41, 42, 42, 42, 44, 46, 46,
		 46, 46, 45, 45, 45, 45, 45, 45, 30, 31, 31, 31, 31, 31, 32, 32, 32, 33,
		 35, 35, 35, 37, 40, 40, 40, 41, 42, 42, 42, 44, 46, 46, 46, 46, 45, 45,
		 45, 45, 45, 45, 30, 31, 31, 31, 31, 31, 32, 32, 32, 33, 35, 35, 35, 37,
		 40, 40, 40, 41, 42, 42, 42, 44, 46, 46, 46, 46, 45, 45, 45, 45, 45, 45,
		 32, 32, 33, 33, 33, 33, 33, 33, 33, 35, 37, 37, 37, 39, 41, 41, 41, 42,
		 43, 43, 43, 45, 47, 47, 47, 46, 46, 46, 46, 45, 45, 45, 33, 34, 34, 34,
		 34, 35, 35, 35, 35, 37, 39, 39, 39, 41, 43, 43, 43, 44, 45, 45, 45, 46,
		 47, 47, 47, 47, 46, 46, 46, 46, 45, 45, 33, 34, 34, 34, 34, 35, 35, 35,
		 35, 37, 39, 39, 39, 41, 43, 43, 43, 44, 45, 45, 45, 46, 47, 47, 47, 47,
		 46, 46, 46, 46, 45, 45, 33, 34, 34, 34, 34, 35, 35, 35, 35, 37, 39, 39,
		 39, 41, 43, 43, 43, 44, 45, 45, 45, 46, 47, 47, 47, 47, 46, 46, 46, 46,
		 45, 45, 35, 35, 36, 36, 36, 37, 37, 37, 37, 39, 41, 41, 41, 43, 45, 45,
		 45, 45, 46, 46, 46, 47, 47, 47, 47, 47, 46, 46, 46, 46, 45, 45, 36, 37,
		 38, 38, 38, 39, 40, 40, 40, 41, 43, 43, 43, 45, 47, 47, 47, 47, 47, 47,
		 47, 47, 48, 48, 48, 47, 46, 46, 46, 46, 45, 45, 36, 37, 38, 38, 38, 39,
		 40, 40, 40, 41, 43, 43, 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48,
		 48, 47, 46, 46, 46, 46, 45, 45, 36, 37, 38, 38, 38, 39, 40, 40, 40, 41,
		 43, 43, 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 46, 46,
		 46, 46, 45, 45, 39, 39, 40, 40, 40, 41, 41, 41, 41, 42, 44, 44, 44, 45,
		 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 48, 48, 48, 48, 47, 47, 47,
		 41, 42, 42, 42, 42, 42, 42, 42, 42, 43, 45, 45, 45, 46, 47, 47, 47, 48,
		 48, 48, 48, 49, 50, 50, 50, 50, 49, 49, 49, 49, 49, 49, 41, 42, 42, 42,
		 42, 42, 42, 42, 42, 43, 45, 45, 45, 46, 47, 47, 47, 48, 48, 48, 48, 49,
		 50, 50, 50, 50, 49, 49, 49, 49, 49, 49, 41, 42, 42, 42, 42, 42, 42, 42,
		 42, 43, 45, 45, 45, 46, 47, 47, 47, 48, 48, 48, 48, 49, 50, 50, 50, 50,
		 49, 49, 49, 49, 49, 49, 45, 45, 45, 45, 45, 44, 44, 44, 44, 45, 46, 46,
		 46, 47, 47, 47, 47, 48, 49, 49, 49, 50, 51, 51, 51, 51, 51, 51, 51, 51,
		 51, 51, 49, 48, 47, 47, 47, 47, 46, 46, 46, 47, 47, 47, 47, 47, 48, 48,
		 48, 49, 50, 50, 50, 51, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 49, 48,
		 47, 47, 47, 47, 46, 46, 46, 47, 47, 47, 47, 47, 48, 48, 48, 49, 50, 50,
		 50, 51, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 49, 48, 47, 47, 47, 47,
		 46, 46, 46, 47, 47, 47, 47, 47, 48, 48, 48, 49, 50, 50, 50, 51, 53, 53,
		 53, 53, 53, 53, 53, 53, 53, 53, 49, 48, 47, 47, 47, 46, 46, 46, 46, 46,
		 47, 47, 47, 47, 47, 47, 47, 48, 50, 50, 50, 51, 53, 53, 53, 53, 53, 53,
		 53, 54, 54, 54, 48, 48, 47, 47, 47, 46, 45, 45, 45, 46, 46, 46, 46, 46,
		 46, 46, 46, 48, 49, 49, 49, 51, 53, 53, 53, 53, 54, 54, 54, 55, 55, 55,
		 48, 48, 47, 47, 47, 46, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 48,
		 49, 49, 49, 51, 53, 53, 53, 53, 54, 54, 54, 55, 55, 55, 48, 48, 47, 47,
		 47, 46, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 48, 49, 49, 49, 51,
		 53, 53, 53, 53, 54, 54, 54, 55, 55, 55, 49, 48, 47, 47, 47, 46, 45, 45,
		 45, 45, 46, 46, 46, 46, 46, 46, 46, 47, 49, 49, 49, 51, 53, 53, 53, 54,
		 55, 55, 55, 56, 57, 57, 49, 48, 47, 47, 47, 46, 45, 45, 45, 45, 45, 45,
		 45, 45, 45, 45, 45, 47, 49, 49, 49, 51, 53, 53, 53, 54, 55, 55, 55, 57,
		 58, 58, 49, 48, 47, 47, 47, 46, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
		 45, 47, 49, 49, 49, 51, 53, 53, 53, 54, 55, 55, 55, 57, 58, 58,
		 /* Size 4x8 */
		 31, 34, 42, 48, 31, 35, 42, 46, 33, 37, 44, 46, 36, 41, 46, 46, 40, 44,
		 48, 48, 45, 46, 49, 51, 47, 47, 50, 54, 47, 46, 49, 55,
		 /* Size 8x4 */
		 31, 31, 33, 36, 40, 45, 47, 47, 34, 35, 37, 41, 44, 46, 47, 46, 42, 42,
		 44, 46, 48, 49, 50, 49, 48, 46, 46, 46, 48, 51, 54, 55,
		 /* Size 8x16 */
		 32, 31, 31, 37, 37, 48, 48, 49, 31, 31, 31, 38, 38, 47, 47, 47, 31, 31,
		 31, 38, 38, 47, 47, 47, 30, 32, 32, 40, 40, 46, 46, 45, 30, 32, 32, 40,
		 40, 46, 46, 45, 33, 36, 36, 43, 43, 47, 47, 46, 33, 36, 36, 43, 43, 47,
		 47, 46, 37, 40, 40, 47, 47, 47, 47, 45, 37, 40, 40, 47, 47, 47, 47, 45,
		 42, 43, 43, 47, 47, 50, 50, 49, 42, 43, 43, 47, 47, 50, 50, 49, 49, 46,
		 46, 48, 48, 53, 53, 53, 49, 46, 46, 48, 48, 53, 53, 53, 48, 46, 46, 47,
		 47, 53, 53, 56, 48, 46, 46, 47, 47, 53, 53, 56, 49, 45, 45, 46, 46, 53,
		 53, 58,
		 /* Size 16x8 */
		 32, 31, 31, 30, 30, 33, 33, 37, 37, 42, 42, 49, 49, 48, 48, 49, 31, 31,
		 31, 32, 32, 36, 36, 40, 40, 43, 43, 46, 46, 46, 46, 45, 31, 31, 31, 32,
		 32, 36, 36, 40, 40, 43, 43, 46, 46, 46, 46, 45, 37, 38, 38, 40, 40, 43,
		 43, 47, 47, 47, 47, 48, 48, 47, 47, 46, 37, 38, 38, 40, 40, 43, 43, 47,
		 47, 47, 47, 48, 48, 47, 47, 46, 48, 47, 47, 46, 46, 47, 47, 47, 47, 50,
		 50, 53, 53, 53, 53, 53, 48, 47, 47, 46, 46, 47, 47, 47, 47, 50, 50, 53,
		 53, 53, 53, 53, 49, 47, 47, 45, 45, 46, 46, 45, 45, 49, 49, 53, 53, 56,
		 56, 58,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 33, 37, 37, 37, 42, 48, 48, 48, 48, 49, 49, 31, 31,
		 31, 31, 31, 34, 37, 37, 37, 42, 47, 47, 47, 48, 48, 48, 31, 31, 31, 31,
		 31, 34, 38, 38, 38, 42, 47, 47, 47, 47, 47, 47, 31, 31, 31, 31, 31, 34,
		 38, 38, 38, 42, 47, 47, 47, 47, 47, 47, 31, 31, 31, 31, 31, 34, 38, 38,
		 38, 42, 47, 47, 47, 47, 47, 47, 31, 31, 32, 32, 32, 35, 39, 39, 39, 42,
		 46, 46, 46, 46, 46, 46, 30, 31, 32, 32, 32, 35, 40, 40, 40, 42, 46, 46,
		 46, 45, 45, 45, 30, 31, 32, 32, 32, 35, 40, 40, 40, 42, 46, 46, 46, 45,
		 45, 45, 30, 31, 32, 32, 32, 35, 40, 40, 40, 42, 46, 46, 46, 45, 45, 45,
		 32, 33, 34, 34, 34, 37, 41, 41, 41, 44, 46, 46, 46, 46, 45, 45, 33, 34,
		 36, 36, 36, 39, 43, 43, 43, 45, 47, 47, 47, 46, 46, 46, 33, 34, 36, 36,
		 36, 39, 43, 43, 43, 45, 47, 47, 47, 46, 46, 46, 33, 34, 36, 36, 36, 39,
		 43, 43, 43, 45, 47, 47, 47, 46, 46, 46, 35, 36, 38, 38, 38, 41, 45, 45,
		 45, 46, 47, 47, 47, 46, 45, 45, 37, 38, 40, 40, 40, 43, 47, 47, 47, 47,
		 47, 47, 47, 46, 45, 45, 37, 38, 40, 40, 40, 43, 47, 47, 47, 47, 47, 47,
		 47, 46, 45, 45, 37, 38, 40, 40, 40, 43, 47, 47, 47, 47, 47, 47, 47, 46,
		 45, 45, 39, 40, 41, 41, 41, 44, 47, 47, 47, 48, 49, 49, 49, 48, 47, 47,
		 42, 42, 43, 43, 43, 45, 47, 47, 47, 48, 50, 50, 50, 50, 49, 49, 42, 42,
		 43, 43, 43, 45, 47, 47, 47, 48, 50, 50, 50, 50, 49, 49, 42, 42, 43, 43,
		 43, 45, 47, 47, 47, 48, 50, 50, 50, 50, 49, 49, 45, 45, 44, 44, 44, 46,
		 47, 47, 47, 49, 51, 51, 51, 51, 51, 51, 49, 48, 46, 46, 46, 47, 48, 48,
		 48, 50, 53, 53, 53, 53, 53, 53, 49, 48, 46, 46, 46, 47, 48, 48, 48, 50,
		 53, 53, 53, 53, 53, 53, 49, 48, 46, 46, 46, 47, 48, 48, 48, 50, 53, 53,
		 53, 53, 53, 53, 48, 47, 46, 46, 46, 47, 47, 47, 47, 50, 53, 53, 53, 54,
		 54, 54, 48, 47, 46, 46, 46, 46, 47, 47, 47, 50, 53, 53, 53, 54, 56, 56,
		 48, 47, 46, 46, 46, 46, 47, 47, 47, 50, 53, 53, 53, 54, 56, 56, 48, 47,
		 46, 46, 46, 46, 47, 47, 47, 50, 53, 53, 53, 54, 56, 56, 48, 47, 45, 45,

		 45, 46, 46, 46, 46, 49, 53, 53, 53, 55, 57, 57, 49, 47, 45, 45, 45, 45,
		 46, 46, 46, 49, 53, 53, 53, 56, 58, 58, 49, 47, 45, 45, 45, 45, 46, 46,
		 46, 49, 53, 53, 53, 56, 58, 58,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 30, 30, 30, 32, 33, 33, 33, 35, 37, 37, 37, 39,
		 42, 42, 42, 45, 49, 49, 49, 48, 48, 48, 48, 48, 49, 49, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 33, 34, 34, 34, 36, 38, 38, 38, 40, 42, 42, 42, 45,
		 48, 48, 48, 47, 47, 47, 47, 47, 47, 47, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 34, 36, 36, 36, 38, 40, 40, 40, 41, 43, 43, 43, 44, 46, 46, 46, 46,
		 46, 46, 46, 45, 45, 45, 31, 31, 31, 31, 31, 32, 32, 32, 32, 34, 36, 36,
		 36, 38, 40, 40, 40, 41, 43, 43, 43, 44, 46, 46, 46, 46, 46, 46, 46, 45,
		 45, 45, 31, 31, 31, 31, 31, 32, 32, 32, 32, 34, 36, 36, 36, 38, 40, 40,
		 40, 41, 43, 43, 43, 44, 46, 46, 46, 46, 46, 46, 46, 45, 45, 45, 33, 34,
		 34, 34, 34, 35, 35, 35, 35, 37, 39, 39, 39, 41, 43, 43, 43, 44, 45, 45,
		 45, 46, 47, 47, 47, 47, 46, 46, 46, 46, 45, 45, 37, 37, 38, 38, 38, 39,
		 40, 40, 40, 41, 43, 43, 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48,
		 48, 47, 47, 47, 47, 46, 46, 46, 37, 37, 38, 38, 38, 39, 40, 40, 40, 41,
		 43, 43, 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 47, 47,
		 47, 46, 46, 46, 37, 37, 38, 38, 38, 39, 40, 40, 40, 41, 43, 43, 43, 45,
		 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 47, 47, 47, 46, 46, 46,
		 42, 42, 42, 42, 42, 42, 42, 42, 42, 44, 45, 45, 45, 46, 47, 47, 47, 48,
		 48, 48, 48, 49, 50, 50, 50, 50, 50, 50, 50, 49, 49, 49, 48, 47, 47, 47,
		 47, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 49, 50, 50, 50, 51,
		 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 48, 47, 47, 47, 47, 46, 46, 46,
		 46, 46, 47, 47, 47, 47, 47, 47, 47, 49, 50, 50, 50, 51, 53, 53, 53, 53,
		 53, 53, 53, 53, 53, 53, 48, 47, 47, 47, 47, 46, 46, 46, 46, 46, 47, 47,
		 47, 47, 47, 47, 47, 49, 50, 50, 50, 51, 53, 53, 53, 53, 53, 53, 53, 53,
		 53, 53, 48, 48, 47, 47, 47, 46, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46,
		 46, 48, 50, 50, 50, 51, 53, 53, 53, 54, 54, 54, 54, 55, 56, 56, 49, 48,
		 47, 47, 47, 46, 45, 45, 45, 45, 46, 46, 46, 45, 45, 45, 45, 47, 49, 49,
		 49, 51, 53, 53, 53, 54, 56, 56, 56, 57, 58, 58, 49, 48, 47, 47, 47, 46,
		 45, 45, 45, 45, 46, 46, 46, 45, 45, 45, 45, 47, 49, 49, 49, 51, 53, 53,
		 53, 54, 56, 56, 56, 57, 58, 58,
		 /* Size 4x16 */
		 31, 33, 42, 48, 31, 34, 42, 47, 31, 34, 42, 47, 31, 35, 42, 45, 31, 35,
		 42, 45, 34, 39, 45, 46, 34, 39, 45, 46, 38, 43, 47, 46, 38, 43, 47, 46,
		 42, 45, 48, 50, 42, 45, 48, 50, 48, 47, 50, 53, 48, 47, 50, 53, 47, 46,
		 50, 54, 47, 46, 50, 54, 47, 45, 49, 56,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 34, 34, 38, 38, 42, 42, 48, 48, 47, 47, 47, 33, 34,
		 34, 35, 35, 39, 39, 43, 43, 45, 45, 47, 47, 46, 46, 45, 42, 42, 42, 42,
		 42, 45, 45, 47, 47, 48, 48, 50, 50, 50, 50, 49, 48, 47, 47, 45, 45, 46,
		 46, 46, 46, 50, 50, 53, 53, 54, 54, 56,
		 /* Size 8x32 */
		 32, 31, 31, 37, 37, 48, 48, 49, 31, 31, 31, 37, 37, 47, 47, 48, 31, 31,
		 31, 38, 38, 47, 47, 47, 31, 31, 31, 38, 38, 47, 47, 47, 31, 31, 31, 38,
		 38, 47, 47, 47, 31, 32, 32, 39, 39, 46, 46, 46, 30, 32, 32, 40, 40, 46,
		 46, 45, 30, 32, 32, 40, 40, 46, 46, 45, 30, 32, 32, 40, 40, 46, 46, 45,
		 32, 34, 34, 41, 41, 46, 46, 45, 33, 36, 36, 43, 43, 47, 47, 46, 33, 36,
		 36, 43, 43, 47, 47, 46, 33, 36, 36, 43, 43, 47, 47, 46, 35, 38, 38, 45,

		 45, 47, 47, 45, 37, 40, 40, 47, 47, 47, 47, 45, 37, 40, 40, 47, 47, 47,
		 47, 45, 37, 40, 40, 47, 47, 47, 47, 45, 39, 41, 41, 47, 47, 49, 49, 47,
		 42, 43, 43, 47, 47, 50, 50, 49, 42, 43, 43, 47, 47, 50, 50, 49, 42, 43,
		 43, 47, 47, 50, 50, 49, 45, 44, 44, 47, 47, 51, 51, 51, 49, 46, 46, 48,
		 48, 53, 53, 53, 49, 46, 46, 48, 48, 53, 53, 53, 49, 46, 46, 48, 48, 53,
		 53, 53, 48, 46, 46, 47, 47, 53, 53, 54, 48, 46, 46, 47, 47, 53, 53, 56,
		 48, 46, 46, 47, 47, 53, 53, 56, 48, 46, 46, 47, 47, 53, 53, 56, 48, 45,
		 45, 46, 46, 53, 53, 57, 49, 45, 45, 46, 46, 53, 53, 58, 49, 45, 45, 46,
		 46, 53, 53, 58,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 30, 30, 30, 32, 33, 33, 33, 35, 37, 37, 37, 39,
		 42, 42, 42, 45, 49, 49, 49, 48, 48, 48, 48, 48, 49, 49, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 34, 36, 36, 36, 38, 40, 40, 40, 41, 43, 43, 43, 44,
		 46, 46, 46, 46, 46, 46, 46, 45, 45, 45, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 34, 36, 36, 36, 38, 40, 40, 40, 41, 43, 43, 43, 44, 46, 46, 46, 46,
		 46, 46, 46, 45, 45, 45, 37, 37, 38, 38, 38, 39, 40, 40, 40, 41, 43, 43,
		 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 47, 47, 47, 46,
		 46, 46, 37, 37, 38, 38, 38, 39, 40, 40, 40, 41, 43, 43, 43, 45, 47, 47,
		 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 47, 47, 47, 46, 46, 46, 48, 47,
		 47, 47, 47, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 49, 50, 50,
		 50, 51, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 48, 47, 47, 47, 47, 46,
		 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 49, 50, 50, 50, 51, 53, 53,
		 53, 53, 53, 53, 53, 53, 53, 53, 49, 48, 47, 47, 47, 46, 45, 45, 45, 45,
		 46, 46, 46, 45, 45, 45, 45, 47, 49, 49, 49, 51, 53, 53, 53, 54, 56, 56,
		 56, 57, 58, 58},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 32, 32, 32, 35, 32, 32, 33, 35, 32, 33, 35, 38, 35, 35, 38, 46,
		 /* Size 8x8 */
		 31, 31, 31, 32, 32, 32, 34, 35, 31, 32, 32, 32, 32, 33, 34, 35, 31, 32,
		 32, 32, 32, 33, 33, 34, 32, 32, 32, 33, 34, 34, 35, 36, 32, 32, 32, 34,
		 35, 35, 36, 38, 32, 33, 33, 34, 35, 36, 38, 40, 34, 34, 33, 35, 36, 38,
		 39, 42, 35, 35, 34, 36, 38, 40, 42, 48,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 33, 34, 34, 36, 36, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 34, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 34, 34, 31, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34,
		 35, 35, 36, 36, 31, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 35, 35, 36,
		 36, 36, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 35, 36, 36, 37, 37,
		 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 32, 32,
		 32, 32, 32, 32, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 33, 33, 33, 33,
		 33, 33, 34, 35, 35, 36, 36, 38, 39, 40, 42, 42, 34, 34, 34, 34, 33, 33,
		 35, 35, 36, 37, 37, 39, 39, 41, 42, 42, 34, 34, 34, 34, 34, 34, 35, 36,
		 36, 37, 37, 40, 41, 42, 45, 45, 36, 35, 35, 35, 34, 34, 36, 36, 37, 38,
		 38, 42, 42, 45, 48, 48, 36, 35, 35, 35, 34, 34, 36, 36, 37, 38, 38, 42,
		 42, 45, 48, 48,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 33, 34, 34, 34, 34, 35, 36, 36, 36, 37, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 34, 34, 34, 34, 35, 35, 35, 35, 37, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34,
		 34, 35, 35, 35, 35, 36, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 34, 35, 35, 35,
		 35, 36, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34,
		 34, 34, 34, 34, 35, 35, 35, 36, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34, 34,
		 34, 34, 34, 35, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33, 34, 34, 34, 34, 34, 35, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34,
		 34, 35, 35, 35, 35, 36, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 35, 35, 35, 35, 36, 36, 36,
		 36, 37, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33,
		 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 36, 37, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34,
		 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 36, 37, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35, 35,
		 35, 35, 36, 36, 36, 36, 36, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35, 35, 36, 36, 36, 36, 37,
		 37, 37, 37, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34,
		 34, 34, 34, 35, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 38, 38, 38, 39,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 34, 35,
		 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36,
		 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 37, 37, 37,
		 37, 38, 38, 38, 38, 39, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
		 34, 34, 34, 34, 35, 35, 36, 36, 36, 36, 37, 38, 38, 38, 38, 39, 40, 40,
		 40, 41, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 35, 35, 35,
		 35, 36, 36, 36, 36, 37, 38, 39, 39, 39, 40, 41, 42, 42, 42, 42, 34, 34,
		 34, 34, 34, 34, 34, 33, 33, 33, 33, 34, 35, 35, 35, 35, 36, 36, 37, 37,
		 37, 38, 39, 39, 39, 39, 41, 42, 42, 42, 42, 43, 34, 34, 34, 34, 34, 34,
		 34, 33, 33, 33, 33, 34, 35, 35, 35, 35, 36, 36, 37, 37, 37, 38, 39, 39,
		 39, 39, 41, 42, 42, 42, 42, 43, 34, 34, 34, 34, 34, 34, 34, 33, 33, 33,
		 33, 34, 35, 35, 35, 35, 36, 36, 37, 37, 37, 38, 39, 39, 39, 39, 41, 42,
		 42, 42, 42, 43, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 36,
		 36, 36, 36, 37, 37, 37, 37, 38, 40, 41, 41, 41, 42, 44, 45, 45, 45, 45,
		 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 34, 35, 36, 36, 36, 36, 37, 37,
		 38, 38, 38, 39, 41, 42, 42, 42, 44, 46, 47, 47, 47, 48, 36, 35, 35, 35,
		 35, 35, 35, 34, 34, 34, 34, 35, 36, 36, 36, 36, 37, 38, 38, 38, 38, 40,
		 42, 42, 42, 42, 45, 47, 48, 48, 48, 49, 36, 35, 35, 35, 35, 35, 35, 34,
		 34, 34, 34, 35, 36, 36, 36, 36, 37, 38, 38, 38, 38, 40, 42, 42, 42, 42,
		 45, 47, 48, 48, 48, 49, 36, 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 35,
		 36, 36, 36, 36, 37, 38, 38, 38, 38, 40, 42, 42, 42, 42, 45, 47, 48, 48,
		 48, 49, 37, 37, 36, 36, 36, 36, 36, 35, 35, 35, 35, 36, 37, 37, 37, 37,
		 38, 39, 39, 39, 39, 41, 42, 43, 43, 43, 45, 48, 49, 49, 49, 50,
		 /* Size 4x8 */
		 31, 31, 32, 35, 32, 32, 32, 35, 32, 32, 33, 34, 32, 32, 34, 36, 32, 33,
		 35, 38, 33, 33, 36, 40, 34, 34, 37, 42, 35, 34, 38, 48,
		 /* Size 8x4 */
		 31, 32, 32, 32, 32, 33, 34, 35, 31, 32, 32, 32, 33, 33, 34, 34, 32, 32,
		 33, 34, 35, 36, 37, 38, 35, 35, 34, 36, 38, 40, 42, 48,
		 /* Size 8x16 */
		 32, 31, 31, 31, 32, 32, 35, 36, 31, 32, 32, 32, 32, 32, 35, 35, 31, 32,
		 32, 32, 32, 32, 35, 35, 31, 32, 32, 32, 32, 32, 34, 35, 31, 32, 32, 32,
		 33, 33, 34, 34, 31, 32, 32, 32, 33, 33, 34, 34, 31, 32, 32, 33, 34, 34,
		 35, 36, 32, 32, 32, 33, 34, 34, 36, 36, 32, 32, 32, 33, 34, 34, 36, 37,
		 32, 32, 33, 34, 35, 35, 37, 38, 32, 32, 33, 34, 35, 35, 37, 38, 33, 33,
		 33, 35, 36, 36, 40, 41, 34, 34, 34, 35, 37, 37, 41, 42, 34, 34, 34, 35,
		 37, 37, 43, 44, 36, 35, 34, 36, 38, 38, 46, 48, 36, 35, 34, 36, 38, 38,
		 46, 48,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 33, 34, 34, 36, 36, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 31, 32, 32, 32, 32, 32,
		 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 32, 32, 32, 32, 33, 33, 34, 34,
		 34, 35, 35, 36, 37, 37, 38, 38, 32, 32, 32, 32, 33, 33, 34, 34, 34, 35,
		 35, 36, 37, 37, 38, 38, 35, 35, 35, 34, 34, 34, 35, 36, 36, 37, 37, 40,
		 41, 43, 46, 46, 36, 35, 35, 35, 34, 34, 36, 36, 37, 38, 38, 41, 42, 44,
		 48, 48,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 33, 35, 36, 36, 36, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 33, 35, 35, 35, 35, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 35, 35, 35, 35, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 35, 35, 35, 35, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 35, 35, 35, 35, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 35, 35, 35, 35, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 34, 35, 35, 35, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 35,
		 35, 35, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34,
		 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 31, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 31, 32, 32, 32,
		 32, 32, 33, 33, 33, 33, 33, 34, 35, 35, 35, 35, 31, 32, 32, 32, 32, 32,
		 33, 33, 34, 34, 34, 34, 35, 36, 36, 36, 32, 32, 32, 32, 32, 32, 33, 34,
		 34, 34, 34, 35, 36, 36, 36, 36, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34,
		 34, 35, 36, 36, 36, 36, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 34, 35,
		 36, 36, 36, 36, 32, 32, 32, 32, 32, 32, 33, 34, 34, 34, 34, 35, 36, 37,
		 37, 37, 32, 32, 32, 33, 33, 33, 33, 34, 35, 35, 35, 36, 37, 38, 38, 38,
		 32, 32, 32, 33, 33, 33, 34, 35, 35, 35, 35, 36, 37, 38, 38, 38, 32, 32,
		 32, 33, 33, 33, 34, 35, 35, 35, 35, 36, 37, 38, 38, 38, 32, 32, 32, 33,
		 33, 33, 34, 35, 35, 35, 35, 36, 37, 38, 38, 38, 32, 33, 33, 33, 33, 33,
		 34, 35, 36, 36, 36, 37, 39, 40, 40, 40, 33, 33, 33, 33, 33, 33, 35, 36,
		 36, 36, 36, 38, 40, 41, 41, 41, 34, 34, 34, 34, 34, 34, 35, 36, 37, 37,
		 37, 39, 41, 42, 42, 42, 34, 34, 34, 34, 34, 34, 35, 36, 37, 37, 37, 39,
		 41, 42, 42, 42, 34, 34, 34, 34, 34, 34, 35, 36, 37, 37, 37, 39, 41, 42,
		 42, 42, 34, 34, 34, 34, 34, 34, 35, 37, 37, 37, 37, 40, 43, 44, 44, 44,
		 35, 35, 34, 34, 34, 34, 36, 37, 38, 38, 38, 41, 45, 47, 47, 47, 36, 35,
		 35, 34, 34, 34, 36, 37, 38, 38, 38, 42, 46, 48, 48, 48, 36, 35, 35, 34,
		 34, 34, 36, 37, 38, 38, 38, 42, 46, 48, 48, 48, 36, 35, 35, 34, 34, 34,
		 36, 37, 38, 38, 38, 42, 46, 48, 48, 48, 37, 36, 36, 36, 36, 36, 37, 38,
		 39, 39, 39, 42, 46, 49, 49, 49,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 34, 34, 34, 34, 35, 36, 36, 36, 37, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34,
		 34, 34, 35, 35, 35, 36, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34,
		 34, 36, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 36, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 36, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35,
		 35, 35, 35, 36, 36, 36, 36, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37,
		 37, 37, 37, 38, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34,
		 34, 34, 34, 35, 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35,
		 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 36,
		 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 33, 33, 33, 33, 33, 33, 33, 33,
		 33, 33, 33, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 38, 39, 39, 39,
		 40, 41, 42, 42, 42, 42, 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 34, 35,
		 35, 36, 36, 36, 36, 37, 37, 37, 37, 39, 40, 41, 41, 41, 43, 45, 46, 46,
		 46, 46, 36, 35, 35, 35, 35, 35, 35, 35, 34, 34, 34, 35, 36, 36, 36, 36,
		 37, 38, 38, 38, 38, 40, 41, 42, 42, 42, 44, 47, 48, 48, 48, 49, 36, 35,
		 35, 35, 35, 35, 35, 35, 34, 34, 34, 35, 36, 36, 36, 36, 37, 38, 38, 38,
		 38, 40, 41, 42, 42, 42, 44, 47, 48, 48, 48, 49, 36, 35, 35, 35, 35, 35,
		 35, 35, 34, 34, 34, 35, 36, 36, 36, 36, 37, 38, 38, 38, 38, 40, 41, 42,
		 42, 42, 44, 47, 48, 48, 48, 49,
		 /* Size 4x16 */
		 31, 31, 32, 36, 31, 32, 32, 35, 32, 32, 32, 35, 32, 32, 32, 35, 32, 32,
		 33, 34, 32, 32, 33, 34, 32, 32, 34, 36, 32, 32, 34, 36, 32, 32, 34, 37,
		 32, 33, 35, 38, 32, 33, 35, 38, 33, 33, 36, 41, 34, 34, 37, 42, 34, 34,
		 37, 44, 35, 34, 38, 48, 35, 34, 38, 48,
		 /* Size 16x4 */
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 32, 32, 32, 32,
		 33, 33, 34, 34, 34, 35, 35, 36, 37, 37, 38, 38, 36, 35, 35, 35, 34, 34,
		 36, 36, 37, 38, 38, 41, 42, 44, 48, 48,
		 /* Size 8x32 */
		 32, 31, 31, 31, 32, 32, 35, 36, 31, 31, 31, 32, 32, 32, 35, 35, 31, 32,
		 32, 32, 32, 32, 35, 35, 31, 32, 32, 32, 32, 32, 35, 35, 31, 32, 32, 32,
		 32, 32, 35, 35, 31, 32, 32, 32, 32, 32, 35, 35, 31, 32, 32, 32, 32, 32,
		 34, 35, 31, 32, 32, 32, 32, 32, 34, 35, 31, 32, 32, 32, 33, 33, 34, 34,
		 31, 32, 32, 32, 33, 33, 34, 34, 31, 32, 32, 32, 33, 33, 34, 34, 31, 32,
		 32, 33, 33, 33, 35, 35, 31, 32, 32, 33, 34, 34, 35, 36, 32, 32, 32, 33,
		 34, 34, 36, 36, 32, 32, 32, 33, 34, 34, 36, 36, 32, 32, 32, 33, 34, 34,
		 36, 36, 32, 32, 32, 33, 34, 34, 36, 37, 32, 32, 33, 33, 35, 35, 37, 38,
		 32, 32, 33, 34, 35, 35, 37, 38, 32, 32, 33, 34, 35, 35, 37, 38, 32, 32,
		 33, 34, 35, 35, 37, 38, 32, 33, 33, 34, 36, 36, 39, 40, 33, 33, 33, 35,
		 36, 36, 40, 41, 34, 34, 34, 35, 37, 37, 41, 42, 34, 34, 34, 35, 37, 37,
		 41, 42, 34, 34, 34, 35, 37, 37, 41, 42, 34, 34, 34, 35, 37, 37, 43, 44,
		 35, 34, 34, 36, 38, 38, 45, 47, 36, 35, 34, 36, 38, 38, 46, 48, 36, 35,
		 34, 36, 38, 38, 46, 48, 36, 35, 34, 36, 38, 38, 46, 48, 37, 36, 36, 37,
		 39, 39, 46, 49,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 34, 34, 34, 34, 35, 36, 36, 36, 37, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 34, 34, 34, 34, 34, 35, 35, 35, 36, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34,
		 34, 34, 34, 34, 34, 36, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 35, 36, 36, 36,
		 36, 37, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34,
		 34, 35, 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35, 35, 35,
		 35, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 35, 35, 35, 35, 35, 35,
		 34, 34, 34, 34, 34, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 39, 40, 41,
		 41, 41, 43, 45, 46, 46, 46, 46, 36, 35, 35, 35, 35, 35, 35, 35, 34, 34,
		 34, 35, 36, 36, 36, 36, 37, 38, 38, 38, 38, 40, 41, 42, 42, 42, 44, 47,
		 48, 48, 48, 49},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 32, 38, 46, 32, 34, 41, 46, 38, 41, 47, 47, 46, 46, 47, 52,
		 /* Size 8x8 */
		 31, 31, 30, 34, 36, 39, 42, 48, 31, 31, 31, 34, 37, 40, 42, 47, 30, 31,
		 32, 35, 39, 41, 42, 46, 34, 34, 35, 39, 42, 44, 45, 47, 36, 37, 39, 42,
		 46, 47, 47, 47, 39, 40, 41, 44, 47, 47, 48, 49, 42, 42, 42, 45, 47, 48,
		 48, 50, 48, 47, 46, 47, 47, 49, 50, 53,
		 /* Size 16x16 */
		 32, 31, 31, 31, 30, 30, 33, 33, 34, 36, 36, 40, 41, 44, 49, 49, 31, 31,
		 31, 31, 31, 31, 33, 34, 36, 38, 38, 41, 42, 44, 48, 48, 31, 31, 31, 31,
		 31, 31, 34, 34, 36, 38, 38, 41, 42, 44, 47, 47, 31, 31, 31, 31, 31, 31,
		 34, 35, 36, 39, 39, 41, 42, 44, 47, 47, 30, 31, 31, 31, 32, 32, 34, 35,
		 37, 40, 40, 42, 42, 44, 46, 46, 30, 31, 31, 31, 32, 32, 34, 35, 37, 40,
		 40, 42, 42, 44, 46, 46, 33, 33, 34, 34, 34, 34, 37, 38, 40, 42, 42, 44,
		 44, 45, 47, 47, 33, 34, 34, 35, 35, 35, 38, 39, 40, 43, 43, 44, 45, 46,
		 47, 47, 34, 36, 36, 36, 37, 37, 40, 40, 42, 45, 45, 45, 46, 46, 47, 47,
		 36, 38, 38, 39, 40, 40, 42, 43, 45, 47, 47, 47, 47, 47, 48, 48, 36, 38,
		 38, 39, 40, 40, 42, 43, 45, 47, 47, 47, 47, 47, 48, 48, 40, 41, 41, 41,
		 42, 42, 44, 44, 45, 47, 47, 48, 48, 49, 50, 50, 41, 42, 42, 42, 42, 42,
		 44, 45, 46, 47, 47, 48, 48, 49, 50, 50, 44, 44, 44, 44, 44, 44, 45, 46,
		 46, 47, 47, 49, 49, 50, 51, 51, 49, 48, 47, 47, 46, 46, 47, 47, 47, 48,
		 48, 50, 50, 51, 53, 53, 49, 48, 47, 47, 46, 46, 47, 47, 47, 48, 48, 50,
		 50, 51, 53, 53,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 31, 33, 33, 33, 33, 34, 36,
		 36, 36, 36, 38, 40, 41, 41, 41, 44, 47, 49, 49, 49, 49, 31, 31, 31, 31,
		 31, 31, 31, 31, 30, 30, 30, 32, 33, 34, 34, 34, 35, 36, 37, 37, 37, 39,
		 41, 42, 42, 42, 44, 47, 48, 48, 48, 48, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 33, 34, 34, 34, 36, 37, 38, 38, 38, 39, 41, 42, 42, 42,
		 44, 46, 48, 48, 48, 47, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 34, 34, 34, 34, 36, 37, 38, 38, 38, 40, 41, 42, 42, 42, 44, 46, 47, 47,
		 47, 47, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 34, 34, 34, 34,
		 36, 37, 38, 38, 38, 40, 41, 42, 42, 42, 44, 46, 47, 47, 47, 47, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 34, 34, 34, 34, 36, 37, 38, 38,
		 38, 40, 41, 42, 42, 42, 44, 46, 47, 47, 47, 47, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 33, 34, 35, 35, 35, 36, 38, 39, 39, 39, 40, 41, 42,
		 42, 42, 44, 46, 47, 47, 47, 47, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 33, 34, 35, 35, 35, 37, 38, 39, 39, 39, 41, 42, 42, 42, 42, 44, 46,
		 46, 46, 46, 46, 30, 30, 31, 31, 31, 31, 31, 31, 32, 32, 32, 33, 34, 35,
		 35, 35, 37, 39, 40, 40, 40, 41, 42, 42, 42, 42, 44, 45, 46, 46, 46, 46,
		 30, 30, 31, 31, 31, 31, 31, 31, 32, 32, 32, 33, 34, 35, 35, 35, 37, 39,
		 40, 40, 40, 41, 42, 42, 42, 42, 44, 45, 46, 46, 46, 46, 30, 30, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 33, 34, 35, 35, 35, 37, 39, 40, 40, 40, 41,
		 42, 42, 42, 42, 44, 45, 46, 46, 46, 46, 31, 32, 32, 32, 32, 32, 33, 33,
		 33, 33, 33, 34, 36, 37, 37, 37, 38, 40, 41, 41, 41, 42, 43, 43, 43, 43,
		 44, 46, 46, 46, 46, 46, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 36,
		 37, 38, 38, 38, 40, 41, 42, 42, 42, 43, 44, 44, 44, 44, 45, 46, 47, 47,
		 47, 46, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 37, 38, 39, 39, 39,
		 40, 42, 43, 43, 43, 44, 44, 45, 45, 45, 46, 47, 47, 47, 47, 47, 33, 34,
		 34, 34, 34, 34, 35, 35, 35, 35, 35, 37, 38, 39, 39, 39, 40, 42, 43, 43,
		 43, 44, 44, 45, 45, 45, 46, 47, 47, 47, 47, 47, 33, 34, 34, 34, 34, 34,
		 35, 35, 35, 35, 35, 37, 38, 39, 39, 39, 40, 42, 43, 43, 43, 44, 44, 45,
		 45, 45, 46, 47, 47, 47, 47, 47, 34, 35, 36, 36, 36, 36, 36, 37, 37, 37,
		 37, 38, 40, 40, 40, 40, 42, 44, 45, 45, 45, 45, 45, 46, 46, 46, 46, 47,
		 47, 47, 47, 47, 36, 36, 37, 37, 37, 37, 38, 38, 39, 39, 39, 40, 41, 42,
		 42, 42, 44, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
		 36, 37, 38, 38, 38, 38, 39, 39, 40, 40, 40, 41, 42, 43, 43, 43, 45, 46,
		 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 36, 37, 38, 38,
		 38, 38, 39, 39, 40, 40, 40, 41, 42, 43, 43, 43, 45, 46, 47, 47, 47, 47,
		 47, 47, 47, 47, 47, 47, 48, 48, 48, 47, 36, 37, 38, 38, 38, 38, 39, 39,
		 40, 40, 40, 41, 42, 43, 43, 43, 45, 46, 47, 47, 47, 47, 47, 47, 47, 47,
		 47, 47, 48, 48, 48, 47, 38, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 42,
		 43, 44, 44, 44, 45, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 49, 49,
		 49, 48, 40, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 43, 44, 44, 44, 44,
		 45, 47, 47, 47, 47, 48, 48, 48, 48, 48, 49, 49, 50, 50, 50, 49, 41, 42,
		 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 44, 45, 45, 45, 46, 47, 47, 47,
		 47, 48, 48, 48, 48, 48, 49, 50, 50, 50, 50, 50, 41, 42, 42, 42, 42, 42,
		 42, 42, 42, 42, 42, 43, 44, 45, 45, 45, 46, 47, 47, 47, 47, 48, 48, 48,
		 48, 48, 49, 50, 50, 50, 50, 50, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42,
		 42, 43, 44, 45, 45, 45, 46, 47, 47, 47, 47, 48, 48, 48, 48, 48, 49, 50,
		 50, 50, 50, 50, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 46,
		 46, 46, 46, 47, 47, 47, 47, 48, 49, 49, 49, 49, 50, 51, 51, 51, 51, 51,
		 47, 47, 46, 46, 46, 46, 46, 46, 45, 45, 45, 46, 46, 47, 47, 47, 47, 47,
		 47, 47, 47, 48, 49, 50, 50, 50, 51, 52, 52, 52, 52, 52, 49, 48, 48, 47,
		 47, 47, 47, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 48, 48, 48, 49,
		 50, 50, 50, 50, 51, 52, 53, 53, 53, 53, 49, 48, 48, 47, 47, 47, 47, 46,
		 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 48, 48, 48, 49, 50, 50, 50, 50,
		 51, 52, 53, 53, 53, 53, 49, 48, 48, 47, 47, 47, 47, 46, 46, 46, 46, 46,
		 47, 47, 47, 47, 47, 47, 48, 48, 48, 49, 50, 50, 50, 50, 51, 52, 53, 53,
		 53, 53, 49, 48, 47, 47, 47, 47, 47, 46, 46, 46, 46, 46, 46, 47, 47, 47,
		 47, 47, 47, 47, 47, 48, 49, 50, 50, 50, 51, 52, 53, 53, 53, 53,
		 /* Size 4x8 */
		 31, 31, 37, 48, 31, 31, 38, 47, 31, 32, 40, 46, 34, 36, 43, 47, 37, 39,
		 46, 47, 39, 41, 47, 48, 42, 43, 47, 50, 48, 46, 48, 53,
		 /* Size 8x4 */
		 31, 31, 31, 34, 37, 39, 42, 48, 31, 31, 32, 36, 39, 41, 43, 46, 37, 38,
		 40, 43, 46, 47, 47, 48, 48, 47, 46, 47, 47, 48, 50, 53,
		 /* Size 8x16 */
		 32, 31, 31, 33, 37, 37, 45, 48, 31, 31, 31, 34, 38, 38, 45, 47, 31, 31,
		 31, 34, 38, 38, 45, 47, 31, 31, 32, 34, 39, 39, 45, 46, 30, 32, 32, 35,
		 40, 40, 44, 46, 30, 32, 32, 35, 40, 40, 44, 46, 33, 34, 35, 37, 42, 42,
		 46, 47, 33, 35, 36, 38, 43, 43, 46, 47, 35, 37, 37, 40, 44, 44, 46, 47,
		 37, 39, 40, 43, 47, 47, 47, 47, 37, 39, 40, 43, 47, 47, 47, 47, 41, 42,
		 42, 44, 47, 47, 49, 49, 42, 42, 43, 44, 47, 47, 49, 50, 44, 44, 44, 45,
		 47, 47, 50, 51, 49, 47, 46, 47, 48, 48, 52, 53, 49, 47, 46, 47, 48, 48,
		 52, 53,
		 /* Size 16x8 */
		 32, 31, 31, 31, 30, 30, 33, 33, 35, 37, 37, 41, 42, 44, 49, 49, 31, 31,
		 31, 31, 32, 32, 34, 35, 37, 39, 39, 42, 42, 44, 47, 47, 31, 31, 31, 32,
		 32, 32, 35, 36, 37, 40, 40, 42, 43, 44, 46, 46, 33, 34, 34, 34, 35, 35,
		 37, 38, 40, 43, 43, 44, 44, 45, 47, 47, 37, 38, 38, 39, 40, 40, 42, 43,
		 44, 47, 47, 47, 47, 47, 48, 48, 37, 38, 38, 39, 40, 40, 42, 43, 44, 47,
		 47, 47, 47, 47, 48, 48, 45, 45, 45, 45, 44, 44, 46, 46, 46, 47, 47, 49,
		 49, 50, 52, 52, 48, 47, 47, 46, 46, 46, 47, 47, 47, 47, 47, 49, 50, 51,
		 53, 53,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 33, 35, 37, 37, 37, 40, 45, 48, 48, 48, 31, 31,
		 31, 31, 31, 31, 33, 36, 37, 37, 37, 41, 45, 48, 48, 48, 31, 31, 31, 31,
		 31, 31, 34, 36, 38, 38, 38, 41, 45, 47, 47, 47, 31, 31, 31, 31, 31, 31,
		 34, 37, 38, 38, 38, 41, 45, 47, 47, 47, 31, 31, 31, 31, 31, 31, 34, 37,
		 38, 38, 38, 41, 45, 47, 47, 47, 31, 31, 31, 31, 31, 31, 34, 37, 38, 38,
		 38, 41, 45, 47, 47, 47, 31, 31, 31, 32, 32, 32, 34, 37, 39, 39, 39, 41,
		 45, 46, 46, 46, 30, 31, 31, 32, 32, 32, 34, 38, 39, 39, 39, 42, 44, 46,
		 46, 46, 30, 31, 32, 32, 32, 32, 35, 38, 40, 40, 40, 42, 44, 46, 46, 46,
		 30, 31, 32, 32, 32, 32, 35, 38, 40, 40, 40, 42, 44, 46, 46, 46, 30, 31,
		 32, 32, 32, 32, 35, 38, 40, 40, 40, 42, 44, 46, 46, 46, 31, 32, 33, 33,
		 33, 33, 36, 39, 41, 41, 41, 43, 45, 46, 46, 46, 33, 34, 34, 35, 35, 35,
		 37, 40, 42, 42, 42, 44, 46, 47, 47, 47, 33, 34, 35, 36, 36, 36, 38, 41,
		 43, 43, 43, 44, 46, 47, 47, 47, 33, 34, 35, 36, 36, 36, 38, 41, 43, 43,
		 43, 44, 46, 47, 47, 47, 33, 34, 35, 36, 36, 36, 38, 41, 43, 43, 43, 44,
		 46, 47, 47, 47, 35, 36, 37, 37, 37, 37, 40, 43, 44, 44, 44, 45, 46, 47,
		 47, 47, 36, 37, 38, 39, 39, 39, 42, 44, 46, 46, 46, 47, 47, 47, 47, 47,
		 37, 38, 39, 40, 40, 40, 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 37, 38,
		 39, 40, 40, 40, 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 37, 38, 39, 40,
		 40, 40, 43, 45, 47, 47, 47, 47, 47, 47, 47, 47, 39, 39, 40, 41, 41, 41,
		 43, 46, 47, 47, 47, 48, 48, 48, 48, 48, 41, 41, 42, 42, 42, 42, 44, 46,
		 47, 47, 47, 48, 49, 49, 49, 49, 42, 42, 42, 43, 43, 43, 44, 46, 47, 47,
		 47, 48, 49, 50, 50, 50, 42, 42, 42, 43, 43, 43, 44, 46, 47, 47, 47, 48,
		 49, 50, 50, 50, 42, 42, 42, 43, 43, 43, 44, 46, 47, 47, 47, 48, 49, 50,
		 50, 50, 44, 44, 44, 44, 44, 44, 45, 47, 47, 47, 47, 49, 50, 51, 51, 51,
		 47, 46, 46, 46, 46, 46, 46, 47, 48, 48, 48, 49, 51, 52, 52, 52, 49, 48,
		 47, 46, 46, 46, 47, 48, 48, 48, 48, 50, 52, 53, 53, 53, 49, 48, 47, 46,
		 46, 46, 47, 48, 48, 48, 48, 50, 52, 53, 53, 53, 49, 48, 47, 46, 46, 46,
		 47, 48, 48, 48, 48, 50, 52, 53, 53, 53, 49, 48, 47, 46, 46, 46, 47, 47,
		 47, 47, 47, 49, 52, 53, 53, 53,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 31, 33, 33, 33, 33, 35, 36,
		 37, 37, 37, 39, 41, 42, 42, 42, 44, 47, 49, 49, 49, 49, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 34, 34, 34, 34, 36, 37, 38, 38, 38, 39,
		 41, 42, 42, 42, 44, 46, 48, 48, 48, 48, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 33, 34, 35, 35, 35, 37, 38, 39, 39, 39, 40, 42, 42, 42, 42,
		 44, 46, 47, 47, 47, 47, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 33,
		 35, 36, 36, 36, 37, 39, 40, 40, 40, 41, 42, 43, 43, 43, 44, 46, 46, 46,
		 46, 46, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 33, 35, 36, 36, 36,
		 37, 39, 40, 40, 40, 41, 42, 43, 43, 43, 44, 46, 46, 46, 46, 46, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 33, 35, 36, 36, 36, 37, 39, 40, 40,
		 40, 41, 42, 43, 43, 43, 44, 46, 46, 46, 46, 46, 33, 33, 34, 34, 34, 34,
		 34, 34, 35, 35, 35, 36, 37, 38, 38, 38, 40, 42, 43, 43, 43, 43, 44, 44,
		 44, 44, 45, 46, 47, 47, 47, 47, 35, 36, 36, 37, 37, 37, 37, 38, 38, 38,
		 38, 39, 40, 41, 41, 41, 43, 44, 45, 45, 45, 46, 46, 46, 46, 46, 47, 47,
		 48, 48, 48, 47, 37, 37, 38, 38, 38, 38, 39, 39, 40, 40, 40, 41, 42, 43,
		 43, 43, 44, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 47,
		 37, 37, 38, 38, 38, 38, 39, 39, 40, 40, 40, 41, 42, 43, 43, 43, 44, 46,
		 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 47, 37, 37, 38, 38,
		 38, 38, 39, 39, 40, 40, 40, 41, 42, 43, 43, 43, 44, 46, 47, 47, 47, 47,
		 47, 47, 47, 47, 47, 48, 48, 48, 48, 47, 40, 41, 41, 41, 41, 41, 41, 42,
		 42, 42, 42, 43, 44, 44, 44, 44, 45, 47, 47, 47, 47, 48, 48, 48, 48, 48,
		 49, 49, 50, 50, 50, 49, 45, 45, 45, 45, 45, 45, 45, 44, 44, 44, 44, 45,
		 46, 46, 46, 46, 46, 47, 47, 47, 47, 48, 49, 49, 49, 49, 50, 51, 52, 52,
		 52, 52, 48, 48, 47, 47, 47, 47, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47,
		 47, 47, 47, 47, 47, 48, 49, 50, 50, 50, 51, 52, 53, 53, 53, 53, 48, 48,
		 47, 47, 47, 47, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47,
		 47, 48, 49, 50, 50, 50, 51, 52, 53, 53, 53, 53, 48, 48, 47, 47, 47, 47,
		 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 49, 50,
		 50, 50, 51, 52, 53, 53, 53, 53,
		 /* Size 4x16 */
		 31, 31, 37, 48, 31, 31, 38, 47, 31, 31, 38, 47, 31, 32, 39, 46, 31, 32,
		 40, 46, 31, 32, 40, 46, 34, 35, 42, 47, 34, 36, 43, 47, 36, 37, 44, 47,
		 38, 40, 47, 47, 38, 40, 47, 47, 41, 42, 47, 49, 42, 43, 47, 50, 44, 44,
		 47, 51, 48, 46, 48, 53, 48, 46, 48, 53,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 31, 34, 34, 36, 38, 38, 41, 42, 44, 48, 48, 31, 31,
		 31, 32, 32, 32, 35, 36, 37, 40, 40, 42, 43, 44, 46, 46, 37, 38, 38, 39,
		 40, 40, 42, 43, 44, 47, 47, 47, 47, 47, 48, 48, 48, 47, 47, 46, 46, 46,
		 47, 47, 47, 47, 47, 49, 50, 51, 53, 53,
		 /* Size 8x32 */
		 32, 31, 31, 33, 37, 37, 45, 48, 31, 31, 31, 33, 37, 37, 45, 48, 31, 31,
		 31, 34, 38, 38, 45, 47, 31, 31, 31, 34, 38, 38, 45, 47, 31, 31, 31, 34,
		 38, 38, 45, 47, 31, 31, 31, 34, 38, 38, 45, 47, 31, 31, 32, 34, 39, 39,
		 45, 46, 30, 31, 32, 34, 39, 39, 44, 46, 30, 32, 32, 35, 40, 40, 44, 46,
		 30, 32, 32, 35, 40, 40, 44, 46, 30, 32, 32, 35, 40, 40, 44, 46, 31, 33,
		 33, 36, 41, 41, 45, 46, 33, 34, 35, 37, 42, 42, 46, 47, 33, 35, 36, 38,
		 43, 43, 46, 47, 33, 35, 36, 38, 43, 43, 46, 47, 33, 35, 36, 38, 43, 43,
		 46, 47, 35, 37, 37, 40, 44, 44, 46, 47, 36, 38, 39, 42, 46, 46, 47, 47,
		 37, 39, 40, 43, 47, 47, 47, 47, 37, 39, 40, 43, 47, 47, 47, 47, 37, 39,
		 40, 43, 47, 47, 47, 47, 39, 40, 41, 43, 47, 47, 48, 48, 41, 42, 42, 44,
		 47, 47, 49, 49, 42, 42, 43, 44, 47, 47, 49, 50, 42, 42, 43, 44, 47, 47,
		 49, 50, 42, 42, 43, 44, 47, 47, 49, 50, 44, 44, 44, 45, 47, 47, 50, 51,
		 47, 46, 46, 46, 48, 48, 51, 52, 49, 47, 46, 47, 48, 48, 52, 53, 49, 47,
		 46, 47, 48, 48, 52, 53, 49, 47, 46, 47, 48, 48, 52, 53, 49, 47, 46, 47,
		 47, 47, 52, 53,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 31, 33, 33, 33, 33, 35, 36,
		 37, 37, 37, 39, 41, 42, 42, 42, 44, 47, 49, 49, 49, 49, 31, 31, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 33, 34, 35, 35, 35, 37, 38, 39, 39, 39, 40,
		 42, 42, 42, 42, 44, 46, 47, 47, 47, 47, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 33, 35, 36, 36, 36, 37, 39, 40, 40, 40, 41, 42, 43, 43, 43,
		 44, 46, 46, 46, 46, 46, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35, 36,
		 37, 38, 38, 38, 40, 42, 43, 43, 43, 43, 44, 44, 44, 44, 45, 46, 47, 47,
		 47, 47, 37, 37, 38, 38, 38, 38, 39, 39, 40, 40, 40, 41, 42, 43, 43, 43,
		 44, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 47, 37, 37,
		 38, 38, 38, 38, 39, 39, 40, 40, 40, 41, 42, 43, 43, 43, 44, 46, 47, 47,
		 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 47, 45, 45, 45, 45, 45, 45,
		 45, 44, 44, 44, 44, 45, 46, 46, 46, 46, 46, 47, 47, 47, 47, 48, 49, 49,
		 49, 49, 50, 51, 52, 52, 52, 52, 48, 48, 47, 47, 47, 47, 46, 46, 46, 46,
		 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 49, 50, 50, 50, 51, 52,
		 53, 53, 53, 53},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 31, 32, 32, 32, 32, 32, 32, 33, 32, 32, 33, 34, 32, 33, 34, 35,
		 /* Size 8x8 */
		 31, 31, 31, 31, 32, 32, 32, 33, 31, 32, 32, 32, 32, 32, 32, 33, 31, 32,
		 32, 32, 32, 32, 32, 33, 31, 32, 32, 32, 32, 32, 32, 33, 32, 32, 32, 32,
		 33, 33, 34, 35, 32, 32, 32, 32, 33, 34, 34, 35, 32, 32, 32, 32, 34, 34,
		 35, 36, 33, 33, 33, 33, 35, 35, 36, 38,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 34, 31, 31,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 33, 34, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 35,
		 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35, 31, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 34, 35, 35, 35, 36, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 34, 35, 35, 35, 36, 37, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 34, 34, 35, 35, 35, 36, 37, 32, 33, 33, 33, 33, 33, 33, 33, 34, 34,
		 34, 35, 36, 36, 36, 38, 34, 34, 34, 34, 34, 33, 33, 34, 35, 35, 35, 36,
		 37, 37, 38, 39,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 34, 34, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 34, 34, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 34, 34, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 34, 34, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 33, 33, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33,
		 33, 33, 33, 33, 34, 34, 34, 34, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34,
		 34, 34, 35, 35, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33,
		 33, 34, 34, 34, 34, 34, 34, 35, 35, 35, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34,
		 34, 34, 34, 35, 35, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 35, 35,
		 35, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 33, 33, 33, 33, 33, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34,
		 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 36, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 35, 35,
		 35, 35, 35, 35, 36, 36, 37, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35,
		 36, 36, 37, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 37, 37,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34,
		 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 37, 37, 32, 32, 33, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35,
		 35, 35, 36, 36, 36, 36, 36, 37, 38, 38, 33, 33, 33, 33, 33, 33, 33, 33,
		 33, 33, 33, 33, 33, 33, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 36,
		 36, 36, 37, 38, 38, 38, 34, 34, 34, 34, 34, 34, 34, 34, 34, 33, 33, 33,
		 33, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38,
		 39, 39, 34, 34, 34, 34, 34, 34, 34, 34, 34, 33, 33, 33, 33, 33, 34, 34,
		 35, 35, 35, 35, 35, 35, 36, 36, 37, 37, 37, 37, 38, 38, 39, 39,
		 /* Size 4x8 */
		 31, 31, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 32, 32,
		 33, 34, 32, 32, 34, 34, 32, 33, 34, 35, 33, 33, 35, 36,
		 /* Size 8x4 */
		 31, 31, 32, 32, 32, 32, 32, 33, 31, 32, 32, 32, 32, 32, 33, 33, 32, 32,
		 32, 32, 33, 34, 34, 35, 32, 32, 32, 33, 34, 34, 35, 36,
		 /* Size 8x16 */
		 32, 31, 31, 31, 31, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 33, 31, 32,
		 32, 32, 32, 32, 32, 33, 31, 32, 32, 32, 32, 32, 32, 33, 31, 32, 32, 32,
		 32, 32, 32, 33, 31, 32, 32, 32, 32, 33, 33, 33, 31, 32, 32, 32, 32, 33,
		 33, 33, 31, 32, 32, 32, 32, 33, 33, 33, 31, 32, 32, 32, 33, 34, 34, 34,
		 32, 32, 32, 32, 33, 34, 34, 34, 32, 32, 32, 32, 33, 34, 34, 34, 32, 32,
		 32, 32, 33, 35, 35, 35, 32, 32, 33, 33, 34, 35, 35, 36, 32, 32, 33, 33,
		 34, 35, 35, 36, 32, 33, 33, 33, 34, 36, 36, 36, 34, 34, 34, 34, 35, 37,
		 37, 38,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 34, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 31, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 33, 33, 34, 34, 34, 35, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34,
		 34, 35, 35, 35, 36, 37, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35,
		 35, 35, 36, 37, 32, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 35, 36, 36,
		 36, 38,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 34, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33, 33, 34, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33,
		 33, 33, 34, 34, 31, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 34, 34,
		 34, 35, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 35,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 35, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 35, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 34, 35, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 34, 34, 34, 34, 35, 35, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 34, 35, 35, 35, 35, 35, 36, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34,
		 35, 35, 35, 35, 36, 36, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 35, 35,
		 35, 35, 36, 37, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 35, 35, 35, 35,
		 36, 37, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 35, 35, 35, 35, 36, 37,
		 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 35, 35, 35, 35, 36, 37, 32, 33,
		 33, 33, 33, 33, 33, 33, 34, 35, 36, 36, 36, 36, 36, 38, 33, 33, 33, 33,
		 33, 33, 33, 34, 34, 35, 36, 36, 36, 36, 37, 38, 34, 34, 34, 34, 34, 34,
		 34, 34, 35, 36, 37, 37, 37, 37, 38, 39, 34, 34, 34, 34, 34, 34, 34, 34,
		 35, 36, 37, 37, 37, 37, 38, 39,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 34, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 34, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 34, 34, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 34, 34, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33, 33, 33, 34, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
		 33, 34, 34, 34, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33,
		 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 35, 35, 36, 36, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34,
		 35, 35, 35, 35, 35, 35, 36, 36, 37, 37, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35,
		 35, 35, 36, 36, 37, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36,
		 37, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33,
		 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 37, 37, 32, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34,
		 34, 35, 35, 36, 36, 36, 36, 36, 36, 37, 38, 38, 34, 34, 34, 34, 34, 34,
		 34, 34, 34, 33, 33, 33, 33, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36,
		 37, 37, 37, 37, 38, 38, 39, 39,
		 /* Size 4x16 */
		 31, 31, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32,
		 32, 32, 32, 32, 32, 33, 32, 32, 32, 33, 32, 32, 33, 33, 32, 32, 33, 34,
		 32, 32, 33, 34, 32, 32, 33, 34, 32, 32, 34, 35, 32, 33, 34, 35, 32, 33,
		 34, 35, 33, 33, 35, 36, 34, 34, 36, 37,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35, 36, 32, 32, 32, 32, 32, 33,
		 33, 33, 34, 34, 34, 35, 35, 35, 36, 37,
		 /* Size 8x32 */
		 32, 31, 31, 31, 31, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 33, 31, 31,
		 32, 32, 32, 32, 32, 33, 31, 32, 32, 32, 32, 32, 32, 33, 31, 32, 32, 32,
		 32, 32, 32, 33, 31, 32, 32, 32, 32, 32, 32, 33, 31, 32, 32, 32, 32, 32,
		 32, 33, 31, 32, 32, 32, 32, 32, 32, 33, 31, 32, 32, 32, 32, 32, 32, 33,
		 31, 32, 32, 32, 32, 32, 32, 33, 31, 32, 32, 32, 32, 33, 33, 33, 31, 32,
		 32, 32, 32, 33, 33, 33, 31, 32, 32, 32, 32, 33, 33, 33, 31, 32, 32, 32,
		 32, 33, 33, 33, 31, 32, 32, 32, 32, 33, 33, 33, 31, 32, 32, 32, 33, 33,
		 33, 34, 31, 32, 32, 32, 33, 34, 34, 34, 32, 32, 32, 32, 33, 34, 34, 34,
		 32, 32, 32, 32, 33, 34, 34, 34, 32, 32, 32, 32, 33, 34, 34, 34, 32, 32,
		 32, 32, 33, 34, 34, 34, 32, 32, 32, 32, 33, 34, 34, 35, 32, 32, 32, 32,
		 33, 35, 35, 35, 32, 32, 33, 33, 33, 35, 35, 36, 32, 32, 33, 33, 34, 35,
		 35, 36, 32, 32, 33, 33, 34, 35, 35, 36, 32, 32, 33, 33, 34, 35, 35, 36,
		 32, 32, 33, 33, 34, 35, 35, 36, 32, 33, 33, 33, 34, 36, 36, 36, 33, 33,
		 33, 33, 34, 36, 36, 37, 34, 34, 34, 34, 35, 37, 37, 38, 34, 34, 34, 34,
		 35, 37, 37, 38,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 33, 33, 34, 34, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 33, 33, 33, 33, 34, 34, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33,
		 34, 34, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34,
		 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 37, 37, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35,
		 35, 35, 35, 35, 36, 36, 37, 37, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33,
		 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 36, 36, 36, 36, 36,
		 36, 37, 38, 38},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 31, 34, 38, 31, 32, 35, 40, 34, 35, 39, 43, 38, 40, 43, 47,
		 /* Size 8x8 */
		 31, 31, 31, 30, 34, 35, 37, 40, 31, 31, 31, 31, 34, 35, 38, 41, 31, 31,
		 31, 31, 35, 36, 39, 41, 30, 31, 31, 32, 35, 36, 40, 42, 34, 34, 35, 35,
		 39, 40, 43, 44, 35, 35, 36, 36, 40, 41, 44, 45, 37, 38, 39, 40, 43, 44,
		 47, 47, 40, 41, 41, 42, 44, 45, 47, 48,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 30, 30, 31, 33, 33, 33, 35, 36, 36, 38, 41, 31, 31,
		 31, 31, 31, 31, 31, 31, 33, 34, 34, 36, 37, 37, 39, 42, 31, 31, 31, 31,
		 31, 31, 31, 32, 34, 34, 34, 37, 38, 38, 40, 42, 31, 31, 31, 31, 31, 31,
		 31, 32, 34, 34, 34, 37, 38, 38, 40, 42, 31, 31, 31, 31, 31, 31, 31, 32,
		 34, 35, 35, 37, 39, 39, 40, 42, 30, 31, 31, 31, 31, 32, 32, 32, 34, 35,
		 35, 38, 40, 40, 41, 42, 30, 31, 31, 31, 31, 32, 32, 32, 34, 35, 35, 38,
		 40, 40, 41, 42, 31, 31, 32, 32, 32, 32, 32, 33, 35, 36, 36, 38, 40, 40,
		 41, 43, 33, 33, 34, 34, 34, 34, 34, 35, 37, 38, 38, 41, 42, 42, 43, 44,
		 33, 34, 34, 34, 35, 35, 35, 36, 38, 39, 39, 41, 43, 43, 44, 45, 33, 34,
		 34, 34, 35, 35, 35, 36, 38, 39, 39, 41, 43, 43, 44, 45, 35, 36, 37, 37,
		 37, 38, 38, 38, 41, 41, 41, 44, 46, 46, 46, 46, 36, 37, 38, 38, 39, 40,
		 40, 40, 42, 43, 43, 46, 47, 47, 47, 47, 36, 37, 38, 38, 39, 40, 40, 40,
		 42, 43, 43, 46, 47, 47, 47, 47, 38, 39, 40, 40, 40, 41, 41, 41, 43, 44,
		 44, 46, 47, 47, 47, 48, 41, 42, 42, 42, 42, 42, 42, 43, 44, 45, 45, 46,
		 47, 47, 48, 48,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 31, 32, 33, 33,
		 33, 33, 33, 34, 35, 36, 36, 36, 36, 37, 38, 40, 41, 41, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 31, 32, 33, 34, 34, 34, 34, 35,
		 36, 37, 37, 37, 37, 37, 39, 40, 42, 42, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 34, 34, 34, 35, 36, 37, 37, 37,
		 37, 38, 39, 40, 42, 42, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 34, 34, 34, 34, 34, 35, 36, 38, 38, 38, 38, 38, 40, 41,
		 42, 42, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33,
		 34, 34, 34, 34, 34, 35, 37, 38, 38, 38, 38, 39, 40, 41, 42, 42, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 34, 34, 34,
		 34, 35, 37, 38, 38, 38, 38, 39, 40, 41, 42, 42, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 34, 34, 34, 34, 35, 37, 38,
		 38, 38, 38, 39, 40, 41, 42, 42, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 32, 33, 34, 34, 34, 34, 34, 36, 37, 38, 38, 38, 38, 39,
		 40, 41, 42, 42, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 33, 34, 35, 35, 35, 35, 36, 37, 38, 39, 39, 39, 39, 40, 41, 42, 42,
		 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 35,
		 35, 35, 35, 36, 37, 39, 39, 39, 39, 40, 40, 41, 42, 42, 30, 30, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 33, 34, 35, 35, 35, 35, 36,
		 38, 39, 40, 40, 40, 40, 41, 42, 42, 42, 30, 30, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 33, 34, 35, 35, 35, 35, 36, 38, 39, 40, 40,
		 40, 40, 41, 42, 42, 42, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 33, 34, 35, 35, 35, 35, 36, 38, 39, 40, 40, 40, 40, 41, 42,
		 42, 42, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 33,
		 34, 35, 35, 35, 35, 36, 38, 39, 40, 40, 40, 40, 41, 42, 42, 42, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 35, 36, 36, 36,
		 36, 37, 38, 40, 40, 40, 40, 41, 41, 42, 43, 43, 32, 32, 32, 32, 33, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 34, 35, 36, 37, 37, 37, 37, 38, 39, 41,
		 41, 41, 41, 42, 42, 43, 43, 43, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34,
		 34, 34, 34, 34, 35, 36, 37, 38, 38, 38, 38, 39, 41, 42, 42, 42, 42, 43,
		 43, 44, 44, 44, 33, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35,
		 36, 37, 38, 39, 39, 39, 39, 40, 41, 43, 43, 43, 43, 43, 44, 44, 45, 45,
		 33, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 37, 38, 39,
		 39, 39, 39, 40, 41, 43, 43, 43, 43, 43, 44, 44, 45, 45, 33, 34, 34, 34,
		 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 37, 38, 39, 39, 39, 39, 40,
		 41, 43, 43, 43, 43, 43, 44, 44, 45, 45, 33, 34, 34, 34, 34, 34, 34, 34,
		 35, 35, 35, 35, 35, 35, 36, 37, 38, 39, 39, 39, 39, 40, 41, 43, 43, 43,
		 43, 43, 44, 44, 45, 45, 34, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36,
		 36, 36, 37, 38, 39, 40, 40, 40, 40, 41, 42, 44, 44, 44, 44, 44, 45, 45,
		 45, 45, 35, 36, 36, 36, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 39,
		 41, 41, 41, 41, 41, 42, 44, 45, 46, 46, 46, 46, 46, 46, 46, 46, 36, 37,
		 37, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 40, 41, 42, 43, 43, 43,
		 43, 44, 45, 46, 47, 47, 47, 47, 47, 47, 47, 47, 36, 37, 37, 38, 38, 38,
		 38, 38, 39, 39, 40, 40, 40, 40, 40, 41, 42, 43, 43, 43, 43, 44, 46, 47,
		 47, 47, 47, 47, 47, 47, 47, 47, 36, 37, 37, 38, 38, 38, 38, 38, 39, 39,
		 40, 40, 40, 40, 40, 41, 42, 43, 43, 43, 43, 44, 46, 47, 47, 47, 47, 47,
		 47, 47, 47, 47, 36, 37, 37, 38, 38, 38, 38, 38, 39, 39, 40, 40, 40, 40,
		 40, 41, 42, 43, 43, 43, 43, 44, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47,
		 37, 37, 38, 38, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 41, 42, 43, 43,
		 43, 43, 43, 44, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 38, 39, 39, 40,
		 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 42, 43, 44, 44, 44, 44, 45,
		 46, 47, 47, 47, 47, 47, 47, 48, 48, 48, 40, 40, 40, 41, 41, 41, 41, 41,
		 41, 41, 42, 42, 42, 42, 42, 43, 44, 44, 44, 44, 44, 45, 46, 47, 47, 47,
		 47, 47, 48, 48, 48, 48, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42,
		 42, 42, 43, 43, 44, 45, 45, 45, 45, 45, 46, 47, 47, 47, 47, 47, 48, 48,
		 48, 48, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43,
		 44, 45, 45, 45, 45, 45, 46, 47, 47, 47, 47, 47, 48, 48, 48, 48,
		 /* Size 4x8 */
		 31, 31, 35, 37, 31, 31, 36, 38, 31, 32, 37, 39, 31, 32, 37, 40, 34, 36,
		 40, 43, 35, 37, 42, 44, 38, 40, 45, 47, 41, 42, 45, 47,
		 /* Size 8x4 */
		 31, 31, 31, 31, 34, 35, 38, 41, 31, 31, 32, 32, 36, 37, 40, 42, 35, 36,
		 37, 37, 40, 42, 45, 45, 37, 38, 39, 40, 43, 44, 47, 47,
		 /* Size 8x16 */
		 32, 31, 31, 31, 33, 37, 37, 38, 31, 31, 31, 31, 33, 38, 38, 39, 31, 31,
		 31, 31, 34, 38, 38, 40, 31, 31, 31, 31, 34, 38, 38, 40, 31, 31, 32, 32,
		 34, 39, 39, 40, 30, 31, 32, 32, 35, 40, 40, 41, 30, 31, 32, 32, 35, 40,
		 40, 41, 31, 32, 33, 33, 35, 40, 40, 41, 33, 34, 35, 35, 37, 42, 42, 43,
		 33, 35, 36, 36, 38, 43, 43, 44, 33, 35, 36, 36, 38, 43, 43, 44, 35, 37,
		 38, 38, 41, 45, 45, 46, 37, 39, 40, 40, 43, 47, 47, 47, 37, 39, 40, 40,
		 43, 47, 47, 47, 39, 40, 41, 41, 43, 47, 47, 47, 42, 42, 43, 43, 44, 47,
		 47, 48,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 30, 30, 31, 33, 33, 33, 35, 37, 37, 39, 42, 31, 31,
		 31, 31, 31, 31, 31, 32, 34, 35, 35, 37, 39, 39, 40, 42, 31, 31, 31, 31,
		 32, 32, 32, 33, 35, 36, 36, 38, 40, 40, 41, 43, 31, 31, 31, 31, 32, 32,
		 32, 33, 35, 36, 36, 38, 40, 40, 41, 43, 33, 33, 34, 34, 34, 35, 35, 35,
		 37, 38, 38, 41, 43, 43, 43, 44, 37, 38, 38, 38, 39, 40, 40, 40, 42, 43,
		 43, 45, 47, 47, 47, 47, 37, 38, 38, 38, 39, 40, 40, 40, 42, 43, 43, 45,
		 47, 47, 47, 47, 38, 39, 40, 40, 40, 41, 41, 41, 43, 44, 44, 46, 47, 47,
		 47, 48,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 33, 35, 37, 37, 37, 37, 38, 42, 31, 31,
		 31, 31, 31, 31, 31, 31, 33, 35, 37, 37, 37, 37, 39, 42, 31, 31, 31, 31,
		 31, 31, 31, 32, 33, 35, 38, 38, 38, 38, 39, 42, 31, 31, 31, 31, 31, 31,
		 31, 32, 34, 36, 38, 38, 38, 38, 40, 42, 31, 31, 31, 31, 31, 31, 31, 32,
		 34, 36, 38, 38, 38, 38, 40, 42, 31, 31, 31, 31, 31, 31, 31, 32, 34, 36,
		 38, 38, 38, 38, 40, 42, 31, 31, 31, 31, 31, 31, 31, 32, 34, 36, 38, 38,
		 38, 38, 40, 42, 31, 31, 31, 31, 31, 31, 31, 32, 34, 36, 38, 38, 38, 38,
		 40, 42, 31, 31, 31, 31, 32, 32, 32, 32, 34, 36, 39, 39, 39, 39, 40, 42,
		 30, 31, 31, 32, 32, 32, 32, 32, 34, 37, 39, 39, 39, 39, 40, 42, 30, 31,
		 31, 32, 32, 32, 32, 33, 35, 37, 40, 40, 40, 40, 41, 42, 30, 31, 31, 32,
		 32, 32, 32, 33, 35, 37, 40, 40, 40, 40, 41, 42, 30, 31, 31, 32, 32, 32,
		 32, 33, 35, 37, 40, 40, 40, 40, 41, 42, 30, 31, 31, 32, 32, 32, 32, 33,
		 35, 37, 40, 40, 40, 40, 41, 42, 31, 31, 32, 32, 33, 33, 33, 33, 35, 38,
		 40, 40, 40, 40, 41, 43, 32, 32, 33, 33, 34, 34, 34, 34, 36, 39, 41, 41,
		 41, 41, 42, 44, 33, 33, 34, 35, 35, 35, 35, 35, 37, 40, 42, 42, 42, 42,
		 43, 44, 33, 34, 35, 35, 36, 36, 36, 36, 38, 40, 43, 43, 43, 43, 44, 45,
		 33, 34, 35, 35, 36, 36, 36, 36, 38, 40, 43, 43, 43, 43, 44, 45, 33, 34,
		 35, 35, 36, 36, 36, 36, 38, 40, 43, 43, 43, 43, 44, 45, 33, 34, 35, 35,
		 36, 36, 36, 36, 38, 40, 43, 43, 43, 43, 44, 45, 34, 35, 36, 37, 37, 37,
		 37, 37, 39, 42, 44, 44, 44, 44, 45, 45, 35, 36, 37, 38, 38, 38, 38, 39,
		 41, 43, 45, 45, 45, 45, 46, 46, 36, 37, 38, 39, 39, 39, 39, 40, 42, 44,
		 47, 47, 47, 47, 47, 47, 37, 38, 39, 40, 40, 40, 40, 41, 43, 45, 47, 47,
		 47, 47, 47, 47, 37, 38, 39, 40, 40, 40, 40, 41, 43, 45, 47, 47, 47, 47,
		 47, 47, 37, 38, 39, 40, 40, 40, 40, 41, 43, 45, 47, 47, 47, 47, 47, 47,
		 37, 38, 39, 40, 40, 40, 40, 41, 43, 45, 47, 47, 47, 47, 47, 47, 39, 39,
		 40, 41, 41, 41, 41, 42, 43, 45, 47, 47, 47, 47, 47, 48, 40, 41, 41, 42,
		 42, 42, 42, 42, 44, 45, 47, 47, 47, 47, 47, 48, 42, 42, 42, 43, 43, 43,
		 43, 43, 44, 46, 47, 47, 47, 47, 48, 48, 42, 42, 42, 43, 43, 43, 43, 43,
		 44, 46, 47, 47, 47, 47, 48, 48,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 31, 32, 33, 33,
		 33, 33, 33, 34, 35, 36, 37, 37, 37, 37, 39, 40, 42, 42, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 34, 34, 34, 35,
		 36, 37, 38, 38, 38, 38, 39, 41, 42, 42, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 33, 34, 35, 35, 35, 35, 36, 37, 38, 39, 39,
		 39, 39, 40, 41, 42, 42, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 33, 35, 35, 35, 35, 35, 37, 38, 39, 40, 40, 40, 40, 41, 42,
		 43, 43, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 33, 34,
		 35, 36, 36, 36, 36, 37, 38, 39, 40, 40, 40, 40, 41, 42, 43, 43, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 33, 34, 35, 36, 36, 36,
		 36, 37, 38, 39, 40, 40, 40, 40, 41, 42, 43, 43, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 33, 34, 35, 36, 36, 36, 36, 37, 38, 39,
		 40, 40, 40, 40, 41, 42, 43, 43, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 33, 33, 33, 34, 35, 36, 36, 36, 36, 37, 39, 40, 41, 41, 41, 41,
		 42, 42, 43, 43, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35,
		 35, 36, 37, 38, 38, 38, 38, 39, 41, 42, 43, 43, 43, 43, 43, 44, 44, 44,
		 35, 35, 35, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 38, 39, 40, 40,
		 40, 40, 40, 42, 43, 44, 45, 45, 45, 45, 45, 45, 46, 46, 37, 37, 38, 38,
		 38, 38, 38, 38, 39, 39, 40, 40, 40, 40, 40, 41, 42, 43, 43, 43, 43, 44,
		 45, 47, 47, 47, 47, 47, 47, 47, 47, 47, 37, 37, 38, 38, 38, 38, 38, 38,
		 39, 39, 40, 40, 40, 40, 40, 41, 42, 43, 43, 43, 43, 44, 45, 47, 47, 47,
		 47, 47, 47, 47, 47, 47, 37, 37, 38, 38, 38, 38, 38, 38, 39, 39, 40, 40,
		 40, 40, 40, 41, 42, 43, 43, 43, 43, 44, 45, 47, 47, 47, 47, 47, 47, 47,
		 47, 47, 37, 37, 38, 38, 38, 38, 38, 38, 39, 39, 40, 40, 40, 40, 40, 41,
		 42, 43, 43, 43, 43, 44, 45, 47, 47, 47, 47, 47, 47, 47, 47, 47, 38, 39,
		 39, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 42, 43, 44, 44, 44,
		 44, 45, 46, 47, 47, 47, 47, 47, 47, 47, 48, 48, 42, 42, 42, 42, 42, 42,
		 42, 42, 42, 42, 42, 42, 42, 42, 43, 44, 44, 45, 45, 45, 45, 45, 46, 47,
		 47, 47, 47, 47, 48, 48, 48, 48,
		 /* Size 4x16 */
		 31, 31, 35, 37, 31, 31, 35, 38, 31, 31, 36, 38, 31, 31, 36, 38, 31, 32,
		 36, 39, 31, 32, 37, 40, 31, 32, 37, 40, 31, 33, 38, 40, 33, 35, 40, 42,
		 34, 36, 40, 43, 34, 36, 40, 43, 36, 38, 43, 45, 38, 40, 45, 47, 38, 40,
		 45, 47, 39, 41, 45, 47, 42, 43, 46, 47,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 34, 36, 38, 38, 39, 42, 31, 31,
		 31, 31, 32, 32, 32, 33, 35, 36, 36, 38, 40, 40, 41, 43, 35, 35, 36, 36,
		 36, 37, 37, 38, 40, 40, 40, 43, 45, 45, 45, 46, 37, 38, 38, 38, 39, 40,
		 40, 40, 42, 43, 43, 45, 47, 47, 47, 47,
		 /* Size 8x32 */
		 32, 31, 31, 31, 33, 37, 37, 38, 31, 31, 31, 31, 33, 37, 37, 39, 31, 31,
		 31, 31, 33, 38, 38, 39, 31, 31, 31, 31, 34, 38, 38, 40, 31, 31, 31, 31,
		 34, 38, 38, 40, 31, 31, 31, 31, 34, 38, 38, 40, 31, 31, 31, 31, 34, 38,
		 38, 40, 31, 31, 31, 31, 34, 38, 38, 40, 31, 31, 32, 32, 34, 39, 39, 40,
		 30, 31, 32, 32, 34, 39, 39, 40, 30, 31, 32, 32, 35, 40, 40, 41, 30, 31,
		 32, 32, 35, 40, 40, 41, 30, 31, 32, 32, 35, 40, 40, 41, 30, 31, 32, 32,
		 35, 40, 40, 41, 31, 32, 33, 33, 35, 40, 40, 41, 32, 33, 34, 34, 36, 41,
		 41, 42, 33, 34, 35, 35, 37, 42, 42, 43, 33, 35, 36, 36, 38, 43, 43, 44,
		 33, 35, 36, 36, 38, 43, 43, 44, 33, 35, 36, 36, 38, 43, 43, 44, 33, 35,
		 36, 36, 38, 43, 43, 44, 34, 36, 37, 37, 39, 44, 44, 45, 35, 37, 38, 38,
		 41, 45, 45, 46, 36, 38, 39, 39, 42, 47, 47, 47, 37, 39, 40, 40, 43, 47,
		 47, 47, 37, 39, 40, 40, 43, 47, 47, 47, 37, 39, 40, 40, 43, 47, 47, 47,
		 37, 39, 40, 40, 43, 47, 47, 47, 39, 40, 41, 41, 43, 47, 47, 47, 40, 41,
		 42, 42, 44, 47, 47, 47, 42, 42, 43, 43, 44, 47, 47, 48, 42, 42, 43, 43,
		 44, 47, 47, 48,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 31, 32, 33, 33,
		 33, 33, 33, 34, 35, 36, 37, 37, 37, 37, 39, 40, 42, 42, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 35, 35, 35, 35, 36,
		 37, 38, 39, 39, 39, 39, 40, 41, 42, 42, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 33, 34, 35, 36, 36, 36, 36, 37, 38, 39, 40, 40,
		 40, 40, 41, 42, 43, 43, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 33, 34, 35, 36, 36, 36, 36, 37, 38, 39, 40, 40, 40, 40, 41, 42,
		 43, 43, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 36,
		 37, 38, 38, 38, 38, 39, 41, 42, 43, 43, 43, 43, 43, 44, 44, 44, 37, 37,
		 38, 38, 38, 38, 38, 38, 39, 39, 40, 40, 40, 40, 40, 41, 42, 43, 43, 43,
		 43, 44, 45, 47, 47, 47, 47, 47, 47, 47, 47, 47, 37, 37, 38, 38, 38, 38,
		 38, 38, 39, 39, 40, 40, 40, 40, 40, 41, 42, 43, 43, 43, 43, 44, 45, 47,
		 47, 47, 47, 47, 47, 47, 47, 47, 38, 39, 39, 40, 40, 40, 40, 40, 40, 40,
		 41, 41, 41, 41, 41, 42, 43, 44, 44, 44, 44, 45, 46, 47, 47, 47, 47, 47,
		 47, 47, 48, 48},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 31, 31, 31, 32, 31, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 33,
		 /* Size 8x8 */
		 31, 31, 31, 31, 31, 31, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32,
		 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32,
		 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 32, 32, 32, 32, 32, 32, 33, 33,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33,
		 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33,
		 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33,
		 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
		 /* Size 4x8 */
		 31, 31, 31, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32,
		 32, 32, 31, 32, 32, 33, 32, 32, 32, 33, 32, 32, 32, 33,
		 /* Size 8x4 */
		 31, 31, 31, 31, 31, 31, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 /* Size 8x16 */
		 32, 31, 31, 31, 31, 31, 31, 32, 31, 31, 31, 31, 31, 31, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32,
		 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32,
		 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32,
		 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32,
		 32, 32, 32, 32, 33, 33, 31, 32, 32, 32, 32, 32, 33, 33, 32, 32, 32, 32,
		 32, 32, 33, 34, 32, 32, 32, 32, 32, 32, 33, 34, 32, 32, 32, 32, 32, 32,
		 33, 34,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34,
		 34, 34,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 33, 33, 34, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33,
		 34, 34, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 34, 34, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 33, 34, 34,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 33, 33, 33, 33, 33, 33, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33,
		 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33,
		 34, 34, 34, 34, 34, 34, 34, 34,
		 /* Size 4x16 */
		 31, 31, 31, 32, 31, 31, 31, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32,
		 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32,
		 31, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 33, 32, 32, 32, 33, 32, 32,
		 32, 33, 32, 32, 32, 33, 32, 32, 32, 33,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 33, 33, 33,
		 /* Size 8x32 */
		 32, 31, 31, 31, 31, 31, 31, 32, 31, 31, 31, 31, 31, 31, 32, 32, 31, 31,
		 31, 31, 31, 31, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32,
		 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32,
		 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32,
		 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32,
		 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32,
		 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32,
		 31, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 31, 32,
		 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 33, 31, 32, 32, 32,
		 32, 32, 33, 33, 31, 32, 32, 32, 32, 32, 33, 33, 31, 32, 32, 32, 32, 32,
		 33, 33, 32, 32, 32, 32, 32, 32, 33, 34, 32, 32, 32, 32, 32, 32, 33, 34,
		 32, 32, 32, 32, 32, 32, 33, 34, 32, 32, 32, 32, 32, 32, 33, 34, 32, 32,
		 32, 32, 32, 32, 33, 34, 32, 32, 32, 32, 32, 32, 33, 34, 32, 32, 32, 32,
		 32, 32, 33, 34,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34,
		 34, 34, 34, 34},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 31, 31, 34, 31, 31, 31, 35, 31, 31, 32, 35, 34, 35, 35, 39,
		 /* Size 8x8 */
		 31, 31, 31, 31, 30, 31, 33, 33, 31, 31, 31, 31, 31, 32, 34, 34, 31, 31,
		 31, 31, 31, 32, 34, 34, 31, 31, 31, 31, 31, 32, 35, 35, 30, 31, 31, 31,
		 32, 32, 35, 35, 31, 32, 32, 32, 32, 33, 36, 36, 33, 34, 34, 35, 35, 36,
		 39, 39, 33, 34, 34, 35, 35, 36, 39, 39,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 31, 33, 33, 33, 33, 31, 31,
		 31, 31, 31, 31, 31, 31, 30, 30, 30, 32, 33, 34, 34, 34, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 34, 34, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 34, 34, 34, 34, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 34, 34, 34, 34, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 34, 34, 34, 34, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33,
		 34, 35, 35, 35, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 35,
		 35, 35, 30, 30, 31, 31, 31, 31, 31, 31, 32, 32, 32, 33, 34, 35, 35, 35,
		 30, 30, 31, 31, 31, 31, 31, 31, 32, 32, 32, 33, 34, 35, 35, 35, 30, 30,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 33, 34, 35, 35, 35, 31, 32, 32, 32,
		 32, 32, 33, 33, 33, 33, 33, 34, 36, 37, 37, 37, 33, 33, 33, 34, 34, 34,
		 34, 34, 34, 34, 34, 36, 37, 38, 38, 38, 33, 34, 34, 34, 34, 34, 35, 35,
		 35, 35, 35, 37, 38, 39, 39, 39, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35,
		 35, 37, 38, 39, 39, 39, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 37,
		 38, 39, 39, 39,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30,
		 30, 30, 30, 31, 31, 32, 33, 33, 33, 33, 33, 33, 33, 34, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 30, 31,
		 31, 32, 33, 33, 33, 33, 33, 33, 33, 34, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 31, 32, 32, 33, 34,
		 34, 34, 34, 34, 34, 34, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 33, 34, 34, 34, 34, 34,
		 34, 35, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 33, 33, 34, 34, 34, 34, 34, 34, 35, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 33, 34, 34, 34, 34, 34, 34, 34, 35, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 33,
		 34, 34, 34, 34, 34, 34, 34, 35, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 33, 34, 34, 34, 34,
		 34, 34, 34, 35, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 33, 34, 34, 34, 34, 34, 34, 34, 35,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 33, 34, 34, 34, 34, 34, 34, 34, 35, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 33, 34, 34, 34, 34, 34, 34, 34, 35, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 33, 34, 35,
		 35, 35, 35, 35, 35, 35, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 33, 34, 35, 35, 35, 35, 35,
		 35, 35, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 33, 33, 34, 35, 35, 35, 35, 35, 35, 36, 30, 30,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 30, 30, 30, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 34,
		 34, 35, 35, 35, 35, 35, 35, 36, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 35,
		 35, 35, 35, 36, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36,
		 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 30, 30, 30, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 30, 30, 30, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35,
		 35, 35, 35, 35, 35, 36, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 36, 36, 36, 36, 36,
		 36, 37, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33,
		 33, 33, 33, 33, 33, 34, 34, 35, 36, 37, 37, 37, 37, 37, 37, 37, 32, 32,
		 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34,
		 34, 34, 35, 36, 37, 37, 37, 37, 37, 37, 37, 38, 33, 33, 33, 33, 33, 34,
		 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 36, 37,
		 37, 38, 38, 38, 38, 38, 38, 39, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34,
		 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 37, 37, 38, 39, 39, 39,
		 39, 39, 39, 40, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35,
		 35, 35, 35, 35, 35, 35, 35, 36, 37, 37, 38, 39, 39, 39, 39, 39, 39, 40,
		 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35,
		 35, 35, 35, 36, 37, 37, 38, 39, 39, 39, 39, 39, 39, 40, 33, 33, 34, 34,
		 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36,
		 37, 37, 38, 39, 39, 39, 39, 39, 39, 40, 33, 33, 34, 34, 34, 34, 34, 34,
		 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 37, 37, 38, 39,
		 39, 39, 39, 39, 39, 40, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,
		 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 37, 37, 38, 39, 39, 39, 39, 39,
		 39, 40, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36,
		 36, 36, 36, 36, 36, 37, 37, 38, 39, 40, 40, 40, 40, 40, 40, 40,
		 /* Size 4x8 */
		 31, 31, 31, 34, 31, 31, 31, 35, 31, 31, 31, 35, 31, 32, 32, 36, 31, 32,
		 32, 36, 31, 33, 33, 37, 34, 36, 36, 40, 34, 36, 36, 40,
		 /* Size 8x4 */
		 31, 31, 31, 31, 31, 31, 34, 34, 31, 31, 31, 32, 32, 33, 36, 36, 31, 31,
		 31, 32, 32, 33, 36, 36, 34, 35, 35, 36, 36, 37, 40, 40,
		 /* Size 8x16 */
		 32, 31, 31, 31, 31, 31, 33, 35, 31, 31, 31, 31, 31, 31, 33, 36, 31, 31,
		 31, 31, 31, 31, 34, 36, 31, 31, 31, 31, 31, 31, 34, 37, 31, 31, 31, 31,
		 31, 31, 34, 37, 31, 31, 31, 31, 31, 31, 34, 37, 31, 31, 31, 32, 32, 32,
		 34, 37, 30, 31, 31, 32, 32, 32, 34, 38, 30, 31, 32, 32, 32, 32, 35, 38,
		 30, 31, 32, 32, 32, 32, 35, 38, 30, 31, 32, 32, 32, 32, 35, 38, 31, 32,
		 33, 33, 33, 33, 36, 39, 33, 34, 34, 35, 35, 35, 37, 40, 33, 34, 35, 36,
		 36, 36, 38, 41, 33, 34, 35, 36, 36, 36, 38, 41, 33, 34, 35, 36, 36, 36,
		 38, 41,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 31, 33, 33, 33, 33, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 34, 34, 34, 34, 31, 31, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 33, 34, 35, 35, 35, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 33, 35, 36, 36, 36, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 33, 35, 36, 36, 36, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 33, 35, 36, 36, 36, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35, 36,
		 37, 38, 38, 38, 35, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 40, 41,
		 41, 41,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 35, 37, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 35, 37, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 36, 37, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 33, 35, 36, 38, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 34, 35, 36, 38, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 33, 34, 35, 37, 38, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33,
		 34, 35, 37, 38, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 35,
		 37, 38, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 35, 37, 38,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 35, 37, 38, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 34, 35, 37, 38, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 33, 34, 35, 37, 38, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 33, 34, 36, 37, 39, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 33, 34, 36, 37, 39, 30, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 33, 34, 36, 38, 39, 30, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33,
		 35, 36, 38, 40, 30, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 35, 36,
		 38, 40, 30, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 35, 36, 38, 40,
		 30, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 35, 36, 38, 40, 30, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 35, 36, 38, 40, 30, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 33, 35, 36, 38, 40, 31, 31, 31, 32, 32, 33,
		 33, 33, 33, 33, 33, 34, 35, 37, 38, 40, 31, 32, 32, 33, 33, 33, 33, 33,
		 33, 33, 33, 35, 36, 37, 39, 41, 32, 32, 33, 33, 34, 34, 34, 34, 34, 34,
		 34, 35, 37, 38, 40, 41, 33, 33, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36,
		 37, 39, 40, 42, 33, 34, 34, 35, 35, 36, 36, 36, 36, 36, 36, 37, 38, 40,
		 41, 43, 33, 34, 34, 35, 35, 36, 36, 36, 36, 36, 36, 37, 38, 40, 41, 43,
		 33, 34, 34, 35, 35, 36, 36, 36, 36, 36, 36, 37, 38, 40, 41, 43, 33, 34,
		 34, 35, 35, 36, 36, 36, 36, 36, 36, 37, 38, 40, 41, 43, 33, 34, 34, 35,
		 35, 36, 36, 36, 36, 36, 36, 37, 38, 40, 41, 43, 33, 34, 34, 35, 35, 36,
		 36, 36, 36, 36, 36, 37, 38, 40, 41, 43, 34, 34, 35, 35, 36, 36, 36, 36,
		 36, 36, 36, 38, 39, 40, 42, 44,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30,
		 30, 30, 30, 31, 31, 32, 33, 33, 33, 33, 33, 33, 33, 34, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 33, 34, 34, 34, 34, 34, 34, 34, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 34,
		 34, 34, 34, 34, 34, 35, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 33, 34, 35, 35, 35, 35, 35,
		 35, 35, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34,
		 35, 36, 36, 36, 36, 36, 36, 36, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 35, 36, 36, 36,
		 36, 36, 36, 36, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 33, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33,
		 33, 34, 35, 36, 36, 36, 36, 36, 36, 36, 32, 32, 32, 32, 32, 33, 33, 33,
		 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 35, 35, 36, 37,
		 37, 37, 37, 37, 37, 38, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34,
		 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 36, 37, 37, 38, 38, 38, 38, 38,
		 38, 39, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36,
		 36, 36, 36, 36, 36, 37, 37, 38, 39, 40, 40, 40, 40, 40, 40, 40, 35, 35,
		 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38,
		 38, 38, 39, 40, 40, 41, 41, 41, 41, 41, 41, 42, 37, 37, 37, 38, 38, 38,
		 38, 38, 38, 38, 38, 38, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 41, 41,
		 42, 43, 43, 43, 43, 43, 43, 44,
		 /* Size 4x16 */
		 31, 31, 31, 34, 31, 31, 31, 34, 31, 31, 31, 35, 31, 31, 31, 35, 31, 31,
		 31, 35, 31, 31, 31, 35, 31, 32, 32, 36, 31, 32, 32, 36, 31, 32, 32, 36,
		 31, 32, 32, 36, 31, 32, 32, 36, 32, 33, 33, 37, 33, 35, 35, 39, 34, 36,
		 36, 40, 34, 36, 36, 40, 34, 36, 36, 40,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 33, 34, 34, 34, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 33, 35, 36, 36, 36, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 33, 35, 36, 36, 36, 34, 34, 35, 35, 35, 35,
		 36, 36, 36, 36, 36, 37, 39, 40, 40, 40,
		 /* Size 8x32 */
		 32, 31, 31, 31, 31, 31, 33, 35, 31, 31, 31, 31, 31, 31, 33, 35, 31, 31,
		 31, 31, 31, 31, 33, 36, 31, 31, 31, 31, 31, 31, 33, 36, 31, 31, 31, 31,
		 31, 31, 34, 36, 31, 31, 31, 31, 31, 31, 34, 37, 31, 31, 31, 31, 31, 31,
		 34, 37, 31, 31, 31, 31, 31, 31, 34, 37, 31, 31, 31, 31, 31, 31, 34, 37,
		 31, 31, 31, 31, 31, 31, 34, 37, 31, 31, 31, 31, 31, 31, 34, 37, 31, 31,
		 31, 31, 31, 31, 34, 37, 31, 31, 31, 32, 32, 32, 34, 37, 31, 31, 31, 32,
		 32, 32, 34, 37, 30, 31, 31, 32, 32, 32, 34, 38, 30, 31, 32, 32, 32, 32,
		 35, 38, 30, 31, 32, 32, 32, 32, 35, 38, 30, 31, 32, 32, 32, 32, 35, 38,
		 30, 31, 32, 32, 32, 32, 35, 38, 30, 31, 32, 32, 32, 32, 35, 38, 30, 31,
		 32, 32, 32, 32, 35, 38, 31, 31, 32, 33, 33, 33, 35, 38, 31, 32, 33, 33,
		 33, 33, 36, 39, 32, 33, 34, 34, 34, 34, 37, 40, 33, 34, 34, 35, 35, 35,
		 37, 40, 33, 34, 35, 36, 36, 36, 38, 41, 33, 34, 35, 36, 36, 36, 38, 41,
		 33, 34, 35, 36, 36, 36, 38, 41, 33, 34, 35, 36, 36, 36, 38, 41, 33, 34,
		 35, 36, 36, 36, 38, 41, 33, 34, 35, 36, 36, 36, 38, 41, 34, 35, 36, 36,
		 36, 36, 39, 42,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30,
		 30, 30, 30, 31, 31, 32, 33, 33, 33, 33, 33, 33, 33, 34, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 33, 34, 34, 34, 34, 34, 34, 34, 35, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 33, 34, 34, 35,
		 35, 35, 35, 35, 35, 36, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 34, 35, 36, 36, 36, 36, 36,
		 36, 36, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 33, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 33, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36, 33, 33, 33, 33, 34, 34,
		 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 36, 37,
		 37, 38, 38, 38, 38, 38, 38, 39, 35, 35, 36, 36, 36, 37, 37, 37, 37, 37,
		 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 39, 40, 40, 41, 41, 41,
		 41, 41, 41, 42},
	},
	{
		{/* Luma */
		 /* Size 4x4 */
		 31, 31, 31, 31, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32,
		 /* Size 8x8 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32,
		 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 /* Size 4x8 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32,
		 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32,
		 /* Size 8x4 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 /* Size 8x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 31, 31, 31, 32,
		 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32,
		 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32,
		 32, 32,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32,
		 /* Size 4x16 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 31, 32,
		 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32,
		 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32, 32, 32, 31, 32,
		 32, 32, 31, 32, 32, 32, 31, 32, 32, 32,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 /* Size 8x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 31, 31, 31, 32, 32, 32, 32, 32, 31, 31, 31, 32, 32, 32, 32, 32,
		 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32,
		 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32,
		 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32,
		 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31,
		 32, 32, 32, 32, 32, 32, 31, 31, 32, 32, 32, 32, 32, 32, 31, 31, 32, 32,
		 32, 32, 32, 32,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 32, 32},
		{/* Chroma */
		 /* Size 4x4 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 /* Size 8x8 */
		 31, 31, 31, 31, 31, 31, 31, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 30, 31, 31, 31, 31, 31, 31, 31,
		 /* Size 16x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32,
		 /* Size 32x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30,
		 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
		 /* Size 4x8 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 30, 31, 32, 32,
		 /* Size 8x4 */
		 31, 31, 31, 31, 31, 31, 31, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 32, 32, 31, 31, 31, 31, 31, 31, 32, 32,
		 /* Size 8x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 31, 31, 31, 31,
		 31, 32, 32, 32, 30, 31, 31, 31, 31, 32, 32, 32, 30, 31, 31, 31, 32, 32,
		 32, 32,
		 /* Size 16x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32,
		 /* Size 16x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
		 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 30, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 30, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 30, 30, 31, 31,
		 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 30, 30, 31, 31, 31, 31,
		 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 30, 30, 31, 31, 31, 31, 31, 31,
		 32, 32, 32, 32, 32, 32, 32, 32,
		 /* Size 32x16 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32,
		 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
		 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32,
		 /* Size 4x16 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 31, 31,
		 32, 32, 31, 31, 32, 32, 30, 31, 32, 32,
		 /* Size 16x4 */
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 32, 32, 32, 32,
		 /* Size 8x32 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 31, 31, 31, 31, 31, 32,
		 32, 32, 31, 31, 31, 31, 31, 32, 32, 32, 31, 31, 31, 31, 31, 32, 32, 32,
		 30, 31, 31, 31, 31, 32, 32, 32, 30, 31, 31, 31, 31, 32, 32, 32, 30, 31,
		 31, 31, 32, 32, 32, 32, 30, 31, 31, 31, 32, 32, 32, 32, 30, 31, 31, 31,
		 32, 32, 32, 32,
		 /* Size 32x8 */
		 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,
		 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
		 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
		 32, 32, 32, 32},
	}};
const static uint16_t Qm_Offset[ TX_SIZES_ALL ] = { 0, 16, 80, 336, 336, 1360, 1392, 1424, 1552, 1680, 2192,
336, 336, 2704, 2768, 2832, 3088, 1680, 2192 };

int inline tile_log2(int blkSize, int target)
{
	int k;
	for (k = 0; (blkSize << k) < target; k++)
	{
	}
	return k;
}
// to do 用 c++ 模板写
int inline Min(int a, int b)
{
	return a <= b ? a : b;
}
int inline Max(int a, int b)
{
	return a >= b ? a : b;
}
int inline Clip3(int a, int b, int c)
{
	return (c < a || c > b) ? ((c < a) ? a : b) : c;
}
int inline Clip1(int x, int BitDepth)
{
	return Clip3(0, 1 << BitDepth, x);
}
int inline Round2(int x, int n)
{
	if (n == 0)
		return x;
	return (x + (1 << (n - 1))) >> n;
}
int inline Round2Signed(int x, int n)
{
	return x >= 0 ? (Round2(x, n)) : -(Round2(-x, n));
}
int inline FloorLog2(int x)
{
	int s = 0;
	while (x != 0)
	{
		x = x >> 1;
		s++;
	}
	return s - 1;
}
int inline CeilLog2(int x)
{
	if (x < 2)
		return 0;
	int i = 1;
	int p = 2;
	while (p < x)
	{
		i++;
		p = p << 1;
	}
	return i;
}
int inline Abs(int x)
{
	return x > 0 ? x : -x;
}
int inline constrain(int diff, int threshold, int damping)
{
	if (!threshold)
		return 0;
	int dampingAdj = Max(0, damping - FloorLog2(threshold));
	int sign = (diff < 0) ? -1 : 1;
	return sign * Clip3(0, Abs(diff), threshold - (Abs(diff) >> dampingAdj));
}
int inline is_inside(int candidateR, int candidateC, int colStart, int colEnd, int rowStart, int rowEnd)
{
	return (candidateC >= colStart &&
			candidateC < colEnd &&
			candidateR >= rowStart &&
			candidateR < rowEnd);
}
int inline is_inside_filter_region(int candidateR, int candidateC, int MiCols, int MiRows)
{
	int colStart = 0;
	int colEnd = MiCols;
	int rowStart = 0;
	int rowEnd = MiRows;
	return (candidateC >= colStart &&
			candidateC < colEnd &&
			candidateR >= rowStart &&
			candidateR < rowEnd);
}

int inline neg_deinterleave(int diff, int ref, int max)
{
	if (!ref)
		return diff;
	if (ref >= (max - 1))
		return max - diff - 1;
	if (2 * ref < max)
	{
		if (diff <= 2 * ref)
		{
			if (diff & 1)
				return ref + ((diff + 1) >> 1);
			else
				return ref - (diff >> 1);
		}
		return diff;
	}
	else
	{
		if (diff <= 2 * (max - ref - 1))
		{
			if (diff & 1)
				return ref + ((diff + 1) >> 1);
			else
				return ref - (diff >> 1);
		}
		return max - (diff + 1);
	}
}
int inline get_plane_residual_size(int subsize, int plane, int subsampling_x, int subsampling_y)
{
	int subx = plane > 0 ? subsampling_x : 0;
	int suby = plane > 0 ? subsampling_y : 0;
	return Subsampled_Size[subsize][subx][suby];
}
int inline is_directional_mode(int mode)
{
	if ((mode >= V_PRED) && (mode <= D67_PRED))
	{
		return 1;
	}
	return 0;
}
int inline av1sort(int *array, int min, int max)
{
}
int inline get_relative_dist(int enable_order_hint, int OrderHintBits, int a, int b)
{
	if (enable_order_hint)
		return 0;
	int diff = a - b;
	int m = 1 << (OrderHintBits - 1);
	diff = (diff & (m - 1)) - (diff & m);
	return diff;
}
// checks that the position is within the same 64x64 block
int inline check_sb_border(int MiRow, int MiCol, int deltaRow, int deltaCol)
{
	int row = (MiRow & 15) + deltaRow;
	int col = (MiCol & 15) + deltaCol;
	return (row >= 0 && row < 16 && col >= 0 && col < 16);
}
int inline project(int *posValid, int *v8, int delta, int dstSign, int max8, int maxOff8)
{
	int base8 = (*v8 >> 3) << 3;
	int offset8;
	if (delta >= 0)
	{
		offset8 = delta >> (3 + 1 + MI_SIZE_LOG2);
	}
	else
	{
		offset8 = -((-delta) >> (3 + 1 + MI_SIZE_LOG2));
	}
	*v8 += dstSign * offset8;
	if (*v8 < 0 ||
		*v8 >= max8 ||
		*v8 < base8 - maxOff8 ||
		*v8 >= base8 + 8 + maxOff8)
	{
		*posValid = 0;
	}
	return *v8;
}
int inline find_tx_size(int w, int h)
{
	int txSz;
	for (txSz = 0; txSz < TX_SIZES_ALL; txSz++)
		if (Tx_Width[txSz] == w && Tx_Height[txSz] == h)
			break;
	return txSz;
}
int inline check_backward(int refFrame)
{
	return ((refFrame >= BWDREF_FRAME) && (refFrame <= ALTREF_FRAME));
}

int inline is_samedir_ref_pair(int ref0, int ref1)
{
	return (ref0 >= BWDREF_FRAME) == (ref1 >= BWDREF_FRAME);
}
int inline ref_count_ctx(int counts0, int counts1)
{
	if (counts0 < counts1)
		return 0;
	else if (counts0 == counts1)
		return 1;
	else
		return 2;
}
int inline count_refs(int frameType, uint8_t AvailU, uint8_t AvailL, uint8_t *AboveRefFrame, uint8_t *LeftRefFrame)
{
	int c = 0;
	if (AvailU)
	{
		if (AboveRefFrame[0] == frameType)
			c++;
		if (AboveRefFrame[1] == frameType)
			c++;
	};
	if (AvailL)
	{
		if (LeftRefFrame[0] == frameType)
			c++;
		if (LeftRefFrame[1] == frameType)
			c++;
	}
	return c;
}
int inline has_nearmv(int YMode)
{
	return (YMode == NEARMV || YMode == NEAR_NEARMV || YMode == NEAR_NEWMV || YMode == NEW_NEARMV);
}
int inline is_scaled(int refFrame, uint8_t *ref_frame_idx, uint8_t *RefUpscaledWidth, uint8_t *RefFrameHeight,
					 int FrameWidth, int FrameHeight)
{
	int refIdx = ref_frame_idx[refFrame - LAST_FRAME];
	int xScale = ((RefUpscaledWidth[refIdx] << REF_SCALE_SHIFT) + (FrameWidth / 2)) / FrameWidth;
	int yScale = ((RefFrameHeight[refIdx] << REF_SCALE_SHIFT) + (FrameHeight / 2)) / FrameHeight;
	int noScale = 1 << REF_SCALE_SHIFT;
	return xScale != noScale || yScale != noScale;
}
int inline ls_product(int a, int b)
{
	return ((a * b) >> 2) + (a + b);
}
int inline nondiag(int v, int divFactor, int divShift)
{
	return Clip3(-WARPEDMODEL_NONDIAGAFFINE_CLAMP + 1,
				 WARPEDMODEL_NONDIAGAFFINE_CLAMP - 1,
				 Round2Signed(v * divFactor, divShift));
}
int inline diag(int v, int divFactor, int divShift)
{
	return Clip3((1 << WARPEDMODEL_PREC_BITS) - WARPEDMODEL_NONDIAGAFFINE_CLAMP + 1,
				 (1 << WARPEDMODEL_PREC_BITS) + WARPEDMODEL_NONDIAGAFFINE_CLAMP - 1,
				 Round2Signed(v * divFactor, divShift));
}
int inline block_shape(int bsize)
{
	int w4 = Num_4x4_Blocks_Wide[bsize];
	int h4 = Num_4x4_Blocks_High[bsize];
	if (h4 > w4)
		return 0;
	else if (h4 < w4)
		return 1;
	else
		return 2;
}
int inline get_wedge_direction(int bsize, int index)
{
	return Wedge_Codebook[block_shape(bsize)][index][0];
}
int inline get_wedge_xoff(int bsize, int index)
{
	return Wedge_Codebook[block_shape(bsize)][index][1];
}
int inline get_wedge_yoff(int bsize, int index)
{
	return Wedge_Codebook[block_shape(bsize)][index][2];
}
inline uint8_t *get_obmc_mask(int length)
{
	uint8_t *ret = NULL;
	if (length == 2)
	{
		ret = (uint8_t *)Obmc_Mask_2;
	}
	else if (length == 4)
	{
		ret = (uint8_t *)Obmc_Mask_4;
	}
	else if (length == 8)
	{
		ret = (uint8_t *)Obmc_Mask_8;
	}
	else if (length == 16)
	{
		ret = (uint8_t *)Obmc_Mask_16;
	}
	else
	{
		ret = (uint8_t *)Obmc_Mask_32;
	}

	return ret;
}
// 获取量化参数
int inline dc_q(int b, int BitDepth)
{
	return Dc_Qlookup[(BitDepth - 8) >> 1][Clip3(0, 255, b)];
}

int inline ac_q(int b, int BitDepth)
{
	return Ac_Qlookup[(BitDepth - 8) >> 1][Clip3(0, 255, b)];
}

// 蝶形变换相关
int inline brev(int numBits, int x)
{
	int t = 0;
	for (int i = 0; i < numBits; i++)
	{
		int bit = (x >> i) & 1;
		t += bit << (numBits - 1 - i);
	}
	return t;
}
// butterfly rotation
void inline B(int a, int b, int angle, int flip, int r, int T[])
{
	int x = T[a] * cos128(angle) - T[b] * sin128(angle);
	int y = T[a] * sin128(angle) + T[b] * cos128(angle);
	T[a] = Round2(x, 12);
	T[b] = Round2(y, 12);

	if (flip)
	{
		int temp = T[a];
		T[a] = T[b];
		T[b] = temp;
	}
}
// Hadamard rotation
void inline H(int a, int b, int flip, int r, int T[])
{
	int x = T[a];
	int y = T[b];
	T[a] = Clip3(-(1 << (r - 1)), (1 << (r - 1)) - 1, x + y);
	T[b] = Clip3(-(1 << (r - 1)), (1 << (r - 1)) - 1, x - y);

	if (flip)
	{
		int temp = T[a];
		T[a] = T[b];
		T[b] = temp;
	}
}

int inline cos128(int angle)
{
	int angle2 = angle & 255;
	if (angle2 >= 0 && angle2 <= 64)
		return Cos128_Lookup[angle2];
	else if (angle2 > 64 && angle2 <= 128)
		return Cos128_Lookup[128 - angle2] * -1;
	else if (angle2 > 128 && angle2 <= 192)
		return Cos128_Lookup[angle2 - 128] * -1;
	else
		return Cos128_Lookup[256 - angle2];
}

// Sine function for integer angles
int inline sin128(int angle)
{
	return cos128(angle - 64);
}
int inline filter4_clamp(int value, int BitDepth)
{
	return Clip3(-(1 << (BitDepth - 1)), (1 << (BitDepth - 1)) - 1, value);
}
int inline is_tx_type_in_set(int txSet, int txType, int is_inter)
{
	return is_inter ? Tx_Type_In_Set_Inter[txSet][txType] : Tx_Type_In_Set_Intra[txSet][txType];
}
int inline get_tx_set(int txSz, int is_inter, int reduced_tx_set)
{
	int txSzSqr = Tx_Size_Sqr[txSz];
	int txSzSqrUp = Tx_Size_Sqr_Up[txSz];
	if (txSzSqrUp > TX_32X32)
		return TX_SET_DCTONLY;
	if (is_inter)
	{
		if (reduced_tx_set || txSzSqrUp == TX_32X32)
			return TX_SET_INTER_3;
		else if (txSzSqr == TX_16X16)
			return TX_SET_INTER_2;
		return TX_SET_INTER_1;
	}
	else
	{
		if (txSzSqrUp == TX_32X32)
			return TX_SET_DCTONLY;
		else if (reduced_tx_set)
			return TX_SET_INTRA_2;
		else if (txSzSqr == TX_16X16)
			return TX_SET_INTRA_2;
		return TX_SET_INTRA_1;
	}
}
int inline get_tx_class(int txType)
{
	if ((txType == V_DCT) ||
		(txType == V_ADST) ||
		(txType == V_FLIPADST))
	{
		return TX_CLASS_VERT;
	}
	else if ((txType == H_DCT) ||
			 (txType == H_ADST) ||
			 (txType == H_FLIPADST))
	{
		return TX_CLASS_HORIZ;
	}
	else
		return TX_CLASS_2D;
}
inline uint16_t *get_mrow_scan(int txSz)
{
	if (txSz == TX_4X4)
		return (uint16_t *)Mrow_Scan_4x4;
	else if (txSz == TX_4X8)
		return (uint16_t *)Mrow_Scan_4x8;
	else if (txSz == TX_8X4)
		return (uint16_t *)Mrow_Scan_8x4;
	else if (txSz == TX_8X8)
		return (uint16_t *)Mrow_Scan_8x8;
	else if (txSz == TX_8X16)
		return (uint16_t *)Mrow_Scan_8x16;
	else if (txSz == TX_16X8)
		return (uint16_t *)Mrow_Scan_16x8;
	else if (txSz == TX_16X16)
		return (uint16_t *)Mrow_Scan_16x16;
	else if (txSz == TX_4X16)
		return (uint16_t *)Mrow_Scan_4x16;
	return (uint16_t *)Mrow_Scan_16x4;
}
inline uint16_t *get_mcol_scan(int txSz)
{
	if (txSz == TX_4X4)
		return (uint16_t *)Mcol_Scan_4x4;
	else if (txSz == TX_4X8)
		return (uint16_t *)Mcol_Scan_4x8;
	else if (txSz == TX_8X4)
		return (uint16_t *)Mcol_Scan_8x4;
	else if (txSz == TX_8X8)
		return (uint16_t *)Mcol_Scan_8x8;
	else if (txSz == TX_8X16)
		return (uint16_t *)Mcol_Scan_8x16;
	else if (txSz == TX_16X8)
		return (uint16_t *)Mcol_Scan_16x8;
	else if (txSz == TX_16X16)
		return (uint16_t *)Mcol_Scan_16x16;
	else if (txSz == TX_4X16)
		return (uint16_t *)Mcol_Scan_4x16;
	return (uint16_t *)Mcol_Scan_16x4;
}
inline uint16_t *get_default_scan(int txSz)
{
	if (txSz == TX_4X4)
		return (uint16_t *)Default_Scan_4x4;
	else if (txSz == TX_4X8)
		return (uint16_t *)Default_Scan_4x8;
	else if (txSz == TX_8X4)
		return (uint16_t *)Default_Scan_8x4;
	else if (txSz == TX_8X8)
		return (uint16_t *)Default_Scan_8x8;
	else if (txSz == TX_8X16)
		return (uint16_t *)Default_Scan_8x16;
	else if (txSz == TX_16X8)
		return (uint16_t *)Default_Scan_16x8;
	else if (txSz == TX_16X16)
		return (uint16_t *)Default_Scan_16x16;
	else if (txSz == TX_16X32)
		return (uint16_t *)Default_Scan_16x32;
	else if (txSz == TX_32X16)
		return (uint16_t *)Default_Scan_32x16;
	else if (txSz == TX_4X16)
		return (uint16_t *)Default_Scan_4x16;
	else if (txSz == TX_16X4)
		return (uint16_t *)Default_Scan_16x4;
	else if (txSz == TX_8X32)
		return (uint16_t *)Default_Scan_8x32;
	else if (txSz == TX_32X8)
		return (uint16_t *)Default_Scan_32x8;
	return (uint16_t *)Default_Scan_32x32;
}
inline uint16_t *get_scan(int txSz, int PlaneTxType)
{
	if (txSz == TX_16X64)
	{
		return (uint16_t *)Default_Scan_16x32;
	}
	if (txSz == TX_64X16)
	{
		return (uint16_t *)Default_Scan_32x16;
	}
	if (Tx_Size_Sqr_Up[txSz] == TX_64X64)
	{
		return (uint16_t *)Default_Scan_32x32;
	}
	if (PlaneTxType == IDTX)
	{
		return get_default_scan(txSz);
	}
	int preferRow = (PlaneTxType == V_DCT ||
					 PlaneTxType == V_ADST ||
					 PlaneTxType == V_FLIPADST);
	int preferCol = (PlaneTxType == H_DCT ||
					 PlaneTxType == H_ADST ||
					 PlaneTxType == H_FLIPADST);
	if (preferRow)
	{
		return get_mrow_scan(txSz);
	}
	else if (preferCol)
	{
		return get_mcol_scan(txSz);
	}
	return get_default_scan(txSz);
}
#endif
