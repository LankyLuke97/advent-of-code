from collections import defaultdict
import math
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day8', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    inp = [line.strip() for line in inp if line.strip()]
    n = len(inp)
    inp = "".join(inp)
    antinodes = set()
    nodes = defaultdict(list)

    for i, c in enumerate(inp):
        if c == '.': continue
        nodes[c].append((i // n, i % n))

    for _, locations in nodes.items():
        for i in range(len(locations)-1):
            for j in range(i+1, len(locations)):
                diff = (locations[i][0] - locations[j][0], locations[i][1] - locations[j][1])
                i_antinode = (locations[i][0] + diff[0], locations[i][1] + diff[1])
                j_antinode = (locations[j][0] - diff[0], locations[j][1] - diff[1])
                if 0 <= i_antinode[0] < n and 0 <= i_antinode[1] < n: antinodes.add(i_antinode)
                if 0 <= j_antinode[0] < n and 0 <= j_antinode[1] < n: antinodes.add(j_antinode)

    end_time = perf_counter()
    return len(antinodes), end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    inp = [line.strip() for line in inp if line.strip()]
    n = len(inp)
    inp = "".join(inp)
    antinodes = set()
    nodes = defaultdict(list)

    for i, c in enumerate(inp):
        if c == '.': continue
        nodes[c].append((i // n, i % n))

    for _, locations in nodes.items():
        if len(locations) == 1:
            continue
        antinodes = antinodes.union(set(locations))
        for i in range(len(locations)-1):
            for j in range(i+1, len(locations)):
                diff = (locations[i][0] - locations[j][0], locations[i][1] - locations[j][1])
                denom = math.gcd(diff[0], diff[1])
                diff = (diff[0] / denom, diff[1] / denom)
                steps = 0
                while True:
                    steps += 1
                    antinode = (locations[i][0] - (diff[0] * steps), locations[i][1] - (diff[1] * steps))
                    if not (0 <= antinode[0] < n and 0 <= antinode[1] < n): break
                    antinodes.add(antinode)
                steps = 0
                while True:
                    steps += 1
                    antinode = (locations[i][0] + (diff[0] * steps), locations[i][1] + (diff[1] * steps))
                    if not (0 <= antinode[0] < n and 0 <= antinode[1] < n): break
                    antinodes.add(antinode)

    end_time = perf_counter()
    return len(antinodes), end_time - start_time

test1_correct = 14
test2_correct = 34
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')