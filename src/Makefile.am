lib_LTLIBRARIES = libihanclient.la
libihanclient_la_SOURCES = varcontainer.cpp ZBLocations.cpp
libihanclient_la_CXXFLAGS = -DMUSCLE_SINGLE_THREAD_ONLY -I$(abs_srcdir)/../include/ -I$(abs_srcdir)/../muscle/ $(BOOST_CPPFLAGS)
libihanclient_la_LIBADD = $(abs_builddir)/../muscle/libmusclemessage.la
libihanclient_la_LDFLAGS = -version-info 1:0:0 -no-undefined

bin_PROGRAMS = demo
demo_SOURCES= varcontainerdemo.cpp
demo_LDADD = $(INTL_MACOSX_LIBS) libihanclient.la  $(BOOST_LDFLAGS) $(BOOST_DATE_TIME_LIB) $(BOOST_SERIALIZATION_LIB)
demo_CXXFLAGS = -DMUSCLE_SINGLE_THREAD_ONLY -I$(abs_srcdir)/../include/ -I$(abs_srcdir)/../muscle/ $(BOOST_CPPFLAGS)	
	
