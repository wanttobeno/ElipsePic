#ifndef CAUTO_GDIPLUS_H__

#define CAUTO_GDIPLUS_H__ 1


#include <Windows.h>  // must be inluded before gdiplus.h, otherwise compile error   
#include <gdiplus.h>  

#pragma comment(lib, "gdiplus.lib")  

class CAutoGDIPlus
{
	ULONG_PTR m_GdiplusToken;

public:
	CAutoGDIPlus()
	{
		Gdiplus::GdiplusStartupInput StartupInput;
		GdiplusStartup(&m_GdiplusToken, &StartupInput, NULL);
	}

	~CAutoGDIPlus()
	{
		// 注意: 卸载前必须清理所有GDI+的对象 因为卸载后再清理会有异常   
		Gdiplus::GdiplusShutdown(m_GdiplusToken);
	}
}g_GdiplusInstance;


#endif // CAUTO_GDIPLUS_H__
