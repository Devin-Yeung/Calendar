CC=clang
CFLAGS=-std=c99 -Wall
DEBUG=-g -fsanitize=address
main: main.c Calendar.c File.c UI.c Utils.c
	$(CC) $(CFLAGS) -g main.c Calendar.c File.c UI.c Utils.c -o main.out
	./main.out

debug: main.c Calendar.c File.c UI.c Utils.c
	$(CC) $(CFLAGS) $(DEBUG) main.c Calendar.c File.c UI.c Utils.c -o main.out
	ASAN_OPTIONS=detect_leaks=1 ./main.out

clean:
	if [ -e *.out ]; then \
		rm *.out; \
	fi
	if [ -e *.dSYM ]; then \
		rm -r *.dSYM; \
	fi
