defmodule Day2 do
  def part1(_path) do
    0
  end

  def part2(_path) do
    0
  end
end

test1_correct = 0
test2_correct = 0
test = Day2.part1("day2/data/day2_test.txt")
if test != test1_correct do
    raise "Part 1 test failed; it returned #{test} instead of #{test1_correct}"
end
IO.puts "Part 1 answer from elixir is: #{Day2.part1("day2/data/day2.txt")}"

test = Day2.part2("day2/data/day2_test.txt")
if test != test2_correct do
    raise "Part 2 test failed; it returned #{test} instead of #{test2_correct}"
end
IO.puts "Part 2 answer from elixir is: #{Day2.part2("day2/data/day2.txt")}"