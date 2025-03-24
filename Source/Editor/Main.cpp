#include "../Utils/CoreMinimal.h"
#include "Windows/Window.h"
#include "../Actors/Actor.h"	
#include "World.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"
#include "../UI/UIManager.h"
#include "../UI/FontManager.h"
#include "../UI/Canvas.h"
#include "../UI/UIImage.h"
#include "../UI/UIManager.h"
#include "..\UI\Widget.h"
#include "..\UI\ConsoleWidget.h"

void Shutdown(GLFWwindow* _window);

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    World* _world = new World();
    Window _window = Window(800, 600, "Oui oui");
    _world->SetWindow(&_window);

    Actor* _actor = _world->SpawnActor();
    _actor->LoadModel("D:/Github/ComUnity/Content/Survival_Backpack/Meshes/Survival_BackPack.fbx");
    _actor->BeginPlay();
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
    _uiManager.Init(_window.GetWindow());

    // oui
    FontManager::GetInstance().LoadFont("D:/Github/ComUnity/Content/Fonts/RubikGlitch-Regular.ttf", 24.0f);

    float f = 0.0f;
    string buf = "oui";
    bool _oui = true;

    while (!glfwWindowShouldClose(_window.GetWindow()))
    {
        _uiManager.StartLoop();

        glfwPollEvents();

        ImGui::Begin("My First Tool", &_oui, ImGuiWindowFlags_MenuBar);

        Text("Hello, world %d", 123);
        if (ImGui::Button("Save"))
            cout << "pd" << endl;

        ImGui::InputText("string", buf.data(), 20);
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

        ImGui::End();

        _deltatime = glfwGetTime() - _time;
        _time = glfwGetTime();

        glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _window.GetController()->PollEvents();

        _uiManager.EndLoop();
        glfwSwapBuffers(_window.GetWindow());
    }

    Shutdown(_window.GetWindow());
    _actor->BeginDestroy();
    delete _world;

    return EXIT_SUCCESS;
	int _width, _height;
	double _time = glfwGetTime();
	double _deltatime = 0.0;
	glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
	vec3 _targetPos = vec3(0.0f);

	UIManager& _uiManager = UIManager::GetInstance();
	_uiManager.Init(_window.GetWindow());

	while (!glfwWindowShouldClose(_window.GetWindow()))
	{
		glfwPollEvents();
		_uiManager.StartLoop();
		_deltatime = glfwGetTime() - _time;
		_time = glfwGetTime();
		glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_window.GetController()->PollEvents();

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


void RotateSinCamera(bool _positive)
{
	mat4 _view = mat4(1.0f);
	const float _radius = -7.5f;
	float _viewZ = (sinf(10.0f) * _radius) * _positive ? 1.0f : -1.0f;
	_view = lookAt(vec3(0.0f, 0.0f, _viewZ), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
}

void RotateCosCamera(bool _positive)
{
	mat4 _view = mat4(1.0f);
	const float _radius = -7.5f;
	float _viewX = (cosf(10.0f) * _radius) * _positive ? 1.0f : -1.0f;
	_view = lookAt(vec3(_viewX, 0.0f, 0.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
}