require 'Set'

$dirStack = ['/']

$dirs = Set.new
$dirDepth = Hash.new()
$dirMappings = Hash.new([])
$dirSizes = Hash.new(0)
$finalisedDirSizes = Hash.new

sum = 0
MAX_SIZE = 100000

def createPath(stack)
    return stack.join("\\")
end

def findDirSize(dir)
    if $finalisedDirSizes.has_key?(dir)
        return $finalisedDirSizes[dir]
    end

    size = $dirSizes[dir]
    unless $dirMappings[dir].nil? 
        $dirMappings[dir].each do |subDir|
            size += findDirSize(subDir)
        end
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
        path = createPath($dirStack)
        if tokens[0] == 'dir'
            newDir = path + "\\" + tokens[1]
            $dirs.add(newDir)
            $dirMappings[path] += [newDir]
        else
            $dirSizes[path] += tokens[0].to_i
        end
    end
end

sum = 0
$dirs.each do |key, val|
    $dirs.add(key)
    size = findDirSize(key)
    if size <= MAX_SIZE
        sum += size
    end
end

puts sum
