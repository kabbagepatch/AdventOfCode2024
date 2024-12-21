I actually did it. I can't believe it

This was a haaard problem, even for part one. Though turns out in part one, I was making a bunch of silly mistakes and then trying optimize solutions that weren't really working from the get go. But basically, I wrote a couple methods to find dpad sequences given an input of numbers or other dpad sequences. After playing around with it a bit, I found that moving left, then up/down and then right was optimal. But also had to take into account the blank spaces. This was where my mistake was. Once I did that correctly, I finally got the answer

Part two, I realised calculating the strings would take way too long and be cumbersome. And I really didn't want to go with BFS. Until I realised I needed to just keep track of the counts of each of the individual moves, and use that to get the next set of counts (by getting the next set of subsequences and breaking that into individual moves). And keep doing that. And then just add the move counts up
