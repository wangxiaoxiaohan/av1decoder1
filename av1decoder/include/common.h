#ifndef _COMMON_
#define _COMMON_
#include "stdio.h"
#include "stdint.h"
enum tristate{
	ONE = 0,
	TWO = 1,
	THREE = 2,
};
#define MAX_OPERATING_POINTS 32//A.3.


#define MAX_CDEF_STRENGTHS 7

#define MAX_SEGMENTS 8
#define MAX_LOOP_FILTER 63

#define SEG_LVL_MAX 8 //这个表示一个段内的 8个“feature”，(不是一个帧内最大8个段 ，这有另一个宏MAX_SEGMENTS 来表示)
//每一个feature的index 用宏来表示，并说明功能，
//比如下面的 SEG_LVL_REF_FRAME， SEG_LVL_GLOBALMV
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
#define	MAX_TILE_COLS 64

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

enum em_interpolation_filters{
	EIGHTTAP = 0,
	EIGHTTAP_SMOOTH = 1,
	EIGHTTAP_SHARP = 2,
	BILINEAR = 3,
	SWITCHABLE = 4,
};
enum em_color_primaries{
	 CP_BT_709  = 1, //BT.709
	 CP_UNSPECIFIED = 2, // Unspecified
	 CP_BT_470_M = 4, //BT.470 System M (historical)
	 CP_BT_470_B_G = 5, //BT.470 System B, G (historical)
	 CP_BT_601  = 6, //BT.601
	 CP_SMPTE_240 = 7, //SMPTE 240
	 CP_GENERIC_FILM = 8, //Generic film (color filters using illuminant C)
	 CP_BT_2020 = 9,   //BT.2020, BT.2100
	 CP_XYZ = 10,  //SMPTE 428 (CIE 1921 XYZ)
	 CP_SMPTE_431 = 11, //SMPTE RP 431-2
	 CP_SMPTE_432 = 12, //SMPTE EG 432-1
	 CP_EBU_3213 = 22, //EBU Tech. 3213-E
};
enum em_transfer_characteristics{
	TC_RESERVED_0 = 0,    //For future use
	TC_BT_709 ,        // BT.709
	TC_UNSPECIFIED ,   //Unspecified
	TC_RESERVED_3 ,   //For future use
	TC_BT_470_M  ,     //  BT.470 System M (historical)
	TC_BT_470_B_G , //BT.470 System B, G (historical)
	TC_BT_601 ,  //BT.601
	TC_SMPTE_240 , //SMPTE 240 M
	TC_LINEAR ,  // Linear
	TC_LOG_100 , //Logarithmic (100 : 1 range)
	TC_LOG_100_SQRT10 , //Logarithmic (100 * Sqrt(10) : 1 range)
	TC_IEC_61966 , //IEC 61966-2-4
	TC_BT_1361 , //BT.1361
	TC_SRGB  , //sRGB //or sYCC
	TC_BT_2020_10_BIT , //BT.2020 10-bit systems
	TC_BT_2020_12_BIT , //BT.2020 12-bit systems
	TC_SMPTE_2084 , //SMPTE ST 2084, ITU BT.2100 PQ
	TC_SMPTE_428 , //SMPTE ST 428
	TC_HLG,     //BT.2100 HLG, ARIB STD-B67
};

enum em_matrix_coefficients{
	 MC_IDENTITY = 0, //Identity matrix
	 MC_BT_709, //BT.709
	 MC_UNSPECIFIED, //Unspecified
	 MC_RESERVED_3, //For future use
	 MC_FCC ,  //US FCC 73.628
	 MC_BT_470_B_G, //BT.470 System B, G (historical)
	 MC_BT_601,   //BT.601
	 MC_SMPTE_240,   //SMPTE 240 M
	 MC_SMPTE_YCGCO, //YCgCo
	 MC_BT_2020_NCL, //BT.2020 non-constant luminance, BT.2100 YCbCr
	 MC_BT_2020_CL ,  //BT.2020 constant luminance
	 MC_SMPTE_2085,  //SMPTE ST 2085 YDzDx
	 MC_CHROMAT_NCL, //Chromaticity-derived non-constant luminance
	 MC_CHROMAT_CL,  //Chromaticity-derived constant luminance
	 MC_ICTCP,  //BT.2100 ICtCp

};
enum em_chroma_sample_position{

	CSP_UNKNOWN    = 0 ,//Unknown(in this case the source video transfer function must be ignaled outside the AV1 bitstream)										
	CSP_VERTICAL,   // Horizontally co-located with (0, 0) luma sample, vertical position in he middle between two luma samples
	CSP_COLOCATED,//co-located with (0, 0) luma sample
	CSP_RESERVED,

};

