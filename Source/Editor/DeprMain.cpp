#include "../Utils/CoreMinimal.h"

#include "Windows/Window.h"
#include "World.h"
#include "..\Actors\Cameras\CameraActor.h"
#include "..\Components\StaticMeshComponent.h"

#include "../NewLightRelated/Material.h"

void Shutdown(GLFWwindow* _window);
vec3 GetPositionAround(const unsigned int& _index, const unsigned int& _maxIndex, const float& _radius);

int deprMain()
{
	Window _window = Window("Engine window", 600, 600);
	World* _world = new World();
	_world->SetWindow(&_window);

	//Actor* _actor = _world->SpawnActor();
	//_actor->LoadModel("Survival_BackPack/Meshes/backpack.obj");
	//_actor->BeginPlay();

	Controller* _controller = _window.GetController();
	Material _material("NewVertTest.vert", "NewFragTest.frag");
	//_material.InitAlbedo(Vector4f(0, 1, 1, 1.f));
	_material.InitAlbedo("Face.png");

	float _vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	// first, configure the cube's VAO (and VBO)
	unsigned int _VBO, _cubeVAO;
	glGenVertexArrays(1, &_cubeVAO);
	glGenBuffers(1, &_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glBindVertexArray(_cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int _lightCubeVAO;
	glGenVertexArrays(1, &_lightCubeVAO);
	glBindVertexArray(_lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);

	//StaticMeshComponent* _mesh = _actor->GetComponent<StaticMeshComponent>();

	int _width, _height;
	double _deltaTime = 0.0;
	double _time = glfwGetTime();
	vec3 _targetPosition = vec3(0.0f);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(_window.GetWindow()))
	{
		#pragma region Computing
		// Compute deltaTime
		_deltaTime = glfwGetTime() - _time;
		_time = glfwGetTime();
		_window.GetController()->ProcessInputs();
		#pragma endregion

		#pragma region Clear
		glfwGetFramebufferSize(_window.GetWindow(), &_width, &_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		#pragma endregion

		//_actor->Tick(_deltaTime);
		#pragma region Compute MVP
		mat4 _view = mat4(1.0f);
		const float& _pitch = cos(_controller->phi) * cos(_controller->theta) * _controller->viewRadius;
		const float& _yaw = sin(_controller->phi) * _controller->viewRadius;
		const float& _roll = cos(_controller->phi) * sin(_controller->theta) * _controller->viewRadius;
		const vec3& _cameraPosition = vec3(_pitch, _yaw, _roll) + _targetPosition;

		//_mesh->SetCameraLocation(_cameraPosition);
		vec3 _up = normalize(vec3(0.0f, cosf(_controller->phi), 0.0f));
		_view = lookAt(_cameraPosition, _targetPosition, _up);

		//const GLuint& _uniformViewPosition = glGetUniformLocation(_mesh->GetShaderProgram(), "uniformViewPosition");
		const GLuint& _uniformViewPosition = glGetUniformLocation(_material.GetShader()->GetShaderProgram(), "uniformViewPosition");
		glUniform3f(_uniformViewPosition, _cameraPosition.x, _cameraPosition.y, _cameraPosition.z);

		mat4 _projection = mat4();
		if (_height != 0.0f)
			_projection = perspective(radians(90.0f), (float)_width / (float)_height, 0.1f, 100.0f);

		mat4 _model = mat4(1.0f);
		#pragma endregion	

		_material.SetMVP(_model, _view, _projection);
		_material.Update();

		//_mesh->SetMVP(_model, _view, _projection);
		//_mesh->Update();

		//Draw
		glBindVertexArray(_cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		#pragma region Update
		glfwSwapBuffers(_window.GetWindow());
		glfwPollEvents();
		#pragma endregion
	}

	//_actor->BeginDestroy();
	Shutdown(_window.GetWindow());
	delete _world;
	return EXIT_SUCCESS;
}

void Shutdown(GLFWwindow* _window)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

vec3 GetPositionAround(const unsigned int& _index, const unsigned int& _maxIndex, const float& _radius)
{
	const float& _step = 360.0f / _maxIndex;

	const float& _radians = (M_PI / 180.0f) * _step * _index;

	const float& _x = 0.0f;
	const float& _y = sin(_radians) * _radius;
	const float& _z = cos(_radians) * _radius;

	return vec3(_x, _y, _z);
}