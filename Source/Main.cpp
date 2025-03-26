#include <iostream>
#include <vector>

// FMT
#include <fmt/core.h>

// ImGui
#include <imgui.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// ReactPhysics3D
#include <reactphysics3d/reactphysics3d.h>

// IrrKlang
#include <irrKlang.h>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Light Related
#include "Editor/Windows/Window.h"	
#include "Editor/World.h"
#include "NewLightRelated/Material.h"

using namespace std;
using namespace Assimp;
using namespace fmt;
using namespace irrklang;
namespace rea = reactphysics3d;

int InitMain();

int main()
{
	if(InitMain())return -1;

	// Créer une fenêtre GLFW
	
	Window _window = Window("Engine window", 600, 600);
	World* _world = new World();
	_world->SetWindow(&_window);


	Controller* _controller = _window.GetController();
	Material _material("NewVertTest.vert", "NewFragTest.frag");
	//_material.InitAlbedo(Vector4f(0, 1, 1, .5f));
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


	int _width, _height;
	double _deltaTime = 0.0;
	double _time = glfwGetTime();
	vec3 _targetPosition = vec3(0.0f);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	// Boucle de rendu
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

	// Nettoyer et quitter
	glfwDestroyWindow(_window.GetWindow());
	glfwTerminate();

	return EXIT_SUCCESS;
}

int InitMain()
{
	cout << "ComUnity : l'Engine des Communistes !" << endl;

	// FMT
	print("value : {}!\n", 12);

	// Assimp
	Importer importer;
	const aiScene* scene = importer.ReadFile("test.obj", aiProcess_Triangulate);
	if (scene)
	{
		cout << "Assimp a chargé un fichier avec " << scene->mNumMeshes << " mesh(es).\n";
	}
	else
	{
		cout << "Assimp n'a pas pu charger le fichier test.obj.\n";
	}

	// ReactPhysics
	// First you need to create the PhysicsCommon object. This is a factory module
	// that you can use to create physics world and other objects. It is also responsible
	// for logging and memory management
	rea::PhysicsCommon physicsCommon;

	// Create a physics world
	rea::PhysicsWorld* world = physicsCommon.createPhysicsWorld();

	// Create a rigid body in the world
	rea::Vector3 position(0, 20, 0);
	rea::Quaternion orientation = rea::Quaternion::identity();
	rea::Transform transform(position, orientation);
	rea::RigidBody* body = world->createRigidBody(transform);

	const rea::decimal timeStep = 1.0f / 60.0f;

	// Step the simulation a few steps
	for (int i = 0; i < 20; i++)
	{
		world->update(timeStep);

		// Get the updated position of the body
		const rea::Transform& transform = body->getTransform();
		const rea::Vector3& position = transform.getPosition();

		// Display the position of the body
		cout << "Body Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << endl;
	}

	// IrrKlang
	ISoundEngine* soundEngine = createIrrKlangDevice();
	if (soundEngine)
	{
		cout << "IrrKlang initialisé avec succès !\n";
		soundEngine->drop();
	}
	else
	{
		cout << "Erreur d'initialisation d'IrrKlang.\n";
	}

	return EXIT_SUCCESS;
}
