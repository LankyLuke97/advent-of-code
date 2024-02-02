require 'Set'

def findPath(encoded, path, endPos, shortestDist)
    lastPos = path[-1]
    if lastPos == endPos
        return path.size
    end

    newPos = [[lastPos[0] - 1, lastPos[1]], [lastPos[0], lastPos[1] + 1], [lastPos[0] + 1, lastPos[1]], [lastPos[0], lastPos[1] - 1]].select { |pos| pos[0] >= 0 and pos[0] < encoded.size and pos[1] >= 0 and pos[1] < encoded[0].size and !path.include?(pos) and encoded[pos[0]][pos[1]] - encoded[lastPos[0]][lastPos[1]] < 2 }

    newPos.each do |pos|
        newPath = path
        newPath << pos
        newDist = findPath(encoded, newPath, endPos, shortestDist)
        if newDist < shortestDist
            shortestDist = newDist
        end
    end

    return shortestDist
end

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

startPos = [-1, -1]
endPos = [-1, -1]
encoded = []

lines.each_with_index do |line, lineIndex|
    line.strip!
    num = []
    line.each_char.with_index do |c, charIndex|
        if c =='S'
            num << 0
            startPos = [lineIndex, charIndex]
        elsif c == 'E'
            num << 25
            endPos = [lineIndex, charIndex]
        else
            num << (c.ord - 'a'.ord)
        end
    end
    encoded << num
end

puts findPath(encoded, [startPos], endPos, 1000000000) - 1