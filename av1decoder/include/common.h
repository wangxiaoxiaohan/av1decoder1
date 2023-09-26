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
	WEDGE_HORIZONTAL  = 0,
	WEDGE_VERTICAL,
	WEDGE_OBLIQUE27,
	WEDGE_OBLIQUE63,
	WEDGE_OBLIQUE117,
	WEDGE_OBLIQUE153,
};
enum em_inverse_transform
{
	DCT_DCT  = 0 ,
	ADST_DCT = 1 ,
	DCT_ADST = 2 ,
	ADST_ADST = 3 ,
	FLIPADST_DCT = 4,
	DCT_FLIPADST = 5 ,
	FLIPADST_FLIPADST = 6 ,
	ADST_FLIPADST = 7 ,
	FLIPADST_ADST = 8,
	IDTX = 9,
	V_DCT = 10,
	H_DCT = 11,
	V_ADST = 12,
	H_ADST = 13,
	V_FLIPADST = 14,
	H_FLIPADST = 15,
};
enum em_tx_set{
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
0, 840, 420, 280, 210, 168, 140, 120, 105
};

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
{ WEDGE_OBLIQUE27, 4, 4 }, { WEDGE_OBLIQUE63, 4, 4 },
{ WEDGE_OBLIQUE117, 4, 4 }, { WEDGE_OBLIQUE153, 4, 4 },
{ WEDGE_HORIZONTAL, 4, 2 }, { WEDGE_HORIZONTAL, 4, 4 },
{ WEDGE_HORIZONTAL, 4, 6 }, { WEDGE_VERTICAL, 4, 4 },
{ WEDGE_OBLIQUE27, 4, 2 }, { WEDGE_OBLIQUE27, 4, 6 },
{ WEDGE_OBLIQUE153, 4, 2 }, { WEDGE_OBLIQUE153, 4, 6 },
{ WEDGE_OBLIQUE63, 2, 4 }, { WEDGE_OBLIQUE63, 6, 4 },
{ WEDGE_OBLIQUE117, 2, 4 }, { WEDGE_OBLIQUE117, 6, 4 },
},
{
{ WEDGE_OBLIQUE27, 4, 4 }, { WEDGE_OBLIQUE63, 4, 4 },
{ WEDGE_OBLIQUE117, 4, 4 }, { WEDGE_OBLIQUE153, 4, 4 },
{ WEDGE_VERTICAL, 2, 4 }, { WEDGE_VERTICAL, 4, 4 },
{ WEDGE_VERTICAL, 6, 4 }, { WEDGE_HORIZONTAL, 4, 4 },
{ WEDGE_OBLIQUE27, 4, 2 }, { WEDGE_OBLIQUE27, 4, 6 },
{ WEDGE_OBLIQUE153, 4, 2 }, { WEDGE_OBLIQUE153, 4, 6 },
{ WEDGE_OBLIQUE63, 2, 4 }, { WEDGE_OBLIQUE63, 6, 4 },
{ WEDGE_OBLIQUE117, 2, 4 }, { WEDGE_OBLIQUE117, 6, 4 },
},
{
{ WEDGE_OBLIQUE27, 4, 4 }, { WEDGE_OBLIQUE63, 4, 4 },
{ WEDGE_OBLIQUE117, 4, 4 }, { WEDGE_OBLIQUE153, 4, 4 },
{ WEDGE_HORIZONTAL, 4, 2 }, { WEDGE_HORIZONTAL, 4, 6 },
{ WEDGE_VERTICAL, 2, 4 }, { WEDGE_VERTICAL, 6, 4 },
{ WEDGE_OBLIQUE27, 4, 2 }, { WEDGE_OBLIQUE27, 4, 6 },

{ WEDGE_OBLIQUE153, 4, 2 }, { WEDGE_OBLIQUE153, 4, 6 },
{ WEDGE_OBLIQUE63, 2, 4 }, { WEDGE_OBLIQUE63, 6, 4 },
{ WEDGE_OBLIQUE117, 2, 4 }, { WEDGE_OBLIQUE117, 6, 4 },
}
};
const static uint8_t Wedge_Master_Oblique_Odd[MASK_MASTER_SIZE] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 18,
37, 53, 60, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};
const static uint8_t Wedge_Master_Oblique_Even[MASK_MASTER_SIZE] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 11, 27,
46, 58, 62, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};
const static uint8_t Wedge_Master_Vertical[MASK_MASTER_SIZE] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 7, 21,
43, 57, 62, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

