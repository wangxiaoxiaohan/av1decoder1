#ifndef _OBU_
#define _OBU_
#include "stdio.h"
#include "stdint.h"
#include "header_common.h"
#include "bitstream.h"
#define OBU_BUF_SIZE 500 * 1024


class obu{
public:
    obu();
	static int parseObuInfo(FILE* fp,int offset,uint8_t *buf,int sz,AV1DecodeContext *ctx);
	//void initSequenceHeader(sequenceHeader *out);
	static int parseSequenceHeader(int sz,bitSt *bs,sequenceHeader *out);
private:


};
#endif
