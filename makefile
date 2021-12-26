main: main.c Calendar.c File.c UI.c Utils.c
	gcc main.c Calendar.c File.c UI.c Utils.c -o main.out
	./main.out

debug: main.c Calendar.c File.c UI.c Utils.c
	gcc -g main.c Calendar.c File.c UI.c Utils.c -o main.out
	lldb main.out

clean:
	rm *.out
	rm -r *.dSYM