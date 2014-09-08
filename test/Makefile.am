ACLOCAL_AMFLAGS = -I autotools
AM_CXXFLAGS =  -DGTEST_HAS_PTHREAD=0 -I$(abs_srcdir)/../include/ -I$(abs_srcdir)/../muscle/ -DMUSCLE_SINGLE_THREAD_ONLY $(BOOST_CPPFLAGS)
##dnl -I$(top_srcdir)/test/ -I$(top_srcdir)/test/gtest/ -I$(top_srcdir) -I$(top_srcdir)/lib/muscle/ -I$(top_srcdir)/lib/include -I$(top_srcdir)/include/ 
AM_LDFLAGS = $(BOOST_LDFLAGS) $(BOOST_ASIO_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_SIGNALS_LIB) $(BOOST_SYSTEM_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_DATE_TIME_LIB) $(BOOST_SERIALIZATION_LIB)  $(BOOST_THREAD_LIB) $(BOOST_REGEX_LIB) -lpthread
check_PROGRAMS = gtest_all_test
TESTS_ENVIROMENT = env GTEST_OUTPUT=@GTEST_OUTPUT@/libihanclient-test.xml
TESTS = gtest_all_test
gtest_all_test_SOURCES = gtest-varstorage_test.cpp gtest-VariableTypes.cpp gtest/gtest-all.cc gtest/gtest_main.cc 
gtest_all_test_LDADD = $(abs_builddir)/../src/libihanclient.la
noinst_HEADERS = gtest/gtest.h
clean-local:
	-rm -rf results
	-rm *.gcno
	-rm *.gcda 
	-rm *.gcov