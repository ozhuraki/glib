/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: LGPL-2.1-only
 */

#include <gio/gio.h>

#include <stdio.h>
#include <stdlib.h>

#define P(fmt, args...)	do {			\
		printf(fmt "\n", ## args);	\
	} while (0)

int main(int argc, char *argv[])
{
	int exit_status = EXIT_FAILURE;
	char *command = (argc > 1) ? argv[1] : "./echo";
	GError *e = NULL;
	GSubprocess *proc = g_subprocess_new(G_SUBPROCESS_FLAGS_STDIN_PIPE |
					     G_SUBPROCESS_FLAGS_STDOUT_PIPE,
					     &e, command, NULL);
	if (e) {
		goto exit;
	}

	g_object_ref(proc);

	char *line = NULL;
	size_t line_len = 0;
	ssize_t chars_read;

	while ((chars_read = getline(&line, &line_len, stdin)) > 0) {
		const gchar *s = "aaa\n";
		s = line;

		GBytes *in = g_bytes_new(s, strlen(s)), *out = NULL;

		g_subprocess_communicate(proc, in, NULL, &out, NULL, &e);

		if (e) {
			goto exit;
		}

		{
			gsize len;
			const gchar *data = g_bytes_get_data(out, &len);
			printf("%*s", (int) len, data);
			g_bytes_unref(out);
		}

		free(line);
		line = NULL;
		line_len = 0;

		// goto exit;
	}

 exit:
	if (e) {
		P("Error: %s", e->message);
	} else {
		exit_status = EXIT_SUCCESS;
	}

	P("TEST: %s", exit_status == EXIT_SUCCESS ? "PASSED" : "FAILED");

	return exit_status;
}
