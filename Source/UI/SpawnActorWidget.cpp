#include "SpawnActorWidget.h"

#include "UIImage.h"

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
		if (Button(_pair.first.c_str()))
			_pair.second.Invoke();
	}
}

