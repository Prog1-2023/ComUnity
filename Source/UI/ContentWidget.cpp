#include "ContentWidget.h"

#include "FileManager.h"

ContentWidget::ContentWidget(const bool& _openedByDefault) : Widget("Content", _openedByDefault)
{
	currentPath = "";
	elements = vector<string>();
	newFolderName = new char;
	newClassName = new char;
	UpdateElements();
}

ContentWidget::~ContentWidget()
{
	delete[] newFolderName;
	delete[] newClassName;
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
	const string& _path = currentPath + "/" + _fileName;
	if (is_directory(FileManager::GetContentPath() + _path))
	{
		currentPath = _path;
		UpdateElements();
	}
	else
	{
		const string& _filePath = FileManager::GetContentPath() + _path;
		system(_filePath.c_str());
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
	if (BeginPopupModal("Create Folder"))
	{
		InputText("Name", newFolderName, 20);
		if (Button("Cancel"))
			CloseCurrentPopup();
		SameLine();
		if (Button("Confirm"))
		{
			CloseCurrentPopup();
			FileManager::CreateFolder(FileManager::GetContentPath() + "/" + currentPath, newFolderName);
			UpdateElements();
		}
		EndPopup();
	}
}

void ContentWidget::CreateClass()
{
	if (BeginPopupModal("Create Class"))
	{
		InputText("Name", newClassName, 30);
		if (Button("Cancel"))
			CloseCurrentPopup();
		SameLine();
		if (Button("Confirm"))
		{
			CloseCurrentPopup();
			const string& _classNameString = string(newClassName);
			const string& _templatePath = FileManager::GetSourcePath() + "/UI/Templates/";
			const string& _contentPath = FileManager::GetContentPath() + "/" + currentPath + "/";
			const string& _headerFilePath = _contentPath + _classNameString + ".h";
			const string& _cppFilePath = _contentPath + _classNameString + ".cpp";
			FileManager::CopyFile(_templatePath + "class.h", _headerFilePath);
			FileManager::CopyFile(_templatePath + "class.cpp", _cppFilePath);
			FileManager::ReplaceFileContent(_headerFilePath, "[NAME]", _classNameString);
			FileManager::ReplaceFileContent(_cppFilePath, "[NAME]", _classNameString);
			UpdateElements();
		}
		EndPopup();
	}
}

void ContentWidget::ImportFile()
{
	if (BeginPopupModal("Import File"))
	{
		Text("test popup");
		EndPopup();
	}
}

void ContentWidget::Draw()
{
	BeginDisabled(currentPath.empty());
	if (Button(" < "))
		GoBack();
	EndDisabled();
	SameLine();
	if (Button("Import"))
		OpenPopup("Import File");
	SameLine();
	if (Button("Create Folder"))
		OpenPopup("Create Folder");
	SameLine();
	if (Button("Create Class"))
		OpenPopup("Create Class");

	CreateFolder();
	CreateClass();
	ImportFile();

	Separator();
	Text(("Content" + currentPath).c_str());
	Separator();

	for (unsigned int _index = 0; _index < elements.size(); _index++)
	{
		if (Button(elements[_index].c_str()))
			Open(elements[_index]);
	}
}

