#ifdef USE_DKCef
#include "DKAssetsV8.h"
#include "DKFile.h"
#include "DKApp.h"

/////////////////////
void DKAssetsV8::Init()
{
	DKLog("DKAssetsV8::Init()\n", DKDEBUG);
	//DKV8::AttachFunction("Test", DKAssetsV8::Test);
	DKV8::AttachFunction("DKAssets_LocalAssets", DKAssetsV8::LocalAssets);
}

///////////////////
void DKAssetsV8::End()
{
	DKLog("DKAssetsV8::End()\n", DKDEBUG);
}

/*
///////////////////////////////////////////////////
bool DKAssetsV8::Test(CefArgs args, CefReturn retval)
{
	DKLog("DKAssetsV8::Test(CefArgs,CefReturn)\n", DKDEBUG);
	DKString data = args[0]->GetStringValue();
	DKString result = data;
	retval = CefV8Value::CreateString(result);
	return true;
}
*/

////////////////////////////////////////////////////////////
bool DKAssetsV8::LocalAssets(CefArgs args, CefReturn retval)
{
	//retval = CefV8Value::CreateString(DKFile::local_assets);
	retval->SetString(0, DKFile::local_assets);
	return true;
}

#endif //USE_DKCef