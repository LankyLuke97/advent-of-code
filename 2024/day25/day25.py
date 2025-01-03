from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day25', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    keys, locks = [], []

    for idx in range(int(len(inp) / 7)):
        group = inp[idx*7:(idx+1)*7]
        schematic = [col.count('#') for col in list(map(list, zip(*group)))]
        if group[0][0] == '#': locks.append(schematic)
        else: keys.append(schematic)

    possible = 0
    for key in keys:
        for lock in locks:
            if any([(a+b)>7 for a, b in zip(key, lock)]): continue
            possible += 1

    end_time = perf_counter()
    return possible, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 3
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')