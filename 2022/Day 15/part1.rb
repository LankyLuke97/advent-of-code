require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
testRow = filename == "input.txt" ? 2000000 : 10

lines = File.readlines(filename)
sensorsDistances = Array.new
beacons = Set.new
sensors = Array.new
minX = 10000000000
maxX = -1
minY = 10000000000
maxY = -1
maxDist = -1

lines.each do |line|
    line.gsub! "Sensor at x=", ""
    line.gsub! " closest beacon is at x=", ""
    line.gsub! " y=", ""
    line.gsub! ":", ","

    sX, sY, bX, bY = line.split(',').map(&:to_i)

    minX = [sX, bX, minX].min
    maxX = [sX, bX, maxX].max
    minY = [sY, bY, minY].min
    maxY = [sY, bY, maxY].max
    maxDist = [(bX - sX).abs + (bY - sY).abs, maxDist].max

    sensorsDistances << [sX, sY, (bX - sX).abs + (bY - sY).abs]
    beacons.add([bX, bY])
    sensors << [sX, sY]
end

display = Hash.new { |hash, key| hash[key] = Set.new }

sensorsDistances.each do |sx, sy, dist|
    (-dist..dist).each do |y|
        unless sy + y == testRow
            next
        end
        ((-dist + y.abs)..(dist - y.abs)).each do |x|
            display[sy + y].add(sx + x)
        end
    end
end

answer = display[testRow].size

sensors.each do |sx, sy|
    if sy == testRow
        answer -= 1
    end
end

beacons.each do |bx, by|
    if by == testRow
        answer -= 1
    end
end

puts answer