from collections import defaultdict
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day12', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    seen = set()
    area = {(0,0)}
    perimeter = 0
    cur_bfs = [(0,0)]
    cur_region = inp[0][0]
    next_bfs = set()
    price = 0

    while cur_bfs:
        y, x = cur_bfs.pop(0)
        for y_off, x_off in directions:
            _y = y+y_off
            _x = x+x_off
            if not (0 <= _y < len(inp) and 0 <= _x < len(inp[0])):
                perimeter += 1
                continue
            if inp[_y][_x] == cur_region:
                if (_y,_x) not in area:
                    area.add((_y,_x))
                    cur_bfs.append((_y,_x))
                continue
            perimeter += 1
            if (_y,_x) not in seen:
                next_bfs.add((_y,_x))

        if cur_bfs: continue

        seen.update(area)
        next_bfs.difference_update(seen)
        price += len(area) * perimeter

        if not next_bfs: break
        
        cur_bfs = [next_bfs.pop()]
        cur_region = inp[cur_bfs[0][0]][cur_bfs[0][1]]
        area = {(cur_bfs[0][0],cur_bfs[0][1])}
        perimeter = 0

    end_time = perf_counter()
    return price, end_time - start_time

def part2(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()
    directions = [(-1,0),(0,1),(1,0),(0,-1)]
    seen = set()
    area = {(0,0)}
    sides = {direction: defaultdict(list) for direction in directions}
    cur_bfs = [(0,0)]
    cur_region = inp[0][0]
    next_bfs = set()
    price = 0

    while cur_bfs:
        y, x = cur_bfs.pop(0)
        for y_off, x_off in directions:
            direction_index = 0 if y_off else 1
            _y = y+y_off
            _x = x+x_off
            if not (0 <= _y < len(inp) and 0 <= _x < len(inp[0])):
                sides[(y_off, x_off)][(_y, _x)[direction_index]].append((_y, _x)[1 - direction_index])
                continue
            if inp[_y][_x] == cur_region:
                if (_y,_x) not in area:
                    area.add((_y,_x))
                    cur_bfs.append((_y,_x))
                continue
            sides[(y_off, x_off)][(_y, _x)[direction_index]].append((_y, _x)[1 - direction_index])
            if (_y,_x) not in seen:
                next_bfs.add((_y,_x))

        if cur_bfs: continue

        seen.update(area)
        next_bfs.difference_update(seen)
        num_sides = 0
        
        for direction in sides.values():
            for locations in direction.values():
                loc = sorted(locations)
                num_sides += len([0 for (l1, l2) in zip(loc[1:], loc[:-1]) if l1 - l2 - 1]) + 1

        price += len(area) * num_sides

        if not next_bfs: break
        
        cur_bfs = [next_bfs.pop()]
        cur_region = inp[cur_bfs[0][0]][cur_bfs[0][1]]
        area = {(cur_bfs[0][0],cur_bfs[0][1])}
        sides = {direction: defaultdict(list) for direction in directions}

    end_time = perf_counter()
    return price, end_time - start_time

test1_correct = 1930
test2_correct = 1206
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')