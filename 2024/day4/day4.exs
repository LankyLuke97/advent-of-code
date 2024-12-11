defmodule Day4 do
  defp extract_diagonals(matrix) do
    height = length(matrix)
    width = length(List.first(matrix))

    0..(height + width - 2)
    |> Enum.map(fn diag_idx ->
      for row <- 0..(height - 1),
          col <- 0..(width - 1),
          row + col == diag_idx,
          do: Enum.at(Enum.at(matrix, row, []), col, nil)
    end)
  end

  def part1(path) do
    File.stream!(path)
    |> Enum.map(&String.trim/1)
    |> Enum.map(&String.graphemes/1)
    |> then(fn lines ->
      forward = Enum.map(lines, &Enum.join/1)
      down = lines
            |> List.zip()
            |> Enum.map(&Enum.join(Tuple.to_list(&1)))
      left_right_diag = extract_diagonals(lines)
      |> Enum.map(&Enum.join(&1))
      right_left_diag = extract_diagonals(Enum.map(lines, &Enum.reverse/1))
      |> Enum.map(&Enum.join(&1))
      [forward, down, left_right_diag, right_left_diag]
    end)
    |> Enum.map(fn direction ->
      Enum.map(direction, fn line ->
        search_pattern = ~r/(?<=X)MA(?=S)|(?<=S)AM(?=X)/
        Enum.count(Regex.scan(search_pattern, line))
      end)
      |> Enum.sum()
    end)
    |> Enum.sum()
  end

  def part2(path) do
    File.stream!(path)
    |> Enum.map(&String.trim/1)
    |> Enum.map(&String.graphemes/1)
    |> then(fn lines ->
      left_right_diag = extract_diagonals(lines)
      |> Enum.map(&Enum.join(&1))
      |> IO.inspect()
      right_left_diag = extract_diagonals(Enum.map(lines, &Enum.reverse/1))
      |> Enum.map(&Enum.join(&1))
      |> IO.inspect()
      [left_right_diag, right_left_diag]
    end)
    |> Enum.map(fn direction ->
      Enum.map(direction, fn line ->
        search_pattern = ~r/(?<=M)A(?=S)|(?<=S)A(?=M)/
        Enum.count(Regex.scan(search_pattern, line))
      end)
      |> Enum.sum()
    end)
  end
end

test1_correct = 18
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
