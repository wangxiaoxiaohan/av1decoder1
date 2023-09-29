#include "header_common.h"
#include "cdf.h"
#include "segmentation.h"

class decode{
public:
    decode();
    ~decode();
	int find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, TileData *t_data,
								 PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1ctx);
	int find_warp_samples(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int has_overlappable_candidates(PartitionData *p_data, BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_above_tx_width(int row, int col,PartitionData *p_data,BlockData *b_data);
	int get_left_tx_height(int row,int col,PartitionData *p_data,BlockData *b_data);
	int init_coeff_cdfs(AV1DecodeContext *av1Ctx);
	int init_non_coeff_cdfs(CDFArrays *cdf);
	int setup_past_independence(AV1DecodeContext *av1Ctx);
	int load_cdfs(AV1DecodeContext *av1Ctx,int ctx);
	int load_previous(AV1DecodeContext *av1Ctx);
	int load_segmentation_params(AV1DecodeContext *av1Ctx,int prevFrame);
	int load_loop_filter_params(AV1DecodeContext *av1Ctx,int prevFrame);
	int load_previous_segment_ids(AV1DecodeContext *av1Ctx);
	int set_frame_refs(AV1DecodeContext *av1Ctx);
	int motion_field_estimation(AV1DecodeContext *av1Ctx);
	int motion_filed_project(AV1DecodeContext *av1Ctx,int src,int dstSign);
	int get_mv_projection(int *mv,int numerator,int denominator,int *projMv);
	int get_block_position(AV1DecodeContext *av1Ctx,int *PosX8,int *PosY8, int x8, int y8, int dstSign, int *projMv );
	int find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, TileData *t_data,
								 PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1ctx);
	int scan_row(int deltaRow,int isCompound,
				TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int scan_col(int deltaCol,int isCompound,
			TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);

	int scan_point(int deltaRow,int deltaCol,int isCompound,
					TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int add_ref_mv_candidate(int mvRow,int  mvCol,int  isCompound,int weight,
								TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int search_stack(int mvRow,int mvCol,int candList,int weight,
						TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int compound_search_stack(int  mvRow ,int  mvCol,int weight,
				TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	
	int temporal_scan(int isCompound,TileData *t_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int extra_search(int isCompound);
	int setup_global_mv(int refList,int *mv,
								 BlockData *b_data,AV1DecodeContext *av1Ctx);
	int lower_mv_precision(AV1DecodeContext *av1Ctx,int *candMv);
	int lower_precision(int *candMv,AV1DecodeContext *av1Ctx);
	int add_tpl_ref_mv(int deltaRow, int deltaCol, int isCompound,TileData *t_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int Sorting(int start,int end ,int isCompound,AV1DecodeContext *av1Ctx);
	void swap_stack(int i, int j, int isCompound, int RefStackMv[][2][2], int WeightStack[],AV1DecodeContext *av1Ctx);
	int extra_search(int isCompound,TileData *t_data,PartitionData* p_data, BlockData *b_data, AV1DecodeContext *av1Ctx);
	int add_extra_mv_candidate(int mvRow, int mvCol, int isCompound,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int context_and_clamping(int isCompound, int numNew,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int clamp_mv_row(int  mvec, int border ,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int clamp_mv_col(int mvec,int border ,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_tx_size(int plane,int txSz,int subsampling_x, int subsampling_y,BlockData *b_data);
	int residual(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,PartitionData *p_data,
				BlockData *b_data, AV1DecodeContext *av1Ctx);
	int transform_tree(int startX, int startY,int w,int h,SymbolContext *sbCtx,bitSt *bs,
					TileData *t_data,PartitionData *p_data,BlockData *b_data, AV1DecodeContext *av1Ctx);
	int transform_block(int plane,int baseX,int baseY,int txSz,int x,int y,SymbolContext *sbCtx,bitSt *bs,
							TileData *t_data,PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1Ctx);
	int predict_intra(int plane,int x,int y,int haveLeft,int haveAbove,
				int haveAboveRight,int haveBelowLeft,int mode,int log2W,int log2H,
				TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int predict_palette(int plane, int startX, int startY, int x, int y, int txSz);
	int predict_chroma_from_luma(int plane, int startX, int startY, int txSz);
	int coeffs(int plane,int startX,int startY,int txSz,SymbolContext *sbCtx,bitSt *bs,
							TileData *t_data,PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1Ctx);
	int transform_type(int x4,int  y4,int txSz,SymbolContext *sbCtx,bitSt *bs,
					BlockData *b_data, AV1DecodeContext *av1Ctx);
	int cacluteAllZeroCtx(int plane,int txSz, int x4,int y4,int w4,int h4,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int compute_tx_type(int plane, int txSz,int blockX,int blockY,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_coeff_base_ctx(int txSz, int plane, int blockX, int blockY, int pos, int c, int isEob,
						BlockData *b_data,AV1DecodeContext *av1Ctx);
	int add_sample(int deltaRow,int deltaCol,TileData *t_data,PartitionData *p_data,
				BlockData *b_data,AV1DecodeContext *av1Ctx);
	void basicIntraPrediction(int w, int h, uint8_t** pred,BlockData *b_data) ;
	int recursiveIntraPrdiction(int w, int h,uint8_t **pred,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int directionalIntraPrediction(int plane,int x,int y,int haveLeft,int haveAbove,
									int mode ,int w ,int h ,int maxX,int maxY,uint8_t **pred,
									BlockData *b_data ,AV1DecodeContext *av1Ctx);
	int filterCornor(Array8 *LeftCol,Array8 *AboveRow);
	int intrafilterType(int plane,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int is_smooth(int row, int col, int plane,PartitionData *p_data) ;
	int get_filter_type(int plane,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx) ;
	int intraEdgeFilterStrengthSelection(int w, int h, int filterType, int delta);
	int intraEdgeFilter(int sz, int strength, int left,BlockData *b_data);
	int intraEdgeUpsampleSelection(int w, int h, int filterType, int delta);
	int intraEdgeUpsample(int numPx,int dir,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int smoothIntraPrediction(int mode, int log2W, int log2H, int w, int h, uint8_t **pred,BlockData *b_data);
	int DCIntraPrediction(int haveLeft ,int haveAbove,int log2W,int log2H,int w,int h,uint8_t **pred,
									BlockData *b_data,AV1DecodeContext *av1Ctx);
	int predict_inter(int plane, int x, int y,int w ,int h ,int candRow,int candCol,
							TileData *t_data,PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int roundingVariablesDerivation(int isCompound,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int warpEstimation(int **CandList, int LocalWarpParams[6], int *LocalValid,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int setupShear(int *warpParams,int *warpValid,int *alpha,int *beta,int *gamma,int *delta);
	int resolveDivisor(int d, int *divShift, int *divFactor);
	int motionVectorScaling(int plane, int refIdx, int x, int y, int mv[2],
								int *startX,int *startY, int *stepX,int *stepY, AV1DecodeContext *av1Ctx);
	int blockWarp(int useWarp,int plane,int refList,int x,int y,
						int i8,int j8,int w,int h,uint8_t **pred,int LocalWarpParams[6],AV1DecodeContext *av1Ctx);
	int setupShear(int *warpParams,int *warpValid,int *alpha,int *beta,int *gamma,int *delta);
	static decode& Instance() {
		static decode m_pInstance;
		return m_pInstance;
	}
private :
	Symbol *sb;
	segmentation *seg_instance;
};