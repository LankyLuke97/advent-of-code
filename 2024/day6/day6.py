from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day6', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    inp = [line.strip() for line in inp if line.strip()]
    start_time = perf_counter()
    
    direction = 0
    index = [-1, -1]
    steps = [[-1, 0],[0, 1],[1, 0],[0, -1]]
    visited = set()

    for y, line in enumerate(inp):
        x = line.find('^')
        if x != -1:
            index = [y,x]
            break

    while True:
        visited.add(tuple(index))
        potential = [index[i] + steps[direction][i] for i in range(2)]
        if not 0 <= potential[0] < len(inp) or not 0 <= potential[1] < len(inp[0]):
            break
        if inp[potential[0]][potential[1]] == '#':
            direction = (direction + 1) % 4
            potential = [index[i] + steps[direction][i] for i in range(2)]
        index = potential

    end_time = perf_counter()
    return len(visited), end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 41
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')