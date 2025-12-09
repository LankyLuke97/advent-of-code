from itertools import combinations
from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        coords = [tuple(map(int, line.strip().split(','))) for line in data if line.strip()]
    for i, j in combinations(range(len(coords)), 2): ans = max(ans, (abs(coords[i][0]-coords[j][0])+1)*(abs(coords[i][1]-coords[j][1])+1))
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        coords = [tuple(map(int, line.strip().split(','))) for line in data if line.strip()]
    h_edges = []
    v_edges = []
    for i in range(len(coords)):
        p1, p2 = coords[i], coords[(i+1)%len(coords)]
        if p1[0] == p2[0]: v_edges.append((p1[0], min(p1[1], p2[1]), max(p1[1], p2[1])))
        else: h_edges.append((min(p1[0], p2[0]), max(p1[0], p2[0]), p1[1]))

    def point_inside(px, py):
        intersections = 0
        for x, min_y, max_y in v_edges:
            if x > px and min_y <= py < max_y: intersections += 1
        return intersections % 2 == 1

    def intersects(r_min_x, r_min_y, r_max_x, r_max_y):
        for x, min_y, max_y in v_edges:
            if r_min_x < x < r_max_x and max(min_y, r_min_y) < min(max_y, r_max_y): return True
        for min_x, max_x, y in h_edges:
            if r_min_y < y < r_max_y and max(min_x, r_min_x) < min(max_x, r_max_x): return True
        return False

    for i, j in combinations(range(len(coords)), 2):
        (x1, y1), (x2, y2) = coords[i], coords[j]
        potential = (abs(x1-x2)+1) * (abs(y1-y2)+1)
        if potential <= ans: continue
        r_min_x, r_max_x = min(x1, x2), max(x1, x2)
        r_min_y, r_max_y = min(y1, y2), max(y1, y2)
        if point_inside(r_min_x + 0.5, r_min_y + 0.5) and not intersects(r_min_x, r_min_y, r_max_x, r_max_y): ans = potential

    return ans

assert 50 == part_one('test.txt')
print(part_one('data.txt'))

assert 24 == part_two('test.txt')
print(part_two('data.txt'))
