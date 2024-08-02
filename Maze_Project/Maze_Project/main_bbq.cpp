//#include "Core.h"
#include "define.h"
#include "GameOver.h"
#include "console.h"
//#include "MK_GameLogic.h"
#include "TitleScene.h"
int main() {                             
	std::ios_base::sync_with_stdio(0);
	std::cout.tie(NULL);

	do {
		if (!Core::GetInst()->Init()) {
			cout << "Game Init Error" << endl;
			Core::DestroyInst();
			return 0;
		}
		if (!TitleScene()) {
			return 0;
		}

		GET_SINGLE(Core)->Run();
	}while (GameOverScene());

	return 0;
}