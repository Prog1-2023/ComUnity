#include "Toolbar.h"

#include "UIManager.h"

Toolbar::Toolbar()
{
	allToggleablePanels = vector<string>();

	allToggleablePanels.push_back("Console");
	allToggleablePanels.push_back("Content");
	allToggleablePanels.push_back("Hierarchy");
	allToggleablePanels.push_back("Scene");
	allToggleablePanels.push_back("Inspector");
	allToggleablePanels.push_back("Project settings");
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
				cout << "Open Project" << endl;
			if (MenuItem("New Project"))
				cout << "New Project" << endl;
			if (MenuItem("Save all"))
				cout << "Save all" << endl;
			if (MenuItem("Close"))
				glfwSetWindowShouldClose(UIManager::GetInstance().GetWindow(), true);
			EndMenu();
		}

		const unsigned int& _amount = static_cast<const unsigned int>(allToggleablePanels.size());
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
