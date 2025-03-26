#include "SpawnActorWidget.h"

#include "UIManager.h"
#include "SceneWidget.h"

SpawnActorWidget::SpawnActorWidget(const bool& _openedByDefault) : Widget("Spawn Actors", _openedByDefault)
{
	tabList = unordered_map<string, SpawnActorTab>();

	SpawnActorTab _meshTab = SpawnActorTab();
	SpawnActorTab _lightTab = SpawnActorTab();

	_meshTab.actorList["Cube"].Add([&]() { cout << "Cube" << endl;});
	_meshTab.actorList["Sphere"].Add([&]() { cout << "Sphere" << endl;});
	_meshTab.actorList["Cylinder"].Add([&]() { cout << "Cylinder" << endl;});
	_meshTab.actorList["Cone"].Add([&]() { cout << "Cone" << endl;});

	_lightTab.actorList["Point Light"].Add([&]() { cout << "Point Light" << endl;});
	_lightTab.actorList["Spot Light"].Add([&]() { cout << "Spot Light" << endl;});
	_lightTab.actorList["Directional Light"].Add([&]() { cout << "Directional Light" << endl;});

	tabList["Meshes"] = _meshTab;
	tabList["Lights"] = _lightTab;
	currentOpenedTab = "Meshes";

	SceneWidget* _sceneWidget = UIManager::GetInstance().GetWidgetOfType<SceneWidget>();
	if (_sceneWidget)
		_sceneWidget->OnDroppedElement().Add([this](const string& _id) { ExecuteEvent(_id); });
}

void SpawnActorWidget::ExecuteEvent(const string& _id)
{
	tabList[currentOpenedTab].actorList[_id].Invoke();
}

void SpawnActorWidget::Draw()
{
	// TODO opti?
	for (const pair<string, SpawnActorTab>& _pair : tabList)
	{
		SameLine();
		BeginDisabled(currentOpenedTab == _pair.first);
		if (Button(_pair.first.c_str()))
			currentOpenedTab = _pair.first;
		EndDisabled();
	}

	Separator();
	for (const pair<string, Event<>>& _pair : tabList[currentOpenedTab].actorList)
	{
		Image(0, ImVec2(50.0f, 50.0f));
		SameLine(0.0f, 0.0f);
		Selectable(_pair.first.c_str());
		if (BeginDragDropSource())
		{
			SetDragDropPayload("SPAWN_ACTOR", &(_pair.first), sizeof(string));
			Text(_pair.first.c_str());
			EndDragDropSource();
		}
	}
}
