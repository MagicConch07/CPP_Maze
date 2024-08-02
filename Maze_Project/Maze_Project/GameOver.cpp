#include "GameOver.h"

void GameOverRender() {
	system("mode con cols=100 lines=40");

	int beforemode = _setmode(_fileno(stdout), _O_U16TEXT);

	wcout << "\n\n\n\n\n\n\n\n\n";
	wcout << L"\t         ██████╗  █████╗ ███╗   ███╗███████╗ ██████╗ ██╗   ██╗███████╗██████╗  " << endl;
	wcout << L"\t	██╔════╝ ██╔══██╗████╗ ████║██╔════╝██╔═══██╗██║   ██║██╔════╝██╔══██╗ " << endl;
	wcout << L"\t	██║  ███╗███████║██╔████╔██║█████╗  ██║   ██║██║   ██║█████╗  ██████╔╝ " << endl;
	wcout << L"\t	██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗ " << endl;
	wcout << L"\t	╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗╚██████╔╝ ╚████╔╝ ███████╗██║  ██║ " << endl;
	wcout << L"\t	 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝ ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝  " << endl;



	int curMode = _setmode(_fileno(stdout), beforemode);

}


bool GameOverScene()
{
	while (true)
	{
		system("cls");
		GameOverRender();
		MENU goMenu = GOMenuRender();
		system("cls");
		switch (goMenu)
		{
		case MENU::GOTO_TITLE:
			GET_SINGLE(Core)->DestroyInst();
			return true;
		case MENU::QUIT:
			return false;
		}
	}
	return true;
}

MENU GOMenuRender() {
	char halka[4] = { '|', '/', '-', '\\' };
	int loop;

	double deltaTime, oldTime = clock();
	loop = 0;

	COORD Resolution = GetConsoleResolution();
	int x = Resolution.X / 2.4;
	int y = Resolution.Y / 1.7;

	Gotoxy(x + 3, Resolution.Y / 2.3);
	cout << "Score : " << GET_SINGLE(Core)->score;

	int top = y;
	int bottom = y + 2;
	Gotoxy(x, y);
	cout << "다시하기";
	Gotoxy(x, y + 2);
	cout << "오늘은 여기까지";

	Gotoxy(x - 2, y);
	cout << halka[loop];
	Sleep(100);
	while (true) {
		if (100 < clock() - oldTime) {
			oldTime = clock();
			++loop;
			if (loop > 3)
				loop = 0;
		}
		Gotoxy(x - 2, y);
		cout << halka[loop];
		KEY eKey = KeyController();
		switch (eKey)
		{
		case KEY::UP:
			if (!(y - 1 < top)) {
				Gotoxy(x - 2, y);
				cout << " ";
				y -= 2;
				Gotoxy(x - 2, y);
				cout << halka[loop];
				Sleep(100);
			}
			break;
		case KEY::DOWN:
			if (!(y + 1 > bottom)) {
				Gotoxy(x - 2, y);
				cout << " ";
				y += 2;
				Gotoxy(x - 2, y);
				cout << halka[loop];
				Sleep(100);
			}
			break;
		case KEY::SPACE:
			if (y == top) {
				return MENU::GOTO_TITLE;
			}
			if (y == top + 2) {
				return MENU::QUIT;
			}
			break;
		}
	}
	return MENU::QUIT;
}