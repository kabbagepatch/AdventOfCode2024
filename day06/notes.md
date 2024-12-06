This problem involved travelling a path in a 2d array. For part one, it was pretty straightforward; travel in a given direction, if you hit an obstacle turn right, if you're out of bounds, we're down. A simple while loop with a switch statement in it did the job

Part two was more interesting. We had to find ways to get the guard get stuck in a loop by adding one obstacle to their path. One thing was immediately obvious to me, that the only places I need to test the obstacle is in their path. So I added a "modified" input file, from part one, with their visited points marked. After that, the only real way I saw of solving this problem was to put an obstacle at each point, one at a time, and see if they get stuck in a loop or still go out of bounds. I slightly modified my part one logic, and added a map to watch for loops (defining a loop as visiting the same point in the same direction twice), and let it run. It was slow. But about a minute later I had my answer