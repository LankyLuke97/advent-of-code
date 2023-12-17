arrangement = Array.new
actions = Array.new
stacks = Array.new
reading_actions = false

File.readlines("input.txt").each do |line|
  if line.strip.empty?
    reading_actions = true
  elsif !reading_actions
    arrangement << line
  else
    actions << line.strip.split.filter_map { |x| x.to_i if x.to_i != 0 }
  end
end

arrangement.reverse!
num_containers = arrangement.shift.strip.split.length

arrangement.each do |line|
  for i in 0..(num_containers-1) do
    if stacks[i].nil?
      stacks[i] = Array.new
    end
    crate = line[0..3].strip
    line = line[4..-1]
    if !crate.empty?
      stacks[i] << crate[1]
    end
  end
end


actions.each do |action|
#  stacks[action[2] - 1] << stacks[action[1] - 1][-(action[0])..-1].reverse # Part 1
  stacks[action[2] - 1] << stacks[action[1] - 1][-(action[0])..-1] # Part 2 
  stacks[action[2] - 1].flatten!
  if action[0] == stacks[action[1] - 1].length
    stacks[action[1] - 1] = Array.new
  else
    stacks[action[1] - 1] = stacks[action[1] - 1][0..(stacks[action[1] - 1].length - action[0] - 1)]
  end
end

puts "Result: #{(stacks.map {|x| x.last()}).flatten.join}"

