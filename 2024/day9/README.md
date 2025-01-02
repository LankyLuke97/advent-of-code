# Advent of Code 2024
## Day 9
### Part 1
Our next stop is, I gather, underwater with some amphipods. The historians' time-and-space travel device seems to have also conjured us personal submarines; what incredible plot armour. In any case, whilst the historians bump into walls and generally cause issues for everyone, we set to work helping an amphipod improve their computer's file storage. Is it just me, or are we not particularly interested in finding CH?  

The file system is represented by a string of digits. Each digit represents, in alternating order, the size of a file, and then the amount of space before the next file. In addition, each file has an ID that starts at 0 and increases for each file seen. So, a file system represented by ```12345``` would look like ```0..111....22222```, and ```90909``` would be ```000000000111111111222222222```, with ```.``` for empty spaces. So far so clear.  

The amphipod wants to compress the files by moving all file blocks as left as possible, starting with the rightmost file. With the example of ```12345``` as given earlier, this would leave a file system looking like this:
```
022111222......
```
The final step is to calculate a checksum. The checksum is the sum of all the file IDs at their final block position; for the above, we would have ```0 * 0 + 2 * 1 + 2 * 2 + 1 * 3 + ...```
### Solution
I'm quite pleased with the approach I took to this problem; in previous years I think I would likely have got a bit bogged down with the representation of the problem, whereas this time I thought more clearly about the underlying data. I started with some pointers to the start and end of the input - the first and last files - as well as the current block of memory I was looking at. For the first file in the input (or the current 'front'), I just added the correct values to the checksum, based on the front file ID and the ever incrementing current block.  

Once the front file was complete, I then checked how many empty spaces there were. For the current back file, I then did something similar, adding to the checksum while there was empty space and there were enough chunks of the back file to fill that empty space. If the file ran out before the empty space, I moved onto the next back file, reducing the back file ID as I did so. Once the empty space had been filled, I moved onto the next front file, repeating the process until all empty spaces to the left of back files had been filled. At this point, it was just a case of adding remaining file blocks to the checksum.
### Part 2
Unfortunately, the massive disk fragmentation this process leads to has caused a considerable slowdown in the computer - who could have guessed it? We'll need to take a different tack.  

The amphipod apparently already has this different tack - now, we're only going to move files if there is a block of empty space large enough for the whole file to fit into. We'll still be starting with the rightmost file, and will still touch each file only once; if there is no suitable gap when we first look, but there is later, it doesn't matter - it had its chance!
### Solution
I couldn't think of anything that did this in better than O(n^2). I started by altering the input to be a list of pairs, where the pairs are the size of the file block and its corresponding ID, or the size of the empty space and an 'ID' of -1 to make it clear. This seemed necessary to me as it seemed harder to create the checksum as I went this time, since we could check the same block of empty space multiple times; I thought it easier to actually create the representation of the memory as I went, though there may well be a cleaner solution that hasn't come to my mind.  

With this alteration of the input complete, I start iterating from the back of the files; for each one, I search for the first empty space large enough to hold it (thank the gods for the greedy algorithm). When I found one, I would reduce the empty space by the size of the file I was about to insert, remove the file at the index I was on, insert an empty space of the correct size there, insert the file before the first empty space, and then insert another empty space of size zero prior to that.  

Once I had moved all the files possible, I simply iterated through the new data, summing a checksum as described initially.

**Part 1:** *20.47 ms*  
**Part 2:** *4,757.51 ms*  

[Back to all days](/2024)