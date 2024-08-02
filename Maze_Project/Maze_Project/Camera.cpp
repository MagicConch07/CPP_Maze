#include "Camera.h"
#include "define.h"

void Camera::MoveCamera()
{
    Player* player = GET_SINGLE(Core)->player;
    int cameraY = player->tPos.y;

    topCam = max(0, cameraY - 10);
    bottomCam = min(MAP_HEIGHT, cameraY + 10);
}

void Camera::CameraUpdate()
{
    Player* player = GET_SINGLE(Core)->player;
    static int cameraY = (topCam + bottomCam) / 2;

    int diff = player->tPos.y - cameraY;
    const int threshold = 4;

    if (abs(diff) >= threshold) {
        GET_SINGLE(MapManager)->obstacle_Wpos += threshold;
        is_move_cam = true;
        cameraY = player->tPos.y;//Lerp(cameraY, player->tPos.y, 0.1f); // 보간 계수 0.1 사용
    }

    topCam = max(0, cameraY - 10);
    bottomCam = min(MAP_HEIGHT, cameraY + 10); //cameraY + 10;
    /*if (cameraY - 10 < 0) {
        bottomCam = cameraY + 10 - (cameraY - 10);
    }*/
}

int Camera::Lerp(int start, int end, float t) {
	return (int)(start + t * (end - start));
}