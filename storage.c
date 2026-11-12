/*
	mlx = mlx_init(WIDTH, HEIGHT, "MLX Window", true); image  =  mlx_new_image(mlx,
	100,  100);  mlx_image_to_window(mlx,  image,   33,   33);   mlx_loop_hook(mlx,
	draw_in_image, image); mlx_loop(mlx); mlx_terminate(mlx);
*/


/* In the map.cub file each texture has a path. Each texture has an  identifier.
For example: 'NO' <--- Identifier './textures/north_texture' <-- path

So I need to be able to scan each  character  in  the  file  untill  I  see  the
identifier. Then I need to up  everything  after  the  space  into  the  correct
variable. Either a texture type, floor or ceiling

There is 6 of these variables. So I should count each time a variable is  added.
Then I know. After 6, everything after that should be the map.  Maybe  theres  a
better what do do this.

Also one thing to consider is, will the stream go back to the start position  or
will it go upto the point it has read to/ stay there?

I have forgot how the scan() & consume() functions work.

It should be something along the lines of

int scan(int fd, char *identifiers) {

}

if (scan(fd, "NO") == 1) {
	// read till the newline and put in the string variable
}

*/

/* I think the problem with this is that each time the function gets  called  it
uses read and consumes two bites. So I should scan then am then put  them  back.
At the moment I am collecting the line and then going past the identifier.

I maybe get next line is not the right function for this. It is taking too  much
so I cant get the next identifier.

*/

