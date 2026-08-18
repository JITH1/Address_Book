CC = gcc
CFLAGS = -Wall -Wextra

Addout : main.o Options.o File.o
	$(CC) $(CFLAGS) main.o Options.o File.o -o Addout
main.o : main.c Contact.h File_handler.h
	$(CC) $(CFLAGS) -c main.c
Options.o : Options.c Contact.h File_handler.h
	$(CC) $(CFLAGS) -c Options.c
File.o : File.c Contact.h File_handler.h
	$(CC) $(CFLAGS) -c File.c

clean :
	rm -f *.o Addout
