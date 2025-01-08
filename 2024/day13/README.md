# Advent of Code 2024
## Day 13
### Part 1
A well-earned break is next, as we stop off at the lobby of a tropical island resort; how pleasant. While the historians continue searching for CH, we decide to try win prizes from a series of claw machines.  

Instead of a joystick or directional buttons, these claw machines instead have two buttons; each button moves it forward by a certain amount and right by another amount; those amounts vary by claw machine. It costs 3 tokens to push the first button and 1 token to push the second. We win the prize if and only if the claw is positioned exactly above the prize, the location of which is also given. An example claw machine looks like this:
```
Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400
```
Some machines aren't winnable (we'd have to push buttons a fraction instead of a whole number in order to line up). We also estimate that each button would need to be pressed no more than 100 times - how else could someone play? What is the minimum number of tokens that we have to spend in order to win all possible prizes?
### Solution
My initial thought was that this was an optimisation problem; there's a lot of talk of minimum amounts, etc., and the constraint of maximum button presses suggests naturally some for loops. However, upon looking more closely at the data we're given, my two remaining neurons fired and informed me that this looks like a linear algebra problem; we have, essentially two unknowns and two equations. The example above would allow us to construct the equations:
```
94A + 22B = 8400
34A + 67B = 5400
```
Now, I wasn't dead certain at the time, but some vague intuition/memory from university also told me that for a system of unknown variables and equations for those variables, if there are the same number of unknowns as equations (as we have here) there is one unique solution; so, despite the rubric discussing minimums, there is only one actual answer for each set of equations. I have since validated that this is true, but at the time I just presumed and went for it.  

With this being the case, I just needed to solve for A or B, check that it was a whole number (this for the constraint of being precisely over the prize) and, if it was an integer, solve for the other of the unknowns and return the cost in tokens (3A + B).  

There followed half an hour of trying to generalise the solution to a two-variable linear algebra equation in the format I'd been given, which was not nearly as hard as I made it for myself; it didn't help matters that I got the coefficients in the initial equations in the wrong order.  

Once I'd faffed about with that for a while, however, it worked perfectly and fast. Very pleasing stuff. I remember a problem in one of the last two years where I saw something similar, didn't get the linear algebra link, and approached it with a grid-search using nested for loops. This generally works fine on part 1, but I knew it wouldn't work for part 2, because...
### Part 2
Due to a unit conversion error (?) in our measurements, the position of every prize is actually 10,000,000,000,000 (10^13) higher on both the x- and y-axes. It will take many more than 100 presses on each button now.
### Solution
It's nice to start predicting these patterns; these sorts of problems always slam the number way up, which ensures that only mathematical solutions are fast enough. Fortunately for me, I'd spotted this on part 1, as I say, so I could copy/paste the code, add the requiste amount to each prize coordinate, and solve. This took about a minute extra to submit and ran just as fast. Wonderful.

**Part 1:** *1.75 ms*  
**Part 2:** *1.75 ms*  

[Back to all days](/2024)