#include "Common.h"

using namespace std;

std::string& getErrStr(int32_t errCode) {
	string errStr = "unknown";

	switch (errCode) {
	case ErrCode::kSuccess:
		errStr = string("success");
		break;
	case ErrCode::kFailed:
		errStr = string("general fail");
		break;
	case ErrCode::kInvalidImg:
		errStr = string("invalid image");
		break;
	case ErrCode::kSaveFileFailed:
		errStr = string("save file faile");
		break;
	case ErrCode::kFileNotFound:
		errStr = string("file not found");
		break;
	default:
		break;
	}

	return errStr;
}