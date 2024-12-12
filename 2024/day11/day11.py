from functools import cache
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day11', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    @cache
    def apply_rule(n):
        if n == 0: return [1]
        str_n = str(n)
        if len(str_n) % 2 == 0: return [int(str_n[:len(str_n) // 2]), int(str_n[len(str_n) // 2:])]
        return [n * 2024]

    @cache
    def transform(stone, depth):
        if not depth: return 1
        transformed = apply_rule(stone)
        return sum(transform(s, depth - 1) for s in transformed)

    inp = [int(i) for line in load_input(test, file_path) for i in line.split()]
    start_time = perf_counter()
    stones = sum(transform(stone, 25) for stone in inp)
    
    end_time = perf_counter()
    return stones, end_time - start_time

def part2(test=False, file_path=None):
    @cache
    def apply_rule(n):
        if n == 0: return [1]
        str_n = str(n)
        if len(str_n) % 2 == 0: return [int(str_n[:len(str_n) // 2]), int(str_n[len(str_n) // 2:])]
        return [n * 2024]

    @cache
    def transform(stone, depth):
        if not depth: return 1
        transformed = apply_rule(stone)
        return sum(transform(s, depth - 1) for s in transformed)

    inp = [int(i) for line in load_input(test, file_path) for i in line.split()]
    start_time = perf_counter()
    stones = sum(transform(stone, 75) for stone in inp)
    
    end_time = perf_counter()
    return stones, end_time - start_time

test1_correct = 55312
test2_correct = 65601038650482
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')