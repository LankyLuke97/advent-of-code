defmodule Day4 do
  def part1(_path) do
    0
  end

  def part2(_path) do
    0
  end
end

test1_correct = 0
test2_correct = 0
test = Day4.part1("day4/data/test.txt")
if test != test1_correct do
    raise "Part 1 test failed; it returned #{test} instead of #{test1_correct}"
end
{u_secs, ans} = :timer.tc(fn -> Day4.part1("day4/data/input.txt") end)
IO.puts "Part 1 answer from elixir is: #{ans}, returned in #{u_secs/1000} ms"

test = Day4.part2("day4/data/test.txt")
if test != test2_correct do
    raise "Part 2 test failed; it returned #{test} instead of #{test2_correct}"
end
{u_secs, ans} = :timer.tc(fn -> Day4.part2("day4/data/input.txt") end)
IO.puts "Part 2 answer from elixir is: #{ans}, returned in #{u_secs/1000} ms"