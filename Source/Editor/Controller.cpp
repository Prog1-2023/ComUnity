#include "Controller.h"
#include <queue>

//scancode, Input
map<int, Input> allInputs;

Controller::Controller(GLFWwindow* _window)
{
	window = _window;
	glfwSetKeyCallback(window, InputCallback);
	glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

	inputMappingContext = map<string, InputAction>();
}

void Controller::PollEvents()
{
	vector<int> _tempToDestroy;

	for (map<int, Input>::const_iterator _it = allInputs.begin(); _it != allInputs.end();_it++)
	{
		const Input& _input = _it->second;

		ComputeKey(_input.scancode);

		/*if (IsValidKey(_input.scancode, { GLFW_KEY_ESCAPE }))
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_UP, GLFW_KEY_W }))
		{
			phi += speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_DOWN, GLFW_KEY_S }))
		{
			phi -= speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_LEFT, GLFW_KEY_A }))
		{
			theta -= speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_RIGHT, GLFW_KEY_D }))
		{
			theta += speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_Q }))
		{
			viewRadius += zoomSpeed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_E }))
		{
			viewRadius -= zoomSpeed;
		}*/

		if (_input.action == GLFW_RELEASE)
			_tempToDestroy.push_back(_it->first);
	}
	
	size_t _size = _tempToDestroy.size();
	for (size_t _i = 0; _i < _size; _i++)
	{
		allInputs.erase(_tempToDestroy[_i]);
	}
}

void Controller::AddInputAction(const string& _name,const vector<GLuint>& _allKeys, const function<void()>& _callback)
{
	InputAction _action = InputAction(_allKeys,_callback);
	inputMappingContext[_name] = _action;
}

void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods)
{
	allInputs[_scancode] = Input(_window, _key, _scancode, _action, _mods);
}
