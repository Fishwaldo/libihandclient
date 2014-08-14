#include "iHanClient/varcontainer.hpp"
#include "iHanClient/LogClass.hpp"

ListOptions_t test[] = {
		{3, "test3"},
		{4, "test4"},
		{-1, ""}
};

void null_deleter(ListOptions_t *) {}

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


	CreateListOptions(options, 3);
	AddListOptions(options, 0, 1, "test1");
	AddListOptions(options, 1, 2, "test2");
	FinishListOptions(options, 2);

	ListStackPointer(newHashVars["LIST2"], test);
	//newHashVars["LIST2"] = test22;
//	ListOptions_t *options = new ListOptions_t[3];
//	options[0].index = 1;
//	strncpy(options[0].desc, "test", 256);
	//=  { .index = 1, .desc = "test"};
//	options[1] =  {2, "test2"};
//	options[2] =  {-1, ""};
	newHashVars["LIST"] = (ListOptions)options;

	Vars->addHashValue("HASH", newHashVars);
	VarStorage newVar(new VarStorage_t());
	newVar->addIntValue("INT", (int)123);
	Vars->addVarStorageValue("VARSTORAGE", newVar);
	Vars->addListValue("LIST", 1, "test");
	Vars->addListValue("LIST", 2, "test2");
	Vars->setListSelectedValue("LIST", 2);

	cout << *(Vars);
	muscle::MessageRef test = Vars->toMuscle();
	test()->PrintToStream();

	uint32 flatsize= test()->FlattenedSize();
	uint8 *flatmsg = (uint8*)malloc(flatsize+10);
	test()->Flatten(flatmsg);

	std::cout << flatsize << std::endl;

	muscle::Message test2;
	test2.Unflatten(flatmsg, flatsize);
	test2.PrintToStream();
	muscle::MessageRef test3;
//	test3.Ref(test2, true);
	test3.SetRef(&test2, false);

	VarContainerFactory(Vars2);
	Vars2->importMuscleMsg(test3);
	std::cout << std::endl << *(Vars2) << std::endl;


//	iHanDClient::Logging::LogInfo( *(Vars.get()));
	iHanClient::Logging::LogInfo("Finished Debug");
	free(flatmsg);
}
