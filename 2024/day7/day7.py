from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day7', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    inp = [map(int, line.replace(':','').strip().split()) for line in inp]
    ans = 0
    for [total, *options] in inp:
        potentials = [options.pop(0)]
        while options:
            option = options.pop(0)
            num = len(potentials)
            for i in range(num):
                potentials.append(potentials[i] * option)
                potentials[i] += option
        if any([potential == total for potential in potentials]): ans += total

    end_time = perf_counter()
    return ans, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 3749
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')