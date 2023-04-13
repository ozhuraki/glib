AC_INIT([test], [0.1])

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([gobject.c])

AM_INIT_AUTOMAKE([foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_CC
AM_PROG_LEX
AC_PROG_YACC

PKG_CHECK_MODULES([DEPS], [glib-2.0, gobject-2.0, json-glib-1.0],
	AC_SUBST([DEPS_CFLAGS])
	AC_SUBST([DEPS_LIBS]),
	AC_MSG_ERROR([sudo apt install libglib2.0-dev libjson-glib-dev]))

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
