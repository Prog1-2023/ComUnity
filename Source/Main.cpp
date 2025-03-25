#include <iostream>

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

using namespace std;
using namespace Assimp;
using namespace fmt;
using namespace reactphysics3d;
using namespace irrklang;

int main()
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
	PhysicsCommon physicsCommon;

	// Create a physics world
	PhysicsWorld* world = physicsCommon.createPhysicsWorld();

	// Create a rigid body in the world
	Vector3 position(0, 20, 0);
	Quaternion orientation = Quaternion::identity();
	Transform transform(position, orientation);
	RigidBody* body = world->createRigidBody(transform);

	const decimal timeStep = 1.0f / 60.0f;

	// Step the simulation a few steps
	for (int i = 0; i < 20; i++) 
	{

		world->update(timeStep);

		// Get the updated position of the body
		const Transform& transform = body->getTransform();
		const Vector3& position = transform.getPosition();

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

	// OpenGL
	// Initialisation de GLFW
	if (!glfwInit()) {
		std::cerr << "Erreur d'initialisation de GLFW!" << std::endl;
		return -1;
	}

	// Créer une fenêtre GLFW
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL avec GLEW", nullptr, nullptr);
	if (!window) {
		std::cerr << "Erreur de création de la fenêtre!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Rendre le contexte de la fenêtre courant
	glfwMakeContextCurrent(window);

	// Initialiser GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Erreur d'initialisation de GLEW!" << std::endl;
		return -1;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Boucle de rendu
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap des buffers
		glfwSwapBuffers(window);

		// Polling des événements
		glfwPollEvents();
	}

	// Nettoyer et quitter
	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}