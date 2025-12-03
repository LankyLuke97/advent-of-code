from math import ceil
from pathlib import Path
import re

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data.readlines():
            line = line.strip()
            l = len(line)
            dp = [[('0','0')] * l for _ in range(2)]
            dp[0][-2] = (line[-2], l-2)
            dp[1][-1] = (line[-1], l-1)
            for idx in range(l-2,-1,-1):
                for row in dp:
                    if row[idx+1][0] <= line[idx]: row[idx] = (line[idx], idx)
                    else: row[idx] = row[idx+1]
            string = ""
            idx = 0
            for row in dp:
                c, idx = row[idx]
                string += c
                idx += 1
            ans += int(string)
    return ans

def part_two(file):
    ans = 0
    return ans

assert 357 == part_one('test.txt')
print(part_one('data.txt'))

assert 0 == part_two('test.txt')
print(part_two('data.txt'))
