
CFLAGS += -Ilibs

all: day1 day2 day3 day4

run: day1-run day2-run day3-run day4-run

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

# Day 3

day3: 03/day3.c
	$(CC) $(CFLAGS) $< -o $@

day3-run: day3
	@./day3 03/input.txt

day3-sample: day3
	@./day3 03/sample.txt

day3-sample2: day3
	@./day3 03/sample2.txt

# Day 4

day4: 04/day4.c
	$(CC) $(CFLAGS) $< -o $@

day4-run: day4
	@./day4 04/input.txt

day4-sample: day4
	@./day4 04/sample.txt

day4-sample2: day4
	@./day4 04/sample2.txt
