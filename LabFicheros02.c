CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGETS = lab01 lab02

all: $(TARGETS)

labFicheros01: labFicheros01.c
	$(CC) $(CFLAGS) labFicheros01.c -o labFicheros01

labFichero02: labFichero02.c
	$(CC) $(CFLAGS) labFichero.c -o llabFichero02

run1: labFichero01
	./labFichero01

run2: labFichero02
	./labFichero02

clean:
	rm -f $(TARGETS)

.PHONY: all clean run1 run2