# Advent of Code 2024
## Day 10
### Part 1
Next up is a lava production facility on an island floating in the sky where, with a small boop, a reindeer alerts us he needs help. The cervine cartographer is attempting to find all suitable hiking trails on a topographical map. A good trail is as long, even, and gradual as possible - for our purposes, this means that it goes from 0 to 9 on our topographical map composed of digits, stepping up 1 each time, going left, right, up, or down, with no diagonals allowed. A trailhead is the zero in the trail, and the score for a trailhead is the number of 9-height positions reachable from it along a good trail. Whilst the reindeer sets about organising his stationary, we set to work.
### Solution
This was quite an easy problem, again. I iterate over the input, skipping any digit that isn't a zero. If a digit is a zero, I perform a breadth-first search from that location, looking for any 9-height locations, which are added to a set (to ensure we don't count the same location twice from different paths). This breadth first search is quite easily constrained based on the problem rubric; we only include a neighbour if its height (value) is exactly one greater than our current location, and along the x- or y-axis by one. We also stop at the grid edge, obviously.  

I sum the number of 9-height locations reachable in such a manner from each trailhead.
### Part 2
The reindeer now wants us to perform the same exercise, but with ratings instead of scores. The difference is just that, instead of counting how many unique 9-height locations we can reach from each trailhead, we instead count how many unique trails there are from each trailhead. 
### Solution
It must be divinde providence, since I was busy on this day, but I needed almost no adjustments to my part two solution. Instead of tracking a set of 9-height locations reached during the breadth-first search, I switched the data structure to a list, meaning the same location could appear multiple times. Each time it appeared, however, signified that it had been reached by a different path; since I cared nothing more about the path except its existence, I was able to change nothing else, and simply sum the size of these lists for the rating of a trailhead.  

**Part 1:** *5.44 ms*  
**Part 2:** *5.63 ms*  

[Back to all days](/2024)