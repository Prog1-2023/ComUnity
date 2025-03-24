#include "../Utils/CoreMinimal.h"
#include "Windows/Window.h"
#include "../Actors/Actor.h"	
#include "World.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"

#pragma region Forwards

/// Classes
// Actor / Component / TransformComponent / StaticMeshComponent / Camera Component / Texture / Shader / Material
// Camera Actor (avec un camera component)
// Controller / World / GameMode / GameInstance / Subsystem / 
// MainLoop


// MainLoop => Controller => World => Actor => Component => TransformComp => CameraActor => CameraComp => StaticMeshComp (Shapes => Shader / Texture / Material)


int main();

void Shutdown(GLFWwindow* _window);

#pragma endregion

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);





	World* _world = new World();
	Window _window = Window(800, 600, "Oui oui");
	_world->SetWindow(&_window);

	Actor* _actor = _world->SpawnActor();
	_actor->LoadModel("D:/Damien/Engine/Content/Survival_Backpack/Meshes/Survival_BackPack.fbx");
	_actor->BeginPlay();

	StaticMeshComponent* _mesh = _actor->GetComponent<StaticMeshComponent>();
	CameraActor* _camera = _world->SpawnActor<CameraActor>();
	_world->SetCurrentCamera(_camera);
	_world->Initialize();

	int _width, _height;
	double _time = glfwGetTime();
	double _deltatime = 0.0;
	glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
	vec3 _targetPos = vec3(0.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//unsigned int lightVAO;
	//glGenVertexArrays(1, &lightVAO);
	//glBindVertexArray(lightVAO);
	//// we only need to bind to the VBO, the container's VBO's data already contains the data.
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//// set the vertex attribute 
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);


#pragma region ImGui

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.MouseDrawCursor = true;

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window.GetWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init("#version 330");

#pragma endregion

	float f = 0.0f;
	string buf = "oui";
	bool _oui = true;

	while (!glfwWindowShouldClose(_window.GetWindow()))
	{
		glfwPollEvents();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		

		ImGui::Begin("My First Tool", &_oui, ImGuiWindowFlags_MenuBar);

		ImGui::Text("Hello, world %d", 123);
		if (ImGui::Button("Save"))
			cout << "pd" << endl;

		ImGui::InputText("string", buf.data(), 20);
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

		ImGui::End();


		// Compute deltaTime
		_deltatime = glfwGetTime() - _time;
		_time = glfwGetTime();

		//_actor->Tick(_deltatime);

		// Clear
		glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_window.GetController()->PollEvents();

		// Faire le MVP au bon endroit

		////TODO move into camera class
		//mat4 _projection = mat4(1.0f);
		//_projection = perspective(radians(90.0f), (float)_width / (float)_height, 0.1f, 100.0f);
		//mat4 _view = mat4(1.0f);
		//const float _pitch = cosf(_world->GetCurrentCamera()->phi) * cosf(_world->GetCurrentCamera()->theta) * _world->GetCurrentCamera()->viewRadius;
		//const float _yaw = sinf(_world->GetCurrentCamera()->phi) * _world->GetCurrentCamera()->viewRadius;
		//const float _roll = cosf(_world->GetCurrentCamera()->phi) * sinf(_world->GetCurrentCamera()->theta) * _world->GetCurrentCamera()->viewRadius;
		//const vec3& _cameraPos = vec3(_pitch, _yaw, _roll) + _targetPos;
		//vec3 _up = vec3(0, 1.0f, 0);
		//if (_world->GetCurrentCamera()->phi > half_pi<float>() || _world->GetCurrentCamera()->phi < -half_pi<float>())
		//{
		//	_up.y *= -1;
		//}
		//_view = lookAt(_cameraPos, _targetPos, _up);

		//if (_height != 0.0)
		//{
		//	_projection = perspective(radians(90.0f), float(_width) / (float)_height, 0.1f, 100.0f);
		//}


		////TODO REMOVE
		//_mesh->SetTime(_time);

		//int _cubeAmount = 1;
		//const float _angleStep = 2.0f * M_PI / _cubeAmount;
		//float _offset = 6.0f;

		//for (int _i = 0; _i < _cubeAmount; _i++)
		//{
		//	float _angle = _angleStep * _i;

		//	mat4 _model = mat4(1.0f);
		//	float _x = cosf(_angle * (float)_time) * _offset;
		//	float _y = sinf(_angle * (float)_time) * _offset;
		//	float _z = sinf(_angle) * cosf(_angle) * _offset;
		//	//_model = translate(_model, vec3(_x, _y, _z));

		//	//_model = translate(_model, vec3(2.0f,0.0f,0.0f));

		//	//_model = rotate(_model, (float)_time * radians(900.0f), vec3(1.0f));
		//	//_model = scale(_model, vec3(0.5f));

		//	_mesh->SetMVP(_model, _view, _projection);
		//	//_mesh->Tick(_deltatime);

		//}


				// Rendering
		// (Your code clears your framebuffer, renders your other stuff etc.)
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// (Your code calls glfwSwapBuffers() etc.)

		// Swap / Display
		
		glfwSwapBuffers(_window.GetWindow());
		//glfwSwapInterval(1);

		// Wait for inputs


	}

#pragma region Deletions

	//glDeleteVertexArrays(1, &_VAO);
	//glDeleteBuffers(1, &_VBO);
	//glDeleteBuffers(1, &_EBO);
	//glDeleteProgram(_shaderProgram);

