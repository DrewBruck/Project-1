Drew Bruck
Project 1 Readme File

This project is (hopefully) a functional, fully working program that can create 
2-dimensional points of any size and perform various actions with said points.

By creating a Class within the program that creates an array of multiple 2D points, the 
user should be able to add and print the sums of points (integers or doubles), 
copy sequences of points, move sequences of points, and best of all, print those 
sequences however they see fit.

This was only made possible by overloading certain key features within the program, such
as <<. >>, +, and =.  By changing the behaviors of these operators, the user should be
able to use these operations on created objects in the program as though they were 
simple integers or strings.

The burden within the assignment was most evident by the overloading of the >> operator so
that the object class could have user-input as a means of constructing 2d Point Objects. 
My inital attempt to solve this involved way too many steps and took in the entire input as 
a string.  Then using the "stoi" operator from the STL, manipulating that to work with 
the constructors.  This proved to be quite a mess and a headache.  My second attempt is 
what is present and that involves taking the first number to create an appropriately sized
object and then creating a loop of that size to correctly input all the points into the class.

