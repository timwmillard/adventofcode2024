
CFLAGS += -Ilibs

all: day1_part1 day1_part2

.PHONY: day1 day1-run

# Day 1

day1: day1_part1 day1_part2

day1-run: day1_part1-run day1_part2-run

day1_part1: 01/day1_part1.c
	$(CC) $(CFLAGS) $< -o $@

day1_part2: 01/day1_part2.c
	$(CC) $(CFLAGS) $< -o $@

day1_part1-run: day1_part1
	@./day1_part1 01/input.txt

day1_part2-run: day1_part2
	@./day1_part2 01/input.txt


