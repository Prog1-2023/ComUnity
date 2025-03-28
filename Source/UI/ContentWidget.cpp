#include "ContentWidget.h"

#include "FileManager.h"
#include "Log.h"

ContentWidget::ContentWidget(const bool& _openedByDefault) : Widget("Content", _openedByDefault), newClassTypes{ "empty", "actor", "component" }
{
	currentPath = "";
	fileToRename = "";
	elements = vector<string>();
	openRename = false;
	openCreateFolder = false;
	openCreateClass = false;
	openImportFile = false;
	maxNameLength = 30;
	popupEnterName = new char[30] { "" };
	UpdateElements();
	time = glfwGetTime();

	selectedClassType = 0;

	const string& _contentPath = FileManager::GetContentPath();
	TextureManager::GetInstance().LoadTexture(_contentPath + "/EditorIcons/Folder.png", folderTexture);
	TextureManager::GetInstance().LoadTexture(_contentPath + "/EditorIcons/File.png", fileTexture);
}

ContentWidget::~ContentWidget()
{
	delete[] popupEnterName;
}

void ContentWidget::UpdateElements()
{
	elements.clear();
	const string& _path = FileManager::GetContentPath() + "/" + currentPath;
	for (const directory_entry& _iterator : directory_iterator(_path))
		elements.push_back(_iterator.path().filename().string());
}

void ContentWidget::Open(const string& _fileName)
{
	const string& _path = FileManager::GetContentPath() + (currentPath.empty() ? "" : "/" + currentPath) + "/" + _fileName;

	if (is_directory(_path))
	{
		currentPath += (currentPath.empty() ? "" : "/") + _fileName;
		UpdateElements();
	}
	else
	{
		system(_path.c_str());
	}
}

void ContentWidget::GoBack()
{
	const size_t& _position = currentPath.find_last_of('/');
	if (_position != string::npos)
	{
		currentPath = currentPath.substr(0, _position);
		UpdateElements();
	}
}

void ContentWidget::CreateFolder()
{
	SetNextWindowSize(ImVec2(350.0f, 150.0f));
	if (BeginPopupModal("Create Folder", nullptr, ImGuiWindowFlags_NoResize))
	{
		Text("Name");
		SameLine();
		InputText("##", popupEnterName, maxNameLength);
		if (Button("Cancel", ImVec2(100.0f, 40.0f)))
		{
			openCreateFolder = false;
			CloseCurrentPopup();
		}
		SameLine(GetWindowWidth() - 30.0f - 100.0f);
		if (Button("Confirm", ImVec2(100.0f, 40.0f)))
		{
			openCreateFolder = false;
			CloseCurrentPopup();
			const string& _path = FileManager::GetContentPath() + "/" + currentPath;
			FileManager::CreateFolder(_path, popupEnterName);
			UpdateElements();
		}
		EndPopup();
	}
}

void ContentWidget::CreateClass()
{
	SetNextWindowSize(ImVec2(350.0f, 150.0f));
	if (BeginPopupModal("Create Class", nullptr, ImGuiWindowFlags_NoResize))
	{
		Text("Name");
		SameLine();
		InputText("##name", popupEnterName, maxNameLength);
		Text("Type ");
		SameLine();
		Combo("##", &selectedClassType, newClassTypes, IM_ARRAYSIZE(newClassTypes));
		if (Button("Cancel", ImVec2(100.0f, 40.0f)))
		{
			openCreateClass = false;
			CloseCurrentPopup();
		}
		SameLine(GetWindowWidth() - 30.0f - 100.0f);
		if (Button("Confirm", ImVec2(100.0f, 40.0f)))
		{
			openCreateClass = false;
			CloseCurrentPopup();
			const string& _className = string(popupEnterName);
			const string& _templatePath = FileManager::GetSourcePath() + "/UI/Templates/";
			const string& _contentPath = FileManager::GetContentPath() + "/" + currentPath + "/";
			const string& _headerFilePath = _contentPath + _className + ".h";
			const string& _cppFilePath = _contentPath + _className + ".cpp";
			const string& _templateClassName = newClassTypes[selectedClassType];
			FileManager::CopyFile(_templatePath + _templateClassName + ".htemplate", _headerFilePath);
			FileManager::CopyFile(_templatePath + _templateClassName + ".cpptemplate", _cppFilePath);
			FileManager::ReplaceFileContent(_headerFilePath, "[NAME]", _className);
			FileManager::ReplaceFileContent(_cppFilePath, "[NAME]", _className);
			UpdateElements();
		}
		EndPopup();
	}
}

void ContentWidget::ImportFile()
{
	SetNextWindowSize(ImVec2(200.0f, 80.0f));
	if (BeginPopupModal("Import File", nullptr, ImGuiWindowFlags_NoResize))
	{
		if (Button("Cancel", ImVec2(60.0f, 20.0f)))
		{
			openImportFile = false;
			CloseCurrentPopup();
		}
		EndPopup();
	}
}


