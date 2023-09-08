/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 * SPDX-License-Identifier: LGPL-2.1
 */
%{
#ifdef YYBISON
int yylex(void);
void yyerror(char *s);
#endif
%}
%token VAR NUM IF
%%
statements: statement
	| statements statement
	;
statement:	VAR '=' expr ';' { printf("xxx: %d\n", $3); }
	;
expr:	expr '+' NUM	{ $$ = $1 + $3; }
	|	 NUM	{ $$ = $1; }
	;
%%
#include <stdio.h>
#include <error.h>

extern FILE *yyin;

int main(int argc, char *argv[])
{
	if (argc > 1) {
		yyin = fopen(argv[1], "r");
	}
	return yyparse();
}

int _yylex(void);

int yylex(void)
{
	long off = yyin ? ftell(yyin) : 0;
	if (off < 0) {
		perror("");
	}
	int token = _yylex();
#ifdef YYBISON
#define yyname yytname
#endif
	printf("%5s (%3d) %3ld\n", yyname[YYTRANSLATE(token)], token, off);

	return token;
}

void yyerror(char *s)
{
        error(1, 0, "%s", s);
}
