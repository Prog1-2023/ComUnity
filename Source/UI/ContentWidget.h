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
	ContentWidget(const bool& _openedByDefault);
	virtual ~ContentWidget();

private:
	void UpdateElements();
	void Open(const string& _fileName);
	void GoBack();
	void CreateFolder();
	void CreateClass();
	void ImportFile();

public:
	void Draw() override;
};
