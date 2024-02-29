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

**Part 1:** *1 ms*
**Part 2:** *2 ms*

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

**Part 1:** *708 ms*
**Part 2:** *2626 ms*

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

**Part 1:** *20 ms*
**Part 2:** *18 ms*

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

**Part 1:** *228 ms*
**Part 2:** *197 ms*

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
For each mapping, I check if the current ```location``` (which is only the location once it has filtered through the pipeline) is within the range described by the mapping. If it is, I alter its value to the corresponding mapping and pipe it through the next type of mapping. If not, we keep checking current mappings. If it doesn't match any, it's passed to the next mapping type unchanged, as it should be.
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
```
My commit message says **...naive solution, pretty slow, but better than the version that consumed all my RAM in a dumpster fire of inefficiency**. Interesting.

**Part 1:** *7 ms*
**Part 2:** *132004 ms*

## Day 6
### Part 1
Our strange progression through the islands continues. Having reached the erstwhile sand pile, we see a boat racing competition; the grand prize of which is a trip to Desert Island - presumably we can find some sand there?  
In order to guarantee ourselves the prize, we feel we need to beat the current record in every race. For our example input, we're given this:
```
Time:      7  15   30
Distance:  9  40  200
```
This describes the time and corresponding record distance for three different races. Our toy boat has a starting speed of zero millimiterers per millisecond. We can hold a button at the start of the race, using some of the race time, to increase its speed. Each second we spend holding the button, its speed upon release increases by one millimiter per millisecond. For the first race we have these options:
```
- Don't hold the button at all (that is, hold it for 0 milliseconds) at the start of the race. The boat won't move; it will have traveled 0 millimeters by the end of the race.
- Hold the button for 1 millisecond at the start of the race. Then, the boat will travel at a speed of 1 millimeter per millisecond for 6 milliseconds, reaching a total distance traveled of 6 millimeters.
- Hold the button for 2 milliseconds, giving the boat a speed of 2 millimeters per millisecond. It will then get 5 milliseconds to move, reaching a total distance of 10 millimeters.
- Hold the button for 3 milliseconds. After its remaining 4 milliseconds of travel time, the boat will have gone 12 millimeters.
- Hold the button for 4 milliseconds. After its remaining 3 milliseconds of travel time, the boat will have gone 12 millimeters.
- Hold the button for 5 milliseconds, causing the boat to travel a total of 10 millimeters.
- Hold the button for 6 milliseconds, causing the boat to travel a total of 6 millimeters.
- Hold the button for 7 milliseconds. That's the entire duration of the race. You never let go of the button. The boat can't move until you let go of the button. Please make sure you let go of the button so the boat gets to move. 0 millimeters.
```
We need to calculate the number of different ways to beat each race and return the product of all the different races.
#### Solution
This puzzle seemed to me to indicate the quadratic function. I'm not exactly sure why, as I'm not generally a very visual thinker, but a picture came to mind of a parabolic curve for the various distances the toy boat would travel after certain lengths of charging time. It seemed to me that, if I plugged the correct values into the quadratic equation, I would be able to find the two "solutions", which would be the minimum and maximum time the button could be held for.
Once I had those, the number of different ways to win a race would just be the range between the two.  
This approach was broadly correct but I was finding that the results for each race were sometimes correct, sometimes off by one.  
I eventually realised that sometimes the maximum time was actually one too high - I think perhaps due to integer rounding, it was giving a 'button holding time' that was one millisecond too long. I added in a check to validate that the upper value did in fact beat the race record - if not, I reduced the range for that race by 1.
```
for(int i = 0; i < times.size(); i++) {
	int solution1 = (times[i] + std::sqrt(std::pow(times[i], 2) - (4 * distances[i]))) / 2;
	int solution2 = (times[i] - std::sqrt(std::pow(times[i], 2) - (4 * distances[i]))) / 2;
	int range = solution1 - solution2;

	if((times[i] - solution1) * solution1 <= distances[i]) range--;

	answer *= range;
}
```
### Part 2
Turns out that there's actually only one race -  the spaces on the paper we were given were just due to extremely bad kerning. I had a hearty laugh at finding out that this is known as *keming* (for some reason, my partner found it only mildly amusing). Our example input went from this:
```
Time:      7  15   30
Distance:  9  40  200
```
to this:
```
Time:      71530
Distance:  940200
```
We now just need to know how many ways there are to beat this single race.
#### Solution
Thanks to the mathematical approach to the first part, I was able to reuse the code almost exactly. The only issue I encountered was that the numbers were large enough for me to encounter integer overflow - as soon as I switched to int64_t (though it could have been a 32 bit integer it turns out), I had the correct answer.  
One noteworthy point from the code:
```
while (timeStream >> token) {
	for(char c : token) time *= 10;
	time += std::stoi(token);
}

