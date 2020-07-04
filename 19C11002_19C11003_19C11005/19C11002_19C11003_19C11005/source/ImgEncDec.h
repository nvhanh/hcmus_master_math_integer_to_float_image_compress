#pragma once

#include "source/RawImg.h"
#include "source/EncodedImg.h"

BEG_NSP_APP();

class ImgEncDec {
public:
	static int32_t encodeImg(const RawImg& rawImg, EncodedImg& encodedImg);
	static int32_t decodeImg(const EncodedImg& encodedImg, RawImg& decodedImg);
};

END_NSP_APP();