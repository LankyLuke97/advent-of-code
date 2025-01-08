# Advent of Code 2024
## Day 8
### Part 1
Arriving next at the Easter Bunny's secret headquarters, we find that antennae have been erected to coerce the populace into purchasing mediocre chocolate as a Christmas present - that bastard bunny! Not on our watch!  

Presented with a grid of these antennae, we need to find their *antinodes* - the locations where, for two nodes of the same frequency, one of the antennae is twice as far away as the other. Frequency is determined by which alphanumeric character represents the antennae. 
### Solution
Quite a straightforward problem, here. I iterate through the grid, adding the coordinates of each antenna (let's call these nodes, so I can stop writing antennae) to a dictionary where the keys are the various frequencies. Once that's done, I iterate through all of the frequencies. For each pair of nodes in that frequency, I calculate the location of the antinode either side, and add them to a set if they lie within the grid we've been given.
### Part 2
Once again, we have missed some crucial detail. Due to 'resonant harmonics' (?), antinodes occur at any point that is exactly in line with two nodes of the same frequency, including at the nodes themselves. We really should start getting all the information required before haring off on our initial calculations...
### Solution
A slightly more complex approach is required here, but not much of one. Whereas in part one I calculated the vector between the two nodes, and then checked the grid locations that vector either side of the two nodes, here an extra step is required. I find the greatest common denominator of each component of that vector, and then divide each component by the gcd. This finds the smallest movement on the grid that maintains whole number coordinates.  

With that, I then iterate steps in each direction from one of the nodes, adding the vector each time, until we reach a location outside of the grid. This is repeated for all pairs of nodes of the same frequency, for all frequencies.  

**Part 1:** *0.37 ms*  
**Part 2:** *2.67 ms*  

[Back to all days](/2024)