const static uint8_t Ii_Weights_1d[MAX_SB_SIZE] = {
60, 58, 56, 54, 52, 50, 48, 47, 45, 44, 42, 41, 39, 38, 37, 35, 34, 33, 32,
31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 22, 21, 20, 19, 19, 18, 18, 17, 16,
16, 15, 15, 14, 14, 13, 13, 12, 12, 12, 11, 11, 10, 10, 10, 9, 9, 9, 8,
8, 8, 8, 7, 7, 7, 7, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 4, 4,
4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
const static uint8_t Quant_Dist_Weight[ 4 ][ 2 ] = {
{ 2, 3 }, { 2, 5 }, { 2, 7 }, { 1, MAX_FRAME_DISTANCE }
};
const static uint8_t Quant_Dist_Lookup[ 4 ][ 2 ] = {
{ 9, 7 }, { 11, 5 }, { 12, 4 }, { 13, 3 }
};
const static uint8_t Obmc_Mask_2[2] = { 45, 64 };
const static uint8_t Obmc_Mask_4[4] = { 39, 50, 59, 64 };
const static uint8_t Obmc_Mask_8[8] = { 36, 42, 48, 53, 57, 61, 64, 64 };
const static uint8_t Obmc_Mask_16[16] = { 34, 37, 40, 43, 46, 49, 52, 54,
56, 58, 60, 61, 64, 64, 64, 64 };
const static uint8_t Obmc_Mask_32[32] = { 33, 35, 36, 38, 40, 41, 43, 44,
45, 47, 48, 50, 51, 52, 53, 55,
56, 57, 58, 59, 60, 60, 61, 62,
64, 64, 64, 64, 64, 64, 64, 64 };
const static uint16_t Dc_Qlookup[ 3 ][ 256 ] = {
{
4, 8, 8, 9, 10, 11, 12, 12, 13, 14, 15, 16,
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
1184, 1232, 1282, 1336
},
{
4, 9, 10, 13, 15, 17, 20, 22, 25, 28, 31, 34,
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
4737, 4929, 5130, 5347
},
{
4, 12, 18, 25, 33, 41, 50, 60,
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
16356, 16943, 17575, 18237, 18949, 19718, 20521, 21387
}
};
const static uint16_t Ac_Qlookup[ 3 ][ 256 ] = {
{
4, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
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
1725, 1759, 1793, 1828
},
{
4, 9, 11, 13, 16, 18, 21, 24, 27, 30, 33, 37,
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
6900, 7036, 7172, 7312
},
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
25551, 26047, 26559, 27071, 27599, 28143, 28687, 29247
}
};

const static uint16_t  Cos128_Lookup[ 65 ] = {
4096, 4095, 4091, 4085, 4076, 4065, 4052, 4036,
4017, 3996, 3973, 3948, 3920, 3889, 3857, 3822,
3784, 3745, 3703, 3659, 3612, 3564, 3513, 3461,
3406, 3349, 3290, 3229, 3166, 3102, 3035, 2967,
2896, 2824, 2751, 2675, 2598, 2520, 2440, 2359,
2276, 2191, 2106, 2019, 1931, 1842, 1751, 1660,
1567, 1474, 1380, 1285, 1189, 1092, 995, 897,
799, 700, 601, 501, 401, 301, 201, 101, 0
};
const static uint8_t Transform_Row_Shift[ TX_SIZES_ALL ] = {
0, 1, 2, 2, 2, 0, 0, 1, 1,
1, 1, 1, 1, 1, 1, 2, 2, 2, 2
};
const static uint8_t Cdef_Uv_Dir[ 2 ][ 2 ][ 8 ] = {
{ {0, 1, 2, 3, 4, 5, 6, 7},
{1, 2, 2, 2, 3, 4, 6, 0} },
{ {7, 0, 2, 4, 5, 6, 6, 6},
{0, 1, 2, 3, 4, 5, 6, 7} }
};
const static uint8_t Cdef_Pri_Taps[2][2] = {
{ 4, 2 }, { 3, 3 }
};
const static uint8_t Cdef_Sec_Taps[2][2] = {
{ 2, 1 }, { 2, 1 }
};

