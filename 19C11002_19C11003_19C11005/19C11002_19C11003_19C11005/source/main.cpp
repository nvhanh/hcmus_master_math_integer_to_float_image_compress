// 19C11002_19C11003_19C11005.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ImgEncDec.h"

USG_NSP_APP();
using namespace std;

int main()
{
	RawImg rawImg("imgs/img_01.jpg");
	int res = rawImg.show();
	if (res != ErrCode::kSuccess) {
		cout << "Error: " << getErrStr(res) << endl;
		return 0;
	}

	EncodedImg encodedImg;
	ImgEncDec::encodeImg(rawImg, encodedImg);

	RawImg decodedImg;
	ImgEncDec::decodeImg(encodedImg, decodedImg);

	decodedImg.save("imgs/decoded.jpg");
	decodedImg.show("decoded image");

	return 0;
}
