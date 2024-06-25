filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

pos = [0,lines[0].index('.')]
lengthPad = lines[0..-3].max_by(&:length).length - 1
directions = Hash.new
directions['R'] = 1
directions['L'] = -1
instructions = Array.new
$lefts = Array.new(lines.size - 2, -1)
$tops = Array.new(lengthPad, -1)
$rights = Array.new(lines.size - 2, -1)
$bottoms = Array.new(lengthPad, -1)
poses = Array.new
cleaned = []

instructions = lines[-1].scan(/\d+[RL]/).map { |pair| [pair[0..-2].to_i, directions[pair[-1]]] }
instructions.append([lines[-1][-1].to_i, 0])

# This is absolute ass hardcoding for specifically my input, nothing to be proud of - but sometimes, we rely on domain knowledge
def wrap(direction, pos)
    newPos = pos.dup
    newDirection = direction
    if direction == 0
        if pos[1] == 149
            #3 right (at the top)
            newPos = [149 - pos[0], 99]
            newDirection = 2
        elsif pos[0] < 100
            #2 right
            newPos = [49, 50 + pos[0]]
            newDirection = 3
        elsif pos[0] < 150
            #3 right (in the middle)
            newPos = [149 - pos[0], 149]
            newDirection = 2
        else
            #1 right
            newPos = [149, pos[0] - 100]
            newDirection = 3
        end
    elsif direction == 1
        if pos[0] == 49
            #2 down
            newPos = [pos[1] - 50, 99]
            newDirection = 2
        elsif pos[0] == 149
            #1 down
            newPos = [100 + pos[1], 49]
            newDirection = 2
        else
            #7 down
            newPos = [0, pos[1] + 100]
            newDirection = 1

        end
    elsif direction == 2
        if pos[0] < 50
            #5 left (at the top)
            newPos = [149 - pos[0], 0]
            newDirection = 0
        elsif pos[0] < 100
            #4 left
            newPos = [100, pos[0] - 50]
            newDirection = 1
        elsif pos[0] < 150
            #5 left (in the middle)
            newPos = [149 - pos[0], 50]
            newDirection = 0
        else
            #6 left
            newPos = [0, pos[0] - 100]
            newDirection = 1
        end
    elsif direction == 3
        if pos[0] == 0
            if pos[1] < 100
                #6 up
                newPos = [100 + pos[1], 0]
                newDirection = 0
            else
                #7 up
                newPos = [199, pos[1] - 100]
                newDirection = 3
            end
        else
            #4 up
            newPos = [50 + pos[1], 50]
            newDirection = 0
        end
    end

    if newDirection == 0
        if $lefts[newPos[0]] == -1
            return [pos, direction]
        end
        return [newPos, newDirection]
    elsif newDirection == 1
        if $tops[newPos[1]] == -1
            return [pos, direction]
        end
        return [newPos, newDirection]
    elsif newDirection == 2
        if $rights[newPos[0]] == -1
            return [pos, direction]
        end
        return [newPos, newDirection]
    elsif newDirection == 3
        if $bottoms[newPos[1]] == -1
            return [pos, direction]
        end
        return [newPos, newDirection]
    end
end

lines.each_with_index do |line,index|
    dot_index = line.index('.')
    hash_index = line.index('#')

    if dot_index && (!hash_index || dot_index < hash_index)
        $lefts[index] = dot_index
    end

    dot_index = line.rindex('.')
    hash_index = line.rindex('#')

    if dot_index && (!hash_index || dot_index > hash_index)
        $rights[index] = dot_index
    end

    cleaned.append(line.delete("\n").ljust(lengthPad))
    if line.strip.empty?
        break
    end
end

cleaned.map(&:chars).transpose.map(&:join).each_with_index do |line,index|
    dot_index = line.index('.')
    hash_index = line.index('#')

    if dot_index && (!hash_index || dot_index < hash_index)
        $tops[index] = dot_index
    end

    dot_index = line.rindex('.')
    hash_index = line.rindex('#')

    if dot_index && (!hash_index || dot_index > hash_index)
        $bottoms[index] = dot_index
    end
end

direction = 0
instructions.each do |distance, turn|
    (1..distance).each do
        if direction == 0
            if pos[1] < cleaned[pos[0]].size - 1
                nC = cleaned[pos[0]][pos[1] + 1]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[1] += 1
                    next
                end
            end
            prevPos = pos.dup
            result = wrap(direction, pos)
            pos = result[0]
            if prevPos == pos
                pos = prevPos.dup
                break
            end
            direction = result[1]
        elsif direction == 1
            if pos[0] < cleaned.size - 1
                nC = cleaned[pos[0] + 1][pos[1]]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[0] += 1
                    next
                end
            end
            prevPos = pos.dup
            result = wrap(direction, pos)
            pos = result[0]
            if prevPos == pos
                pos = prevPos.dup
                break
            end
            direction = result[1]
        elsif direction == 2
            if pos[1] > 0
                nC = cleaned[pos[0]][pos[1] - 1]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[1] -= 1
                    next
                end
            end        
            prevPos = pos.dup
            result = wrap(direction, pos)
            pos = result[0]
            if prevPos == pos
                pos = prevPos.dup
                break
            end
            direction = result[1]
        elsif direction == 3
            if pos[0] > 0
                nC = cleaned[pos[0] - 1][pos[1]]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[0] -= 1
                    next
                end
            end
            prevPos = pos.dup
            result = wrap(direction, pos)
            pos = result[0]
            if prevPos == pos
                pos = prevPos.dup
                break
            end
            direction = result[1]
        end
    end
    
    direction = (direction + turn) % 4
end

puts "#{1000 * (pos[0]+1) + 4 * (pos[1]+1) +direction}"
File.open("rubycoords.txt","w") do |f|
    poses.each {|e| f.puts "#{e.inspect}\n"}
end