const static int8_t  Cdef_Directions[8][2][2] = {
{ { -1, 1 }, { -2, 2 } },
{ { 0, 1 }, { -1, 2 } },
{ { 0, 1 }, { 0, 2 } },
{ { 0, 1 }, { 1, 2 } },
{ { 1, 1 }, { 2, 2 } },
{ { 1, 0 }, { 2, 1 } },
{ { 1, 0 }, { 2, 0 } },
{ { 1, 0 }, { 2, -1 } }
};
const static int8_t Upscale_Filter[SUPERRES_FILTER_SHIFTS][SUPERRES_FILTER_TAPS] = {
{ 0, 0, 0, 128, 0, 0, 0, 0 }, { 0, 0, -1, 128, 2, -1, 0, 0 },
{ 0, 1, -3, 127, 4, -2, 1, 0 }, { 0, 1, -4, 127, 6, -3, 1, 0 },
{ 0, 2, -6, 126, 8, -3, 1, 0 }, { 0, 2, -7, 125, 11, -4, 1, 0 },
{ -1, 2, -8, 125, 13, -5, 2, 0 }, { -1, 3, -9, 124, 15, -6, 2, 0 },
{ -1, 3, -10, 123, 18, -6, 2, -1 }, { -1, 3, -11, 122, 20, -7, 3, -1 },
{ -1, 4, -12, 121, 22, -8, 3, -1 }, { -1, 4, -13, 120, 25, -9, 3, -1 },
{ -1, 4, -14, 118, 28, -9, 3, -1 }, { -1, 4, -15, 117, 30, -10, 4, -1 },
{ -1, 5, -16, 116, 32, -11, 4, -1 }, { -1, 5, -16, 114, 35, -12, 4, -1 },
{ -1, 5, -17, 112, 38, -12, 4, -1 }, { -1, 5, -18, 111, 40, -13, 5, -1 },
{ -1, 5, -18, 109, 43, -14, 5, -1 }, { -1, 6, -19, 107, 45, -14, 5, -1 },
{ -1, 6, -19, 105, 48, -15, 5, -1 }, { -1, 6, -19, 103, 51, -16, 5, -1 },
{ -1, 6, -20, 101, 53, -16, 6, -1 }, { -1, 6, -20, 99, 56, -17, 6, -1 },
{ -1, 6, -20, 97, 58, -17, 6, -1 }, { -1, 6, -20, 95, 61, -18, 6, -1 },
{ -2, 7, -20, 93, 64, -18, 6, -2 }, { -2, 7, -20, 91, 66, -19, 6, -1 },
{ -2, 7, -20, 88, 69, -19, 6, -1 }, { -2, 7, -20, 86, 71, -19, 6, -1 },
{ -2, 7, -20, 84, 74, -20, 7, -2 }, { -2, 7, -20, 81, 76, -20, 7, -1 },
{ -2, 7, -20, 79, 79, -20, 7, -2 }, { -1, 7, -20, 76, 81, -20, 7, -2 },
{ -2, 7, -20, 74, 84, -20, 7, -2 }, { -1, 6, -19, 71, 86, -20, 7, -2 },
{ -1, 6, -19, 69, 88, -20, 7, -2 }, { -1, 6, -19, 66, 91, -20, 7, -2 },
{ -2, 6, -18, 64, 93, -20, 7, -2 }, { -1, 6, -18, 61, 95, -20, 6, -1 },
{ -1, 6, -17, 58, 97, -20, 6, -1 }, { -1, 6, -17, 56, 99, -20, 6, -1 },
{ -1, 6, -16, 53, 101, -20, 6, -1 }, { -1, 5, -16, 51, 103, -19, 6, -1 },
{ -1, 5, -15, 48, 105, -19, 6, -1 }, { -1, 5, -14, 45, 107, -19, 6, -1 },
{ -1, 5, -14, 43, 109, -18, 5, -1 }, { -1, 5, -13, 40, 111, -18, 5, -1 },
{ -1, 4, -12, 38, 112, -17, 5, -1 }, { -1, 4, -12, 35, 114, -16, 5, -1 },
{ -1, 4, -11, 32, 116, -16, 5, -1 }, { -1, 4, -10, 30, 117, -15, 4, -1 },
{ -1, 3, -9, 28, 118, -14, 4, -1 }, { -1, 3, -9, 25, 120, -13, 4, -1 },
{ -1, 3, -8, 22, 121, -12, 4, -1 }, { -1, 3, -7, 20, 122, -11, 3, -1 },
{ -1, 2, -6, 18, 123, -10, 3, -1 }, { 0, 2, -6, 15, 124, -9, 3, -1 },
{ 0, 2, -5, 13, 125, -8, 2, -1 }, { 0, 1, -4, 11, 125, -7, 2, 0 },
{ 0, 1, -3, 8, 126, -6, 2, 0 }, { 0, 1, -3, 6, 127, -4, 1, 0 },
{ 0, 1, -2, 4, 127, -3, 1, 0 }, { 0, 0, -1, 2, 128, -1, 0, 0 },
};

const static uint8_t  Sgr_Params[ (1 << SGRPROJ_PARAMS_BITS) ][ 4 ] = {
{ 2, 12, 1, 4 }, { 2, 15, 1, 6 }, { 2, 18, 1, 8 }, { 2, 21, 1, 9 },
{ 2, 24, 1, 10 }, { 2, 29, 1, 11 }, { 2, 36, 1, 12 }, { 2, 45, 1, 13 },
{ 2, 56, 1, 14 }, { 2, 68, 1, 15 }, { 0, 0, 1, 5 }, { 0, 0, 1, 8 },
{ 0, 0, 1, 11 }, { 0, 0, 1, 14 }, { 2, 30, 0, 0 }, { 2, 75, 0, 0 }
};
const static uint8_t Tx_Width_Log2[ TX_SIZES_ALL ] = {
2, 3, 4, 5, 6, 2, 3, 3, 4, 4, 5, 5, 6, 2, 4, 3, 5, 4, 6
};

