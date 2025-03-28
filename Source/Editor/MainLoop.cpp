#include "MainLoop.h"
//#include "Controller.h"

MainLoop::MainLoop(const int _widht, const int _height, const string& _windowName)
{
	window = nullptr;
	windowDimension = Vector2i(_widht,_height);
	windowLabel = _windowName;

	time = 0.0f;
	deltatime = 0.0f;
}

bool MainLoop::Init()
{
	if (!glfwInit())
	{
		cerr << "Initialization of GLFW failed !" << endl;
		return false;
	}

	GLFWwindow* _window = glfwCreateWindow(windowDimension.x, windowDimension.y, windowLabel.c_str(), NULL, NULL);
	if (!_window)
	{
		cerr << "Window creation failed !" << endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_window);

	//glfwSetKeyCallback(_window, InputCallback);


	return true;
}

void MainLoop::Update()
{
	while (!glfwWindowShouldClose(window))
	{
		deltatime = glfwGetTime() - time;
		time = glfwGetTime();

		Clear();
		Draw();
		Display();
	}
	Shutdown();
}

void MainLoop::Clear()
{
	glfwGetFramebufferSize(window, &windowDimension.x, &windowDimension.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainLoop::Draw()
{
	// DRAW ALL ELEMENTS
}

void MainLoop::Display()
{
	glfwSwapBuffers(window);

	// Deletion ?
}

void MainLoop::Shutdown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
