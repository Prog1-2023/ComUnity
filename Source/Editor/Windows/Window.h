#pragma once
#include "../../Utils/CoreMinimal.h"
#include "../Controller.h"

class Window
{
	string name;
	Vector2i size;
	GLFWwindow* renderWindow;
	Controller* controller;

public:
	FORCEINLINE Vector2i GetSize() const
	{
		return size;
	}
	FORCEINLINE GLFWwindow* GetWindow() const
	{
		return renderWindow;
	}
	FORCEINLINE Controller* GetController() const
	{
		return controller;
	}

public:
	Window(const string& _name = "Unknown");
	Window(const string& _name, const int _width, const int _height);
	Window(const string& _name, const Vector2i& _windowSize);
	~Window();

private:
	void Construct(const string& _name, const Vector2i& _windowSize);
	void Init();
	void InitWindow();
	void InitGLEW();
	void InitController();

public:
	void Update();
};