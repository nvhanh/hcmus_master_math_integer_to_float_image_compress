#include "ImgEncDec.h"
#include <math.h>
#include <stdint.h>

USG_NSP_APP();

inline uint8_t getBit(const uint8_t& val, const uint8_t& pos) {
	return ((val & (1 << pos)) >> pos);
}

inline uint8_t getBit(const uint16_t& val, const uint8_t& pos) {
	return ((val & (1 << pos)) >> pos);
}

inline void modifyBit(uint8_t& val, size_t pos, uint8_t bitVal) {
	uint8_t mask = 1 << pos;
	val = (val & ~mask) | ((bitVal << pos) & mask);
}

inline void modifyBit(uint16_t& val, size_t pos, uint8_t bitVal) {
	uint16_t mask = 1 << pos;
	val = (val & ~mask) | ((bitVal << pos) & mask);
}

int32_t ImgEncDec::encodeImg(const RawImg& rawImg, EncodedImg& encodedImg) {
	encodedImg.reset();
	encodedImg.rawIntVal.clear();

	int32_t numFloatVal = (rawImg.bufferLength + 15) / 16;
	encodedImg.width = rawImg.width;
	encodedImg.heigth = rawImg.heigth;
	encodedImg.bufferLength = numFloatVal;
	encodedImg.buffer = new double[numFloatVal];
	memset(encodedImg.buffer, 0, numFloatVal);

	encodedImg.rawIntVal.resize(numFloatVal);

	float powArr[8];
	powArr[0] = pow(2, 128 - (0 + 1) * 16);
	powArr[1] = pow(2, 128 - (1 + 1) * 16);
	powArr[2] = pow(2, 128 - (2 + 1) * 16);
	powArr[3] = pow(2, 128 - (3 + 1) * 16);
	powArr[4] = pow(2, 128 - (4 + 1) * 16);
	powArr[5] = pow(2, 128 - (5 + 1) * 16);
	powArr[6] = pow(2, 128 - (6 + 1) * 16);
	powArr[7] = pow(2, 128 - (7 + 1) * 16);

	for (size_t chunk = 0; chunk < numFloatVal - 1; chunk++) {
		encodedImg.buffer[chunk] = 0;
		encodedImg.rawIntVal[chunk].resize(8);

		size_t rawBufferIdx = chunk * 16;
		for (uint8_t bitPos = 0; bitPos < 8; bitPos++) {
			uint16_t intVal = 0;

			modifyBit(intVal, 0, getBit(rawImg.buffer[rawBufferIdx], 8 - bitPos));
			modifyBit(intVal, 1, getBit(rawImg.buffer[rawBufferIdx + 1], 8 - bitPos));
			modifyBit(intVal, 2, getBit(rawImg.buffer[rawBufferIdx + 2], 8 - bitPos));
			modifyBit(intVal, 3, getBit(rawImg.buffer[rawBufferIdx + 3], 8 - bitPos));
			modifyBit(intVal, 4, getBit(rawImg.buffer[rawBufferIdx + 4], 8 - bitPos));
			modifyBit(intVal, 5, getBit(rawImg.buffer[rawBufferIdx + 5], 8 - bitPos));
			modifyBit(intVal, 6, getBit(rawImg.buffer[rawBufferIdx + 6], 8 - bitPos));
			modifyBit(intVal, 7, getBit(rawImg.buffer[rawBufferIdx + 7], 8 - bitPos));
			modifyBit(intVal, 8, getBit(rawImg.buffer[rawBufferIdx + 8], 8 - bitPos));
			modifyBit(intVal, 9, getBit(rawImg.buffer[rawBufferIdx + 9], 8 - bitPos));
			modifyBit(intVal, 10, getBit(rawImg.buffer[rawBufferIdx + 10], 8 - bitPos));
			modifyBit(intVal, 11, getBit(rawImg.buffer[rawBufferIdx + 11], 8 - bitPos));
			modifyBit(intVal, 12, getBit(rawImg.buffer[rawBufferIdx + 12], 8 - bitPos));
			modifyBit(intVal, 13, getBit(rawImg.buffer[rawBufferIdx + 13], 8 - bitPos));
			modifyBit(intVal, 14, getBit(rawImg.buffer[rawBufferIdx + 14], 8 - bitPos));
			modifyBit(intVal, 15, getBit(rawImg.buffer[rawBufferIdx + 15], 8 - bitPos));

			encodedImg.buffer[chunk] += intVal * powArr[bitPos];
			encodedImg.rawIntVal[chunk][bitPos] = intVal;
		}
	}

	/// pading
	encodedImg.rawIntVal[numFloatVal - 1].resize(8);

	return ErrCode::kFailed;
}


