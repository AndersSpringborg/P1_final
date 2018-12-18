
program: input.o output.o algoritme.o
	gcc input.o output.o algoritme.o main.c -o program


input.o: input.c
	gcc -c input.c

output.o: output.c
	gcc -c output.c

algoritme.o: algoritme.c
	gcc -c algoritme.c

clean:
	rm *.o program
