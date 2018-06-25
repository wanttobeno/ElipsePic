#pragma once

#include <Windows.h>
#include <GdiPlus.h>

enum IMAGE_TYPE
{
	IMAGE_BMP,
	IMAGE_PNG,
	IMGAE_JPG,
	IMAGE_GIF,
	IMAGE_TIFF,
};

bool GetImageCoder(CLSID &encodeerClsid,IMAGE_TYPE type);

bool ElipsePic(wchar_t* pPicPath,wchar_t* pSavePath);