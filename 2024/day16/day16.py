import heapq
from functools import reduce
import os
import math
from pathlib import Path
from time import perf_counter, sleep

def load_input(test=False, file_path=None):
    file_path = Path(f'day16', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]
    
class Node:
    def __init__(self, y, x, direction, parent, f, g):
        self.y = y
        self.x = x
        self.direction = direction
        self.parent = parent
        self.f = f
        self.g = g
    def __lt__(self, other):
        return (self.f < other.f)

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    map_ = []
    start_node = None
    end_pos = None

    for y, line in enumerate(inp):
        new_line = []
        for x, c in enumerate(line):
            if c == 'S': start_node = Node(y, x, 1, None, 0, 0)
            elif c == 'E': end_pos = (y, x)
            if c == '#': new_line.append(-1)
            else: new_line.append(0)
        map_.append(new_line)

    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    min_steps = math.inf

    open_nodes = [start_node]
    closed_nodes = [[[math.inf for _ in range(len(directions))] for _ in range(len(map_[0]))] for _ in range(len(map_))]
    visited = {}
    
    while open_nodes:
        cur_node = heapq.heappop(open_nodes)

        if cur_node.y == end_pos[0] and cur_node.x == end_pos[1]:
            min_steps = min(min_steps, cur_node.g)
            continue
        if cur_node.g >= closed_nodes[cur_node.y][cur_node.x][cur_node.direction]: continue
        closed_nodes[cur_node.y][cur_node.x][cur_node.direction] = cur_node.g
        moves = [(1001, ((cur_node.y + directions[(cur_node.direction + 1) % 4][0], cur_node.x + directions[(cur_node.direction + 1) % 4][1]), (cur_node.direction + 1) % 4)),
                 (1001, ((cur_node.y + directions[(cur_node.direction - 1) % 4][0], cur_node.x + directions[(cur_node.direction - 1) % 4][1]), (cur_node.direction - 1) % 4)),
                 (1, ((cur_node.y + directions[cur_node.direction][0], cur_node.x + directions[cur_node.direction][1]), cur_node.direction))]
        for cost, (next_position, next_direction) in moves:
            new_g = cur_node.g + cost
            if new_g >= closed_nodes[next_position[0]][next_position[1]][next_direction] or map_[next_position[0]][next_position[1]] == -1: continue
            h = abs(end_pos[0] - next_position[0]) + abs(end_pos[1] - next_position[1])
            f = new_g + h
            new_node = Node(next_position[0], next_position[1], next_direction, None, f, new_g)
            heapq.heappush(open_nodes, new_node)

    end_time = perf_counter()
    return min_steps, end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    map_ = []
    start_node = None
    end_pos = None

    for y, line in enumerate(inp):
        new_line = []
        for x, c in enumerate(line):
            if c == 'S': start_node = Node(y, x, 1, None, 0, 0)
            elif c == 'E': end_pos = (y, x)
            if c == '#': new_line.append(-1)
            else: new_line.append(0)
        map_.append(new_line)

    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    min_steps = math.inf

    open_nodes = [start_node]
    closed_nodes = [[[math.inf for _ in range(len(directions))] for _ in range(len(map_[0]))] for _ in range(len(map_))]
    visited = {}
    
    while open_nodes:
        cur_node = heapq.heappop(open_nodes)

        if cur_node.y == end_pos[0] and cur_node.x == end_pos[1]:
            min_steps = min(min_steps, cur_node.g)
            path_cost = cur_node.g
            if path_cost not in visited:
                visited[path_cost] = set()
            while cur_node:
                visited[path_cost].add((cur_node.y, cur_node.x))
                cur_node = cur_node.parent
            continue
        if cur_node.g > closed_nodes[cur_node.y][cur_node.x][cur_node.direction]: continue
        closed_nodes[cur_node.y][cur_node.x][cur_node.direction] = cur_node.g
        moves = [(1001, ((cur_node.y + directions[(cur_node.direction + 1) % 4][0], cur_node.x + directions[(cur_node.direction + 1) % 4][1]), (cur_node.direction + 1) % 4)),
                 (1001, ((cur_node.y + directions[(cur_node.direction - 1) % 4][0], cur_node.x + directions[(cur_node.direction - 1) % 4][1]), (cur_node.direction - 1) % 4)),
                 (1, ((cur_node.y + directions[cur_node.direction][0], cur_node.x + directions[cur_node.direction][1]), cur_node.direction))]
        for cost, (next_position, next_direction) in moves:
            new_g = cur_node.g + cost
            if new_g > closed_nodes[next_position[0]][next_position[1]][next_direction] or map_[next_position[0]][next_position[1]] == -1: continue
            h = abs(end_pos[0] - next_position[0]) + abs(end_pos[1] - next_position[1])
            f = new_g + h
            new_node = Node(next_position[0], next_position[1], next_direction, cur_node, f, new_g)
            heapq.heappush(open_nodes, new_node)

    end_time = perf_counter()
    return len(visited[min(visited.keys())]), end_time - start_time

test1_correct = 11048
test2_correct = 64
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')