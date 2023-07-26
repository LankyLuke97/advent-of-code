full_overlap = 0
partial_overlap = 0

File.readlines("input.txt").each do |line|
  line = line.strip.split(',').map { |x| x.split('-') }
  range1 = (line[0][0]..line[0][1]).to_a
  range2 = (line[1][0]..line[1][1]).to_a
  overlap_range = range1 & range2

  if overlap_range.length == [range1.length, range2.length].min
    full_overlap += 1
    partial_overlap += 1
  elsif overlap_range.length > 0
    partial_overlap += 1
  end
end

puts "Number of full overlaps: #{full_overlap}, partial_overlaps: #{partial_overlap}"
