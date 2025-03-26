#include "../Utils/CoreMinimal.h"
#include "../Editor/Windows/Window.h"
#include "../Editor/World.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"

#pragma region Forwards

//template <typename RetType = void*, typename Type = GLfloat>
//RetType SizeOf(const int _count);

//string GetPath(const FolderType& _folderType);
//bool CheckShaderForErrors(const GLuint& _shader, const string& _shaderName = "");
//bool Generate2DShape(vector<GLfloat>& _vertices, vector<GLuint>& _edges, const int _verticesCount, const bool _useColor);
//bool Generate3DShape(vector<GLfloat>& _vertices, vector<GLuint>& _edges, const int _verticesCount, const bool _useColor);
//unsigned int LoadTexture(const string& _filePath);
vec3 GetPositionAround(const unsigned int _index, const unsigned int _count, const float _radius);
//void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods);
void Shutdown(GLFWwindow* _window);

#pragma endregion

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "../Actors/Lights/LightActor.h"
#include "../Actors/Skybox.h"
#include "../NewLightRelated/Material.h"

using namespace Assimp;

int main()
{
	Window _window = Window("Engine", Vector2i(800, 800));
	World* _world = new World();
	_world->SetWindow(&_window);

	Actor* _actor = _world->SpawnActor<CameraActor>();
	_actor->LoadModel("backpack/Model/backpack.obj");

	LightActor* _light = _world->SpawnLight(NONE);
	LightActor* _light2 = _world->SpawnLight(DIRECTIONAL);

	Skybox* _skybox = _world->SpawnActor<Skybox>();
	
	_skybox->Init({ "cube_right.png", "cube_left.png",
		"cube_up.png", "cube_down.png", "cube_back.png", "cube_front.png" }, 100.f);

	int _size = _world->GetAllActors().size();

	for (size_t i = 0; i < _size; i++)
	{
		_world->GetAllActors()[i]->BeginPlay();
	}


	Controller* _controller = _window.GetController();

	StaticMeshComponent* _mesh = _actor->GetComponent<StaticMeshComponent>();
	CameraComponent* _camera = _actor->GetComponent<CameraComponent>();

	int _width, _height;
	double _deltaTime = 0.0;
	double _time = glfwGetTime();
	vec3 _targetPosition = vec3(0.0f);
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(_window.GetWindow()))
	{
#pragma region Computing
		// Compute deltaTime
		_deltaTime = glfwGetTime() - _time;
		_time = glfwGetTime();
		_window.GetController()->ProcessInputs();
#pragma endregion

#pragma region Clear
		glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#pragma endregion

		for (size_t i = 0; i < _size; i++)
		{
			_world->GetAllActors()[i]->Tick(_deltaTime);
		}

		mat4 _view = mat4(1.0f);
		_view = _camera->ComputeView();
		//const float& _pitch = cos(_controller->phi) * cos(_controller->theta) * _controller->viewRadius;
		//const float& _yaw = sin(_controller->phi) * _controller->viewRadius;
		//const float& _roll = cos(_controller->phi) * sin(_controller->theta) * _controller->viewRadius;
		//const vec3& _cameraPosition = vec3(_pitch, _yaw, _roll) + _targetPosition;


		mat4 _skyboxView = mat4(1.0f);
		const float& _pitch = cos(_controller->phi) * cos(_controller->theta) * _controller->viewRadius;
		const float& _yaw = sin(_controller->phi) * _controller->viewRadius;
		const float& _roll = cos(_controller->phi) * sin(_controller->theta) * _controller->viewRadius;
		const vec3& _cameraPosition = vec3(_pitch, _yaw, _roll) + _targetPosition;

		_mesh->SetCameraLocation(_cameraPosition);

		vec3 _up = normalize(vec3(0.0f, cosf(_controller->phi), 0.0f));
		 if (_controller->phi > half_pi<float>() || _controller->phi < -half_pi<float>())
			_up.y = -1.0f; 
			_skyboxView = lookAt(_cameraPosition, _targetPosition, _up);

		mat4 _projection = mat4();
		if (_height != 0.0f)
			_projection = perspective(radians(90.0f), (float)_width / (float)_height, 0.1f, 1000.0f);

		mat4 _skyboxModel = mat4(1.0f);
		mat4 _model = mat4(1.0f);
		_skyboxModel = translate(_skyboxModel, _cameraPosition);
		_skybox->SetMVP(_skyboxModel, _skyboxView, _projection);
		_mesh->SetMVP(_model, _view, _projection);



#pragma region Update
		glfwSwapBuffers(_window.GetWindow());
		glfwPollEvents();
#pragma endregion
	}

	_actor->BeginDestroy();
	Shutdown(_window.GetWindow());
	delete _world;
	return EXIT_SUCCESS;
}

vec3 GetPositionAround(const unsigned int _index, const unsigned int _count, const float _radius)
{
	vec3 _position = vec3(0.0f);
	const float _angle = 2.0f * M_PI / _count * _index;

	_position.x = cosf(_angle) * _radius;
	_position.y = sinf(_angle) * _radius;

	return _position;
}

//#define KEY(GLFW_KEY) glfwGetKeyScancode(GLFW_KEY)
//
//bool IsValidKey(const unsigned int _scancode, const vector<unsigned int>& _allKeys)
//{
//	const unsigned int _keysCount = _allKeys.size();
//	for (unsigned int _index = 0; _index < _keysCount; _index++)
//	{
//		if (_scancode == KEY(_allKeys[_index])) return true;
//	}
//
//	return false;
//}
//
//void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods)
//{
//	if (_action != GLFW_PRESS || _action == GLFW_REPEAT)
//	{
//		if (IsValidKey(_scancode, { GLFW_KEY_ESCAPE }))
//		{
//			glfwSetWindowShouldClose(_window, true);
//		}
//
//		const float speed = 0.05f;
//		const float zoomSpeed = 0.1f;
//
//		if (IsValidKey(_scancode, { GLFW_KEY_UP, GLFW_KEY_W }))
//		{
//			cout << "HAUT" << endl;
//			phi += speed;
//		}
//
//		if (IsValidKey(_scancode, { GLFW_KEY_DOWN, GLFW_KEY_S }))
//		{
//			cout << "DOWN" << endl;
//			phi -= speed;
//		}
//
//		if (IsValidKey(_scancode, { GLFW_KEY_LEFT, GLFW_KEY_A }))
//		{
//			cout << "LEFT" << endl;
//			theta -= speed;
//		}
//
//		if (IsValidKey(_scancode, { GLFW_KEY_RIGHT, GLFW_KEY_D }))
//		{
//			cout << "RIGHT" << endl;
//			theta += speed;
//		}
//
//		if (IsValidKey(_scancode, { GLFW_KEY_Q }))
//		{
//			cout << "ZOOM" << endl;
//			viewRadius += zoomSpeed;
//		}
//
//		if (IsValidKey(_scancode, { GLFW_KEY_E }))
//		{
//			cout << "DE-ZOOM" << endl;
//			viewRadius -= zoomSpeed;
//		}
//	}
//}

void Shutdown(GLFWwindow* _window)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}