# Advent of Code 2024
## Day 2
### Part 1
Somewhere along here I realised that this is the 10th anniversary of AoC and that all the locations are references to previous problems, hence the 'historian' bit - cool stuff. Our first location is the Red-Nosed Reindeer nuclear fusion/fission plant - sure...  

We're needed to analyse some unusual data from the facility. We're given a list of reports containing a number of levels (integers). We need to declare each report either safe or unsafe. A safe report is strictly increasing or strictly decreasing by at most 3 between each level.
### Solution
Looking back, I already think this could be written more neatly, but never mind. Through a series of list comprehensions, we apply the following to each line. 
* Strip the line.
* Split the line on whitespace.
* Convert all to integers.
* Zip the result with its shifted self to create a pairwise iteration (have recently learned about itertools.pairwise, which would have been useful here and a number of other times throughout AoC).
* If all the pairwise differences have an absolute value between 1 and 3 inclusive and all have the same sign, then add one to the number of safe reports.

It's this last step that's ugly in the code, but it does the job.
### Part 2
Alas, incomplete requirements! The engineers forgot to mention the Problem Dampener; essentially, this allows for one bad level in a report. If removing a single level would make the report safe, then we can count it as such.
### Solution
There may well have been a more intelligent solution to this than mine (there so often is), but I just bruteforced this. I followed all the same steps for part 1 for each repor; if it was safe, then grand, on we go. If not, I iterate through each level in the report, checking whether the report is safe if it is removed.  

**Part 1:** *3.16 ms*  
**Part 2:** *7.14 ms*  

[Back to all reports](/2024)