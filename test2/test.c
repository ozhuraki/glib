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

	char *line = NULL;
	size_t line_len = 0;
	ssize_t chars_read;

	while ((chars_read = getline(&line, &line_len, stdin)) > 0) {
		static char in[4096];
		char *out = line;
		ssize_t len = write(fd[OUT], out, strlen(out));

		g_usleep(G_USEC_PER_SEC * 1);

		len = read(fd[IN], in, sizeof(in));

		write(fileno(stdout), in, len);

		g_clear_pointer(&line, g_free);
		line_len = 0;
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
