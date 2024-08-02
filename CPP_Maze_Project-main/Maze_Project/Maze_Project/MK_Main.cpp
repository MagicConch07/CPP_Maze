#include "define.h"
#include "MK_Core.h"
#include "MK_GameLogic.h"
#include "TitleScene.h"

int main() 
{
	if (!GET_SINGLE(MK_Core)->Init())
	{
		cout << "Game Init Error" << endl;
		MK_Core::DestroyInst();
		return 0;
	}

	if (!TitleScene()) {
		return 0;
	}

	GET_SINGLE(MK_Core)->Run();
	return 0;
}