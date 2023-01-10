
set substitute-path ../../../gio src/glib/gio

file test
b g_subprocess_communicate_utf8_finish
ign 1 1
r
