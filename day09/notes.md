This was a lot of just iterating through the list of numbers, both from the front and the back, and doing things with the information

For part one, I really wanted to just calculate the checkSum using the loop and not actually form the resulting filesystem. So I set up a loop that counts the files from front, but also keeps track of the back files that can be moved to the spaces between the front files. That worked well enough

But as it goes with these problems, sometimes the solution isn't quite right for part two. So for part two, when entire files had to be moved together, I decided I should actually build the filesystem as a vector, and move things around accordingly. So that's exactly what I did. Then my loop was set to start from the back of the filestring, and try to find a place for each file from the front and "fill up that space" by just modifying the filestring, while updating the filesystem vector accordingly.
