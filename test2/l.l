/* # -*-c-*- */
/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 * SPDX-License-Identifier: LGPL-2.1
 */
%{
#include "y.tab.h"
extern int yylval;
%}

%%
\$[a-z]+	return VAR;
[0-9]+		yylval = atoi(yytext); return NUM;
[ \t]		; // ignore white space
\n		return 0; // EOF
.		return yytext[0];
%%
