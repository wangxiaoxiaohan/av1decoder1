#ifndef _COMMON_
#define _COMMON_
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
	INTRA_FRAME,
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



static uint8_t Remap_Lr_Type[4] = {
	RESTORE_NONE,RESTORE_SWITCHABLE,RESTORE_WIENER,RESTORE_SGRPROJ
};


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
int inline Round2(int x,int n){
	return 0;
}

int inline FloorLog2(int x){	
	int s = 0;
	while ( x != 0 ) {
		x = x >> 1;
		s++;
	}
	return s - 1;
}

#endif

