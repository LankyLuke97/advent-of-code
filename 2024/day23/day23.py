from collections import defaultdict
from itertools import combinations
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day23', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    pc_group = defaultdict(set)
    for line in inp:
        pc_1, pc_2 = line.split('-')
        pc_group[pc_1].add(pc_1)
        pc_group[pc_1].add(pc_2)
        pc_group[pc_2].add(pc_1)
        pc_group[pc_2].add(pc_2)

    parties = set()

    for key, group in pc_group.items():
        if not key.startswith('t'): continue
        for pc in group:
            if pc == key: continue
            _group = group & pc_group[pc]
            for combination in combinations(_group, 3):
                if key not in combination or pc not in combination: continue
                parties.add(frozenset(combination))

    end_time = perf_counter()
    return len(parties), end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 7
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')