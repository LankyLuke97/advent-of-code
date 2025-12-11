from functools import cache
from pathlib import Path

def part_one(file):
    neighbours = {}
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data:
            key, value = line.split(':')
            neighbours[key] = value.strip().split()

    @cache
    def search(key):
        if key == 'out': return 1
        if key not in neighbours: return 0
        return sum([search(neighbour) for neighbour in neighbours[key]])

    return search('you') 

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        pass
    return ans

assert 5 == part_one('test.txt')
print(part_one('data.txt'))

assert 0 == part_two('test.txt')
print(part_two('data.txt'))
