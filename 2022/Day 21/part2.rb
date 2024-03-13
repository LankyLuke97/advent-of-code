filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

$monkeys = Hash.new
$monkeysCalculated = Hash.new
$humanChain = Array.new

def calculateMonkey(monkey, chain)
    chain.append monkey

    if $monkeysCalculated.include? monkey
        return $monkeysCalculated[monkey]
    end

    if monkey == "humn"
        $humanChain = chain
    end

    if $monkeys[monkey].size == 1
        $monkeysCalculated[monkey] = $monkeys[monkey][0].to_i
        return $monkeys[monkey][0].to_i
    end

    op = $monkeys[monkey]
    val1 = calculateMonkey(op[0], chain.dup)
    val2 = calculateMonkey(op[2], chain.dup)
    
    if monkey == "root"
        return val2-val1
    end

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

diff = calculateMonkey("root", Array.new) 

$humanChain.each do |monkey|
    if monkey == "root"
        diff = ($humanChain.include?($monkeys[monkey][0]) ? diff : -diff) + $monkeysCalculated[$humanChain[1]]
        next
    end

    if monkey == "humn"
        break
    end

    op = $monkeys[monkey]
    order = $humanChain.include?(op[0]) ? 0 : 1
    static = $monkeysCalculated[($humanChain.include?(op[0]) ? op[2] : op[0])]

    if op[1] == '+'
        diff -= static
    elsif op[1] == '-'
        if order == 0
            diff += static
        else
            diff = -(diff - static)
        end
    elsif op[1] == '*'
        diff /= static
    elsif op[1] == '/'
        if order == 0
            diff *= static
        else
            diff = static / diff
        end
    end
end

puts diff