require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

directionInd = 0
directions = [[0,-1],[0,1],[-1,0],[1,0]]
checks = [[[-1,-1],[+0,-1],[+1,-1]],
          [[-1,+1],[+0,+1],[+1,+1]],
          [[-1,-1],[-1,+0],[-1,+1]],
          [[+1,-1],[+1,+0],[+1,+1]]]

elfPositions = Array.new

lines.each_with_index do |line, yIndex|
    line.strip!
    line.each_char.with_index do |c, xIndex|
        if c == '.'
            next
        end
        elfPositions << [xIndex, yIndex]
    end
end

needToMove = true
rounds = 0

while needToMove do
    rounds += 1
    needToMove = false
    toMove = Hash.new

    elfPositions.each_with_index do |elf1, e1|
        elfPositions.each_with_index do |elf2, e2|
            if e2 <= e1
                next
            end
            if (elf1[0]-elf2[0]).abs <= 1 && (elf1[1]-elf2[1]).abs <= 1
                needToMove = true
                unless toMove.include? e1
                    toMove[e1] = Set.new
                end
                unless toMove.include? e2
                    toMove[e2] = Set.new
                end
                toMove[e1].add(e2)
                toMove[e2].add(e1)
            end
        end
    end

    unless needToMove
        break
    end

    moveSuggestions = Hash.new

    toMove.each do |elf, adjacent|
        suggestion = nil
        (0..3).each do |indOffset|
            elfInWay = false
            adjacent.each do |adjacentElf|
                diff = [elfPositions[adjacentElf][0] - elfPositions[elf][0],elfPositions[adjacentElf][1] - elfPositions[elf][1]]
                check = checks[indOffset]
                if check.include? diff
                    elfInWay = true
                    break
                end
            end

            unless elfInWay
                position = elfPositions[elf]
                step = directions[indOffset]
                suggestion = [position[0] + step[0], position[1] + step[1]]
                break
            end
        end

        unless suggestion.nil?
            unless moveSuggestions.include? suggestion
                moveSuggestions[suggestion] = Array.new
            end
            moveSuggestions[suggestion].append(elf)
            next
        end
    end
    moved = false

    moveSuggestions.each do |suggestion, elves|
        if elves.size > 1
            next
        end
        elfPositions[elves[0]] = suggestion
        moved = true
    end

    unless moved
        break
    end

    directions = directions[1..-1].append directions[0]
    checks = checks[1..-1].append checks[0]
end

puts rounds