from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day11', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = [(int(i),i) for line in load_input(test, file_path) for i in line.split()]
    start_time = perf_counter()

    for _ in range(25):
        new_inp = []
        for i, str_rep in inp:
            if i == 0: new_inp.append((1, '1'))
            elif len(str_rep) % 2 == 0:
                first_half = int(str_rep[:int(len(str_rep)/2)])
                second_half = int(str_rep[int(len(str_rep)/2):])
                new_inp.append((first_half,str(first_half)))
                new_inp.append((second_half,str(second_half)))
            else: new_inp.append((i * 2024, str(i*2024)))
        inp = new_inp

    end_time = perf_counter()
    return len(inp), end_time - start_time

def part2(test=False, file_path=None):
    def get_length_dp(dp, lengths, key, depth):
        if key in lengths: return lengths[key]
        if depth == 0: return len(dp[key][0])
        lengths[key] = sum([get_length_dp(dp, lengths, k, depth-1) for k in dp[key][depth-1]])
        return lengths[key]

    inp = [(int(i), 0) for line in load_input(test, file_path) for i in line.split()]
    start_time = perf_counter()
    steps = 25

    dp = {}

    for _ in range(steps):
        new_inp = []

        for i, index in inp:
            if i in dp:
                new_inp.append((i, index + 1))
                continue
            if i == 0:
                dp[i] = [[1]]
                new_inp.append((1, 0))
            elif len(str(i)) % 2 == 0:
                str_rep = str(i)
                first_half = int(str_rep[:int(len(str_rep)/2)])
                second_half = int(str_rep[int(len(str_rep)/2):])
                dp[i] = [[first_half, second_half]]
                new_inp.append((first_half,0))
                new_inp.append((second_half,0))
            else:
                dp[i] = [[i*2024]]
                new_inp.append((i * 2024, 0))

        new_dp = {}
        for key, value in dp.items():
            new_value = []
            for v in value[-1]:
                if v in dp:
                    new_value.extend(dp[v][0])
                    continue
                if v == 0:
                    new_dp[v] = [[1]]
                    new_value.append(1)
                elif len(str(v)) % 2 == 0:
                    str_rep = str(v)
                    first_half = int(str_rep[:int(len(str_rep)/2)])
                    second_half = int(str_rep[int(len(str_rep)/2):])
                    new_dp[v] = [[first_half, second_half]]
                    new_value.append(first_half)
                    new_value.append(second_half)
                else:
                    new_dp[v] = [[v*2024]]
                    new_value.append(v*2024)
            dp[key].append(new_value)
        dp |= new_dp
        inp = new_inp
    
    num_stones = sum([get_length_dp(dp, {}, i, index) for i, index in inp])

    end_time = perf_counter()
    return num_stones, end_time - start_time

test1_correct = 55312
test2_correct = 55312
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')