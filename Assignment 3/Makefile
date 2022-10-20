CC=g++
SOURCES= main.cpp FASTAreadset_HT.cpp
DEPS= FASTAreadset_HT.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(EXECUTABLE)
	@echo

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) -c $*.cpp

clean:
	$(RM) *.o *~ $(EXECUTABLE)
