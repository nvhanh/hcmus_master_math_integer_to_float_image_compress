#include "EncodedImg.h"
#include <fstream>

#define SEGMENT_SIZE 32768

USG_NSP_APP();
using namespace std;

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
	buffer = new double[bufferLength];

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

bool EncodedImg::isValidImg() {
	return width > 0 && heigth > 0
		&& bufferLength > 0
		&& buffer != nullptr;
}

int32_t EncodedImg::fromFile(const std::string& encodedFile) {
	reset();

	std::ifstream encFile(encodedFile, ios::in | ios::binary);
	if (!encFile.is_open())
		return ErrCode::kFileNotFound;

	encFile.read((char*)&width, sizeof(width));
	encFile.read((char*)&heigth, sizeof(heigth));
	encFile.read((char*)&bufferLength, sizeof(bufferLength));
	buffer = new double[bufferLength];

	// Đọc file theo từng đoạn để tăng tốc độ
	int32_t remainSize = bufferLength;
	while (remainSize > SEGMENT_SIZE) {
		encFile.read((char*)&buffer[bufferLength - remainSize], SEGMENT_SIZE * sizeof(buffer[0]));
		remainSize -= SEGMENT_SIZE;
	}

	if (remainSize > 0) {
		encFile.read((char*)&buffer[bufferLength - remainSize], remainSize * sizeof(buffer[0]));
	}

	encFile.close();

	return ErrCode::kFailed;
}

int32_t EncodedImg::saveFile(const std::string& encodedFile) {
	if (!isValidImg())
		return ErrCode::kInvalidImg;

	std::ofstream encFile(encodedFile, ios::out | ios::binary);
	if (!encFile.is_open())
		return ErrCode::kSaveFileFailed;

	encFile.clear();

	encFile.write((const char*)&width, sizeof(width));
	encFile.write((const char*)&heigth, sizeof(heigth));
	encFile.write((const char*)&bufferLength, sizeof(bufferLength));

	// Ghi file theo từng đoạn để tăng tốc độ
	int32_t remainSize = bufferLength;
	while (remainSize > SEGMENT_SIZE) {
		encFile.write((const char*)&buffer[bufferLength - remainSize], SEGMENT_SIZE * sizeof(buffer[0]));
		remainSize -= SEGMENT_SIZE;
	}

	if (remainSize > 0) {
		encFile.write((const char*)&buffer[bufferLength - remainSize], remainSize * sizeof(buffer[0]));
	}

	encFile.close();
	return ErrCode::kSuccess;
}