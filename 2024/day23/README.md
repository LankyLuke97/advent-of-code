# Advent of Code 2024
## Day 23
### Part 1
We're back in a secure area at Easter Bunny HQ, though can any of these areas really be considered secure if we repeatedly blunder our way in without difficulty?  

We find a poster for a LAN party, so we download a map of the local network, which lists every connection between two computers.  

LAN parties typically involve multiplayer games, so we can probably locate it by finding groups of computers that are all connected to each other. We'll start by looking for sets of three computers that are all connected to each other. We're also still looking for CH, and we're pretty sure that his PC name starts with the letter 't', so we can ignore any sets that don't contain at least one PC that starts with 't'. How many such sets of three are there?
### Solution
Right, I didn't like this problem, I'm going to put that out there now; at least part 1. That's more on me than the design of the problem; I think it's one of the problems I most just fumbled about with and through different options at, as opposed to really understanding what was going on and finding a good solution.  

I start by constructing a dictionary, where the key is PCs and the value is a set of all the other PCs that this PC is connected to (including itself).  

Once that's done, I iterate through the key/group pairs in the dictionary. If the key doesn't start with *t*, then we can skip this one. If it does, I then iterate over all the PCs in the group (call this group Set A). For each one I fetch the PCs that it is connected to from the dictionary (call this Set B). I can then take the intersection of this Set A and Set B, which represents all the PCs that are part of fully connected triangles involving the PC that starts with 't'. Can you see why I don't like my solution? What does that sentence even mean? Is it working because there's an underlying concept to graphs that I've managed to capture, or is it luck? Or both?  

Regardless, with this intersection, I then add all size 3 combinations of the set to another set to ensure uniqueness, and then count how many of those there are at the end.  

Let's move swiftly onwards.
### Part 2
There are way too many results to go through them all. We can't see any employees, so presume that they must all be at the LAN party; if that's the case, then the LAN party will be the largest set of computers that are all connected to each other. The LAN party posters say that the password to get into the LAN party is the name of every computer at the party, sorted alphabetically, and then joined with commas.

What's the password?
### Solution
Ok, so we're looking for a way to find the largest fully connected subgraph within another graph...  

I started by trying to adapt my part 1 solution but quickly gave that up as a bad job. I have never really studied any graph algorithms, so I turned to Google here, as I presumed this would be a solved problem; it is indeed.  

Like so many others, I found the Bron-Kerbosch algorithm, and implemented the naive version of it, which worked first time. I was willing to look into the improvements based on using a pivot, but since it ran in about a quarter of a second, I called it good and left it there.  

Next year, I will have studied graphs and have some of these basic algorithms as tools that I am at least aware of, if not able to implement without reference to pseudocode.

**Part 1:** *10.26 ms*  
**Part 2:** *278.07 ms*  

[Back to all days](/2024)