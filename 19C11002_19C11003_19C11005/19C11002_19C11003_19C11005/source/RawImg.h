#pragma once

#include "Common.h"

BEG_NSP_APP();


class RawImg {
public:
	RawImg();
	RawImg(const RawImg& otherImg);
	RawImg(const std::string& fileName);
	~RawImg();

	void reset();
	bool isValidImg();
	int32_t show(const std::string& windowsName = "image", int32_t maxWidth = 1280, int32_t maxHeigth = 720);
	int32_t save(const std::string& fileName);

public:
	uint8_t* buffer;
	int32_t bufferLength;
	int32_t width;
	int32_t heigth;
};


END_NSP_APP();
