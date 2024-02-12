require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

solid = Hash.new { |hash, key| hash[key] = Set.new }

maxY = 0

lines.each do |line|
    currentX = -1
    currentY = -1
    nextX = -1
    nextY = -1

    points = line.split(' -> ')
    currentX, currentY = points[0].split(',').map(&:to_i)
    
    points[1..-1].each do |point|
        nextX, nextY = point.split(',').map(&:to_i)

        dX = nextX - currentX
        dY = nextY - currentY
        xDir = dX == 0 ? 1 : dX / dX.abs
        yDir = dY == 0 ? 1 : dY / dY.abs
        
        (0..dX.abs).each do |x|
            (0..dY.abs).each do |y|
                if currentY + (y * yDir) > maxY
                    maxY = currentY + (y * yDir)
                end
                solid[currentX + (x * xDir)].add(currentY + (y * yDir))
            end
        end

        currentX = nextX
        currentY = nextY
    end
end

minX = solid.keys.min
maxX = solid.keys.max
maxY += 2
units = 0

while true
    currentX = 500
    currentY = 0

    while true
        nextY = currentY + 1

        unless solid[currentX].include?(nextY) or nextY == maxY
            currentY = nextY
            next
        end

        nextX = currentX - 1

        unless solid[nextX].include?(nextY) or nextY == maxY
            currentX = nextX
            currentY = nextY

            next
        end

        nextX = currentX + 1

        unless solid[nextX].include?(nextY) or nextY == maxY
            currentX = nextX
            currentY = nextY

            next
        end

        solid[currentX].add(currentY)
        break
    end

    units += 1

    if solid[500].include?(0)
        break
    end
end

puts units