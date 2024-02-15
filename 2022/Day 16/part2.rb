require 'Set'

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s
lines = File.readlines(filename)

$flows = Hash.new
$distanceGraph = Hash.new
$maxPressureReleased = 0
$checked = Hash.new

def pressureRelease(minutes, mValve, mTime, eValve, eTime, openValves, pressureReleased)
    if minutes == 0
        
        if openValves == ["DD", "JJ", "BB", "HH", "CC", "EE"]
            puts "1. #{openValves} IS CORRECT: #{pressureReleased}, #{minutes} remaining"
        end
        $maxPressureReleased = [$maxPressureReleased, pressureReleased].max
        return
    end

    if mTime == eTime
        minutes -= mTime
        if minutes < 0
            return
        end
        if openValves == ["DD", "JJ", "BB", "HH", "CC", "EE"] or openValves == ["DD", "JJ", "BB", "HH", "CC"]  or openValves == ["DD", "JJ", "BB", "HH"] or openValves == ["DD", "JJ", "BB"]   or openValves == ["DD", "JJ"]  or openValves == ["DD"] 
            releasing = 0
            openValves.each do |o|
                releasing += $flows[o]
            end
            puts "a) #{openValves.inspect} are open at minute #{26 - minutes}, releasing #{releasing} pressure"
            puts "a1) Valve #{mValve} will release #{$flows[mValve]} for #{minutes} minutes for a total of #{$flows[mValve] * minutes}"
            puts "a2) Valve #{eValve} will release #{$flows[eValve]} for #{minutes} minutes for a total of #{$flows[eValve] * minutes}"
        end
        pressureReleased += ($flows[mValve] + $flows[eValve]) * minutes
        mTime = 0
        eTime = 0
    elsif mTime < eTime
        minutes -= mTime
        if minutes < 0
            return
        end
        if openValves == ["DD", "JJ", "BB", "HH", "CC", "EE"] or openValves == ["DD", "JJ", "BB", "HH", "CC"]  or openValves == ["DD", "JJ", "BB", "HH"] or openValves == ["DD", "JJ", "BB"]   or openValves == ["DD", "JJ"]  or openValves == ["DD"] 
            releasing = 0
            openValves.each do |o|
                releasing += $flows[o]
            end
            puts "b) #{openValves.inspect} are open at minute #{26 - minutes}, releasing #{releasing} pressure"
            puts "b1) Valve #{mValve} will release #{$flows[mValve]} for #{minutes} minutes for a total of #{$flows[mValve] * minutes}"
        end
        pressureReleased += ($flows[mValve]) * minutes
        mTime = 0
        eTime -= mTime
    elsif mTime > eTime
        minutes -= eTime
        if minutes < 0
            return
        end
        if openValves == ["DD", "JJ", "BB", "HH", "CC", "EE"] or openValves == ["DD", "JJ", "BB", "HH", "CC"]  or openValves == ["DD", "JJ", "BB", "HH"] or openValves == ["DD", "JJ", "BB"]   or openValves == ["DD", "JJ"]  or openValves == ["DD"] 
            releasing = 0
            openValves.each do |o|
                releasing += $flows[o]
            end
            puts "c) #{openValves.inspect} are open at minute #{26 - minutes}, releasing #{releasing} pressure"
            puts "c1) Valve #{eValve} will release #{$flows[eValve]} for #{minutes} minutes for a total of #{$flows[eValve] * minutes}"
        end
        pressureReleased += ($flows[eValve]) * minutes
        mTime -= eTime
        eTime = 0
    end

    if mTime == 0 and eTime == 0
        $distanceGraph[mValve].each do |nextMValve, nextMTime|
            $distanceGraph[eValve].each do |nextEValve, nextETime|
                if nextEValve == nextMValve or openValves.include?(nextEValve) or openValves.include?(nextMValve) or $flows[nextEValve] == 0 or $flows[nextMValve] == 0
                    next
                end
                
                newOpenValves = openValves.dup
                newOpenValves << nextEValve
                newOpenValves << nextMValve
                pressureRelease(minutes, nextMValve, nextMTime, nextEValve, nextETime, newOpenValves, pressureReleased)
            end
        end
    
        if openValves == ["DD", "JJ", "BB", "HH", "CC", "EE"]
            puts "2. #{openValves} IS CORRECT: #{pressureReleased}, #{minutes} remaining"
        end
        $maxPressureReleased = [$maxPressureReleased, pressureReleased].max
        return
    elsif mTime == 0
        $distanceGraph[mValve].each do |nextValve, time|
            if nextValve == eValve or openValves.include?(nextValve) or $flows[nextValve] == 0
                next
            end
            
            newOpenValves = openValves.dup
            newOpenValves << nextValve
            pressureRelease(minutes, nextValve, time, eValve, eTime, newOpenValves, pressureReleased)
        end
    
        
        if openValves == ["DD", "JJ", "BB", "HH", "CC", "EE"]
            puts "3. #{openValves} IS CORRECT: #{pressureReleased}, #{minutes} remaining"
        end
        $maxPressureReleased = [$maxPressureReleased, pressureReleased].max
        return
    elsif eTime == 0
        $distanceGraph[eValve].each do |nextValve, time|
            if nextValve == mValve or openValves.include?(nextValve) or $flows[nextValve] == 0
                next
            end
            
            newOpenValves = openValves.dup
            newOpenValves << nextValve
            pressureRelease(minutes, mValve, mTime, nextValve, time, newOpenValves, pressureReleased)
        end
        
        if openValves == ["DD", "JJ", "BB", "HH", "CC", "EE"]
            puts "4. #{openValves} IS CORRECT: #{pressureReleased}, #{minutes} remaining"
        end
        $maxPressureReleased = [$maxPressureReleased, pressureReleased].max
        return
    end
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

$distanceGraph.each do |key, value|
    puts "#{key}: #{value.inspect}"
end

pressureRelease(26, 'AA', 0, 'AA', 0, [], 0)

puts $maxPressureReleased