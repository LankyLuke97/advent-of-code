from functools import reduce
from itertools import zip_longest
from operator import add, mul
from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        ans = sum([reduce(add if problem[-1] == '+' else mul, map(int, problem[:-1])) for problem in zip(*[line.strip().split() for line in data.readlines()])])
    return ans

def part_two(file):
    ans = 0
    lines = []
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        lines = [line.rstrip('\n') for line in data.readlines()]
    cuts = [i for i, c in enumerate(lines[-1]) if c != ' ']+[len(lines[1])+1]
    lines = [[line[i:j-1] for i, j in zip(cuts[:-1], cuts[1:])] for line in lines]
    for problem in zip(*lines):
        op = add if '+' == problem[-1][0] else mul
        ans += reduce(op, [int(''.join(rev).strip()) for rev in zip_longest(*[''.join(reversed(p)) for p in problem[:-1]])])
    return ans

assert 4277556 == part_one('test.txt')
print(part_one('data.txt'))

assert 3263827 == part_two('test.txt')
print(part_two('data.txt'))
