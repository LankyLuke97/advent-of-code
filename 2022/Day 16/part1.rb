require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

$flows = Hash.new
$graph = Hash.new
$maxPressureReleased = 0
$checked = Hash.new

def pressureRelease(minutes, currentValve, openValves, currentPressurePerMinute, pressureReleased)
    if minutes == 0
        $maxPressureReleased = [$maxPressureReleased, pressureReleased].max
        $checked[currentValve] = 0
        return 0
    end

    pressureReleased += currentPressurePerMinute

    unless openValves.include?(currentValve) or $flows[currentValve] == 0
        newOpenValves = openValves.dup
        newOpenValves << currentValve
        pressureRelease(minutes - 1, currentValve, newOpenValves, currentPressurePerMinute + $flows[currentValve], pressureReleased)
    end

    $graph[currentValve].each do |nextValve|
        if $checked.keys.include?(nextValve)

        else 
            pressureRelease(minutes - 1, nextValve, openValves, currentPressurePerMinute, pressureReleased)
        end
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
    $graph[valve] = leadsTo
end

$graph.each do |key, val|
    val.each do |v|
        $graph[v].add(key)
    end
end

pressureRelease(30, 'AA', [], 0, 0)

puts $maxPressureReleased