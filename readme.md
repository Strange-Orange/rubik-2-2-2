# Rubik 2-2-2 Breadth First search

This was inspired by the MIT OpenCourseWare [lecture](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-13-breadth-first-search-bfs/) on breadth first search and the associated [pdf](https://courses.csail.mit.edu/6.006/fall11/rec/rec16.pdf).

This is not very suitable for solving the Rubik's cube, it was created for me to get a greater intuition on how breadth first search works on a large graph.

## Warning
This is a breadth first search on a 2-2-2 Rubik's cube, that is over 3 million possible configurations. This means it can be an absolute memory hog, it can easily use over 6 gigabytes of memory on certain scrambles.

### Usage
The scramble to be performed is passed as arguments in the order they are to take place.
Just the letter reperesenting the face for a quarter clockwise rotation and the letter and a for a quarter turn anti-clockwise. Example below.
Once the cube has been solved the program will print the moves to perform to return to the solved state and close.

f and fa for front clockwise and anti-clockwise

r and ra for right clockwise and anti-clockwise

l and la for left clockwise and anti-clockwise

u and ua for upper clockwise and anti-clockwise

b and ba for bottom clockwise and anti-clockwise

e and ea for end clockwise and anti-clockwise

### Example
```
f ra b ea
```
These arguments will perform a front clockwise, right anti-clockwise, bottom clockwise and a end anti-clockwise rotations on the cube.
