from operator import add, mul
from functools import reduce
from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        ans = sum([reduce(add, map(int, problem[:-1])) if problem[-1] == '+' else reduce(mul, map(int,problem[:-1])) for problem in zip(*[line.strip().split() for line in data.readlines()])])
    return ans

def part_two(file):
    ranges = []
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        pass
    return sum([b-a+1 for a, b in ranges])

assert 4277556 == part_one('test.txt')
print(part_one('data.txt'))

assert 0 == part_two('test.txt')
print(part_two('data.txt'))
