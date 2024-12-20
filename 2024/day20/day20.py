from copy import deepcopy
import heapq
import math
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day20', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

class Node:
    def __init__(self, y, x, parent, f, g):
        self.y = y
        self.x = x
        self.parent = parent
        self.f = f
        self.g = g
    def __lt__(self, other):
        return (self.f < other.f)

def a_star(grid, start, end):
    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    open_nodes = [start]
    closed_nodes = [[math.inf] * len(grid[0]) for _ in range(len(grid))]
    min_steps = math.inf
    end_node = None
    
    while open_nodes:
        cur_node = heapq.heappop(open_nodes)

        if cur_node.y == end[0] and cur_node.x == end[1]:
            end_node = cur_node
            break
        
        if cur_node.g >= closed_nodes[cur_node.y][cur_node.x]: continue
        closed_nodes[cur_node.y][cur_node.x] = cur_node.g
        for direction in directions:
            next_position = (cur_node.y + direction[0], cur_node.x + direction[1])
            new_g = cur_node.g + 1
            if new_g >= closed_nodes[next_position[0]][next_position[1]] or grid[next_position[0]][next_position[1]]: continue
            h = abs(end[0] - next_position[0]) + abs(end[1] - next_position[1])
            f = new_g + h
            new_node = Node(next_position[0], next_position[1], cur_node, f, new_g)
            heapq.heappush(open_nodes, new_node)

    path = []
    cur_node = end_node

    while cur_node:
        path.append((cur_node.y, cur_node.x))
        cur_node = cur_node.parent
    return min_steps, path[::-1]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    dist = 10 if test else 100

    grid = [[0] * len(inp[0]) for _ in range(len(inp))]
    start = end = None
    for y, line in enumerate(inp):
        for x, c in enumerate(line):
            if c == 'S': start = Node(y, x, None, 0, 0)
            elif c == 'E': end = (y, x)
            elif c == '#': grid[y][x] = -1
    _, path = a_star(grid, start, end)
    cheats = 0
    for i, (y, x) in enumerate(path[:-dist]):
        potential = {(y-2, x), (y, x+2), (y+2, x), (y, x-2)}
        cheats += sum([1 for (c_y, c_x) in path[i+dist+2:] if (c_y, c_x) in potential])

    end_time = perf_counter()
    return cheats, end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    grid = [[0] * len(inp[0]) for _ in range(len(inp))]
    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    start = end = None
    for y, line in enumerate(inp):
        for x, c in enumerate(line):
            if c == 'S': start = Node(y, x, None, 0, 0)
            elif c == 'E': end = (y, x)
            elif c == '#': grid[y][x] = -1
    _, path = a_star(grid, start, end)
    path_set = set(path)

    dist = 70 if test else 100

    cheats = 0
    cheat_amounts = []
    for i, (y, x) in enumerate(path[:-dist]):
        potential = {}
        for length in range(20, 1, -1):
            for y_offset in range(-length, length + 1):
                x_offset = length - abs(y_offset)
                for _dir in (-1, 1):
                    if (y+y_offset, x+(_dir*x_offset)) not in path_set: continue
                    potential[(y+y_offset, x+(_dir*x_offset))] = length
        for j, (c_y, c_x) in enumerate(path[i+dist:]):
            if (c_y, c_x) not in potential: continue
            if j - potential[(c_y, c_x)] >= 0: cheats += 1
    end_time = perf_counter()
    return cheats, end_time - start_time

test1_correct = 10
test2_correct = 41
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')