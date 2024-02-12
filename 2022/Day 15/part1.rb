require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
testRow = filename == "input.txt" ? 2000000 : 10

lines = File.readlines(filename)
sensors = Array.new
minX = 10000000000
maxX = -1

lines.each do |line|
    line.gsub! "Sensor at x=", ""
    line.gsub! " closest beacon is at x=", ""
    line.gsub! " y=", ""
    line.gsub! ":", ","

    sX, sY, bX, bY = line.split(',').map(&:to_i)

    if bX < minX
        minX = bX
    end
    if bX > maxX
        maxX = bX
    end

    sensors << [sX, sY, (bX - sX).abs + (bY - sY).abs]
end

display = Hash.new { |hash, key| hash[key] = Set.new }

sensors.each do |sx, sy, dist|
    (-dist..dist).each do |y|
        ((-dist + y.abs)..(dist - y.abs)).each do |x|
            display[sy + y].add(sx + x)
        end
    end
end

str = ""
(0..display.size - 1).each do |i|
    unless i == 10
        next
    end
    (minX..maxX).each do |j|
        if display[i].include?(j)
            str += "#"
        else
            str += "."
        end
    end
    puts str
    str = ""
end