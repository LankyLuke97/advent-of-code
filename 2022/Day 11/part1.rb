require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

items = []
operations = []
tests = []

lines.each do |line|
    line.strip!
    if line.empty? or line.include?("Monkey")
        next
    end

    line = line.split(':')

    if line[0].include?("Starting")
        items << line[1].split(',').map {|i| i.strip.to_i}.reverse
    elsif line[0].include?("Operation")
        op = line[1].split
        opEnum = -1
        if op[4] == "old"
            opEnum = 2
        elsif op[3] == '+'
            opEnum = 0
        elsif op[3] == '*'
            opEnum = 1
        end
        operations << [opEnum, op[4].to_i]
    elsif line[0].include?("Test")
        tests << [line[1].split[-1].to_i, -1, -1]
    elsif line[0].include?("true")
        tests[-1][1] = line[1].split[-1].to_i
    elsif line[0].include?("false")
        tests[-1][2] = line[1].split[-1].to_i
    end
end

items.each_with_index do |item, index|
    # puts "Monkey #{index}: #{item.join(",")}"
end

inspected = Array.new(items.size, 0)

(1..20).each do |r|

    items.each_with_index do |item, monkeyIndex|
        operation = operations[monkeyIndex]
        t = tests[monkeyIndex]
        # puts "Monkey #{monkeyIndex}:"
        while(!item.empty?)
            newItem = item.pop
            # puts "\tMonkey inspects an item with a worry level of #{newItem}"
            inspected[monkeyIndex] += 1
            if operation[0] == 0
                newItem += operation[1]
                # puts "\t\tWorry level increases by #{operation[1]} to #{newItem}"
            elsif operation[0] == 1
                newItem *= operation[1]
                # puts "\t\tWorry level is multiplied by #{operation[1]} to #{newItem}"
            else
                newItem = newItem * newItem
                # puts "\t\tWorry level is multiplied by itself to #{newItem}"
            end
            newItem = (newItem / 3).floor
            # puts "\t\tMonkey gets bored with item. Worry level is divided by 3 to #{newItem}"

            if newItem % t[0] == 0
                items[t[1]].unshift(newItem)
                # puts "\t\tCurrent worry level is divisible by #{t[0]}"
                # puts "\t\tItem with worry level #{newItem} is thrown to monkey #{t[1]}"
            else
                items[t[2]].unshift(newItem)
                # puts "\t\tCurrent worry level is not ivisible by #{t[0]}"
                # puts "\t\tItem with worry level #{newItem} is thrown to monkey #{t[2]}"
            end
        end
    end
    # puts "After round #{r}"
    items.each_with_index do |item, index|
        # puts "Monkey #{index}: #{item.join(",")}"
    end
end

inspected.sort! {|x, y| y <=> x}
monkeyBusiness = inspected[0] * inspected[1] #lol
puts monkeyBusiness
