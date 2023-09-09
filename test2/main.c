/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 * SPDX-License-Identifier: LGPL-2.1
 */

#include <stdio.h>
#include <json-glib/json-glib.h>

enum { IN, OUT, DELTA };
FILE *f[3];
char *buf;
long size;
GVariant *v0, *v;

void load(FILE *f)
{
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buf = malloc(size + 1);
	fread(buf, size, 1, f);
	buf[size] = '\0';
	if (buf[size - 1] == '\n') {
		buf[--size] = '\0';
	}
	v = g_variant_new_parsed(buf);
}

void save(FILE *f)
{
	unsigned long size = size;
	buf = json_gvariant_serialize_data(v, &size);
	fprintf(f, "%*s\n", (int) size, buf);
}

void delta(void)
{
	GVariantIter i;
	char *key;
	GVariant *val;
	GVariantBuilder *b = g_variant_builder_new(G_VARIANT_TYPE("a{sv}"));
	for (g_variant_iter_init(&i, v0);
	     g_variant_iter_loop(&i, "{sv}", &key, &val);
	     g_variant_builder_add(b, "{sv}", key, val));
	for (g_variant_iter_init(&i, v);
	     g_variant_iter_loop(&i, "{sv}", &key, &val);
	     g_variant_builder_add(b, "{sv}", key, val));
	v = g_variant_builder_end(b);
}

int main(int argc, char *argv[])
{
	f[IN]    = argc > 1 && strcmp(argv[1], "stdin") ? fopen(argv[1], "r") : stdin;
	f[OUT]   = argc > 2 && strcmp(argv[2], "stdout") ? fopen(argv[2], "w") : stdout;
	f[DELTA] = (argc > 3) ? fopen(argv[3], "r") : NULL;

	load(f[IN]);

	if (f[DELTA]) {
		v0 = v;
		load(f[DELTA]);
		delta();
	}

	save(f[OUT]);

	return 0;
}
