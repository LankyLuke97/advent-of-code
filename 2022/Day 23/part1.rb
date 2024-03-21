require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

directionInd = 0
directions = [[0,-1],[0,1],[-1,0],[1,0]]
checks = [[[-1,-1],[0,-1],[1,-1]],[[-1,1],[0,1],[1,1]],[[-1,-1],[-1,0],[-1,1]],[[1,-1],[1,0],[1,1]]]

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

while needToMove && rounds < 10 do
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
                check = checks[(directionInd + indOffset) % 4]
                if check.include? diff
                    elfInWay = true
                    break
                end
            end

            unless elfInWay
                position = elfPositions[elf]
                step = directions[(directionInd + indOffset) % 4]
                suggestion = [position[0] + step[0], position[1] + step[1]]
                break
            end
        end

        unless suggestion.nil?
            moveSuggestions[elf] = suggestion
            next
        end
    end

    clashing = Set.new

    moveSuggestions.each do |e1, suggestion|
        moveSuggestions.each do |e2, otherSuggestion|
            if e2 <= e1
                next
            end
            if suggestion == otherSuggestion
                clashing.add(suggestion)
            end
        end

        unless clashing.include? suggestion
            elfPositions[e1] = suggestion
        end
    end
    
    directionInd = (directionInd + 1) % 4
end

minX = elfPositions.min_by {|x, y| x }[0]
maxX = elfPositions.max_by {|x, y| x }[0]
minY = elfPositions.min_by {|x, y| y }[1]
maxY = elfPositions.max_by {|x, y| y }[1]

puts (((maxX + 1 - minX)* (maxY + 1 - minY)) - elfPositions.size)