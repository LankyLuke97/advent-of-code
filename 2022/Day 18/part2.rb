filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

m = 0
lines.each do |line|
    m = line.split(',').map(&:to_i).append(m).max
end

m += 4

mapping  = Array.new(m) { Array.new(m) { Array.new(m, 0) } }

lines.each do |line|
    x, y, z = line.split(',').map(&:to_i)

    mapping[x+1][y+1][z+1] = mapping[x+1][y+1][z+1] | 64
end

changed = true
mapping[0][0][0] = mapping[0][0][0] | 128

while changed
    changed = false

    (0..m-1).each do |x|
        (0..m-1).each do |y|
            (0..m-1).each do |z|
                if (mapping[x][y][z] & 192) != 128
                    next
                end

                unless x == 0
                    if (mapping[x-1][y][z] & 192) == 0
                        mapping[x-1][y][z] = mapping[x-1][y][z] | 128
                        changed = true
                    elsif (mapping[x-1][y][z] & 64) == 64
                        mapping[x-1][y][z] = mapping[x-1][y][z] | 1
                    end
                end
                
                unless y == 0
                    if (mapping[x][y-1][z] & 192) == 0
                        mapping[x][y-1][z] = mapping[x][y-1][z] | 128
                        changed = true
                    elsif (mapping[x][y-1][z] & 64) == 64
                        mapping[x][y-1][z] = mapping[x][y-1][z] | 2
                    end
                end

                unless z == 0
                    if (mapping[x][y][z-1] & 192) == 0
                        mapping[x][y][z-1] = mapping[x][y][z-1] | 128
                        changed = true
                    elsif (mapping[x][y][z-1] & 64) == 64
                        mapping[x][y][z-1] = mapping[x][y][z-1] | 4
                    end
                end

                unless x == m - 1
                    if (mapping[x+1][y][z] & 192) == 0
                        mapping[x+1][y][z] = mapping[x+1][y][z] | 128
                        changed = true
                    elsif (mapping[x+1][y][z] & 64) == 64
                        mapping[x+1][y][z] = mapping[x+1][y][z] | 8
                    end
                end

                unless y == m - 1
                    if (mapping[x][y+1][z] & 192) == 0
                        mapping[x][y+1][z] = mapping[x][y+1][z] | 128
                        changed = true
                    elsif (mapping[x][y+1][z] & 64) == 64
                        mapping[x][y+1][z] = mapping[x][y+1][z] | 16
                    end
                end

                unless z == m - 1
                    if (mapping[x][y][z+1] & 192) == 0
                        mapping[x][y][z+1] = mapping[x][y][z+1] | 128
                        changed = true
                    elsif (mapping[x][y][z+1] & 64) == 64
                        mapping[x][y][z+1] = mapping[x][y][z+1] | 32
                    end
                end
            end
        end
    end
end

exposed = 0
(0..m-1).each do |x|
    (0..m-1).each do |y|
        (0..m-1).each do |z|
            check = mapping[x][y][z]
            if check & 64 == 0
                next
            end
            check = (check & 63)
            count = 0
            while check > 0
                count += check & 1
                check >>= 1
            end
            exposed += count
        end
    end
end

=begin
mapping.each_with_index do |layer, ind|
    puts "LAYER #{ind}:\n-------------------------"
        str = "  "
        (0..layer[0].size - 1).each do |i|
            str += "#{i.to_s[-1]}"
        end
        puts str
        layer_exposd = 0
        layer.each_with_index do |row, index|
            str = "#{index.to_s[-1]} " 
            row.each do |c|
                if c & 192 == 192
                    str += '?'
                elsif c & 128 == 128
                    str += '.'
                elsif c & 64 == 64
                    count = 0
                    check = c & 63
                    while check > 0
                        count += check & 1
                        check >>= 1
                    end
                    layer_exposd += count
                    if count == 0
                        str += ' '
                    else
                        str += count.to_s
                    end
                else 
                    str +='#'
                end
            end
            puts str
        end
    puts "-------------------------"
end
=end
puts exposed