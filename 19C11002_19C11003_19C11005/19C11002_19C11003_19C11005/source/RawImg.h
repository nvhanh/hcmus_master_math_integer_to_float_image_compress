#pragma once

#include "Common.h"

BEG_NSP_APP();

#define MAX_SHOW_WIDTH 1280
#define MAX_SHOW_HEIGHT 720
#define DEFAULT_WINDOWS_NAME "image"


class RawImg {
public:
	RawImg();
	RawImg(const RawImg& otherImg);
	RawImg(const std::string& fileName);
	~RawImg();

	void reset();
	bool isValidImg();
	int32_t show(const std::string& windowsName = DEFAULT_WINDOWS_NAME, int32_t maxWidth = MAX_SHOW_WIDTH, int32_t maxHeigth = MAX_SHOW_HEIGHT);
	int32_t save(const std::string& fileName);

public:
	uint8_t* buffer;
	int32_t bufferLength;
	int32_t width;
	int32_t heigth;
};


END_NSP_APP();
