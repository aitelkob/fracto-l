
# Fract'ol

This project seeks to create a small fractal exploration program.
The program has 6 different types of fractals, in which some vary with the
mouse. Using the mouse, one can also zoom in and zoom out, change colors, and
reset the fractals to the default values. There's also a play of color to feel
the depth of each fractal.

<table style="width:100%">
  <tr>
    <td><img src="resources/1.png"style="width:100px;height:50px;"></td>
    <td><img src="resources/2.png"style="width:100px;height:50px;"></td>
    <td><img src="resources/3.png"style="width:100px;height:50px;"></td>
  </tr>
<tr>
    <td><img src="resources/4.png"style="width:100px;height:50px;"></td>
    <td><img src="resources/5.png"style="width:100px;height:50px;"></td>
    <td><img src="resources/6.png"style="width:100px;height:50px;"></td>
  </tr>
</table>

## Getting Started

### Compiling

Run the following commands:

* To compile
	- `make`
* To remove objects:
	- `make clean`
* To remove objects and binary file (program):
	- `make fclean`
* To re-compile:
	- `make re`

### Executing

To execute the program:

`./fractol <fractal-number>`

*See usage message to see a list of available fractals*

#### Try it!

Try running the following:

`./fractol mandelbrot`

`./fractol julia`

`./fractol sphere`

## Screenshots

**Usage message and controls:**

<img src="resources/12.png" width="400" />

**Program running:**

<img src="resources/fr.png" width="550" />

<img src="resources/fractol-screenshot03.png" width="550" />

<img src="resources/fractol-screenshot04.png" width="550" />
