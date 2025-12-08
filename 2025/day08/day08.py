from collections import Counter
from itertools import combinations
from pathlib import Path

def part_one(file, connections=1000):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        positions = [[int(x) for x in l.strip().split(',')] for l in data.readlines()]
    roots = [i for i in range(len(positions))]
    sizes = [1 for _ in range(len(positions))]
    
    def find_parent(x):
        if roots[x] != x:
            roots[x] = find_parent(roots[x])
            return roots[x]

        return x

    def square_dist(x, y):
        if len(x) != len(y): raise ValueError(f"Both {x} and {y} must be iterables of numeric data")
        return sum([(a-b)*(a-b) for a, b in zip(x, y)])

    for _, p1, p2 in sorted([(square_dist(positions[i], positions[j]), i, j) for i, j in combinations(range(len(positions)), 2)])[:connections]:
        x_root, y_root = find_parent(p1), find_parent(p2)
        if x_root != y_root:
            if sizes[x_root] < sizes[y_root]: x_root, y_root = y_root, x_root
            roots[y_root] = roots[x_root]
            sizes[y_root] += sizes[x_root]
    for i in range(len(positions)): find_parent(i)
    roots = sorted(Counter(roots).values(), reverse=True)
    ans = roots[0] * roots[1] * roots[2]
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        positions = [[int(x) for x in l.strip().split(',')] for l in data.readlines()]
    roots = [i for i in range(len(positions))]
    sizes = [1 for _ in range(len(positions))]
    
    def find_parent(x):
        if roots[x] != x:
            roots[x] = find_parent(roots[x])
            return roots[x]

        return x

    def square_dist(x, y):
        if len(x) != len(y): raise ValueError(f"Both {x} and {y} must be iterables of numeric data")
        return sum([(a-b)*(a-b) for a, b in zip(x, y)])

    connections = len(positions)-1
    for _, p1, p2 in sorted([(square_dist(positions[i], positions[j]), i, j) for i, j in combinations(range(len(positions)), 2)]):
        x_root, y_root = find_parent(p1), find_parent(p2)
        if x_root != y_root:
            connections -= 1
            if not connections:
                ans = positions[p1][0] * positions[p2][0]
                break
            if sizes[x_root] < sizes[y_root]: x_root, y_root = y_root, x_root
            roots[y_root] = roots[x_root]
            sizes[y_root] += sizes[x_root]

    return ans

assert 40 == part_one('test.txt', connections=10)
print(part_one('data.txt'))

assert 25272 == part_two('test.txt')
print(part_two('data.txt'))
