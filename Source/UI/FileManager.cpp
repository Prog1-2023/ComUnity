#include "FileManager.h"

#include <filesystem>
#include <fstream>
#include "Log.h"

void FileManager::Delete(const string& _path)
{
	remove_all(_path);
}

void FileManager::CreateFolder(const string& _path, const string& _folderName)
{
	create_directory(_path + "/" + _folderName);
}

void FileManager::DeleteFolder(const string& _path)
{
	Delete(_path);
}

void FileManager::CreateFile(const string& _path, const string& _fileName, const string& _data)
{
	ofstream _stream = ofstream(_path + "/" + _fileName);
	_stream << _data;
	_stream.close();
}

void FileManager::DeleteFile(const string& _path)
{
	Delete(_path);
}

void FileManager::CopyFile(const string& _fileToCopy, const string& _copyLocation)
{
	copy(_fileToCopy, _copyLocation);
}

string FileManager::GetProjectPath()
{
	const path& _path = current_path();

	const path::iterator& _it = find(_path.begin(), _path.end(), "ComUnity");
	if (_it != _path.end())
	{
		path _fixedPath;
		for (path::iterator _pathPart = _path.begin(); _pathPart != _it; ++_pathPart)
			_fixedPath /= *_pathPart;
		_fixedPath /= "ComUnity";

		return _fixedPath.string();
	}

	LOG_WARNING("The 'ComUnity' folder was not found in the current path.");
	return "";
}

string FileManager::GetContentPath()
{
	return GetProjectPath() + "/" + "Content";
}

string FileManager::GetSourcePath()
{
	return GetProjectPath() + "/" + "Source";
}

string FileManager::GetBinariesPath()
{
	return GetProjectPath() + "/" + "Binaries";
}

bool FileManager::DoesFolderExist(const string& _path)
{
	return exists(_path);
}

bool FileManager::DoesFileExist(const string& _path)
{
	return exists(_path);
}

int FileManager::ReplaceFileContent(const string& _path, const string& _toReplace, const string& _replaceWith)
{
	ifstream _inStream = ifstream(_path);
	stringstream _buffer;
	_buffer << _inStream.rdbuf();
	string _content = _buffer.str();
	_inStream.close();

	int _amountReplaced = 0;
	size_t _position = _content.find(_toReplace);
	while (_position != string::npos)
	{
		_content.replace(_position, _toReplace.size(), _replaceWith);
		_position = _content.find(_toReplace);
		_amountReplaced++;
	}

	ofstream _outStream = ofstream(_path);
	_outStream << _content;
	_outStream.close();

	return 0;
}

SaveData::SaveData(const string& _saveName)
{
	saveName = _saveName;
	Load();
}

SaveData::~SaveData()
{
	Save();
}

bool SaveData::DoesKeyExist(const string& _key)
{
	return data.contains(_key);
}

void SaveData::Load()
{
	const string& _path = FileManager::GetContentPath() + "/Saves/" + saveName + ".ComUnitySave";
	ifstream _streamIn = ifstream(_path);
	string _line;

	while (getline(_streamIn, _line))
	{
		size_t _start = 0;
		size_t _end = 0;
		string _key = "";
		string _value = "";
		_end = _line.find(": ", _start);
		_key = _line.substr(_start, _end - _start);
		_value = _line.substr(_end - _start + 2, _line.length());
		cout << "Key: " << _key << " | Value: " << _value << endl;
		SetData(_key.c_str(), _value.c_str());
	}
	_streamIn.close();
}

void SaveData::Save()
{
	if (saveName.empty())
		return;
	if (data.size() == 0)
		return;

	const string& _path = FileManager::GetContentPath() + "/Saves/" + saveName + ".ComUnitySave";
	ofstream _streamOut = ofstream(_path);

	for (const pair<string, string>& _pair : data)
		_streamOut << _pair.first << ": " << _pair.second << endl;

	_streamOut.close();
}

int SaveData::GetInt(const string& _id)
{
	if (!DoesKeyExist(_id))
	{
		LOG_ERROR("Error: Save key not found! " + _id);
		return -1;
	}
	return stoi(data[_id]);
}

string SaveData::GetString(const string& _id)
{
	if (!DoesKeyExist(_id))
	{
		LOG_ERROR("Error: Save key not found! " + _id);
		return "";
	}
	return data[_id];
}

float SaveData::GetFloat(const string& _id)
{
	if (!DoesKeyExist(_id))
	{
		LOG_ERROR("Error: Save key not found! " + _id);
		return -1.0f;
	}
	return stof(data[_id]);
}

bool SaveData::GetBool(const string& _key)
{
	if (!DoesKeyExist(_key))
	{
		LOG_ERROR("Error: Save key not found! " + _key);
		return -1.0f;
	}
	return (bool)stoi(data[_key]);
}

void SaveData::SetData(const string& _id, const string& _value)
{
	data[_id] = _value;
}
