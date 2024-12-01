
all: day1

day1: 1/day1.c
	$(CC) $(CFLAGS) $< -o $@

