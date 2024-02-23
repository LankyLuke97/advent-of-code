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
Having mapped the information, I then interated through all of the special characters, for each one checking all the surrounding positions for matches in the ```numberPositions``` dictionary. If there were any matches, I found the matching part number in the ```numberMappings``` dictionary and added it to the result. I then removed each result from its respective dictionary to prevent duplicate part additions.  
Happy with my solution, I hit run and - it failed my test case. What on earth...  

Much debugging later, I had to call it a night. I just couldn't figure out the solution.  
Undeterred despite falling at such an early hurdle, I returned the next day for further debugging; my patience was eventually rewarded. I changed how I was doing the regex searches, as they weren't returning all the values (I think just the first one?). I realised I had also made a mistake in the way I was searching around each part. The mistake was such that it didn't flag up in my test, which caused an incorrect submission, but eventually I noticed the '-' that should have been a '+' and sent the bugger on his way. Part 1, complete.
### Part 2
Snatching defeat from the jaws of victory! It seems something is still wrong. Turns out, one of the gears needs to be replaced. A gear is any ```*``` symbol adjacent to exactly two part numbers. The gear ratio is the multiplication of each of those part numbers. We need to sum all the gear ratios.  
In the given example, there are two gears: in the top left, adjacent to ```467``` and ```35``` - this has a gear ratio of ```16345```; and in the lower right, adjacent to ```755``` and ```598```, with a gear ratio of ```467835```.
#### Solution
Thanks to the way I had written my part 1, this took no time at all. I exactly replicated the code to start with; then, I changed the special character search to only look for ```*```, as only this character could be a gear.  
Then, when searching for adjacent part numbers, this happens on a per potential-gear basis. I tracked all the adjacent parts in a vector; if the length of that vector was two, I added the multiplication of the two eleents to the answer. 

