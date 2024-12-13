from pathlib import Path
import re
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day13', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def calculate_tokens(a, b, loc):
    b_presses = (loc[0] * a[1] - loc[1] * a[0]) / (b[0] * a[1] - b[1] * a[0])
    if not ((int(b_presses)) == b_presses): return 0
    a_presses = (loc[0] - (b[0] * b_presses)) / (a[0])
    return int(a_presses*3 + b_presses)

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    tokens = 0
    
    while inp:
        button_a = tuple([int(m) for m in re.findall(r'(?<=[X|Y]\+)\d+', inp.pop(0))])
        button_b = tuple([int(m) for m in re.findall(r'(?<=[X|Y]\+)\d+', inp.pop(0))])
        location = tuple([int(m) for m in re.findall(r'(?<=[X|Y]=)\d+', inp.pop(0))])
        tokens += calculate_tokens(button_a, button_b, location)

    end_time = perf_counter()
    return tokens, end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    tokens = 0
    
    while inp:
        button_a = tuple([int(m) for m in re.findall(r'(?<=[X|Y]\+)\d+', inp.pop(0))])
        button_b = tuple([int(m) for m in re.findall(r'(?<=[X|Y]\+)\d+', inp.pop(0))])
        location = tuple([10000000000000 + int(m) for m in re.findall(r'(?<=[X|Y]=)\d+', inp.pop(0))])
        tokens += calculate_tokens(button_a, button_b, location)

    end_time = perf_counter()
    return tokens, end_time - start_time

test1_correct = 480
test2_correct = 875318608908
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')