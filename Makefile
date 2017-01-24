.PHONY: all clean

all:
	mkdir -p bin
	gcc -std=gnu99 -o bin/main main.c -ldl
	gcc -std=gnu99 -shared -fPIC -o bin/plugin-hello.so plugin-hello.c
	gcc -std=gnu99 -shared -fPIC -o bin/plugin-world.so plugin-world.c

clean:
	rm -rf bin
