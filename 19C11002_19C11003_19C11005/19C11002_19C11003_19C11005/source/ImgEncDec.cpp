#include "ImgEncDec.h"

USG_NSP_APP();

int32_t ImgEncDec::encodeImg(const RawImg& rawImg, EncodedImg& encodedImg) {
	//cv::Mat rawMat = rawImg.getImg();


	return ErrCode::kFailed;
}


int32_t ImgEncDec::decodeImg(const EncodedImg& encodedImg, RawImg& decodedImg) {
	return ErrCode::kFailed;
}
