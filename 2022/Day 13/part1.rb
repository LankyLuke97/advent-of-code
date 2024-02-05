require 'strscan'

def parseString(input)
    result = []
    current_list = result
  
    scanner = StringScanner.new(input)
  
    until scanner.eos?
        case
        when scanner.scan(/\[/)
            current_list << parseString(scanner.scan_until(/\]/))
        when scanner.scan(/\d+/)
            current_list << scanner.matched.to_i
        when scanner.scan(/,/)
            # Ignore commas
        when scanner.scan(/\s+/)
            # Ignore whitespace
        when scanner.scan(/\]/)
            # Ignore commas
        else
            raise "Unexpected character: #{scanner.peek(1)}"
        end
    end
  
    result
end

def compare(list1, list2, canConvert)
    puts "Compare #{list1.inspect} vs #{list2.inspect}"
    if !!list1.is_a?(Array) ^ !!list2.is_a?(Array)
        unless canConvert    
            return false
        end

        if list1.is_a?(Array)
            puts "Mixed types; convert right to [#{list2}] and retry comparison"
            return compare(list1, [list2], false)
        else
            puts "Mixed types; convert left to [#{list1}] and retry comparison"
            return compare([list1], list2, false)
        end
    end

    list1.each_with_index do |l1, index|
        if index >= list2.size
            puts "Right side ran out of items, so inputs are not in the right order"
            return false
        end
        
        l2 = list2[index]

        if l1.is_a?(Integer) && l2.is_a?(Integer)
            puts "Compare #{l1} vs #{l2}"

            if l1 > l2
                puts "Right side is smaller, so inputs are not in the right order"
                return false
            end

            if(l1 < l2)
                puts "Left side is smaller, so inputs are in the right order"
                return true
            end
        else
            if !compare(l1, l2, canConvert)
                return false
            end
        end
    end
    
    puts "Left side ran out of items, so inputs are in the right order"
    
    true
end

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

left = nil
right = nil
index = 0
correct = 0

lines.each do |line|
    line.strip!
    if left.nil?
        left = parseString(line)
        next
    end

    if right.nil?
        right = parseString(line)
        next
    end

    index += 1

    puts "== Pair #{index} =="

    if compare(left, right, true)
        correct += index
    end

    puts "\n"

    left = nil
    right = nil
end

puts correct