#pragma endregion

	Shutdown(_window.GetWindow());
	_actor->BeginDestroy();
	delete _world;

	return EXIT_SUCCESS;
}

void Shutdown(GLFWwindow* _window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(_window);
	glfwTerminate();
}


void RotateSinCamera(bool _positive)
{
	mat4 _view = mat4(1.0f);
	const float _radius = -7.5f;

	//float _viewX = cosf(_angle) * _radius;
	float _viewZ = (sinf(10.0f) * _radius) * _positive ? 1.0f : -1.0f;
	_view = lookAt(vec3(0.0f, 0.0f, _viewZ), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));

	//_view = translate(_view, vec3(0.0f, 0.0f, -5.0f));

	//unsigned int _uniformView = glGetUniformLocation(_shaderProgram, "uniformView");
	//glUniformMatrix4fv(_uniformView, 1, GL_FALSE, value_ptr(_view));
}

void RotateCosCamera(bool _positive)
{
	mat4 _view = mat4(1.0f);
	const float _radius = -7.5f;

	float _viewX = (cosf(10.0f) * _radius) * _positive ? 1.0f : -1.0f;
	//float _viewZ = sinf(_angle) * _radius;
	_view = lookAt(vec3(_viewX, 0.0f, 0.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));

	//_view = translate(_view, vec3(0.0f, 0.0f, -5.0f));

	//unsigned int _uniformView = glGetUniformLocation(_shaderProgram, "uniformView");
	//glUniformMatrix4fv(_uniformView, 1, GL_FALSE, value_ptr(_view));
}





/*#include "../Utils/CoreMinimal.h"
#include "Windows/Window.h"
#include "../Actors/Actor.h"
#include "World.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"


#pragma region Forwards

void Shutdown(GLFWwindow* _window);

#pragma endregion

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	World* _world = new World();
	Window _window = Window(800, 600, "Oui oui");
	_world->SetWindow(&_window);

	Actor* _actor = _world->SpawnActor();
	//_actor->LoadModel("D:/Damien/Engine/Content/Survival_Backpack/Meshes/Survival_BackPack.fbx");
	//_actor->AddComponent<StaticMeshComponent>();
	_actor->BeginPlay();

	CameraActor* _camera = _world->SpawnActor<CameraActor>();
	_camera->BeginPlay();

	_world->SetCurrentCamera(_camera);
	_world->Initialize();

	int _width, _height;
	double _time = glfwGetTime();
	double _deltatime = 0.0;
	glClearColor(0.5f, 0.2f, 0.2f, 1.0f);

#pragma region Vertices

	float _vertices[] = {
		// positions
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};
#pragma endregion

#pragma region Shaders
	GLuint _shaderProgram = 0;
	string _vertexShaderPath = "VertexShader.vert";
	string _fragmentShaderPath = "FragmentShader.frag";

	glEnable(GL_DEPTH_TEST);
	const path& _currentPath = current_path();
	const path& _shaderPath = _currentPath.parent_path() / "Source/Shaders/";
	const string& _shaderPathstr = _shaderPath.string();

	// VertexShader
	unsigned int _vertexShader = glCreateShader(GL_VERTEX_SHADER);
	string _vertexShaderCode;
	_vertexShaderCode = TShader::ReadShader(_shaderPathstr + _vertexShaderPath);
	const char* _vertexShaderData = _vertexShaderCode.c_str();
	glShaderSource(_vertexShader, 1, &_vertexShaderData, NULL);
	glCompileShader(_vertexShader);

	// FragmentShader
	unsigned int _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	string _fragmentShaderCode;
	_fragmentShaderCode = TShader::ReadShader(_shaderPathstr + _fragmentShaderPath);
	const char* _fragmentShaderData = _fragmentShaderCode.c_str();
	glShaderSource(_fragmentShader, 1, &_fragmentShaderData, NULL);
	glCompileShader(_fragmentShader);

	// Link shaders
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);

	GLuint _modelID = glGetUniformLocation(_shaderProgram, "uniformModel");
	GLuint _viewID = glGetUniformLocation(_shaderProgram, "uniformView");
	GLuint _projectionID = glGetUniformLocation(_shaderProgram, "uniformProjection");

	// Clear shaders
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
#pragma endregion

#pragma region Buffers

	GLuint _VAO, _VBO;
	glGenVertexArrays(1, &_VAO); // Init 1 VAO
	glGenBuffers(1, &_VBO); // Init 1 VBO

	glBindVertexArray(_VAO); // Bind VAO

	glBindBuffer(GL_ARRAY_BUFFER, _VBO); // BIND VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW); // Setup vertices

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

#pragma endregion

	while (!glfwWindowShouldClose(_window.GetWindow()))
	{
		_window.GetController()->PollEvents();

		// Compute deltaTime
		_deltatime = glfwGetTime() - _time;
		_time = glfwGetTime();

		// Tick
		//_actor->Tick(_deltatime);
		_camera->Tick(_deltatime);

		// Faire le MVP au bon endroit
		//_world->SetVM(); // mange tes morts

		// Clear
		glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(_shaderProgram);
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 108);

		// Swap / Display
		glfwSwapBuffers(_window.GetWindow());
		//glfwSwapInterval(1);

		// Wait for inputs
		glfwPollEvents();
	}

	Shutdown(_window.GetWindow());
	_actor->BeginDestroy();
	_camera->BeginDestroy();
	delete _world;

	return EXIT_SUCCESS;
}

void Shutdown(GLFWwindow* _window)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}*/