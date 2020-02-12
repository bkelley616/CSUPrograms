CC=gcc -g -Wall
CFLAGS=-I.
DEPS = myls.h stringout.h
OBJ = myls.o stringout.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
myls: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
		
.PHONY: clean
clean:
	rm -f * .o myls