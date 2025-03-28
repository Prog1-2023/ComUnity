#include "UIManager.h"

#include "ConsoleWidget.h"
#include "ContentWidget.h"
#include "HierarchyWidget.h"
#include "SceneWidget.h"
#include "InspectorWidget.h"
#include "ProjectSettingsWidget.h"
#include "EditorPreferencesWidget.h"
#include "SpawnActorWidget.h"
#include "FileManager.h"
#include "GameWidget.H"

UIManager::UIManager()
{
	toolbar = Toolbar();
	allWidgets = map<string, Widget*>();
	world = nullptr;
	window = nullptr;
}

UIManager::~UIManager()
{
	for (const pair<string, Widget*>& _pair : allWidgets)
		delete _pair.second;
}

void UIManager::InitPanels()
{
	new ConsoleWidget(true);
	new ContentWidget(true);
	new HierarchyWidget(true);
	new GameWidget(true);
	new SceneWidget(true);
	new InspectorWidget(true);
	new ProjectSettingsWidget(false);
	new SpawnActorWidget(true);
	new EditorPreferencesWidget(false);
}

void UIManager::InitDockingPositions()
{
	const string& _initFile = FileManager::GetBinariesPath() + "/imgui.ini";
	if (!FileManager::DoesFileExist(_initFile))
	{
		const string& _from = FileManager::GetSourcePath() + "/UI/Templates/imgui.ini";
		const string& _to = _initFile;
		FileManager::CopyFile(_from, _initFile);
	}
}

void UIManager::Init(GLFWwindow* _window, World* _world)
{
	window = _window;
	world = _world;
	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO& _io = GetIO();
	_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	InitPanels();
	InitDockingPositions();
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

void UIManager::RegisterWidget(const string& _widgetName, Widget* _widget)
{
	allWidgets[_widgetName] = _widget;
}

void UIManager::DrawAll()
{
	toolbar.Draw();
	DockSpaceOverViewport(GetMainViewport()->ID);
	for (const pair<string, Widget*>& _pair : allWidgets)
	{
		if (_pair.second->GetIsActiveRef())
		{
			Begin(_pair.first.c_str(), &_pair.second->GetIsActiveRef());
			_pair.second->Draw();
			End();
		}
	}

}

void UIManager::OpenPanel(const string& _widgetName)
{
	if (allWidgets.contains(_widgetName))
		allWidgets[_widgetName]->SetIsActive(true);
}

void UIManager::ClosePanel(const string& _widgetName)
{
	if (allWidgets.contains(_widgetName))
		allWidgets[_widgetName]->SetIsActive(false);
}

void UIManager::TogglePanel(const string& _widgetName)
{
	if (allWidgets.contains(_widgetName))
	{
		if (allWidgets[_widgetName]->GetIsActiveRef()) allWidgets[_widgetName]->SetIsActive(false);
		else allWidgets[_widgetName]->SetIsActive(true);
	}
}
