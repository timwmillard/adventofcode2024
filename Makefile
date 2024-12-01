
CFLAGS += -Ilibs

all: day1

day1: 1/day1.c
	$(CC) $(CFLAGS) $< -o $@

day1-run: day1 
	@./day1 1/input.txt


