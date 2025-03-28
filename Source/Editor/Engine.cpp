#include "Engine.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"
#include "../Actors/Skybox.h"



Engine::Engine()
{
    window = new Window("Engine Render window", 600, 600);
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
    #pragma region INITIALIZATION_OF_LIFETIME_TYPES
    // Create the controller
    //Controller* _controller = window->GetController();
    #pragma endregion

    #pragma region LIGHT_DEMO_INITIALISATION

    Actor* _cameraActor = levelManager.GetCurrentLevel()->SpawnActor<CameraActor>();
    //Actor* _actor = levelManager.GetCurrentLevel()->SpawnActor<Actor>();
    Actor* _actor = levelManager.GetCurrentLevel()->SpawnBasicShape<Actor>(CUBE,"test");
    //_actor->LoadModel("backpack/Model/backpack.obj");


    LightActor* _light = levelManager.GetCurrentLevel()->SpawnActor<LightActor>(NONE);
    LightActor* _light2 = levelManager.GetCurrentLevel()->SpawnActor<LightActor>(DIRECTIONAL);

    SkyBox* _skybox = levelManager.GetCurrentLevel()->SpawnActor<SkyBox>();

    _skybox->Init({ "cube_right.png", "cube_left.png","cube_up.png",
            "cube_down.png",  "cube_front.png","cube_back.png" }, 1.f);

    //StaticMeshComponent* _mesh = _actor->CreateComponent<StaticMeshComponent>();
    //_mesh->LoadModel("backpack/Model/backpack.obj");
    StaticMeshComponent* _mesh = _actor->GetComponent<StaticMeshComponent>();

    CameraComponent* _camera = _cameraActor->GetComponent<CameraComponent>();
    // Create the controller
   
    InitInput(_camera);
    
    //Sound
    //TODO cline but don't work
    //SoundInfo _soundInfo = SoundInfo(true, Vector3f(0.0f, 0.0f, 5.0f), true, 1.0f, 1.0f, true, false, true);
    //SoundActor* _sound = _currentLevel->SpawnActor<SoundActor>("../Content/Sound/sonic-unleashed-ost.mp3", _soundInfo);
    //SoundActor* _sound = levelManager.GetCurrentLevel()->SpawnActor<SoundActor>("../Content/Sound/sonic-unleashed-ost.mp3", _soundInfo);

    //TODO not cline but work
    //SoundInfo _soundInfo = SoundInfo(true, Vector3f(0.0f, 0.0f, 5.0f), true, 1.0f, 1.0f, true, false, true);
    //SoundActor _sound = SoundActor(levelManager.GetCurrentLevel(),"../Content/Sound/sonic-unleashed-ost.mp3", _soundInfo);
    //_sound.Construct();
    //_sound.BeginPlay();


#pragma endregion
    
    //Begin play on all Actors
    std::set<Actor*> _allActor = levelManager.GetCurrentLevel()->GetActorManager().GetAllActors();
    for (Actor* _actor : _allActor)
        _actor->BeginPlay();

    //Init time and size of window variables
    int _width, _height;
    double _deltaTime = 0.0;
    double _time = glfwGetTime();
    vec3 _targetPosition = vec3(0.0f);

    //Set the gl clear color
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    //The polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
    //Enable the depth
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window->GetWindow())) // PROBABLY REMOVE ESCAPE
    {
        #pragma region Computing
        // Compute deltaTime
        _deltaTime = glfwGetTime() - _time;
        _time = glfwGetTime();
        // Processing inputs
        
       /* _controller->ProcessInputs();*/
       
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

    const float _phi = _camera->GetPhi();
    const float _theta = _camera->GetTheta();
    const float _viewRadius = _camera->GetViewRadius();

        const float& _pitch = cos(_phi) * cos(_theta) * _viewRadius;
        const float& _yaw = sin(_phi) * _viewRadius;
        const float& _roll = cos(_phi) * sin(_theta) * _viewRadius;
        const vec3& _cameraPosition = vec3(_pitch, _yaw, _roll) + _targetPosition;

        _mesh->SetCameraLocation(_cameraPosition);

        vec3 _up = normalize(vec3(0.0f, cosf(_phi), 0.0f));
        _view = lookAt(_cameraPosition, _targetPosition, _up);
        _skyboxView = _view;

        //const GLuint& _uniformViewPosition = glGetUniformLocation(_mesh->GetShaderProgram(), "uniformViewPosition");
        //const GLuint& _uniformViewPosition = glGetUniformLocation(_material.GetShader()->GetShaderProgram(), "uniformViewPosition");
        //glUniform3f(_uniformViewPosition, _cameraPosition.x, _cameraPosition.y, _cameraPosition.z);

        mat4 _projection = mat4();
        if (_height != 0.0f)
            _projection = perspective(radians(90.0f), (float)_width / (float)_height, 0.1f, 100.0f);

        mat4 _skyboxModel = mat4(1.0f);
        mat4 _model = mat4(1.0f);
        _skyboxModel = translate(_skyboxModel, _cameraPosition);
        _skybox->SetMVP(_skyboxModel, _skyboxView, _projection);
        //_mesh->GetTransform()->rotation += 1 * _deltaTime;
        //_model = rotate(_model, _mesh->GetTransform()->rotation.x, vec3(1, 0, 0));
        //_model = rotate(_model, _mesh->GetTransform()->rotation.y, vec3(0, 1, 0));
        //_model = rotate(_model, _mesh->GetTransform()->rotation.z, vec3(0, 0, 1));
        //translate
        //scale
        _mesh->SetMVP(_model, _view, _projection);
        //_mesh->SetUniformModelMatrix();
        #pragma endregion	
        //world->Update();

        window->Update(); // ProcessInputs 
        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    glfwDestroyWindow(window->GetWindow());
    glfwTerminate();

}

void Engine::Stop()
{

    levelManager.Destroy();
    //world->Stop();
    // destroy level
}

void Engine::InitInput(CameraComponent* _camera)
{
    Controller* _controller = window->GetController();

    const function<void()> _moveCameraUp = bind(&CameraComponent::MoveViewUp, _camera);
    _controller->AddInputAction("CameraMoveUp", { GLFW_KEY_W }, _moveCameraUp);
    const function<void()> _moveCameraDown = bind(&CameraComponent::MoveViewDown, _camera);
    _controller->AddInputAction("CameraMoveDown", { GLFW_KEY_S }, _moveCameraDown);
    const function<void()> _moveCameraLeft = bind(&CameraComponent::MoveViewLeft, _camera);
    _controller->AddInputAction("CameraMoveLeft", { GLFW_KEY_A }, _moveCameraLeft);
    const function<void()> _moveCameraRight = bind(&CameraComponent::MoveViewRight, _camera);
    _controller->AddInputAction("CameraMoveRight", { GLFW_KEY_D }, _moveCameraRight);
    const function<void()> _zoomInCamera = bind(&CameraComponent::ZoomIn, _camera);
    _controller->AddInputAction("CameraZoomIn", { GLFW_KEY_E }, _zoomInCamera);
    const function<void()> _zoomOutCamera = bind(&CameraComponent::ZoomOut, _camera);
    _controller->AddInputAction("CameraZoomOut", { GLFW_KEY_Q }, _zoomOutCamera);
}