enum em_frame_type{
	KEY_FRAME = 0,
	INTER_FRAME = 1,
	INTRA_ONLY_FRAME = 2,
	SWITCH_FRAME = 3
};
enum em_ref_frame_type{
	NONE  = -1,
	INTRA_FRAME = 0,
	LAST_FRAME,
	LAST2_FRAME,
	LAST3_FRAME,
	GOLDEN_FRAME,
	BWDREF_FRAME,
	ALTREF2_FRAME,
	ALTREF_FRAME,
};

enum obuType{
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
enum em_frame_restoration_type{
	RESTORE_NONE = 0,
	RESTORE_WIENER = 1,
	RESTORE_SGRPROJ = 2,
	RESTORE_SWITCHABLE =3
};

enum em_TxMode{
	ONLY_4X4 = 0,
	TX_MODE_LARGEST	 = 1,
	TX_MODE_SELECT = 2
};
enum em_SubSize{
	BLOCK_4X4  = 0,
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
	BLOCK_INVALID  = 22
};
enum em_partition{
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
enum em_intra_frame_y_mode{
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
enum em_motion_mode{
	SIMPLE = 0,
	OBMC,
	LOCALWARP
};
enum em_compound_type{
	COMPOUND_WEDGE = 0,
	COMPOUND_DIFFWTD,
	COMPOUND_AVERAGE,
	COMPOUND_INTRA,
	COMPOUND_DISTANCE
};
enum em_ymode{
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
enum em_mv_joint{
	MV_JOINT_ZERO = 0,
	MV_JOINT_HNZVZ ,
	MV_JOINT_HZVNZ ,
	MV_JOINT_HNZVNZ
};
enum em_uv_mode{
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
enum em_mv_class {
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

enum em_signU {
	CFL_SIGN_ZERO = 0,
	CFL_SIGN_NEG,
	CFL_SIGN_POS,
};



const static uint8_t Remap_Lr_Type[4] = {
	RESTORE_NONE,RESTORE_SWITCHABLE,RESTORE_WIENER,RESTORE_SGRPROJ
};
const static int8_t Wiener_Taps_Mid[3] = {
	3, -7, 15
};
const static int8_t Sgrproj_Xqd_Mid[2] = {
	-32, 31
};

const static int8_t Subsampled_Size[ BLOCK_SIZES ][ 2 ][ 2 ] = {
{ { BLOCK_4X4, BLOCK_4X4}, {BLOCK_4X4, BLOCK_4X4} },
{ { BLOCK_4X8, BLOCK_4X4}, {BLOCK_INVALID, BLOCK_4X4} },
{ { BLOCK_8X4, BLOCK_INVALID}, {BLOCK_4X4, BLOCK_4X4} },
{ { BLOCK_8X8, BLOCK_8X4}, {BLOCK_4X8, BLOCK_4X4} },
{ {BLOCK_8X16, BLOCK_8X8}, {BLOCK_INVALID, BLOCK_4X8} },
{ {BLOCK_16X8, BLOCK_INVALID}, {BLOCK_8X8, BLOCK_8X4} },
{ {BLOCK_16X16, BLOCK_16X8}, {BLOCK_8X16, BLOCK_8X8} },
{ {BLOCK_16X32, BLOCK_16X16}, {BLOCK_INVALID, BLOCK_8X16} },
{ {BLOCK_32X16, BLOCK_INVALID}, {BLOCK_16X16, BLOCK_16X8} },
{ {BLOCK_32X32, BLOCK_32X16}, {BLOCK_16X32, BLOCK_16X16} },
{ {BLOCK_32X64, BLOCK_32X32}, {BLOCK_INVALID, BLOCK_16X32} },
{ {BLOCK_64X32, BLOCK_INVALID}, {BLOCK_32X32, BLOCK_32X16} },
{ {BLOCK_64X64, BLOCK_64X32}, {BLOCK_32X64, BLOCK_32X32} },
{ {BLOCK_64X128, BLOCK_64X64}, {BLOCK_INVALID, BLOCK_32X64} },
{ {BLOCK_128X64, BLOCK_INVALID}, {BLOCK_64X64, BLOCK_64X32} },
{ {BLOCK_128X128, BLOCK_128X64}, {BLOCK_64X128, BLOCK_64X64} },
{ {BLOCK_4X16, BLOCK_4X8}, {BLOCK_INVALID, BLOCK_4X8} },
{ {BLOCK_16X4, BLOCK_INVALID}, {BLOCK_8X4, BLOCK_8X4} },
{ {BLOCK_8X32, BLOCK_8X16}, {BLOCK_INVALID, BLOCK_4X16} },
{ {BLOCK_32X8, BLOCK_INVALID}, {BLOCK_16X8, BLOCK_16X4} },
{ {BLOCK_16X64, BLOCK_16X32}, {BLOCK_INVALID, BLOCK_8X32} },
{ {BLOCK_64X16, BLOCK_INVALID}, {BLOCK_32X16, BLOCK_32X8} },
};
const static int8_t  Num_4x4_Blocks_Wide[ BLOCK_SIZES ] = {
1, 1, 2, 2, 2, 4, 4, 4, 8, 8, 8,
16, 16, 16, 32, 32, 1, 4, 2, 8, 4, 16
};
const static int8_t Num_4x4_Blocks_High[ BLOCK_SIZES ] = {
1, 2, 1, 2, 4, 2, 4, 8, 4, 8, 16,
8, 16, 32, 16, 32, 4, 1, 8, 2, 16, 4
};
const static int8_t Size_Group[ BLOCK_SIZES ] = {
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3,
3, 3, 3, 3, 3, 0, 0, 1, 1, 2, 2
};

const static int8_t Mi_Width_Log2[ BLOCK_SIZES ] = {
0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
4, 4, 4, 5, 5, 0, 2, 1, 3, 2, 4
};

const static int8_t Mi_Height_Log2[ BLOCK_SIZES ] = {
0, 1, 0, 1, 2, 1, 2, 3, 2, 3, 4,
3, 4, 5, 4, 5, 2, 0, 3, 1, 4, 2
};
const static int8_t Intra_Mode_Context[ INTRA_MODES ] = {
0, 1, 2, 3, 4, 4, 4, 4, 3, 0, 1, 2, 0
};

const static int8_t Partition_Subsize[10][BLOCK_SIZES] = {
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

int inline tile_log2(int  blkSize, int target){
	int k;
	for (k = 0; (blkSize << k) < target; k++ ) {
	}
	return k;

}
// to do 用 c++ 模板写
int inline Min(int a,int b){
	return a <= b ? a:b;
}
int inline Max(int a,int b){
	return a >= b ? a:b;
}
int inline Clip3(int a,int b,int c){
	return (c < a || c > b) ? ((c < a) ? a :b) : c;
}
int inline Clip1(int x,int BitDepth){
	return Clip3(0,1 << BitDepth,x);
}
int inline Round2(int x,int n){
	if ( n == 0 )
		return x;
	return ( x + ( 1 << (n - 1) ) ) >> n;
}
int inline Round2Signed(int x,int n){
	return x >= 0 ? (Round2(x,n)):-(Round2(-x,n));
}
int inline FloorLog2(int x){	
	int s = 0;
	while ( x != 0 ) {
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

int inline is_inside(int candidateR,int  candidateC ,int colStart, int colEnd,int rowStart, int rowEnd) { 
	return ( candidateC >= colStart &&
	candidateC < colEnd &&
	candidateR >= rowStart &&
	candidateR < rowEnd );
}
int inline neg_deinterleave(int diff,int ref,int max)
{
	if (!ref)
		return diff ;
	if (ref >= (max - 1)) 
		return max - diff - 1 ;
	if (2 * ref < max)
		{
			if (diff <= 2 * ref)
			{
				if (diff & 1)
					return ref + ((diff + 1) >> 1);
				else return 
					ref - (diff >> 1);
			}
			return diff;
		}
	else
	{
		if (diff <= 2 * (max - ref - 1))
		{
			if (diff & 1)
				return ref + ((diff + 1) >> 1);
			 else return 
			 	ref - (diff >> 1);
		}
		return max - (diff + 1);
	}
}
int inline get_plane_residual_size( int subsize, int plane ,int subsampling_x,int subsampling_y){ 
	int subx = plane > 0 ? subsampling_x : 0;
	int suby = plane > 0 ? subsampling_y : 0;
	return Subsampled_Size[ subsize ][ subx ][ suby ];
}
int inline is_directional_mode(int mode ) { 
	if ( ( mode >= V_PRED ) && ( mode <= D67_PRED ) ) {
		return 1;
	}
	return 0;
}
int inline av1sort(int *array,int min ,int max){

	
}
//checks that the position is within the same 64x64 block
int inlie check_sb_border(int MiRow ,int MiCol,int deltaRow, int deltaCol ) {
	row = (MiRow & 15) + deltaRow;
	col = (MiCol & 15) + deltaCol;
	return ( row >= 0 && row < 16 && col >= 0 && col < 16 );
}

#endif

