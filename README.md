# Advent of Code 2025: (C)asually (c)omputing C-(C)ode (C4)
Fun with the advent of code 2025. This is me just experimenting around in C. Next year Rust?
Binaries were compiled on M1 Max MacOS Tahoe 26.1.

## Solutions (so far)
Can be wrong.

### Day 1
1. password: 989
2. password pt. 2: 5941

### Day 2
1. final sum: 38158151648
2. final sum pt. 2: 45283684555

### Day 3:
1. final sum: 17427
2. final sum pt. 2: 173161749617495

### Day 4:
1. final sum: 1553
2. final sum pt.2 : 8442

### Day 5:
1. final sum: 661
2. final sum pt.2: 359526404143208

### Day 6:
1. final sum: 5381996914800
2. final sum pt.2: 9627174150897

### Day 7:
1. final sum: 1602
2. final sum pt.2: 135656430050438

### Day 8:
1. final sum: 112230
2. final sum pt.2: 2573952864

### Day 9:
1. final sum: 4745816424
2. final sum pt.2: 1351617690

### Day 10:
1. final sum: 399
2. final sum pt.2: 15631

### Day 11:
1. final sum: 539
2. final sum pt.2: 413167078187872

## Highlights
Some of my AoC journey:
* Day 10 / Part 2 almost broke my spite, I was trying to brute-force the solution using a linear approximation. For some reason, the first 10 state machines were solving just fine, but the 11th machine was not bruteforceable or did not convolute in a static median. I let this bruteforcing algorithm run for three days (dec 23th-dec 25th) and could not find a solution for the 11th machine onewards. Then used a approch similar to what I would expect Z3 to do in this case and do a rational gaussian elimination approch.
* I would really like to write a small visulation of Day 7 (day-7-laboratories/decoder.c) to show a wavefront-like picture-by-picture solving. Maybe later :-)


## Learnings of AoC '25
As this was my first AoC, I want to write down some learnings for the future.

* Benchmarking with hyperfine ./{EXECUTABLE} -N --warmup 50 --min-runs 100
