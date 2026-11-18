# Quest 1

[Quest description](https://everybody.codes/event/2026/quests/1)

## Problem summary

The problem at hand is determining the number of pinecones necessary to fill in the defenses. To do that, we need to parse the input file out for heach outpost. The files seem large enough to practically put into memory as a string, but I'd like to avoid that if possible, so each one is chunked.

## Approach

### Part 1

This part has to do with making squares out of the number already there. For any value, it's just the distance to the next perfect squre. I found that if I just take the square root, and then the ceiling of the value, it gets you the base you need. Square that value, and take the difference and you're good. There's a chance that there can be too many operations, especially floating point ones, so there's a chance to revise the integer arithmetic if I want to push the speed. Otherwise, the method seems to work alright.

### Part 2

This time, we need the perimiter. We can cut out a lot of the internals fortuately, but we have a similar problem still. The key difference, is that increasing the side of a square increases the number by 4, meaning that we actually are just increasing by 4. This means that the size will always BE a multiple of 4 as well (p = 4n - 4 = 4(n-1) so is must be a multiple of 4). So we can just take the number mod 4, and see the distance to a multiple of 4. However, it will always need to go higher, so we can just subtract that modulus from 4 as it's our "overhang" from the lower multiple, and we need the upper part.

### Part 3

This one was conceptually easy. It ends up being the distance to the square. HOWEVER, they squares must be odd. That's easy enough to handle, as we can just add 1 to even numbers to make them odd. There's again a minimum requirement, easily fixed. The last part that gives trouble is making sure that the numbers that are already perfect squares are used properly. Since the ceiling of a whole number will just be the number, we can be confident that their distance must be zero. If that's the case, just add one to the square base we're using and proceed

## Notes and lessons learned

Pretty good. I'd make sure to setup the infrastructure BEFORE jumping into the challenge, but not too bad honestly. Overall, it wasn't too bad. Just used standard library stuff. Nothing really past C++14 I think, so not especially modern either. I think to speed things up, I'd probably find a way to multi-thread it. I can imagine that the gains may be negligible, but it could increase speed.
