#ifdef USE_DKDuktape 
#include "DKMySqlJS.h"
#include "DKMySql.h"


///////////////////////
void DKMySqlJS::Init()
{
	DKDuktape::AttachFunction("DKMySql_Connect", DKMySqlJS::Connect, 4);
	DKDuktape::AttachFunction("DKMySql_Database", DKMySqlJS::Database, 1);
	DKDuktape::AttachFunction("DKMySql_Query", DKMySqlJS::Query, 1);
}

/////////////////////////////////
int DKMySqlJS::Connect(duk_context* ctx)
{
	DKString host = duk_require_string(ctx, 0);
	DKString name = duk_require_string(ctx, 1);
	DKString pass = duk_require_string(ctx, 2);
	DKString port = duk_require_string(ctx, 3);
	DKMySql::Instance("DKMySql")->Connect(host, name, pass, port);
	return 1;
}

//////////////////////////////////
int DKMySqlJS::Database(duk_context* ctx)
{
	DKString name = duk_require_string(ctx, 0);
	DKMySql::Instance("DKMySql")->Database(name);
	return 1;
}

///////////////////////////////
int DKMySqlJS::Query(duk_context* ctx)
{
	DKString query = duk_require_string(ctx, 0);

	DKStringArray records;
	DKMySql::Instance("DKMySql")->Query(query, records);

	if(records.empty()){ return 0; }
	DKString string = toString(records, ",");
	duk_push_string(ctx, string.c_str());

	return 1;
}

#endif //USE_DKDuktape