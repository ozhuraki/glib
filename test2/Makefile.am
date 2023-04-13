
AM_CFLAGS = @DEPS_CFLAGS@
LDADD = @DEPS_LIBS@ -lfl

AM_YFLAGS = -d

bin_PROGRAMS = parser scanner gobject

BUILT_SOURCES = parser-yacc.h parser-yacc.c scanner-lex.c

scanner_SOURCES = scanner.c scanner-lex.l parser-yacc.y

parser_SOURCES = parser.c scanner-lex.l parser-yacc.y

gobject_SOURCES = gobject.c
gobject_LDADD = @DEPS_LIBS@

TESTS = \
	tests/scanner-01.txt \
	tests/parser-01.txt

LOG_COMPILER = $(srcdir)/tests/test-wrapper.sh

MAINTAINERCLEANFILES = Makefile.in \
	aclocal.m4 compile configure config.guess config.sub depcomp missing \
	install-sh ltmain.sh test-driver ylwrap

maintainer-clean-local:
	-rm -rf m4 .deps

clean-local:
	-rm $(BUILT_SOURCES)
