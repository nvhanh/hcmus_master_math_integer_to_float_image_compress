#pragma once

#include "Common.h"
#include "opencv2/opencv.hpp"

BEG_NSP_APP();

class EncodedImg {
public:
	EncodedImg();
	EncodedImg(const std::string& encodedFile);

	int32_t fromEncodedFile(const std::string& encodedFile);

protected:
	int32_t _width;
	int32_t _height;
};

END_NSP_APP();
