defmodule Day1 do
  def part1(path) do
    File.stream!(path, :line)
    |> Stream.map(&String.trim/1)
    |> Stream.map(&String.split(&1, " ", [trim: true]))
    |> Enum.to_list()
    |> Enum.reduce({[], []}, fn [l, r], {acc_l, acc_r} ->
      {[String.to_integer(l) | acc_l], [String.to_integer(r) | acc_r]}
    end)
    |> then(fn {l, r} -> Enum.zip(Enum.sort(l), Enum.sort(r)) end)
    |> Enum.map(fn {l, r} -> abs(r-l) end)
    |> Enum.sum()
  end

  def part2(path) do
    File.stream!(path, :line)
    |> Stream.map(&String.trim/1)
    |> Stream.map(&String.split(&1, " ", [trim: true]))
    |> Enum.to_list()
    |> Enum.reduce({[], []}, fn [l, r], {acc_l, acc_r} ->
      {[String.to_integer(l) | acc_l], [String.to_integer(r) | acc_r]}
    end)
    |> then(fn {l, r} -> {l, Enum.frequencies(r)} end)
    |> then(fn {l, r_freq} ->
      Enum.map(l, fn value ->
        value * Map.get(r_freq, value, 0)
      end)
    end)
    |> Enum.sum()
  end
end

test1_correct = 11
test2_correct = 31
test = Day1.part1("day1/data/day1_test.txt")
if test != test1_correct do
    raise "Part 1 test failed; it returned #{test} instead of #{test1_correct}"
end
IO.puts "Part 1 answer from elixir is: #{Day1.part1("day1/data/day1.txt")}"

test = Day1.part2("day1/data/day1_test.txt")
if test != test2_correct do
    raise "Part 2 test failed; it returned #{test} instead of #{test2_correct}"
end
IO.puts "Part 2 answer from elixir is: #{Day1.part2("day1/data/day1.txt")}"
