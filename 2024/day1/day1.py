from collections import Counter
from pathlib import Path

def load_input(test=False):
    file_path = Path('day1', 'data', f'day1{"_test" if test else ""}.txt')
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False):
    inp = load_input(test)
    left, right = sorted([int(line.split()[0]) for line in inp]), sorted([int(line.split()[1]) for line in inp])
    return sum([abs(l - r) for l, r in zip(left, right)])

def part2(test=False):
    inp = load_input(test)
    left, right = [int(line.split()[0]) for line in inp], Counter([int(line.split()[1]) for line in inp])
    return sum([l*right[l] for l in left])

test1_correct = 11
test2_correct = 31
test = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
print(f'Part 1 answer is: {part1()}')
test = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
print(f'Part 2 answer is: {part2()}')