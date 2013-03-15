#!/bin/sh
rm test/result/*.xml
export CXXFLAGS="-g -O0 -Wall"
if [ "$GTEST_OUTPUT"set = "set" ] ; then
	export GTEST_OUTPUT=xml:result/
fi	 
echo "Outputing Test Results: " $GTEST_OUTPUT
./configure --enable-gcov --with-gtestoptions=$GTEST_OUTPUT
make clean
make check
cd test
gcov *.cpp
mkdir -p ../target/site/clover
./gcov_to_clover.py -o ../target/site/clover/clover.xml *.gcov
