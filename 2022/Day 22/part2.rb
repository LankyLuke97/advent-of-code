require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

cubeSize = filename == "input.txt" ? 50 : 4
pos = [0,lines[0].index('.')]
lengthPad = lines[0..-3].max_by(&:length).length - 1
directions = Hash.new
directions['R'] = 1
directions['L'] = -1
instructions = Array.new
lefts = Array.new(lines.size - 2, -1)
tops = Array.new(lengthPad, -1)
rights = Array.new(lines.size - 2, -1)
bottoms = Array.new(lengthPad, -1)
cleaned = []

def wrapCube(cubeSize, lines)
    innerCorners = Set.new

    lines.each_with_index do |line, y|
        if y == 0 or y == (lines.size - 1)
            next
        end

        line.each_char.with_index do |c, x|
            if x == 0 or x == (line.size - 1)
                next
            end

            numEmpty = 0

            (-1..1).each do |i|
                (-1..1).each do |j|
                    if lines[y+j][x+i] == ' '
                        numEmpty+= 1
                    end
                end
            end

            if numEmpty == 1
                if x % cubeSize == (cubeSize - 1)
                    x+= 1
                end
                if y % cubeSize == (cubeSize - 1)
                    y+= 1
                end
                
                innerCorners << [x, y]
            end
        end
    end
    
    innerCorners = innerCorners.to_a

    # The below could be fleshed out for all the cube unfoldings
    if innerCorners.size == 2
        puts "NEED TO IMPLEMENT"
        return
    elsif innerCorners.size == 3
        distances = innerCorners.combination(2).map { |pair| [(pair[1][0]-pair[0][0]) / cubeSize, (pair[1][1] - pair[0][1]) / cubeSize]}
        puts distances.inspect
    elsif innerCorners.size == 4
        puts "NEED TO IMPLEMENT"
        return
    end
end

instructions = lines[-1].scan(/\d+[RL]/).map { |pair| [pair[0..-2].to_i, directions[pair[-1]]] }
instructions.append([lines[-1][-1].to_i, 0])

lines.each_with_index do |line,index|
    dot_index = line.index('.')
    hash_index = line.index('#')

    if dot_index && (!hash_index || dot_index < hash_index)
        lefts[index] = dot_index
    end

    dot_index = line.rindex('.')
    hash_index = line.rindex('#')

    if dot_index && (!hash_index || dot_index > hash_index)
        rights[index] = dot_index
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
        tops[index] = dot_index
    end

    dot_index = line.rindex('.')
    hash_index = line.rindex('#')

    if dot_index && (!hash_index || dot_index > hash_index)
        bottoms[index] = dot_index
    end
end

been = Array.new(cleaned.size) { Array.new(lengthPad, -1) }

been[pos[0]][pos[1]]=0

direction = 0
instructions.each do |distance, turn|
    if direction == 0
        (1..distance).each do 
            unless pos[1] == cleaned[pos[0]].size - 1
                nC = cleaned[pos[0]][pos[1] + 1]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[1] += 1
                    been[pos[0]][pos[1]]=direction
                    # puts  "0a. Moving to #{pos.inspect}"
                    next
                end
            end
            if lefts[pos[0]] == -1
                break
            end
            pos[1] = lefts[pos[0]]
            # puts  "0b. Moving to #{pos.inspect}"
            been[pos[0]][pos[1]]=direction
        end
    elsif direction == 1
        (1..distance).each do 
            unless pos[0] == cleaned.size - 1
                nC = cleaned[pos[0] + 1][pos[1]]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[0] += 1
                    been[pos[0]][pos[1]]=direction
                    # puts  "1a. Moving to #{pos.inspect}"
                    next
                end
            end
            if tops[pos[1]] == -1
                break
            end
            pos[0] = tops[pos[1]]
            been[pos[0]][pos[1]]=direction
            # puts  "1b. Moving to #{pos.inspect}"
        end
    elsif direction == 2
        (1..distance).each do 
            unless pos[1] == 0
                nC = cleaned[pos[0]][pos[1] - 1]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[1] -= 1
                    been[pos[0]][pos[1]]=direction
                    # puts  "2a. Moving to #{pos.inspect}"
                    next
                end
            end
            if rights[pos[0]] == -1
                break
            end
            pos[1] = rights[pos[0]]
            been[pos[0]][pos[1]]=direction
            # puts  "2b. Moving to #{pos.inspect}"
        end
    elsif direction == 3
        (1..distance).each do 
            unless pos[0] == 0
                nC = cleaned[pos[0] - 1][pos[1]]
                if nC == '#'
                    break
                end
                if nC == '.'
                    pos[0] -= 1
                    been[pos[0]][pos[1]]=direction
                    # puts  "3a. Moving to #{pos.inspect}"
                    next
                end
            end
            if bottoms[pos[1]] == -1
                break
            end
            pos[0] = bottoms[pos[1]]
            been[pos[0]][pos[1]]=direction
            # puts  "3b. Moving to #{pos.inspect}"
        end
    end

    direction = (direction + turn) % 4
    # puts  "Turning to #{direction}"
    # puts "Go #{distance}, turn #{turn}, facing #{direction}"
end 

cleaned.each_with_index do |line, yInd|
    str = ""
    line.each_char.with_index do |c, xInd|
        b = been[yInd][xInd]
        if [yInd, xInd] == [148, 35]
            str +='O'
        else
            str += c
        end
=begin
        if b == -1
            str += c
        elsif b == 0
            str += ">"
        elsif b == 1
            str += "v"
        elsif b == 2
            str += "<"
        elsif b == 3
            str += "^"
        end
=end
    end
    # puts str
end

puts pos.inspect
puts direction

puts "#{1000 * (pos[0]+1) + 4 * (pos[1]+1) +direction}"

wrapCube(cubeSize, cleaned)