Recursion is your friend. Especially in problems like this. The operators had to be applied left to right, which means I can go in reverse and use recursion, and check if the result is possible without the last operand. Some small logic to look for impossible conditions (like multiplication when the result is not divisible by the last operand), and it worked pretty well

For part two, I just had to add a small extra condition to my recursion, to check for concatenation, thanks to some string checks. And it also worked

The only thing to look out for was using long instead of ints, coz the numbers are big
