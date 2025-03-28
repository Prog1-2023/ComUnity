#include "../Source/Utils/CoreMinimal.h"

//Light Related
#include "Editor/Windows/Window.h"	
//#include "Editor/World.h"
#include "NewLightRelated/Material.h"
#include "Actors/Cameras/CameraActor.h"
#include "Actors/Skybox.h"
#include "Components/StaticMeshComponent.h"

int InitMain();
void Shutdown(GLFWwindow* _window);

#include "Editor/Engine.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Logger::Reset();
	system("cls");
}

int main()
{
	// Initialisation de GLFW
	if (!glfwInit())
	{
		std::cerr << "Échec de l'initialisation de GLFW !" << std::endl;
		return -1;
	}

	// Créer une fenêtre GLFW
	GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Test", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Échec de la création de la fenêtre GLFW !" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Activer la synchronisation verticale

	// Initialisation d'OpenGL (si vous ne l'avez pas déjà)
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Échec de l'initialisation de GLEW !" << std::endl;
		return -1;
	}

	// Initialisation d'ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// Initialisation d'ImGui avec GLFW et OpenGL
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	bool show_demo_window = true;

	// Boucle principale
	while (!glfwWindowShouldClose(window))
	{
		// Gérer les événements
		glfwPollEvents();

		// Démarrer une nouvelle frame d'ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Affichage de la fenêtre de démo d'ImGui
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// Rendu des éléments ImGui
		ImGui::Render();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Dessiner avec OpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Échanger les buffers pour afficher à l'écran
		glfwSwapBuffers(window);
	}

	// Nettoyage avant de quitter
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

/*
int main()
{

	return EXIT_SUCCESS;

	if (InitMain())return -1;

	InitConfig();

	Engine _engine;
	_engine.Run();

	return EXIT_SUCCESS;
}
*/
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
	//rea::PhysicsCommon physicsCommon;

	//// Create a physics world
	//rea::PhysicsWorld* world = physicsCommon.createPhysicsWorld();

	//// Create a rigid body in the world
	//rea::Vector3 position(0, 20, 0);
	//rea::Quaternion orientation = rea::Quaternion::identity();
	//rea::Transform transform(position, orientation);
	//rea::RigidBody* body = world->createRigidBody(transform);

	//const rea::decimal timeStep = 1.0f / 60.0f;

	// Step the simulation a few steps
	//for (int i = 0; i < 20; i++)
	//{
	//	world->update(timeStep);

	//	// Get the updated position of the body
	//	const rea::Transform& transform = body->getTransform();
	//	const rea::Vector3& position = transform.getPosition();

	//	// Display the position of the body
	//	cout << "Body Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << endl;
	//}

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

void Shutdown(GLFWwindow* _window)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}