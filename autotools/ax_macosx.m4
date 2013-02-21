dnl Checks for special options needed on MacOS X.
dnl Defines INTL_MACOSX_LIBS.
AC_DEFUN([Check_MACOSX],
[
  dnl Check for API introduced in MacOS X 10.2.
  AC_CACHE_CHECK([for CoreServices],
    ax_cv_have_CoreServices,
    [gt_save_CPPFLAGS="$CPPFLAGS"
     CPPFLAGS="$CPPFLAGS -I/System/Library/Frameworks/CoreServices.framework/Headers"
     gt_save_LIBS="$LIBS"
     LIBS="$LIBS -framework CoreServices"
     AC_TRY_LINK([#include <CoreServices.h>],
       [CFNullGetTypeID()],
       [have_CoreServices=yes],
       [have_CoreServices=no])
     CPPFLAGS="$gt_save_CPPFLAGS"
     LIBS="$gt_save_LIBS"])
  if test $have_CoreServices = yes; then
    AC_DEFINE([HAVE_COREFOUNDATION], 1,
      [Define to 1 if you have the MacOS X CoreServices Framework.])
  fi
  INTL_MACOSX_LIBS=
  if test $have_CoreServices = yes; then
    INTL_MACOSX_LIBS="-Wl,-framework -Wl,CoreServices -Wl,-framework -Wl,CoreFoundation -Wl,-framework -Wl,IOKit"
    CPPFLAGS="$CPPFLAGS -DDARWIN"
  fi
  AM_CONDITIONAL([MACOSX], [test $have_CoreServices = yes])
  AC_SUBST([INTL_MACOSX_LIBS])
])