while (distanceStream >> token) {
	for (char c : token) distance *= 10;
	distance += std::stoi(token);
}
```
That is a strange what in which to construct the time and the distance. I don't know if I hadn't figured out that theres a ```stol``` and ```stoll``` in the standard library, or if I didn't think to just remove the whitespace from the input. Either way, that's odd. The main thing is it worked.

**Part 1:** *7 ms*
**Part 2:** *1 ms*

## Day 7
### Part 1
My narrative self has apparently become equally exasperated with the elves, as the story makes a point of predicting they'll want our help with the missing parts for their sand machine.  
But first, time for a multiple-day camel ride now. Having done this once in real life for half an hour, I can attest to the need for some sort of distraction if you were to do it for extended periods of time. To this end, our new guide offers to play a game of Camel Cards.  
Somewhat dubiously descrivd as similar to poker, in Camel Cards we get a list of hands of five cards with the same values as normal cards (T replaces 10 to keep everything 1 character). The strength of a hand follows this order:
```
- Five of a kind, where all five cards have the same label: AAAAA
- Four of a kind, where four cards have the same label and one card has a different label: AA8AA
- Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
- Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
- Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
- One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
- High card, where all cards' labels are distinct: 23456
```
Aces high for any tiebreaks beteen hands, with the importance of the cards being left to right - that is to say, if you have ```A2222``` and ```4AAAA```, they are both four of a kind but the first hand is stronger because its leftmost card is higher. The same would be true of ```AAA4A``` and ```A4AAA``` - left is stronger here.
Each hand we are given has a corresponding bid. Our example input looks like this:  
```
32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483
```
We have to rank the hands from weakest to strongest and return the sum of the products of bids and ranks.
#### Solution
This seemed like an initially complicated problem, but with the right data structures it ends up being almost trivial in the final implementation.  
I created the concept of a Hand struct - it has three jobs. 
- Firstly, store the value of Ace to 2, which is 13 to 1 (that could have maybe been more sensible, but oh well). 
- Secondly, implement a comparison between hands on the basis of the values of the hands (next point).
- Thirdly, calculate the value of a hand.

It's this last point where the magic happens. I needed a way to ensure that a better type of hand is always higher in comparison to a worse type of hand, but where two of the same type of hand took into account the face values of cards in order of importance.  
Although I had the right idea for a while, it took a little bit of fiddling to get the numbers exactly right. The final value calculation for a hand looked like this:
```
for (int i = 0; i < cards.size(); i++) {
	char card = cards[i];
	value += mappings[card] * std::pow(14, cards.size() - i - 1);
	cardTypes.try_emplace(card, 0);
	cardTypes[card]++;
}

