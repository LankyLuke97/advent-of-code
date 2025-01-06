# Advent of Code 2024
## Day 20
### Part 1
While the historians bustle off to investigate the CPU we were just inside, we get going on a race condition festival, where programs compete to see who can finish in the fewest picoseconds around a long and twisting code path.  

The programs are allowed a single **cheat** during the course of a race, where they can disable collisions and move through walls. The cheats can last for 2 picoseconds and you must be back on valid track at the end, else you're disqualified.  

How many cheats are there that save at least 100 picoseconds?
### Solution
Beep beep, it's the A* algorithm, get in! (I don't know, writing 25 of these post-mortems is driving me loopy. For-loopy? While-loopy? Not sure.)  

My initial approach to part 1, which I changed later after doing part 2, was pretty crap. I just ran the A* algorithm once to get the best path without cheats, and then ran it over and over and over for what the best path would be if I treated one of the walls in the maze as not being there, saving the difference between that and the non-cheating approach. I then finished with a list comprehension on a Counter of time saved to find the number of cheats that save 100 steps.

As you can imagine, this was very, very slow, and didn't work for part 2...
### Part 2
Ah, sorry, that ruleset is milliseconds out of date (I ran the numbers and that's like being a century or two out of date, if we think in terms of seconds rather than picoseconds - strange, eh). Now, cheats can last for 20 picoseconds instead of 2. They don't have to last the full time, but there is still only one cheat allowed per race - there's no saving the unused time for a later cheat.

How many cheats are there now that save 100 picoseconds?
### Solution
I got viciously stuck here, in part because my solution to the first part was so rubbish. I initially tried an adjustment to the A* algorithm to provide a shortcut jump from a point on the grid to every other non-wall grid point within 20 steps, one at a time. As you can imagine, if part 1 was slow, this was glacial. I stopped to reassess.  

Eventually, I clocked onto the idea that would save me; part of the reason I didn't realise earlier was because I ignored or missed what seemed to be an insignificant detail on the rubric, but is actually vital: there is a **single path** from the start to the end. That means that our cheats, whatever they are, *must start and end on that path*. Suddenly we can cut out the vast majority of the search space for our A* algorithm.  

Better than that though - we don't need the A* algorithm after finding the path initially! Instead, we can construct the path using the algorithm, and then iterate through each point on the path, up until 100 steps before the end of the path (since we want cheats that save at least 100 steaps, anything after that is of no use). We can then find all the nodes on the path within a Manhattan distance of 20, and check if it is at least 100 steps along the path. If it is, then it's a valuable cheat.  

I'm slightly disappointed with how long this insight took to come to me, though that's a strange metric to worry about in a way. I'm hoping that, had I seen/noted that line of the rubric, it might have come to me sooner.  

**Part 1:** *3,746.41 ms*  
**Part 2:** *6,859.65 ms*  

[Back to all days](/2024)