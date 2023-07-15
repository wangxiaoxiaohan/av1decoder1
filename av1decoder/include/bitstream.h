#ifndef _BIT_STREAM_
#define _BIT_STREAM_
#include "stdint.h"
#include "common.h"
typedef struct bitSt{
    int offset;
    uint8_t offsetInByte;
    uint8_t *dataPtr;
}bitSt;

void inline initBitStream(bitSt *bs, uint8_t *data)
{
    bs->offsetInByte = 0;
    bs->offset = 0;
    bs->dataPtr = data;

}
void  inline updateOffset(bitSt *bs)
{
    bs->offsetInByte += 1;
    bs->offset +=  bs->offsetInByte / 8;
    bs->offsetInByte %= 8;
}
uint8_t inline readOneBit(bitSt *bs)
{
    uint8_t ret = bs->dataPtr[bs->offset] << bs->offsetInByte;
    ret = ret >> 7;
    updateOffset(bs);
	//printf("readOneBit %d\n",ret);
    return ret;

}
uint32_t inline readBits(bitSt *bs,int len)
{
    uint32_t  ret = 0;	
    for(int i =  0; i < len ;i ++){
        ret =  (ret << 1) | readOneBit(bs); 
    }
    return ret;
	
}
/*
uint64_t readleb128(bitSt *bs)
{
    uint64_t ret = 0;
	int pos = 0,end;
	do{
		int tmp = readBits(bs,8);
		printf(" %d\n",tmp);
		end = ! (0x80 & tmp); //最高位标记是否还有数据
		ret |= (uint64_t)(tmp & 0x7f) << pos;
		pos += 7;

	}while(!end && (pos + 8) < 64);
		
    return ret;
}
*/
//这些读算法都是完全按照spec来写的
uint64_t inline readleb128(bitSt *bs,uint8_t* Leb128Bytes)
{ 
	uint64_t value = 0;
	*Leb128Bytes = 0;
	for (int i = 0; i < 8; i++ ) {
		int leb128_byte = readBits(bs,8);
		value |= ( (leb128_byte & 0x7f) << (i*7) );
		*Leb128Bytes += 1;
		if ( !(leb128_byte & 0x80) ) {
			break;
		}
	}
	return value;
}
uint64_t inline readUlvc(bitSt *bs)
{
	int leadingZeros = 0;
	while ( 1 ) {
		int done = readOneBit(bs); 
		if ( done )
			break;
		leadingZeros++;
	}
	if ( leadingZeros >= 32 ) {
		return ( 1 << 32 ) - 1;
	}
	return readBits(bs,leadingZeros) + ( 1 << leadingZeros ) - 1;
}
uint64_t inline readns(bitSt *bs,int n){
	int w = FloorLog2(n) + 1;
	int m = (1 << w) - n;
	int v =  readBits(bs,w-1);
	if ( v < m )
		return v;
	int extra_bit = readOneBit(bs);
	return (v << 1) - m + extra_bit;
}
uint64_t inline readsu(bitSt *bs,int n) { 
	uint64_t value = readBits(bs,n);
	int signMask = 1 << (n - 1);
	if ( value & signMask )
		value = value - 2 * signMask;
	return value;
}
int inline decode_subexp(bitSt * bs,int numSyms ) { 
	int i = 0;
	int mk = 0;
	int k = 3;
	while ( 1 ) {
		int b2 = i ? k + i - 1 : k;
		int a = 1 << b2;
		if ( numSyms <= mk + 3 * a ) {
			//subexp_final_bits ns(numSyms - mk);
			return readns(bs,numSyms - mk) + mk;
		} else {
			if ( readOneBit(bs) ) {
				i++;
				mk += a;
			} else {
				return readBits(bs, 2) + mk;
			}
		}
	}
}
int inline inverse_recenter(int r,int v) { 
	if ( v > 2 * r )
		return v;
	else if ( v & 1 )
		return r - ((v + 1) >> 1);
	else
		return r + (v >> 1);
}


int inline decode_unsigned_subexp_with_ref(bitSt * bs,int  mx,int r ) {
	int v = decode_subexp( bs,mx );
	if ( (r << 1) <= mx ) {
		return inverse_recenter(r, v);
	} else {
		return mx - 1 - inverse_recenter(mx - 1 - r, v);
	}
}

int inline decode_signed_subexp_with_ref(bitSt * bs,int low, int high, int r ) { 
	int x = decode_unsigned_subexp_with_ref(bs,high - low, r - low);
	return x + low;
}

#endif
