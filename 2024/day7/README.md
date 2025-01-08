# Advent of Code 2024
## Day 7
### Part 1
Arriving at a bridge that I distinctly remember from previous Christmas', we find a group of engineers trying to repair it (sounds like it might need a from-the-ground rethink). They are apparently almost done, but just need to check some final calibrations; unfortunately, a group of elephants have run off with the operators they need. We can help them by going through their test values and telling them which ones could possibly be produced by their operations.  

Examples of test values might be:
```
190: 10 19
83: 7 5
```
We insert either a + or a * between each number (barring the first one, which is our target) and evaluate left to right; if there is any selection of operators that could allow us to make the target number, then that test is a success and we add its target value to a cumulative result.
### Solution
I figured the obvious solution here was a brute force search, and that it may or may not require some sort of recursion/memoisation approach; however, brute force was enough in the end. For each test, I split the line into the total value and the rest, which was then unpacked. I then appended the first value from that unpacking to my list of potential options. I popped the first of those options and created a list out of it called potentials.  

Then, for each of the remaining numbers in the options list, I would pop it, and a) append the product of it and all numbers in the potentials list to the potentials list and b) add it to all the numbers in the potential list. This simulated the various paths I could theoretically take. Once all the numbers were processed, I just checked whether any of them matched the target. Rinse and repeat.
### Part 2
Ah - some well hidden elephants are holding a third type of operator, the concatenation operator. We should also account for that.
### Solution
This was quite a pleasant part two. It's massively slower, but still well within tolerances (which is to say I don't get bored waiting for it). Given, say 12 and 345, the concatenation operator would return 12,345. The naive approach (for Python, at least, where such godforsaken feats are allowed) would be to cast each integer to a string, then concatenate them, then cast it back to an integer. My impression, however, is that this is unnecessarily slow. Instead, I took a maths-y approach, by doing ```a * (10 ** math.ceil(math.log10(option))) + b```. I don't know for certain that this is faster, because I didn't try a proper benchmark, but it seemed quicker when I tried the two approaches, so let's go with it.  

**Part 1:** *42.24 ms*  
**Part 2:** *4,583.25 ms*  

[Back to all days](/2024)