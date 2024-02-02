filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

lines.each_with_index do |line, index|
    lines[index] = line.strip
end

answer = 0

scenic = Array.new (lines.size){ Array.new(lines[0].size, 0) }

(0..lines.size - 1).each do |i|
    (0..lines[0].size - 1).each do |j|
        tree = lines[i][j].to_i
        
        left = 0
        (j-1..0).step(-1).each do |ind|
            left += 1
            if lines[i][ind].to_i >= tree
                break
            end
        end

        right = 0
        (j+1..lines[i].size - 1).each do |ind|
            right += 1
            if lines[i][ind].to_i >= tree
                break
            end
        end
        
        up = 0
        (i-1..0).step(-1).each do |ind|
            up += 1
            if lines[ind][j].to_i >= tree
                break
            end
        end

        down = 0
        (i+1..lines.size - 1).each do |ind|
            down += 1
            if lines[ind][j].to_i >= tree
                break
            end
        end
        answer = [answer, up * right * down * left].max
    end
end

puts answer