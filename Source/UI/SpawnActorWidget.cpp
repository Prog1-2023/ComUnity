#include "SpawnActorWidget.h"

#include "UIManager.h"
#include "SceneWidget.h"
#include "Log.h"

SpawnActorWidget::SpawnActorWidget(const bool& _openedByDefault) : Widget("Spawn Actors", _openedByDefault)
{
	tabList = unordered_map<string, SpawnActorTab>();

	SpawnActorTab _meshTab = SpawnActorTab();
	SpawnActorTab _lightTab = SpawnActorTab();

	_meshTab.actorList["Cube"].Add([&]() { LOG("Cube"); });
	_meshTab.actorList["Sphere"].Add([&]() { LOG("Sphere"); });
	_meshTab.actorList["Cylinder"].Add([&]() { LOG("Cylinder");});
	_meshTab.actorList["Cone"].Add([&]() { LOG("Cone");});

	_lightTab.actorList["Point Light"].Add([&]() { LOG("Point Light"); });
	_lightTab.actorList["Spot Light"].Add([&]() { LOG("Spot Light");});
	_lightTab.actorList["Directional Light"].Add([&]() { LOG("Directional Light");});

	tabList["Meshes"] = _meshTab;
	tabList["Lights"] = _lightTab;
	currentOpenedTab = "Meshes";

	SceneWidget* _sceneWidget = UIManager::GetInstance().GetWidgetOfType<SceneWidget>();
	if (_sceneWidget)
		_sceneWidget->OnDroppedElement().Add([this](const int& _id) { ExecuteEvent(_id); });
}

void SpawnActorWidget::ExecuteEvent(const int& _id)
{
	const unsigned int& _meshesAmount = tabList["Meshes"].actorList.size();
	const string& _actorType = (_id < _meshesAmount ? "Meshes" : "Lights");
	unsigned int _currentIndex = _actorType == "Lights" ? _meshesAmount : 0;
	for (const pair<string, SpawnActor>& _pair : tabList[_actorType].actorList)
	{
		if (_currentIndex == _id)
		{
			_pair.second.callback.Invoke();
			break;
		}
		_currentIndex++;
	}
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
	int _index = currentOpenedTab == "Lights" ? tabList["Meshes"].actorList.size() : 0;
	for (const pair<string, SpawnActor>& _pair : tabList[currentOpenedTab].actorList)
	{
		Image(_pair.second.texture.textureID, ImVec2(50.0f, 50.0f));
		SameLine(0.0f, 0.0f);
		Selectable(_pair.first.c_str());
		if (BeginDragDropSource())
		{
			SetDragDropPayload("SPAWN_ACTOR", &_index, sizeof(int));
			Text(_pair.first.c_str());
			EndDragDropSource();
		}
		_index++;
	}
}
