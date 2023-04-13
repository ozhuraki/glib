/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser-yacc.h"

extern int yylex(void);
extern char *yytext;

void yyerror(char *message)
{
	fprintf(stderr, "%s\n", message);
}

int main(int argc, char *argv[])
{
	FILE *f = (argc > 1) ? fopen(argv[1], "r") : stdin;
	int exit_status = EXIT_FAILURE;
	int r;

	while((r = yylex())) {
		printf("%d %s\n", r, yytext);
	}

 end_test:
	printf("TEST: %s\n", exit_status == EXIT_SUCCESS ? "PASSED" : "FAILED");

	return exit_status;
}
