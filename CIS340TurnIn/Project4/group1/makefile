CC=gcc -g -Wall
CFLAGS=-I.
DEPS = commands.h
OBJ = minixConsole.o commands.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
minixConsole: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
		
.PHONY: clean
clean:
	rm -f * .o minixConsole