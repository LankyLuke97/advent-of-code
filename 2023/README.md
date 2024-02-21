# Advent of Code 2023

The below is a retrospective/post-mortem on my first full advent of code. I was delayed in beginning the challenge due to what eventually transpired to be an exploded motherboard that took three months to replace and necessitated the use of a backup laptop that took some time to get into working order.  
I decided to approach the challenges using C++. This was the first language I taught myself to program in, but I never felt fully confident in the syntax and nuances of the language; aside from that, it's also been over a decade since those days, and modern C++ has many additions with which I have no experience.  
I can't say with confidence that I'm now an expert in the language, but I feel much more comfortable with it after a month or so of everyday usage. With that out of the way, onto the challenges.  

## Day 1
### Part 1
We start the year off being somewhat unwittingly loaded into a trebuchet to investigate an issue with global snow production - I gather that, despite 2000-something years of Christmas, Santa's elves don't have the month of December down to a fine art.  
Aside from anything else, one of them has been playing silly buggers with the trbuchet calibration. Might need to get OSHA involved...  

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
two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven*2
zoneight234
7pqrstsixteen
```
We now had to find the first digit, either numeric or spelled out, and construct the two digit number for each.
#### Solution
This one didn't feel pretty, but again, for just a thousand input strings it worked fine.  
I first iterated through each string forward and backward, looking for the first numeric string in each case - I kept track of where this was located with a pointer for each.  
I then took the substring of the start of the line to the first numeric digit and the reversed substring from the last numeric digit to the end.
```
xtwone   3    four
```
In the first string, I searched for all the spelled out numbers - in the second, I searched for all the spelled out numbers written backwards. If in either case one was found, then the first (or last) digit was in fact, that number. If multiple were found, then the lowest start index was the first (or last).  
In hindsight, as I write this report, the double reversing for finding the last written number could have been avoided entirely by simply using the number with the highest start index rather than the lowest. Likewise, I could have skipped the substring section and simply checked if any instances were found before the numeric digits.

## Day 2
### Part 1
Having been successfully launched to a floating Snow Island, we're met by an elf apologising for the lack of snow and explaining that he can help pass the rather long walk with a simple game involving coloured cubes. Personally, I'd have preferred a strong drink and an air-condition limo after the traumatic experience of being launched into the air by a medieval instrument of war, but there were apparently budget constraints.  
The game to which we are treated involves numbers of red, green, and blue cubes being placed secretly into a bag; we are then shown multiple selections of the cubes (with replacement) per game.
```
Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
```
We must determine which of the games were possible if the bag had been loaded each time with 12 red, 13 green, and 14 blue cubes. Sum the possible game IDs for the answer.
#### Solution
Very simple problem this one. Just a bit of string manipulation to get the game ID, then looping through tokens in each line. If the token can be parsed to an int, then it's the current number. If it can't, then it must be a word indicating the colour associated with that number. After that, it's just a simple check that the number is less than or equal to what we would expect.
```
while(iss >> token) {
	try {
		i = std::stoi(token);
	} catch(std::invalid_argument const& ex) {
		if((token.substr(0, 3) == "red" && i > r) || (token.substr(0, 5) == "green" && i > g) || (token.substr(0, 4) == "blue" && i > b)) {
			add = false;
			break;
		}
	}
}

if (add) answer += id;
```
### Part 2
#### Solution
Another gentle part 2 that required almost no adjustments to my code. Instead of checking whether a game is valid based on the arbitrarily given 12 red, 13 green, and 14 blue cubes, we instead had to determine the minimum number of cubes required for each game to be possible.  
Keeping the same process of looping through the line, this time I tracked the largest number seen for each colour; this will be our minimum number for that colour cube for that game. For each line, multiply them together, sum all of them for the answer. Done in double quick time.
```
while (iss >> token) {
	try {
		i = std::stoi(token);
	} catch (std::invalid_argument const& ex) {
		if(token.substr(0, 3) == "red" && i > r) {
			r = i;
		} else if(token.substr(0, 5) == "green" && i > g) {
			g = i;
		} else if(token.substr(0, 4) == "blue" && i > b) {
			b = i;
		}
	}
}

answer += (r * g * b);
```

## Day 3
### Part 1
Having been enjoyably diverted by the cube game, we've found ourselves at a gondola lift station housing (shock) broken gondolas and we are once again roped into fixing it. These elves, do any of them have the expertise their jobs require?  
Given an '*engine schematic*', we have to sum up the part numbers in the schematic. A number is a part number if it adjacent (including diagonally adjacent) to any non-number, non-period character. In the below example, ```114``` and ```58``` are not part numbers - the rest are.
```
467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
```
#### Solution
Even this early on, I started to feel that I was writing less-than concise code. Nevertheless, the approach I took was as followed.  
The first step was to iterate over all lines, searching for any special characters or numbers, both using regex searching. I've not done anything with regex in C++, and like many software engineers the concept as a whole tends to feel unassailable. I'm not yet confident in C++ with the concepts - I would like to perhaps revisit it.  
I tracked the positions of all special characters - simple enough. For the potential part numbers, I create a dictionary called ```numberPositions```, the keys of which are each position lying within a part number, the value being the start position. So if the first row of the input were ```..897...```, then I would emplace ```{2: 2, 3: 2, 4: 2}```. I simultaneously created a separate dictionary called ```numberMappings```, the keys of which were the start positions of those numbers and the values being the part number it self. In the prior example, this would be ```{2: 897}```.  
Having mapped the information, I then interated through all of the special characters, for each one checking all the surrounding positions for matches in the ```numberPositions``` dictionary. If there were any matches, I found the matching part number in the ```numberMappings`` dictionary and added it to the result. I then removed each result from its respective dictionary to prevent duplicate part additions.  
Happy with my solution, I hit run and - it failed my test case. What on earth...  

Much debugging later, I had to call it a night. I just couldn't figure out the solution.  
Undeterred despite falling at such an early hurdle, I returned the next day for further debugging; my patience was eventually rewarded. I changed how I was doing the regex searches, as they weren't returning all the values (I think just the first one?). I realised I had also made a mistake in the way I was searching around each part. The mistake was such that it didn't flag up in my test, which caused an incorrect submission, but eventually I noticed the '-' that should have been a '+' and sent the bugger on his way. Part 1, complete.
### Part 2
Snatching defeat from the jaws of victory! It seems something is still wrong. Turns out, one of the gears is wrong. A gear is any ```*``` symbol adjacent to exactly two part numbers. The gear ratio is the multiplication of each of those part numbers. We need to sum all the gear ratios.  
In the given example, there are two gears: in the top left, adjacent to ```467``` and ```35``` - this has a gear ratio of ```16345```; and in the lower right, adjacent to ```755``` and ```598```, with a gear ratio of ```467835```.
#### Solution
Thanks to the way I had written my part 1, this took no time at all. I exactly replicated the code to start with; then, I changed the special character search to only look for ```*```, as only this character could be a gear.  
Then, when searching for adjacent part numbers, this happens on a per potential-gear basis. I tracked all the adjacent parts in a vector; if the length of that vector was two, I added the multiplication of the two elements to the answer. 