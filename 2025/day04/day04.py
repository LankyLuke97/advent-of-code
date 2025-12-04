from pathlib import Path

def part_one(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        rolls = set()
        directions = ((-1,0),(-1,1),(0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1))
        for y, line in enumerate(data.readlines()):
            for x, c in enumerate(line.strip()):
                if '@' == c: rolls.add((y,x))
        for y, x in rolls:
            count = 0
            for dy, dx in directions: count += 1 if (y+dy, x+dx) in rolls else 0
            if count < 4: ans += 1
        
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        check = []
        rolls = set()
        directions = ((-1,0),(-1,1),(0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1))
        mx, my = 0, 0
        for y, line in enumerate(data.readlines()):
            my = y
            mx = len(line)-1
            for x, c in enumerate(line.strip()):
                if '@' == c:
                    check.append((y,x))
                    rolls.add((y,x))
        while check:
            y, x = check.pop()
            if (y, x) not in rolls: continue
            count = 0
            neighbours = [(y+dy, x+dx) for dy, dx in directions if (y+dy, x+dx) in rolls]
            if len(neighbours) < 4:
                ans += 1
                check.extend(neighbours)
                rolls.remove((y, x))
    return ans

assert 13 == part_one('test.txt')
print(part_one('data.txt'))

assert 43 == part_two('test.txt')
print(part_two('data.txt'))
