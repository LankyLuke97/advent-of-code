password = 0
cur = 50

with open('data.txt', mode='r', encoding='utf8') as data:
    for line in data.readlines():
        dir, dist = 1 if line[0] == 'R' else -1, int(line[1:])
        cur = (cur + dir * dist) % 100
        if not cur: password += 1

print(password)

password = 0
cur = 50

with open('data.txt', mode='r', encoding='utf8') as data:
    for line in data.readlines():
        dir, (p, dist) = 1 if line[0] == 'R' else -1, divmod(int(line[1:]), 100)
        password += p
        if cur != 0:
            if dir < 0 and cur - dist <= 0: password += 1
            elif dir > 0 and cur + dist >= 100: password += 1
        cur = (cur + dir * dist) % 100

print(password)
