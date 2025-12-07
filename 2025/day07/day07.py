from functools import cache
from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data: 
            beams = {line.index('S')}
            break
        for line in data:
            new_beams = set()
            for beam in beams: 
                if '^' == line[beam]:
                    new_beams.add(beam-1)
                    new_beams.add(beam+1)
                    ans += 1
                else: new_beams.add(beam)
            beams = new_beams
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data: 
            start = line.index('S')
            break
        splits = set()
        max_y = 0
        for y, line in enumerate(data.readlines()):
            splits |= {(y, x) for x, c in enumerate(line) if '^' == c}
            max_y = y
    
    @cache
    def rec(y, x):
        if y >= max_y: return 1
        if (y, x) not in splits: return rec(y+1, x)
        return rec(y+1, x-1) + rec(y+1,x+1)

    ans = rec(0, start)

    return ans

assert 21 == part_one('test.txt')
print(part_one('data.txt'))

assert 40 == part_two('test.txt')
print(part_two('data.txt'))
