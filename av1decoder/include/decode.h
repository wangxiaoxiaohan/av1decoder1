class decode{
public:
    decode();
    ~decode();
	int find_mv_stack(int isCompound,SymbolContext *sbCtx, bitSt *bs, TileData *t_data,
								 PartitionData *p_data, BlockData *b_data, AV1DecodeContext *av1ctx);
	static decode& Instance() {
		static decode m_pInstance;
		return m_pInstance;
	}
};