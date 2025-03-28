#include "Controller.h"
#include "map"
//InputController currentInput;
vector<InputController> currentInput;
map<int, InputController> allInputs;

Controller::Controller(GLFWwindow* _window)
{
	//TODO MOVE into camera class
	viewRadius = 5.0f;
	theta = 0.0f;
	phi = 0.0f;
	speed = 1.f;
	zoomSpeed = 1.f;
	window = _window;
	glfwSetKeyCallback(window, InputCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Controller::ProcessInputs()
{
	vector<int> _tempToDestroy;

	for (const pair<int, InputController>& _pair : allInputs)
	{
		InputController _input = _pair.second;

		//if (_input.action != GLFW_PRESS && _input.action != GLFW_REPEAT) return;

		if (IsValidKey(_input.scancode, { GLFW_KEY_ESCAPE }))
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_UP, GLFW_KEY_W }))
		{
			cout << "HAUT" << endl;
			phi += speed * deltaTime;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_DOWN, GLFW_KEY_S }))
		{
			cout << "DOWN" << endl;
			phi -= speed * deltaTime;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_LEFT, GLFW_KEY_A }))
		{
			cout << "LEFT" << endl;
			theta -= speed * deltaTime;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_RIGHT, GLFW_KEY_D }))
		{
			cout << "RIGHT" << endl;
			theta += speed * deltaTime;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_Q }))
		{
			cout << "ZOOM" << endl;
			viewRadius -= zoomSpeed * deltaTime;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_E }))
		{
			cout << "DE-ZOOM" << endl;
			viewRadius += zoomSpeed * deltaTime;
		}

		if (_input.action == GLFW_RELEASE)
			_tempToDestroy.push_back(_pair.first);
	}
	int _size = _tempToDestroy.size();
	for (int i = 0; i < _size; i++)
	{
		allInputs.erase(_tempToDestroy[i]);
	}
}

void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods)
{
	allInputs[_scancode] = (InputController(_window, _key, _scancode, _action, _mods));
}
