#pragma once
#include <Windows.h>

#include "Core.h"
#include "mci.h"
#include "console.h"
#include "define.h"
#include "MapManager.h"
#include "MK_Core.h"

class MK_GameLogic
{
private:
	MK_GameLogic();
	static MK_GameLogic* m_pInst;
public:
	static MK_GameLogic* GetInst()
	{
		if (m_pInst == nullptr)
			m_pInst = new MK_GameLogic;
		return m_pInst;
	}
public:
	void Init();
};

