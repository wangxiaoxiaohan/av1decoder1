#include "header_common.h"
class decode{
public:
    decode();
    ~decode();
	int find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, TileData *t_data,
								 PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1ctx);
	int setup_global_mv(int refList,int *mv,
								 BlockData *b_data,AV1DecodeContext *av1Ctx);
	int context_and_clamping(int isCompound, int numNew);

	int find_warp_samples(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int has_overlappable_candidates(PartitionData *p_data, BlockData *b_data);
	int get_above_tx_width(int row, int col,PartitionData *p_data,BlockData *b_data);
	int get_left_tx_height(int row,int col,PartitionData *p_data,BlockData *b_data);
	int init_coeff_cdfs(AV1DecodeContext *av1Ctx);
	int init_non_coeff_cdfs(CDFArrays *cdf);
	int setup_past_independence(AV1DecodeContext *av1Ctx);
	int load_cdfs(AV1DecodeContext *av1Ctx,int ctx);
	int load_previous(AV1DecodeContext *av1Ctx);
	int load_segmentation_params(AV1DecodeContext *av1Ctx,int prevFrame);
	int load_loop_filter_params(AV1DecodeContext *av1Ctx,int prevFrame);
	int load_previous_segment_ids();

	int decode::predict_intra(int plane,int x,int y,int haveLeft,int haveAbove,
				int haveAboveRight,int haveBelowLeft,int mode,int log2W,int log2H,
				PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1);

	static decode& Instance() {
		static decode m_pInstance;
		return m_pInstance;
	}
};