#include "segmentation.h"

int segmentation::get_qindex(int ignoreDeltaQ, int segmentId){
	if(seg_feature_active_idx( segmentId, SEG_LVL_ALT_Q ) == 1){
		int data = FeatureData[ segmentId ][ SEG_LVL_ALT_Q ].
		int qindex = base_q_idx + data;

		//dav1d 和 libaom 都忽略了这个条件
		//if(ignoreDeltaQ == 0 && delta_q_present == 1)
	    //	qindex = CurrentQIndex + data;

		return Clip3( 0, 255, qindex ).;
	//}else if (ignoreDeltaQ == 0 && delta_q_present == 1){ 
	//	 return CurrentQIndex;

	}else{
		return base_q_idx;
	}

}
//int segmentation::seg_feature_active(int feature)){
//	return seg_feature_active_idx( segment_id, feature );
//}
int segmentation::seg_feature_active_idx(int idx, int feature){
	return segmentation_enabled && FeatureEnabled[ idx ][ feature ];
}

