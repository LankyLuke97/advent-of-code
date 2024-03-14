filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

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

mapComplete = false
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
                    next
                end
            end
            if lefts[pos[0]] == -1
                break
            end
            pos[1] = lefts[pos[0]]
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
                    next
                end
            end
            if tops[pos[1]] == -1
                break
            end
            pos[0] = tops[pos[1]]
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
                    next
                end
            end
            if rights[pos[0]] == -1
                break
            end
            pos[1] = rights[pos[0]]
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
                    next
                end
            end
            if bottoms[pos[1]] == -1
                break
            end
            pos[0] = bottoms[pos[1]]
        end
    end

    direction = (direction + turn) % 4
end 

puts "#{1000 * (pos[0]+1) + 4 * (pos[1]+1) +direction}"