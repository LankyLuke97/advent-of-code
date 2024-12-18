import math
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day18', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    max_coord = 7 if test else 71
    b = 12 if test else 1024
    grid = [[0] * max_coord for _ in range(max_coord)]

    for l in inp[:b]:
        x, y = l.split(',')
        grid[int(y)][int(x)] = -1
    search = [(0, 0, 0)]
    visited = {}
    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    min_dist = math.inf
    while search:
        y, x, steps = search.pop(0)
        if steps >= min_dist: continue
        if (y, x) == (max_coord-1, max_coord-1): min_dist = steps
        if (y, x) in visited and visited[(y, x)] <= steps: continue
        visited[y, x] = steps
        for y_off, x_off in directions:
            _y, _x = y+y_off, x+x_off
            if not(0 <= _y < max_coord and 0 <= _x < max_coord): continue
            if grid[_y][_x]: continue
            
            search.append((_y, _x, steps + 1))

    end_time = perf_counter()
    return min_dist, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 22
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')