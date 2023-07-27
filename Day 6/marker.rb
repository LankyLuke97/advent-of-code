data = Array.new
MARKER_LENGTH = 14

File.readlines("input.txt").each do |line|
  data << line.strip
end

data = data.flatten[0].split("")
marker_window = data.shift(MARKER_LENGTH)

for i in MARKER_LENGTH..(data.length-1) do
  marker_window << data.shift

  if(marker_window.length > MARKER_LENGTH)
    marker_window.shift
  end

  if(marker_window.to_set.length == MARKER_LENGTH)
    puts "First marker at #{(i + 1).to_s}"
    break
  end
end
