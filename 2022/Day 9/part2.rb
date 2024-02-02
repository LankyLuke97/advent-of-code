require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

KNOTS=10
visited = Set.new
visited.add([0,0])
rows = Array.new(KNOTS, 0)
cols = Array.new(KNOTS, 0)

lines.each do |line|
    instruction = line.split
    dist = instruction[1].to_i
    earlyStop = false

    if instruction[0] == 'U'
        (1..dist).each do
            rows[0] += 1

            (1..KNOTS - 1).each do |k|
                if rows[k - 1] - rows[k] < 2
                    colDiff = cols[k - 1] - cols[k]
                    if colDiff.abs < 2
                        break
                    end

                    rows[k] = rows[k-1]
                    if colDiff < 0
                        cols[k] -= 1
                    elsif colDiff > 0
                        cols[k] += 1
                    end
                    next
                end

                rows[k] += 1
                colDiff = cols[k - 1] - cols[k]
                if colDiff < 0
                    cols[k] -= 1
                elsif colDiff > 0
                    cols[k] += 1
                end
            end

            visited.add([cols[-1], rows[-1]])
        end
    elsif instruction[0] == 'R'
        (1..dist).each do
            cols[0] += 1

            (1..KNOTS - 1).each do |k|
                if cols[k - 1] - cols[k] < 2
                    rowDiff = rows[k - 1] - rows[k]
                    if rowDiff.abs < 2
                        break
                    end

                    cols[k] = cols[k-1]
                    if rowDiff < 0
                        rows[k] -= 1
                    elsif rowDiff > 0
                        rows[k] += 1
                    end
                    next
                end

                cols[k] += 1
                rowDiff = rows[k - 1] - rows[k]
                if rowDiff < 0
                    rows[k] -= 1
                elsif rowDiff > 0
                    rows[k] += 1
                end
            end

            visited.add([cols[-1], rows[-1]])
        end
    elsif instruction[0] == 'D'
        (1..dist).each do
            rows[0] -= 1

            (1..KNOTS - 1).each do |k|
                if rows[k - 1] - rows[k] > -2
                    colDiff = cols[k - 1] - cols[k]
                    if colDiff.abs < 2
                        break
                    end

                    rows[k] = rows[k-1]
                    if colDiff < 0
                        cols[k] -= 1
                    elsif colDiff > 0
                        cols[k] += 1
                    end
                    next
                end

                rows[k] -= 1
                colDiff = cols[k - 1] - cols[k]
                if colDiff < 0
                    cols[k] -= 1
                elsif colDiff > 0
                    cols[k] += 1
                end
            end

            visited.add([cols[-1], rows[-1]])
        end
    elsif instruction[0] == 'L'
        (1..dist).each do
            cols[0] -= 1

            (1..KNOTS - 1).each do |k|
                if cols[k - 1] - cols[k] > -2
                    rowDiff = rows[k - 1] - rows[k]
                    if rowDiff.abs < 2
                        break
                    end

                    cols[k] = cols[k-1]
                    if rowDiff < 0
                        rows[k] -= 1
                    elsif rowDiff > 0
                        rows[k] += 1
                    end
                    next
                end

                cols[k] -= 1
                rowDiff = rows[k - 1] - rows[k]
                if rowDiff < 0
                    rows[k] -= 1
                elsif rowDiff > 0
                    rows[k] += 1
                end
            end

            visited.add([cols[-1], rows[-1]])
        end
    end
end

puts visited.size