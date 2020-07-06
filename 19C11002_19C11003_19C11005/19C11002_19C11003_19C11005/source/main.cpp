// 19C11002_19C11003_19C11005.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ImgEncDec.h"

USG_NSP_APP();
using namespace std;

int main()
{
	/// TODO (hanhnv)
	// cài đặt các command để tiện gọi, không cần sửa code khi đổi input/output

	/// --------- Load ảnh cần nén ---------------
	RawImg rawImg("imgs/img_01.jpg");
	// Lưu ảnh dưới định dạng raw (Bitmap) để tiện so sánh
	rawImg.save("imgs/raw.bmp");
	// Hiển thị ảnh vừa đọc được
	int res = rawImg.show();
	if (res != ErrCode::kSuccess) {
		cout << "Error: " << getErrStr(res) << endl;
		return 0;
	}

	/// --------- Nén ảnh load được ---------------
	EncodedImg encodedImg;
	ImgEncDec::encodeImg(rawImg, encodedImg);
	encodedImg.saveFile("imgs/encoded_double.ssd");

	/// --------- Load ảnh đã được nén ---------------
	EncodedImg encodedImg2;
	encodedImg2.fromFile("imgs/encoded_double.ssd");

	/// --------- Giải nén ảnh đã load ---------------
	RawImg decodedImg;
	ImgEncDec::decodeImg(encodedImg2, decodedImg);

	decodedImg.save("imgs/decoded_double.jpg");
	decodedImg.show("decoded image");

	return 0;
}
