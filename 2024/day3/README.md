# Advent of Code 2024
## Day 3
### Part 1
Having arrived next at the North Pole Toboggan Rental Shop, we're invited to check the warehouse manually for CH, since the computers are on the blink, with corrupted memory.  

Given an input like ```xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))```, we need to find all the instances of **mul(**_some number_**,** _another number_**)**, perform the multiplication of the two numbers, and then sum up all the products.
### Solution
Gone are the days where I would have started searching manually, character by character, at the mercy of changing instructions from the AoC overlords! Now I reach for Regex; tremble not at its fickle moods, for I have the knowing of it!; it dances to my tune!

*Ahem*. What I mean to say is that this seems to be a problem neatly suited to regex, and now that I can confidently write a positive and negative lookbehind *and* lookahead, we should be good to go.  

The input is multiple lines for the sake of readability, but it's all the same instruction; so I combine the lines, search for matches of ```(?<=mul\()\d{1,3},\d{1,3}(?=\))```, split the result on commas, convert each part of the list to an integer, and then add the product to the final result - a neat one-liner that I was over-pleased with (I spent far too long getting good at basic regex not too gloat now).
### Part 2
We are presented with a final boss, something to test our mettle...a flag? A flag as to whether or not to perform the multiplication in the form of do()/don't() instructions? Sure, piece of cake.
### Solution
Expanding the regex to also search for do() and don't(), I then iterate through all the matches; if it's a do(), then set the flag to True; if it's don't(), then set the flag to False; if it's a multiplication, only do the multiplication if it's True; easy. We don't even need to track anything in some sort of stack, because only the last instruction counts - i.e., if we see three do() instructions, just one don't() cancels them, we don't need three. Draft that up, and...  

The test result doesn't pass. It's wrong. My hubris!  

...  

Ok, quite an easy fix to cover a silly moment of shortsightedness - the flag needs to start as True and I started it as False; in both the test and the actual inputs, there is a single mul(...) instruction prior to a don't() instruction, meaning my answer was under. Slightly embarrassing, but quickly rectified.  

**Part 1:** *0.813 ms*  
**Part 2:** *0.743 ms*  

[Back to all days](/2024)