/* I should count upto the point I get a newline and then  I  should  take  that
number and just copy across everything upto that number.

Wait but then we cant go back or can we? Because we have read  upto  that  point
can we go back? */ /* In order to get each  part  of  the  grid  correctly.  How
should I approach this? How will the .cub file differ each time?

	- The order of the floor, ceiling, north, south, east and west tetures can
	  change so I need to use their  "identifiers"  and  then  store  the  path
	  or information that comes afterwards.

*/ /* This should be easier because we are looking for the start of the map  (so
either a 1 or a 0) and then we are using get_next_line() to grab  each  line  of
the map. data->grid is an array of strings. data->grid[0] is  the  first  string
and so on... I should go upto the point

I need to count the number of lines in the grid so I can create the memory space
for the correct amount of lines.

Turns out the best way to do it is to close the file descriptor and then re-open
it so I get a fresh stream to work with.

So the first file descriptor will be used to count the number of  lines  in  the
grid and the second file descriptor will be to  fill  those  lines  but  in  the
data->grid array.

*/ /*

void print_player(t_player *player) {
	printf("%d\n", player->x_position); printf("%d\n", player->y_position);
}                                                                             */
/******************************************************************************
	Orientation:

	How can I figure this out? What numbers do I have to  work  with?  What  is  my
	range of numbers? Work on this.

	Learning

	Understanding Orientation Coordinates:

	X +1 to -1 : Left & Right

	Y +1 to -1 : Up & Down


/*******************************************************************************/
/*
Orientation vector? What should my default be?

I want the player to be looking up and straight. So the y should be 1 and the  x
should be 0. These are the defaults. I might have to change this later  but  for
now this is my instinct. I should be able to use this information along with the
feild of veiw and half_of_feild_of_view variables to draw a triangle.

I want to improve the following  in  my  program  as  it  should  make  it  more
organised and easeir to work with. Also I want to check if the things I have  in
mind are common pratice or not? My first idea is moving the global varaibles.  I
have heard its bad practice to use global variables so I want to know is there a
better way to use the mlx_image_t *var variables? Maybe I should but them  in  a
struct?

Next I want to have one main game struct that  has  pointer  to  all  the  other
structs in my program. This is mainly so I can parse all the data  I  have  into
the mlx functions. Most of the mlx functions only allow  for  one  thing  to  be
parsed. By having this main/ majour struct I can parse a single thing  but  have
all of my data accessable. I also want to become more familiar  with  instances.
What they do and how they work. Also the meaning behind the word.

*/
/*
At the moment the player can move through walls. This  should  not  be  allowed.
Therefore I need to create a function  or  something  that  will  check  if  the
updated coordinates of the player will hit a wall. If yes  then  revert  to  the
original position. If no then update position.

The difficult part is that in my grid I am not moving the 'N' (player) value.  I
never update the "char **grid". Maybe I should update the grid? Or  maybe  there
is another way?

GOOGLE SEARCH

checking the map grid coordinates during player movement

1)
check the map value at the player's future x and y coordinates before updating their position.
Convert  player  coordinates to map index:

Divide the player's float position by tile size

Ok so I can use the grid cell x and y value?

to get the integer grid cell (map_x, map_y).

Check  the  map  cell:  Look  at map[new_y][new_x].

Condition: If the  value  is  equal  to  '1'  (or  whatever character represents
a  wall  in  your  config),  do  not  update  the  player's position.

2. Adding a Collision Radius (Buffer)

If you check only the exact center point of the player, they might clip slightly
into the corners of walls. To fix this,  add  a  small  safety  buffer  (margin)
around the player's position: • When moving forward/backward or strafing, test a
few offset points around the player (e.g., player_x  +  buffer  and  player_y  +
buffer) against the map array. • If any of those offset points land  on  a  '1',
block the movement for that axis.

NEED TO UPDATE

	- The players position should be a float
	- Need to get my head around the grid cell
	- The map cell


*/
/*
::::::::::::::::::::::::::::		TASK		::::::::::::::::::::::::::::::::

From the information I have collected I should now build the mini  map.  Putting
the player in the correct position and moving the player through  the  map  with
the button press hooks. I can than  also  use  the  feild  of  view  and  player
oreintation vector to draw the feild of view lines  and  the  looking  direction
line. After that I should attempt the DDA Algorithum.

Lets first look through the other example structs for the player  and  check  my
struct is holding all the information needed. Then I should check  that  I  have
parsed all the infromation I need for the player and map. After, draw it out.


::::::::::::::::::::::::::		LEARNING		::::::::::::::::::::::::::::::::


--------------    What is a Vector?		-----------------

For 2D a vector is two numbers. For 3D  it  is  three  numbers  or  more.  These
numbers give you an idea of somethings position in space. For example if we have
a 2D map. We need both the x and y coordinates inorder to understand  the  exact
possition of something. So this is what a "vector is".

The word "vector" in terms of mathamatics was created in th 1840s  by  an  Irish
Mathmatician called William Rowan Hamilton. He gave the word vector the meaning:
A number with 4 parts. So its basicly a number that has 2 or 3 or 4 parts to it.
For example (2, 45) for x and y or (23, 33, 21) for x y and z.


STEPS:

1) Get the player orientation
2) Substract FOV / 2 to player orientation
3) Cast a ray traces it until it hits a wall
4) Record the distance between the player and the wall hit
5) Add angle increment (0.001636 rad) to throw the next ray
6) Repeat from step 3 until ray orientation is player orientation + (FOV / 2)

*/

/*
:::::::::::::::::::::::::::::	CURRENTLY	 :::::::::::::::::::::::::::::::::::

How should I interact with walls? I know the wall is a 1 on the grid. But the thing
that is confusing is that the player position is based on x and y values and the
"grid" or "wall" does not have this?

Create feild  of  view  and ray coming out of the player.

*/

