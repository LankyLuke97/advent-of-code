from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day10', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = [[int(l) for l in line.strip()] for line in load_input(test, file_path) if line.strip()]
    start_time = perf_counter()
    ans = 0
    directions = [(-1,0),(0,1),(1,0),(0,-1)]

    for y in range(len(inp)):
        for x in range(len(inp[0])):
            if inp[y][x]: continue
            trailheads = set()

            bfs = [(y, x, 0)]
            while bfs:
                _y, _x, height = bfs.pop(0)
                if height == 9:
                    trailheads.add((_y, _x))
                    continue
                for y_off, x_off in directions:
                    if (0 <= _y+y_off < len(inp) and
                       0 <= _x+x_off < len(inp[0]) and
                       inp[_y+y_off][_x+x_off] == (height+1)):
                        bfs.append((_y+y_off, _x+x_off, height+1))

            ans += len(trailheads)

    end_time = perf_counter()
    return ans, end_time - start_time

def part2(test=False, file_path=None):
    inp = [[int(l) for l in line.strip()] for line in load_input(test, file_path) if line.strip()]
    start_time = perf_counter()
    ans = 0
    directions = [(-1,0),(0,1),(1,0),(0,-1)]

    for y in range(len(inp)):
        for x in range(len(inp[0])):
            if inp[y][x]: continue
            trailheads = []

            bfs = [(y, x, 0)]
            while bfs:
                _y, _x, height = bfs.pop(0)
                if height == 9:
                    trailheads.append((_y, _x))
                    continue
                for y_off, x_off in directions:
                    if (0 <= _y+y_off < len(inp) and
                       0 <= _x+x_off < len(inp[0]) and
                       inp[_y+y_off][_x+x_off] == (height+1)):
                        bfs.append((_y+y_off, _x+x_off, height+1))

            ans += len(trailheads)

    end_time = perf_counter()
    return ans, end_time - start_time

test1_correct = 36
test2_correct = 81
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')