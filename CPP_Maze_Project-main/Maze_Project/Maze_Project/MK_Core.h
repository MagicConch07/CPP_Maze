#pragma once
#include "define.h"
#include "Camera.h"
#include "MK_GameLogic.h"
class Player;
class Camera;
class GameTimer;

class MK_Core
{
private:
    MK_Core();
    static MK_Core* m_pInst;

private:
    bool gameOver = false;
    double lastTime = speed;

public:
    static MK_Core* GetInst() {
        if (m_pInst == nullptr)
            m_pInst = new MK_Core;
        return m_pInst;
    }
    static void DestroyInst() {
        DESTROYER(m_pInst);
    }

public:
    Player* player;
    Camera* camera;
    GameTimer* gameTime;

    int score = 0;
    double speed = 1;

    bool Init();
    void Run();
    void Update();
    void Render();
    void GameStart();
    void GameOver();
};

