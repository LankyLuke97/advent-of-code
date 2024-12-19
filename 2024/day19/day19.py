from functools import cache
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day19', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

@cache
def find_pattern(towels, pattern):
    for towel in towels:
        if pattern == towel: return 1
        if pattern.startswith(towel) and find_pattern(towels, pattern[len(towel):]): return 1
    return 0

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    possible = 0
    towels = tuple([t.strip() for t in inp[0].split(',')])
    for design in inp[1:]:
        possible += find_pattern(towels, design)

    end_time = perf_counter()
    return possible, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 6
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')