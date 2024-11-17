#pragma once


#include <iostream>
#include <windows.h>
#include <tchar.h>

#include "../headers/bmpLoader.h"


namespace usefulObjects
{
}

class Window
{
private:
	static inline BMPImg bmpLoader;
	static inline HINSTANCE hInstance = (GetModuleHandle(nullptr));
	HWND hWnd;
public:
	static const inline HINSTANCE& getInstance() { return hInstance; }
	static inline BMPImg& getBmpLoader() { return bmpLoader; }

public:
	// win api
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();
	bool ProcessMessages();

};
// win api methods
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// own methods
void fillImageData(HWND hWnd);
