#include "iHanClient/varcontainer.hpp"
#include "iHanClient/LogClass.hpp"



int main(int argc, char *argv[]) {
	iHanClient::Logging::Log::Create("", true, iHanClient::Logging::LogLevel_Debug);
	iHanClient::Logging::LogInfo("Starting Demo");
	VarStorage Vars;
	Vars.reset(new VarStorage_t());
	Vars->addIntValue("INT", (int)123);
	Vars->addStringValue("STRING", (std::string)"String");
	Vars->addLongValue("LONG", (long)-1);
	Vars->addLongLongValue("LONGLONG", (long long)-1);
	Vars->addFloatValue("FLOAT", (float)1.24);
	Vars->addBoolValue("BOOL", (bool)true);
	Vars->addTimeValue("DATE", boost::posix_time::ptime(boost::posix_time::time_from_string("2010-01-10 10:23:23")));
	HashVals newHashVars;
	newHashVars["STRING"] = (std::string)"string";
	newHashVars["INT"] = (int)123;
	newHashVars["LONG"] = (long)-1;
	newHashVars["LONGLONG"] = (long long)-1;
	newHashVars["FLOAT"] = (float)1.24;
	newHashVars["TIME"] = boost::posix_time::ptime(boost::posix_time::time_from_string("2011-01-10 1:30:12"));
	Vars->addHashValue("HASH", newHashVars);
	VarStorage newVar(new VarStorage_t());
	newVar->addIntValue("INT", (int)123);
	Vars->addVarStorageValue("VARSTORAGE", newVar);
	cout << *(Vars);
//	iHanDClient::Logging::LogInfo( *(Vars.get()));
	iHanClient::Logging::LogInfo("Finished Debug");
}
