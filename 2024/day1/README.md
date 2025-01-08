# Advent of Code 2024
## Day 1
### Part 1
As is traditional for the dysfunctional organisation that is North Pole Presents plc., something has gone catostophoically wrong right before Christmas; the Chief Historian has gone missing, and is required for the sleigh launch. The rubric says he's been missing for months, and yet no-one has attempted to find him prior to this, despite knowing for a fact that he would be needed? Truly, art imitates life.  

To find him, we're just going to check fifty different places, and we know for a fact that he'll be in one of them. Sure. Feels like, unless he's a quantum particle superpositioned over all of but only those fifty places, they might actually already know where he is, but let's crack on with the time-and-space hopping.  

To begin with, we need to reconcile two lists of historical locations (integers); the reconciliation process entails finding the distance (absolute difference) between the smallest number in the first list and the smallest in the second list, then the second smallest, and so on, summing all the distances.  

### Solution
An easy one to get going, as usual. I create two lists of integers by splitting each line in the input, sort each one, then return the sums of the differences between all the pairs in the lists.  
### Part 2
Next up is apparently that the Chief Historian (CH going forward, as I don't want to write that phrase out 50 times) has appalling handwriting and we can't read most of the digits (at what point does it cross from bad handwriting to straight-up just not knowing how to write a number?); instead, we now need to calculate a similarity score.  

For each number in the left list, we calculate the number of times it appears in the right list, and then multiply that by the number. We do this for every number in the left list, summing them all.  
### Solution
Already, I get to use something from Fluent Python (self-study for the win); instead of a list for the right-side, I create a Counter, which just provides a mapping of integers as keys to the number of occurences of that instance, returning 0 if you query a key that it doesn't contain - ideal! I then iterate through the left-hand list, summing the product of each int with its occurrences in the Counter.  

Thinking about it now, the left-hand list could also probably be a counter and it might look neater, but I suspect this would involve an extra number of iterations through the list. No CH to be found, on we go.  

**Part 1:** *0.84 ms*  
**Part 2:** *0.93 ms*

[Back to all reports](/2024)