const static uint8_t Tx_Height_Log2[ TX_SIZES_ALL ] = {
2, 3, 4, 5, 6, 3, 2, 4, 3, 5, 4, 6, 5, 4, 2, 5, 3, 6, 4
};
const static uint8_t Tx_Size_Sqr[ TX_SIZES_ALL ] = {
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
TX_16X16
};
const static uint8_t Tx_Size_Sqr_Up[ TX_SIZES_ALL ] = {
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
TX_64X64
};
const static uint8_t Tx_Type_In_Set_Intra[ TX_SET_TYPES_INTRA ][ TX_TYPES ] = {
{
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
},
{
1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
},
{
1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
}
};
const static uint8_t Tx_Type_In_Set_Inter[ TX_SET_TYPES_INTER ][ TX_TYPES ] = {
{
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
},
{
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
},
{
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
},
{
1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
}
};

const static uint16_t Default_Scan_4x4[ 16 ] = {
0, 1, 4, 8,
5, 2, 3, 6,
9, 12, 13, 10,
7, 11, 14, 15
};
const static uint16_t Mcol_Scan_4x4[ 16 ] = {
0, 4, 8, 12,
1, 5, 9, 13,
2, 6, 10, 14,
3, 7, 11, 15
};
const static uint16_t Mrow_Scan_4x4[ 16 ] = {
0, 1, 2, 3,
4, 5, 6, 7,
8, 9, 10, 11,
12, 13, 14, 15
};
const static uint16_t Default_Scan_4x8[ 32 ] = {
0, 1, 4, 2, 5, 8, 3, 6, 9, 12, 7, 10, 13, 16, 11, 14,
17, 20, 15, 18, 21, 24, 19, 22, 25, 28, 23, 26, 29, 27, 30, 31
};
const static uint16_t Mcol_Scan_4x8[ 32 ] = {
0, 4, 8, 12, 16, 20, 24, 28, 1, 5, 9, 13, 17, 21, 25, 29,
2, 6, 10, 14, 18, 22, 26, 30, 3, 7, 11, 15, 19, 23, 27, 31
};
const static uint16_t Mrow_Scan_4x8[ 32 ] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};
const static uint16_t Default_Scan_8x4[ 32 ] = {
0, 8, 1, 16, 9, 2, 24, 17, 10, 3, 25, 18, 11, 4, 26, 19,
12, 5, 27, 20, 13, 6, 28, 21, 14, 7, 29, 22, 15, 30, 23, 31
};
const static uint16_t Mcol_Scan_8x4[ 32 ] = {
0, 8, 16, 24, 1, 9, 17, 25, 2, 10, 18, 26, 3, 11, 19, 27,
4, 12, 20, 28, 5, 13, 21, 29, 6, 14, 22, 30, 7, 15, 23, 31
};
const static uint16_t Mrow_Scan_8x4[ 32 ] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};
const static uint16_t Default_Scan_8x8[ 64 ] = {
0, 1, 8, 16, 9, 2, 3, 10,
17, 24, 32, 25, 18, 11, 4, 5,
12, 19, 26, 33, 40, 48, 41, 34,
27, 20, 13, 6, 7, 14, 21, 28,
35, 42, 49, 56, 57, 50, 43, 36,
29, 22, 15, 23, 30, 37, 44, 51,
58, 59, 52, 45, 38, 31, 39, 46,
53, 60, 61, 54, 47, 55, 62, 63
};
const static uint16_t Mcol_Scan_8x8[ 64 ] = {
0, 8, 16, 24, 32, 40, 48, 56,
1, 9, 17, 25, 33, 41, 49, 57,
2, 10, 18, 26, 34, 42, 50, 58,
3, 11, 19, 27, 35, 43, 51, 59,
4, 12, 20, 28, 36, 44, 52, 60,
5, 13, 21, 29, 37, 45, 53, 61,
6, 14, 22, 30, 38, 46, 54, 62,
7, 15, 23, 31, 39, 47, 55, 63
};
const static uint16_t Mrow_Scan_8x8[ 64 ] = {
0, 1, 2, 3, 4, 5, 6, 7,
8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23,
24, 25, 26, 27, 28, 29, 30, 31,
32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47,
48, 49, 50, 51, 52, 53, 54, 55,
56, 57, 58, 59, 60, 61, 62, 63
};
const static uint16_t Default_Scan_8x16[ 128 ] = {
0, 1, 8, 2, 9, 16, 3, 10, 17, 24, 4, 11, 18, 25, 32,
5, 12, 19, 26, 33, 40, 6, 13, 20, 27, 34, 41, 48, 7, 14,
21, 28, 35, 42, 49, 56, 15, 22, 29, 36, 43, 50, 57, 64, 23,
30, 37, 44, 51, 58, 65, 72, 31, 38, 45, 52, 59, 66, 73, 80,
39, 46, 53, 60, 67, 74, 81, 88, 47, 54, 61, 68, 75, 82, 89,
96, 55, 62, 69, 76, 83, 90, 97, 104, 63, 70, 77, 84, 91, 98,
105, 112, 71, 78, 85, 92, 99, 106, 113, 120, 79, 86, 93, 100, 107,
114, 121, 87, 94, 101, 108, 115, 122, 95, 102, 109, 116, 123, 103, 110,
117, 124, 111, 118, 125, 119, 126, 127
};
const static uint16_t Mcol_Scan_8x16[ 128 ] = {
0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120,
1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105, 113, 121,
2, 10, 18, 26, 34, 42, 50, 58, 66, 74, 82, 90, 98, 106, 114, 122,
3, 11, 19, 27, 35, 43, 51, 59, 67, 75, 83, 91, 99, 107, 115, 123,
4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84, 92, 100, 108, 116, 124,
5, 13, 21, 29, 37, 45, 53, 61, 69, 77, 85, 93, 101, 109, 117, 125,
6, 14, 22, 30, 38, 46, 54, 62, 70, 78, 86, 94, 102, 110, 118, 126,
7, 15, 23, 31, 39, 47, 55, 63, 71, 79, 87, 95, 103, 111, 119, 127
};
const static uint16_t Mrow_Scan_8x16[ 128 ] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104,
105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
120, 121, 122, 123, 124, 125, 126, 127
};
const static uint16_t Default_Scan_16x8[ 128 ] = {
0, 16, 1, 32, 17, 2, 48, 33, 18, 3, 64, 49, 34, 19, 4, 80,
65, 50, 35, 20, 5, 96, 81, 66, 51, 36, 21, 6, 112, 97, 82, 67,
52, 37, 22, 7, 113, 98, 83, 68, 53, 38, 23, 8, 114, 99, 84, 69,
54, 39, 24, 9, 115, 100, 85, 70, 55, 40, 25, 10, 116, 101, 86, 71,
56, 41, 26, 11, 117, 102, 87, 72, 57, 42, 27, 12, 118, 103, 88, 73,
58, 43, 28, 13, 119, 104, 89, 74, 59, 44, 29, 14, 120, 105, 90, 75,
60, 45, 30, 15, 121, 106, 91, 76, 61, 46, 31, 122, 107, 92, 77, 62,
47, 123, 108, 93, 78, 63, 124, 109, 94, 79, 125, 110, 95, 126, 111, 127
};
const static uint16_t Mcol_Scan_16x8[ 128 ] = {
0, 16, 32, 48, 64, 80, 96, 112, 1, 17, 33, 49, 65, 81, 97, 113,
2, 18, 34, 50, 66, 82, 98, 114, 3, 19, 35, 51, 67, 83, 99, 115,
4, 20, 36, 52, 68, 84, 100, 116, 5, 21, 37, 53, 69, 85, 101, 117,
6, 22, 38, 54, 70, 86, 102, 118, 7, 23, 39, 55, 71, 87, 103, 119,
8, 24, 40, 56, 72, 88, 104, 120, 9, 25, 41, 57, 73, 89, 105, 121,
10, 26, 42, 58, 74, 90, 106, 122, 11, 27, 43, 59, 75, 91, 107, 123,
12, 28, 44, 60, 76, 92, 108, 124, 13, 29, 45, 61, 77, 93, 109, 125,
14, 30, 46, 62, 78, 94, 110, 126, 15, 31, 47, 63, 79, 95, 111, 127
};
const static uint16_t Mrow_Scan_16x8[ 128 ] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104,
105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
120, 121, 122, 123, 124, 125, 126, 127
};
const static uint16_t Default_Scan_16x16[ 256 ] = {
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
250, 251, 236, 221, 206, 191, 207, 222, 237, 252, 253, 238, 223, 239, 254, 255
};
const static uint16_t Mcol_Scan_16x16[ 256 ] = {
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
15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239, 255
};
const static uint16_t Mrow_Scan_16x16[ 256 ] = {
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
255
};
const static uint16_t Default_Scan_16x32[ 512 ] = {
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
510, 511
};
const static uint16_t Default_Scan_32x16[ 512 ] = {
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
479, 511
};

