require 'Set'

$dirStack = ['/']

$dirs = Set.new
$dirMappings = Hash.new([])
$dirSizes = Hash.new(0)
$finalisedDirSizes = Hash.new

def findDirSize(dir)
    if $finalisedDirSizes.has_key?(dir)
        return $finalisedDirSizes[dir]
    end

    size = $dirSizes[dir]
    $dirMappings.each do |subDir|
        size += findDirSize(subDir)
    end
    $finalisedDirSizes[dir] = size
    return size
end

filename = ARGV.length() == 0 ? "input.txt" : ARGV[0].to_s

File.readlines(filename).each do |line|
    tokens = line.strip.split

    if tokens[0] == '$'
        if tokens[1] == 'cd'
            if tokens[2] == '..'
                $dirStack.pop
            elsif tokens[2] == '/'
                $dirStack = ['/']
            else
                $dirStack << tokens[2]
            end
        end
    else
        if tokens[0] == 'dir'
            $dirs.add (tokens[1])
            $dirMappings[$dirStack[-1]] << tokens[1]
        else
            $dirSizes[$dirStack[-1]] += tokens[0].to_i
        end
    end
end

sum = 0
MAX_SIZE = 100000

$dirs.each do |dir|
    size = findDirSize(dir)
    if size <= MAX_SIZE
        sum += size
    end
end

puts sum
