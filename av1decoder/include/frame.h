#ifndef _FRAME_
#define _FRAME_
#include "header_common.h"
#include "av1decoder.h"
#include "obu.h"
#include "cdf.h"

class frame{
public:
    frame(){};
	~frame(){}
	int readTileInfo(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr);
	int readQuantizationParams(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr);
	int read_interpolation_filter(bitSt *bs,frameHeader *frameHdr);
	int readSuperresParams(bitSt *bs,sequenceHeader *seqHdr,sizeInfo *si);
	int readSegmentationParams(bitSt *bs, sequenceHeader *seqHdr, frameHeader *frameHdr);
	int readLoopFilterParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader);
	int readCdefParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader);
	int readLrParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHeader);
	int readSkipModeParams(bitSt *bs, frameHeader *frameHdr,AV1DecodeContext *av1ctx,sequenceHeader *seqHeader);
	int readGlobalMotionParams(bitSt *bs, frameHeader *frameHdr);
	int readFilmGrainParams(bitSt *bs, frameHeader *frameHdr,sequenceHeader *seqHdr);
	int readDeltaQuantizerParams(bitSt *bs, frameHeader *frameHdr);
	int readDeltaLoopfilterParams(bitSt *bs, frameHeader *frameHdr);
	int readRenderSize(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr,sizeInfo *out);
	int readFrameSize(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr,sizeInfo *out);
	int parseFrameHeader(int sz,bitSt *bs,AV1DecodeContext * av1ctx,sequenceHeader *seqHdr,obuHeader *obuheader, frameHeader *out);
	int get_relative_dist(sequenceHeader *seqHdr,int a,int b);
	int read_delta_q(bitSt *bs);
	int read_global_param(frameHeader *frameHdr,bitSt *bs, int type,int ref,int idx );

	int decode_tile(SymbolContext *sbCtx, bitSt *bs,TileData *t_data,AV1DecodeContext *av1ctx);
	int decode_partition(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,PartitionData *p_data,int r,int c,int sbSize, AV1DecodeContext *av1ctx);
	int decodeFrame(int sz, bitSt *bs, AV1DecodeContext *av1ctx);
	int decode_block(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,int r,int c,int subSize, AV1DecodeContext *av1ctx);

	int mode_info(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int intra_frame_mode_info(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx );
	int inter_frame_mode_info(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int read_segment_id(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int read_cdef(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int read_delta_qindex(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int read_delta_lf(SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int assign_mv(int isCompound,SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int read_mv_component(int MvCtx,int comp,SymbolContext *sbCtx,bitSt *bs,TileData *t_data,
							PartitionData *p_data,BlockData *b_data,AV1DecodeContext *av1ctx);
	int intra_angle_info_y(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1ctx);
	int intra_angle_info_uv(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1ctx);
	int read_cfl_alphas(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1ctx);

	int palette_mode_info(SymbolContext *sbCtx,bitSt *bs,PartitionData *p_data,
							BlockData *b_data,AV1DecodeContext *av1ctx);
	int filter_intra_mode_info(SymbolContext *sbCtx,bitSt *bs,BlockData *b_data,AV1DecodeContext *av1ctx);
	int get_palette_cache(int plane,PartitionData *p_data,BlockData *b_data);





	
	static frame& Instance() {
		static frame m_pInstance;
		return m_pInstance;
 
	}


private:

};
#endif
