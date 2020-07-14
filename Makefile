CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o sdl_hello main.c `pkg-config sdl2 --libs --cflags`
stable:clean
	$(CC) $(CFLAGS) -o sdl_hello main.c `pkg-config sdl2 --libs --cflags`
clean:
	rm -vfr *~ sdl_hello
run:stable
	./sdl_hello
