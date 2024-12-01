
CFLAGS += -Ilibs

all: day1

run: day1-run

# Day 1

day1: 01/day1.c
	$(CC) $(CFLAGS) $< -o $@

day1-run: day1
	@./day1 01/input.txt

day1-sample: day1
	@./day1 01/sample.txt

