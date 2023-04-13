/*
 * Copyright © 2023, Intel Corporation.
 * SPDX-License-Identifier: ISC
 */

#include <glib-object.h>
#include <json-glib/json-glib.h>

#define TEST_TYPE_OBJECT test_object_get_type()
G_DECLARE_DERIVABLE_TYPE(TestObject, test_object, TEST, OBJECT, GObject)

struct _TestObjectClass {
	GObjectClass parent_class;
};

struct TestObject {
	GObject parent_instance;
};

G_DEFINE_TYPE(TestObject, test_object, G_TYPE_OBJECT)

void test_object_class_init(TestObjectClass *c) { }
void test_object_init(TestObject *o) { }

int main(int argc, char *argv[])
{
	void *obj = g_object_new(TEST_TYPE_OBJECT, NULL);
	gsize len;
	char *s = json_gobject_to_data(G_OBJECT(obj), &len);

	printf("%s\n", s);

	return 0;
}
