#pragma once
#include<fcntl.h>
#include<corecrt_io.h>
#include"define.h"

void TitleRender();
bool TitleScene();
void InfoRender();
enum class MENU {
	START, INFO, QUIT, GOTO_TITLE
};
MENU MenuRender();
enum class KEY {
	_, UP, DOWN, SPACE
};

KEY KeyController();;
void EnterAnimation();