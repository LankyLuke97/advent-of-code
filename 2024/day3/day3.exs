defmodule Day3 do
  def part1(path) do
    File.stream!(path)
    |> Enum.map(&String.trim/1)
    |> Enum.join()
    |> then(fn input ->
      Regex.scan(~r/mul\((\d{1,3}),(\d{1,3})\)/, input)
      |> Enum.map(fn [_, x, y] -> {String.to_integer(x), String.to_integer(y)} end)
    end)
    |> Enum.reduce(0, fn {x, y}, acc -> acc + (x * y) end)
  end

  def part2(_path) do
    0
  end
end

test1_correct = 161
test2_correct = 0
test = Day3.part1("day3/data/test.txt")
if test != test1_correct do
    raise "Part 1 test failed; it returned #{test} instead of #{test1_correct}"
end
{u_secs, ans} = :timer.tc(fn -> Day3.part1("day3/data/input.txt") end)
IO.puts "Part 1 answer from elixir is: #{ans}, returned in #{u_secs/1000} ms"

test = Day3.part2("day3/data/test.txt")
if test != test2_correct do
    raise "Part 2 test failed; it returned #{test} instead of #{test2_correct}"
end
{u_secs, ans} = :timer.tc(fn -> Day3.part2("day3/data/input.txt") end)
IO.puts "Part 2 answer from elixir is: #{ans}, returned in #{u_secs/1000} ms"
