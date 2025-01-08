# Advent of Code 2024
## Day 24
### Part 1
Moving swiftly along, we find ourselves at the edge of the star fruit grove, where a monitoring device has been installed after the last incident; of course, the monitoring device is now malfunctioning.  

Upon investigation, it seems to be trying to produce a number through some boolean logic gates, operating on values that are either true or false (1 or 0). Gates wait until both inputs are received before producing output; this means that 0 is not 'no value', which is its own, separate state on the wire. There are no loops, so a gate will not change output once it's been determined.  

There are a number of inputs whose name starts with x, with y, and outputs that start with z, all of which end with 2 digits. The x and y inputs are the beginning inputs to the system, the two binary numbers; the 2 digits are the order those bits appear in the binary numbers, with x00 and y00 as the respective least significant bits. The same convention is true for the z outputs, which is intended to be the final outcome from the system. What **decimal** number does the system output?
### Solution
Right, this first part is a fairly simple simulation. I just need to parse the input to get our start X and Y numbers, parse all the operations, and then perform the operations.  

I track a ```known``` dictionary of gates to their values, which initially contain only the X and Y gates. I then iterate through the operations in the order presented in the input. If either of the operands is not yet in the dictinary, I just append the whole operation to the back of the processing queue again. If they're both known, I update the ```known``` dictionary for the output value, and continue processing. If the output is a z gate, I separately track that to later process and convert into a decimal number.
### Part 2
The device apears to be trying to add the X and Y numbers and output the result to Z. However, the output is incorrect, as some wires appear to have been switched. Based on our forensic analysis of scuff marks, we can tell that there are exaclty four pairs of gates whose output wires have been swapped, and that no gate's output was swapped multiple times (strange that we can tell this much, but not which wires have been swapped).  

We need to figure out which eight output wires have been swapped and output their names alphabetically and joined with commas.
### Solution
Man, this one stumped me for a long while. I started by plotting out the gates and their connections on paper; after about 3 sets of repeating patterns, the thought occurred to me that I had likely already been given enough to know what this data structure was. The rubric stated that it takes two binary numbers and adds them - so it's most likely a ripple adder (tens of thousands of pounds I paid for that university education, got to put it to use somehow). Of course, I couldn't remember what went into a ripple adder, so I looked up the logic gate structure: lo and behold, it looks an awful lot like my crappy drawing I've been doing (at least topologically).  

Where to go from here then? I could continue on with the pattern, drawing out the gates and connections, and I would eventually spot the 8 crossed wires. There's no rule against this, but it was Christmas Eve and I suspect my partner would have buried my lifeless body in a ditch if that's how I chose to spend my day.  

I couldn't puzzle it out, though I spent a lot of time prodding at the edges of what was eventually to be the correct solution. Eventually I gave it up for a bad job as I had to travel down to family.  

I picked it up on Christmas after completing day 25, and finally managed to coerce my neurons into firing. It came down to a series of rules about the structure of the adder, which is what I'd been thinking the day before; I must have been tired, because I couldn't figure out how to encode what seemed intuitive.  

* If the output gate starts with 'z' and the operation is not XOR and it's not the final (most significant) output, then the it's wrong.
* If the operation is XOR and none of the gates start with 'x', 'y', or 'z', then the output gate is wrong.
* If the operation is AND and this isn't the start of the adder (i.e. it's not the half adder for the least significant bits, which has a different structure to the rest), then we need to check all the instructions for the one where this output gate is in the operands. If the operation for *that* instruction is not OR, then this output gate is wrong.
* If the operation is XOR, then we need to check all the instructions for the one where this output gates is in the operands. If the operation for *that* instruction is OR, then this output gate is wrong.  

Well, that's a mouthful, but neat in the end. I could have sped this up by creating some sort of dictionary for the output gate to where it's used as an input, since this would then be an O(1) lookup rather than repeated for loops, but it runs fast enough and is clearer to read this way.

And so endeth my Advent of Code 2024 (having already completed Day 25 by this point). 

**Part 1:** *0.76 ms*  
**Part 2:** *2.59 ms*  

[Back to all days](/2024)