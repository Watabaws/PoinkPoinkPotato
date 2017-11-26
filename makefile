family_piping: pipepipe.o
	gcc -o family_piping pipepipe.o

pipepipe.o: pipepipe.c
	gcc -c pipepipe.c

run: family_piping
	./family_piping
