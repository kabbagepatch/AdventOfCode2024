Yet another maze. I pulled out my BFS code and put it in here. The only catch. Now we can warp through a wall. For part one, just one wall, so I found all the walls that you can warp through, and did a BFS the maze with that wall removed. That gave me the answer.

Part two, you can warp through as many walls as you can in 20 steps. This is a lot more complicated and expensive to run BFS through, given the sheer number of possibilities. My initial idea was that one by one, treating one point at a time as the "warp start", I'll find the places it can "warp end" safely, and count that as the neighbors as I run BFS. However, I realised that I'll be computing the distance to this warp start over and over. And how often am I gonna hit the same warp ends through different starts. And then, after thinking about it for a while, it hit me. I already have those values. In the BFS, looking for end, I calculate the distance to each space, from the start. I can just use those values and use this equation for the time saved:
```
time_saved = start_to_warpend - (start_to_warpstart + warp_distance)
```
that is, the difference in time to get to the warp end the normal way and the cheat way
Thus, I don't need to do another BFS at all! My CPU thanks me
