import heapq
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

class Node:
    def __init__(self, y, x, parent, f, g):
        self.y = y
        self.x = x
        self.parent = parent
        self.f = f
        self.g = g
    def __lt__(self, other):
        return (self.f < other.f)

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    max_coord = 7 if test else 71
    b = 12 if test else 1024
    grid = [[0] * max_coord for _ in range(max_coord)]
    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    current_path = set()
    start_node = Node(0, 0, None, 0, 0)

    for l in inp:
        b_x, b_y = l.split(',')
        grid[int(b_y)][int(b_x)] = -1
        if current_path and (int(b_y), int(b_x)) not in current_path: continue

        path = False
        min_steps = math.inf
        open_nodes = [start_node]
        closed_nodes = [[math.inf] * len(grid[0]) for _ in range(len(grid))]
        min_steps = math.inf
        end = (max_coord-1, max_coord-1)
        end_node = None
        
        while open_nodes:
            cur_node = heapq.heappop(open_nodes)

            if cur_node.y == end[0] and cur_node.x == end[1]:
                path = True
                end_node = cur_node
                break
            
            if cur_node.g >= closed_nodes[cur_node.y][cur_node.x]: continue
            closed_nodes[cur_node.y][cur_node.x] = cur_node.g
            for direction in directions:
                next_position = (cur_node.y + direction[0], cur_node.x + direction[1])
                if not (0 <= next_position[0] < max_coord and 0 <= next_position[1] < max_coord): continue
                new_g = cur_node.g + 1
                if new_g >= closed_nodes[next_position[0]][next_position[1]] or grid[next_position[0]][next_position[1]]: continue
                h = abs(end[0] - next_position[0]) + abs(end[1] - next_position[1])
                f = new_g + h
                new_node = Node(next_position[0], next_position[1], cur_node, f, new_g)
                heapq.heappush(open_nodes, new_node)

        if not path:
            break
        cur_node = end_node
        current_path.clear()
        while cur_node:
            current_path.add((cur_node.y, cur_node.x))
            cur_node = cur_node.parent

    end_time = perf_counter()
    return ','.join((b_x, b_y)), end_time - start_time

test1_correct = 22
test2_correct = '6,1'
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')