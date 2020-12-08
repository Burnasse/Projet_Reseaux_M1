CC = gcc
CCFLAGS = -w -Wall -g

OBJ = iftun.o extremite.o

all : test_iftun test_ext_in test_ext_out

test_iftun: test_iftun.c iftun.o 
	$(CC) $(CCFLAGS) test_iftun.c -o test_iftun iftun.o
	
test_ext_in: test_ext_in.c $(OBJ)
	$(CC) $(CCFLAGS) test_ext_in.c -o test_ext_in $(OBJ)

test_ext_out: test_ext_out.c $(OBJ)
	$(CC) $(CCFLAGS) test_ext_out.c -o test_ext_out $(OBJ)

iftun.o : iftun.c
	$(CC) $(CCFLAGS) -c iftun.c
	
extremite.o : extremite.c
		$(CC) $(CCFLAGS) -c extremite.c

clean:
	- rm *.o
	- rm test_iftun
	- rm test_extremite_in
	- rm test_extremite_out