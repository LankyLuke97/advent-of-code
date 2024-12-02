defmodule Day2 do
  def unsafe_report(report) do
    !(Enum.all?(report, fn {l, r} -> String.to_integer(l) - String.to_integer(r) in 1..3 end) or
      Enum.all?(report, fn {l, r} -> String.to_integer(l) - String.to_integer(r) in -3..-1 end))
  end

  def part1(path) do
    File.stream!(path, :line)
    |> Stream.map(&String.trim/1)
    |> Stream.map(&String.split/1)
    |> Stream.map(&Stream.zip(&1, tl(&1)))
    |> Stream.reject(fn report -> unsafe_report(report) end)
    |> Enum.count()
  end

  def part2(path) do
    File.stream!(path, :line)
    |> Stream.map(&String.trim/1)
    |> Stream.map(&String.split/1)
    |> Enum.map(fn inner_list ->
      [inner_list] ++ Enum.map(0..(Enum.count(inner_list) - 1), fn i ->
        inner_list
        |> Enum.with_index()
        |> Enum.reject(fn {_val, idx} -> idx == i end)
        |> Enum.map(fn {val, _idx} -> val end)
      end)
    end)
    |> Enum.map(fn inner_list ->
      Enum.map(inner_list, &Enum.zip(&1, tl(&1)))
    end)
    |> Enum.reject(fn report_list ->
        Enum.all?(report_list, fn report ->
          unsafe_report(report)
        end)
      end)
    |> Enum.count()
  end
end

test1_correct = 2
test2_correct = 4
test = Day2.part1("day2/data/test.txt")
if test != test1_correct do
    raise "Part 1 test failed; it returned #{test} instead of #{test1_correct}"
end
{u_secs, ans} = :timer.tc(fn -> Day2.part1("day2/data/input.txt") end)
IO.puts "Part 1 answer from elixir is: #{ans}, returned in #{u_secs/1000} ms"

test = Day2.part2("day2/data/test.txt")
if test != test2_correct do
    raise "Part 2 test failed; it returned #{test} instead of #{test2_correct}"
end
{u_secs, ans} = :timer.tc(fn -> Day2.part2("day2/data/input.txt") end)
IO.puts "Part 2 answer from elixir is: #{ans}, returned in #{u_secs/1000} ms"
