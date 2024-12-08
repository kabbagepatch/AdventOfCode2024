To start off, I built up a nice map for every antenna location, with the frequency type as the key. Then I just iterated through the grid, point by point, looking for any points that are, 1) in line with two of the antennae and 2) twice the distance from one than the other. 

I used manhattan distance because I realised if a point is twice the true distance away from another, it is also twice the manhattan distance away. That simplified things. And gave me the answer

And this was the first time part two was easier than part one. I just had to remove the distance check and the rest of the logic was the same.
