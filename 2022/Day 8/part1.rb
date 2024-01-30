filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

lines.each_with_index do |line, index|
    lines[index] = line.strip
end

leftMapping = []
rightMapping = []
upMapping = Array.new(lines.size) { Array.new(lines[0].size, 0) }
downMapping = Array.new(lines.size) { Array.new(lines[0].size, 0) }

lines.each do |line|
    maxHeight = -1
    lineMapping = []
    line.each_char do |c|
        lineMapping << maxHeight
        maxHeight = [maxHeight, c.to_i].max
    end
    leftMapping << lineMapping
    maxHeight = -1
    lineMapping = []

    line = line.reverse
    line.each_char do |c|
        lineMapping << maxHeight
        maxHeight = [maxHeight, c.to_i].max
    end

    rightMapping << lineMapping.reverse
end

(0..lines[0].size - 1).each do |j|
    maxHeight = -1
    (0..lines.size - 1).each do |i|
        lineMapping = upMapping[i]
        lineMapping[j] = maxHeight
        upMapping[i] = lineMapping
        maxHeight = [maxHeight, lines[i][j].to_i].max
    end
end

(0..lines[0].size - 1).each do |j|
    maxHeight = -1
    (0..lines.size - 1).each do |i|
        lineMapping = downMapping[i]
        lineMapping[j] = maxHeight
        downMapping[i] = lineMapping
        maxHeight = [maxHeight, lines[lines.size - 1 - i][j].to_i].max
    end
end

downMapping = downMapping.reverse

answer = 0
visible = Array.new(lines.size) { Array.new(lines[0].size, 0) }

(0..lines.size - 1).each do |i|
    (0..lines[0].size - 1).each do |j|
        tree = lines[i][j].to_i
        if tree > leftMapping[i][j]
            visible[i][j] = 1
            next
        end

        if tree > rightMapping[i][j]
            visible[i][j] = 1
            next
        end

        if tree > upMapping[i][j]
            visible[i][j] = 1
            next
        end

        if tree > downMapping[i][j]
            visible[i][j] = 1
            next
        end
    end
end

visible.each do |row|
    # Iterate through each element in the row and add it to the sum
    row.each do |element|
        answer += element
    end
end

puts answer