lib_LTLIBRARIES = libihanclient.la
libihanclient_la_SOURCES = varcontainer.cpp
libihanclient_la_CXXFLAGS = -DMUSCLE_SINGLE_THREAD_ONLY -I$(top_srcdir)/lib/include/ -I$(top_srcdir)/lib/muscle/
libihanclient_la_LIBADD = $(top_builddir)/lib/muscle/libmusclemessage.la
libihanclient_la_LDFLAGS = -version-info 1:0:0 -no-undefined

bin_PROGRAMS = demo
demo_SOURCES= varcontainerdemo.cpp
demo_LDADD = libihanclient.la  $(BOOST_LDFLAGS) $(BOOST_DATE_TIME_LIB) $(BOOST_SERIALIZATION_LIB)
demo_CXXFLAGS = -DMUSCLE_SINGLE_THREAD_ONLY -I$(top_srcdir)/lib/include/ -I$(top_srcdir)/lib/muscle/	
	
