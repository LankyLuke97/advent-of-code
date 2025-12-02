from math import ceil
from pathlib import Path
import re

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for r in data.readlines()[0].split(','):
            start, end = map(int, r.split('-'))
            for i in range(start, end+1):
                if re.fullmatch(r'(\d+)\1', str(i)): ans += i
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for r in data.readlines()[0].split(','):
            start, end = map(int, r.split('-'))
            for i in range(start, end+1):
                if re.fullmatch(r'(\d+)\1+', str(i)): ans += i
    return ans

assert 1227775554 == part_one('test.txt')
print(part_one('data.txt'))

assert 4174379265 == part_two('test.txt')
print(part_two('data.txt'))
