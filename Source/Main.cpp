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

using namespace std;
using namespace Assimp;
using namespace fmt;
using namespace reactphysics3d;
using namespace irrklang;

#pragma region MyRegion


struct VarMetaData;

struct ClassMetaData
{
	const char* className;
	vector<VarMetaData> allVarsMetaData;

public:
	ClassMetaData(const char* _className)
	{
		className = _className;
	}

	void RegisterVarMetaData(const VarMetaData& _varMetaData)
	{
		allVarsMetaData.push_back(_varMetaData);
	}
};

struct VarMetaData
{

};

class TestClass;

#define SETUP_VAR(Type, Var) \
private: \
    Type Var; \
public: \
    void Set##Var(const Type& _value) { Var = _value; } \
    Type Get##Var() { return Var; } \
	Type* Get##Var##Type() \
	{ \
		const size_t& _hasValue = typeid(Var).hash_code(); \
		return reinterpret_cast<Type*>(_hasValue); \
	} \
	const char* Get##Var##TypeName() { return #Type; }

#define GENERATED_BODY(Class) \
	SETUP_VAR(Class, MetaData)

#define UPROPERTY(Type, Var) \
	SETUP_VAR(Type, Var)

using namespace std;

struct Coucou
{

};

class TestClass
{
	//GENERATED_BODY(TestClass)

	UPROPERTY(Coucou, Value)

public:
	TestClass() {}

	void Test()
	{
		//SetMetaData(GetMetaDataTestClass());

		/*SetValue(12);
		cout << Value << endl;
		cout << GetValue() << endl;
		cout << GetValueType() << endl;
		cout << GetValueTypeName() << endl;
		cout << typeid(Value).name() << endl;*/
	}
};

#pragma endregion

int main()
{
	cout << "ComUnity : l'Engine des Communistes !" << endl;

	TestClass _test = TestClass();
	_test.Test();

	return EXIT_SUCCESS;

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

	// GLM
	glm::vec3 positionGLM(1.0f, 2.0f, 3.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec4 transformedPosition = model * glm::vec4(positionGLM, 1.0f);
	std::cout << "Transformed position: ("
		<< transformedPosition.x << ", "
		<< transformedPosition.y << ", "
		<< transformedPosition.z << ")\n";

	return EXIT_SUCCESS;
}