/*
Why is this effecting the players x and y coordinates before a key  is  pressed?
The instance variable seems to interfeer with the position.
*/
/*
Description:
First I create a new image for the player_image variable in the player struct. I
then fill that image with a colour. I then put the player to the window. This is
where there must be a mistake. There must be a problem with the plyaer y  and  x
positions.

Lets have a look and see how these are built.

There must be something wrong with the players x and y. Got it. Found the problem.
The i and j values were being assigned to the opposite x and y postions.

*/
/*
Description:
This function creates a new image that is 33 by 33  for  the  mlx  in  the  game
struct. I then fill this image with the colour green. I thne  loop  through  the
char **grid. If the grid[i][j] == '1' then put the wall  image  to  the  window.
This seems to be rendering everything correctly.
*/
/*
It is to also get comfortable with my grid map and how the map is being built on
the screen. What is happening when a 1 or 0 is found. Also why is the player not
being create in the correct place? Should I move the 'N' (player)  in  the  grid
map aswell? At the moment the player  is  only  moving  by  updating  the  image
instance variables. I need a way to detect  a  wall  so  the  player  cannot  go
through the walls.

When I update the x and y coordinates  of  the  player  I  either  increment  or
de-increment by 5. Is this 5 pixels or 5 cm or something else? How can I check if
the player is hitting a wall or not? Answer: instances are updated with the unit
of pixels. So it moves 5 pixels forward like I expected.

How much can I update the instance befor I have to update the position of the 'N'
in the grid map?


I need to divide by the wall size and then do the check. Also I need  to  change
the variables from ints to floats. This is because when I do the wall check then
I need an exact number to work with. For example when I divide the  new_position
by the wall size I will likley get a float value. e.g. 2,2 ---> 40,40 ---->  40,
45 ----> 2, 2.25.


Before I start moving the player I need to create a boundry so that I dont get a
segfault when trying to use the if statement with my wall check.



*/
/* The maximum x and y values in char **grid
X = 13 and Y = 29 */
/*
How can I do rotation?
Direction can be a vector: x and y components | y = +1, x = 0 | Facing North (straight up)

My player has an x direction and a y direction

at the moment y is 1 and x is 0. So the line should go
straight up. How can I draw this.

I can start at the player position. Then if

Ok I think I understand now. I basicly do I while loop and put a
pixel to the screen.

The putpixel() function looks like this.


mlx_put_pixel(img, x, y, color);

It needs x and y coordinates.

So this is the key part. I can increment or de-increment the x and y coordinates by the
vector x and y values. Pretty cool and simple

*/


/*
I need to be able to draw a line that shoots out in front of the player so I can
see the orientation of the player and when they rotate.

Common Pattern
Create the "new_image"
Fill the new_image;
Put the new_image to the screen

*/
/*
Function Description

I want to move the arrow

- Left -- Look left
- Right -- Look Right

W (forward), A (left), S (back), D (right)

When I press the left key I want the dir_x and dir_y to change.


*/
/*
::::::::::::::::::::::::::		THINKING	   ::::::::::::::::::::::::::::::::::::

The hardest number to find is the exact x and y positions that the mlx_put_pixel()
can use. To find these numbers I have to understand sin and cos. These two maths
functions return the number values I need so that mlx_put_pixel() can accuratly put
the pixel in the correct position and draw the line.

To get the correct value I need to do a calculation.

I need to times the degrees, say 90

Question: Why is any of this triginomitary stuff relevent to me?

I need to draw a line. This is easy. I can just use a while loop like this

while (i < 100)
{
	mlx_put_pixel(mlx, i, j, colour);
	i++;	
}

But if I want to draw a line that is at a certain degree from a single point

I need some x and y coordinates plus an angle?

*//*
	• (X) Coordinate: Radius x cos(Radians)
	• (Y) Coordinate: Radius x sin(Radians)

double degrees = 90.0;
double radius = 10.0; // Distance from the center poin

What is a Radian?

Convert to radians inside the function call: degrees * (PI / 180.0)
double x = radius * cos(degrees * (PI / 180.0));
double y = radius * sin(degrees * (PI / 180.0));


x = radius * cos(radian value);

	 ^^^
  why radius? Ahh yes, the radius is just the distance out that we are going. 
  so in a while loop it usually will be i++. However I could call the variable
  radius++

  so as we increment radius by 1 each time. we also get a new x / y value beacuse
  we times the 1 or 2 or 3 or 4 by the return value of cos() or sin(). 

  The return value of cos() for example gives use the exact coordinate we need. 

  The cos(radian) function returns a value between -1 and 1. 
  The sin(radian) function does the same thing but is specific for the y cooridnates.

Finally this is beggining to click. 

I could make a special function that allowed me to simply pass the degree value I
want instead of having to pass the radian value. So I could do something like this

	 x = degree_cos(90); <--- Would return 0 
	 y = degree_sin(90); <--- Would return 1

	x_coordinate = x * radius;
	y_coordinate = y * radius;

So I should be able to take the return values of these funtions and give them 
to the mlx_put_pixel() function for the x and y coordinates for that specific
pixel and then increment the radius.

Then if I want to change the angle of the line with the arrow keys I shold be able
to increase or reduce the degree angle. Then remember to update the mlx image; 

*/