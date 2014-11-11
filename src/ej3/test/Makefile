CC=g++
CFLAGS=-c -Wall -Werror -pedantic -O2 -std=c++0x
#-ggdb
LDFLAGS=
SOURCES=genRandom.cpp genConst.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=genRan genConst

all: $(SOURCES) $(EXECUTABLE)
	
genRan: genRandom.o
	$(CC) genRandom.o $(LDFLAGS) -o $@


genConst: genConst.o
	$(CC) genConst.o $(LDFLAGS) -o $@

genRandom.o:
	$(CC) $(CFLAGS) genRandom.cpp -o $@

genConst.o:
	$(CC) $(CFLAGS) genConst.cpp -o $@

#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
	
