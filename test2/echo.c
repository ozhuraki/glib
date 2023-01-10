/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: LGPL-2.1-only
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t line_len = 0;
	ssize_t chars_read;
	FILE *fp = fopen("echo.log", "w+");

	while ((chars_read = getline(&line, &line_len, stdin)) > 0) {

		fprintf(fp, "%s", line);
		fflush(fp);
		printf("%s", line);
		fprintf(stdout, "%s", line);
		fflush(stdout);

		free(line);
		line = NULL;
		line_len = 0;
	}

	return 0;
}
