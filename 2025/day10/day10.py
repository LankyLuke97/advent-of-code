from functools import cache
from itertools import combinations
from pathlib import Path
import re

def part_one(file):
    ans = 0

    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data:
            search = re.search(r'\[([\.|#]+)](( \(\d+((,\d+)*)\))+)', line.strip())
            target, buttons = 0, []
            
            @cache
            def configure(state, presses, idx, s=''):
                if state == target:  return presses
                min_presses = float('inf')
                state ^= buttons[idx]
                s += str(idx)
                presses += 1
                if state == target:  return presses
                for i in range(idx+1, len(buttons)):
                    min_presses = min(min_presses, configure(state, presses, i, s))
                state ^= buttons[idx]
                return min_presses
            
            for c in search.group(1):
                target <<= 1
                if '#' == c: target += 1
            max_lights = len(search.group(1))-1

            for b in search.group(2).split():
                button_value = 0
                for x in b[1:-1].split(','):
                    button_value |= (1 << (max_lights-int(x)))
                buttons.append(button_value)
            
            ans += min([configure(0, 0, i) for i in range(len(buttons)-1, -1, -1)])
    return ans

def part_two(file):
    ans = 0
    with open(Path(__file__).resolve().parent / file, mode='r', encoding='utf8') as data:
        for line in data:
            _, *buttons, target = line.split()
            target = tuple(int(x) for x in target[1:-1].split(','))
            buttons = [[int(x) for x in b[1:-1].split(',')] for b in buttons]
            buttons = [tuple(int(i in b) for i in range(len(target))) for b in buttons]
            costs = {}
            for pattern_len in range(len(buttons)+1):
                for bs in combinations(range(len(buttons)), pattern_len):
                    pattern = tuple(map(sum, zip((0,) * len(buttons[0]), *(buttons[i] for i in bs))))
                    if pattern not in costs: costs[pattern] = pattern_len

            @cache
            def recurse(goal):
                if all(i == 0 for i in goal): return 0
                answer = 1_000_000
                for pattern, pattern_cost in costs.items():
                    if all(i <= j and i%2 == j%2 for i, j in zip(pattern, goal)):
                        new_goal = tuple((j-i)//2 for i, j in zip(pattern, goal))
                        answer = min(answer, pattern_cost + 2 * recurse(new_goal))
                return answer
            ans += recurse(target)
    return ans

assert 7 == part_one('test.txt')
print(part_one('data.txt'))

assert 33 == part_two('test.txt')
print(part_two('data.txt'))
