#include "ContentWidget.h"

#include "FileManager.h"

ContentWidget::ContentWidget(const bool& _openedByDefault) : Widget("Content", _openedByDefault)
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
	cout << "Refresh content panel!" << endl;
}

void ContentWidget::Open(const string& _fileName)
{
	const string& _path = currentPath + "/" + _fileName;
	if (is_directory(FileManager::GetContentPath() + _path))
	{
		currentPath = _path;
		UpdateElements();
	}
	else
	{
		system((FileManager::GetContentPath() + _path).c_str());
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
	SetNextWindowSize(ImVec2(200.0f, 80.0f));
	if (BeginPopupModal("Create Folder", nullptr, ImGuiWindowFlags_NoResize))
	{
		Text("Name");
		SameLine();
		InputText("##", popupEnterName, maxNameLength);
		if (Button("Cancel", ImVec2(60.0f, 20.0f)))
		{
			openCreateFolder = false;
			CloseCurrentPopup();
		}
		SameLine(GetWindowWidth() - 30.0f - 40.0f);
		if (Button("Confirm", ImVec2(60.0f, 20.0f)))
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
	SetNextWindowSize(ImVec2(200.0f, 80.0f));
	if (BeginPopupModal("Create Class", nullptr, ImGuiWindowFlags_NoResize))
	{
		Text("Name");
		SameLine();
		InputText("##", popupEnterName, maxNameLength);
		if (Button("Cancel", ImVec2(60.0f, 20.0f)))
		{
			openCreateClass = false;
			CloseCurrentPopup();
		}
		SameLine(GetWindowWidth() - 30.0f - 40.0f);
		if (Button("Confirm", ImVec2(60.0f, 20.0f)))
		{
			openCreateClass = false;
			CloseCurrentPopup();
			const string& _className = string(popupEnterName);
			const string& _templatePath = FileManager::GetSourcePath() + "/UI/Templates/";
			const string& _contentPath = FileManager::GetContentPath() + "/" + currentPath + "/";
			const string& _headerFilePath = _contentPath + _className + ".h";
			const string& _cppFilePath = _contentPath + _className + ".cpp";
			FileManager::CopyFile(_templatePath + "class.htemplate", _headerFilePath);
			FileManager::CopyFile(_templatePath + "class.cpptemplate", _cppFilePath);
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
	const string& _path = FileManager::GetContentPath() + currentPath + "/" + _fileName;

	if (FileManager::DoesFileExist(_path)) FileManager::DeleteFile(_path);
	else if (FileManager::DoesFolderExist(_path)) FileManager::DeleteFolder(_path);
	UpdateElements();
}

void ContentWidget::RenameFile()
{
	if (BeginPopupModal("Rename File", nullptr))
	{
		InputText("New Name", popupEnterName, 30);
		if (Button("Cancel"))
		{
			openRename = false;
			CloseCurrentPopup();
		}
		SameLine();
		if (Button("Confirm"))
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

	BeginDisabled(currentPath.empty());
	if (Button(" < "))
		GoBack();
	EndDisabled();
	SameLine();
	if (Button("Import"))
		openImportFile = true;
	SameLine();
	if (Button("Create Folder"))
	{
		ResetInput();
		openCreateFolder = true;
	}
	SameLine();
	if (Button("Create Class"))
	{
		ResetInput();
		openCreateClass = true;
	}
	SameLine();
	if (Button("Refresh"))
		UpdateElements();

	if (BeginPopupContextWindow("ContentRCC"))
	{
		if (MenuItem("Import File"))
			openImportFile = true;
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

	Separator();
	Text(("Content" + currentPath).c_str());
	Separator();

	const string& _basePath = FileManager::GetContentPath() + currentPath + "/";
	for (unsigned int _index = 0; _index < elements.size(); _index++)
	{
		const string& _path = _basePath + elements[_index];
		Image((is_directory(_path) ? folderTexture.textureID : fileTexture.textureID), ImVec2(25.0f, 25.0f));
		SameLine(0.0f, 0.0f);
		if (Button(elements[_index].c_str()))
			Open(elements[_index]);
		if (_index >= elements.size())
			return;
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

