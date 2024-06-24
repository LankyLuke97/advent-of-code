filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

sum = 0

lines.each do |line|
    dec = 0
    pos = 0
    line.strip!
    line.reverse.each_char do |c|
        if c == '-'
            c = -1
        elsif c == '='
            c = -2
        else
            c = c.to_i
        end

        dec += (c * (5**pos))
        pos += 1
    end
    sum += dec
end

snafu = ''
carry = 0

while sum > 0
    dig = sum % 5 + carry
    sum /= 5
    carry = 0

    if dig == 3
        dig = '='
        carry = 1
    elsif dig == 4
        dig = '-'
        carry = 1
    elsif dig == 5
        dig = '0'
        carry = 1
    end
    
    snafu += "#{dig}"
end

puts snafu.reverse