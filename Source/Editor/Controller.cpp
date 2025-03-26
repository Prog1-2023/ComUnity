#include "Controller.h"

vector<Input> allInputs = vector<Input>();

Controller::Controller(GLFWwindow* _window)
{
	// TODO move into Camera class
	//viewRadius = 50.0f;
	viewRadius = 5.0f;
	theta = 0.0f;
	phi = 0.0f;
	speed = 0.05f;
	zoomSpeed = 0.1f;

	window = _window;
	glfwSetKeyCallback(window, InputCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Controller::ProcessInputs()
{
	int _offset = 0;
	FOR_OFFSET(allInputs, _offset)
	{
		const Input& _currentInput = allInputs[_index];

		if (IsValidKey(_currentInput.scancode, { GLFW_KEY_ESCAPE }))
			glfwSetWindowShouldClose(window, true);
		if (IsValidKey(_currentInput.scancode, { GLFW_KEY_UP, GLFW_KEY_W }))
			phi += speed;
		if (IsValidKey(_currentInput.scancode, { GLFW_KEY_DOWN, GLFW_KEY_S }))
			phi -= speed;
		if (IsValidKey(_currentInput.scancode, { GLFW_KEY_LEFT, GLFW_KEY_A }))
			theta += speed;
		if (IsValidKey(_currentInput.scancode, { GLFW_KEY_RIGHT, GLFW_KEY_D }))
			theta -= speed;
		if (IsValidKey(_currentInput.scancode, { GLFW_KEY_E }))
			viewRadius += zoomSpeed;
		if (IsValidKey(_currentInput.scancode, { GLFW_KEY_Q }))
			viewRadius -= zoomSpeed;

		if (_currentInput.action == GLFW_RELEASE)
		{
			allInputs.erase(allInputs.begin() + _index);
			_index--;
			_offset++;
		}
	}
}

void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods)
{
	if (_action != GLFW_PRESS && _action != GLFW_RELEASE)
		return;

	FOR(allInputs)
	{
		Input& _currentInput = allInputs[_index];

		if (_currentInput.scancode == _scancode)
		{
			_currentInput.action = _action;
			return;
		}
	}
	allInputs.push_back(Input(_window, _key, _scancode, _action, _mods));
}
