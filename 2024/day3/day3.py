from pathlib import Path
import re
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day3', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    inp = "".join([i.strip() for i in inp])
    start_time = perf_counter()
    ans = sum([int(match.split(',')[0]) * int(match.split(',')[1]) for match in re.findall(r'(?<=mul\()\d{1,3},\d{1,3}(?=\))', inp)])
    end_time = perf_counter()
    return ans, end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    inp = "".join([i.strip() for i in inp])
    start_time = perf_counter()
    instructions = re.findall(r'(?<=mul\()\d{1,3},\d{1,3}(?=\))|do\(\)|don\'t\(\)', inp)
    ans = 0
    enabled = True
    for instruction in instructions:
        if instruction == 'do()': enabled = True
        elif instruction == "don't()": enabled = False
        elif enabled: 
            instruction = instruction.split(',')
            ans += int(instruction[0]) * int(instruction[1])
    end_time = perf_counter()
    return ans, end_time - start_time

test1_correct = 161
test2_correct = 48
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(file_path=Path('day3','data','test2.txt'))
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')