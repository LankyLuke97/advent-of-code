# Advent of Code 2024
## Day 25
### Part 1
We've not managed to find CH, so we decide to head back to his office, just in case. It does indeed sound like someone is inside, but knocking gets no response; we contact North Pole security to see if they can unlock the door. Unfortunately, they've lost track of which locks are installed and which keys go with them (painfully accurate) and so the best they can do is send over schematics for the keys and locks. These are in a cryptic file format, but also come with manufacturer information, so we call the support number.  

We're told that we can't know if a certain key will open a lock until we try it, but we can know if a certain key *definitely can't* open a given lock. The schematics look like this:
```
#####
.####
.####
.####
.#.#.
.#...
.....

#####
##.##
.#.##
...##
...#.
...#.
.....

.....
#....
#....
#...#
#.#.#
#.###
#####

.....
.....
#.#..
###..
###.#
###.#
#####

.....
.....
.....
#....
#.#..
#.#.#
#####
```
As always, hashes represent filled space and full-stops represent empty space. Schematics with the top row filled represent locks, while those with bottom row filled represent keys. A key *definitely* won't fit a lock if any of the pins of the lock overlap with the shape of the key.  

How many unique lock/key pairs fit together without overlapping in any column?
### Solution
Thank the gods, an easy one to round out the year.  

I parse each schematic into a list of numbers representing the column 'heights' - the number of hashes in that column - and store it in one of two lists, depending on whether it's a key or lock. Then, it's a simple matter of comparing each key with each lock; if any of the columns, when summed across the two schematics, is greater than 7, then there's an overlap. If they're all 7 or less, this is a pair that fits, so we increment the counter.  
### Part 2
As always, there's no part 2 problem, just a quite sweet rubric about all of this work being, in fact, to complete a gift that's meant for us, a record of all the places we've been and people we've helped over the last decade (or 3 years in my case). A feel good end to the year (once I finished day 24). As always, a massive thanks to Eric Wastl for the effort that goes into this.
### Solution
Merry Christmas!

**Part 1:** *53.80 ms*
**Part 2:** *N/A*  

[Back to all days](/2024)