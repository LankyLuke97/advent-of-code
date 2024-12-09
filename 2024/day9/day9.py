from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day9', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = [int(i) for i in list(load_input(test, file_path)[0].strip())]
    start_time = perf_counter()
    front_file = 0
    back_file = len(inp)//2
    current_back_blocks = inp.pop()
    current_unit = 0
    checksum = 0

    while inp:
        for _ in range(inp.pop(0)):
            checksum += (front_file * current_unit)
            current_unit += 1
        if not inp:
            break
        front_file += 1
        empty_space = inp.pop(0)
        while empty_space and (current_back_blocks or inp):
            if current_back_blocks == 0:
                inp.pop()
                current_back_blocks = inp.pop()
                back_file -= 1
            checksum += (back_file * current_unit)
            current_back_blocks -= 1
            empty_space -= 1
            current_unit += 1

    while current_back_blocks:
        checksum += (back_file * current_unit)
        current_back_blocks -= 1
        current_unit += 1

    end_time = perf_counter()
    return checksum, end_time - start_time

def part2(test=False, file_path=None):
    inp = [int(i) for i in list(load_input(test, file_path)[0].strip())]
    start_time = perf_counter()
    inp = [[i, ind // 2 if ind % 2 == 0 else -1] for ind, i in enumerate(inp)]
    file_pointer = len(inp) - 1

    while file_pointer > 0:
        num_blocks, file_id = inp[file_pointer]
        empty_pointer = 1
        while empty_pointer < file_pointer and inp[empty_pointer][0] < num_blocks:
            empty_pointer += 2
        if empty_pointer < file_pointer:
            inp[empty_pointer][0] -= num_blocks
            inp.pop(file_pointer)
            inp.insert(file_pointer, [num_blocks, -1])
            inp.insert(empty_pointer, [num_blocks, file_id])
            inp.insert(empty_pointer, [0, -1])
        else:
            file_pointer -= 2

    current_unit = 0
    checksum = 0

    while inp:
        num_blocks, file_id = inp.pop(0)
        if file_id == -1 or not num_blocks:
            current_unit += num_blocks
            continue
        for _ in range(num_blocks):
            checksum += (file_id * current_unit)
            current_unit += 1

    end_time = perf_counter()
    return checksum, end_time - start_time

test1_correct = 1928
test2_correct = 2858
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')