const static uint16_t Default_Scan_32x32[ 1024 ] = {
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
927, 958, 989, 1020, 1021, 990, 959, 991, 1022, 1023
};
const static uint16_t Default_Scan_4x16[ 64 ] = {
0, 1, 4, 2, 5, 8, 3, 6, 9, 12, 7, 10, 13, 16, 11, 14,
17, 20, 15, 18, 21, 24, 19, 22, 25, 28, 23, 26, 29, 32, 27, 30,
33, 36, 31, 34, 37, 40, 35, 38, 41, 44, 39, 42, 45, 48, 43, 46,
49, 52, 47, 50, 53, 56, 51, 54, 57, 60, 55, 58, 61, 59, 62, 63
};
const static uint16_t Mcol_Scan_4x16[ 64 ] = {
0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61,
2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62,
3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63
};

const static uint16_t Mrow_Scan_4x16[ 64 ] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
};
const static uint16_t Default_Scan_16x4[ 64 ] = {
0, 16, 1, 32, 17, 2, 48, 33, 18, 3, 49, 34, 19, 4, 50, 35,
20, 5, 51, 36, 21, 6, 52, 37, 22, 7, 53, 38, 23, 8, 54, 39,
24, 9, 55, 40, 25, 10, 56, 41, 26, 11, 57, 42, 27, 12, 58, 43,
28, 13, 59, 44, 29, 14, 60, 45, 30, 15, 61, 46, 31, 62, 47, 63
};
const static uint16_t Mcol_Scan_16x4[ 64 ] = {
0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,
4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,
8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,
12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63
};
const static uint16_t Mrow_Scan_16x4[ 64 ] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
};

