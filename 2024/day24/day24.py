from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day24', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    known = {}
    zs = []

    for i, line in enumerate(inp):
        if ':' not in line: break
        known[line.split(':')[0]] = line.split(':')[1].strip() == '1'

    to_process = [line.split() for line in inp[i:]]
    while to_process:
        g1, op, g2, _, out = to_process.pop(0)
        if g1 not in known or g2 not in known:
            to_process.append((g1, op, g2, '->', out))
            continue
        if out in known:
            print("Already seen")
            continue
        match op:
            case 'AND': known[out] = known[g1] & known[g2]
            case 'OR': known[out] = known[g1] | known[g2]
            case 'XOR': known[out] = known[g1] ^ known[g2]
        if out.startswith('z'): zs.append((out, 1 if known[out] else 0))
    zs = sorted(zs, key=lambda x: x[0], reverse=True)
    ans = 0
    for _, z in zs:
        ans = ans << 1
        ans += z
        
    end_time = perf_counter()
    return ans, end_time - start_time

def part2(test=False, file_path=None):
    # inp = load_input(test, file_path)
    start_time = perf_counter()

    end_time = perf_counter()
    return 0, end_time - start_time

test1_correct = 2024
test2_correct = 0
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')