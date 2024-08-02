#include "Player.h"

Player::Player()
{
	tPos = { 0,0 };
	tNewPos = tPos;
	lastMoveTime = 0;
	p_obstacle_pos = 17;
	isDead = false;
}

void restoreTile(MapManager* mapManager, int x, int y, char originalType, int delayMilliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
	mapManager->arrMap[y][x] = (char)OBJ_TYPE::TRAIL2;
	std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
	mapManager->arrMap[y][x] = originalType;
}

void Player::Move()
{
	//this->tNewPos = this->tNewPos + Dirif ()
	if ((clock() - lastMoveTime) < .1f) return;

	lastMoveTime = clock();

	//isDead = true;

	tNewPos = tPos;
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		tNewPos = Raycast(tPos, {0, -1});
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		tNewPos = Raycast(tPos, {0, 1});
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		tNewPos = Raycast(tPos, {-1, 0});
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		tNewPos = Raycast(tPos, {1, 0});
	}

	tNewPos.x = std::clamp(tNewPos.x, 0, MAP_WIDTH - 2);
	tNewPos.y = max(tNewPos.y, 0);

	/*tPos =tNewPos;
	cout << tPos.x << "\n";
	cout << tPos.y;*/

	if (tPos == tNewPos) return;

	std::vector<FLOAT2> pathTiles = getLinePoints(tPos, tNewPos);
	for (const auto& index : pathTiles) {
		char* tile = &MapManager::GetInst()->arrMap[index.y][index.x];
		if (*tile != (char)OBJ_TYPE::TRAIL && *tile != (char)OBJ_TYPE::TRAIL2 && *tile != (char)OBJ_TYPE::ROAD) continue;
		*tile = (char)OBJ_TYPE::TRAIL;

		std::thread restoreThread(restoreTile, MapManager::GetInst(), index.x, index.y, (char)OBJ_TYPE::ROAD, 100);
		restoreThread.detach(); // 메인 스레드와 독립적으로 실행
	}

	tPos = tNewPos;

	if (tPos.y < 11) {  // 맵의 상단에 가까워지면
		static const char SECTION[SECTION_HEIGHT][SECTION_WIDTH] = {
			"11011111111111111111",
			"10000000000111111111",
			"10000000000000000001",
			"10011111110000001101",
			"11110000000001110001",
			"10000001110000011111",
			"10000000000000000001",
			"10011000000000000001",
			"10011000000111111001",
			"10011000000000000001",
			"11111000000000000001",
			"10011111111000000001",
			"10011000000000000001",
			"10011000000000000001",
			"10011000000000000001",
			"10000000000000000001",
			"10000000000000011111",
			"10000000000000000001",
			"10001111111111100001",
			"11111111100000001111",
			"10000000000010000001",
			"10111111111111111111",
			"10000000000000000001",
			"11111111111111111101",
			"10000000000000000001",
			"10000011111100000001",
			"10000000000000000001",
			"10000000000011111111",
			"11111111111000000001",
			"10000100001000000001",
			"10000100001000000001",
			"10000100001111000001",
			"10000100000001000001",
			"10000111100000000001",
			"11110000000111111111",
			"10000000100001000001",
			"10001111111111000001",
			"10000000000000000001",
			"10000000000000000001",
		};
		MapManager::GetInst()->AddSection(SECTION);
		tPos.y += SECTION_HEIGHT;  // 플레이어를 섹션 아래로 이동, 첫 줄 제거했기 때문에 -2
		GET_SINGLE(Core)->camera->MoveCamera();
	}
}

FLOAT2 Player::Raycast(FLOAT2 origin, FLOAT2 dir)
{
	FLOAT2 newPos = origin;
	int maxTries = 100;
	int tries = 0;
	while (tries < maxTries) {
		newPos = { newPos.x + dir.x , newPos.y + dir.y };
		if (MapManager::GetInst()->arrMap[newPos.y][newPos.x] == (char)OBJ_TYPE::WALL) {
			newPos = { newPos.x - dir.x, newPos.y - dir.y };
			return newPos;
		}
		/*else if (MapManager::GetInst()->arrMap[newPos.y][newPos.x] == (char)OBJ_TYPE::DANGER) {
			newPos = { newPos.x - dir.x, newPos.y - dir.y };
			return newPos;
		}*/
		if (newPos.x == MAP_WIDTH || newPos.y == MAP_HEIGHT 
			|| newPos.x == -1
			|| newPos.y == -1) {
			//newPos = { std::clamp(newPos.x,0,MAP_WIDTH), std::clamp(newPos.y,0,MAP_HEIGHT) };
			return newPos;
		}
		++tries;
	}
	return origin;
}


//너무 에바 쎄바 약간 쌀밥먹으려고 초밥집 가서 회만 다 때버리는 급에 과도한 알고리즘이라 폐기
//std::vector<FLOAT2> Player::getLinePoints(FLOAT2 start, FLOAT2 end) {
//	std::vector<FLOAT2> points;
//	int dx = std::abs(end.x - start.x);
//	int sx = start.x < end.x ? 1 : -1;
//	int dy = -std::abs(end.y - start.y);
//	int sy = start.y < end.y ? 1 : -1;
//	int err = dx + dy;
//
//	while (true) {
//		points.push_back(start);
//		if (start.x == end.x && start.y == end.y) break;
//		int e2 = 2 * err;
//		if (e2 >= dy) {
//			err += dy;
//			start.x += sx;
//		}
//		if (e2 <= dx) {
//			err += dx;
//			start.y += sy;
//		}
//	}
//
//	return points;
//}

std::vector<FLOAT2> Player::getLinePoints(FLOAT2 start, FLOAT2 end) {
	std::vector<FLOAT2> points;

	// 수평 이동
	if (start.y == end.y) {
		int xStart = min(start.x, end.x);
		int xEnd = max(start.x, end.x);
		for (int x = xStart; x <= xEnd; ++x) {
			points.push_back({ x, start.y });
		}
	}
	// 수직 이동
	else if (start.x == end.x) {
		int yStart = min(start.y, end.y);
		int yEnd = max(start.y, end.y);
		for (int y = yStart; y <= yEnd; ++y) {
			points.push_back({ start.x, y });
		}
	}

	return points;
}