switch(cardTypes.size()) {
case 1:
	value += 6000000;
	break;
case 2:
	for(auto kv : cardTypes) {
		if(kv.second == 4 || kv.second == 1) value += 5000000;
		else value += 4000000;
		break;
	}
	break;
case 3:
	for (auto kv : cardTypes) {
		if(kv.second == 3) {
			value += 3000000;
			break;
		}
		if(kv.second == 2) {
			value += 2000000;
			break;
		}
	}
	break;
case 4:
	value += 1000000;
	break;
default:
	break;
}
```
Breaking this down: I iterated through the cards, storing the types of card and the number of them in a map, as well as creating a base 14 value using the card types - base 14 to ensure that a '2' earlier than an 'A' is more valuable.  
Once that was done, I checked the number of types of card in the dictionary to see what type of hand it was. 
- If there was one type, it must be a 5 of a kind.
- If there were two types of card, it could either be a full house or a four of a kind - I could tell based on whether the first card type had either 1 or 4 instances, or neither.
- Three types of card and we were either looking at three of a kind or two pairs - again, I could discern this based on the values of the cards dictionary.
- Four types of cards meant it was definitely a single pair.
- Otherwise, we're looking at a high card.
Having determined what type of hand I was dealing with, I added a large integer to ensure that, for example, all hands of two pairs were worth less than three of a kind, regardless of the values or orderings of the actual cards; Three of a kind was less than a full house; and so on.  

With the calculation of the value of a hand complete, the main problem is solved by simply constructing an **ordered** map of the hands and bids, using the hands as the keys. This ordered map, along with the hand value and custom comparison, means that once I'd read the file, I had an already ranked list of bids, and could perform a simple sum of products for the answer. A very satisfying final solution.  
### Part 2
We have had an additional rule introduced (perhaps because we were winning and the elf is a sore loser? Who can say). Regardless, now the 'J' stands for Joker. Any 'J's are counted as the card that would create the strongest hand. To compensate, they are now worth the least themselves - that is, the cards now run in value 'A', 'K', ..., '2', 'J'.  
How do we rank the bids now?
#### Solution
For some reason, I struggled with this one initially. The approach seems obvious and near enough identical to part 1 - I simply needed to calculate the strength of a hand differently.  
My approach, after a lot of debugging edge cases, was this. When iterating through the cards, keep track of the numbers of jokers. Don't put jokers in the card dictionary. Once I'd figured out how many jokers there were and how many of the other types of cards there were, I added the number of jokers to the card which had the most cards already - this always gave the best possible hand.
```
for (int i = 0; i < cards.size(); i++) {
	char card = cards[i];
	value += mappings[card] * std::pow(14, cards.size() - i - 1);
	if (card == 'J') {
		jokers++;
		continue;
	}
	cardTypes.try_emplace(card, 0);
	cardTypes[card]++;
}

if(jokers > 0) {
	char strongest = cards[0];
	int strongestNumCards = cardTypes[strongest];

	for (int i = 1; i < cards.size(); i++) {
		char card = cards[i];
		if (card == 'J') continue;
		int numCards = cardTypes[card];
		if (numCards > strongestNumCards) {
			strongestNumCards = numCards;
			strongest = card;
		}
	}

	cardTypes[strongest] += jokers;
}

