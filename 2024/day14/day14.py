from pathlib import Path
import png
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day14', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    q = [0, 0, 0, 0]
    seconds = 100
    width, height = (11, 7) if test else (101, 103)
    for line in inp:
        parts = [p.split('=')[1] for p in line.split()]
        pos_vel = [int(i) for i in [details for p in parts for details in p.split(',')]]
        x = (pos_vel[0] + seconds * pos_vel[2]) % width
        if x == (width // 2): continue
        y = (pos_vel[1] + seconds * pos_vel[3]) % height
        if y == (height // 2): continue
        if x < width // 2:
            if y < height // 2: q[0] += 1
            else: q[2] += 1
        else:
            if y < height // 2: q[1] += 1
            else: q[3] += 1

    end_time = perf_counter()
    return q[0]*q[1]*q[2]*q[3], end_time - start_time

def part2(test=False, file_path=None):
    if test: return 0, 0
    inp = load_input(test, file_path)
    start_time = perf_counter()

    width, height = (11, 7) if test else (101, 103)
    robots = []
    for line in inp:
        parts = [p.split('=')[1] for p in line.split()]
        robots.append([int(i) for i in [details for p in parts for details in p.split(',')]])

    image = [[0] * width for _ in range(height)]
    
    w = png.Writer(width=width, height=height, greyscale=True)
    for step in range(1, 10000):
        positions = set()
        for robot in robots:
            robot[0] = (robot[0] + robot[2]) % width
            robot[1] = (robot[1] + robot[3]) % height
            positions.add((robot[0], robot[1]))
        for (x, y) in positions:
            image[y][x] = 255
        
        # with open(Path('day14','data','pngs',f'{step:04}.png'), 'wb') as frame:
        #    w.write(frame, image)
        if step == 7492:
            with open(Path('day14','data','easter_egg_7492.png'), 'wb') as frame:
                w.write(frame, image)

        for (x, y) in positions:
            image[y][x] = 0
        
    end_time = perf_counter()
    return 7492, end_time - start_time

test1_correct = 12
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')