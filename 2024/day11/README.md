# Advent of Code 2024
## Day 11
### Part 1
On Pluto, the historians start checking the infinite corridors (what happens when you have infinite time but also infinite corridors to check - who wins in the limit?), our attention is captured by a series of physics-defying stones in a perfect line, on each of which is engraved a number. Every time we blink, each stone transforms itself according to the first of the following three rules which applies to it:
* If the stone is engraved with a 0, the zero is replaced with a 1.
* If the stone is engraved with an even number of digits, it splits into two stones with half of the digit on each (a stone with 2024 would become two stones with 20 and 24 respectively).
* Otherwise, the number on the stone is multiplied by 1.  
We want to know (for some reason) how the stones will evolve if we keep blinking at them. Specifically, we want to know how many stones there will be after 25 blinks.
### Solution
This was a fairly straightforward problem initially, though the solution I'm about to describe doesn't match what is now in the code.  

For each number in our initial list, I checked which rule applied, adding the new number(s) to a new list - I did this to handle the case of splitting stones. Repeating this 25 times, I then counted the number of items in the list and returned the (thankfully correct) answer.
### Part 2
The historians are taking a long time due to the infinite nature of their search and we are, apparently, still bored. How any stones are there after 75 blinks?
### Solution
Well, first, what happens if I just run the same code for part 1 but with 75 repetitions instead of 25? Not a fat lot, that's what. After adding some debugging to output the length of the list at each iteration, I see that it very quickly stalls out after 25, starting to take minutes per iteration of the list by the time we're at 40 blinks. I have no intention of waiting long enough for that to finish - I'd sooner search the infinite corridors of Pluto.  

I realise that I'm probably looking at a recursive memoisation problem here; the trick is just to figure out what I need to memoise. After some deliberation, some trial, and a fair whack of error, I settle on two functions; one that, given a stone and a number of blinks, recursively counts the number of stones that will turn into, and another that applies the rules to a stone (just the once). Both of these get the @cache decorator smacked on them (which, thanks to Fluent Python, I now actually understand better the workings of), and that's that.  

The cache on the the first function is the most important, as it will skip huge numbers of recursions and stone transformations, but the cache on the application of the rules for a given stone does reduce the runtime on part 2 from ~300ms to ~150ms.  

With this process working, I replaced my part 1 solution with the same, and a starting number of blinks of 25; from memory, this was a significant improvement on my original solution.  

When in doubt, give @cache a try.

**Part 1:** *6.13 ms*  
**Part 2:** *155.06 ms*  

[Back to all days](/2024)