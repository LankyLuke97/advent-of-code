from functools import cache
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
        pass
    return ans

assert 7 == part_one('test.txt')
print(part_one('data.txt'))

assert 0 == part_two('test.txt')
print(part_two('data.txt'))
