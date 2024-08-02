#include "MK_Core.h"
MK_Core* MK_Core::m_pInst = nullptr;

MK_Core::MK_Core()
{
	player = new Player();
	camera = new Camera();
	camera->bottomCam = MAP_HEIGHT / 2;
	score = 0;
}

bool MK_Core::Init()
{
	if (player == nullptr) player = new Player();
	if (camera == nullptr) camera = new Camera();

	GET_SINGLE(MK_GameLogic)->Init();

	return true;
}

void MK_Core::Run()
{
	gameTime = new GameTimer();
	PlayBgm(TEXT("gamebgm.mp3"), 100);

	while (true)
	{
		Update();
		Gotoxy(0, 0);
		if (gameOver == false)
		{
			Render();
		}
	}
}

void MK_Core::Update()
{
	this->player->Move();
	this->gameTime->Update();
	this->camera->CameraUpdate();
	score += gameTime->GetDeltaTime();
}	

void MK_Core::Render()
{
	for (int i = std::clamp(camera->topCam - 2, 0, 60); i < std::clamp(camera->bottomCam, -100, 80); ++i)
	{
		for (int _ = 0; _ < (GetConsoleResolution().X) / 2 - MAP_WIDTH; ++_) {
			cout << " ";
		}

		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (player->tPos.x == j && player->tPos.y == i)
			{
				SetColor((int)COLOR::LIGHT_YELLOW);
				cout << "¢Â";
			}
			else if (arrMap[i][j] == (char)OBJ_TYPE::WALL)
			{
				SetColor((int)COLOR::LIGHT_YELLOW, (int)COLOR::YELLOW);
				cout << "  ";
			}
			else if (arrMap[i][j] == (char)OBJ_TYPE::ROAD)
				cout << "  ";
			else if (arrMap[i][j] == (char)OBJ_TYPE::START)
				cout << "¡Ú";
			else if (arrMap[i][j] == (char)OBJ_TYPE::TRAIL) {
				SetColor((int)COLOR::LIGHT_YELLOW, (int)COLOR::LIGHT_YELLOW);
				cout << "  ";
			}
			else if (arrMap[i][j] == (char)OBJ_TYPE::TRAIL2) {
				SetColor((int)COLOR::MINT, (int)COLOR::MINT);
				cout << "  ";
			}
			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
		}
		cout << "\n";
	}

	Gotoxy(MAP_WIDTH / 1.5, 21);
	//cout << "topCam: " << std::clamp(camera->topCam - 2, 0, 100) << " " << "bottomCam: " << std::clamp(camera->bottomCam, 0, 40);
	/*Gotoxy(MAP_WIDTH / 1.5, 21);
	cout << "PlayerPos: " << player->tPos.x << ", " << player->tPos.y << "\t\t";
	Gotoxy(MAP_WIDTH / 1.5, 20);
	cout << "Score: " << gameTime->GetGameTime();*/

	/*Gotoxy(GetConsoleResolution().X / 2 - MAP_WIDTH, 21);
	cout << "PlayerPos: " << player->tPos.x << ", " << player->tPos.y << "\t\t";
	Gotoxy(GetConsoleResolution().X / 2 - MAP_WIDTH, 20);
	cout << "Score: " << gameTime->GetGameTime();*/

	/*Gotoxy(GetConsoleResolution().X / 2 - MAP_WIDTH, 21);
	GET_SINGLE(MapManager)->ObstacleRender();*/

	// Clean Up ObstacleRender
	// DestoryObstacle();

	// GameOver
	//if (player->tPos.y >= camera->bottomCam) GameOver();
}

void MK_Core::GameStart()
{
	gameOver = false;
}

void MK_Core::GameOver()
{
	GET_SINGLE(MapManager)->GameOverRender();
	gameOver = true;
}