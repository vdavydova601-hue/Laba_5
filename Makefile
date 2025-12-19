Сборка файлов Makefile :

all: theater

theater: main.o theater_db.o
 gcc -o theater main.o theater_db.o

main.o: main.c theater_db.h
 gcc -c main.c

theater_db.o: theater_db.c theater_db.h
 gcc -c theater_db.c

clean:
 rm -f *.o theater





