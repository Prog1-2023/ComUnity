#pragma once

#include "../Utils/CoreMinimal.h"
#include "Widget.h"
#include "TextureManager.h"

class ContentWidget : public Widget
{
	string currentPath;
	vector<string> elements;
	char* popupEnterName;
	string fileToRename;
	bool openRename;
	bool openCreateFolder;
	bool openCreateClass;
	bool openImportFile;
	int maxNameLength;
	TextureData folderTexture;
	TextureData fileTexture;

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
	void DeleteFile(const string& _fileName);
	void RenameFile();
	void ResetInput(const string& _newInput = "");

public:
	void Draw() override;
};
