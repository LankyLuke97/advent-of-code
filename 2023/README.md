# Advent of Code 2023

The below is a retrospective/post-mortem on my first full advent of code. I was delayed in beginning the challenge due to what eventually transpired to be an exploded motherboard that took three months to replace and necessitated the use of a backup laptop that took some time to get into working order.  
I decided to approach the challenges using C++. This was the first language I taught myself to program in, but I never felt fully confident in the syntax and nuances of the language; aside from that, it's also been over a decade since those days, and modern C++ has many additions with which I have no experience.  
I can't say with confidence that I'm now an expert in the language, but I feel much more comfortable with it after a month or so of everyday usage. With that out of the way, onto the challenges.  

## Day 1
### Part 1
The challenges started off simple, as always. Given a list of strings:
```
1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
```
We had to find the first and last number in each line, using the former as the first digit and the latter as the second digit of a two digit number. The sum of all these answers is the puzzle solution.  
#### Solution
Easy one to approach. There were a thousand strings in the puzzle input, none of which are more than a few tens of characters long. I simply iterated through each line, once forwards and once backwards, keeping track of the first number found in each instance.  
Once they were found, the two digit number could be constructed and added to the running sum.
### Part 3
We're told now that some of the digits are actually spelled out with letters; **one**, **two**, **three**, and so on, as below.
```
*two*1*nine*
*eight*wo*three*
abc*one*2*three*xyz
x*two*ne3*four*
*4*nineeightseven*2*
z*one*ight23*4*
*7*pqrst*six*teen
```
We now had to find the first digit, either numeric or spelled out, and construct the two digit number for each.
#### Solution
This one didn't feel pretty, but again, for just a thousand input strings it worked fine.  
I first iterated through each string forward and backward, looking for the first numeric string in each case - I kept track of where this was located with a pointer for each.  
I then took the substring of the start of the line to the first numeric digit and the reversed substring from the last numeric digit to the end.
```
*zoneight*__2__3harold5__4__*dfsixteen*
```
In the first string, I searched for all the spelled out numbers - in the second, I searched for all the spelled out numbers written backwards. If in either case one was found, then the first (or last) digit was in fact, that number. If multiple were found, then the lowest start index was the first (or last).  
```
*z__one__ight*__2__3harold5__4__*df__six__teen*
```
In hindsight, as I write this report, the double reversing for finding the last written number could have been avoided entirely by simply using the number with the highest start index rather than the lowest. Likewise, I could have skipped the substring section and simply checked if any instances were found before the numeric digits.
