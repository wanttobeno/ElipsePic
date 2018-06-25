/*
	
	http://blog.sina.com.cn/s/blog_9fc7e85f0102y7a5.html
*/
#include "ElipsePic.h"

using namespace Gdiplus;

bool GetImageCoder(CLSID &encodeerClsid,IMAGE_TYPE type)
{
	bool bRet = false;
	// 获取编码器的CLSID[class id]
	UINT num = 0;	// 图像编码器的数量
	UINT size = 0;	// 图像编码数组的字节数
	ImageCodecInfo* pICI = NULL;

	GetImageEncodersSize(&num,&size); // 获取系统编码器的数量和大小
	if (size == 0)
		return false;
	wchar_t * pBmp = L"image/bmp";
	wchar_t * pPng = L"image/png";
	wchar_t * pJpg = L"image/jpeg";
	wchar_t * pGif = L"image/gif";
	wchar_t * pTiff = L"image/tiff";
	wchar_t * pDest;
	switch(type)
	{
	case IMAGE_BMP:
		pDest = pBmp;
		break;
	case IMAGE_PNG:
		pDest = pPng;
		break;
	case IMGAE_JPG:
		pDest = pJpg;
		break;
	case IMAGE_GIF:
		pDest = pGif;
		break;
	case IMAGE_TIFF:
		pDest = pTiff;
		break;
	}

	pICI = (ImageCodecInfo*)(malloc(size));
	if (pICI == NULL)
		return false;
	GetImageEncoders(num,size,pICI);
	for (UINT j=0;j<num;j++)
	{
		if (_wcsicmp(pICI[j].MimeType,pDest)==0) // //jpeg bmp gif tiff png 
		{
			encodeerClsid = pICI[j].Clsid;
			bRet = true;
			break;
		}
	}
	free(pICI);
	return bRet;
}


bool ElipsePic(wchar_t* pPicPath,wchar_t* pSavePath)
{
	Image image(pPicPath);
	Bitmap b(image.GetWidth(),image.GetHeight());
	Graphics g(&b);
	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	GraphicsPath p(FillModeAlternate);
	p.AddEllipse(0,0,image.GetWidth(),image.GetHeight());
	g.FillPath(&TextureBrush(&image),&p);

	CLSID encodeerClsid;
	IMAGE_TYPE type = IMAGE_PNG;
	GetImageCoder(encodeerClsid ,type);
	
	Status status = b.Save(pSavePath,&encodeerClsid);
	if (status == Status::Ok)
		return true;
	return false;
}