defmodule Day2 do
  def part1(path) do
    File.stream!(path, :line)
    |> Stream.map(&String.trim/1)
    |> Stream.map(&String.split/1)
    |> Stream.map(&Stream.zip(&1, tl(&1)))
    |> Stream.reject(fn inner ->
      !(Enum.all?(inner, fn {l, r} -> String.to_integer(l) - String.to_integer(r) in 1..3 end) or
      Enum.all?(inner, fn {l, r} -> String.to_integer(l) - String.to_integer(r) in -3..-1 end))
    end)
    |> Enum.count()
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