int32_t ImgEncDec::decodeImg(const EncodedImg& encodedImg, RawImg& decodedImg) {
	decodedImg.reset();

	decodedImg.width = encodedImg.width;
	decodedImg.heigth = encodedImg.heigth;
	decodedImg.bufferLength = encodedImg.bufferLength * 16;
	decodedImg.buffer = new uint8_t[decodedImg.bufferLength];
	memset(decodedImg.buffer, 0, decodedImg.bufferLength);

	float powArr[8];
	powArr[0] = pow(2, 128 - (0 + 1) * 16);
	powArr[1] = pow(2, 128 - (1 + 1) * 16);
	powArr[2] = pow(2, 128 - (2 + 1) * 16);
	powArr[3] = pow(2, 128 - (3 + 1) * 16);
	powArr[4] = pow(2, 128 - (4 + 1) * 16);
	powArr[5] = pow(2, 128 - (5 + 1) * 16);
	powArr[6] = pow(2, 128 - (6 + 1) * 16);
	powArr[7] = pow(2, 128 - (7 + 1) * 16);

	for (size_t chunk = 0; chunk < encodedImg.bufferLength; chunk++) {
		double chunkVal = encodedImg.buffer[chunk];

		size_t rawBufferIdx = chunk * 16;

		//std::cout << chunkVal << "|";
		for (uint8_t bitPos = 0; bitPos < 8; bitPos++) {
			uint16_t intVal = chunkVal / powArr[bitPos];
			chunkVal -= powArr[bitPos];

			//intVal = encodedImg.rawIntVal[chunk][bitPos];
			//std::cout << intVal << " ";

			modifyBit(decodedImg.buffer[rawBufferIdx], 8 - bitPos, getBit(intVal, 0));
			modifyBit(decodedImg.buffer[rawBufferIdx + 1], 8 - bitPos, getBit(intVal, 1));
			modifyBit(decodedImg.buffer[rawBufferIdx + 2], 8 - bitPos, getBit(intVal, 2));
			modifyBit(decodedImg.buffer[rawBufferIdx + 3], 8 - bitPos, getBit(intVal, 3));
			modifyBit(decodedImg.buffer[rawBufferIdx + 4], 8 - bitPos, getBit(intVal, 4));
			modifyBit(decodedImg.buffer[rawBufferIdx + 5], 8 - bitPos, getBit(intVal, 5));
			modifyBit(decodedImg.buffer[rawBufferIdx + 6], 8 - bitPos, getBit(intVal, 6));
			modifyBit(decodedImg.buffer[rawBufferIdx + 7], 8 - bitPos, getBit(intVal, 7));
			modifyBit(decodedImg.buffer[rawBufferIdx + 8], 8 - bitPos, getBit(intVal, 8));
			modifyBit(decodedImg.buffer[rawBufferIdx + 9], 8 - bitPos, getBit(intVal, 9));
			modifyBit(decodedImg.buffer[rawBufferIdx + 10], 8 - bitPos, getBit(intVal, 10));
			modifyBit(decodedImg.buffer[rawBufferIdx + 11], 8 - bitPos, getBit(intVal, 11));
			modifyBit(decodedImg.buffer[rawBufferIdx + 12], 8 - bitPos, getBit(intVal, 12));
			modifyBit(decodedImg.buffer[rawBufferIdx + 13], 8 - bitPos, getBit(intVal, 13));
			modifyBit(decodedImg.buffer[rawBufferIdx + 14], 8 - bitPos, getBit(intVal, 14));
			modifyBit(decodedImg.buffer[rawBufferIdx + 15], 8 - bitPos, getBit(intVal, 15));
		}

		for (int i = 0; i < 16; i++) {
			//std::cout << (int)decodedImg.buffer[rawBufferIdx + i] << " ";
		}
	}

	return ErrCode::kFailed;
}
