output: computer.o memory.o shell.o cpu.o load.o
	gcc computer.o memory.o shell.o cpu.o load.o -o computer.exe

main.o: computer.c computer.h
	gcc -c computer.c

memory.o: memory.c
	gcc -c memory.c

shell.o: shell.c
	gcc -c shell.c

cpu.o: cpu.c
	gcc -c cpu.c

load.o: load.c
	gcc -c load.c

clean:
	rm *o computer.exe