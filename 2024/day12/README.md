# Advent of Code 2024
## Day 12
### Part 1
Next up - Stardew Valley! Or at least, that's what it feels like. We've returned to the infinite farm from last year, where the Elves would like to set up fences around each region of garden plots. They can't figure out how much fence they need to order, however.  

We're given a map of the various plots; each plot grows only a single type of plant and is indicated by a single letter on the map. When multiple plots growing the samme type of plant are touching either horizontally or vertically, they form a region. These are the regions they want to fence in.  

In order to accurately cost the fencing for these pesky elves, we need to know the area and perimeter of all the different regions. The price for a region is the area multiplied by the perimeter; we then need to sum all those prices for all the regions. Good stuff, let's see what we can do.  
### Solution
Ok, let's start with a couple thoughts. The area of a region is obviously pretty trivial to find, as it's just the number of plots that are contained within the region. A method for calculating the perimeter didn't immediately come to me, so I put a pin in that and began the process of finding the various regions.  

The basis of the process is a breadth-first search, obviously. I start at a grid square (in my case, top left) and initialise the search queue to this. While the search queue is not empty, I pop off the first item, and check the surrounding plots. If it's out of the grid, I skip it. If it's the same type of plant (same value) then I add this new square to both the current region and the breadth-first search, with which I continue.  

If it's not the same region, and I haven't 'seen' this plot, I add it to a queue labelled ```next_bfs```; these are plots that aren't part of an already calculated region and therefore are potential starting points for our next region. It's also at this point that I realised how to calculate the perimeter. Every time I encounter a grid plot that is either not the same type as our current region, or I'm trying to check outside of the map, I have a perimeter segment; I can simply increment a counter by 1 each time this happens.  

Once the breadth-first search has run out of plots to check in this region, I update a set called ```seen``` with the whole area, so that future searches know to ignore these plots. I also remove the whole area from the ```next_bfs``` set; this means that I only flood-fill each region once. I then increment the ```price``` counter with the product of the size of the area and the perimeter counter.  

If there are still plots remaining in ```next_bfs```, I pop the first one, reset the various data structures that track the current area, and repeat the process. 
### Part 2
Ah, good news! We're ordering so much fencing that we qualify for a bulk discount. Instead of using the perimeter of each area, the price is instead the product of the area and the *number of sides* the region has.  

There's a warning note here about not connecting fences across diagonally. So, if we had a map that looked like this:
```
AAAAAA
AAABBA
AAABBA
ABBAAA
ABBAAA
AAAAAA
```
There would be two different sides for the As that are on lines 3 and 4 - they wouldn't connect. The rubric describes this as having an in-side and and out-side, which need to match up (there is then an excellent pun about the Möbius Fencing Company and one-sided contract terms). Let's go.
### Solution
Much of the approach here is unchanged from the first part. Instead of a simple counter that I increment for the perimeter, I instead have a dictionary of sides; the keys are direction offsets that I use in the breadth-first search (\[(-1,0),(0,1),(1,0),(0,-1)\]) and the initial values are defaultdicts with a value of list.  

Then, in the locations where previously I would have incremented the perimeter counter, I instead do this:
```
sides[(y_off, x_off)][(_y, _x)[direction_index]].append((_y, _x)[1 - direction_index])
```
Let's break this down. ```(y_off, x_off)``` is the current direction offset from the breadth-first search. ```(_y, _x)``` is the grid point I'm checking after adding those offsets to the current grid point. ```direction_index``` is 0 if ```x_off``` is 0 and 1 otherwise. To illustrate it with an example, if our current search square is at (3, 5) and we're checking to the right, and find a different region, then in ```sides[(0, 1)][6]``` I append 3. This means that there is a fence side on the right hand side of a grid square at 6 on the x axis, at a y point of 3. It's actually at 5 on the x axis, but it doesn't matter really, so long as the coordinates are consistent.  

Nothing else changes, until we get to calculating the price of the region. Instead of the product of the area and the perimeter, I need to calculate the number of sides. For each direction in those sides, and for each coordinate within those directions, I take the list of values and sort them. I then, using quite a nice list comprehension on a zip, count the number of locations where one value is more than one away from the previous value; this represents a break in the line and therefore a new side beginning. I then add one to that to account for the fact that there will be one side at the end that doesn't have a value after it to check against.
```
for direction in sides.values():
    for locations in direction.values():
        loc = sorted(locations)
        num_sides += len([0 for (l1, l2) in zip(loc[1:], loc[:-1]) if l1 - l2 - 1]) + 1
```
That worked first time as well, which is honestly astonishing.

**Part 1:** *39.15 ms*  
**Part 2:** *57.99 ms*  

[Back to all days](/2024)