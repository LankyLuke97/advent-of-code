require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

$flows = Hash.new
$distanceGraph = Hash.new
$pressureWithValves = Hash.new
$checked = Hash.new

def pressureRelease(minutes, currentValve, openValves, pressureReleased)
    if minutes == 0
        if !$pressureWithValves.include?(openValves)
            $pressureWithValves[openValves] = pressureReleased
        end
        return
    end
    pressureReleased += $flows[currentValve] * minutes

    $distanceGraph[currentValve].each do |nextValve, time|
        if openValves.include?(nextValve) or $flows[nextValve] == 0
            next
        end

        remainingTime = minutes - time

        if remainingTime < 0
            next
        end
        
        newOpenValves = openValves.dup
        newOpenValves << nextValve
        pressureRelease(remainingTime, nextValve, newOpenValves, pressureReleased)
    end

    if !$pressureWithValves.include?(openValves)
        $pressureWithValves[openValves] = pressureReleased
    end
    return
end

lines.each do |line|
    line.strip!
    line.gsub! "Valve ", ""
    line.gsub! "has flow rate=", ""
    line.gsub! "; tunnel leads to valve", ""
    line.gsub! "; tunnels lead to valves", ""
    line.gsub! ",", ""

    line = line.split

    valve = line[0]
    flow = line[1].to_i
    leadsTo = Set.new(line[2..-1])
    
    $flows[valve] = flow
    $distanceGraph[valve] = leadsTo
end

$distanceGraph.each do |valve, leadsTo|
    newValue = Hash[$distanceGraph.keys.map {|k| [k, 1000000]}]
    leadsTo.each do |v|
        newValue[v] = 1
    end
    newValue[valve] = 0
    $distanceGraph[valve] = newValue
end

$distanceGraph.keys.each do |k|
    $distanceGraph.keys.each do |i|
        $distanceGraph.keys.each do |j|
            $distanceGraph[i][j] = [$distanceGraph[i][j], $distanceGraph[i][k] + $distanceGraph[k][j]].min
        end
    end
end

$distanceGraph.each do |key, inner_hash|
    $distanceGraph[key] = inner_hash.transform_values { |val| val + 1 }
end

pressureRelease(26, 'AA', [], 0)
maxPressure = 0

$pressureWithValves.each do |key1, value1|
    $pressureWithValves.each do |key2, value2|
        unless key1 & key2 == []
            next
        end
        maxPressure = [maxPressure, value1 + value2].max
    end
end

puts maxPressure