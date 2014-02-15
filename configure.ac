#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ(2.61)
AC_INIT(libihanclient, 0.2)
AC_CONFIG_AUX_DIR(autotools)
AC_CONFIG_SRCDIR([src/varcontainer.cpp])
AC_CONFIG_HEADER([include/config.h])
AC_CONFIG_MACRO_DIR(autotools)
AC_CACHE_LOAD
AM_INIT_AUTOMAKE(silent-rules)
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE
#AC_MSG_HEADER([Configuring Core Now])

dnl AC_LIBTOOL_DLOPEN
dnl AC_DISABLE_SHARED
dnl AC_LIBTOOL_WIN32_DLL
dnl AC_LIBLTDL_CONVENIENCE

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
# AC_PROG_YACC 
# AC_PROG_LEX
# AC_PATH_PROG( SED, sed, , $PATH:/usr/bin:/usr/local/bin)

AX_BOOST_BASE(1.37)
# AX_BOOST_SYSTEM
# AX_BOOST_ASIO
# AX_BOOST_SIGNALS
# AX_BOOST_PROGRAM_OPTIONS
# AX_BOOST_FILESYSTEM
AX_BOOST_DATE_TIME
AX_BOOST_SERIALIZATION
# AX_BOOST_THREAD
# AX_BOOST_REGEX
# PKG_CHECK_MODULES([LOG4CXX], [liblog4cxx])
CXXFLAGS="$CXXFLAGS $APR_CFLAGS $APRUTIL_CFLAGS $LOG4CXX_CFLAGS"
Check_MACOSX
LIBS="$LIBS $APR_LIBS $APRUTIL_LIBS $LOG4CXX_LIBS $INTL_MACOSX_LIBS"

AC_MSG_CHECKING(Whether to Enable Coverage Testing...)
AC_ARG_ENABLE(gcov,
AC_HELP_STRING([--enable-gcov], [Enable Coverage Testing]),
[ case "$enableval" in
  yes)
	CXXFLAGS="$CXXFLAGS -fprofile-arcs -ftest-coverage --coverage"
	LIBS="$LIBS -lgcov"
	AC_MSG_RESULT(yes - Watch your Log Files)
	;;
  *)
	AC_MSG_RESULT(no)
	;;
  esac],
AC_MSG_RESULT(no)
)


dnl check if we are running with Debug....
AC_MSG_CHECKING(Whether to Enable Debuging...)
AC_ARG_ENABLE(debug,
AC_HELP_STRING([--enable-debug], [Enable Debuging]),
[ case "$enableval" in
  yes)
	AC_DEFINE(DEBUG, 1, 'Enable Debugging')
	CXXFLAGS="$CXXFLAGS -ggdb -Wall -O0 -U_FORTIFY_SOURCE"
	AC_MSG_RESULT(yes - Watch your Log Files)
	;;
  *)
	CXXFLAGS="$CXXFLAGS -DNDEBUG"
	AC_MSG_RESULT(no)
	;;
  esac],
CFLAGS="$CFLAGS -DNDEBUG"
AC_MSG_RESULT(no)
)

AC_MSG_CHECKING([Options for GTEST Framework])
AC_ARG_WITH(gtestoptions, 
AC_HELP_STRING([--with-gtestoptions=<options>], [Options to pass to Gtest Framework via GTEST_OUTPUT]),
AS_IF([test "x$with_gtestoptions" != x],
	AC_SUBST([GTEST_OUTPUT], $with_gtestoptions),
	AC_SUBST([GTEST_OUTPUT], "")
)
)
AC_MSG_RESULT($with_gtestoptions)

if test "${ac_configure_args+set}" != "set" ; then
      ac_configure_args=
      for ac_arg in ${1+"[$]@"}; do
         ac_configure_args="$ac_configure_args '$ac_arg'"
      done
fi
AC_SUBST([CONFIGURE_ARGS], $ac_configure_args)

AC_CONFIG_FILES([Makefile muscle/Makefile include/Makefile src/Makefile libihanclient.pc test/Makefile])
AC_CONFIG_FILES([libihanclient.spec libihanclient.dsc debian/libihanclient-dev.dirs debian/libihanclient-dev.install])
AC_CACHE_SAVE
AC_OUTPUT
