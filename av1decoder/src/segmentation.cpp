#include "segmentation.h"

int segmentation::get_qindex(int ignoreDeltaQ, int segmentId,frameHeader *frameHdr){
	if(seg_feature_active_idx( segmentId, SEG_LVL_ALT_Q,frameHdr ) == 1){
		int data = frameHdr->segmentation_params.FeatureData[ segmentId ][ SEG_LVL_ALT_Q ];
		int qindex = frameHdr->quantization_params.base_q_idx + data;

		//dav1d 和 libaom 都忽略了这个条件
		//if(ignoreDeltaQ == 0 && delta_q_present == 1)
	    //	qindex = CurrentQIndex + data;

		return Clip3( 0, 255, qindex );
	//}else if (ignoreDeltaQ == 0 && delta_q_present == 1){ 
	//	 return CurrentQIndex;

	}else{
		return frameHdr->quantization_params.base_q_idx;
	}

}
//int segmentation::seg_feature_active(int feature)){
//	return seg_feature_active_idx( segment_id, feature );
//}
int segmentation::seg_feature_active_idx(int idx, int feature,frameHeader *frameHdr){
	return frameHdr->segmentation_params.segmentation_enabled && frameHdr->segmentation_params.FeatureEnabled[ idx ][ feature ];
}

int segmentation::seg_feature_active(int segment_id,int feature,frameHeader *frameHdr){
	return seg_feature_active_idx( segment_id, feature,frameHdr);

}