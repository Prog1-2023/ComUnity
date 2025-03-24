#include "UIManager.h"

#include "../Utils/CoreMinimal.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Init(GLFWwindow* _window)
{
	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO& _io = GetIO();
	_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UIManager::StartLoop()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	NewFrame();
}

void UIManager::EndLoop()
{
	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

void UIManager::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	DestroyContext();
}