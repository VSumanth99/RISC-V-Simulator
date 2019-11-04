CC = gcc
CFLAGS = -std=c99
SRC_FILES = main.c instruc_utils.c instruc_exec.c
EXEC = riscsimul

all:
	$(CC) $(SRC_FILES) $(CFLAGS) -o $(EXEC)

clean:
	rm $(EXEC)
