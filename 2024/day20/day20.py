from collections import Counter
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
    def __init__(self, y, x, f, g):
        self.y = y
        self.x = x
        self.f = f
        self.g = g
    def __lt__(self, other):
        return (self.f < other.f)

def a_star(grid, start, end, min_steps=math.inf, closed_nodes=None, shortcut=None):
        directions = [(-1,0),(0,1),(1,0),(0,-1)]
        open_nodes = [start]
        closed_nodes = [[math.inf] * len(grid[0]) for _ in range(len(grid))] if not closed_nodes else closed_nodes
        
        while open_nodes:
            cur_node = heapq.heappop(open_nodes)

            if cur_node.y == end[0] and cur_node.x == end[1]: min_steps = min(min_steps, cur_node.g); continue
            if cur_node.g >= closed_nodes[cur_node.y][cur_node.x]: continue
            closed_nodes[cur_node.y][cur_node.x] = cur_node.g
            for direction in directions:
                next_position = (cur_node.y + direction[0], cur_node.x + direction[1])
                new_g = cur_node.g + 1
                if new_g >= closed_nodes[next_position[0]][next_position[1]] or grid[next_position[0]][next_position[1]]: continue
                h = abs(end[0] - next_position[0]) + abs(end[1] - next_position[1])
                f = new_g + h
                new_node = Node(next_position[0], next_position[1], f, new_g)
                heapq.heappush(open_nodes, new_node)
            if shortcut and (cur_node.y, cur_node.x) == shortcut[0]:
                next_position = shortcut[1]
                new_g = cur_node.g + shortcut[2]
                if new_g >= closed_nodes[next_position[0]][next_position[1]] or grid[next_position[0]][next_position[1]]: continue
                h = abs(end[0] - next_position[0]) + abs(end[1] - next_position[1])
                f = new_g + h
                new_node = Node(next_position[0], next_position[1], f, new_g)
                heapq.heappush(open_nodes, new_node)
        return min_steps, closed_nodes

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    grid = [[0] * len(inp[0]) for _ in range(len(inp))]
    start = end = None
    for y, line in enumerate(inp):
        for x, c in enumerate(line):
            if c == 'S': start = Node(y, x, 0, 0)
            elif c == 'E': end = (y, x)
            elif c == '#': grid[y][x] = -1
    min_path, _ = a_star(grid, start, end)
    cheats = []
    for y in range(1, len(grid)-1):
        for x in range(1, len(grid[0]) -1):
            if not grid[y][x]: continue
            if (grid[y-1][x] or grid[y+1][x]) and (grid[y][x-1] or grid[y][x+1]): continue
            grid[y][x] = 0
            cheats.append(min_path - a_star(grid, start, end, min_path)[0])
            grid[y][x] = -1
    
    cheats = sum([value for key, value in Counter([cheat for cheat in cheats if cheat]).items() if key >= 100])

    end_time = perf_counter()
    return cheats, end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    grid = [[0] * len(inp[0]) for _ in range(len(inp))]
    start = end = None
    for y, line in enumerate(inp):
        for x, c in enumerate(line):
            if c == 'S': start = Node(y, x, 0, 0)
            elif c == 'E': end = (y, x)
            elif c == '#': grid[y][x] = -1
    min_path, closed_nodes = a_star(grid, start, end)

    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    cheats = []
    for y in range(1, len(grid)-1):
        for x in range(1, len(grid[0]) -1):
            if grid[y][x]: continue
            checked_cheats = set()
            for length in range(20, 1, -1):
                for y_offset in range(-length, length + 1):
                    x_offset = length - abs(y_offset)
                    for _dir in (-1, 1):
                        cheat_start = (y+y_offset, x+(_dir*x_offset))
                        if (cheat_start) in checked_cheats: continue
                        checked_cheats.add(cheat_start)
                        if cheat_start == end:
                            cheats.append(min_path - (closed_nodes[y][x] + length))
                            continue
                        if not (0 < cheat_start[0] < len(grid) - 1 and 0 < cheat_start[1] < len(grid[0]) - 1): continue
                        if grid[cheat_start[0]][cheat_start[1]]: continue
                        _closed_nodes = deepcopy(closed_nodes)
                        _closed_nodes[cheat_start[0]][cheat_start[1]] = closed_nodes[y][x] + length
                        if _closed_nodes[cheat_start[0]][cheat_start[1]] >= closed_nodes[cheat_start[0]][cheat_start[1]]: continue
                        # cheats.append(min_path - a_star(grid, Node(cheat_start[0], cheat_start[1], 0, _closed_nodes[cheat_start[0]][cheat_start[1]]), end, min_path, _closed_nodes)[0])
                        cheats.append(min_path - a_star(grid, start, end, min_path, shortcut=((y,x),cheat_start,length))[0])
                        # if(cheats[-1]): print(f'Cheat starting at {(y,x)} and ending at {cheat_start} saves {cheats[-1]} picoseconds.')

    cheats = Counter([cheat for cheat in cheats if cheat])
    cheats = sorted([(value, key) for key, value in cheats.items()], key=lambda x: x[1])
    # for key, value in cheats: print(f'There are {key} cheats that save {value} picoseconds.')
    # cheats = sum([value for key, value in Counter([cheat for cheat in cheats if cheat]).items() if key >= 100])

    end_time = perf_counter()
    return sum([key for key, value in cheats if value >= 100]), end_time - start_time

test1_correct = 0
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
#part1_ans, part1_time = part1()
#print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')