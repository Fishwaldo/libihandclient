/*
 *  gtest-varstorage_test.cpp
 *  xBeeHome
 *
 *  Created by Justin Hammond on 11/4/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <gtest/gtest.h>
#include <boost/archive/tmpdir.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#if 0
#define BOOST_SP_ENABLE_DEBUG_HOOKS
#endif
#if 0
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#include <boost/utility.hpp>
#include "sp_collector.cpp"
#endif
#include "iHanClient/varcontainer.hpp"
#include "iHanClient/LogClass.hpp"
#include "../src/varcontainer.cpp"


namespace testing {
	namespace internal {
		namespace {
		class VarContainerTest : public testing::Test {
				protected:
				     virtual void SetUp() {
						 //this->Vars &= new VarStorage();
						 iHanClient::Logging::Log::Create("", true, iHanClient::Logging::LogLevel_Debug);
						 this->Vars.reset(new VarStorage_t());
						 this->Vars->addIntValue("INT", (int)123);
						 this->Vars->addStringValue("STRING", (std::string)"String");
						 this->Vars->addLongValue("LONG", (long)-1);
						 this->Vars->addLongLongValue("LONGLONG", (long long)-1);
						 this->Vars->addFloatValue("FLOAT", (float)1.24);
						 this->Vars->addBoolValue("BOOL", (bool)true);
						 this->Vars->addTimeValue("DATE", boost::posix_time::ptime(boost::posix_time::time_from_string("2010-01-10 10:23:23")));
						 HashVals newHashVars;
						 newHashVars["STRING"] = (std::string)"string";
						 newHashVars["INT"] = (int)123;
						 newHashVars["LONG"] = (long)-1;
						 newHashVars["LONGLONG"] = (long long)-1;
						 newHashVars["FLOAT"] = (float)1.24;
						 newHashVars["TIME"] = boost::posix_time::ptime(boost::posix_time::time_from_string("2011-01-10 1:30:12"));
						 this->Vars->addHashValue("HASH", newHashVars);
						 VarStorage newVar(new VarStorage_t());
						 newVar->addIntValue("INT", (int)123);
						 this->Vars->addVarStorageValue("VARSTORAGE", newVar);

						 /* test Array Handling */
						 this->Vars->addIntValue("MULTIINT", (int)456);
						 this->Vars->addIntValue("MULTIINT", (int)789);
						 this->Vars->addStringValue("MULTISTRING", (std::string)"String1");
						 this->Vars->addStringValue("MULTISTRING", (std::string)"String2");
						 this->Vars->addLongValue("MULTILONG", (long)112233);
						 this->Vars->addLongValue("MULTILONG", (long)223344);
						 this->Vars->addLongLongValue("MULTILONGLONG", (long long)33445566);
						 this->Vars->addLongLongValue("MULTILONGLONG", (long long)77889900);
						 this->Vars->addFloatValue("MULTIFLOAT", (float)3.45);
						 this->Vars->addFloatValue("MULTIFLOAT", (float)6.78);
						 this->Vars->addBoolValue("MULTIBOOL", (bool)true);
						 this->Vars->addBoolValue("MULTIBOOL", (bool)true);
						 this->Vars->addTimeValue("MULTIDATE", boost::posix_time::ptime(boost::posix_time::time_from_string("2010-01-10 10:23:23")));
						 this->Vars->addTimeValue("MULTIDATE", boost::posix_time::ptime(boost::posix_time::time_from_string("2011-02-28 11:33:43")));

				     }

				VarStorage Vars;
			};


			TEST_F(VarContainerTest, ReturnsTrueForCountItems) {
				EXPECT_EQ(Vars->getSize(), 16);
			}

			TEST_F(VarContainerTest, CheckIntContents) {
				int i;
				Vars->getIntValue("INT", i);
				EXPECT_EQ(123,i);
			}
			TEST_F(VarContainerTest, CheckStringContents) {
				std::string val;
				Vars->getStringValue("STRING", val);
				EXPECT_STREQ("String", val.c_str());
			}
			TEST_F(VarContainerTest, CheckLongContents) {
				long i;
				Vars->getLongValue("LONG", i);
				EXPECT_EQ((long)-1, i);
			}
			TEST_F(VarContainerTest, CheckLongLongContents) {
				long long i;
				Vars->getLongLongValue("LONGLONG", i);
				EXPECT_EQ((long long)-1, i);
			}
			TEST_F(VarContainerTest, CheckFloatContents) {
				float i;
				Vars->getFloatValue("FLOAT", i);
				EXPECT_FLOAT_EQ((float)1.24, i);
			}
			TEST_F(VarContainerTest, CheckBoolContents) {
				bool i;
				Vars->getBoolValue("BOOL", i);
				EXPECT_EQ(true, i);
			}
			TEST_F(VarContainerTest, CheckDateContents) {
				boost::posix_time::ptime i;
				Vars->getTimeValue("DATE", i);
				EXPECT_EQ(boost::posix_time::ptime(boost::posix_time::time_from_string("2010-01-10 10:23:23")), i);
			}
			TEST_F(VarContainerTest, CheckHashContents) {
				HashVals val;
				EXPECT_TRUE(Vars->getHashValue("HASH", val));
				EXPECT_TRUE(boost::get<std::string>(val["STRING"]) == "string");
				EXPECT_TRUE(boost::get<int>(val["INT"]) == 123);
				EXPECT_TRUE(boost::get<long>(val["LONG"]) == (long)-1);
				EXPECT_TRUE(boost::get<long long>(val["LONGLONG"]) == (long long)-1);
				EXPECT_TRUE(boost::get<float>(val["FLOAT"]) == (float)1.24);
				EXPECT_TRUE(boost::get<boost::posix_time::ptime>(val["TIME"]) == boost::posix_time::ptime(boost::posix_time::time_from_string("2011-01-10 1:30:12")));
			}
			TEST_F(VarContainerTest, CheckVarStorageContents) {
				VarStorage val;
				EXPECT_TRUE(Vars->getVarStorageValue("VARSTORAGE", val));
				int i;
				EXPECT_TRUE(val->getIntValue("INT", i));
				EXPECT_EQ((int)123, i);
			}
			TEST_F(VarContainerTest, AddIntValueAndCheck) {
				int i = 321;
				EXPECT_TRUE(Vars->addIntValue("INT", i)) << "Adding Int Value Failed";
				int j;
				EXPECT_TRUE(Vars->getIntValue("INT", j, 1)) << "Getting 2nd Int Value Failed";
				EXPECT_EQ((int)321, j) << "Int Value Didn't Match";
			}
			TEST_F(VarContainerTest, AddStringValueAndCheck) {
				std::string val("Testing213");
				EXPECT_TRUE(Vars->addStringValue("STRING", val)) << "Adding String Value Failed";
				std::string val2;
				EXPECT_TRUE(Vars->getStringValue("STRING", val2, 1)) << "Getting 2nd Int Value Failed";
				EXPECT_STREQ("Testing213", val.c_str()) << "String Value Didn't Match";
			}
			TEST_F(VarContainerTest, AddLongValueAndCheck) {
				long i = (long)-2;
				EXPECT_TRUE(Vars->addLongValue("LONG", i)) << "Adding Long Value Failed";
				long j;
				EXPECT_TRUE(Vars->getLongValue("LONG", j, 1)) << "Getting 2nd Long Value Failed";
				EXPECT_EQ((long)-2, j) << "Long Value Didn't Match";
			}
			TEST_F(VarContainerTest, AddLongLongValueAndCheck) {
				long long i = (long long)-2;
				EXPECT_TRUE(Vars->addLongLongValue("LONGLONG", i)) << "Adding Long Long Value Failed";
				long long j;
				EXPECT_TRUE(Vars->getLongLongValue("LONGLONG", j, 1)) << "Getting 2nd Long Long Value Failed";
				EXPECT_EQ((long long)-2, j) << "long long Value Didn't Match";
			}
			TEST_F(VarContainerTest, AddFloatValueAndCheck) {
				float i = (float)9.32;
				EXPECT_TRUE(Vars->addFloatValue("FLOAT", i)) << "Adding float Value Failed";
				float j;
				EXPECT_TRUE(Vars->getFloatValue("FLOAT", j, 1)) << "Getting 2nd Float Value Failed";
				EXPECT_FLOAT_EQ((float)9.32, j) << "float Value Didn't Match";
			}
			TEST_F(VarContainerTest, AddBOOLValueAndCheck) {
				bool i = false;
				EXPECT_TRUE(Vars->addBoolValue("BOOL", i)) << "Adding Bool Value Failed";
				bool j;
				EXPECT_TRUE(Vars->getBoolValue("BOOL", j, 1)) << "Getting 2nd Bool Value Failed";
				EXPECT_FALSE(j) << "Bool Value Didn't Match";
			}
			TEST_F(VarContainerTest, AddDateValueAndCheck) {
				boost::posix_time::ptime i(boost::posix_time::time_from_string("2011-04-12 18:54:34"));
				EXPECT_TRUE(Vars->addTimeValue("DATE", i));
				boost::posix_time::ptime j;
				EXPECT_TRUE(Vars->getTimeValue("DATE", j, 1));
				EXPECT_EQ(i, j);
			}
			TEST_F(VarContainerTest, ReplaceIntValueAndCheck) {
				int i = 456;
				EXPECT_TRUE(Vars->addIntValue("INT", i)) << "Adding 2nd Value Failed";
				int j;
				EXPECT_TRUE(Vars->getIntValue("INT", j, 1)) << "Getting 2nd Value Failed";
				EXPECT_EQ(i, j) << "2nd Value didn't match";
				i = 789;
				EXPECT_GE(Vars->replaceIntValue("INT", i, 1),0) << "Replace Failed";
				EXPECT_TRUE(Vars->getIntValue("INT", j, 1)) << "Getting Replaced Value Failed";
				EXPECT_EQ(i, j) << "Replacement Value didn't match";
				EXPECT_TRUE(Vars->getIntValue("INT", j, 0)) << "Getting First Value Failed";
				EXPECT_EQ(123, j);
			}
			TEST_F(VarContainerTest, ReplaceStringValueAndCheck) {
				std::string val("InitialString");
				EXPECT_TRUE(Vars->addStringValue("STRING", val)) << "Adding 2nd Value Failed";
				std::string j;
				EXPECT_TRUE(Vars->getStringValue("STRING", j, 1)) << "Getting 2nd Value Failed";
				EXPECT_STREQ(val.c_str(), j.c_str()) << "2nd Value didn't match";
				val = "789";
				EXPECT_GE(Vars->replaceStringValue("STRING", val, 1),0) << "Replace Failed";
				EXPECT_TRUE(Vars->getStringValue("STRING", j, 1)) << "Getting Replaced Value Failed";
				EXPECT_STREQ(val.c_str(), j.c_str()) << "Replacement Value didn't match";
				EXPECT_TRUE(Vars->getStringValue("STRING", j, 0)) << "Getting First Value Failed";
				EXPECT_STREQ("String", j.c_str());
			}
			TEST_F(VarContainerTest, ReplaceLongValueAndCheck) {
				long i = (long)-456;
				EXPECT_TRUE(Vars->addLongValue("LONG", i)) << "Adding 2nd Value Failed";
				long j;
				EXPECT_TRUE(Vars->getLongValue("LONG", j, 1)) << "Getting 2nd Value Failed";
				EXPECT_EQ(i, j) << "2nd Value didn't match";
				i = (long)-789;
				EXPECT_GE(Vars->replaceLongValue("LONG", i, 1),0) << "Replace Failed";
				EXPECT_TRUE(Vars->getLongValue("LONG", j, 1)) << "Getting Replaced Value Failed";
				EXPECT_EQ(i, j) << "Replacement Value didn't match";
				EXPECT_TRUE(Vars->getLongValue("LONG", j, 0)) << "Getting First Value Failed";
				EXPECT_EQ((long)-1, j);
			}
			TEST_F(VarContainerTest, ReplaceLongLongValueAndCheck) {
				long long i = (long long)-325;
				EXPECT_TRUE(Vars->addLongLongValue("LONGLONG", i)) << "Adding 2nd Value Failed";
				long long j;
				EXPECT_TRUE(Vars->getLongLongValue("LONGLONG", j, 1)) << "Getting 2nd Value Failed";
				EXPECT_EQ(i, j) << "2nd Value didn't match";
				i = (long long)-729;
				EXPECT_GE(Vars->replaceLongLongValue("LONGLONG", i, 1),0) << "Replace Failed";
				EXPECT_TRUE(Vars->getLongLongValue("LONGLONG", j, 1)) << "Getting Replaced Value Failed";
				EXPECT_EQ(i, j) << "Replacement Value didn't match";
				EXPECT_TRUE(Vars->getLongLongValue("LONGLONG", j, 0)) << "Getting First Value Failed";
				EXPECT_EQ((long)-1, j);
			}
			TEST_F(VarContainerTest, ReplaceFloatValueAndCheck) {
				float i = (float)22.341;
				EXPECT_TRUE(Vars->addFloatValue("FLOAT", i)) << "Adding 2nd Value Failed";
				float j;
				EXPECT_TRUE(Vars->getFloatValue("FLOAT", j, 1)) << "Getting 2nd Value Failed";
				EXPECT_FLOAT_EQ(i, j) << "2nd Value didn't match";
				i = (float)11.932;
				EXPECT_GE(Vars->replaceFloatValue("FLOAT", i, 1),0) << "Replace Failed";
				EXPECT_TRUE(Vars->getFloatValue("FLOAT", j, 1)) << "Getting Replaced Value Failed";
				EXPECT_FLOAT_EQ(i, j) << "Replacement Value didn't match";
				EXPECT_TRUE(Vars->getFloatValue("FLOAT", j, 0)) << "Getting First Value Failed";
				EXPECT_FLOAT_EQ((float)1.24, j);
			}
			TEST_F(VarContainerTest, ReplaceBoolValueAndCheck) {
				bool i = true;
				EXPECT_TRUE(Vars->addBoolValue("BOOL", i)) << "Adding 2nd Value Failed";
				bool j;
				EXPECT_TRUE(Vars->getBoolValue("BOOL", j, 1)) << "Getting 2nd Value Failed";
				EXPECT_EQ(i, j) << "2nd Value didn't match";
				i = false;
				EXPECT_GE(Vars->replaceBoolValue("BOOL", i, 1),0) << "Replace Failed";
				EXPECT_TRUE(Vars->getBoolValue("BOOL", j, 1)) << "Getting Replaced Value Failed";
				EXPECT_EQ(i, j) << "Replacement Value didn't match";
				EXPECT_TRUE(Vars->getBoolValue("BOOL", j, 0)) << "Getting First Value Failed";
				EXPECT_EQ(true, j);
			}
			TEST_F(VarContainerTest, ReplaceDateValueAndCheck) {
				boost::posix_time::ptime i(boost::posix_time::time_from_string("2011-04-12 18:54:34"));
				EXPECT_TRUE(Vars->addTimeValue("DATE", i));
				boost::posix_time::ptime j;
				EXPECT_TRUE(Vars->getTimeValue("DATE", j, 1));
				EXPECT_EQ(i, j);
				i = boost::posix_time::time_from_string("2012-12-12 23:59:59");
				EXPECT_GE(Vars->replaceTimeValue("DATE", i, 1),0);
				EXPECT_TRUE(Vars->getTimeValue("DATE", j, 1));
				EXPECT_EQ(i, j);
				EXPECT_TRUE(Vars->getTimeValue("DATE", j, 0));
				EXPECT_EQ(boost::posix_time::time_from_string("2010-01-10 10:23:23"), j);
			}
			TEST_F(VarContainerTest, ReplaceVarStorageValueAndCheck) {
				VarStorage newVar(new VarStorage_t());
				EXPECT_TRUE(newVar->addStringValue("STRING", "NewVar"));
				EXPECT_GE(this->Vars->replaceVarStorageValue("VARSTORAGE", newVar), 0);

				VarStorage getVar;
				EXPECT_TRUE(this->Vars->getVarStorageValue("VARSTORAGE", getVar));
				std::string value;
				EXPECT_TRUE(getVar->getStringValue("STRING", value));
				EXPECT_EQ("NewVar", value);
			}
			TEST_F(VarContainerTest, CopyConstructor) {
				 VarContainerCopy(newvals, this->Vars);
				 this->Vars->addIntValue("INT", (int)123);
				 {
					 int oldval, newval;
					 EXPECT_TRUE(this->Vars->getIntValue("INT", oldval));
					 EXPECT_TRUE(newvals->getIntValue("INT", newval));
					 EXPECT_EQ(oldval, newval);
				 }
				 {
					 long oldval, newval;
					 EXPECT_TRUE(this->Vars->getLongValue("LONG", oldval));
					 EXPECT_TRUE(newvals->getLongValue("LONG", newval));
					 EXPECT_EQ(oldval, newval);
				 }
				 {
					 long long oldval, newval;
					 EXPECT_TRUE(this->Vars->getLongLongValue("LONGLONG", oldval));
					 EXPECT_TRUE(newvals->getLongLongValue("LONGLONG", newval));
					 EXPECT_EQ(oldval, newval);
				 }
				 {
					 float oldval, newval;
					 EXPECT_TRUE(this->Vars->getFloatValue("FLOAT", oldval));
					 EXPECT_TRUE(newvals->getFloatValue("FLOAT", newval));
					 EXPECT_FLOAT_EQ(oldval, newval);
				 }
				 {
					 bool oldval, newval;
					 EXPECT_TRUE(this->Vars->getBoolValue("BOOL", oldval));
					 EXPECT_TRUE(newvals->getBoolValue("BOOL", newval));
					 EXPECT_FLOAT_EQ(oldval, newval);
				 }
				 {
					 boost::posix_time::ptime oldval, newval;
					 EXPECT_TRUE(this->Vars->getTimeValue("DATE", oldval));
					 EXPECT_TRUE(newvals->getTimeValue("DATE", newval));
					 EXPECT_EQ(oldval, newval);
				 }
				 {
					 HashVals oldval, newval;
					 EXPECT_TRUE(this->Vars->getHashValue("HASH", oldval));
					 EXPECT_TRUE(newvals->getHashValue("HASH", newval));
					 EXPECT_EQ(oldval["STRING"], newval["STRING"]);
					 EXPECT_EQ(oldval["INT"], newval["INT"]);
					 EXPECT_EQ(oldval["LONG"], newval["LONG"]);
					 EXPECT_EQ(oldval["LONGLONG"], newval["LONGLONG"]);
					 EXPECT_EQ(oldval["TIME"], newval["TIME"]);
				 }
				 {
					 VarStorage oldval, newval;
					 EXPECT_TRUE(this->Vars->getVarStorageValue("VARSTORAGE", oldval));
					 EXPECT_TRUE(newvals->getVarStorageValue("VARSTORAGE", newval));
					 int oldint, newint;
					 EXPECT_TRUE(oldval->getIntValue("INT", oldint));
					 EXPECT_TRUE(newval->getIntValue("INT", newint));
					 EXPECT_EQ(oldint, newint);

				 }
			}
			TEST_F(VarContainerTest, Serialize) {
				VarStorage newVars(new VarStorage_t());
				std::string filename(boost::archive::tmpdir());
				filename += "/testSerialize.xml";
				std::ofstream ofs(filename.c_str());
				EXPECT_TRUE(ofs.good());
				boost::archive::xml_oarchive oa(ofs);
				oa << BOOST_SERIALIZATION_NVP(Vars);
				ofs.close();
				std::ifstream ifs(filename.c_str());
				EXPECT_TRUE(ifs.good());
				boost::archive::xml_iarchive ia(ifs);
				ia >> BOOST_SERIALIZATION_NVP(newVars);
				ifs.close();
				EXPECT_EQ(newVars->getSize(),16);
				int i;
				newVars->getIntValue("INT", i);
				EXPECT_EQ(123,i);
				std::string val;
				newVars->getStringValue("STRING", val);
				EXPECT_STREQ("String", val.c_str());
				long j;
				newVars->getLongValue("LONG", j);
				EXPECT_EQ((long)-1, j);
				long long k;
				newVars->getLongLongValue("LONGLONG", k);
				EXPECT_EQ((long long)-1, k);
				float l;
				newVars->getFloatValue("FLOAT", l);
				EXPECT_FLOAT_EQ((float)1.24, l);
				bool m;
				newVars->getBoolValue("BOOL", m);
				EXPECT_EQ(true, m);
				boost::posix_time::ptime n;
				newVars->getTimeValue("DATE", n);
				EXPECT_EQ(boost::posix_time::ptime(boost::posix_time::time_from_string("2010-01-10 10:23:23")), n);
				Vars->getIntValue("MULTIINT", i, 0);
				EXPECT_EQ(456,i);
				Vars->getIntValue("MULTIINT", i, 1);
				EXPECT_EQ(789,i);
				Vars->getStringValue("MULTISTRING", val, 0);
				EXPECT_STREQ("String1", val.c_str());
				Vars->getStringValue("MULTISTRING", val, 1);
				EXPECT_STREQ("String2", val.c_str());
				Vars->getLongValue("MULTILONG", j, 0);
				EXPECT_EQ((long)112233, j);
				Vars->getLongValue("MULTILONG", j, 1);
				EXPECT_EQ((long)223344, j);
				Vars->getLongLongValue("MULTILONGLONG", k, 0);
				EXPECT_EQ((long long)33445566, k);
				Vars->getLongLongValue("MULTILONGLONG", k, 1);
				EXPECT_EQ((long long)77889900, k);
				Vars->getFloatValue("MULTIFLOAT", l, 0);
				EXPECT_FLOAT_EQ((float)3.45, l);
				Vars->getFloatValue("MULTIFLOAT", l, 1);
				EXPECT_FLOAT_EQ((float)6.78, l);
				Vars->getBoolValue("MULTIBOOL", m, 0);
				EXPECT_EQ(true, m);
				Vars->getBoolValue("MULTIBOOL", m, 1);
				EXPECT_EQ(true, m);
				Vars->getTimeValue("MULTIDATE", n, 0);
				EXPECT_EQ(boost::posix_time::ptime(boost::posix_time::time_from_string("2010-01-10 10:23:23")), n);
				Vars->getTimeValue("MULTIDATE", n, 1);
				EXPECT_EQ(boost::posix_time::ptime(boost::posix_time::time_from_string("2011-02-28 11:33:43")), n);

				std::remove(filename.c_str());
#if 0
				find_unreachable_objects();
#endif
			}
			TEST_F(VarContainerTest, CheckMultiIntContents) {
				int i;
				Vars->getIntValue("MULTIINT", i, 0);
				EXPECT_EQ(456,i);
				Vars->getIntValue("MULTIINT", i, 1);
				EXPECT_EQ(789,i);

			}
			TEST_F(VarContainerTest, CheckMultiStringContents) {
				std::string val;
				Vars->getStringValue("MULTISTRING", val, 0);
				EXPECT_STREQ("String1", val.c_str());
				Vars->getStringValue("MULTISTRING", val, 1);
				EXPECT_STREQ("String2", val.c_str());
			}
			TEST_F(VarContainerTest, CheckMultiLongContents) {
				long i;
				Vars->getLongValue("MULTILONG", i, 0);
				EXPECT_EQ((long)112233, i);
				Vars->getLongValue("MULTILONG", i, 1);
				EXPECT_EQ((long)223344, i);

			}
			TEST_F(VarContainerTest, CheckMultiLongLongContents) {
				long long i;
				Vars->getLongLongValue("MULTILONGLONG", i, 0);
				EXPECT_EQ((long long)33445566, i);
				Vars->getLongLongValue("MULTILONGLONG", i, 1);
				EXPECT_EQ((long long)77889900, i);

			}
			TEST_F(VarContainerTest, CheckMultiFloatContents) {
				float i;
				Vars->getFloatValue("MULTIFLOAT", i, 0);
				EXPECT_FLOAT_EQ((float)3.45, i);
				Vars->getFloatValue("MULTIFLOAT", i, 1);
				EXPECT_FLOAT_EQ((float)6.78, i);

			}
			TEST_F(VarContainerTest, CheckMultiBoolContents) {
				bool i;
				Vars->getBoolValue("MULTIBOOL", i, 0);
				EXPECT_EQ(true, i);
				Vars->getBoolValue("MULTIBOOL", i, 1);
				EXPECT_EQ(true, i);

			}
			TEST_F(VarContainerTest, CheckMultiDateContents) {
				boost::posix_time::ptime i;
				Vars->getTimeValue("MULTIDATE", i, 0);
				EXPECT_EQ(boost::posix_time::ptime(boost::posix_time::time_from_string("2010-01-10 10:23:23")), i);
				Vars->getTimeValue("MULTIDATE", i, 1);
				EXPECT_EQ(boost::posix_time::ptime(boost::posix_time::time_from_string("2011-02-28 11:33:43")), i);

			}


		}  // namespace
	}  // namespace internal
}  // namespace testing
