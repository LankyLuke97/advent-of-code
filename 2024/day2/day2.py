from pathlib import Path

def load_input(test=False): 
    file_path = Path(f'day2', 'data', f'day2{"_test" if test else ""}.txt')
    with open(file_path, 'r') as f:
        return f.readlines()

def part1(test=False):
    inp = load_input(test)
    reports = [list(map(int, line.strip().split())) for line in inp if line.strip() != ""]
    reports = [list(zip(report[:-1], report[1:])) for report in reports]
    return sum ([1 if 
        all([1 <= abs(diff[0] - diff[1]) <= 3 for diff in report]) and
        (all([diff[0] < diff[1] for diff in report]) or
        all([diff[1] < diff[0] for diff in report]))
    else 0 for report in reports])

def part2(test=False):
    def is_safe(report):
        return (all([1 <= abs(diff[0] - diff[1]) <= 3 for diff in report]) and
        (all([diff[0] < diff[1] for diff in report]) or
        all([diff[1] < diff[0] for diff in report])))
    
    inp = load_input(test)
    safe = 0
    reports = [list(map(int, line.strip().split())) for line in inp if line.strip() != ""]

    for report in reports:
        if is_safe(report=list(zip(report[:-1], report[1:]))):
            safe += 1
            continue
        for i in range(len(report)):
            cleaned_report = report[:i] + report[i+1:]
            if is_safe(report=list(zip(cleaned_report[:-1], cleaned_report[1:]))):
                safe += 1
                break

    return safe

test1_correct = 2
test2_correct = 4
test = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
print(f'Part 1 answer is: {part1()}')
test = part2(test=True)
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
print(f'Part 2 answer is: {part2()}')