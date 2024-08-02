#include<Windows.h>
#include "console.h"

void FullScreen()
{
	//SetConsoleDisplayMode
	//(GetStdHandle(STD_OUTPUT_HANDLE),
	//	CONSOLE_FULLSCREEN_MODE, NULL);
	ShowWindow(GetConsoleWindow(),
		SW_MAXIMIZE);
	//::SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN,
	//	VK_RETURN, 0x20000000);
}

void Gotoxy(int _x, int _y)
{
	// 콘솔창 핸들
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 커서 관련 구조체.
	COORD Cur = { _x, _y }; // *2가 자연스러울수도있음.
	// 콘솔 커서의 위치를 강제 이동시키는 함수.
	SetConsoleCursorPosition(hOut, Cur);
}

BOOL GotoPos(int _x, int _y)
{
	// 콘솔창 핸들
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 커서 관련 구조체.
	COORD Cur = { _x, _y }; // *2가 자연스러울수도있음.
	// 콘솔 커서의 위치를 강제 이동시키는 함수.
	return SetConsoleCursorPosition(hOut, Cur);
}

COORD CursorPos()
{
	CONSOLE_SCREEN_BUFFER_INFO Buf;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		, &Buf);
	return Buf.dwCursorPosition;
}

void SetCursorVis(bool _vis, DWORD _size)
{
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.bVisible = _vis; // on, off
	curinfo.dwSize = _size; // 1~100
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		, &curinfo);
}

void SetColor(int _textcolor, int _bgcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
		, (_bgcolor << 4) | _textcolor);
}

int GetColor()
{
	CONSOLE_SCREEN_BUFFER_INFO Buf;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		, &Buf);
	int color = Buf.wAttributes & 0xf;
	return color;
}

void LockResize()
{
	HWND console = GetConsoleWindow();
	if (nullptr != console)
	{
		LONG style = GetWindowLong(console, GWL_STYLE);
		style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;// &~WS_CAPTION;
		SetWindowLong(console, GWL_STYLE, style);
	}
}
COORD GetConsoleResolution()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		, &info);
	short width = info.srWindow.Right - info.srWindow.Left + 1;
	short height = info.srWindow.Bottom - info.srWindow.Top + 1;
	return COORD{ width, height };
}

void SetFontSize(UINT _weight, UINT _sizex, UINT _sizey)
{
	// 굵게. 사이즈의 크기는 못키우나요?
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetCurrentConsoleFontEx(hOut, false, &font);
	font.FontWeight = _weight;
	font.dwFontSize.X = _sizex;
	font.dwFontSize.Y = _sizey;
	SetCurrentConsoleFontEx(hOut, false, &font);

}

bool IsWindows10OrGreater()
{
	OSVERSIONINFOEXW osInfo = { 0 };
	osInfo.dwOSVersionInfoSize = sizeof(osInfo);
	osInfo.dwMajorVersion = 10;
	DWORDLONG conditionMask = 0;
	VER_SET_CONDITION(conditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);

	return VerifyVersionInfoW(&osInfo, VER_MAJORVERSION, conditionMask);
}
