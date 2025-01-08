# Advent of Code 2024
## Day 4
### Part 1
Arriving next at the Ceres monitoring station, a small Elf requests help finding the word 'XMAS' in a word search that appears to be made of, yes, exclusively the letters X, M, A, and S; good stuff. The word can be either forward or backwards horizontally, vertically, and, gods above, in both diagonal directions. We need to find them all.
### Solution
This was a mess for me to write, frankly. I started by creating horizontal lines, then vertical lines from the input, and then the two sets of diagonals. I might go and look now at a better way of doing this, because mine is a mess of loops and string building over the coure of thirty lines.  

However, once that's done, the actual answer is quite straight-forward. I just sum the number of times 'XMAS' or 'SAMX' occurs in each of the horizontal, vertical, and diagonal lines. Important to note here is that the reverse of 'XMAS' is not, in fact, 'SMAX' - I will leave it to the reader to guess how long that took me to notice.
### Part 2
In this part, the elf starts by looking at me 'quizzically' because I've misunderstood the assignment. Now, so far as I can tell, I've looked at this and provided an answer, not debated my working; this leads me to believe that this elf *knows the bastard answer, otherwise how can she know I'm wrong?* Additionally, she was the one who gave me the bloody instructions.  

In any case, I instead need to find crossed 'MAS's - i.e. instances that look like this:
```
M.S
.A.
M.S
```
Or some equivalent - again, the MAS could be going backwards (SMA? Or SAM? A lot more obvious without the X, for some reason).  

As a point of interest, this was where I stopped with Elixir the first time through. My solution to part 1 was 16 times slower than the Python and required heavy ChatGPT, so I figured that this wasn't particularly helpful to anyone involved.
### Solution
The obvious starting point is similar to before, constructing diagonal passes through the square grid of text. This time, however, I needed to know the location of each string I found, specifically of the 'A' in the middle - any matching locations in the other set of diagonals would necessarily form the cross pattern I was looking for.  

To that end, I tracked the start location along the grid edge from which each diagonal line began; this allowed me to find the coordinate of the 'A' within the original grid for each instance of either 'MAS' or 'SAM' that I found. I stored these coordinates in a set for each diagonal direction, and then the number of coordinates in the intersection described the number of unique coordinates of crosses between the two.  

Strictly speaking, all the coordinates would have been unique anyway and so I could just as well have used a list, but using sets meant I could do a nice ```len(first_set.intersection(second_set))``` for the answer, which was pleasingly concise.  

**Part 1:** *6.66 ms*  
**Part 2:** *8.53 ms*  

[Back to all days](/2024)