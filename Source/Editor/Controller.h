#pragma once
#include "../Utils/CoreMinimal.h"

#define KEY(GLFW_KEY) glfwGetKeyScancode(GLFW_KEY)

struct Input
{
	GLFWwindow* window;
	int key;
	int scancode;
	int action;
	int mods;

	Input() = default;
	Input(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods)
	{
		window = _window;
		key = _key;
		scancode = _scancode;
		action = _action;
		mods = _mods;
	}
};

struct InputAction
{
	vector<GLuint> keys;
	function<void()> callback;

	InputAction() = default;

	InputAction(const vector<GLuint>& _keys, const function<void()>& _callback)
	{
		keys = _keys;
		callback = _callback;
	}

	bool IsRightKey(const GLuint& _scancode)
	{
		GLuint _size = keys.size();
		for (GLuint _i = 0; _i < _size; _i++)
		{
			if (_scancode == KEY(keys[_i]))
				return true;
		}
		return false;
	}

	void Invoke()
	{
		callback();
	}
};

class Controller
{
	map<string, InputAction> inputMappingContext;

	//TODO move into camera class
	GLFWwindow* window;

private:
	/*FORCEINLINE bool IsValidKey(const GLuint& _scancode, const vector<unsigned int>& _allKeys)
	{
		const GLuint& _keysCount = _allKeys.size();
		for (unsigned int _i = 0; _i < _keysCount; _i++)
		{
			if (_scancode == KEY(_allKeys[_i]))
				return true;
		}

		return false;
	}*/
	FORCEINLINE void ComputeKey(const GLuint& _scancode)
	{
		for (pair <string, InputAction> _pair : inputMappingContext)
		{
			if (_pair.second.IsRightKey(_scancode))
				_pair.second.Invoke();
		}
	}

public:
	Controller(GLFWwindow* _window);

public:
	void PollEvents();
	void AddInputAction(const string& _name,const vector<GLuint>& _allKeys, const function<void()>& _callback);
};

void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods);