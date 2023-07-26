current_calories = 0
calories = Array.new

File.readlines('input.txt').each do |line|
  if !line.strip.empty?
    current_calories += line.to_i
  else
    calories << current_calories
    current_calories = 0
  end
end

calories.sort! { |a, b| b <=> a }

puts "Calories carried by top 3: #{calories.slice(0, 3).sum}"
