/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: LGPL-2.1-only
 */

#include <gio/gio.h>
#include <gio/gunixinputstream.h>
#include <gio/gunixoutputstream.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P(fmt, args...)	do {			\
		printf(fmt "\n", ## args);	\
	} while (0)

void msg_dump(void *data, ssize_t len)
{
	ssize_t i;
	for (i = 0; i < len; i++) {
		printf("%02x ", ((unsigned char *) data)[i]);
	}
	printf("\n");
}

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

	enum { IN = 0, OUT };
	int fd[] = {
		    g_unix_input_stream_get_fd(G_UNIX_INPUT_STREAM(g_subprocess_get_stdout_pipe(proc))),
		    g_unix_output_stream_get_fd(G_UNIX_OUTPUT_STREAM(g_subprocess_get_stdin_pipe(proc)))
	};
	char *data[] = { "a\n", "bc\n", "def\n" }, in[13];

	char *line = NULL;
	size_t line_len = 0;

	for (int i = 0; i < 3; i++) { /*(chars_read = getline(&line, &line_len, stdin)) > 0*/
		char *out = data[i];
		ssize_t len = write(fd[OUT], out, strlen(out));

		len = read(fd[IN], in, sizeof(in));
		msg_dump(in, len);
		printf("%*s", (int) len, in);

		/* g_clear_pointer(&line, g_free); */
		/* line_len = 0; */
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
