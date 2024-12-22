The first part was easy. Just a few operations on a few numbers. Easily done

The second part also wasn't too bad. The brute force approach of testing each possible sequence was pretty silly. So I went with the method of accumulating the prices for each buyer for every change sequence possible in the buyer's prices. With this, I had a big map of sequences and their corresponding prices for each buyer. Iterating through that, I was able to find the max price. It was on change sequence 1, 0, -1, 3
