CC=g++
CFLAGS= -std=c++11
SOURCES = Implementations.cpp main.cpp trie_node.cpp prefix_trie.cpp
DEPS= Implementations.h trie_node.h prefix_trie.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all:$(EXECUTABLE)
	@echo Finished!

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) 	-c $*.cpp

clean:

	$(RM) *.o *~ $(EXECUTABLE)