const static uint16_t Default_Scan_8x32[ 256 ] = {
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
255
};
const static uint16_t Default_Scan_32x8[ 256 ] = {
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
255
};
const static uint8_t Coeff_Base_Pos_Ctx_Offset[ 3 ] = {
SIG_COEF_CONTEXTS_2D,
SIG_COEF_CONTEXTS_2D + 5,
SIG_COEF_CONTEXTS_2D + 10
};
const static uint8_t Mode_To_Txfm[ UV_INTRA_MODES_CFL_ALLOWED ] = {
DCT_DCT, // DC_PRED
ADST_DCT, // V_PRED
DCT_ADST, // H_PRED
DCT_DCT, // D45_PRED
ADST_ADST, // D135_PRED
ADST_DCT, // D113_PRED
DCT_ADST, // D157_PRED
DCT_ADST, // D203_PRED
ADST_DCT, // D67_PRED
ADST_ADST, // SMOOTH_PRED
ADST_DCT, // SMOOTH_V_PRED
DCT_ADST, // SMOOTH_H_PRED
ADST_ADST, // PAETH_PRED
DCT_DCT, // UV_CFL_PRED
};
const static uint8_t Sig_Ref_Diff_Offset[ 3 ][ SIG_REF_DIFF_OFFSET_NUM ][ 2 ] = {
{
{ 0, 1 }, { 1, 0 }, { 1, 1 }, { 0, 2 }, { 2, 0 }
},
{
{ 0, 1 }, { 1, 0 }, { 0, 2 }, { 0, 3 }, { 0, 4 }
},
{
{ 0, 1 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }
}
};

const static uint8_t Adjusted_Tx_Size[ TX_SIZES_ALL ] = {
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
TX_32X16
};

const static uint8_t Coeff_Base_Ctx_Offset[ TX_SIZES_ALL ][ 5 ][ 5 ] = {
{
{ 0, 1, 6, 6, 0 },
{ 1, 6, 6, 21, 0 },
{ 6, 6, 21, 21, 0 },
{ 6, 21, 21, 21, 0 },
{ 0, 0, 0, 0, 0 }
},
{
{ 0, 1, 6, 6, 21 },
{ 1, 6, 6, 21, 21 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 1, 6, 6, 21 },
{ 1, 6, 6, 21, 21 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 1, 6, 6, 21 },
{ 1, 6, 6, 21, 21 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 1, 6, 6, 21 },
{ 1, 6, 6, 21, 21 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 11, 11, 11, 0 },
{ 11, 11, 11, 11, 0 },
{ 6, 6, 21, 21, 0 },
{ 6, 21, 21, 21, 0 },
{ 21, 21, 21, 21, 0 }
},
{
{ 0, 16, 6, 6, 21 },
{ 16, 16, 6, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 0, 0, 0, 0, 0 }
},
{
{ 0, 11, 11, 11, 11 },
{ 11, 11, 11, 11, 11 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 16, 6, 6, 21 },
{ 16, 16, 6, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 }
},
{
{ 0, 11, 11, 11, 11 },
{ 11, 11, 11, 11, 11 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 16, 6, 6, 21 },
{ 16, 16, 6, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 }
},
{
{ 0, 11, 11, 11, 11 },
{ 11, 11, 11, 11, 11 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 16, 6, 6, 21 },
{ 16, 16, 6, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 }
},
{
{ 0, 11, 11, 11, 0 },
{ 11, 11, 11, 11, 0 },
{ 6, 6, 21, 21, 0 },
{ 6, 21, 21, 21, 0 },
{ 21, 21, 21, 21, 0 }
},
{
{ 0, 16, 6, 6, 21 },
{ 16, 16, 6, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 0, 0, 0, 0, 0 }
},
{
{ 0, 11, 11, 11, 11 },
{ 11, 11, 11, 11, 11 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 16, 6, 6, 21 },
{ 16, 16, 6, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 }
},
{
{ 0, 11, 11, 11, 11 },
{ 11, 11, 11, 11, 11 },
{ 6, 6, 21, 21, 21 },
{ 6, 21, 21, 21, 21 },
{ 21, 21, 21, 21, 21 }
},
{
{ 0, 16, 6, 6, 21 },
{ 16, 16, 6, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 },
{ 16, 16, 21, 21, 21 }
}
};

