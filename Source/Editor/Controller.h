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

    GLFWwindow* window;

public:
    float viewRadius;
    float theta; 
    float phi;
    float speed;
    float zoomSpeed;


private:

    FORCEINLINE void ComputeKey(const GLuint& _scancode)
    {
        for (pair <string, InputAction> _pair : inputMappingContext)
        {
            if (_pair.second.IsRightKey(_scancode))
                _pair.second.Invoke();
        }
    }
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
    Controller(GLFWwindow* _window);

public:
    //void pollevents();
    //void addinputaction(const string& _name, const vector<gluint>& _allkeys, const function<void()>& _callback);
    void ProcessInputs();
};

void InputCallback(GLFWwindow* _window, const int _key, const int _scancode, const int _action, const int _mods);