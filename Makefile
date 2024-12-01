
CFLAGS += -Ilibs

all: day1_part1 day1_part2

.PHONY: day1 day1-run

day1: day1_part1 day1_part2

day1-run: day1_part1-run day1_part2-run

day1_part1: 1/day1_part1.c
	$(CC) $(CFLAGS) $< -o $@

day1_part2: 1/day1_part2.c
	$(CC) $(CFLAGS) $< -o $@

day1_part1-run: day1_part1
	@./day1_part1 1/input.txt

day1_part2-run: day1_part2
	@./day1_part2 1/input.txt


