#pragma once
#include "../../Utils/CoreMinimal.h"
#include "../Controller.h"

class Window
{
	string name;
	Vector2i size;
	GLFWwindow* window;
	Controller* controller;

public:
	FORCEINLINE GLFWwindow* GetWindow() const { return window; }
	FORCEINLINE Vector2i GetSize() const { return size; }
	FORCEINLINE Controller* GetController() const { return controller; }

public:
	Window(const string& _name = "Unknown");
	Window(const int _width, const int _height, const string& _name);
	Window(const Vector2i& _windowSize, const string& _name);
	~Window();

private:
	void Construct(const Vector2i& _size, const string& _name);
	void Init();
	void InitWindow();
	void InitGLEW();
	void InitController();
};