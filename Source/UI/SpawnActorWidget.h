#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "../Utils/Event.h"
#include "FileManager.h"
#include "TextureManager.h"

struct SpawnActor
{
	Event<> callback;
	TextureData texture;

public:
	SpawnActor()
	{

	}
	SpawnActor(const Event<>& _callback, const string& _textureName)
	{
		callback = _callback;
		TextureManager::GetInstance().LoadTexture(FileManager::GetContentPath() + "/EditorIcons/" + _textureName, texture);
	}
};

struct SpawnActorTab
{
	unordered_map<string, SpawnActor> actorList;
};

class SpawnActorWidget : public Widget
{

	unordered_map<string, SpawnActorTab> tabList;
	string currentOpenedTab;
	
public:
	SpawnActorWidget(const bool& _openedByDefault);
	virtual ~SpawnActorWidget() = default;

private:
	void ExecuteEvent(const int& _id);

public:
	void Draw() override;
};