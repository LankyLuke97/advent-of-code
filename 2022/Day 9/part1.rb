require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

visited = Set.new
visited.add([0,0])
headCol = headRow = tailCol = tailRow = 0

lines.each do |line|
    instruction = line.split
    dist = instruction[1].to_i

    if instruction[0] == 'U'
        (1..dist).each do
            headRow+= 1
            if headRow - tailRow < 2
                next
            end
            tailRow+= 1
            tailCol = headCol
            visited.add([tailCol, tailRow])
        end
    elsif instruction[0] == 'R'
        (1..dist).each do
            headCol+= 1
            if headCol - tailCol < 2
                next
            end
            tailCol+= 1
            tailRow = headRow
            visited.add([tailCol, tailRow])
        end
    elsif instruction[0] == 'D'
        (1..dist).each do
            headRow-= 1
            if headRow - tailRow > -2
                next
            end
            tailRow-= 1
            tailCol = headCol
            visited.add([tailCol, tailRow])
        end
    elsif instruction[0] == 'L'
        (1..dist).each do
            headCol-= 1
            if headCol - tailCol > -2
                next
            end
            tailCol-= 1
            tailRow = headRow
            visited.add([tailCol, tailRow])
        end
    end
end

puts visited.size