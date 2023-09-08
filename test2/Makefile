
YACC = yacc
LEX = flex
CFLAGS = -O0 -g

all: clean
	$(YACC) -d -t *.y
	echo '#define YY_READ_BUF_SIZE 1' >> y.tab.h
	flex l.l
	sed -i 's/^YY_DECL$$/int _yylex (void)/' *.yy.c
	$(CC) $(CFLAGS) -o x *.c -ll
	yaccviso y.y; rm -fv depgraph.vcg
	echo '$$i = 1 + 1; $$j = 2 + 2;' > in
	./x in
	echo $$?

clean:
	rm -fv x *.yy.c *.tab.[ch] *.dot *.vcg in

bison:
	$(MAKE) YACC=bison

yydebug:
	$(MAKE) YYDEBUG=1

debug-macro:
	$(MAKE) CFLAGS='-O0 -g3 -gdwarf-3 -fdebug-macro' # clang
