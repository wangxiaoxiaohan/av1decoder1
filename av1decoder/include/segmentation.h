#ifndef _SEGMENTATION_
#define _SEGMENTATION_
#include "stdio.h"
#include "stdint.h"
#include "header_common.h"

static uint8_t Segmentation_Feature_Bits[ SEG_LVL_MAX ] = { 8, 6, 6, 6, 6, 3, 0, 0 };
static uint8_t Segmentation_Feature_Signed[ SEG_LVL_MAX ] = { 1, 1, 1, 1, 1, 0, 0, 0 };
static uint8_t Segmentation_Feature_Max[ SEG_LVL_MAX ] = {
			255, MAX_LOOP_FILTER, MAX_LOOP_FILTER,
			MAX_LOOP_FILTER, MAX_LOOP_FILTER, 7, 0, 0 };



class segmentation{
public:
    segmentation(){}
	~segmentation(){}

	int get_qindex(int ignoreDeltaQ, int segmentId,frameHeader *frameHdr,int CurrentQIndex);
	int seg_feature_active(int segment_id,int feature,frameHeader *frameHdr);
	int seg_feature_active_idx(int idx, int feature,frameHeader *frameHdr);
	static segmentation& Instance() {
		static segmentation m_pInstance;
		return m_pInstance;
	}
private:

};
#endif




