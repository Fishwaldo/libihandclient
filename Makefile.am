#ACLOCAL_AMFLAGS = -I autotools
SUBDIRS	= muscle include src test
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libihanclient.pc
EXTRA_DIST = bootstrap.sh docs/Doxyfile
docdir = ${datarootdir}/doc/${PACKAGE}-${VERSION}/
doc_DATA = README
include $(top_srcdir)/autotools/aminclude.am