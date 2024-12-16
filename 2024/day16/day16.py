import heapq
import math
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day16', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    map_ = []
    start_pos = (-1,-1)
    end_pos = (-1,-1)

    for y, line in enumerate(inp):
        new_line = []
        for x, c in enumerate(line):
            if c == 'S': start_pos = (y, x)
            elif c == 'E': end_pos = (y, x)
            if c == '#': new_line.append(-1)
            else: new_line.append(0)
        map_.append(new_line)

    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    min_steps = math.inf

    open_nodes = [(0, 0, (start_pos, 1))]
    g_costs = {}
    closed_nodes = set()
    
    while open_nodes:
        f_score, g_score, (cur_position, cur_direction) = heapq.heappop(open_nodes)
        if cur_position == end_pos:
            min_steps = min(min_steps, f_score)
            continue
        if (cur_position, cur_direction) in closed_nodes: continue
        closed_nodes.add((cur_position, cur_direction))
        moves = [(1000, (cur_position, (cur_direction + 1) % 4)),
                 (1000, (cur_position, (cur_direction - 1) % 4)),
                 (1, ((cur_position[0] + directions[cur_direction][0], cur_position[1] + directions[cur_direction][1]), cur_direction))]
        for cost, move in moves:
            next_position, next_direction = move
            if move in closed_nodes or map_[next_position[0]][next_position[1]] == -1: continue
            new_g = g_score + cost
            h = abs(end_pos[0] - next_position[0]) + abs(end_pos[1] - next_position[1])
            f = new_g + h
            if move in g_costs and g_costs[move] <= new_g: continue
            g_costs[move] = new_g
            heapq.heappush(open_nodes, (f, new_g, move))

    end_time = perf_counter()
    return min_steps, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 11048
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')