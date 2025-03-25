#include "HierarchyWidget.h"

#include "UIManager.h"
#include "../Editor/World.h"

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
	const unsigned int& _amount = static_cast<const unsigned int>(_allActors.size());
	for (unsigned int _index = 0; _index < _amount; _index++)
	{
		BeginDisabled(selectedActorIndex == _index);
		const string& _text = to_string(_index) + " -> " + typeid(_allActors[_index]).name(); // TODO change to name
		if (Button(_text.c_str()))
		{
			selectedActorIndex = _index;
			onActorSelected.Invoke(_allActors[_index]);
		}
		EndDisabled();
	}
}

