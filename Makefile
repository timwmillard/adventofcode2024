
CFLAGS += -Ilibs

all: day1 day2

run: day1-run day2-run

# Day 1

day1: 01/day1.c
	$(CC) $(CFLAGS) $< -o $@

day1-run: day1
	@./day1 01/input.txt

day1-sample: day1
	@./day1 01/sample.txt

# Day 2

day2: 02/day2.c
	$(CC) $(CFLAGS) $< -o $@

day2-run: day2
	@./day2 02/input.txt

day2-sample: day2
	@./day2 02/sample.txt

