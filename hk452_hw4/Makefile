CC=g++
SOURCES= main.cpp FASTAreadset_HT.cpp BLAST_DB.cpp
DEPS= FASTAreadset_HT.h BLAST_DB.h
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
