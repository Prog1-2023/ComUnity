#include "Window.h"

Window::Window(const string& _name)
{
	Construct(Vector2i(0, 0), _name);
}

Window::Window(const int _width, const int _height, const string& _name)
{
	Construct(Vector2i(_width, _height), _name);
}

Window::Window(const Vector2i& _windowSize, const string& _name)
{
	Construct(_windowSize, _name);
}

Window::~Window()
{
	delete controller;
}

void Window::Construct(const Vector2i& _size, const string& _name)
{
	name = _name;
	size = _size;
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
	const string& _errorName = !_errorText ? "Unknown error" : _errorText;
	const string& _error = "Asserted Error => glewInit failed : " + _errorName;
	Assert(_initStatus == GLEW_OK, _error.c_str());
}

void Window::InitController()
{
	controller = new Controller(window);
}
