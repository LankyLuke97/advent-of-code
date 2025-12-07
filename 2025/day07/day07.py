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
        pass
    return ans

assert 21 == part_one('test.txt')
print(part_one('data.txt'))

assert 0 == part_two('test.txt')
print(part_two('data.txt'))
