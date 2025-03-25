#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"

class ContentWidget : public Widget
{
	string currentPath;
	vector<string> elements;
	char* newFolderName;
	char* newClassName;
	
public:
	FORCEINLINE string GetProjectSources() const { return GetAbsolutePath() + "\\Sources"; }
	FORCEINLINE string GetProjectContent() const { return GetAbsolutePath() + "\\Content"; }

public:
	ContentWidget(const bool& _openedByDefault);
	virtual ~ContentWidget();

private:
	void UpdateElements();
	void Open(const string& _fileName);
	void GoBack();
	void CreateFolder();
	void CreateClass();
	void ImportFile();
	void WriteToFile(const string& _fileName, const string& _content);

public:
	void Draw() override;
};


#pragma once

#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"

class NAME : public Actor
{

public:
	NAME();
	~NAME();

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(const float _deltatime) override;
};

