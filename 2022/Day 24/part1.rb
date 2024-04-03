require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

horizontalSize = lines[0].strip.size
verticalSize = lines.size

start = [lines[0].index('.'), 0]
finish = [lines[-1].index('.'), verticalSize - 1]

paths = [[1, start]]
blizzards = Hash.new
directions = [[0, -1], [1, 0], [0, 1], [-1, 0]]

lines.each_with_index do |line, y|
    line.strip.each_char.with_index do |c, x|
        if c == '#' or c == '.'
            next
        end
        pos = [x, y]
        movement = []

        if c == '^'
            movement = directions[0]
        elsif c == '>'
            movement = directions[1]
        elsif c == 'v'
            movement = directions[2]
        elsif c == '<'
            movement = directions[3]
        end

        unless blizzards.include? pos
            blizzards[pos] = []
        end
        blizzards[pos].append movement
    end
end

foundEnd = false

while !foundEnd
    newPaths = []
    puts "NEW LOOP:\n#{paths.size} different paths, with size #{paths[0][0]}"
    paths.each do |path|
        #puts "Checking #{path[-1].inspect}"

        if path[-1] == finish
            puts "Shortest path is #{path[0]}\n"
            foundEnd = true
            break
        end

        if blizzards.include? path[-1]
            next
        end
        unless path[-1] == start
            if path[-1][0] == 0 or path[-1][0] == (horizontalSize - 1) or path[-1][1] == 0 or path[-1][1] == (verticalSize - 1)
                next
            end
        end
        
        newPath = path.dup
        newPath[0] += 1
        newPaths.append newPath
        directions.each do |dir|
            newPath = path.dup
            newPath[0] += 1
            newPath[-1] = [path[-1][0] + dir[0], path[-1][1] + dir[1]]
            newPaths.append newPath
        end
    end

    paths = newPaths.dup
    #puts "After: #{paths.inspect}"

    newBlizzards = Hash.new

    blizzards.each do |pos, directions|
        #puts "Sorting blizzards moving #{directions.inspect} at #{pos.inspect}"
        directions.each do |direction|
            newPos = [pos[0] + direction[0], pos[1] + direction[1]]
            if newPos[0] == 0
                newPos[0] = horizontalSize-2
            elsif newPos[0] == horizontalSize - 1
                newPos[0] == 1
            elsif newPos[1] == 0
                newPos[1] = verticalSize - 2
            elsif newPos[1] == verticalSize - 1
                newPos[1] = 1
            end

            unless newBlizzards.include? newPos
                newBlizzards[newPos] = []
            end
            newBlizzards[newPos].append direction
        end
    end

    blizzards = newBlizzards.dup
end