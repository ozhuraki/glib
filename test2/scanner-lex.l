/* # -*-c-*- */
/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 */
%{
#include "parser-yacc.h"
%}

%%

\$[a-z]+ { yylval = atoi(yytext); return NUM; }
[0-9]+	{ yylval = yytext; return ID; }
.|\n	{ }

%%
