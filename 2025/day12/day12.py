from pathlib import Path
import re

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        lines = data.readlines()
    for line in lines[30:]:
        search = re.search(r'(\d+)x(\d+):((?: \d+){6})', line.strip())
        width, length = int(search.group(1)), int(search.group(2))
        num_presents = sum([int(x) for x in search.group(3).strip().split()])
        if (width // 3) * (length // 3) >= num_presents: ans += 1
    return ans

assert 0 == part_one('test.txt')
print(part_one('data.txt'))

