require 'Set'

class MinPriorityQueue
    def initialize
        @heap = []
    end
  
    def size
        @heap.size
    end
  
    def empty?
        @heap.empty?
    end
  
    def enqueue(element, priority)
        node = { element: element, priority: priority }
        @heap << node
        heapify_up(size - 1)
    end
  
    def dequeue
        return nil if empty?
    
        swap(0, size - 1)
        min_node = @heap.pop
        heapify_down(0)
        min_node[:element]
    end

    def update_priority(element, new_priority)
        index = @heap.index { |node| node[:element] == element }
    
        return unless index
    
        old_priority = @heap[index][:priority]
        @heap[index][:priority] = new_priority
    
        if new_priority < old_priority
            heapify_up(index)
        else
            heapify_down(index)
        end
    end
  
    private
  
    def heapify_up(index)
        while index > 0
            parent_index = (index - 1) / 2
  
            break if @heap[parent_index][:priority] <= @heap[index][:priority]
    
            swap(index, parent_index)
            index = parent_index
        end
    end
  
    def heapify_down(index)
        while true
            left_child_index = 2 * index + 1
            right_child_index = 2 * index + 2
            smallest = index
    
            if left_child_index < size && @heap[left_child_index][:priority] < @heap[smallest][:priority]
                smallest = left_child_index
            end
    
            if right_child_index < size && @heap[right_child_index][:priority] < @heap[smallest][:priority]
                smallest = right_child_index
            end
    
            break if smallest == index
    
            swap(index, smallest)
            index = smallest
        end
    end
  
    def swap(i, j)
        @heap[i], @heap[j] = @heap[j], @heap[i]
    end
end

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

lines = File.readlines(filename)

startPos = -1
endPos = -1

verticalSize = lines.size
horizontalSize = lines[0].size - 1
graph = {}
distances = {}
queue = MinPriorityQueue.new

lines.each_with_index do |line, lineIndex|
    line.strip!
    line.each_char.with_index do |c, charIndex|
        index = lineIndex * horizontalSize + charIndex
        if c =='S'
            startPos = index
            queue.enqueue(index, 0)
            distances[index] = 0
        else
            if c == 'E'
                endPos = index
            end

            queue.enqueue(index, 2000000000)
            distances[index] = 2000000000
        end

        graph[index] = []
        thisHeight = c == 'S' ? 0 : c == 'E' ? 25 : c.ord - 97

        unless lineIndex == 0
            thatHeight = lines[lineIndex - 1][charIndex] == 'S' ? 0 : lines[lineIndex - 1][charIndex] == 'E' ? 25 : lines[lineIndex - 1][charIndex].ord - 97
            dist = thatHeight - thisHeight <= 1 ? 1 : 1000000
            graph[index] << [index - horizontalSize, dist]
        end
        
        unless lineIndex == verticalSize - 1
            thatHeight = lines[lineIndex + 1][charIndex] == 'S' ? 0 : lines[lineIndex + 1][charIndex] == 'E' ? 25 : lines[lineIndex + 1][charIndex].ord - 97
            dist = thatHeight - thisHeight <= 1 ? 1 : 1000000
            graph[index] << [index + horizontalSize, dist]
        end

        unless charIndex == 0
            thatHeight = lines[lineIndex][charIndex - 1] == 'S' ? 0 : lines[lineIndex][charIndex - 1] == 'E' ? 25 : lines[lineIndex][charIndex - 1].ord - 97
            dist = thatHeight - thisHeight <= 1 ? 1 : 1000000
            graph[index] << [index - 1, dist]
        end

        unless charIndex == horizontalSize - 1
            thatHeight = lines[lineIndex][charIndex + 1] == 'S' ? 0 : lines[lineIndex][charIndex + 1] == 'E' ? 25 : lines[lineIndex][charIndex + 1].ord - 97
            dist = thatHeight - thisHeight <= 1 ? 1 : 1000000
            graph[index] << [index + 1, dist]
        end
    end
end

while !queue.empty?
    index = queue.dequeue

    graph[index].each do |neighbour|
        alt = distances[index] + neighbour[1]
        if alt < distances[neighbour[0]]
            distances[neighbour[0]] = alt
            queue.update_priority(neighbour[0], alt)
        end
    end
end

puts distances[endPos]