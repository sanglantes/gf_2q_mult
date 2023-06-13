CC = gcc
CFLAGS = -Wextra -pedantic -O2 -std=c11 -fsanitize=address -o
INFILE = gf_binary_mult.c
OUTFILE = a.out
build:
	$(CC) $(INFILE) $(CFLAGS) $(OUTFILE)
clean: $(OUTFILE)
	rm $(OUTFILE) 
