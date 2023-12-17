scores = { "X" => 0,
           "Y" => 1,
           "Z" => 2 }
against = { "A" => [3, 4, 8],
            "B" => [1, 5, 9],
            "C" => [2, 6, 7] }
score = 0

File.readlines("input.txt").each do |line| 
  letters = line.split
  score += against[letters[0]][scores[letters[1]]]
end

puts "Total score: #{score}"
