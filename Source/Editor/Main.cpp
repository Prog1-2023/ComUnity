#include "../Utils/CoreMinimal.h"
#include "Windows/Window.h"
#include "../Actors/Actor.h"    
#include "World.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"
#include "../UI/Canvas.h"
#include "../UI/UIImage.h"
#include "../UI/UIManager.h"
#include "..\UI\Widget.h"
#include "..\UI\ConsoleWidget.h"
#include "../UI/UIText.h"

void Shutdown(GLFWwindow* _window);

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    World* _world = new World();
    Window _window = Window(800, 600, "Engine");
    _world->SetWindow(&_window);

    Actor* _actor = _world->SpawnActor();
    _actor->BeginPlay();

    StaticMeshComponent* _mesh = _actor->GetComponent<StaticMeshComponent>();
    CameraActor* _camera = _world->SpawnActor<CameraActor>();
    _world->SetCurrentCamera(_camera);
    _world->Initialize();

    int _width, _height;
    double _time = glfwGetTime();
    double _deltatime = 0.0;
    glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
    vec3 _targetPos = vec3(0.0f);

    UIManager& _uiManager = UIManager::GetInstance();
    _uiManager.Init(_window.GetWindow(), _world);

    //Test text
    FontManager* fontManager = new FontManager();
    fontManager->LoadFont(GetAbsolutePath() + "/Content/Fonts/RubikGlitch-Regular.ttf", 24.0f);

    UIText uiText(fontManager, _world,"Hello World");



    while (!glfwWindowShouldClose(_window.GetWindow()))
    {
        glfwPollEvents();
        _uiManager.StartLoop();
        _deltatime = glfwGetTime() - _time;
        _time = glfwGetTime();
        glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _window.GetController()->PollEvents();

        //Test text
        uiText.Draw();

        _uiManager.DrawAll();

        _uiManager.EndLoop();
        glfwSwapBuffers(_window.GetWindow());
    }

    Shutdown(_window.GetWindow());
    _actor->BeginDestroy();
    delete _world;

    return EXIT_SUCCESS;
}

void Shutdown(GLFWwindow* _window)
{
    UIManager::GetInstance().Destroy();
    glfwDestroyWindow(_window);
    glfwTerminate();
}