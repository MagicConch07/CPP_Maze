#include "MapManager.h"

MapManager* MapManager::m_pInst = nullptr;

MapManager::MapManager()
{
}

void MapManager::Init(std::string const MAP_FILE)
{
	std::ios_base::sync_with_stdio(false);
	cout.tie();

	// Loading Map
	std::fstream readMap(MAP_FILE);
	if (readMap.is_open())
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			readMap.getline(arrMap[i], MAP_WIDTH);
			if (readMap.fail())
				std::cout << "File Error";
		}
	}
	// RAII
	readMap.close();
}

void MapManager::AddSection(const char section[SECTION_HEIGHT][SECTION_WIDTH])
{
	for (int i = MAP_HEIGHT - 1; i >= SECTION_HEIGHT; --i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			arrMap[i][j] = arrMap[i - SECTION_HEIGHT][j];
		}
		//arrMap[i][MAP_WIDTH] = '\0';  // Null-terminate each row
	}

	// 새로운 섹션을 맨 위에 추가
	for (int i = 0; i < SECTION_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			arrMap[i][j] = section[i][j];
		}
		//arrMap[i][MAP_WIDTH] = '\0';  // Null-terminate each row
	}
}


void MapManager::ObstacleRender()
{
	Gotoxy(0, obstacle_pos);
	for (int i = 0; i < 2; ++i)
	{
		for (int _ = 0; _ < (GetConsoleResolution().X) / 2 - MAP_WIDTH; ++_)
		{
			std::cout << " ";
		}
		for (int j = 0; j < MAP_WIDTH - 1; ++j)
		{
			SetColor((int)COLOR::RED);
			cout << "▲";
		}
		cout << "\n";
	}
	SetColor((int)COLOR::WHITE);
}

void MapManager::GameOverRender()
{
	cout << "Game Over";
}

void MapManager::DestoryObstacle(int destory_pos_y)
{
	Gotoxy(0, destory_pos_y + 2);
	for (int _ = 0; _ < (GetConsoleResolution().X) / 2 - MAP_WIDTH; ++_)
	{
		std::cout << " ";
	}
	for (int i = 0; i < MAP_WIDTH - 1; ++i)
	{
		cout << "  ";
	}
}
