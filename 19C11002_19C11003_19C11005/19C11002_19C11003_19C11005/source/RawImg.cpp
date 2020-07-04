#include "RawImg.h"

USG_NSP_APP();
using namespace cv;
using namespace std;


RawImg::RawImg() {
}

RawImg::RawImg(const std::string& fileName) {
	_img = imread(fileName, IMREAD_COLOR);
}

RawImg::~RawImg() {

}

int32_t RawImg::show(const std::string& windowsName, cv::Size maxSize) {
	if (!isValidImg()) {
		return ErrCode::kInvalidImg;
	}

	if (_img.rows <= maxSize.height && _img.cols <= maxSize.width)
		imshow(windowsName, _img);
	else {
		cv::Mat tmp = _img.clone();
		cv::Size curSize = tmp.size();
		cv::Size newSize = curSize.width / (float)maxSize.width > curSize.height / (float)maxSize.height
			? cv::Size(maxSize.width, curSize.height * maxSize.width / curSize.width)
			: cv::Size(curSize.width * maxSize.height / curSize.height, maxSize.height);

		cv::resize(_img, tmp, newSize);
		imshow(windowsName, tmp);
	}

	waitKey(0);

	return ErrCode::kSuccess;
}

bool RawImg::isValidImg() {
	return _img.cols > 0 && _img.rows > 0;
}