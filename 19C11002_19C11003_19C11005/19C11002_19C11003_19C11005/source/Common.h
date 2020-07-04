#pragma once

#define BEG_NSP_APP() namespace IED {
#define END_NSP_APP() }
#define USG_NSP_APP() using namespace IED

#include <iostream>

struct ErrCode {
	enum type {
		kSuccess = 0,
		kFailed = -1,
		kInvalidImg = -2,
	};
};

std::string& getErrStr(int32_t errCode);
