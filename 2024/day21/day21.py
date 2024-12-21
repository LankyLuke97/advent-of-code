from functools import cache
import math
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day21', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]
    
number_pad = [
    "789",
    "456",
    "123",
    "X0A"
]
directional_pad = [
    "X^A",
    "<v>"
]
directions = [((-1,0),'^'),((0,1),'>'),((1,0),'v'),((0,-1),'<')]

@cache
def steps(start, end, layer, num_layers):
    if layer == 0: return 1
    grid = directional_pad if layer != num_layers else number_pad
    min_path = 1000
    paths = []
    cur_pos = None
    for y, l in enumerate(grid):
        for x, c in enumerate(l):
            if c == start: cur_pos = (y, x); break
        if cur_pos: break
    search = [("",cur_pos)]
    while search:
        path, pos = search.pop(0)
        if len(path) > min_path: continue
        if grid[pos[0]][pos[1]] == end: 
            path += 'A'
            paths.append(path)
            min_path = len(path)
            continue
        for direction,c in directions:
            next_pos = (pos[0]+direction[0], pos[1]+direction[1])
            if not (0 <= next_pos[0] < len(grid) and 0 <= next_pos[1] < len(grid[0])) or grid[next_pos[0]][next_pos[1]] == 'X': continue
            search.append((path+c, next_pos))
            
    paths = ['A' + path for path in paths if len(path) <= min_path]
    costs = []
    for path in paths:
        #print(f'Checking {path}')
        cost = 0
        for _start, _end in zip(path[:-1], path[1:]):
            _cost = steps(_start, _end, layer-1, num_layers)
            #print(f'Cost to move from {_start} -> {_end} in {path} is {_cost}')
            cost += _cost
        costs.append((cost, path))
    print(f'At level {layer}, the min path is {min(costs,key=lambda x: x[0])[1]}')
    return min(costs,key=lambda x: x[0])[0]
    min_cost = min(sum([steps(_start, _end, layer-1, num_layers) for path in paths for _start, _end in zip(path[:-1],path[1:])]))
    return min_cost

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    complexity = 0
    for line in inp:
        for start, end in zip(line[:-1], line[1:]):
            s = steps(start,end,3,3)
            i = int(line[:-1])
            print(f'Moving from {start} to {end} took {s} instructions')
            print(f'Adding {s} * {i} ({s*i}) to {complexity} for {complexity + (s*i)}')
            complexity += s*i
    #complexity = sum([steps(start,end,3,3) * int(line[:-1]) for line in inp for start, end in zip(line[:-1], line[1:])])

    end_time = perf_counter()
    return complexity, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 126384
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')