## Day 4
### Part 1
Having discovered a new talent as a gondola engineer, we wave goodbye to Snow Island and take to the sky, arriving on a new, decidedly warmer and more humid island. An elf playing with coloured cards informs us this is Island Island (?) and that the gardener might know where the water source is - of course, he's on a different island. The small kind, surrounded by water, not the giant physics-defying floating kind. The elf promises to lend us his boat if we help him with his cards.  
Each card has two lists of numbers. One is a list of winning numbers and the other is a list of the numbers we have.
```
Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
```
You get one point for each card for the first winning number; it is then doubled for each successive winning number. The points are therefore 8 2, 2, 1, 0, 0 for cards 1 to 6 respectively. What'st the sum of all the winning cards?
#### Solution
I was clearly taking advantage of some time off work and some easy challenges here, as my commit history shows day 3, day 4, and an attempt at day 5 all committed on the same day.  
I iterated through each line, ignoring the card number. I stored each token as a number in a vector of winning numbers, until the looped failed to parse a token as a number - this was the pipe.  
```
while(true) {
	iss >> token;
	try {
		winningNumbers.push_back(std::stoi(token));
	} catch (std::invalid_argument const& ex) {
		break;
	}
}
```
I am aware that using a ```try {...} catch {...}``` statement for control flow is something of a [faux pas](https://blog.awesomesoftwareengineer.com/p/throwing-exceptions-vs-control-flow), but the thing is, this is AoC, not production ready code; pipe down. (See what I did there? It's a pipe symbol that causes the exception. Humour me.)  
I then continued parsing the rest of the line, which contained the numbers we had. For each one, if it was found in the winning numbers, I incremented a counter. At the end of each line, I added 2 to the power of (winning - 1) to the answer. Something nice to note here is that if there are no winning numbers, this is 2 to the power of -1, which is 0.5, which gets rounded down to 0 during the integer maths as required. Complete accident at first.  
```
while(iss >> token) {
	winning += (std::find(winningNumbers.begin(), winningNumbers.end(), std::stoi(token)) != winningNumbers.end());
}
answer += std::pow(2, winning - 1);
```
### Part 2
Turns out, the elf hadn't actually read the rules of the game and instead had just gone for it with his presumptions of how it worked. I think I see why there's so many problems around Christmas every year.  
There's no such thing as points. For each winning number on a card, you win copies of that number of the following cards. From the page:  
> - Card 1 has four matching numbers, so you win one copy each of the next four cards: cards 2, 3, 4, and 5.
> - Your original card 2 has two matching numbers, so you win one copy each of cards 3 and 4.
> - Your copy of card 2 also wins one copy each of cards 3 and 4.
> - Your four instances of card 3 (one original and three copies) have two matching numbers, so you win four copies each of cards 4 and 5.
> - Your eight instances of card 4 (one original and seven copies) have one matching number, so you win eight copies of card 5.
> - Your fourteen instances of card 5 (one original and thirteen copies) have no matching numbers and win no more cards.
> - Your one instance of card 6 (one original) has no matching numbers and wins no more cards.
We need to sum how many original and copied cards we have at the end. Thanks to a neatly constructed set of inputs, we'll never generate a copy of a card that isn't in the input.  
#### Solution
I started the same way; for each line, iterate through the tokens to get the winning numbers until I hit the pipe symbol. Here's where it differs: instead of adding the 'power' of the card, I tracked the number of copies of each card in a dictionary, starting with 1 for every card (the original). When we generate a copy of a card, we add to the dictionary the number of copies of the current card we have.

```
std::vector<int> cardMembers(input.size() - 1, 1);
...
int copyCard = lineNum + 1;
int copyMultiplier = cardMembers[lineNum];
while (iss >> token) {
	if(std::find(winningNumbers.begin(), winningNumbers.end(), std::stoi(token)) == winningNumbers.end()) continue;
	cardMembers[copyCard++] += copyMultiplier;
}
lineNum++;
```
At the end, I returned the sum of the values of the dictionary. A job well done.

## Day 5
### Part 1
The gardener is horrified when he realises how long it's been since they turned off the water supply - he was distracted with feeding everyone (a laudable goal, I'm sure). It turns out the issue is that they have no sand to filter the water, and they can't make snow with dirty water, apparently.  
In the same breath as sending us off to check on the sand, he also asks for help with the food production. They're having trouble with understanding the latest Island Island Almanac, which lists:
- All of the seeds that need to be plant
- The type of soil to use with each seed
- The type of fertiliser to use with each soil
- The type of water (?) to use with each fertiliser
- Ad nauseam
Our example input looks like so:
```
seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4
```
Rather than listing every source and corresponding destination one by one, the lines are ranges. Taking the ```seed-to-soil map``` as an example:
```
50 98 2
52 50 48
```
The first line describes a destination range starting at 50, a source range starting at 98, and a range length of 2. So:
```
98 -> 50
99 -> 51
```
The second line means that the source range starts at ```50``` and contains ```48``` numbers, corresponding to a destination range starting at ```52```, which will also contain ```48``` consecutive numbers.  
Any source numbers that aren't mapped correspond to the same destination number. The ```seed-to-soil map``` therefore looks like this:
```
seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51
```
We can repeat this process for all the maps. The gardener wants to know the lowest location number corresponding to any of the seeds.
#### Solution
My first attempt used a naive implementation of creating a dictionary for every map given in the input. Finding the location of a seed was then a straightforward task of iteratively feeding the seed input through the chain of maps in the correct order.  
This worked perfectly for the exmaple input. However, the actual input had much larger numbers for the ranges, and so my laptop ran out of memory in which to store the behemoth dictionaries. Sometimes, you can't just brute force the problem.  
Coming back the next day, I got to work. I switched out my map of every single number for the more intelligent approach of storing the ranges given to us as a vector of vectors of vectors. The top level of vectors contained seven vectors, one for each map type. Each of those vectors contained all the maps given for that type.  
For each seed, I then went through this loop:
```
int64_t location = seed;
for(int i = 0; i < mappings.size(); i++) {
	for(int j = 0; j < mappings[i].size(); j++) {
		int64_t start = mappings[i][j][0], mapping = mappings[i][j][1], range = mappings[i][j][2];
		if(location < start) continue;
		if(location >= start + range) continue;
		location = (location - start) + mapping;
		break;
	}
}
if(location < closestLocation) closestLocation = location;
```
For each mapping, I check if the current ```location``` (which is only the location once it has filtered through the pipeline) is within the range described by the mapping. If it is, I alter it's value to the corresponding mapping and pipe it through the next type of mapping. If not, we keep checking current mappings. If it doesn't match any, it's passed to the next mapping type unchanged, as it should be.
### Part 2
Turns out, they didn't RTFM properly (again). Instead of individual seeds, the almanac describes ranges of seeds. The seed numbers come in pairs, the first number referring to the start of a range and the second number describing the length of the range.
So, in the example, ```seeds: 79 14 55 13``` actually means two ranges, the first starting at ```79``` and containing ```14``` values (```79``` to ```92``` inclusive), the second starting at ```55``` and containing ```13``` values (```55``` to ```67``` inclusive).  
The problem remains the same - of those seeds, which corresponds with the lowest location number?
#### Solution
I decided that my previous implementation was perfectly reasonable. All I did was add an additional loop to deal with the range of seed numbers:
```
for (int64_t i = 0; i < inp; i++) {
	int64_t location = start + i;
	for (int i = 0; i < mappings.size(); i++) {
		for (int j = 0; j < mappings[i].size(); j++) {
			...
		}
	}
	if (location < closestLocation) closestLocation = location;
}
My commit message says **...naive solution, pretty slow, but better than the version that consumed all my RAM in a dumpster fire of inefficiency**. Interesting.
