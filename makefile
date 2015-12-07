CC = gcc
CFLAGS = -g -Wall -pthread -pedantic -std=gnu99
LDFLAGS = -pthread
SOURCES = main.c dirtravers.c getoption.c worklist.c threading.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = mfind_p

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@


.c.h.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
