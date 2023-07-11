#include "stdio.h"
#include "stdlib.h"
#include "av1decoder.h"
int main(int argc ,char **argv){
    FILE *fp = fopen("./out3.obu","r");
    uint8_t *buffer = (uint8_t *)malloc(OBU_BUF_SIZE);
    int offset = 0 ;
    while(1){
        int size = obu::parseObuInfo(fp,offset,buffer,0);
        offset += size;
    }

	fclose(fp);

}