#include "../Utils/CoreMinimal.h"
#include "Windows/Window.h"
#include "../Actors/Actor.h"	
#include "World.h"
#include "../Actors/Cameras/CameraActor.h"
#include "../Components/StaticMeshComponent.h"
#include "../UI/Canvas.h"
#include "../UI/UIImage.h"
#include "../Serialization/Serialization.h"

/// Classes
// Actor / Component / TransformComponent / StaticMeshComponent / Camera Component / Texture / Shader / Material
// Camera Actor (avec un camera component)
// Controller / World / GameMode / GameInstance / Subsystem / 
// MainLoop


// MainLoop => Controller => World => Actor => Component => TransformComp => CameraActor => CameraComp => StaticMeshComp (Shapes => Shader / Texture / Material)


int main();

void Shutdown(GLFWwindow* _window);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Serialization::GetInstance().StartSerialization();

	World* _world = new World();
	Window _window = Window(800, 600, "Oui oui");
	_world->SetWindow(&_window);

	Actor* _actor = _world->SpawnActor();
	//_actor->LoadModel("D:/Damien/Engine/Content/Survival_Backpack/Meshes/Survival_BackPack.fbx");
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
	//io.MouseDrawCursor = true;

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_window.GetWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init("#version 330");

#pragma endregion

	//Canvas* _canva = new Canvas(_world,"Canva");
	//UIImage* _image = new UIImage(_world,"Image Test");
	//_canva->Add(_image);

	while (!glfwWindowShouldClose(_window.GetWindow()))
	{
		glfwPollEvents();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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

		//_canva->Draw();


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

	//delete _canva;
	//delete _image;

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
