filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

m = 0
lines.each do |line|
    m = line.split(',').map(&:to_i).append(m).max
end

m += 2

mapping  = Array.new(m) { Array.new(m) { Array.new(m, 63) } }

lines.each do |line|
    x, y, z = line.split(',').map(&:to_i)

    mapping[x][y][z] = mapping[x][y][z] | 64
    unless x == 0
        mapping[x - 1][y][z] = mapping[x - 1][y][z] & 126
    end

    unless y == 0 
        mapping[x][y - 1][z] = mapping[x][y - 1][z] & 125
    end
    
    unless z == 0
        mapping[x][y][z - 1] = mapping[x][y][z - 1] & 123
    end

    mapping[x + 1][y][z] = mapping[x + 1][y][z] & 119
    mapping[x][y + 1][z] = mapping[x][y + 1][z] & 111
    mapping[x][y][z + 1] = mapping[x][y][z + 1] & 95
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