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
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 10092
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')