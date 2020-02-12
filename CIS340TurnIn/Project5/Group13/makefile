CC=gcc -g -Wall
CFLAGS=-I.
DEPS =
OBJ = shell.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
shell: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
		
.PHONY: clean
clean:
	rm -f * .o shell