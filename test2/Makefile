
YACC = yacc

all: clean
	$(YACC) -d -t y.y
	flex l.l
	sed -i 's/^YY_DECL$$/int _yylex (void)/' lex.yy.c
	$(CC) $(CFLAGS) -o x lex.yy.c y.tab.c -ll
	echo '$$i = 1 + 1;' | ./x; echo $$?

clean:
	rm -fv x *.yy.c *.tab.[ch]
