# Advent of Code 2024
## Day 17
### Part 1
Departing from a presumably thrilling Reindeer Olympics, we suddenly find ourselves not where we intended to go, but falling through infinite blackness. Dearie me.  

Something appears to have gone wrong with transportation device and, in the long-held tradition between STEM and humanities disciples, the historians hoof it over to us to sort.  

It appears to have unfolded into a 3-bit computer that can perform one of 8 instructions at a time, either on the number given to it as an argument or on the number stored in one of three registers based on both the argument and the operation type. Our first task is just to determine what the program is trying to output.
### Solution
There's not much to say about the approach to this part, as it's primarily a simulation that runs very quickly based on a number of if/elif statements. I've since learned about the match statement in Python (thank you again, Fluent Python) which might have made this look a little slicker, but fundamentally there's not much to it.
### Part 2
Ah, the issue is that this program is supposed to output a copy of itself (which is apparently known as a *Quine*), but the initial value we are providing to it has been corrupted. What is the lowest positive initial value for the first register (which drives the program) that causes the program to output a copy of itself?
### Solution
This broke me, it really did. Bar the second last day, this was for me the epitome of difficult, and in hindsight it was a dumb presumption from me that didn't hold out.  

I started, as you always should, by attempting a brute force. After leaving that for five minutes, I killed the program and thought again. Perhaps if I investigated more deeply what the actual steps were doing I would be able to puzzle out the approach; in the first part, I hadn't bothered, other than to encode what each operation did based on the rubric.  

What eventually (very eventually) became clear was that the program would output a digit based on the 3 least significant bits of the input, after which it would shift the input 3 bits to the right and continue. The maximum number you can store in 3 bits is, obviously, 7, so you could view this as outputting a digit based on the least signifcant unit of an octal number and then dividing by 8. The program has 16 digits, so I could just check all possible numbers between 8^15 and 8^16! Excellent, I've managed to reduce the search space.  

I gave this a try, even knowing that the vast majority of the search space was still in this range, and then I killed it after another 5 minutes; some back-of-the-napkin maths showed I was looking at approximately 781 years for this to run; although this was reduced from about 893 years for the unfiltered search, it's not quite good enough.  

I thought and thought and couldn't quite make the connection that would allow me to solve this. Eventually, I checked the Reddit solution thread for pointers, and realised that (obviously, in hindsight) the nature of the program was such that I could build each octet up one at a time in reverse order. Bingo!  

Except, even after doing so, it still didn't work. It output most of the program correctly, but not some of the initial numbers. In particular, it seemed to refuse to output 2. After an awful lot of likely unhelpful playing around, I eventually gave up for the day.  

Coming back the next morning, I figured out my issue. I had essentially written a greedy algorithm. I presumed that, for each octet, the lowest number was correct. However, due to the bit shifting involved, this seemed to later not be the case. What I needed was something akin to a breadth-first search (as always); for each program instruction, I only only needed to check n to n+8 over the previous value I'd built, but I needed to check *all* of those numbers that produced the correct digits, recursively. Bugger.  

I'll leave the description there as it's clearer in the code than I could hope to explain here; I'm quite disappointed about needing pointers on this one, as it seems so obvious in hindsight; but then again, your keys are always in the last place you look...

**Part 1:** *0.10 ms*  
**Part 2:** *65.86 ms*  

[Back to all days](/2024)