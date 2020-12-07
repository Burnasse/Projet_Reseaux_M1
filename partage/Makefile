CC = gcc
CCFLAGS = -w -Wall -g

OBJ = tunalloc.o extremite.o

all : test_tunalloc test_ext_in test_ext_out

test_tunalloc: test_tunalloc.c tunalloc.o 
	$(CC) $(CCFLAGS) test_tunalloc.c -o test_tunalloc tunalloc.o
	
test_ext_in: test_ext_in.c $(OBJ)
	$(CC) $(CCFLAGS) test_ext_in.c -o test_ext_in $(OBJ)

test_ext_out: test_ext_out.c $(OBJ)
	$(CC) $(CCFLAGS) test_ext_out.c -o test_ext_out $(OBJ)

tunalloc.o : tunalloc.c
	$(CC) $(CCFLAGS) -c tunalloc.c
	
extremite.o : extremite.c
		$(CC) $(CCFLAGS) -c extremite.c

clean:
	- rm *.o
	- rm test_tunalloc
	- rm test_extremite_in
	- rm test_extremite_out