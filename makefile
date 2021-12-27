main: main.c Calendar.c File.c UI.c Utils.c
	gcc -std=c99 main.c Calendar.c File.c UI.c Utils.c -o main.out
	./main.out

debug: main.c Calendar.c File.c UI.c Utils.c
	gcc -std=c99 -g main.c Calendar.c File.c UI.c Utils.c -o main.out
	lldb main.out

clean:
	if [ -e *.out ]; then \
		rm *.out; \
	fi
	if [ -e *.dSYM ]; then \
		rm -r *.dSYM; \
	fi