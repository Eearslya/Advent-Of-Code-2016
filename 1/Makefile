CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
BINARY=prgm

TESTSOURCES=$(wildcard tests/*.c)
TESTOBJECTS=$(TESTSOURCES:.c=.o)
TESTBINARY=test

all: $(SOURCES) $(BINARY) cleanobj
tests: $(TESTBINARY) cleanobj cleantest
tests: CFLAGS += -DUNITTEST -coverage
tests: LDFLAGS += -lcmocka -coverage
coverage: $(BINARY) cleanobj
coverage: CFLAGS += -coverage
coverage: LDFLAGS += -coverage

$(OBJECTS): .FORCE

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

$(TESTBINARY): $(OBJECTS) $(TESTOBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(TESTOBJECTS) -g -o $@
	rm -f tests/*.gcda tests/*.gcno

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: cleanobj cleantest cleancov cleanemacs
	rm -f $(BINARY) $(TESTBINARY)

cleanobj:
	rm -f $(OBJECTS)

cleantest:
	rm -f $(TESTOBJECTS)

cleancov:
	rm -f *.gcov src/*.gcda src/*.gcno tests/*.gcno tests/*.gcda

cleanemacs:
	rm -f *~ src/*~ tests/*~

.FORCE:
