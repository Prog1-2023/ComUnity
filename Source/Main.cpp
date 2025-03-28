#include <iostream>

// FMT
#include <fmt/core.h>

// ImGui
#include <imgui.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// IrrKlang
#include <irrKlang.h>

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace Assimp;
using namespace fmt;
using namespace irrklang;

enum Category
{
	Category1 = 0x0001,
	Category2 = 0x0002,
	Category3 = 0x0003,
	Category4 = 0x0004,
	Category5 = 0x0005,
	Category6 = 0x0006,
	Category7 = 0x0007,
	Category8 = 0x0010,
	Category9 = 0x0011,
	Category10 = 0x0012,
	Category11 = 0x0013,
	Category12 = 0x0014,
	Category13 = 0x0015,
	Category14 = 0x0016,
	Category15 = 0x0017,
	Category16 = 0x0020,
	Category17 = 0x0021,
	Category18 = 0x0022,
	Category19 = 0x0023,
	Category20 = 0x0024,
	Category21 = 0x0025,
	Category22 = 0x0026,
	Category23 = 0x0027,
	Category24 = 0x0030,
	Category25 = 0x0031,
	Category26 = 0x0032,
	Category27 = 0x0033,
	Category28 = 0x0034,
	Category29 = 0x0035,
	Category30 = 0x0037,
	Category31 = 0x0040,
	Category32 = 0x0041,
};
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