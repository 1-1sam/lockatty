lockatty: main.o file.o pw.o shadow-auth.o
	cc main.o file.o pw.o shadow-auth.o -lcrypt -lcrypto -lncurses -o lockatty

main.o: main.c file.h pw.h shadow-auth.h
	cc -c main.c
pw.o: pw.c
	cc -c -lcrypto pw.c
shadow-auth.o: shadow-auth.c
	cc -c -lcrypt shadow-auth.c
file.o: file.c
	cc -c file.c