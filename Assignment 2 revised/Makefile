CC=g++
CFLAGS= -std=c++11 -Wall -pedantic -g
SOURCES= main.cpp FASTAreadset_LL.cpp
DEPS= FASTAreadset_LL.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=run

all: $(EXECUTABLE)
	@echo Make has finished.

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	$(RM) *.o *~ $(EXECUTABLE)
