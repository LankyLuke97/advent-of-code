# Advent of Code 2024
## Day 19
### Part 1
The next stop of our little odyssey is at the hot springs on Gear Island, which I remember all too well from last year. This year, however, nothing seems to be going wrong, and we venture to visit the onsen next door - only to be drafted into some free labour.  

The Official Onsen Branding Expert (OOBE? Terrible acronym) has produced a list of designs, a long sequence of stripe colours, that they would like to display using a series of striped towels placed side by side. So we might have the towels ```ggr```, ```g```, and ```r```, and the pattern ```ggrgrg```; we can make this a number of ways, but the obvious one is ```ggr->g->r->g```. We can't reverse a pattern, however, as the would cause the onsen logo to face the wrong way or be upside-down.  

The staff can get us as many copies of each towel pattern as we like. How many of the OOBE's list of designs are possible?
### Solution
I struggled so much the Gear Island problem last year, because I couldn't for the life of me figure out the dynamic programming approach required to solve it.  

This definitely also presents itself as a recursive problem to my mind, since it seems easiest to define and, based on the lengths of the patterns, I think I'm unlikely to have issues with the size of the call stack.  

The difference between this year and last year is that I bloody well know how to solve a recursive problem properly now.  

So, the recursive definition is this: a pattern can be made out of the provided towels if the pattern starts with one of the towels, and the rest of the pattern after that starting towel can be constructed out of the available towels. The base cases are that the pattern doesn't start with any of the available towels, in which case this approach doesn't work and we return 0, or there is a towel that exactly matches the whole pattern, in which case we have succeeded and return 1.  

Then we stick a cache on it because it's too slow otherwise.
### Part 2
The staff don't like some of the approaches to the designs we've suggested (why on earth does this matter if the overall pattern is what we care about?); to avoid endlessly rearranging towels, let's give them every possible option.  

For our answer, we want the sum of different ways the possible patterns can be made.
### Solution
Cache, cache, memoised cache. One really has to marvel at what modern programming languages can do for you out of the box, and then question what we lose in return.  

The solution here is almost identical to part 1, except I made a change to the recursive find_pattern: instead of just returning 1 as soon as it finds *some* solution to the pattern with the given towels, it instead finds all the possible ways to make that pattern and sums them, recursively. Then, to keep part 1 working, I just add a wrapper to add 1 to a cumulative answer if the result from find_patterns is not 0.  

An interesting note here is that, by dint of using the same cached function for both part 1 and part 2, part 2 runs about 300 times faster than part 1. Not often you see that, at least in my code.

**Part 1:** *960.42 ms*  
**Part 2:** *3.07 ms*  

[Back to all days](/2024)