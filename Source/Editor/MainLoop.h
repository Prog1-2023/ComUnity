#pragma once
#include "../Utils/CoreMinimal.h"

class MainLoop
{
	GLFWwindow* window;
	Vector2i windowDimension;
	string windowLabel;

	float time;
	float deltatime;

public:
	MainLoop(const int _widht, const int _height, const string& _windowName);

public:
	bool Init();
	void Update();

private:
	void Clear();
	void Draw();
	void Display();

	void Shutdown();
};

