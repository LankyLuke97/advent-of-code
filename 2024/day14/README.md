# Advent of Code 2024
## Day 14
### Part 1
Teleporting to the lobby of Easter Bunny to break into their bathroom, we find that the security has been increased since the last time we broke in to use the same bathroom; is that really a surprise? Instead of just a keypad, they now have what can only be described as a kill box full of robots; fortunately, these robots each have a set velocity, and are perfectly capable of being in the same x/y spot by dint of flying over and under each other. They have another feature worth noting: teleportation. When they would otherwise pass out of the grid we're given, they instead teleport to the other side. Very impressive stuff.  

We need to simulate where the robots will be after 100 seconds, count how many are in each quadrant (ignoring the exact middle horizontally and vertically) to determine the safest location, and then return the product of the quadrants.
### Solution
This was a strangely easy one for this far into AoC, I thought. I didn't bother simulating each individual step for each robot, as I presumed part 2 would be another case of slamming the number up really high (more on that later); instead, I calculated where each robot would be after 100 seconds if they *weren't* teleporting, and the applied modulos for both the x- and y-axes based on the given grid size - easy stuff.  

For each robot, I checked whether, at the end of that process, it was in exactly the middle either horizontally or vertically; if not, I added it to the correct quadrant, and finally returned the product of those quadrants.
### Part 2
Apparently, these robots will very rarely arrange themselves into a picture of a Christmas tree; how many seconds must elapse for the robots to first display that Christmas tree?
### Solution
I was really not expecting this; as I say, I was presuming it would be to check where the robots were after a million seconds or some such. In any case, this was an interesting departure from the norm.  

My final solution, as was the case for so many people, was to simulate the robots for a number of steps, and save the output from each step ro a black and white image in a folder, labelled with the timestamp. I then manually scrolled through the windows explorer, looking for the Christmas tree amongst all the noise (an activity that spawned a number of amusing memes on the Reddit thread). I derived a surprising amount of satisfaction once I finally spotted it.  

I scrolled the Reddit solutions to see if anyone had come up with more programmatic solutions than this; the best that I saw, which I did think was an interesting approach, was to calculate the dispersion of the robots at each step; during the timestep where the robots were forming a Christmas tree image, the dispersion was likely to be the lowest, since they would all be clumped together. In the end, I decided it wasn't worth more than the pleasure of spotting a Christmas tree amongst a bunch of random noise. Go figure that one out.  

**Part 1:** *0.89 ms*
**Part 2:** *N/A*  

[Back to all days](/2024)