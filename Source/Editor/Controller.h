#pragma once

#include "../Utils/CoreMinimal.h"
#define KEY(GLFW_KEY) glfwGetKeyScancode(GLFW_KEY)

struct InputController
{
	GLFWwindow* window;
	int key;
	int scancode;
	int action;
	int mods;

	InputController() = default;
	InputController(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods)
	{
		window = _window;
		key = _key;
		scancode = _scancode;
		action = _action;
		mods = _mods;
	}
};


class Controller
{
	//TODO MOVE into camera class
public:
	float viewRadius;
	float theta;
	float phi;
	float speed;
	float zoomSpeed;
	float deltaTime;
private:
	GLFWwindow* window;

public:
	Controller(GLFWwindow* _window);
	~Controller() = default;

private:

	FORCEINLINE bool IsValidKey(const unsigned int _scancode, const vector<unsigned int>& _allKeys) const
	{
		const unsigned int _keysCount = _allKeys.size();
		for (unsigned int _index = 0; _index < _keysCount; _index++)
		{
			if (_scancode == KEY(_allKeys[_index])) return true;
		}
		return false;
	}

public:
	void ProcessInputs();
	FORCEINLINE void SetDeltaTime(float _value) { deltaTime = _value; }
};

void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods);
