#include "Toolbar.h"

#include "UIManager.h"
#include "Log.h"
#include "UIMacros.h"

Toolbar::Toolbar()
{
	allToggleablePanels = vector<string>();

	allToggleablePanels.push_back("Console");
	allToggleablePanels.push_back("Content");
	allToggleablePanels.push_back("Hierarchy");
	allToggleablePanels.push_back("Scene");
	allToggleablePanels.push_back("Game");
	allToggleablePanels.push_back("Inspector");
	allToggleablePanels.push_back("Project Settings");
	allToggleablePanels.push_back("Editor Preferences");
	allToggleablePanels.push_back("Spawn Actors");

	isGameRunning = false;
}

void Toolbar::Draw()
{
	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("Open Project"))
				LOG("Open Project");
			if (MenuItem("New Project"))
				LOG("New Project");
			if (MenuItem("Save all"))
				LOG("Save all");
			if (MenuItem("Close"))
				glfwSetWindowShouldClose(UIManager::GetInstance().GetWindow(), true);
			EndMenu();
		}

		SIZE_CAST(_amount, allToggleablePanels.size());
		if (_amount >= 1)
		{
			if (BeginMenu("Panels"))
			{
				for (unsigned int _index = 0; _index < _amount; _index++)
				{
					const string& _panelName = allToggleablePanels[_index];
					if (MenuItem(_panelName.c_str()))
						UIManager::GetInstance().TogglePanel(_panelName);
				}
				EndMenu();
			}
		}
		Separator();
		BeginDisabled(isGameRunning);
		if (Button("Start"))
		{
			isGameRunning = true;
			onGameStatusChanged.Invoke(true);
		}
		EndDisabled();
		BeginDisabled(!isGameRunning);
		if (Button("Stop"))
		{
			isGameRunning = false;
			onGameStatusChanged.Invoke(false);
		}
		EndDisabled();
		EndMainMenuBar();
	}
}
