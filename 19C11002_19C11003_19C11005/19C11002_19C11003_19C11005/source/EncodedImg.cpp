#include "EncodedImg.h"

USG_NSP_APP();

EncodedImg::EncodedImg() :
buffer(nullptr),
bufferLength(0), 
width(0), 
heigth(0) {

}

EncodedImg::EncodedImg(const EncodedImg& otherImg) {
	if (this == &otherImg)
		return;

	reset();

	bufferLength = otherImg.bufferLength;
	width = otherImg.width;
	heigth = otherImg.heigth;
	buffer = new float[bufferLength];

	if (bufferLength > 0)
		memcpy(buffer, otherImg.buffer, bufferLength);
}

EncodedImg::EncodedImg(const std::string& encodedFile) :
EncodedImg() {

}

EncodedImg::~EncodedImg() {
	reset();
}

void EncodedImg::reset() {
	if (!buffer)
		delete[] buffer;

	buffer = nullptr;
	bufferLength = 0;
	width = 0;
	heigth = 0;
}

int32_t EncodedImg::fromEncodedFile(const std::string& encodedFile) {
	return ErrCode::kFailed;
}