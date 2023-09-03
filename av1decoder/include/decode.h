class decode{
public:
    decode();
    ~decode();
	int find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, TileData *t_data,
								 PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1ctx);
	int find_warp_samples(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int has_overlappable_candidates(PartitionData *p_data, BlockData *b_data);
	int get_above_tx_width(int row, int col,PartitionData *p_data,BlockData *b_data);
	int get_left_tx_height(int row,int col,PartitionData *p_data,BlockData *b_data);
	int init_non_coeff_cdfs(CDFArrays *cdf);
	int setup_past_independence(AV1DecodeContext *av1Ctx);
	int load_cdfs(AV1DecodeContext *av1Ctx,int ctx);
	int load_previous(AV1DecodeContext *av1Ctx);
	static decode& Instance() {
		static decode m_pInstance;
		return m_pInstance;
	}
};