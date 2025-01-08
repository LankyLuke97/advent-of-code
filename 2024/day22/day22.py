from collections import defaultdict, deque
from functools import cache
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day22', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    def next_num(num, iterations=2000):
        for _ in range(iterations):
            num = ((num << 6) ^ num) & 16777215
            num = ((num >> 5) ^ num) & 16777215
            num = ((num << 11) ^ num) & 16777215
        return num

    inp = load_input(test, file_path)
    start_time = perf_counter()

    secrets = sum([next_num(int(line)) for line in inp])

    end_time = perf_counter()
    return secrets, end_time - start_time

def part2(test=False, file_path=None):
    def all_changes(num, iterations=2000):
        prev = num % 10
        sequence = deque([],4)
        sequences_to_amount = {}
        for _ in range(3):
            num = ((num << 6) ^ num) & 16777215
            num = ((num >> 5) ^ num) & 16777215
            num = ((num << 11) ^ num) & 16777215
            last = num % 10
            sequence.append(last - prev)
            prev = last
        for _ in range(3, iterations):
            num = ((num << 6) ^ num) & 16777215
            num = ((num >> 5) ^ num) & 16777215
            num = ((num << 11) ^ num) & 16777215
            last = num % 10
            sequence.append(last - prev)
            prev = last
            if tuple(sequence) in sequences_to_amount: continue
            sequences_to_amount[tuple(sequence)] = last
        return sequences_to_amount

    inp = load_input(test, file_path)
    start_time = perf_counter()

    all_sequences = defaultdict(int)
    for line in inp:
        for sequence, num in all_changes(int(line)).items():
            all_sequences[sequence] += num
    max_bananas = max(all_sequences.values())

    end_time = perf_counter()
    return max_bananas, end_time - start_time

test1_correct = 37327623
test2_correct = 23
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True, file_path=Path('day22','data','test2.txt'))
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')