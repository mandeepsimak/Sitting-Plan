OBJ = seat_main.o seat_functions.o 		                       		# target
OBJ1 = input_main.o input.o
CC = g++									# compiler variable
DEBUG = -g									# debugging flag 
CFLAGS = -Wall -c $(DEBUG)							# linking flag
LFLAGS = -Wall $(DEBUG)					  	  # flag used in compiling and creating object files	

# All targets 
all: input run seat run1

# target to generate executable file.

input: $(OBJ1)
	$(CC) $(LFLAGS) $(OBJ1) -o input

seat: $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) -o seat

# target to run executable file	
run: 
	./input

run1:
	./seat

# dependencies of seat_main.cpp
input_main.o: input_main.cpp input.h
	$(CC) $(CFLAGS) input_main.cpp

# dependencies of seat_main.cpp
input.o: input.cpp input.h
	$(CC) $(CFLAGS) input.cpp

# dependencies of seat_main.cpp
seat_main.o: seat_main.cpp seat_classes.h files.h
	$(CC) $(CFLAGS) seat_main.cpp

# dependencies of seat_functions.cpp
seat_functions.o: seat_functions.cpp seat_classes.h files.h
	$(CC) $(CFLAGS) seat_functions.cpp 

# to destroy all the object and exectuable file
clean:
	rm -f *.o *.out seat input

# to create tar file 	
tar:
	tar cfv seat.tar seat_main.o seat_functions.o
