# Advent of Code 2024
## Day 5
### Part 1
Ask anyone who works with technology, and they'll tell you it's a good idea to keep a baseball bat ready in case the printer starts showing signs of intelligence - it's also handy for when the printer starts playing up, as so frequently does the printer in sub-basement 17.  

We are given a list of page ordering rules and pages to produce for a number of updates to the sleigh launch safety manual. The rules are structured in the form ```X|Y```, meaning tht if both X and Y are to be produced as part of an update, X must be printed before Y. The updates are just a string of comma separated page numbers - standard stuff.  

We need to sum the middle page number from each correct update.
### Solution
I seem to remember fumbling around with this one for a while longer than I should have; the information is not that complicated, nor is the size of the input that large. I think I read the rubric too quickly and missed some of the details, such as not worrying about a rule if one of the page numbers doesn't appear.  

What I eventually settled on was, first, constructing a dictionary of pages to a list of pages that need to be seen prior to that page if they are both to be produced as part of an update; that is to say, the keys were the Y's from the rules and the values were lists of all the X's associated with that Y.  

Next, I iterated through each of the 'updates'. For each one, I checked each page in turn. If there were no rules associated with it, great. If there, then all pages within those rules that *hadn't already been seen* were added to a 'must not see' list (because they must have already been seen if they're both in this update). If any future page is in that list, then we know a rule has been broken. The page is then added to a corresponding 'seen' list.  

Once all pages had been successfully iterated through without breaking the ordering, I could add the middle number of the list to the answer.
### Part 2
I think I predicted something like this; I must be doing too many of these problems. I've got some time to kill while the elves print and the historians search, so my avatar decides to fix the incorrectly ordered updates according to the rules. Then we sum the middle numbers from only those lists - what's the solution now?
### Solution
I'm quite pleased with this one, looking back at the solution. It starts the same way, constructing the rules and then iterating through the updates. This time, however, we're looking for updates with issues.  

Once we find one, I need to sort it. Ideally, I wanted to use the built-in Timsort, for the sake of not reinventing the wheel, and I had a feeling that I could, if I could provide the correct key.  

This lead to me learning about what the ```key``` parameter for ```sorted()``` really does in Python, and how to create a more complicated comparison function and convert it into a single argument key.  

The comparison function takes two pages, *l* and *r*, and a set of rules (the rules constructed from the ```X|Y``` inputs). If *l* is in the values for *r*, then it must come before *r*, so the comparison function returns -1. Otherwise, if *r* is in the values for *l*, it must come before *l*, so the function returns 1. If neither is true, then we don't care and the order can remain as is, so it returns 0. This is where the fact that Timsort is stable is useful (though I appreiciate, looking at [this Wikipedia page](https://en.wikipedia.org/wiki/Category:Stable_sorts), that there are in fact many stable sorting algorithms): when two pages were unrelated, their relative ordering would be unchanged.  

The rest of the solution was identical to part one, just taking the middle value of the sorted list and adding it to the cumulative sum.  

**Part 1:** *12.28 ms*  
**Part 2:** *14.71 ms*  

[Back to all days](/2024)