const static uint8_t Mag_Ref_Offset_With_Tx_Class[ 3 ][ 3 ][ 2 ] = {
{ { 0, 1 }, { 1, 0 }, { 1, 1 } },
{ { 0, 1 }, { 1, 0 }, { 0, 2 } },
{ { 0, 1 }, { 1, 0 }, { 2, 0 } }
};


const static uint8_t Tx_Type_Intra_Inv_Set1[ 7 ] = { IDTX, DCT_DCT, V_DCT, H_DCT, ADST_ADST, ADST_DCT, DCT_ADST };
const static uint8_t Tx_Type_Intra_Inv_Set2[ 5 ] = { IDTX, DCT_DCT, ADST_ADST, ADST_DCT, DCT_ADST };
const static uint8_t Tx_Type_Inter_Inv_Set1[ 16 ] = { IDTX, V_DCT, H_DCT, V_ADST, H_ADST, V_FLIPADST, H_FLIPADST,
DCT_DCT, ADST_DCT, DCT_ADST, FLIPADST_DCT, DCT_FLIPADST, ADST_ADST,
FLIPADST_FLIPADST, ADST_FLIPADST, FLIPADST_ADST };
const static uint8_t Tx_Type_Inter_Inv_Set2[ 12 ] = { IDTX, V_DCT, H_DCT, DCT_DCT, ADST_DCT, DCT_ADST, FLIPADST_DCT,
DCT_FLIPADST, ADST_ADST, FLIPADST_FLIPADST, ADST_FLIPADST,
FLIPADST_ADST };
const static uint8_t Tx_Type_Inter_Inv_Set3[ 2 ] = { IDTX, DCT_DCT };

