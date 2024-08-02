#pragma once
#include "define.h"
#include "Core.h"

const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 80;

const int SECTION_WIDTH = 21;
const int SECTION_HEIGHT = 40;

enum class OBJ_TYPE
{
	ROAD = '0', WALL, START, COIN, TRAIL = (char)222, TRAIL2
};

class MapManager
{
private:
	MapManager();
	static MapManager* m_pInst;

public:
	static MapManager* GetInst() {
		if (m_pInst == nullptr)
			m_pInst = new MapManager;
		return m_pInst;
	}

public:
	char arrMap[MAP_HEIGHT][MAP_WIDTH] = {};

	int obstacle_pos = 0;
	int obstacle_Wpos = 0;

	void AddSection(const char section[SECTION_HEIGHT][SECTION_WIDTH]);
	void Init(std::string const MAP_FILE);
	void ObstacleRender();
	void GameOverRender();
	void DestoryObstacle(int destory_pos_y);
};

