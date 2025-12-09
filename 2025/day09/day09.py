from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        coords = [tuple(map(int, line.strip().split(','))) for line in data if line.strip()]
    for i in range(len(coords)):
        for j in range(i+1,len(coords)):
            ans = max(ans, abs((coords[i][0]-coords[j][0]+1)*(coords[i][1]-coords[j][1]+1)))
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        pass
    return ans

assert 50 == part_one('test.txt')
print(part_one('data.txt'))

assert 0 == part_two('test.txt')
print(part_two('data.txt'))
