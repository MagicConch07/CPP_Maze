#pragma once
#include "define.h"

class Camera
{
private:
	int threshold = 1;
	int Lerp(int start, int end, float t);
public:
	void MoveCamera();
	void CameraUpdate();
public:
	Camera()
	{
		topCam = 0;
		bottomCam = 20;
		is_move_cam = false;
	}

	int topCam;
	int bottomCam;
	bool is_move_cam = false;
};