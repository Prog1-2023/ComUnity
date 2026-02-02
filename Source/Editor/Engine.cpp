#include "Engine.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"
#include "../Actors/Skybox.h"
#include "../Actors/Lights/LightActor.h"
#include "../UI/SceneWidget.h"
#include "../Actors/Grid.h"

Engine::Engine()
{
	window = new Window("Engine Render window", 1920, 1080);
	//world = nullptr;
	levelManager = LevelManager::GetInstance();
	uiManager = &UIManager::GetInstance();
}

Engine::~Engine()
{
	delete window;
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

	uiManager->Init(window->GetWindow(), _currentLevel);

	_currentLevel->GetActorManager().Init();
}

void Engine::Update()
{
#pragma region INITIALIZATION_OF_LIFETIME_TYPES
	// Create the controller
	Controller* _controller = window->GetController();
#pragma endregion

#pragma region LIGHT_DEMO_INITIALISATION

	Actor* _cameraActor = levelManager.GetCurrentLevel()->SpawnActor<CameraActor>();
	Actor* _backpackActor = levelManager.GetCurrentLevel()->SpawnActor<CameraActor>();
	_backpackActor->LoadModel("backpack/Model/backpack.obj");
	_backpackActor->SetDisplayName("BackPack");

	LightActor* _light = levelManager.GetCurrentLevel()->SpawnActor<LightActor>(POINT);
	LightActor* _light2 = levelManager.GetCurrentLevel()->SpawnActor<LightActor>(DIRECTIONAL);

	StaticMeshComponent* _mesh = _backpackActor->GetComponent<StaticMeshComponent>();
	CameraComponent* _camera = _cameraActor->GetComponent<CameraComponent>();


#pragma endregion

	//Begin play on all Actors
	Array<Actor*> _allActor = levelManager.GetCurrentLevel()->GetActorManager().GetAllActors();
	for (Actor* _actor : _allActor)
		_actor->BeginPlay();

	//Init time and size of window variables
	int _width, _height;
	double _deltaTime = 0.0;
	double _time = glfwGetTime();
	vec3 _targetPosition = vec3(0.0f);

	//Set the gl clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//The polygon mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
	//Enable the depth
	glEnable(GL_DEPTH_TEST);



	unsigned int _FBO;
	glGenFramebuffers(1, &_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window->GetWindow())) // PROBABLY REMOVE ESCAPE
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

		uiManager->StartLoop();

#pragma region Computing
		// Compute deltaTime
		_deltaTime = glfwGetTime() - _time;
		_time = glfwGetTime();
		// Processing inputs

		_controller->ProcessInputs();
#pragma endregion

#pragma region Clear
		glfwGetFramebufferSize(window->GetWindow(), &_width, &_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#pragma endregion

#pragma region TICK_ACTORS
		levelManager.UpdateCurrentLevel(_deltaTime);
#pragma endregion


#pragma region COMPUTE_MVP
		mat4 _view = mat4(1.0f);
		mat4 _skyboxView = mat4(1.0f);
		_view = _camera->ComputeView(window);

		const float& _pitch = cos(_controller->phi) * cos(_controller->theta) * _controller->viewRadius;
		const float& _yaw = sin(_controller->phi) * _controller->viewRadius;
		const float& _roll = cos(_controller->phi) * sin(_controller->theta) * _controller->viewRadius;
		const vec3& _cameraPosition = vec3(_pitch, _yaw, _roll) + _targetPosition;

		_mesh->SetCameraLocation(_cameraPosition);

		vec3 _up = normalize(vec3(0.0f, cosf(_controller->phi), 0.0f));
		_view = lookAt(_cameraPosition, _targetPosition, _up);
		_skyboxView = _view;

		//const GLuint& _uniformViewPosition = glGetUniformLocation(_mesh->GetShaderProgram(), "uniformViewPosition");
		//const GLuint& _uniformViewPosition = glGetUniformLocation(_material.GetShader()->GetShaderProgram(), "uniformViewPosition");
		//glUniform3f(_uniformViewPosition, _cameraPosition.x, _cameraPosition.y, _cameraPosition.z);

		mat4 _projection = mat4();
		if (_height != 0.0f)
			_projection = perspective(radians(90.0f), (float)_width / (float)_height, 0.1f, 100.0f);
		mat4 _model = mat4(1.0f);
			
		
		SkyBox* _skybox = levelManager.GetCurrentLevel()->GetSkyBox();
		if (_skybox)
		{
			mat4 _skyboxModel = mat4(1.0f);
			_skyboxModel = translate(_skyboxModel, _cameraPosition);

			_skybox->SetMVP(_skyboxModel, _skyboxView, _projection);
		}

		Grid* _grid = levelManager.GetCurrentLevel()->GetGrid();
		if (_grid)
		{
			mat4 _gridModel = mat4(1.0f);

			_grid->SetMVP(_gridModel, _view, _projection);
		}

		_mesh->SetMVP(_model, _view, _projection);
#pragma endregion	
		//world->Update();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		UIManager::GetInstance().GetWidgetOfType<SceneWidget>()->SetTextureColorBuffer(textureColorbuffer);

		window->Update(); // ProcessInputs 
		uiManager->DrawAll();
		uiManager->EndLoop();

		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}

	glfwDestroyWindow(window->GetWindow());
	glfwTerminate();
	glDeleteFramebuffers(1, &_FBO);
	glDeleteFramebuffers(1, &rbo);
}

void Engine::Stop()
{
	levelManager.Destroy();
	uiManager->Destroy();
	//world->Stop();
	// destroy level
}