#!/bin/sh
rm test/result/*.xml
export CXXFLAGS="-g -O0 -Wall"
if [ "$GTEST_OUTPUT"set = "set" ] ; then
	export GTEST_OUTPUT=xml:result/
fi	 
echo "Outputing Test Results: " $GTEST_OUTPUT
./configure --with-gtestoptions=$GTEST_OUTPUT
make distcheck
