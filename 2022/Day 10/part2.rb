require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)
cycles = [1]
x = 1

lines.each do |line|
    cycles << x
    if line.strip == "noop"
        next
    end
    cycles << x

    x += line.strip.split[1].to_i

    if cycles.size > 240
        break
    end
end
cycles << x

str = ""

(1..240).each do |i|
    if (i - 1) % 40 == 0
        puts str
        str = ""
    end

    p = ((i - 1) % 40)
    if cycles[i] - 1 == p or cycles[i] == p or cycles[i] + 1 == p
        str += '#'
    else
        str += '.'
    end
end
puts str
