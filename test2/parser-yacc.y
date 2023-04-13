/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 */
%{
%}

%token ID NUM

%%

expr:
	ID
	| NUM
	| expr '+' expr
	| expr '=' expr
	;

%%
