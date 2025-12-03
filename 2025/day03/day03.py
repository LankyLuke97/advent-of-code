from math import ceil
from pathlib import Path
import re

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data.readlines():
            line = line.strip()
            l = len(line)
            dp = [[('0',0)] * l for _ in range(2)]
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
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data.readlines():
            line = line.strip()
            l = len(line)
            dp = [[('0',0)] * l for _ in range(12)]
            for i in range(len(dp)):
                for j in range(i-12, 0):
                    dp[i][i-j] = (line[i-12], l+i-12)

            for row in dp: print(row)
            input()
            for idx in range(l-2,-1,-1):
                for row in dp:
                    if row[idx+1][0] <= line[idx] and row[idx][1] <= idx: row[idx] = (line[idx], idx)
                    else: row[idx] = row[idx+1]
                print(f'-----{idx:02}-----')
                for row in dp: print(row)
                input()

            string = ""
            idx = 0
            for row in dp:
                c, idx = row[idx]
                string += c
                idx += 1
            print(string)
            for row in dp: print(row)
            input()
            ans += int(string)
    return ans

assert 357 == part_one('test.txt')
print(part_one('data.txt'))

assert 3121910778619 == part_two('test.txt')
print(part_two('data.txt'))
