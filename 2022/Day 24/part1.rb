require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

$startPos = [0, lines[0].index('.')]
$endPos = [lines.count - 1, lines[-1].index('.')]

=begin
Blizzard values
right - 1
down  - 2
left  - 4
up    - 8
Elves - 16
If a position is greater than 16, there are elves and at least one blizzard - dead path
=end
$axes = [[0, 1], [1, 0], [0, -1], [-1, 0], [0, 0]]
$reverseAxes = [[0, -1], [-1, 0], [0, 1], [1, 0], [0, 0]]
$shortestPath = 10000000000000000000
$shortestPathStr = ""
$blizzardsRight = lines[1..-2].map { |line| line[1..-3].each_char.map { |c| { '>' => 1 }[c] || 0 } }
$blizzardsDown = lines[1..-2].map { |line| line[1..-3].each_char.map { |c| { 'v' => 1 }[c] || 0 } }
$blizzardsLeft = lines[1..-2].map { |line| line[1..-3].each_char.map { |c| { '<' => 1 }[c] || 0 } }
$blizzardsUp = lines[1..-2].map { |line| line[1..-3].each_char.map { |c| { '^' => 1 }[c] || 0 } }
$rowLength = lines[0].size - 3
$colLength = lines.size - 2

def display(map, timeStep)
    map.each do |line|
        str = ""
        line.each_with_index do |c, i|
            if line[(i - timeStep) % $rowLength] == 1
                str += '#'
            else 
                str += '.'
            end
        end
        puts str
    end
    puts "#{'X' * map[0].size}"
end

toCheck = [[$startPos, 0, ""]]
checked = Set.new
mod = $rowLength.lcm($colLength)

while toCheck.size > 0
    elfPos = toCheck[0][0]
    steps = toCheck[0][1]
    path = toCheck[0][2]
    toCheck = toCheck[1..-1]

    if checked.include?([elfPos, steps % mod])
        next
    end
    checked.add([elfPos, steps % mod])

    if steps >= $shortestPath
        next
    end
    steps += 1

    (0..4).each do |dir|
        newElfPos = [elfPos[0] + $axes[dir][0], elfPos[1] + $axes[dir][1]]
        newPath = path.dup
        newPath += dir.to_s

        if newElfPos == $endPos
            if steps < $shortestPath
                $shortestPath = steps
                $shortestPathStr = newPath
            end
            break
        end

        if newElfPos == $startPos
            toCheck.append([newElfPos, steps, newPath])
            next
        end

        if newElfPos[0] <= 0 or newElfPos[0] >= $colLength + 1 or newElfPos[1] <= 0 or newElfPos[1] >= $rowLength + 1
            next
        end
        
        checkPos = [newElfPos[0] - 1, newElfPos[1] - 1]
        if $blizzardsRight[checkPos[0]][(checkPos[1] - steps) % $rowLength] == 1
            next
        end
        if $blizzardsDown[(checkPos[0] - steps) % $colLength][checkPos[1]] == 1
            next
        end
        if $blizzardsLeft[checkPos[0]][(checkPos[1] + steps) % $rowLength] == 1
            next
        end
        if $blizzardsUp[(checkPos[0] + steps) % $colLength][checkPos[1]] == 1
            next
        end
        
        toCheck.append([newElfPos, steps, newPath])
    end
end

puts $shortestPath

$shortestPathStr.each_char.with_index do |c, i|
    str = { '4' => 'wait', '0' => 'move right', '1' => 'move down', '2' => 'move left', '3' => 'move up' }[c]
    puts "Minute #{i + 1}, #{str}"
end