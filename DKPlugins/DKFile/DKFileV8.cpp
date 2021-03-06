#ifdef USE_DKCef
#include "DKFileV8.h"
#include "DKFile.h"
#include "DKApp.h"

/////////////////////
void DKFileV8::Init()
{
	DKLog("DKFileV8::Init()\n", DKDEBUG);
	//DKV8::AttachFunction("Test", DKFileV8::Test);
	DKV8::AttachFunction("DKFile_ChDir", DKFileV8::ChDir);
	DKV8::AttachFunction("DKFile_Copy", DKFileV8::Copy);
	DKV8::AttachFunction("DKFile_CopyFolder", DKFileV8::CopyFolder);
	DKV8::AttachFunction("DKFile_Delete", DKFileV8::Delete);
	DKV8::AttachFunction("DKFile_DirectoryContents", DKFileV8::DirectoryContents);
	DKV8::AttachFunction("DKFile_Exists", DKFileV8::Exists);
	DKV8::AttachFunction("DKFile_FileToString", DKFileV8::FileToString);
	DKV8::AttachFunction("DKFile_GetAbsolutePath", DKFileV8::GetAbsolutePath);
	DKV8::AttachFunction("DKFile_GetSetting", DKFileV8::GetSetting);
	DKV8::AttachFunction("DKFile_GetShortName", DKFileV8::GetShortName);
	DKV8::AttachFunction("DKFile_IsDirectory", DKFileV8::IsDirectory);
	DKV8::AttachFunction("DKFile_MkDir", DKFileV8::MkDir);
	DKV8::AttachFunction("DKFile_Rename", DKFileV8::Rename);
	DKV8::AttachFunction("DKFile_SetSetting", DKFileV8::SetSetting);
	DKV8::AttachFunction("DKFile_StringToFile", DKFileV8::StringToFile);
}

///////////////////
void DKFileV8::End()
{
	DKLog("DKFileV8::End()\n", DKDEBUG);
}

/*
///////////////////////////////////////////////////
bool DKFileV8::Test(CefArgs args, CefReturn retval)
{
	DKLog("DKFileV8::Test(CefArgs,CefReturn)\n", DKDEBUG);
	DKString data = args[0]->GetStringValue();
	DKString result = data;
	retval = CefV8Value::CreateString(result);
	return true;
}
*/

////////////////////////////////////////////////////
bool DKFileV8::ChDir(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKFile::ChDir(path);
	return true;
}

