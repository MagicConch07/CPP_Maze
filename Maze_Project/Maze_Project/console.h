#pragma once
#include<Windows.h>
#include<iostream>

void FullScreen();
void Gotoxy(int _x, int _y);
BOOL GotoPos(int _x, int _y);
COORD CursorPos();
void SetCursorVis(bool _vis, DWORD _size);
void SetColor(int _textcolor = 15, int _bgcolor = 0);
int GetColor();
void LockResize();
COORD GetConsoleResolution();
void SetFontSize(UINT _weight, UINT _sizex, UINT _sizey);
enum class COLOR
{
	BLACK, BLUE, GREEN, SKYBLUE, RED,
	VOILET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
	LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
	LIGHT_YELLOW, WHITE, END
};
bool IsWindows10OrGreater();
bool IsWindows11OrGreater();