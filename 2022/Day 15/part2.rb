require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
testCoord = filename == "input.txt" ? 4000000 : 20

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

display = Hash.new { |hash, key| hash[key] = Array.new }

(0..testCoord).each do |y|
    puts y
    within = false
    (0..testCoord).each do |x|
        within = false
        sensorsDistances.each do |sx, sy, dist|
            if (sx - x).abs + (sy - y).abs <= dist
                within = true
                break
            end
        end

        unless within
            puts (x*4000000) + y
            break
        end
    end
    unless within
        break
    end
end