switch(cardTypes.size()) {
case 1:
	value += 6000000;
	break;
...
```
After this adjustment, everything else should be the same. It even worked for the example input - but on the real input, it was wrong, presumably by not much. I couldn't figure it out, even after hours of debugging.  
At this point, it was Christmas Eve, thanks to start-delaying exploding laptop. I decided not to torture myself on Christmas Day and instead did the first part of day 8 - I don't actually remember squeezing this in. I took Boxing Day off - my first day not programming for some time at this point, as I'd been on a roll.  
But December 27th I was back with a fiery vengence, ready to beat this problem into submission. I did what I should have done as soon as it was clear there were edge cases I was missing - come up with a bunch of scenarios involving jokers and check the orderings manually. As soon as I decided to do that, I could see a problem with a single hand.  
J.  
J.  
J.  
J.  
J.  
A hand full of jokers. This should be one of the strongest hands in the game barring any other five-of-a-kinds, so why was it sitting as the very weakest hand in my test?  
Eventually, it came down to the smallest of changes. I needed to ignore the 'strongestCard' checks when there were 0 or 5 jokers, not just 0 - and then, in the case of no card types in the dictionary, we must be looking at a hand full of jokers so act accordingly. The changes came down to this:
```
for (int i = 0; i < cards.size(); i++) {
	char card = cards[i];
	value += mappings[card] * std::pow(14, cards.size() - i - 1);
	if (card == 'J') {
		jokers++;
		continue;
	}
	cardTypes.try_emplace(card, 0);
	cardTypes[card]++;
}

if(jokers > 0 && jokers < 5) { <------------------------------
	char strongest = cards[0];
	int strongestNumCards = cardTypes[strongest];

	for (int i = 1; i < cards.size(); i++) {
		char card = cards[i];
		if (card == 'J') continue;
		int numCards = cardTypes[card];
		if (numCards > strongestNumCards) {
			strongestNumCards = numCards;
			strongest = card;
		}
	}

	cardTypes[strongest] += jokers;
}

switch(cardTypes.size()) {
case 0:	<------------------------------
case 1:
	value += 6000000;
	break;
...
```
How frustrating...

**Part 1:** *83 ms*
**Part 2:** *14 ms*

## Day 8
### Part 1
Having lost our guide and camel companion because she turned out to be, say it with me now, a ghost, we find a set of maps and try to puzzle our way out of the desert. We have a list of directions and a list of nodes:
```
RL

AAA = (BBB, CCC)
BBB = (DDD, EEE)
CCC = (ZZZ, GGG)
DDD = (DDD, DDD)
EEE = (EEE, EEE)
GGG = (GGG, GGG)
ZZZ = (ZZZ, ZZZ)
```
Starting at ```AAA```, we navigate our way through the nodes until we reach ```ZZZ```. At each step, we choose either the left or right node in the pair of choices based on our current instruction from the first line, which loops if we run out of instructions before reaching ZZZ (i.e. the first line is really RLRLRLRLRLRLRL..... ad infinitum).  
How many steps does it take us to go from ```AAA``` to ```ZZZ```?
#### Solution
There's very little to say about this part. I constructed a map of the nodes, where each value is the pair of nodes connected to the key node. I then set the current node to the start and follow the instructions until I reached the end, counting the number of steps. Nothing interesting here.
### Part 2
The previous attempt was apparently not good enough and now we think the map is actually for ghosts! Additionally, these ghosts would apparently start simultaneously at all nodes ending in A and would, for each instance of themselves, follow the instructions from the respective nodes until all instances of the ghosts were simultaneously at nodes ending in Z. Confusing, so let's look at the example again.  
> - Step 0: You are at 11A and 22A.
> - Step 1: You choose all of the left paths, leading you to 11B and 22B.
> - Step 2: You choose all of the right paths, leading you to 11Z and 22C.
> - Step 3: You choose all of the left paths, leading you to 11B and 22Z.
> - Step 4: You choose all of the right paths, leading you to 11Z and 22B.
> - Step 5: You choose all of the left paths, leading you to 11B and 22C.
> - Step 6: You choose all of the right paths, leading you to 11Z and 22Z.
#### Solution
Ah, to be young and unaware of AoC's propensity for cycle detection problems (I think that's the quote). Initially this seemed straightforward to me. Convert the code to keep track of a vector of current positions, for each of which we took the appropriate step, and only stop once all the isntances were at nodes ending in Z. Simple, clean, worked beautifully for the example. What could go wrong?  

Once I'd acknowledged that it was almost definitely too slow to just leave running (though the halting problem was haunting me a little), it was back to the drawing board. I tried out various optimisation ideas, but they were fundamentally piddly time improvements if they weren't already being done by compiler optimisation in the background. Eventually I realised I must be going about this the wrong way; I believe it was at this point that I took my first peek at the Reddit solutions page for a pointer.  
It was here that I saw the term cycle detection; of course, I knew of the concept of cycles in a graph, but it had never occurred to me that this might well be the solution here. I had promised myself before starting AoC that I would keep outside help to a minimum, so as soon as I had this idea I went to close the tab; as I did so, my eyes glanced over one final term - LCM...  
So, I altered my code. Now, instead of iterating through all 'ghosts' at every step, I stuck with one ghost at a time and figured out how many steps it would take to reach a node ending in Z. Once I had that value for all ghosts, I calculated the lowest common mmultiple for them all, plugging each into an LCM function with the value of the previous LCM:
```
answer = 1;

for(int dist : cycleDistances) {
	answer = lcm(answer, dist);
}
```
Bada-bing bada-boom, the answer appeared before me even faster than part 1.

Looking back with more understanding of a) cycle detection and b) how AoC tends to structure problems, I think I was quite lucky with how the inputs were constructed. There was actually no guarantee that there wasn't an extra section of steps before the system settled in a steady cycle for each ghost - unless that was in fact the case and fortunately enough the factorisation was such that the lowest common multiple was still the same? Perhaps we'll never know...

**Part 1:** *32 ms*
**Part 2:** *7 ms*

## Day 9
### Part 1
As the sandstorm subsides, we find ourselves standing at a miraculous oasis beneath another floating island, from which (we leap to the not unreasonable conclusion) the missing parts should be coming. While we wait for the sun to heat up the desert sand so we can use the thermals to glide up to the island on a convenient hang glider, we decide to perform an ecological survey of sorts on the oasis; evidently, we've not got enough to be getting on with in terms of sorting global snow production.  
Our handy **O**asis **a**nd **S**and **I**nstability **S**ensor, or **OASIS** for short (is this an instance of GNU or CINC?), produces a report of many values and how they're changing over time, each contained within a single line.
```
0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45
```
We need to predict the next value for each sequence. Taking the second line as an example, we would need to produce something like this:
```
1   3   6  10  15  21
  2   3   4   5   6
    1   1   1   1
      0   0   0
```
Once we've reached a sequence where all the numbers are 0, we can extrapolate our way back up to predict the next number in the original sequence. To do this, we add the last number of the bottom sequence to the last number of the sequence above, to get a new number, repeating this iteratively:
```
1   3   6  10  15  21  28 [21+7]
  2   3   4   5   6   7 [6+1]
    1   1   1   1   1 [1+0]
      0   0   0   0 [0+0]
```
We then need to sum the new numbers for all the sequences for our final answer. Seems straightforward enough - let's go!
#### Solution
Quite a straightforward one today, very much a case of transcribing exactly what's written into code, without any tricky edge cases that I noticed. I started by creating a vector for each line, containing all the integers as written.  
Next, I repeatedly created a new sequence from the differences between each value in the sequence. I checked if any of the values in the new sequence were non-zero; if so, I flagged that the process needed to be run again.
```
bool allZero = false;

while (!allZero) {
	allZero = true;
	sequences.push_back(sequence);
	sequence.clear();
	prevSeq = sequences.back();

	for (int i = 1; i < prevSeq.size(); i++) {
		int diff = prevSeq[i] - prevSeq[i - 1];
		sequence.push_back(diff);
		allZero = allZero && (diff == 0);
	}
}
```
Once all the values in a sequence were 0 and I could break out of the above loop, all that was left was to propagate that information back up through the sequences. Starting with a cumulative 'add' of zero and beginning at the last sequence created, I summed all the final values of each sequence.
```
int add = 0;
for(int i = sequences.size() - 1; i > -1; i--) {
	add += sequences[i].back();
}

answer += add;
```
Something to note was that I tracked all the sequences created for each line in a vector of vectors and reiterated over each of those. Perhaps I could have improved performance by starting the cumulative add on the way down the sequences - then I could have just kept track of one at any given time and skipped out the second loop entirely.
### Part 2
Apparently I'm *still* underworked, as now I decide to extrapolate backwards. What a surprise...
#### Solution
I don't know whether it was just down to the manner in which I implemented the first part or whether this was just a particularly easy second part, but this was just as straightforward as the first part, with an almost identical approach. The sequence creation was identical - the only difference was in the extrapolation.
```
int add = 0;
for (int i = sequences.size() - 1; i > -1; i--) {
	add = sequences[i].front() - add;
}

answer += add;
```
Day 9 in the books - onto double digits and a real struggle over the next three weeks...

**Part 1:** *20 ms*
**Part 2:** *3 ms*

## Day 10
### Part 1
On the floating island above the desert, we find nothing except an entirely metal world: floor, plants, even an animal scurrying away! We're immediately drawn away from the signs we had been following labelled "Hot Springs" to try catch this random, potentially dangerous animal.  
Scanning the ground, we realise a large proportion is actually densely packed pipes in amongst the rest of the ground, represented like this:
> - | is a vertical pipe connecting north and south.
> - - is a horizontal pipe connecting east and west.
> - L is a 90-degree bend connecting north and east.
> - J is a 90-degree bend connecting north and west.
> - 7 is a 90-degree bend connecting south and west.
> - F is a 90-degree bend connecting south and east.
> - . is ground; there is no pipe in this tile.
> - S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
We assess from the acoustings of the scurrying below is that there is one large continuous loop containing the animal - something like this:
```
.....
.F-7.
.|.|.
.L-J.
.....
```
Or this:
```
..F7.
.FJ|.
SJ.L7
|F--J
LJ...
```
But there are lots of pipes not connected to the main loop and we're also not certain of the shape of the pipe the animal leapt down, ```S```:
```
7-F7-
.FJ|7
SJLL7
|F--J
LJ.LJ
```
We want to get ahead of the animal. To do this, we need to find the tile around the loop that is furthest in terms of steps around the loop regardless of direction from the starting tile. For the example above, the tile marked 8 is furthest away.
```
..45.
.236.
01.78
14567
23...
```
Now let's find it on the real input.
#### Solution
Let's crack our knuckles and get to work. First off, let's figure out where the starting tile is:
```
for(std::string line : input) {
	if(line.empty()) break;

	for(char c : line) {
		if(c == 'S') {
			lineNum = currentLine;
			col = currentCol;

			break;
		}
		currentCol++;
	}
	if (lineNum > -1 && col > -1) break;
	currentLine++;
}
```
Easy enough, what's next? I needed to know what direction to start off in, as we don't know the shape of the pipe under 'S'. I figured that, for at least part 1, they would make it obvious and I wouldn't have to track multiple directions until they hit dead ends - this presumption turned out to be correct.  
So, I was able to check if the tile about was a tile you could logically 'enter' from below (i.e a '7', '|', or 'F'), the one to left was one you could enter from the right, etc, and start there:
```
if(lineNum > 0) {
	if(input[lineNum - 1][col] == '7' || input[lineNum - 1][col] == '|' || input[lineNum - 1][col] == 'F') direction = 0;
}
if(lineNum < input.size() - 2 && direction == -1) {
	if (input[lineNum + 1][col] == 'J' || input[lineNum + 1][col] == '|' || input[lineNum + 1][col] == 'L') direction = 2;
}
if(col < input[lineNum].size() - 2 && direction == -1) {
	if(input[lineNum][col + 1] == 'J' || input[lineNum][col + 1] == '-' || input[lineNum][col + 1] == '7') direction = 1;
}
if(col > 0 && direction == -1) {
	if(input[lineNum][col - 1] == 'L' || input[lineNum][col - 1] == '-' || input[lineNum][col - 1] == 'F') direction = 3;
}
```
Now I setup the main loop. Each iteration, I increment the step count and move to the tile in the current 'direction'. I then alter the direction based on the tile. Let's say I currently have direction '0' for 'up' and I enter a '|' tile - well, my direction doesn't change, I continue to go up. But if I enter a 'F', I now have direction '1' for 'right' and will adjust my next step accordingly. In code, that breaks down to a big ol' switch statement with accompanying ifs. (I have ommitted all the checks that the step I was taking made sense in terms of the problem - not moving sideways into a '|' pipe for exmaple - for legibility.)
```
while(!end) {
	steps++;

	switch(direction) {
	case 0:
		lineNum--;
		break;
	case 1:
		col++;
		break;
	case 2:
		lineNum++;
		break;
	case 3:
		col--;
		break;
	}

	char current = input[lineNum][col];
	switch (current) {
	case '.':
		std::cout << "Shouldn't encounter ground" << std::endl;
		assert(false);
		break;
	case '|':
		break;
	case '-':
		break;
	case 'L':
		if(direction == 2) direction = 1;
		else direction = 0;
		break;
	case 'J':
		if(direction == 2) direction = 3;
		else direction = 0;
		break;
	case '7':
		if(direction == 0) direction = 3;
		else direction = 2;
		break;
	case 'F':
		if(direction == 0) direction = 1;
		else direction = 2;
		break;
	case 'S':
		end = true;
		break;
	}
}
```
Once I reach 'S' again, we have traversed the full loop and counted the number of steps it took - the answer is just halfway along - ```return (steps / 2) + steps % 2;```
Excellent, onto par - oh, it doesn't work? It's trying to access outside the vectors? What??
Some debugging later, and one solitary change in the next commit:
```
for(std::string line : input) {
	if(line.empty()) break;

	for(char c : line) {
		...
	}
	if (lineNum > -1 && col > -1) break;
	currentLine++;
	currentCol = 0; <------------------------------
}
```
With a bit of extreme face-palming, I had my solution. I just needed to actually start from the starting location.
### Part 2
Having been unable to catch the creature thus far, we are struck by another brainwave (or perhaps a cartoon mallet?) - perhaps the animal has a nest enclosed by the loop we have identified? But is it even worth searching all those pipes...  
Well, lets figure out how many possible tiles that could be and then decide!  
Taking this example pipe layout:
```
...........
.S-------7.
.|F-----7|.
.||.....||.
.||.....||.
.|L-7.F-J|.
.|..|.|..|.
.L--J.L--J.
...........
```
There are only four tiles enclosed in the loop, marked I below. The segment in the very middle, marked with O, is actually outside the loop:
```
...........
.S-------7.
.|F-----7|.
.||OOOOO||.
.||OOOOO||.
.|L-7OF-J|.
.|II|O|II|.
.L--JOL--J.
.....O.....
```
But the same is actually true of the below layout:
```
..........
.S------7.
.|F----7|.
.||OOOO||.
.||OOOO||.
.|L-7F-J|.
.|II||II|.
.L--JL--J.
..........
```
So, we're talking about inside from a topographical perspective. Should be breezy, right?
#### Solution
Wrong. I found this a conceptually challenging puzzle. If the layout was of the first type above, with at least one tile of gap between any loop pieces, then this would be a case of a simple flood-fill algorithm. Obviously, however, they wouldn't have given the second example were that the case - or at least, it would have been cruel to do so.  
I toyed around with the idea of implementing a [point in polygon algorithm](https://en.wikipedia.org/wiki/Point_in_polygon), but from memory decided that it would be my backup approach, as it felt quite complex to do and I wasn't certain if there were prequisites about the polygons that perhaps my loop wouldn't fulfil.  
I eventually took the approach that I think many people did, looking on the solutions thread afterwards - I took the singular pipe characters and blew them up to 3x3 represntations:
```
	...
F = .##
	.#.
	
	.#.
| = .#.
	.#.
```
Then, two '|' symbols next to each other (||) became:
```
.#..#.
.#..#.
.#..#.
```
I also replaced any symbols not part of the main loop with the ground representation, a 3x3 grid of '.' - I repurposed the approach from the first part to figure out which tiles those were - as well as surrounding the whole thing with an extra ring of empty tiles. Once all of that was in place, then I could implement a simple flood fill algorithm, replacing '.' with 'O'.  
Finally, I counted the number of grid-aligned 3x3 blocks of periods - these were the original tiles inside the loop.  
```
This would be one tile inside a basic loop:

OOOOOOOOO
O#######O
O#.....#O
O#.III.#O
O#.III.#O
O#.III.#O
O#.....#O
O#######O
OOOOOOOOO
```
I'm not going to show any code for this one, as it's several hundred lines, but it's all available on the repository. I was pleased to be done with this part two without implementing the polygon approach.

**Part 1:** *24 ms*
**Part 2:** *7 ms*

## Day 11
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *25 ms*
**Part 2:** *6 ms*

## Day 12
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *120 ms*
**Part 2:** *2354 ms*

## Day 13
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *54 ms*
**Part 2:** *2 ms*

## Day 14
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *19 ms*
**Part 2:** *53 ms*

## Day 15
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *15 ms*
**Part 2:** *2 ms*

## Day 16
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *64 ms*
**Part 2:** *16531 ms*

## Day 17
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *368 ms*
**Part 2:** *1134 ms*

## Day 18
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *71 ms*
**Part 2:** *23 ms*

## Day 19
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *25 ms*
**Part 2:** *12 ms*

## Day 20
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *49 ms*
**Part 2:** *130 ms*

## Day 21
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *47 ms*
**Part 2:** *77806 ms*

## Day 22
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *45 ms*
**Part 2:** *1 ms*

## Day 23
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *25 ms*
**Part 2:** *1 ms*

## Day 24
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *18 ms*
**Part 2:** *3 ms*

## Day 25
### Part 1

#### Solution

### Part 2

#### Solution

**Part 1:** *75217 ms*
**Part 2:** *0 ms*
