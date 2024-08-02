#pragma once
#include "define.h"
class Player;
class Camera;
class GameTimer;

class Core
{
private:
    Core();
public:
    Player* player;
    Camera* camera;
    GameTimer* timer;
    int score = 0;
    double time = 0;
    int delete_cam_count = 0;
    bool obstacle_render = true;
public:
    bool Init();
    void Run();
    void Update();
    void Render();
    void ObsTime();
    void ResetObsRender();
public:
    static Core* GetInst() {
        if (m_pInst == nullptr)
            m_pInst = new Core;
        return m_pInst;
    }
    static void DestroyInst() {
        DESTROYER(m_pInst);
    }
private:
    static Core* m_pInst;
};
