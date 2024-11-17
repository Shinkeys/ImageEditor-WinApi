#include "../headers/windowManager.h"

BITMAPINFO  bmInfo;
HBITMAP hBitmap = nullptr;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		/*RECT rectangle;
		GetWindowRect(hWnd, &rectangle);
		hBitmap = (HBITMAP)LoadImage(Window::getInstance(), L"data\\second.bmp", IMAGE_BITMAP, 
			rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, LR_LOADFROMFILE);

		if (hBitmap == nullptr)
		{
			std::cout << Window::getInstance();
			std::cout << '\n' << GetLastError();
		}*/
		/*CaptureImage(hWnd);*/
		break;
	case WM_PAINT:
	{
		CaptureImage(hWnd);
		PAINTSTRUCT     ps;
		HDC hdc;
		HDC hdcMem;
		HGDIOBJ oldBitmap;
		void* ppvBits = nullptr;
		void* sourceData = BMPImg::getData();

		hdc = BeginPaint(hWnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);

		
		if (!hdcMem)
		{
			DeleteDC(hdc);
			MessageBox(NULL,
				_T("Create compatible dc method failed!"),
				_T("Win32 image editor"),
				NULL);
			throw std::runtime_error("Closing window!");
		}

		hBitmap = CreateDIBSection(hdc, &bmInfo, DIB_RGB_COLORS, &ppvBits, NULL, 0);
		if (hBitmap == (HBITMAP)nullptr)
		{
			DeleteDC(hdc);
			DeleteDC(hdcMem);
			MessageBox(NULL,
				_T("Create dib section method failed!"),
				_T("Win32 image editor"),
				NULL);
			throw std::runtime_error("Closing window!");
		}
		else
		{
			memcpy(ppvBits, sourceData, bmInfo.bmiHeader.biSizeImage);
		}


		oldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
		if (!oldBitmap)
		{
			MessageBox(NULL,
				_T("Create select object method failed!"),
				_T("Win32 image editor"),
				NULL);
			throw std::runtime_error("Closing window!");
		}


		/*GetObject(hBitmap, sizeof(bmInfo), &bmInfo);*/
		BitBlt(hdc, 0, 0, bmInfo.bmiHeader.biWidth, bmInfo.bmiHeader.biHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);


		EndPaint(hWnd, &ps);


		break;
	} // to do
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		return 0;

		// processing image

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CaptureImage(HWND hWnd)
{
	auto& bmpLoader = Window::getBmpLoader();
	// load image
	bmpLoader.read("data/tree.bmp");
	bmInfo.bmiHeader.biSize = bmpLoader.getInfoHeader().headerSize;
	bmInfo.bmiHeader.biWidth = bmpLoader.getInfoHeader().width;
	bmInfo.bmiHeader.biHeight = bmpLoader.getInfoHeader().height;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biBitCount = bmpLoader.getInfoHeader().bitCount;
	bmInfo.bmiHeader.biCompression = BI_RGB;
	bmInfo.bmiHeader.biSizeImage = 
		((bmInfo.bmiHeader.biWidth * bmInfo.bmiHeader.biBitCount + 31) / 32) * 4 * bmInfo.bmiHeader.biHeight;
	bmInfo.bmiHeader.biXPelsPerMeter = 0;
	bmInfo.bmiHeader.biYPelsPerMeter = 0;
	bmInfo.bmiHeader.biClrUsed = 0;
	bmInfo.bmiHeader.biClrImportant = 0;

	std::cout << "\nInfo in window manager:";
	std::cout << "\nbiSize: " << bmInfo.bmiHeader.biSize;
	std::cout << "\nbiWidth: " << bmInfo.bmiHeader.biWidth;
	std::cout << "\nbiHeight: " << bmInfo.bmiHeader.biHeight;
	std::cout << "\nbiBitCount: " << bmInfo.bmiHeader.biBitCount << '\n';
}






Window::Window()
{
	const wchar_t CLASS_NAME[] = L"Image editor";


	WNDCLASS windowClass = {  }; // registering window class

	windowClass.lpszClassName = CLASS_NAME;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpfnWndProc = WindowProc;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;


	if (!RegisterClass(&windowClass))
	{
		MessageBox(NULL,
			_T("Call to Register Class failed"),
			_T("Win32 guided tour"),
			NULL);

	}

	hWnd = CreateWindowEx(
		0, // styles of window
		CLASS_NAME, // window class
		L"Image editor", // text of window
		WS_OVERLAPPEDWINDOW, // window style

		// size and pos
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL, // parent window
		NULL, // menu
		hInstance, // instance handler
		NULL // additional application data
	);


	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 guided tour"),
			NULL);
		throw std::runtime_error("CLOSING");
	}


	// displaying window if alright
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}





Window::~Window()
{
	const wchar_t CLASS_NAME[] = L"Image editor";


	UnregisterClass(CLASS_NAME, hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}


		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}




