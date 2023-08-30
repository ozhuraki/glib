/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 * SPDX-License-Identifier: LGPL-2.1
 */
// %{
// %}

%token VAR NUM

%%
statement:	VAR '=' expr ';' { printf("xxx: %d\n", $3); }
	;

expr:	expr '+' NUM	{ $$ = $1 + $3; }
	|	 NUM	{ $$ = $1; }
	;
%%

#include <stdio.h>
#include <error.h>

int main(int argc, char *argv[])
{
	yyparse();

	return 0;
}

void yyerror(char *s)
{
	error(1, 0, "%s", s);
}

int _yylex(void);

int yylex(void)
{
	int token = _yylex();

	char *s = yyname[YYTRANSLATE(token)];

	if (s) {
		printf("%s (%d)\n", s, token);
	} else {
		printf("'%c' (%d)\n", (char) token, token);
	}

	return token;
}
