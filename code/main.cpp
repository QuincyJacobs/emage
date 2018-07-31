#include <Windows.h>
#include <stdio.h>
#include <stdint.h>

#include "pixel.h"
#include "file.h"

#define internal static;
#define global_variable static

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

struct win32_offscreen_buffer
{
	// NOTE: Pixels are always 32-bits wide, Memory order BB GG RR XX
	BITMAPINFO Info;
	void *Memory;
	int Width;
	int Height;
	int Pitch;
};

struct win32_window_dimension
{
	int Width;
	int Height;
};

global_variable bool Running;
global_variable win32_offscreen_buffer GlobalBackBuffer;

internal win32_window_dimension Win32GetWindowDimension(HWND Window)
{
	win32_window_dimension Result;

	RECT ClientRect;
	GetClientRect(Window, &ClientRect);
	Result.Width = ClientRect.right - ClientRect.left;
	Result.Height = ClientRect.bottom - ClientRect.top;

	return Result;
}

internal void Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
{
	// TODO: Don't free memory first, free after. Only free first if that fails...

	if (Buffer->Memory)
	{
		VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
	}

	Buffer->Width = Width;
	Buffer->Height = Height;
	int BytesPerPixel = 4;

	Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
	Buffer->Info.bmiHeader.biWidth = Buffer->Width;
	Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
	Buffer->Info.bmiHeader.biPlanes = 1;
	Buffer->Info.bmiHeader.biBitCount = 32;
	Buffer->Info.bmiHeader.biCompression = BI_RGB;

	int BitmapMemorySize = (Buffer->Width * Buffer->Height) * BytesPerPixel;
	Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	Buffer->Pitch = Width*BytesPerPixel;

	// TODO: Probably clear screen to black
}

internal void RenderEmg(win32_offscreen_buffer *Buffer, Pixel **pixelArray)
{
	uint8 *Row = (uint8 *)Buffer->Memory;

	for (int Y = 0; Y < Buffer->Height; ++Y)
	{
		uint32 *Pix = (uint32 *)Row;

		for (int X = 0; X < Buffer->Width; ++X)
		{
			Pixel curPixel = pixelArray[Y][X];
			uint8 Blue = curPixel.blue;
			uint8 Green = curPixel.green;
			uint8 Red = curPixel.red;

			*Pix++ = ((Red << 16) | (Green << 8) | Blue);
		}
		Row += Buffer->Pitch;
	}
}

internal void Win32DisplayBufferInWindow(win32_offscreen_buffer *Buffer, HDC DeviceContext,
	int WindowWidth, int WindowHeight)
{
	// TODO: Aspect ratio correction
	StretchDIBits(DeviceContext,
		0, 0, WindowWidth, WindowHeight,
		0, 0, Buffer->Width, Buffer->Height,
		Buffer->Memory,
		&Buffer->Info,
		DIB_RGB_COLORS, SRCCOPY);
}

internal LRESULT CALLBACK Win32MainWindowCallback(HWND Window,
	UINT Message,
	WPARAM WParam,
	LPARAM LParam)
{
	LRESULT Result = 0;

	switch (Message)
	{
	case WM_SIZE:
	{

	} break;

	case WM_DESTROY:
	{
		// TODO: Handle with message to user
		Running = false;
	} break;

	case WM_CLOSE:
	{
		Running = false;
	} break;

	case WM_ACTIVATEAPP:
	{
		OutputDebugStringA("WM_ACTIVATEAPP\n");
	} break;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:
	case WM_KEYDOWN:
	{
		uint32 VKCode = WParam;
		bool WasDown = ((LParam & (1 << 30)) != 0);
		bool IsDown = ((LParam & (1 << 31)) == 0);

		if (WasDown != IsDown)
		{
			if (VKCode == 'W')
			{
			}
			else if (VKCode == 'A')
			{
			}
			else if (VKCode == 'S')
			{
			}
			else if (VKCode == 'D')
			{
			}
			else if (VKCode == 'Q')
			{
			}
			else if (VKCode == 'E')
			{
			}
			else if (VKCode == VK_UP)
			{
			}
			else if (VKCode == VK_LEFT)
			{
			}
			else if (VKCode == VK_DOWN)
			{
			}
			else if (VKCode == VK_RIGHT)
			{
			}
			else if (VKCode == VK_ESCAPE)
			{
				OutputDebugStringA("ESCAPE: ");
				if (IsDown)
				{
					OutputDebugStringA("IsDown ");
				}
				if (WasDown)
				{
					OutputDebugStringA("WasDown");
				}
				OutputDebugStringA("\n");
			}
			else if (VKCode == VK_SPACE)
			{
			}
		}

		bool AltKeyWasDown = ((LParam & (1 << 29)) != 0);
		if ((VKCode == VK_F4) && AltKeyWasDown)
		{
			Running = false;
		}
	}break;


	case WM_PAINT:
	{
		PAINTSTRUCT Paint;
		HDC DeviceContext = BeginPaint(Window, &Paint);

		win32_window_dimension Dimension = Win32GetWindowDimension(Window);
		Win32DisplayBufferInWindow(&GlobalBackBuffer, DeviceContext,
			Dimension.Width, Dimension.Height);

		EndPaint(Window, &Paint);
	} break;

	default:
	{
		Result = DefWindowProc(Window, Message, WParam, LParam);
		break;
	}
	}
	return(Result);
}


int CALLBACK WinMain(
	HINSTANCE Instance,
	HINSTANCE PreviousInstance,
	LPSTR     CommandLine,
	int       ShowCode
)
{
	WNDCLASS WindowClass = {};

	char *readTestFileName = (char *)"test.emg";
	char *writeTestFileName = (char *)"writeTest.emg";
	char *fileTestString = (char *)"0000000000000005ff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffffff0000ff00ff00ff0000ffffffffffffffffffff";
	printFile(readTestFileName, fileTestString);
	//printFile(readTestFileName, "0000000000000005ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

	long stride = 0;
	long rows = 0;

	Pixel** pixelArray = getPixelArrayFromFile(readTestFileName, &stride, &rows);
	writePixelsToFile(writeTestFileName, pixelArray, &stride, &rows);
	printEmgFileStatistics(writeTestFileName);

	Win32ResizeDIBSection(&GlobalBackBuffer, stride, rows);

	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = Win32MainWindowCallback;
	WindowClass.hInstance = Instance;
	//  WindowClass.hIcon = 0;
	WindowClass.lpszClassName = "Emage_Window_Class";

	if (RegisterClass(&WindowClass))
	{
		HWND Window =
			CreateWindowExA(
				0,
				WindowClass.lpszClassName,
				"Renderer",
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				400,
				200,
				0,
				0,
				Instance,
				0);

		if (Window)
		{
			HDC DeviceContext = GetDC(Window);

			Running = true;
			while (Running)
			{

				MSG Message;
				while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{
					if (Message.message == WM_QUIT)
					{
						Running = false;
					}

					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}

				RenderEmg(&GlobalBackBuffer, pixelArray);

				win32_window_dimension Dimension = Win32GetWindowDimension(Window);
				Win32DisplayBufferInWindow(&GlobalBackBuffer, DeviceContext,
					Dimension.Width, Dimension.Height);

				ReleaseDC(Window, DeviceContext);
			}
		}
		else
		{
			// TODO: Error handling
		}
	}
	else
	{
		// TODO: Error handling
	}

	// stop program from exiting
	getchar();

	return (0);
}

