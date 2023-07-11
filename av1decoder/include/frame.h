#ifndef _FRAME_
#define _FRAME_
#include "stdio.h"
#include "stdint.h"
#include "header_common.h"
#include "av1decoder.h"
#include "obu.h"


class frame{
public:
    frame(){};
	~frame(){}
	int readTileInfo(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr);
	int readQuantizationParams(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr);
	int read_interpolation_filter(bitSt *bs,frameHeader *frameHdr);
	int readSuperresParams(bitSt *bs,sequenceHeader *seqHdr,sizeInfo *si);
	int readRenderSize(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr,sizeInfo *out);
	int readFrameSize(bitSt *bs,sequenceHeader *seqHdr,frameHeader *frameHdr,sizeInfo *out);
	int parseFrameHeader(int sz,bitSt *bs,AV1DecodeContext * av1ctx,sequenceHeader *seqHdr,obuHeader *obuheader, frameHeader *out);
	int get_relative_dist(sequenceHeader *seqHdr,int a,int b);
	int read_delta_q(bitSt *bs);

private:

};
#endif
