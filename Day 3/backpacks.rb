priority_sum = 0
auth_sum = 0
line_counter = 0

auths = Array.new(3)

File.readlines("input.txt").each do |line|
  line = line.strip.chars.map do |c|
    if ('a'..'z').include?(c)
      c.ord - 'a'.ord + 1
    elsif ('A'..'Z').include?(c)
      c.ord - 'A'.ord + 27
    end
  end

  auths[line_counter] = line
  line_counter += 1

  compartment1 = line.slice(0, line.length / 2)
  compartment2 = line.slice(line.length / 2, line.length / 2)

  priority_sum += (compartment1 & compartment2).sum

  if line_counter == 3
    line_counter = 0
    auth_sum += (auths[0] & auths[1] & auths[2]).sum
  end
end

puts "Sum of priorities: #{priority_sum}\nSum of auths: #{auth_sum}"
