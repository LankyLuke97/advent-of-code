from collections import defaultdict
from functools import cmp_to_key
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day5', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    rules = defaultdict(list)
    correct_pages = 0

    for X, Y in [l.strip().split('|') for l in inp if '|' in l]:
        rules[Y].append(X)

    for update in [l.strip().split(',') for l in inp if ',' in l]:
        seen = []
        must_not_see = []
        correct = True
        for page in update:
            seen.append(page)
            if page in must_not_see:
                correct = False
                break
            if page in rules:
                for must_see in rules[page]:
                    if must_see in seen:
                        continue
                    must_not_see.append(must_see)
        if correct: correct_pages += int(update[len(update) // 2])

    end_time = perf_counter()
    return correct_pages, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 143
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')