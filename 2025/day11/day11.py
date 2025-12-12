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
    neighbours = {}
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data:
            key, value = line.split(':')
            neighbours[key] = value.strip().split()

    @cache
    def search(key, dac, fft):
        if key == 'out': return 1 if dac and fft else 0
        if key not in neighbours: return 0
        dac |= 'dac' == key
        fft |= 'fft' == key
        return sum([search(neighbour,dac,fft) for neighbour in neighbours[key]])

    return search('svr', False, False) 

assert 5 == part_one('test.txt')
print(part_one('data.txt'))

assert 2 == part_two('test2.txt')
print(part_two('data.txt'))
