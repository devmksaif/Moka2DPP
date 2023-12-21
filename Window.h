#pragma once
#include "Windows.h"

class MOKA2DWINDOW
{
public:
	MOKA2DWINDOW(const int width, const int height, const char TITLE[]);
	HWND getHandler();
	~MOKA2DWINDOW();
private:
	HWND handler;
};