const static uint8_t  Filter_Intra_Mode_To_Intra_Dir[ INTRA_FILTER_MODES ] = {
DC_PRED, V_PRED, H_PRED, D157_PRED, DC_PRED
};

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
int inline constrain(int diff,int  threshold, int damping) {
	if ( !threshold )
		return 0;
	int dampingAdj = Max(0, damping - FloorLog2( threshold ) );
	int sign = (diff < 0) ? -1 : 1;
	return sign * Clip3(0, Abs(diff), threshold - (Abs(diff) >> dampingAdj) );
}
int inline is_inside(int candidateR, int candidateC, int colStart, int colEnd, int rowStart, int rowEnd)
{
	return (candidateC >= colStart &&
			candidateC < colEnd &&
			candidateR >= rowStart &&
			candidateR < rowEnd);
}
int inline  is_inside_filter_region( int candidateR, int candidateC ,int MiCols,int MiRows) { 
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
int inline get_relative_dist(int enable_order_hint,int OrderHintBits, int a, int b)
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
int inline block_shape(int bsize) {
	int w4 = Num_4x4_Blocks_Wide[bsize];
	int h4 = Num_4x4_Blocks_High[bsize];
	if ( h4 > w4 )
	return 0;
	else if ( h4 < w4 )
	return 1;
	else
	return 2;
}
int inline get_wedge_direction(int bsize, int index) {
return Wedge_Codebook[block_shape(bsize)][index][0];
}
int inline get_wedge_xoff(int bsize, int index) {
return Wedge_Codebook[block_shape(bsize)][index][1];
}
int inline get_wedge_yoff(int bsize, int index) {
return Wedge_Codebook[block_shape(bsize)][index][2];
}
inline uint8_t* get_obmc_mask(int length)
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
//获取量化参数
int inline dc_q(int b ,int BitDepth){
	return  Dc_Qlookup[ (BitDepth-8) >> 1 ][ Clip3( 0, 255, b ) ] ;
}

int inline ac_q(int b ,int BitDepth){
	return Ac_Qlookup[ (BitDepth-8) >> 1 ][ Clip3( 0, 255, b ) ] ;
}

//蝶形变换相关
int inline brev(int numBits, int x) {
    int t = 0;
    for (int i = 0; i < numBits; i++) {
        int bit = (x >> i) & 1;
        t += bit << (numBits - 1 - i);
    }
    return t;
}
//butterfly rotation
void inline B(int a, int b, int angle, int flip, int r, int T[]) {
    int x = T[a] * cos128(angle) - T[b] * sin128(angle);
    int y = T[a] * sin128(angle) + T[b] * cos128(angle);
    T[a] = Round2(x, 12);
    T[b] = Round2(y, 12);

    if (flip) {
        int temp = T[a];
        T[a] = T[b];
        T[b] = temp;
    }
}
//Hadamard rotation
void inline H(int a, int b, int flip, int r, int T[]) {
    int x = T[a];
    int y = T[b];
    T[a] = Clip3(-(1 << (r - 1)), (1 << (r - 1)) - 1, x + y);
    T[b] = Clip3(-(1 << (r - 1)), (1 << (r - 1)) - 1, x - y);

    if (flip) {
        int temp = T[a];
        T[a] = T[b];
        T[b] = temp;
    }
}

int inline cos128(int angle) {
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
int inline sin128(int angle) {
    return cos128(angle - 64);
}
int inline filter4_clamp( int value ,int BitDepth) {
	return Clip3( -(1 << (BitDepth - 1)), (1 << (BitDepth - 1)) - 1, value );
}
int inline is_tx_type_in_set(int txSet,int txType,int is_inter)
{
	return is_inter ? Tx_Type_In_Set_Inter[txSet][txType] : Tx_Type_In_Set_Intra[txSet][txType];
}
int inline get_tx_set(int txSz,int is_inter,int reduced_tx_set)
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
inline uint16_t*  get_mrow_scan(int txSz)
{
	if (txSz == TX_4X4)
		return (uint16_t*)Mrow_Scan_4x4;
	else if (txSz == TX_4X8)
		return (uint16_t*)Mrow_Scan_4x8;
	else if (txSz == TX_8X4)
		return (uint16_t*)Mrow_Scan_8x4;
	else if (txSz == TX_8X8)
		return (uint16_t*)Mrow_Scan_8x8;
	else if (txSz == TX_8X16)
		return (uint16_t*)Mrow_Scan_8x16;
	else if (txSz == TX_16X8)
		return (uint16_t*)Mrow_Scan_16x8;
	else if (txSz == TX_16X16)
		return (uint16_t*)Mrow_Scan_16x16;
	else if (txSz == TX_4X16)
		return (uint16_t*)Mrow_Scan_4x16;
	return (uint16_t*)Mrow_Scan_16x4;
}
inline uint16_t* get_mcol_scan(int txSz)
{
	if (txSz == TX_4X4)
		return (uint16_t*)Mcol_Scan_4x4;
	else if (txSz == TX_4X8)
		return (uint16_t*)Mcol_Scan_4x8;
	else if (txSz == TX_8X4)
		return (uint16_t*)Mcol_Scan_8x4;
	else if (txSz == TX_8X8)
		return (uint16_t*)Mcol_Scan_8x8;
	else if (txSz == TX_8X16)
		return (uint16_t*)Mcol_Scan_8x16;
	else if (txSz == TX_16X8)
		return(uint16_t*)Mcol_Scan_16x8;
	else if (txSz == TX_16X16)
		return (uint16_t*)Mcol_Scan_16x16;
	else if (txSz == TX_4X16) 
		return (uint16_t*)Mcol_Scan_4x16;
	return (uint16_t*)Mcol_Scan_16x4;
}
inline uint16_t* get_default_scan(int txSz)
{
	if (txSz == TX_4X4)
		return (uint16_t*)Default_Scan_4x4;
	else if (txSz == TX_4X8)
		return (uint16_t*)Default_Scan_4x8;
	else if (txSz == TX_8X4)
		return (uint16_t*)Default_Scan_8x4;
	else if (txSz == TX_8X8)
		return (uint16_t*)Default_Scan_8x8;
	else if (txSz == TX_8X16)
		return (uint16_t*)Default_Scan_8x16;
	else if (txSz == TX_16X8)
		return (uint16_t*)Default_Scan_16x8;
	else if (txSz == TX_16X16)
		return (uint16_t*)Default_Scan_16x16;
	else if (txSz == TX_16X32)
		return (uint16_t*)Default_Scan_16x32;
	else if (txSz == TX_32X16)
		return (uint16_t*)Default_Scan_32x16;
	else if (txSz == TX_4X16)
		return (uint16_t*)Default_Scan_4x16;
	else if (txSz == TX_16X4)
		return (uint16_t*)Default_Scan_16x4;
	else if (txSz == TX_8X32)
		return (uint16_t*)Default_Scan_8x32;
	else if (txSz == TX_32X8)
		return (uint16_t*)Default_Scan_32x8;
	return (uint16_t*)Default_Scan_32x32;
}
inline uint16_t* get_scan(int txSz,int PlaneTxType)
{
	if (txSz == TX_16X64)
	{
		return (uint16_t*)Default_Scan_16x32;
	}
	if (txSz == TX_64X16)
	{
		return (uint16_t*)Default_Scan_32x16;
	}
	if (Tx_Size_Sqr_Up[txSz] == TX_64X64)
	{
		return (uint16_t*)Default_Scan_32x32;
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
