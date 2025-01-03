# Advent of Code 2024
## Day 15
### Part 1
We reappear back in our submarines, just in time to help some lanternfish with a rogue robot in a warehouse. The lanternfish have a map of the current warehouse and a list of the moves the robot is going to attempt to make (is that really a rogue robot, then?); they need our help predicting where the robot is going to be. The robots moves are going to fail sometimes. When it encounters a box, it will try to push that box; if there is an empty space following it, then no problem; if there's a wall afterwards, it'll fail to move; if there's another box, then it depends whether there's an empty space, a wall, or another box beyond that.  

The robot can move any number of boxes in a push, so long as there isn't a wall at the end of the chain; it will also (obviously) fail to move into the walls itself.  

We need to figure out where all the boxes will be at the end of the movements from the robot. The lanternfish use a GPS system where the position of a box is determined to be 100 * its distance from the top of the warehouse + its distance from the left wall. We need to return the sum of all these positions for the boxes.
### Solution
I gather that there was a previous problem involving lanternfish that caused some amount of PTSD for the AoC community at large, but this time round the problem seems blessedly easy. We just need to simulate the robot and boxes according to the constraints given in the rubric.  

If the robot attempts to move into a wall, don't. If it attempts to move into an empty space, do. If it attempts to move into a chain of boxes (including a chain of just one box), then check if there is an empty space at the end of the chain. If there is, replace that with a box, and move the robot into the start of the chain; this reflects the end state of moving each box in the chain along one space, but is much quicker.  

Finally, sum the various GPS values for each box.
### Part 2
Just as we save the day here, another robot goes rogue. This time, its in a warehouse where the layout is the same, except everything is twice as wide. 
### Solution
The double width has no practical difference when the robot is moving left or right, but when moving up or down, one box has the ability to push two boxes. This means that I need to check a potentially widening 'front' of boxes for any walls. If there is a wall blocking any of the boxes that would potentially move, then the whole movement fails. If there is an area of empty space into which the robot could push the boxes, then I need to move them all one space - there's no easy chain trick here.  

The solution I came to was based on a breadth-first search (what a useful tool). I start with the search space of just the robot. While the search space isn't empty, I check the grid positions in the direction of movement for each position in the search space. If, at any point, I encounter a wall, then I know the whole movement has failed and break out with that failure. If it's an empty space, then I continue without adding anything to the search space. If it's one half of a box, then I add this new position to the next search space, as well as the other half of the box (this requires me to encode which side of the box is which in my grid representation). Once a 'front' is exhausted, I add all of the affected boxes to a list, and move onto the new 'front' that needs to be checked. Only once we have found all empty spaces can we stop, as that means there are no more boxes that might run into walls.  

With this list of affected boxes, I now work in reverse order, updating the grid to reflect the movement of each box. I work in reverse order to ensure that no information is lost; if I worked forwards, then I would overwrite information that's going to be needed later in the process. Finally, I return the same GPS sum as for part 1.

**Part 1:** *8.23 ms*
**Part 2:** *24.59 ms*  

[Back to all days](/2024)