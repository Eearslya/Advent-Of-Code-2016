CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
BINARY=prgm

all: $(SOURCES) $(BINARY) cleanobj

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

valgrind: $(BINARY)
	valgrind --tool=memcheck --leak-check=full -q ./$(BINARY)

clean: cleanobj cleanemacs
	rm -f $(BINARY)

cleanobj:
	rm -f $(OBJECTS)

cleanemacs:
	rm -f *~ src/*~ tests/*~
