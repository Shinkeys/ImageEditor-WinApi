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
	HWND hWnd; // to remove static when would have multiple windows

private:
	void CaptureImage(HWND hWnd);


public:
	static const inline HINSTANCE& getInstance() { return hInstance; }

public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();
	bool ProcessMessages();
	// 

};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
