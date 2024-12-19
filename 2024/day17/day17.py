import math
from pathlib import Path
from time import perf_counter

def load_input(test=False, file_path=None):
    file_path = Path(f'day17', 'data', f'{"test" if test else "input"}.txt') if not file_path else file_path
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines() if line.strip()]

def part1(test=False, file_path=None):
    inp = load_input(test, file_path)
    start_time = perf_counter()

    registers = [int(i.split(':')[1].strip()) for i in inp[:3]]
    program = [int(i) for i in inp[3].split(':')[1].strip().split(',')]
    pointer = 0
    out = []

    while pointer < len(program) - 1:
        instruction = program[pointer]
        literal_operand = program[pointer + 1]
        combo_operand = literal_operand if literal_operand < 4 else registers[literal_operand % 4]

        if instruction == 0: registers[0] = int(registers[0] * (2 ** -combo_operand))
        elif instruction == 1: registers[1] = registers[1] ^ literal_operand
        elif instruction == 2: registers[1] = combo_operand % 8
        elif instruction == 3 and registers[0]: pointer = literal_operand - 2
        elif instruction == 4: registers[1] = registers[1] ^ registers[2]
        elif instruction == 5: out.append(combo_operand % 8)
        elif instruction == 6: registers[1] = int(registers[0] * (2 ** -combo_operand))
        elif instruction == 7: registers[2] = int(registers[0] * (2 ** -combo_operand))
        pointer += 2

    end_time = perf_counter()
    return ','.join([str(i) for i in out]), end_time - start_time

def part2(test=False, file_path=None):
    def run_program(program, a):
        b, c = 0, 0
        pointer = 0
        out = []

        while pointer < len(program) - 1:
            instruction, literal_operand = program[pointer:pointer+2]
            op = {0:0, 1:1, 2:2, 3:3, 4:a, 5:b, 6:c}

            if instruction == 0: a = int(a * (2 ** -op[literal_operand]))
            elif instruction == 1: b = b ^ literal_operand
            elif instruction == 2: b = op[literal_operand] % 8
            elif instruction == 3 and a: pointer = literal_operand - 2
            elif instruction == 4: b = b ^ c
            elif instruction == 5: out.append(op[literal_operand] % 8)
            elif instruction == 6: b = int(a * (2 ** -op[literal_operand]))
            elif instruction == 7: c = int(a * (2 ** -op[literal_operand]))
            pointer += 2
        return out

    inp = load_input(test, file_path)
    start_time = perf_counter()
    program = [int(i) for i in inp[3].split(':')[1].strip().split(',')]
    todo = [(0,1)]
    min_ans = math.inf
        
    while todo:
        a, i = todo.pop(0)
        for a in range(a, a+8):
            if run_program(program, a) == program: min_ans = min(min_ans, a)
            elif i <= len(program) and run_program(program, a) == program[-i:]:
                todo.append((a*8, i+1))

    end_time = perf_counter()
    return min_ans, end_time - start_time

test1_correct = '4,6,3,5,6,3,5,2,1,0'
test2_correct = 117440
test, _ = part1(test=True)
assert test == test1_correct, f'Part 1 test failed; it returned {test} instead of {test1_correct}'
part1_ans, part1_time = part1()
print(f'Part 1 answer is: {part1_ans}, returned in {part1_time * 1000:.3f} ms')
test, _ = part2(test=True,file_path=Path('day17','data','test2.txt'))
assert test == test2_correct, f'Part 2 test failed; it returned {test} instead of {test2_correct}'
part2_ans, part2_time = part2()
print(f'Part 2 answer is: {part2_ans}, returned in {part2_time * 1000:.3f} ms')