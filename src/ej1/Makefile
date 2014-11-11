CC=g++
CFLAGS=-c -Wall -Werror -pedantic -O2 -std=c++0x
#-ggdb
LDFLAGS=-lrt
SOURCES=problema1.cpp jugador.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=problema1

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

genRan.o: genRandom.cpp
	$(CC) $(CFLAGS) genRandom.cpp -o genRan.o

genRan: genRan.o
	$(CC) genRan.o $(LDFLAGS) -o genRan

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
	
