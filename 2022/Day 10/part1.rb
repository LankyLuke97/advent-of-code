require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)
cycles = [1]
check = [20, 60, 100, 140, 180, 220]
x = 1

lines.each do |line|
    cycles << x
    if line.strip == "noop"
        next
    end
    cycles << x

    x += line.strip.split[1].to_i

    if cycles.size > check[-1]
        break
    end
end
cycles << x

sum = 0
check.each do |c|
    sum += c * cycles[c]
end

puts sum