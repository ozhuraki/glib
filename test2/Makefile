
CC=gcc -O0 -g

all: test echo

test: test.c
	$(CC) -o test test.c `pkg-config --cflags --libs gio-unix-2.0`

echo: echo.c
	$(CC) -o echo echo.c

clean:
	rm -fv test echo echo.log
