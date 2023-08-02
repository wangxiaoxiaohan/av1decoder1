#include "stdio.h"
#include "stdlib.h"
#include "av1decoder.h"
void initContext(AV1DecodeContext **ctx){
	AV1DecodeContext *c = (AV1DecodeContext *)malloc(sizeof(AV1DecodeContext));
	memset(c, 0, sizeof(AV1DecodeContext));
	for(int i = 0 ; i < NUM_REF_FRAMES ; i++){
		AV1Frame *f = (AV1Frame *)malloc(sizeof(AV1Frame));
		c->ref_frames[i] = f;
	}

	frameHeader *fh = (frameHeader *)malloc(sizeof(frameHeader));
	sequenceHeader *sh = (sequenceHeader *)malloc(sizeof(sequenceHeader));

	c->frameHdr =  fh;
	c->seqHdr = sh;
	c->SeenFrameHeader = 0;
	*ctx = c;
	
}
int main(int argc ,char **argv){
    FILE *fp = fopen("./out6.obu","r");
    uint8_t *buffer = (uint8_t *)malloc(OBU_BUF_SIZE);
    int offset = 0 ;

	AV1DecodeContext *ctx;
	initContext(&ctx);
    while(1){
        int size = obu::Instance().parseObuInfo(fp,offset,buffer,0,ctx);
        offset += size;
    }

	fclose(fp);

}