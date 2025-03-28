#include "HierarchyWidget.h"

#include "UIManager.h"
#include "../Editor/World.h"
#include "UIMacros.h"

HierarchyWidget::HierarchyWidget(const bool& _openedByDefault) : Widget("Hierarchy", _openedByDefault)
{
	selectedActorIndex = -1;
}

void HierarchyWidget::Draw()
{
	World* _world = UIManager::GetInstance().GetWorld();
	if (!_world)
	{
		Separator();
		TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "World not found!");
		Separator();
		return;
	}
	vector<Actor*> _allActors = _world->GetAllActors();

	FOREACH(_amount, _allActors.size())
	{
		BeginDisabled(selectedActorIndex == _index);
		const string& _actorName = typeid(_allActors[_index]).name(); // TODO change to name
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
				onActorDeleteAction.Invoke(_allActors[_index]);
			EndPopup();
		}
	}
}

