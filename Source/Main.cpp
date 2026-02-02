#include <iostream>
#include <vector>

// FMT
#include <fmt/core.h>

// ImGui
//#include <imgui.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// ReactPhysics3D
//#include <reactphysics3d/reactphysics3d.h>

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
//#include "Editor/World.h"
#include "NewLightRelated/Material.h"
#include "Actors/Cameras/CameraActor.h"
#include "Actors/Skybox.h"
#include "Components/StaticMeshComponent.h"

#include"Manager/SoundManager.h"
#include"Actors/SoundActor.h"

using namespace std;
using namespace Assimp;
using namespace fmt;
using namespace irrklang;
//namespace rea = reactphysics3d;

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
	//ISoundEngine* _soundEngine = createIrrKlangDevice();
	//
	////SoundManager::GetInstance().GetSoundEngine()->play3D("../Content/Sound/sonic-unleashed-ost.mp3", vec3df(0.0f, 0.0f, 5.0f), true, false, true, E_STREAM_MODE::ESM_AUTO_DETECT, true);
	//SoundInfo _soundInfo = SoundInfo(true, Vector3f(0.0f, 0.0f, 5.0f), true, 1.0f, 1.0f, true, false, true);
	//SoundActor _sound = SoundActor(nullptr,"../Content/Sound/sonic-unleashed-ost.mp3", _soundInfo);
	//_sound.Construct();
	//_sound.BeginPlay();
	//int _index = 0;
	//while (_index >= 0 || _index <= 120000)
	//{
	//	_index++;

	//	cout << _index << endl;
	//}
	//return 0;


	if (InitMain())return -1;

	InitConfig();

	Engine _engine;
	_engine.Run();

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
	/*ISoundEngine* soundEngine = createIrrKlangDevice();
	if (soundEngine)
	{
		cout << "IrrKlang initialisé avec succès !\n";
		soundEngine->drop();
	}
	else
	{
		cout << "Erreur d'initialisation d'IrrKlang.\n";
	}*/

	return EXIT_SUCCESS;
}

void Shutdown(GLFWwindow* _window)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}
