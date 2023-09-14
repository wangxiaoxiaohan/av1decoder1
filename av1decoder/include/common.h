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
// 以下三种自定义 数组，支持访问 -1 下标。内部做了转换，-1实际上为第一个元素。总元素数量比构造传入的值是多一个的
// 一维数组性能较之普通数组损失在6-7层左右
// 二维数组性能一半左右
// 三维未测
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
const static uint8_t Subpel_Filters[6][16][8] = {
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

int inline is_inside(int candidateR, int candidateC, int colStart, int colEnd, int rowStart, int rowEnd)
{
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
uint8_t* inline get_obmc_mask(int length ) {
if ( length == 2 ) {
return Obmc_Mask_2;
} else if ( length == 4 ) {
return Obmc_Mask_4;
} else if ( length == 8 ) {
return Obmc_Mask_8;
} else if ( length == 16 ) {
return Obmc_Mask_16;
} else {
return Obmc_Mask_32;
}
}

#endif
