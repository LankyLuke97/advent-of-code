require 'strscan'

def parseString(input, depth=0)
    result = []

    scanner = StringScanner.new(input)

    until scanner.eos?
        case
        when scanner.scan(/\[/)
            nested_list = parseString(scanner.scan_until(/\]/), depth + 1)
            result << nested_list
            
        when scanner.scan(/\d+/)
            result << scanner.matched.to_i
        when scanner.scan(/,/)
            # Ignore commas
        when scanner.scan(/\s+/)
            # Ignore whitespace
        when scanner.scan(/\]/)
            break  # Exit the loop when encountering ]
        else
            raise "Unexpected character: #{scanner.peek(1)}"
        end
    end

    result
end

def compare(list1, list2)
    if list1.is_a?(Integer) and list2.is_a?(Integer)
        if list1 < list2
            return 1
        elsif list1 > list2
            return -1
        end
        return 0                    
    end

    if !!list1.is_a?(Array) ^ !!list2.is_a?(Array)
        if list1.is_a?(Array)
            return compare(list1, [list2])
        else
            return compare([list1], list2)
        end
    end

    list1.each_with_index do |l1, index|
        if index >= list2.size
            break
        end

        res = compare(list1[index], list2[index])
        unless res == 0
            return res
        end
    end

    return compare(list1.size, list2.size)
end

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

firstDividerIdx = 1
secondDividerIdx = 2
firstDivider = parseString("[[2]]")
secondDivider = parseString("[[6]]")

lines.each do |line|
    line.strip!
    if line.nil? or line.empty?
        next
    end

    packet = parseString(line)

    if compare(packet, firstDivider) == 1
        firstDividerIdx += 1
    end
    if compare(packet, secondDivider) == 1
        secondDividerIdx += 1
    end
end

puts firstDividerIdx * secondDividerIdx