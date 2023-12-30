#include "stdio.h"
#include "stdlib.h"
#include "av1decoder.h"
#include "frame.h"

int main(int argc ,char **argv){
    FILE *fp = fopen("./out9.obu","r");
    uint8_t *buffer = (uint8_t *)malloc(OBU_BUF_SIZE);
    int offset = 0 ;

	AV1DecodeContext *ctx = (AV1DecodeContext *)malloc(sizeof(AV1DecodeContext));
	memset(ctx, 0, sizeof(AV1DecodeContext));
	ctx->SeenFrameHeader = 0;

	frame* f =  &frame::Instance();
	
	//f->allocDecodeContext(ctx);
    while(1){
        int size = obu::Instance().parseObuInfo(fp,offset,buffer,0,ctx);
        offset += size;
    }

	fclose(fp);

}