#pragma once

#include "../Utils/CoreMinimal.h"
#include "Singleton.h"

class FileManager : public Singleton<FileManager>
{

private:
	static void Delete(const string& _path);

public:
	static void CreateFolder(const string& _path, const string& _folderName);
	static void DeleteFolder(const string& _path);
	static void CreateFile(const string& _path, const string& _fileName, const string& _data = "");
	static void DeleteFile(const string& _path);
	static void CopyFile(const string& _fileToCopy, const string& _copyLocation);
	static string GetProjectPath();
	static string GetContentPath();
	static string GetSourcePath();
	static string GetBinariesPath();
	static bool DoesFolderExist(const string& _path);
	static bool DoesFileExist(const string& _path);
	static int ReplaceFileContent(const string& _path, const string& _toReplace, const string& _replaceWith);
};