///////////////////////////////////////////////////
bool DKFileV8::Copy(CefArgs args, CefReturn retval)
{
	//DKString src = args[0]->GetStringValue();
	DKString src = args->GetString(0);
	//DKString dest = args[1]->GetStringValue();
	DKString dest = args->GetString(1);
	//bool overwrite = args[2]->GetBoolValue();
	bool overwrite = args->GetBool(2);
	if(!DKFile::Copy(src, dest, overwrite, true)){
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////
bool DKFileV8::CopyFolder(CefArgs args, CefReturn retval)
{
	//DKString src = args[0]->GetStringValue();
	DKString src = args->GetString(0);
	//DKString dst = args[1]->GetStringValue();
	DKString dst = args->GetString(1);
	//bool overwrite = args[2]->GetBoolValue();
	bool overwrite = args->GetBool(2);
	//bool recursive = args[3]->GetBoolValue();
	bool recursive = args->GetBool(3);
	DKLog("CopyFolder(" + src + "," + dst + "," + toString(overwrite) + "," + toString(recursive) + ")\n", DKINFO);
	if (!DKFile::CopyFolder(src, dst, overwrite, recursive)){
		DKLog("DKFile::CopyFolder(): failed. \n", DKERROR);
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////
bool DKFileV8::Delete(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKFile::Delete(path);
	return true;
}

////////////////////////////////////////////////////////////////
bool DKFileV8::DirectoryContents(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKLog("DKFileV8::DirectoryContents("+path+",CefReturn)\n", DKDEBUG);
	DKStringArray arry;
	if(!DKFile::GetDirectoryContents(path, arry)){
		return true;
	}
	DKString string = toString(arry, ",");
	//retval = CefV8Value::CreateString(string);
	retval->SetString(0, string);
	return true;
}

/////////////////////////////////////////////////////
bool DKFileV8::Exists(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	if(!DKFile::PathExists(path)){
		//retval = CefV8Value::CreateBool(false);
		retval->SetBool(0, false);
		return true; 
	}
	//retval = CefV8Value::CreateBool(true);
	retval->SetBool(0, true);
	return true;
}

///////////////////////////////////////////////////////////
bool DKFileV8::FileToString(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKString string;
	if (!DKFile::FileToString(path, string)) { return false; }
	//retval = CefV8Value::CreateString(string);
	retval->SetString(0, string);
	return true;
}

//////////////////////////////////////////////////////////////
bool DKFileV8::GetAbsolutePath(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKLog("DKFileV8::GetAbsolutePath("+path+",CefReturn)\n", DKDEBUG);
	DKString aPath;
	if(!DKFile::GetAbsolutePath(path, aPath)){ return false; }
	//retval = CefV8Value::CreateString(aPath);
	retval->SetString(0, aPath);
	return true;
}

/////////////////////////////////////////////////////////
bool DKFileV8::GetSetting(CefArgs args, CefReturn retval)
{
	//DKString file = args[0]->GetStringValue();
	DKString file = args->GetString(0);
	//DKString param = args[1]->GetStringValue();
	DKString param = args->GetString(1);
	DKString value;
	if(!DKFile::GetSetting(file, param, value)){
		return true;
	}
	//retval = CefV8Value::CreateString(value);
	retval->SetString(0, value);
	return true;
}

///////////////////////////////////////////////////////////
bool DKFileV8::GetShortName(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKLog("DKFileV8::GetShortName("+path+",CefReturn)\n", DKDEBUG);
#ifdef WIN32
	DKString shortname;
	if(DKFile::GetShortName(path, shortname)){
		//retval = CefV8Value::CreateString(shortname);
		retval->SetString(0, shortname);
		return true;
	}
#endif
	//retval = CefV8Value::CreateString(path);
	retval->SetString(0, path);
	return true;
}

//////////////////////////////////////////////////////////
bool DKFileV8::IsDirectory(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKLog("DKFileV8::IsDirectory("+path+",CefReturn)\n", DKDEBUG);
	if(!DKFile::IsDirectory(path)){
		//retval = CefV8Value::CreateBool(false);
		retval->SetBool(0, false);
		return true;
	}
	//retval = CefV8Value::CreateBool(true);
	retval->SetBool(0, true);
	return true;
}

////////////////////////////////////////////////////
bool DKFileV8::MkDir(CefArgs args, CefReturn retval)
{
	//DKString path = args[0]->GetStringValue();
	DKString path = args->GetString(0);
	DKFile::MakeDir(path);
	return true;
}

/////////////////////////////////////////////////////
bool DKFileV8::Rename(CefArgs args, CefReturn retval)
{
	//DKString input = args[0]->GetStringValue();
	DKString input = args->GetString(0);
	//DKString output = args[1]->GetStringValue();
	DKString output = args->GetString(1);
	//bool overwrite = args[2]->GetBoolValue();
	bool overwrite = args->GetBool(2);
	if(!DKFile::Rename(input, output, overwrite)){
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////
bool DKFileV8::SetSetting(CefArgs args, CefReturn retval)
{
	//DKString file = args[0]->GetStringValue();
	DKString file = args->GetString(0);
	//DKString param = args[1]->GetStringValue();
	DKString param = args->GetString(1);
	//DKString value = args[2]->GetStringValue();
	DKString value = args->GetString(2);
	if(!DKFile::SetSetting(file, param, value)){ 
		return false; 
	}
	return true;
}

///////////////////////////////////////////////////////////
bool DKFileV8::StringToFile(CefArgs args, CefReturn retval)
{
	//DKString string = args[0]->GetStringValue();
	DKString string = args->GetString(0);
	//DKString file = args[1]->GetStringValue();
	DKString file = args->GetString(1);
	if (!DKFile::StringToFile(string, file)) { return false; }
	return true;
}

#endif //USE_DKCef