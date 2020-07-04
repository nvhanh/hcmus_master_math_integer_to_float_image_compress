#pragma once

#include "Common.h"
#include "opencv2/opencv.hpp"

BEG_NSP_APP();


class RawImg {
public:
	RawImg();
	RawImg(const std::string& fileName);
	~RawImg();

	int32_t show(const std::string& windowsName = "image", cv::Size maxSize = cv::Size(1280, 720));
	bool isValidImg();

protected:
	cv::Mat _img;
};


END_NSP_APP();
