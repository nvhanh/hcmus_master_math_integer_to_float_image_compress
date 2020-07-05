#pragma once

#include "Common.h"
#include "opencv2/opencv.hpp"

BEG_NSP_APP();

class EncodedImg {
public:
	EncodedImg();
	EncodedImg(const EncodedImg& otherImg);
	EncodedImg(const std::string& encodedFile);
	~EncodedImg();

	void reset();
	int32_t fromEncodedFile(const std::string& encodedFile);

public:
	double* buffer;
	int32_t bufferLength;
	int32_t width;
	int32_t heigth;

	std::vector<std::vector<uint16_t> > rawIntVal;
};

END_NSP_APP();
