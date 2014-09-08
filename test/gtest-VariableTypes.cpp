/*
 *  gtest-uuid_test.cpp
 *  xBeeHome
 *
 *  Created by Justin Hammond on 11/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <gtest/gtest.h>
#include "iHanClient/VariableTypes.hpp"
#include "../src/VariableTypes.cpp"

namespace testing {
namespace internal {
namespace {

TEST(VariableTypesTest, CheckValid) {
	EXPECT_STREQ(iHanClient::VarTypeHelper::Get()->VarTypetoName(iHanClient::VarTypeHelper::CT_NAME).c_str(), "CT_NAME");
}

TEST(VariableTypesTest, InsertAndCheck) {
	EXPECT_EQ(iHanClient::VarTypeHelper::Get()->InsertVarType("CT_TEST"), 1000);
	EXPECT_STREQ(iHanClient::VarTypeHelper::Get()->VarTypetoName(1000).c_str(), "CT_TEST");
}
TEST(VariableTypesTest, getByName) {
	EXPECT_EQ(iHanClient::VarTypeHelper::Get()->VarTypeNametoID("CT_NAME"), iHanClient::VarTypeHelper::CT_NAME);
}


}  // namespace
}  // namespace internal
}  // namespace testing
