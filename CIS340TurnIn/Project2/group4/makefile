CC=gcc -g -Wall
CFLAGS=-I.
DEPS = node.h
OBJ = main.o node.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
main: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
		
.PHONY: clean
clean:
	rm -f * .o main