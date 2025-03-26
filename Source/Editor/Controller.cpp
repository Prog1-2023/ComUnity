#include "Controller.h"
#include "map"
//InputController currentInput;
vector<Input> currentInput;
map<int,Input> allInputs;

Controller::Controller(GLFWwindow* _window)
{
	//TODO move into Camera class
	viewRadius = 5.0f;
	theta = 0.0f;
	phi = 0.0f;
	speed = 0.05f;
	zoomSpeed = 0.1f;

	//Window
	window = _window;
	glfwSetKeyCallback(window, InputCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Controller::ProcessInputs()
{
	vector<int> _tempToDestroy;

	for (const pair<int, Input>& _pair : allInputs)
	{
		Input _input = _pair.second;

		//if (_input.action != GLFW_PRESS && _input.action != GLFW_REPEAT) return;

		if (IsValidKey(_input.scancode, { GLFW_KEY_ESCAPE }))
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_UP, GLFW_KEY_W }))
		{
			cout << "HAUT" << endl;
			phi += speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_DOWN, GLFW_KEY_S }))
		{
			cout << "DOWN" << endl;
			phi -= speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_LEFT, GLFW_KEY_A }))
		{
			cout << "LEFT" << endl;
			theta -= speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_RIGHT, GLFW_KEY_D }))
		{
			cout << "RIGHT" << endl;
			theta += speed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_Q }))
		{
			cout << "ZOOM" << endl;
			viewRadius += zoomSpeed;
		}

		if (IsValidKey(_input.scancode, { GLFW_KEY_E }))
		{
			cout << "DE-ZOOM" << endl;
			viewRadius -= zoomSpeed;
		}

		if (_input.action == GLFW_RELEASE)
			_tempToDestroy.push_back(_pair.first);
	}
	int _size = _tempToDestroy.size();
	for (int i = 0; i < _size; i++)
	{
		allInputs.erase(_tempToDestroy[i]);
	}

	/*for (int i = 0; i < currentInput.size(); i++)
	{
		if (currentInput[i].action != GLFW_PRESS && currentInput[i].action != GLFW_REPEAT) return;

		if (IsValidKey(currentInput[i].scancode, { GLFW_KEY_ESCAPE }))
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (IsValidKey(currentInput[i].scancode, { GLFW_KEY_UP, GLFW_KEY_W }))
		{
			cout << "HAUT" << endl;
			phi += speed;
		}

		if (IsValidKey(currentInput[i].scancode, { GLFW_KEY_DOWN, GLFW_KEY_S }))
		{
			cout << "DOWN" << endl;
			phi -= speed;
		}

		if (IsValidKey(currentInput[i].scancode, { GLFW_KEY_LEFT, GLFW_KEY_A }))
		{
			cout << "LEFT" << endl;
			theta -= speed;
		}

		if (IsValidKey(currentInput[i].scancode, { GLFW_KEY_RIGHT, GLFW_KEY_D }))
		{
			cout << "RIGHT" << endl;
			theta += speed;
		}

		if (IsValidKey(currentInput[i].scancode, { GLFW_KEY_Q }))
		{
			cout << "ZOOM" << endl;
			viewRadius += zoomSpeed;
		}

		if (IsValidKey(currentInput[i].scancode, { GLFW_KEY_E }))
		{
			cout << "DE-ZOOM" << endl;
			viewRadius -= zoomSpeed;
		}

	}*/
}

void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods)
{
	//currentInput = InputController(_window, _key, _scancode, _action, _mods);
	/*InputController _controller = InputController(_window, _key, _scancode, _action, _mods);
	if (_action == GLFW_PRESS)
		currentInput.push_back(_controller);
	else
	{
		for (int i = 0; i < currentInput.size(); i++)
		{
			if (currentInput[i].scancode == _controller.scancode)
			{
				currentInput.erase(currentInput.begin() + i);
				break;
			}

		}
	}*/
	
	allInputs[_scancode] = (Input(_window, _key, _scancode, _action, _mods));
	
}
