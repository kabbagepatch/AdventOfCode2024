The first part was straightforward enough. Split each report into levels, and iterate over them to find any unsafe ones.

For the second part, I really wanted to try and avoid making new vectors over and over with one less element. So I modified some of the logic to check for unsafe levels and addeda a "ignore index" property. Worked well enough and we didn't need new vectors
