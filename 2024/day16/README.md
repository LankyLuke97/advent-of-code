# Advent of Code 2024
## Day 16
### Part 1
Despite the apparently obscene urgency of our mission, we decide to take further time out from searching for CH to watch some of the Reindeer Olympics; actually, that sounds awesome, we should definitely stop to watch.  

The big event is this year is the Reindeer Maze, where the reindeer compete for the lowest score. All the reindeer start on a given start tile, facing east, and need to reach the end. The can move forward one tile at a time for a cost of 1, turn 90 degrees for a cost of 1000 (presumably the hooves are slippery on the ice?), and can't run into or indeed through walls.  

What's the lowest score a reindeer could possibly get?
### Solution
A simple maze problem means we're reaching for that A* path-finding algorithm (although it could have also been Dijkstra's, since we don't care about the actual path here). I won't dive into the details, since this is a solved problem for which there are numerous examples and pseucode. The only interesting way of viewing this is to treat each position in the map as having four copies: one for each direction you can approach be facing when at the node. This leads quite naturally to a three dimensional representation of the map instead of two, and our goal is to reach the end position within any of those dimensions, since we don't care about the direction we're facing when we finish.
### Part 2
Now we know where the best paths are, we can decide where to sit, as there is seating along the edge of all path tiles. There are many factors that go into determining the best place to sit, but the primary decider is whether the tile is on one of the best paths; if it's not, we'd miss all the action. We need to figure out how many different tiles we could sit on, i.e., how many are on at least one of the best paths.
### Solution
Okay, so now instead of just figuring out what the minimum cost is, we also need to reconstruct all minimum paths through the maze and return how many unique path tiles they all pass through. Fine.  

The approach I took again starts with the A* algorithm (useful now that I wrote this instead of Dijkstra's for part 1); whenever a path reaches the end goal, I reconstruct the full path and store the nodes within it in a set in a dictionary; the keys for this dictionary are the costs for the paths, the values are sets of the grid positions that have been visited as part of paths for the given cost.  

Once the full search has run, I take the minimum key in the dictionary, retrieve the set of visited grid positions associated with paths of that cost, and return how many positions we have seen.

**Part 1:** *73.70 ms*  
**Part 2:** *377.69 ms*  

[Back to all days](/2024)