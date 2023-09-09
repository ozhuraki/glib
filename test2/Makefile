# python3-jsondiff

all: clean
	$(CC) $(CFLAGS) -o x main.c `pkg-config --cflags --libs json-glib-1.0`
	echo -n "@a{sv} { 'a': <1> }" > in
	./x in
	echo -n "@a{sv} { 'b': <2> }" > delta
	./x in stdout delta > out.json
	./x in in.json
	echo $$(jsondiff-jsondiff in.json out.json)

clean:
	rm -fv x in out delta *.json
