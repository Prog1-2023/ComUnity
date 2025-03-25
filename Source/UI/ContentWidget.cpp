#include "ContentWidget.h"

#include <filesystem>
#include <fstream>

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
	const string& _path = GetProjectContent() + "/" + currentPath;
	for (const directory_entry& _iterator : directory_iterator(_path))
		elements.push_back(_iterator.path().filename().string());
}

void ContentWidget::Open(const string& _fileName)
{
	const string& _path = currentPath + "/" + _fileName;
	if (is_directory(GetProjectContent() + _path))
	{
		currentPath = _path;
		UpdateElements();
	}
	else
	{
		const string& _filePath = GetProjectContent() + _path;
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
			create_directory(GetProjectContent() + "/" + currentPath + "/" + newFolderName);
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
			// TODO move text to template files
			const string& _classNameString = string(newClassName);
			WriteToFile(_classNameString + ".h", "#pragma once\n\n#include \"../Utils/CoreMinimal.h\"\n#include \"../Actors/Actor.h\"\n\nclass " + _classNameString + " : public Actor\n{\n\npublic:\n\t" + _classNameString + "();\n\t~" + _classNameString + "();\n\t\npublic:\n\tvirtual void BeginPlay() override;\n\tvirtual void BeginDestroy() override;\n\tvirtual void Tick(const float _deltatime) override;\n };\n");
			WriteToFile(_classNameString + ".cpp", "#include \"" + _classNameString + ".h\"\n\n" + _classNameString + "::" + _classNameString + "()\n{\n\n}\n\n" + _classNameString + "::~" + _classNameString + "()\n{\n\n}\n\nvoid " + _classNameString + "::BeginPlay()\n{\n\tSuper::BeginPlay();\n}\n\nvoid " + _classNameString + "::BeginDestroy()\n{\n\tSuper::BeginDestroy();\n}\n\nvoid " + _classNameString + "::Tick(const float _deltatime)\n{\n\tSuper::Tick(_deltatime);\n}\n");
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

void ContentWidget::WriteToFile(const string& _fileName, const string& _content)
{
	ofstream _stream = ofstream(GetProjectContent() + "/" + currentPath + "/" + _fileName);
	_stream << _content;
	_stream.close();
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

