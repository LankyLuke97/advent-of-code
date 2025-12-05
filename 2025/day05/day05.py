import bisect
from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        ranges = []
        for line in data:
            if not line.strip(): break
            start, end = list(map(int, line.split('-')))
            idx = bisect.bisect_right(ranges, start, key=lambda x: x[0])
            if idx > 0 and start <= ranges[idx-1][1] + 1:
                idx -= 1
                start, end = ranges[idx][0], max(end, ranges[idx][1])
                ranges[idx] = [start, end]
            else: ranges = ranges[:idx] + [[start, end]] + ranges[idx:]
            merge_idx = idx
            while merge_idx < len(ranges) - 1 and end >= ranges[merge_idx+1][0] - 1:
                merge_idx += 1
                end = max(end, ranges[merge_idx][1])
            if merge_idx != idx: ranges = ranges[:idx] + [[start, end]] + ranges[merge_idx+1:]
        for line in data: 
            id = int(line.strip())
            idx = bisect.bisect_right(ranges, id, key=lambda x: x[0])
            if id > 0 and ranges[idx-1][0] <= id <= ranges[idx-1][1]: ans += 1#; print(f"{id} falls in range {ranges[idx-1]}")
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        pass
    return ans

assert 3 == part_one('test.txt')
print(part_one('data.txt'))

assert 0 == part_two('test.txt')
print(part_two('data.txt'))
