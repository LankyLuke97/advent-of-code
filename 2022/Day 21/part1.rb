filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

$monkeys = Hash.new
$monkeysCalculated = Hash.new

def calculateMonkey(monkey)
    if $monkeysCalculated.include? monkey
        return $monkeysCalculated[monkey]
    end

    if $monkeys[monkey].size == 1
        $monkeysCalculated[monkey] = $monkeys[monkey][0].to_i
        return $monkeys[monkey][0].to_i
    end

    op = $monkeys[monkey]
    val1 = calculateMonkey(op[0])
    val2 = calculateMonkey(op[2])

    if op[1] == '+'
        val = val1 + val2
    elsif op[1] == '-'
        val = val1 - val2
    elsif op[1] == '*'
        val = val1 * val2
    elsif op[1] == '/'
        val = val1 / val2
    end

    $monkeysCalculated[monkey] = val
    return val
end


lines.each do |line|
    monkey, op = line.split(':')
    op.strip!
    $monkeys[monkey] = op.split
end

puts calculateMonkey("root")