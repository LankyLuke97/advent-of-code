from math import ceil
from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for r in data.readlines()[0].split(','):
            start, end = r.split('-')
            cur = start[:len(start)//2]
            if not cur: cur = '1'
            start, end = int(start), int(end)
            while int(cur+cur) < start: cur = str(int(cur)+1)
            while int(cur+cur) <= end:
                ans += int(cur+cur)
                cur = str(int(cur)+1)
    return ans

assert 1227775554 == part_one('test.txt')
print(part_one('data.txt'))

assert 4174379265 == part_two('test.txt')
print(part_two('data.txt'))
