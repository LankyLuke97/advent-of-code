filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

m = 0
lines.each do |line|
    m = line.split(',').map(&:to_i).append(m).max
end

m += 2

mapping  = Array.new(m) { Array.new(m) { Array.new(m, 0) } }

lines.each do |line|
    x, y, z = line.split(',').map(&:to_i)

    mapping[x][y][z] = mapping[x][y][z] | 64
end

changed = true
mapping[0][0][0] = mapping[0][0][0] | 128

while changed
    changed = false

    (0..m-1).each do |x|
        (0..m-1).each do |y|
            (0..m-1).each do |z|
                if mapping[x][y][z] & 192 != 128
                    next
                end

                unless x == 0
                    if mapping[x-1][y][z] & 192 == 0
                        mapping[x-1][y][z] = mapping[x-1][y][z] | 128
                        changed = true
                    elsif mapping[x-1][y][z] & 64 == 64
                        mapping[x-1][y][z] = mapping[x-1][y][z] = mapping[x-1][y][z] | 1
                    end
                end
                
                unless y == 0
                    if mapping[x-1][y][z] & 192 == 0
                        mapping[x-1][y][z] =mapping[x-1][y][z] | 128
                        changed = true
                    elsif mapping[x-1][y][z] & 64 == 64
                        mapping[x-1][y][z] =mapping[x-1][y][z] | 2
                    end
                end

                unless z == 0
                    if mapping[x][y][z-1] & 192 == 0
                        mapping[x][y][z-1] = mapping[x][y][z-1] | 128
                        changed = true
                    elsif mapping[x][y][z-1] & 64 == 64
                        mapping[x][y][z-1] = mapping[x][y][z-1] | 4
                    end
                end

                unless x == m - 1
                    if mapping[x+1][y][z] & 192 == 0
                        mapping[x+1][y][z] = mapping[x+1][y][z] | 128
                        changed = true
                    elsif mapping[x+1][y][z] & 64 == 64
                        mapping[x+1][y][z] = mapping[x+1][y][z] | 8
                    end
                end

                unless y == m - 1
                    if mapping[x][y+1][z] & 192 == 0
                        mapping[x][y+1][z] = mapping[x][y+1][z] | 128
                        changed = true
                    elsif mapping[x][y+1][z] & 64 == 64
                        mapping[x][y+1][z] = mapping[x][y+1][z] | 16
                    end
                end

                unless z == m - 1
                    if mapping[x][y][z+1] & 192 == 0
                        mapping[x][y][z+1] = mapping[x][y][z+1] | 128
                        changed = true
                    elsif mapping[x][y][z+1] & 64 == 64
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

puts exposed