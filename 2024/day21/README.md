# Advent of Code 2024
## Day 21
### Part 1
> “We got a bit carried away,” said Moist. “We were a bit too creative in our thinking. We > encouraged mongooses to breed in the posting boxes to keep down the snakes…”
> Lord Vetinari said nothing.
> “Er… which, admittedly, we introduced into the letter boxes to reduce the number of toads…”
> Lord Vetinari repeated himself.
> “Er… which, it’s true, staff put in the posting boxes to keep down the snails…”
> Lord Vetinari remained unvocal.
> “Er… These, I must in fairness point out, got into the boxes of their own accord, in order to eat the glue on the stamps,” said Moist, aware that he was beginning to burble.
> “Well, at least you were saved the trouble of having to introduce them yourselves,” said Lord Vetinari cheerfully. “As you indicate, this may well have been a case where chilly logic should have been replaced by the common sense of, perhaps, the average chicken.”  
>
>Terry Pratchett, *Making Money*  

This quote from the inestimable Terry Pratchett was the first thing that came to mind as I read the mess of today's challenge; directing a robot to direct a robot to direct a robot to enter a series of numbers on a numberpad, via a series of directional keypads, in order to save a  historian trapped in a death chamber. Why do we have to use robots? Well, the number pad is also in a death chamber, as is the first directional keypad, as is the second. Don't question it.  

Given the numberpad and three consectuve directional keypads, which look like the below:
```
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+

    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
```
We need to enter a series of 4 digit keys in the fewest keypresses possible. The first directional pad controls the robot arm at the second, which controls the robot arm at the third, which controls the robot arm at the numeric keypad; so far, so nonsensical.

All the robots start with the pointer directed at the A button on their respective pads. The directional arrows move where the next arm in the chain is pointing; the A(ctivate? ction?) button tells it to press down where it's currently pointing. We also aren't allowed to go over the empty gap on any keypad at any point.  

How many keystrokes do we need, at a minimum, to enter all the codes?

### Solution
I had the right idea on this fairly quickly but got hung up on a detail that messed me up a bit. There are a few key insights that make this managable.  

Firstly, every time the arm on a layer presses a button, all the previous layers must, by definition, be point at the A button. This will come in handy later on. Additionally, we're looking for the shortest number of button presses possible. This means that, always, we're going to attempt to move as far as possible in one direction before changing to another. By doing this, the previous layers of robot are able to take advantage of just repeatedly pressing the activate button.

Ok, let's think. Whatever the solution, it's probably going to need a cache, because honestly, what doesn't at this point. More specifically, I can see how quickly this is going to expand across the layers, and I'm willing to bet that part two will just be a crap more layers of directional keypads, so we might as well write that optimised recursive solution now.  

We need to sum how many buttons we, at the end of the chain, need to press to move from A to the first digit, to the second digit, to the third digit, and then back to A. The recursive solution, then, is based on this:  

We create a series of pairs of digits we need to move from and to on the numeric key pad. This is passed to a recursive function, along with what layer this is in the chain and the total number of layers.  

The recursive function checks if we're at layer 0 (by my convention, this is the keypad we control). If we are, return 1, since we can just press any button without issue. If not, we select whether we're on a directional pad or the numeric pad, based on whether the current layer is equal to the number of layers.

We then find *all* the minimum paths required to navigate from the start to the end, using a breadth-first search with the constraint that any path over the empty space is disallowed. In reality, this will likely be just two, alternating L-shapes. We append 'A', because we need to tell the preceding layer to activate as well.  

Once we have those paths, we again create a series of pairs of steps from A along the path required and back to A. These pairs are recursively passed into the function, with a reduction of 1 in the layer parameter, and summed. This gives us the key presses for that particular path. We return the minimum number of key presses over the various paths. This cascades up and gives us our final answer.  

### Part 2
Just as we rescue the hapless victim, another historian is discovered to be trapped in another deadly room; it never rains but it pours, eh? This time, however, there are many more hazards, meaning there is one directional keypad in use by us, twenty-five in use by robots, and one numeric keypad in use by the final robot. What's the minimum number of keypresses needed now?
### Solution
Ding dong, 26 different robots are involved now. Gee, sure hope that's not too hard to handle.  

Copy, paste, change two 3s to 26s, and we're done, in the same amount of time, actually. Again, because both parts are using the same @cache decorated function, a lot of the hard work is done by the time we start running the second part, which clearly makes up for the extra layers. I tried changing part 2 to use the same number of layers as part 1 and it runs in ~0.03ms, since all the work now is just fetching from a dictionary.

**Part 1:** *1.19 ms*  
**Part 2:** *1.19 ms*  

[Back to all days](/2024)