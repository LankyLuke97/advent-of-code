# Advent of Code 2024
## Day 18
### Part 1
We've arrived inside a computer at the North Pole. If I had a quid every time that's happened, I'd have two quid; which isn't a lot, but it's strange that it's happened twice...  

A **User** has misunderstood what a pushdown automaton is (I don't blame them) and they're pushing whole bytes down on top of us; we need to flee with the historians!  

First, though, we need to know what locations are safe and what to avoid. Given a list of where the bytes are going to fall on a grid, we need to simulate where all the bytes will be after a kilobyte has fallen, and what our shortest path will be.
### Solution
Thank goodness, a respite after my disastrous day 17. This first part just combines a 'simulation', which is really just parsing the text file and turning then provided coordinates into a grid of walkable and non-walkable locations, and a breadth-first search.  

I don't think there's much more to say here, since this is a well-worn path now, so let's see what's going on in part 2.
### Part 2
The historians are struggling with navigating this pixelated universe, as they aren't as practised as us. We need to figure out how fast they need to go.  

What's the first byte that will cut off the path to the exit once it falls?
### Solution
Right, let's think. The naive solution to this is obvious: instead of simulating the first 1024 steps and then finding the shortest path, I simulate the steps one at a time, running the path-finding algorithm at each step. So long as there is still a path through, then we continue. Once it fails, we return the current byte location.  

Surprisingly, this actually works in a barely acceptable timeframe, about 18 seconds. At the time, I left it here and moved on.  

As I was writing up this post-mortem, however, it occured to me that there's a fairly trivial optimisation. Let's consider the below example, where '.' shows an empty space, '#' shows a previously fallen byte, 'O' shows our current shortest path through the grid, and 'X' shows the byte that's just landed:
```
OO.#OOO
.O#OO#O
.OOO#OO
X..#OO#
..#OO#.
.#.O#..
#.#OOOO
```
There's no point, in scenarios like the above, in running our path algorithm again. The only time we need to find a new path to the end is when a byte lands *on* our current path.  

So, I've just switched to using an A* algorithm for the path algorithm, purely because I have one written for a later day that I was able to copy and paste, which allows the reconstruction of a actual path, as opposed to the very basic BFS I had previously. With this, I can then add an extra check in our simulation: if the current byte is not part of that path, keep going without searching the grid again.  

This provides a whopping 30x speedup for the small memory cost of the path: since we don't actually care to follow the path, I use a set instead of a list (not caring about the order of the grid points, in other words), to allow for fast membership tests from the falling bytes.  

**Part 1:** *8.49 ms*  
**Part 2:** *607.05 ms*  

[Back to all days](/2024)