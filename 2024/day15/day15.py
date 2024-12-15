from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day15', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    directions = {'^': (-1, 0), '>': (0, 1), 'v': (1, 0), '<': (0, -1)}
    robot = (-1, -1)

    map = [[-1 if i == '#' else (1 if i == 'O' else 0) for i in l] for l in inp if l.startswith('#')]
    movements = [directions[m] for l in inp if not l.startswith('#') for m in l]
    for y, l in enumerate(inp):
        for x, c in enumerate(l):
            if c == '@':
                robot = (y, x)
                break
        if robot[0] != -1: break
    
    for movement in movements:
        can_move = False
        end_of_chain = (robot[0] + movement[0], robot[1] + movement[1])
        moving = map[end_of_chain[0]][end_of_chain[1]]
        while map[end_of_chain[0]][end_of_chain[1]] != -1:
            if map[end_of_chain[0]][end_of_chain[1]] == 0:
                map[end_of_chain[0]][end_of_chain[1]] = moving
                robot = (robot[0] + movement[0], robot[1] + movement[1])
                map[robot[0]][robot[1]] = 0
                break
            end_of_chain = (end_of_chain[0] + movement[0], end_of_chain[1] + movement[1])
    
    gps = sum([100*y + x for y in range(len(map)) for x in range(len(map[0])) if map[y][x] == 1])

    end_time = perf_counter()
    return gps, end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    directions = {'^': (-1, 0), '>': (0, 1), 'v': (1, 0), '<': (0, -1)}
    robot = (-1, -1)
    mappings = {'#': [-1, -1], '.': [0, 0], 'O': [1, 2]}
    map = []

    for y, l in enumerate(inp):
        if not l.startswith('#'): break
        new_line = []
        for x, c in enumerate(l):
            if c == '@':
                robot = (y, 2*x)
                new_line.extend(mappings['.'])
            else: new_line.extend(mappings[c])
        map.append(new_line)
        
    movements = [directions[m] for l in inp if not l.startswith('#') for m in l]

    for movement in movements:
        affected = []
        can_move = True
        front = {(robot[0],robot[1])}
        while front:
            new_front = set()
            new_affected = set()
            for f in front:
                next_front = (f[0] + movement[0], f[1] + movement[1])
                if map[next_front[0]][next_front[1]] == -1:
                    can_move = False
                    break
                if map[next_front[0]][next_front[1]] == 0: continue
                new_affected.add(next_front)
                new_front.add(next_front)
                if movement[0]:
                    linked = (next_front[0], next_front[1] + (3 - 2 * map[next_front[0]][next_front[1]]))
                    new_affected.add(linked)
                    new_front.add(linked)
            if not can_move: break
            affected.append(new_affected)
            front = new_front

        if not can_move: continue

        for move in affected[::-1]:
            for y, x in move:
                map[y+movement[0]][x+movement[1]] = map[y][x]
                map[y][x] = 0
        robot = (robot[0] + movement[0], robot[1] + movement[1])

    gps = sum([100*y + x for y in range(len(map)) for x in range(len(map[0])) if map[y][x] == 1])

    end_time = perf_counter()
    return gps, end_time - start_time

test1_correct = 10092
test2_correct = 9021
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')