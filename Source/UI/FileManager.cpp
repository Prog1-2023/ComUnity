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
