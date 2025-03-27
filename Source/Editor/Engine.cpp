#include "Engine.h"

Engine::Engine()
{
    window = new Window("Engine Render Window", 800, 800);
    //world = nullptr;
    levelManager = LevelManager::GetInstance();
}

Engine::~Engine()
{
    delete window;
    //delete world;
}

void Engine::Run()
{
    Start();
	Update();
	Stop();
}

void Engine::Start()
{
    //window->Start(); => pas besoin déjà init auto

    /*world = new World(window); // => change to level
    world->Start();*/

    Level* _currentLevel = new Level("DefaultLevel");
    levelManager.SetLevel(_currentLevel);
}

void Engine::Update()
{
    GLFWwindow* _mainWindow = window->GetWindow();
    int _width, _height;

    float _time = 0.0f; 
    float _deltaTime = 0.0f;

    while (!glfwWindowShouldClose(_mainWindow)) // PROBABLY REMOVE ESCAPE
    {
        _deltaTime = glfwGetTime() - _time;
        _time = glfwGetTime();

        glfwGetFramebufferSize(_mainWindow, &_width, &_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //world->Update();
        levelManager.UpdateCurrentLevel(_deltaTime);

        window->Update(); // ProcessInputs 

        glfwSwapBuffers(_mainWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(_mainWindow);
    glfwTerminate();

    /*while (Level* _currentLevel = LevelManager::GetInstance().GetCurrentLevel())
    {
        TM_Seconds& _timer = M_TIMER;
        const float _deltaTime = _timer.Update();
        _currentLevel->Update(_deltaTime);
    }*/
}

void Engine::Stop()
{

    levelManager.Destroy();
    //world->Stop();
    // destroy level
}