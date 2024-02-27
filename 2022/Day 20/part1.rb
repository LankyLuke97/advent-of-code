filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

orderVals = Hash.new
initialZeroInd = -1

lines.each_with_index do |line, index|
    orderVals[index] = line.to_i
    if line.strip == '0'
        initialZeroInd = index
    end
end

order = orderVals.keys.dup

(0..order.size - 1).each do |i|
    currentIndex = order.find_index(i)
    move = orderVals[i]
    if move == 0 
        next
    end
    newIndex = (currentIndex + move <= 0 ? currentIndex +move - 1 : currentIndex + move) % order.size
    if newIndex == currentIndex
        next
    end
    newOrder = Array.new
    
    if newIndex > currentIndex
        #puts "GREATER: currentIndex #{currentIndex}, move #{move}, newIndex #{newIndex}"
        newOrder = (currentIndex > 0 ? order[0..currentIndex-1] : []) + order[currentIndex+1..newIndex] + [order[currentIndex]] + (newIndex < order.size - 1 ? order[newIndex+1..-1] : [])
        #puts "#{(currentIndex > 0 ? order[0..currentIndex-1] : [])} + #{order[currentIndex+1..newIndex]} + #{[i]} + #{(newIndex < order.size - 1 ? order[newIndex+1..-1] : [])}"

        if newOrder.size != order.size
            puts "GREATER: currentIndex #{currentIndex}, move #{move}, newIndex #{newIndex}"
            puts "#{currentIndex}: #{(currentIndex > 0 ? order[0..currentIndex-1] : []).size}"
            puts order[currentIndex+1..newIndex].size
            puts [i].size
            puts "#{newIndex}: #{(newIndex < order.size - 1 ? order[newIndex+1..-1] : []).size}"
        end
    else
        #puts "LESSER: currentIndex #{currentIndex}, move #{move}, newIndex #{newIndex}"
        newOrder = (newIndex > 0 ? order[0..newIndex] : []) + [i] + (newIndex > 0 ? order[newIndex+1..currentIndex-1] : order[newIndex..currentIndex-1]) + (currentIndex < order.size - 1 ? order[currentIndex+1..-1] : [])
        #puts "#{order[0..newIndex]} + #{[i]} + #{order[newIndex+1..currentIndex-1]} + #{order[currentIndex+1..-1]}"

        if newOrder.size != order.size
            puts "LESSER: currentIndex #{currentIndex}, move #{move}, newIndex #{newIndex}"
            puts (newIndex > 0 ? order[0..newIndex] : []).size
            puts [i].size
            puts (newIndex > 0 ? order[newIndex+1..currentIndex-1] : order[newIndex..currentIndex-1]).size
            puts (currentIndex < order.size - 1 ? order[currentIndex+1..-1] : []).size
        end
    end

    order = newOrder
end
answer = 0
zeroIndex = order.find_index(initialZeroInd)
[(1000+zeroIndex) % order.size, (2000+zeroIndex) % order.size, (3000+zeroIndex) % order.size].each do |n|
    answer += orderVals[order[n]]
end
puts answer