void ContentWidget::DeleteFile(const string& _fileName)
{
	const string& _path = FileManager::GetContentPath() + (currentPath.empty() ? "" : "/" + currentPath) + "/" + _fileName;

	if (FileManager::DoesFileExist(_path)) {
		FileManager::DeleteFile(_path);
	}
	else if (FileManager::DoesFolderExist(_path)) {
		FileManager::DeleteFolder(_path);
	}

	UpdateElements();
}

void ContentWidget::RenameFile()
{
	SetNextWindowSize(ImVec2(350.0f, 150.0f));
	if (BeginPopupModal("Rename File", nullptr, ImGuiWindowFlags_NoResize))
	{
		Text("New Name");
		SameLine();
		InputText("##name", popupEnterName, maxNameLength);
		if (Button("Cancel", ImVec2(100.0f, 40.0f)))
		{
			openRename = false;
			CloseCurrentPopup();
		}
		SameLine(GetWindowWidth() - 30.0f - 100.0f);
		if (Button("Confirm", ImVec2(100.0f, 40.0f)))
		{
			openRename = false;
			CloseCurrentPopup();
			const string& _oldFile = FileManager::GetContentPath() + "/" + currentPath + "/" + fileToRename;
			const string& _test = string(popupEnterName);
			const string& _newFile = FileManager::GetContentPath() + "/" + currentPath + "/" + _test;
			FileManager::CopyFile(_oldFile, _newFile);
			FileManager::DeleteFile(_oldFile);
			UpdateElements();
		}
		EndPopup();
	}
}

void ContentWidget::ResetInput(const string& _newInput)
{
	const unsigned int& _newInputSize = static_cast<const unsigned int>(_newInput.length());
	for (unsigned int _index = 0; _index < maxNameLength - 1; _index++)
		popupEnterName[_index] = (_index >= _newInputSize ? (char)0 : _newInput[_index]);
}

void ContentWidget::Draw()
{
	if (openRename)
	{
		OpenPopup("Rename File");
		RenameFile();
	}
	if (openCreateFolder)
	{
		OpenPopup("Create Folder");
		CreateFolder();
	}
	if (openCreateClass)
	{
		OpenPopup("Create Class");
		CreateClass();
	}
	if (openImportFile)
	{
		OpenPopup("Import File");
		ImportFile();
	}

	if (glfwGetTime() - time >= 3.0)
	{
		time = glfwGetTime();
		UpdateElements();
	}

	BeginDisabled(currentPath.empty());
	EndDisabled();
	//if (Button("Import##ImportFile"))
	//	openImportFile = true;
	SameLine();
	if (Button("Create Folder##CreateFolder"))
	{
		ResetInput("");
		openCreateFolder = true;
	}
	SameLine();
	if (Button("Create Class##CreateClass"))
	{
		ResetInput("");
		openCreateClass = true;
	}
	SameLine();
	if (Button("Refresh##Refresh"))
		UpdateElements();

	Separator();

	vector<string> _pathSegments;
	string _tempPath = "";
	stringstream _ss(currentPath);
	string _segment;

	while (getline(_ss, _segment, '/'))
		_pathSegments.push_back(_segment);

	if (Button("Content##ContentRoot"))
	{
		currentPath = "";
		UpdateElements();
	}
	SameLine();
	Text("/");

	for (size_t _index = 0; _index < _pathSegments.size(); _index++)
	{
		if (_pathSegments[_index].empty())
			continue;
		if (!_tempPath.empty())
			_tempPath += "/";
		_tempPath += _pathSegments[_index];

		SameLine();
		if (Button((_pathSegments[_index] + "##PathButton" + to_string(_index)).c_str()))
		{
			currentPath = _tempPath;
			UpdateElements();
		}

		if (_index < _pathSegments.size() - 1)
		{
			SameLine();
			Text("/");
		}
	}

	Separator();

	BeginChild("ContentScrollArea", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	if (BeginPopupContextWindow("ContentRCC"))
	{
		//if (MenuItem("Import File"))
		//	openImportFile = true;
		if (MenuItem("Create Folder"))
		{
			ResetInput();
			openCreateFolder = true;
		}
		if (MenuItem("Create Class"))
		{
			ResetInput();
			openCreateClass = true;
		}
		if (MenuItem("Refresh"))
			UpdateElements();
		EndPopup();
	}

	const string& _basePath = FileManager::GetContentPath() + "/" + currentPath + "/";
	for (unsigned int _index = 0; _index < elements.size(); _index++)
	{
		const string& _path = _basePath + elements[_index];
		Image((is_directory(_path) ? folderTexture.textureID : fileTexture.textureID), ImVec2(25.0f, 25.0f));
		SameLine(0.0f, 0.0f);
		if (Button(elements[_index].c_str()))
			Open(elements[_index]);

		if (_index < elements.size())
		{
			if (BeginPopupContextItem((elements[_index] + "RCC").c_str()))
			{
				if (MenuItem("Open"))
					Open(elements[_index]);
				if (MenuItem("Rename"))
				{
					fileToRename = elements[_index];
					ResetInput(fileToRename);
					openRename = true;
				}
				if (MenuItem("Delete"))
					DeleteFile(elements[_index]);
				EndPopup();
			}
		}
	}

	EndChild();
}

