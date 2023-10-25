#ifndef _DECODE_
#define _DECODE_
#include "header_common.h"
#include "cdf.h"
#include "segmentation.h"

class decode{
public:
    decode();
    ~decode();
	int decode_frame_wrapup( AV1DecodeContext *av1Ctx);
	int find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, 
								  BlockData *b_data, AV1DecodeContext *av1Ctx);
	int find_warp_samples(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int has_overlappable_candidates( BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_above_tx_width(int row, int col,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_left_tx_height(int row,int col,BlockData *b_data,AV1DecodeContext *av1Ctx);
	
	int init_coeff_cdfs(AV1DecodeContext *av1Ctx);
	int init_non_coeff_cdfs(CDFArrays *cdf);
	int setup_past_independence(AV1DecodeContext *av1Ctx);
	int load_cdfs(AV1DecodeContext *av1Ctx,int ctx);
	int save_cdfs(AV1DecodeContext *av1Ctx,int ctx);
	int save_grain_params(AV1DecodeContext *av1Ctx,int i);
	int load_grain_params(AV1DecodeContext *av1Ctx,int i);
	int load_previous(AV1DecodeContext *av1Ctx);
	int save_loop_filter_params(AV1DecodeContext *av1Ctx,int i);
	int load_loop_filter_params(AV1DecodeContext *av1Ctx,int prevFrame);
	int save_segmentation_params(AV1DecodeContext *av1Ctx,int i);
	int load_segmentation_params(AV1DecodeContext *av1Ctx,int prevFrame);
	int load_previous_segment_ids(AV1DecodeContext *av1Ctx);


	int set_frame_refs(AV1DecodeContext *av1Ctx);
	int motion_field_estimation(AV1DecodeContext *av1Ctx);
	int motion_filed_project(AV1DecodeContext *av1Ctx,int src,int dstSign);
	int get_mv_projection(int *mv,int numerator,int denominator,int *projMv);
	int get_block_position(AV1DecodeContext *av1Ctx,int *PosX8,int *PosY8, int x8, int y8, int dstSign, int *projMv );

	int scan_row(int deltaRow,int isCompound,
				BlockData *b_data,AV1DecodeContext *av1Ctx);
	int scan_col(int deltaCol,int isCompound,
			BlockData *b_data,AV1DecodeContext *av1Ctx);

	int scan_point(int deltaRow,int deltaCol,int isCompound,
					BlockData *b_data,AV1DecodeContext *av1Ctx);
	int add_ref_mv_candidate(int mvRow,int  mvCol,int  isCompound,int weight,
								BlockData *b_data,AV1DecodeContext *av1Ctx);
	int search_stack(int mvRow,int mvCol,int candList,int weight,
						BlockData *b_data,AV1DecodeContext *av1Ctx);
	int compound_search_stack(int  mvRow ,int  mvCol,int weight,
				BlockData *b_data,AV1DecodeContext *av1Ctx);
	
	int temporal_scan(int isCompound,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int setup_global_mv(int refList,int *mv,
								 BlockData *b_data,AV1DecodeContext *av1Ctx);
	int lower_mv_precision(AV1DecodeContext *av1Ctx,int *candMv);
	int lower_precision(int *candMv,AV1DecodeContext *av1Ctx);
	int add_tpl_ref_mv(int deltaRow, int deltaCol, int isCompound,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int Sorting(int start,int end ,int isCompound,AV1DecodeContext *av1Ctx);
	void swap_stack(int i, int j, int isCompound, int RefStackMv[][2][2], int WeightStack[],AV1DecodeContext *av1Ctx);
	int extra_search(int isCompound, BlockData *b_data, AV1DecodeContext *av1Ctx);
	int add_extra_mv_candidate(int mvRow, int mvCol, int isCompound,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int context_and_clamping(int isCompound, int numNew,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int clamp_mv_row(int  mvec, int border ,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int clamp_mv_col(int mvec,int border ,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_tx_size(int plane,int txSz,int subsampling_x, int subsampling_y,BlockData *b_data);
	int residual(SymbolContext *sbCtx,bitSt *bs,
				BlockData *b_data, AV1DecodeContext *av1Ctx);
	int transform_tree(int startX, int startY,int w,int h,SymbolContext *sbCtx,bitSt *bs,
					BlockData *b_data, AV1DecodeContext *av1Ctx);
	int transform_block(int plane,int baseX,int baseY,int txSz,int x,int y,SymbolContext *sbCtx,bitSt *bs,
							 BlockData *b_data, AV1DecodeContext *av1Ctx);
	int predict_intra(int plane,int x,int y,int haveLeft,int haveAbove,
				int haveAboveRight,int haveBelowLeft,int mode,int log2W,int log2H,
				BlockData *b_data,AV1DecodeContext *av1Ctx);
	int coeffs(int plane,int startX,int startY,int txSz,SymbolContext *sbCtx,bitSt *bs,
							 BlockData *b_data, AV1DecodeContext *av1Ctx);
	int transform_type(int x4,int  y4,int txSz,SymbolContext *sbCtx,bitSt *bs,
					BlockData *b_data, AV1DecodeContext *av1Ctx);
	int cacluteAllZeroCtx(int plane,int txSz, int x4,int y4,int w4,int h4, BlockData *b_data,AV1DecodeContext *av1Ctx);
	int compute_tx_type(int plane, int txSz,int blockX,int blockY,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_coeff_base_ctx(int txSz, int plane, int blockX, int blockY, int pos, int c, int isEob,
						BlockData *b_data,AV1DecodeContext *av1Ctx);
	int add_sample(int deltaRow,int deltaCol,
				BlockData *b_data,AV1DecodeContext *av1Ctx);
	void basicIntraPrediction(int w, int h, uint16_t** pred,BlockData *b_data) ;
	int recursiveIntraPrdiction(int w, int h,uint16_t **pred,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int directionalIntraPrediction(int plane,int x,int y,int haveLeft,int haveAbove,
									int mode ,int w ,int h ,int maxX,int maxY,uint16_t **pred,
									BlockData *b_data ,AV1DecodeContext *av1Ctx);
	int filterCornor(Array16 *LeftCol,Array16 *AboveRow);
	int intrafilterType(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int is_smooth(int row, int col, int plane,AV1DecodeContext *av1Ctx) ;
	int get_filter_type(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx) ;
	int intraEdgeFilterStrengthSelection(int w, int h, int filterType, int delta);
	int intraEdgeFilter(int sz, int strength, int left,BlockData *b_data);
	int intraEdgeUpsampleSelection(int w, int h, int filterType, int delta);
	int intraEdgeUpsample(int numPx,int dir,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int smoothIntraPrediction(int mode, int log2W, int log2H, int w, int h, uint16_t **pred,BlockData *b_data);
	int DCIntraPrediction(int haveLeft ,int haveAbove,int log2W,int log2H,int w,int h,uint16_t **pred,
									BlockData *b_data,AV1DecodeContext *av1Ctx);
	int predict_inter(int plane, int x, int y,int w ,int h ,int candRow,int candCol,int IsInterIntra,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int roundingVariablesDerivation(int isCompound,AV1DecodeContext *av1Ctx);
	int warpEstimation(int CandList[4][4], int LocalWarpParams[6], int *LocalValid,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int setupShear(int *warpParams,int *warpValid,int *alpha,int *beta,int *gamma,int *delta);
	int resolveDivisor(int d, int *divShift, int *divFactor);
	int motionVectorScaling(int plane, int refIdx, int x, int y, int mv[2],
								int *startX,int *startY, int *stepX,int *stepY, AV1DecodeContext *av1Ctx);
	int blockWarp(int useWarp,int plane,int refList,int x,int y,
						int i8,int j8,int w,int h,uint16_t **pred,int LocalWarpParams[6],
						BlockData *b_data,AV1DecodeContext *av1Ctx);
	int block_inter_prediction(int plane, int refIdx, int x, int y, int xStep, int yStep, 
							int w, int h, int candRow, int candCol,uint16_t **pred,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int wedgeMask(int WMW,int WMH,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int intraModeVariantMask(int w, int h,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int differenceWeightMask(uint16_t ***preds, int w, int h,BlockData *b_data,  AV1DecodeContext *av1Ctx);
	int distanceWeights(int candRow,int candCol,int *FwdWeight,int *BckWeight,  
							 AV1DecodeContext *av1Ctx);
	int maskBlend(uint16_t ***preds,int plane , int dstX,int dstY,int w,int h,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int overlappedMotionCompensation(int plane, int w ,int h,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int predict_overlap(int MiSize,int plane ,int x4,int y4,int predW,int predH,int subX,int subY ,
				int candRow,int candCol ,int pass,uint8_t *mask,BlockData *b_data, AV1DecodeContext *av1Ctx);
	int OverlapBlending(int plane ,int predX,int predY,int predW,int predH ,int pass,
							uint16_t **obmcPred,uint8_t *mask,AV1DecodeContext *av1Ctx);
	int predict_palette(int plane, int startX, int startY, int x, int y, int txSz,
						BlockData *b_data,AV1DecodeContext *av1Ctx);
	int predict_chroma_from_luma(int plane, int startX, int startY, int txSz,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_dc_quant(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_ac_quant(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int reconstruct(int plane, int x, int y, int txSz,BlockData *b_data,AV1DecodeContext *av1Ctx);


	int inverseDCTArrayPermutation(int T[],int n);
	int inverseDCT(int T[], int n, int r);
	void inverseADSTInputArrayPermutation(int* T, int n);
	void inverseADSTOutputArrayPermutation(int* T, int n);
	void inverseADST4(int* T, int r);
	void inverseADST8(int* T, int r);
	void inverseADST16(int* T, int r);
	void inverseADST(int T[],int n,int r);
	void inverseWalshHadamardTransform(int* T, int shift) ;
	void inverseIdentityTransform4(int* T);
	void inverseIdentityTransform8(int* T);
	void inverseIdentityTransform16(int* T);
	void inverseIdentityTransform32(int* T);
	void inverseIdentityTransform(int *T,int n);
	void twoDInverseTransformBlock(int txSz,int **Residual,BlockData *b_data,AV1DecodeContext *av1Ctx) ;


	void loopFilter(AV1DecodeContext *av1Ctx);
	void edgeLoopFilter(int plane, int pass, int row, int col, AV1DecodeContext *av1Ctx);
	int filterSizeProcess(int txSz, int prevTxSz, int pass, int plane);
	void adaptiveFilterStrength(int row, int col, int plane, int pass, int* lvl, int* limit, int* blimit, int* thresh,
							AV1DecodeContext *av1Ctx) ;
	int adaptiveFilterStrengthSelection(int segment, int ref, int modeType, int deltaLF, int plane, int pass,
										AV1DecodeContext *av1Ctx);
	void sampleFiltering(int x,int  y,int  plane, int limit,int  blimit,int  thresh,int  dx,int  dy,
						int  filterSize ,AV1DecodeContext *av1Ctx);
	void filterMaskProcess(int x,int y,int plane,int limit,int blimit,int thresh,int dx,int dy,int filterSize,
						int *hevMask,int *filterMask,int *flatMask ,int *flatMask2,AV1DecodeContext *av1Ctx);
	void narrowFilter(int x,int y,int plane,int dx ,int dy,int *hevMask,AV1DecodeContext *av1Ctx);
	void wideFilter(int x,int y,int plane,int dx ,int dy,int log2Size,AV1DecodeContext *av1Ctx);



	void cdef(AV1DecodeContext *av1Ctx);
	void cdefBlock(int r, int c, int idx, AV1DecodeContext *av1Ctx);
	void cdefDirectionProcess(int r, int c, int *yDir, int *var,
									AV1DecodeContext *av1Ctx);
	void cdefFilter(int plane, int r, int c, int priStr, int secStr, int damping, int dir,
							 AV1DecodeContext *av1Ctx );
	int cdef_get_at(int plane,int x0,int y0,int i, int j,int dir,int k,int sign,int subX,int subY,
							int * CdefAvailable,uint16_t ***CurrFrame,AV1DecodeContext *av1Ctx);


	void upscalingProcess(uint16_t ***inputFrame,uint16_t ***outputFrame,AV1DecodeContext *av1Ctx);

	void loopRestoration(AV1DecodeContext *av1Ctx);
	void loopRestoreBlock(int plane,int row ,int col,AV1DecodeContext *av1Ctx);
	void wienerFilter(int plane ,int unitRow,int unitCol,int x,int y,int w,int h,
								 AV1DecodeContext *av1Ctx);
	void wienerCoefficient(int coeff[3],int filter[7]);
	int getSourceSample(int plane ,int x,int y, AV1DecodeContext *av1Ctx);
	void selfGuidedFilter(int plane,int unitRow,int unitCol, int x,int y,int w,int h,
								AV1DecodeContext *av1Ctx);
	void boxFilter(int plane,int x,int y,int w,int h,int set ,int pass,int **F,
					AV1DecodeContext *av1Ctx);

	void output(AV1DecodeContext *av1Ctx);
	void intermediateOutputPreparation(int *w,int *h,int *subX,int *subY,int *bidepth,AV1DecodeContext *av1Ctx);
	void filmGrainSynthesis(int w, int h, int subX, int subY,AV1DecodeContext *av1Ctx);
	int get_random_number( int bits ,int *RandomRegister);
	void generateGrain(int GrainMin,int GrainMax, int *RandomRegister ,AV1DecodeContext *av1Ctx) ;
	void scalingLookupInitialization(AV1DecodeContext *av1Ctx);
	int get_x(int plane, int i,AV1DecodeContext *av1Ctx);
	int get_y(int plane, int i,AV1DecodeContext *av1Ctx);
	void addNoiseSynthesis(int GrainMin,int GrainMax,int * RandomRegister,int w, int h, int subX, int subY, AV1DecodeContext *av1Ctx);
	void motionFieldMotionVectorStorage(AV1DecodeContext *av1Ctx);
	void referenceFrameUpdate(AV1DecodeContext *av1Ctx);
	void referenceFrameLoading( AV1DecodeContext *av1Ctx);
	static decode& Instance() {
		static decode m_pInstance;
		return m_pInstance;
	}
private :
	Symbol *sb;
	segmentation *seg_instance;
};

#endif