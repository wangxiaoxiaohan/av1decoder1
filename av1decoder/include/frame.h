#ifndef _FRAME_
#define _FRAME_
#include "header_common.h"
#include "av1decoder.h"
#include "obu.h"
#include "cdf.h"
#include "decode.h"
#include "segmentation.h"

class frame{
public:
    frame();
	~frame();
	void allocDecodeContext(AV1DecodeContext *av1Ctx);
	void allocFrameContext(frameHeader *frameHdr,int wbuffersize,int hbuffersize,FrameContext **fCtx);

	void releaseDecodeContext(AV1DecodeContext *av1Ctx);
	void releaseFrameContext(frameHeader *frameHdr,int WBuffMiSize,int HBuffMiSize,FrameContext *fCtx);
	void init_symbol(SymbolContext *sbCtx,bitSt *bs,int sz,AV1DecodeContext *av1Ctx);
	void exit_symbol(SymbolContext *sbCtx,bitSt *bs,int TileNum,AV1DecodeContext *av1Ctx);
    void frame_end_update_cdf(AV1DecodeContext *av1Ctx);

	int readTileInfo(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr);
	int readQuantizationParams(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr);
	int read_interpolation_filter(bitSt *bs,frameHeader *frameHdr);
	int readSuperresParams(bitSt *bs,sequenceHeader *seqHdr,sizeInfo *si);
	int readSegmentationParams(bitSt *bs, sequenceHeader *seqHdr, frameHeader *frameHdr);
	int readLoopFilterParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader);
	int readCdefParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader);
	int readLrParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader);
	int readSkipModeParams(bitSt *bs, frameHeader *frameHdr,AV1DecodeContext *av1Ctx,sequenceHeader *seqHeader);
	int readGlobalMotionParams(bitSt *bs, frameHeader *frameHdr);
	int readFilmGrainParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHdr,AV1DecodeContext *av1Ctx);
	int readDeltaQuantizerParams(bitSt *bs, frameHeader *frameHdr);
	int readDeltaLoopfilterParams(bitSt *bs, frameHeader *frameHdr);
	int readRenderSize(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr,sizeInfo *out);
	int readFrameSize(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr,sizeInfo *out);
	int parseUncompressedHeader(int sz,bitSt *bs,AV1DecodeContext * av1Ctx,sequenceHeader *seqHdr,obuHeader *obuheader, frameHeader *out);
	int read_delta_q(bitSt *bs);
	int read_global_param(frameHeader *frameHdr,bitSt *bs, int type,int ref,int idx );

	int decode_tile(SymbolContext *sbCtx, bitSt *bs,AV1DecodeContext *av1Ctx);
	int decode_partition(SymbolContext *sbCtx,bitSt *bs,int r,int c,int sbSize, AV1DecodeContext *av1Ctx);
	int decodeFrame(int sz, bitSt *bs, AV1DecodeContext *av1Ctx);
	int decode_block(SymbolContext *sbCtx,bitSt *bs,
							int r,int c,int subSize, AV1DecodeContext *av1Ctx);

	int mode_info(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int intra_frame_mode_info(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx );
	int inter_frame_mode_info(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int read_segment_id(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int read_cdef(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int read_delta_qindex(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int read_delta_lf(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int assign_mv(int isCompound,SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int read_mv_component(int MvCtx,int comp,SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int intra_angle_info_y(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int intra_angle_info_uv(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int read_cfl_alphas(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx);

	int palette_mode_info(SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int filter_intra_mode_info(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int get_palette_cache(int plane,BlockData *b_data,AV1DecodeContext *av1Ctx);

	int inter_segment_id(int preSkip,SymbolContext *sbCtx, bitSt *bs,
								BlockData *b_data, AV1DecodeContext *av1Ctx);


	int mark_ref_frames(AV1DecodeContext *av1Ctx,int  idLen);
	int read_ref_frames(SymbolContext *sbCtx, bitSt *bs, 
								  BlockData *b_data, AV1DecodeContext *av1Ctx);

	int inter_block_mode_info(SymbolContext *sbCtx, bitSt *bs, 
								  BlockData *b_data, AV1DecodeContext *av1Ctx);
	int intra_block_mode_info(SymbolContext *sbCtx, bitSt *bs,
								 BlockData *b_data, AV1DecodeContext *av1Ctx);
	int read_interintra_mode(int isCompound,SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);

	int read_motion_mode(int isCompound,SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);					
	int read_compound_type(int isCompound,SymbolContext *sbCtx,bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int palette_tokens(SymbolContext *sbCtx, bitSt *bs,
						 BlockData *b_data, AV1DecodeContext *av1Ctx);
	int get_palette_color_context(uint8_t **colorMap,int r,int c,int n,BlockData *b_data);
	int read_block_tx_size(SymbolContext *sbCtx, bitSt *bs,
								 BlockData *b_data, AV1DecodeContext *av1Ctx);
	int read_var_tx_size(int row,int col,int txSz,int depth,SymbolContext *sbCtx, bitSt *bs, 
								 BlockData *b_data, AV1DecodeContext *av1Ctx);
	int read_tx_size(int allowSelect, SymbolContext *sbCtx, bitSt *bs,BlockData *b_data,AV1DecodeContext *av1Ctx);
	int compute_prediction(SymbolContext *sbCtx, bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int reset_block_context(int bw4, int bh4,SymbolContext *sbCtx, bitSt *bs,
							BlockData *b_data,AV1DecodeContext *av1Ctx);
	int needs_interp_filter(BlockData *b_data,AV1DecodeContext *av1Ctx);

	int clear_cdef(int r, int c,AV1DecodeContext *av1Ctx);
	int read_lr(SymbolContext *sbCtx, bitSt *bs,int r,int c, int bSize,
				 AV1DecodeContext *av1Ctx);
	int read_lr_unit(SymbolContext *sbCtx, bitSt *bs,int plane,int unitRow,int unitCol,
						AV1DecodeContext  *av1Ctx);
	int clear_block_decoded_flags(int r, int c, int sbSize4, AV1DecodeContext *av1Ctx);
	int clear_above_context(AV1DecodeContext  *av1Ctx);
	int clear_left_context(AV1DecodeContext  *av1Ctx);
	static frame& Instance() {
		static frame m_pInstance;
		return m_pInstance;
	}
private:
	Symbol *sb;
	segmentation *seg_instance;
	decode *decode_instance;
	int scount;

};
#endif
