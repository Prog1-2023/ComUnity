#include "HierarchyWidget.h"

#include "UIManager.h"
#include "../Editor/World.h"
#include "UIMacros.h"
#include "../Manager/LevelManager.h"
#include "Log.h"

HierarchyWidget::HierarchyWidget(const bool& _openedByDefault) : Widget("Hierarchy", _openedByDefault)
{
	selectedActorIndex = -1;
	onActorDeleteAction = Event<void, Actor*>();
}

void HierarchyWidget::Draw()
{
	//Level* _level =	LevelManager::GetInstance().GetCurrentLevel();
	Level* _level = UIManager::GetInstance().GetLevel();

	if (!_level)
	{
		Separator();
		TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Level not found!");
		Separator();
		return;
	}
	vector<Actor*> _allActors = _level->GetActorManager().GetAllActors().GetVector();

	FOREACH(_amount, _allActors.size())
	{
		BeginDisabled(selectedActorIndex == _index);
		const string& _actorName = _allActors[_index]->GetDisplayName();
		const string& _text = to_string(_index) + " -> " + _actorName;

		if (Button(_text.c_str()))
		{
			selectedActorIndex = _index;
			onActorSelected.Invoke(_allActors[_index]);
		}
		EndDisabled();

		if (BeginPopupContextItem((to_string(_index) + _actorName + "RCC").c_str()))
		{
			if (MenuItem("Delete"))
			{
				LOG("Deleted : " + _allActors[_index]->GetDisplayName());
				onActorDeleteAction.Invoke(_allActors[_index]);
			}
			EndPopup();
		}
	}
}

