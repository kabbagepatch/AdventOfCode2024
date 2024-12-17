Part one was a fairly straightforward looking Dijkstra's problem, where I had a weighted maze, and I had to find my way around it. With some handy helper methods to handle the score calculations based on direction, it was easily done

Part two ended up being more complicated than I thought. My simple Dijkstra was good at finding one path with the minimum score. But finding all paths seemed to be a struggle. I tried multiple variations of keeping track of the parents, scores, etc. Nothing seemed to work. It either only gave me one path, or started including more inefficient paths. 

My biggest issue was that because of the turning cost, a particular cell's minimum score was different based on the direction I'm facing, and therefore, the next cell's score could be the same regardless of the path it took to get to the previous cell. This was particularly common when a path split into two, and later met back up.

In the end, I had to change my code so that instead of keeping track of each cell's minimum score as a singular value, I keep track of each cell's minimum score facing a certain direction (i.e, where it came from), and similarly, the parent from that direction. And during the parent backtracking, instead of finding the parent with the lowest score, I find the parent with that would cost the lowest to get to the current cell
