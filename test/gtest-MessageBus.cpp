/*
 *  gtest-uuid_test.cpp
 *  xBeeHome
 *
 *  Created by Justin Hammond on 11/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <gtest/gtest.h>
#include "iHanClient/MessageBus.hpp"
#include "../src/MessageBus.cpp"

namespace testing {
namespace internal {
namespace {
	class MessageBusTest : public testing::Test {
			protected:
			     virtual void TearDown() {
			     }

		};

TEST_F(MessageBusTest, createSetVar) {
	MessageBusFactory(MB);
	VarContainerFactory(test);
	test->addStringValue("test", "test");
	EXPECT_TRUE(MB->createSetVar(test, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_SET_VAR);
	VarStorage result = MB->getSetVar();
	EXPECT_TRUE(result != NULL);

	std::string mystr;
	EXPECT_TRUE(result->getStringValue("test", mystr));
	EXPECT_STREQ(mystr.c_str(), "test");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType(SRVCAP_ENDPT_VARS), ST_VARSTORAGE);
	EXPECT_EQ(trans->getType(MSGB_FROM), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_SET_VAR);
}
TEST_F(MessageBusTest, createSetConfig) {
	MessageBusFactory(MB);
	VarContainerFactory(test);
	test->addStringValue("test", "test");
	EXPECT_TRUE(MB->createSetConfig(test, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_SET_CONFIG);
	VarStorage result = MB->getSetConfig();
	EXPECT_TRUE(result != NULL);

	std::string mystr;
	EXPECT_TRUE(result->getStringValue("test", mystr));
	EXPECT_STREQ(mystr.c_str(), "test");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType(SRVCAP_ENDPT_CONFIG), ST_VARSTORAGE);
	EXPECT_EQ(trans->getType(MSGB_FROM), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_SET_CONFIG);
}
TEST_F(MessageBusTest, createReportVar) {
	MessageBusFactory(MB);
	VarContainerFactory(test);
	test->addStringValue("test", "test");
	EXPECT_TRUE(MB->createReportVar(test, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_REPORT_VAR);
	VarStorage result = MB->getReportVar();
	EXPECT_TRUE(result != NULL);

	std::string mystr;
	EXPECT_TRUE(result->getStringValue("test", mystr));
	EXPECT_STREQ(mystr.c_str(), "test");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType(SRVCAP_ENDPT_VARS), ST_VARSTORAGE);
	EXPECT_EQ(trans->getType(MSGB_FROM), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_REPORT_VAR);
}
TEST_F(MessageBusTest, createReportConfig) {
	MessageBusFactory(MB);
	VarContainerFactory(test);
	test->addStringValue("test", "test");
	EXPECT_TRUE(MB->createReportConfig(test, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_REPORT_CONFIG);
	VarStorage result = MB->getReportConfig();
	EXPECT_TRUE(result != NULL);

	std::string mystr;
	EXPECT_TRUE(result->getStringValue("test", mystr));
	EXPECT_STREQ(mystr.c_str(), "test");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType(SRVCAP_ENDPT_CONFIG), ST_VARSTORAGE);
	EXPECT_EQ(trans->getType(MSGB_FROM), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_REPORT_CONFIG);

}TEST_F(MessageBusTest, createNewDevice) {
	MessageBusFactory(MB);
	VarContainerFactory(newclient);
	newclient->addStringValue(SRVCAP_PARENT_SERIAL, "1234");
	newclient->addLongValue(SRVCAP_ENDPT_TYPE, 12345);
	newclient->addStringValue(SRVCAP_ENDPT_SERIAL, "5678");
	newclient->addStringValue(SRVCAP_ENDPT_NAME, "myname");
	VarContainerFactory(cd);
	newclient->addVarStorageValue(SRVCAP_ENDPT_CONFIG_DESC, cd);
	VarContainerFactory(gc);
	newclient->addVarStorageValue(SRVCAP_ENDPT_CONFIG, gc);
	VarContainerFactory(vd);
	newclient->addVarStorageValue(SRVCAP_ENDPT_VARS_DESC, vd);
	VarContainerFactory(gv);
	newclient->addVarStorageValue(SRVCAP_ENDPT_VARS, gv);

	EXPECT_TRUE(MB->createNewDevice(newclient, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_NEW_DEVICE);
	VarStorage result = MB->getNewDevice();
	EXPECT_TRUE(result != NULL);
	std::string mystr;
	EXPECT_TRUE(result->getStringValue(SRVCAP_PARENT_SERIAL, mystr));
	EXPECT_STREQ(mystr.c_str(), "1234");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType(SRVCAP_ENDPT_CONFIG_DESC), ST_VARSTORAGE);
	EXPECT_EQ(trans->getType(SRVCAP_PARENT_SERIAL), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_NEW_DEVICE);

}

TEST_F(MessageBusTest, createDelDevice) {
	MessageBusFactory(MB);
	EXPECT_TRUE(MB->createDelDevice("delclient", "testclient"));
	EXPECT_EQ(MB->getType(), MSB_DEL_DEVICE);
	std::string result = MB->getDelDevice();
	EXPECT_GT(result.length(), 0);
	EXPECT_STREQ(result.c_str(), "delclient");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType(SRVCAP_ENDPT_SERIAL), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_DEL_DEVICE);
}

TEST_F(MessageBusTest, createSetup) {
	MessageBusFactory(MB);
	VarContainerFactory(test);
	test->addStringValue("test", "test");
	EXPECT_TRUE(MB->createSetup(test, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_SETUP);
	VarStorage result = MB->getSetup();
	EXPECT_TRUE(result != NULL);
	std::string mystr;
	EXPECT_TRUE(result->getStringValue("test", mystr));
	EXPECT_STREQ(mystr.c_str(), "test");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType("test"), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_SETUP);
}

TEST_F(MessageBusTest, createClientCap) {
	MessageBusFactory(MB);
	VarContainerFactory(test);
	test->addStringValue(MSGB_CLNCAP_AUTHUSER, "test");
	test->addStringValue(MSGB_CLNCAP_AUTHKEY, "pw");
	test->addLongValue(MSGB_CLNCAP_CAPDEVICE, 1);
	test->addLongValue(MSGB_CLNCAP_HOSTID, 21);
	test->addLongLongValue(MSGB_CLNCAP_FLAGS, 0);
	EXPECT_TRUE(MB->createClientCap(test, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_CLIENT_CAP);
	VarStorage result = MB->getClientCap();
	EXPECT_TRUE(result != NULL);
	std::string mystr;
	EXPECT_TRUE(result->getStringValue(MSGB_CLNCAP_AUTHUSER, mystr));
	EXPECT_STREQ(mystr.c_str(), "test");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType(MSGB_CLNCAP_AUTHUSER), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_CLIENT_CAP);
}

TEST_F(MessageBusTest, createServerCap) {
	MessageBusFactory(MB);
	VarContainerFactory(test);
	test->addStringValue("test", "test");
	EXPECT_TRUE(MB->createServerCap(test, "testclient"));
	EXPECT_EQ(MB->getType(), MSB_SERVER_CAP);
	VarStorage result = MB->getServerCap();
	EXPECT_TRUE(result != NULL);
	std::string mystr;
	EXPECT_TRUE(result->getStringValue("test", mystr));
	EXPECT_STREQ(mystr.c_str(), "test");
	VarStorage trans = MB->getTransportVarStorage();
	EXPECT_EQ(trans->getType("test"), ST_STRING);
	EXPECT_EQ(trans->getWhat(), MSB_SERVER_CAP);
}
TEST_F(MessageBusTest, importTransportVarStorage) {
	VarContainerFactory(newclient);
	newclient->setWhat(MSB_NEW_DEVICE);
	newclient->addStringValue(SRVCAP_PARENT_SERIAL, "1234");
	newclient->addLongValue(SRVCAP_ENDPT_TYPE, 12345);
	newclient->addStringValue(SRVCAP_ENDPT_SERIAL, "5678");
	newclient->addStringValue(SRVCAP_ENDPT_NAME, "myname");
	VarContainerFactory(cd);
	newclient->addVarStorageValue(SRVCAP_ENDPT_CONFIG_DESC, cd);
	VarContainerFactory(gc);
	newclient->addVarStorageValue(SRVCAP_ENDPT_CONFIG, gc);
	VarContainerFactory(vd);
	newclient->addVarStorageValue(SRVCAP_ENDPT_VARS_DESC, vd);
	VarContainerFactory(gv);
	newclient->addVarStorageValue(SRVCAP_ENDPT_VARS, gv);

	MessageBusFactory(MB);
	EXPECT_TRUE(MB->importTransportVarStorage(newclient));
	VarStorage client = MB->getNewDevice();
	EXPECT_TRUE(client != NULL);
	std::string name;
	EXPECT_TRUE(client->getStringValue(SRVCAP_ENDPT_NAME, name));
	EXPECT_STREQ(name.c_str(), "myname");
}



}  // namespace
}  // namespace internal
}  // namespace testing
