#pragma once
#define GET_SINGLE(c) c::GetInst()
#define DESTROYER(p) if (p != nullptr) {delete p;p = nullptr;}
#include<iostream>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#include"Player.h"
#include"mci.h"
#include"console.h"
#include"GameTimer.h"
#include "Camera.h"
#include"MapManager.h"
using std::cout;
using std::wcout;
using std::endl;
