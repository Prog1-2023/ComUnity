#include <iostream>
#include <vector>

// FMT
#include <fmt/core.h>

// ImGui
#include <imgui.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// ReactPhysics3D
//#include <reactphysics3d/reactphysics3d.h>

// IrrKlang
#include <irrKlang.h>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Light Related
#include "Editor/Windows/Window.h"	
#include "Manager/Level.h"
#include "NewLightRelated/Material.h"
#include "Actors/Cameras/CameraActor.h"
#include "Actors/Skybox.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/Lights/LightActor.h"

using namespace std;
using namespace Assimp;
using namespace fmt;
using namespace irrklang;
//namespace rea = reactphysics3d;

int InitMain();
void Shutdown(GLFWwindow* _window);

int main()
{
	if (InitMain())return -1;

	#pragma region INITIALIZATION_OF_LIFETIME_TYPES
	// Create a GLFW window
	Window _window = Window("Engine window", 600, 600);
	// Create the world
	Level* _level = new Level("DefaultLevel");
	//_level->SetWindow(&_window);
	// Create the controller
	Controller* _controller = _window.GetController();
	#pragma endregion

	#pragma region LIGHT_DEMO_INITIALISATION

	Actor* _actor = _level->SpawnActor<CameraActor>();
	//_actor->LoadModel("backpack/Model/backpack.obj");

	/*LightActor* _light = _level->SpawnActor<>(NONE);
	LightActor* _light2 = _level->SpawnActor<>(DIRECTIONAL);*/

	Skybox* _skybox = _level->SpawnActor<Skybox>();

	_skybox->Init({ "cube_right.png", "cube_left.png",
		 "cube_down.png", "cube_up.png", "cube_front.png","cube_back.png" }, 1.f);

	StaticMeshComponent* _mesh = _actor->GetComponent<StaticMeshComponent>();
	CameraComponent* _camera = _actor->GetComponent<CameraComponent>();

	#pragma endregion

	//Begin play on all Actors
	int _size = _level->GetActorManager().GetAllActors().size();
	//for (size_t i = 0; i < _size; i++)
	for (Actor* _actor : _level->GetActorManager().GetAllActors())
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

	// Boucle de rendu
	while (!glfwWindowShouldClose(_window.GetWindow()))
	{
		#pragma region Computing
		// Compute deltaTime
		_deltaTime = glfwGetTime() - _time;
		_time = glfwGetTime();
		// Processing inputs
		_window.GetController()->ProcessInputs();
		#pragma endregion

		#pragma region Clear
		glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		#pragma endregion
		
		#pragma region TICK_ACTORS
		// Tick all actors of the world
		//for (size_t i = 0; i < _size; i++)
		for (Actor* _actor : _level->GetActorManager().GetAllActors())
			_actor->Tick(_deltaTime);
		#pragma endregion

		#pragma region COMPUTE_MVP
		mat4 _view = mat4(1.0f);
		mat4 _skyboxView = mat4(1.0f);
		_view = _camera->ComputeView();

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

		mat4 _skyboxModel = mat4(1.0f);
		mat4 _model = mat4(1.0f);
		_skyboxModel = translate(_skyboxModel, _cameraPosition);
		_skybox->SetMVP(_skyboxModel, _skyboxView, _projection);
		_mesh->SetMVP(_model, _view, _projection);
		#pragma endregion	

		#pragma region Update
		glfwSwapBuffers(_window.GetWindow());
		glfwPollEvents();
		#pragma endregion
	}

	// Clean and quit
	glfwDestroyWindow(_window.GetWindow());
	glfwTerminate();
	delete _level;
	_level = nullptr;
	return EXIT_SUCCESS;
}

int InitMain()
{
	cout << "ComUnity : l'Engine des Communistes !" << endl;

	// FMT
	print("value : {}!\n", 12);

	// Assimp
	Importer importer;
	const aiScene* scene = importer.ReadFile("test.obj", aiProcess_Triangulate);
	if (scene)
	{
		cout << "Assimp a chargé un fichier avec " << scene->mNumMeshes << " mesh(es).\n";
	}
	else
	{
		cout << "Assimp n'a pas pu charger le fichier test.obj.\n";
	}


	// IrrKlang
	ISoundEngine* soundEngine = createIrrKlangDevice();
	if (soundEngine)
	{
		cout << "IrrKlang initialisé avec succès !\n";
		soundEngine->drop();
	}
	else
	{
		cout << "Erreur d'initialisation d'IrrKlang.\n";
	}

	return EXIT_SUCCESS;
}

void Shutdown(GLFWwindow* _window)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}
