from pathlib import Path
import re
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day4', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    X = 'XMAS'
    _X = 'SAMX'
    forward = [l.strip() for l in inp]
    down = ["".join([l[i] for l in forward]) for i in range(len(forward[0]))]
    left_right_diag = []
    for i in range(len(forward) - 3):
        str_top = ""
        j = i
        while j < len(forward) and j < len(forward[0]):
            str_top += forward[j-i][j]
            j += 1
        left_right_diag.append(str_top)
        if not i:
            continue
        str_side = ""
        j = i
        while j < len(forward) and j < len(forward[0]):
            str_side += forward[j][j-i]
            j += 1
        left_right_diag.append(str_side)

    right_left_diag = []
    for i in range(3, len(forward)):
        str_top = ""
        x = i
        y = 0
        while x >= 0 and y < len(forward):
            str_top += forward[y][x]
            x -= 1
            y += 1
        right_left_diag.append(str_top)
        if i == len(forward) - 1:
            continue
        str_side = ""
        x = len(forward[0]) - 1
        y = len(forward) - i - 1
        while x >= 0 and y < len(forward):
            str_side += forward[y][x]
            x -= 1
            y += 1
        right_left_diag.append(str_side)

    ans = (sum([l.count(X) for l in forward]) +
          sum([l.count(_X) for l in forward]) +
          sum([l.count(X) for l in down]) +
          sum([l.count(_X) for l in down]) + 
          sum([l.count(X) for l in left_right_diag]) +
          sum([l.count(_X) for l in left_right_diag]) + 
          sum([l.count(X) for l in right_left_diag]) +
          sum([l.count(_X) for l in right_left_diag]))
    end_time = perf_counter()
    return ans, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 18
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')