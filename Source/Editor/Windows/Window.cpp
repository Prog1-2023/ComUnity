#include "Window.h"

Window::Window(const string& _name)
{
	Construct(_name, Vector2i());
}

Window::Window(const string& _name, const int _width, const int _height)
{
	Construct(_name, Vector2i(_width, _height));
}

Window::Window(const string& _name, const Vector2i& _windowSize)
{
	Construct(_name, _windowSize);	
}

Window::~Window()
{
	delete controller;
}

void Window::Construct(const string& _name, const Vector2i& _windowSize)
{
	name = _name;
	size = _windowSize;
	window = nullptr;
	controller = nullptr;

	Init();
}

void Window::Init()
{
	InitWindow();
	InitGLEW();
	InitController();
}

void Window::InitWindow()
{
	Assert(glfwInit(), "Initialization of GLFW failed !");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	window = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);
	Assert(window, "Window creation failed !");

	glfwMakeContextCurrent(window);
}

void Window::InitGLEW()
{
	glewExperimental = true;
	GLenum _initStatus = glewInit();

	const char* _errorText = (const char*)glewGetErrorString(_initStatus);
	const string& _errorName = !_errorText ? "/!\\ Unknown error /!\\" : _errorText;
	const string& _error = "Error => Initialization of GLEW failed: " + _errorName;
	Assert(_initStatus == GLEW_OK, _error.c_str());
}

void Window::InitController()
{
	controller = new Controller(window);
}