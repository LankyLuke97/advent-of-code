require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
testCoord = filename == "input.txt" ? 4000000 : 20

lines = File.readlines(filename)
sensors = Array.new

lines.each do |line|
    line.gsub! "Sensor at x=", ""
    line.gsub! " closest beacon is at x=", ""
    line.gsub! " y=", ""
    line.gsub! ":", ","

    sX, sY, bX, bY = line.split(',').map(&:to_i)

    sensors << [sX, sY, (bX - sX).abs + (bY - sY).abs]
end

acoeffs = Set.new
bcoeffs = Set.new

sensors.each do |x, y, r|
    acoeffs.add(y-x+r+1)
    acoeffs.add(y-x-r-1)
    bcoeffs.add(x+y+r+1)
    bcoeffs.add(x+y-r-1)
end

acoeffs.each do |a|
    bcoeffs.each do |b|
        p = [(b - a) / 2, (a + b) / 2]
        if p.all? { |c| 0 < c && c < testCoord }
            if sensors.all? { |sx, sy, r| lambda_function = ->(p, t) { (p[0] - t[0]).abs + (p[1] - t[1]).abs }; lambda_function.call(p, [sx, sy]) > r }
                puts 4000000 * p[0] + p[1]
            end
        end
    end
end