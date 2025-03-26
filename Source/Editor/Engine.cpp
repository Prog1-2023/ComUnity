#include "Engine.h"

Engine::Engine()
{
}

void Engine::Start()
{
	Update();
	Stop();
}

void Engine::Update()
{
    /*while (Level* _currentLevel = LevelManager::GetInstance().GetCurrentLevel())
    {
        TM_Seconds& _timer = M_TIMER;
        const float _deltaTime = _timer.Update();
        _currentLevel->Update(_deltaTime);
    }*/
}

void Engine::Stop()
{
    // destroy level
}