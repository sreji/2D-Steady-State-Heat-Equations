# Solving 2D Steady State Heat Equations
 
## Introduction

  The goal of this project was to solve the 2D steady-state heat equation using a sparse Conjugate Gradient solver.
In the first part of the project I created a CG solver that took in the system of equations produced by Ax = b and found 
the solution x given an initial guess. Then in part two, I used that solver to find the mean temperature within a pipe where 
hot fluid was being transferred and where cold air jets were being distributed along the pipe. This was done by discretizing 
the pipe wall and forming the system of equations of the  form using the boundary conditions provided. I then plotted the
distribution of temperatures on a pseudocolor plot and plotted the mean temperature isoline to visual the problem.

## Implementation of CGSolver

  In order to use my CGSolver, I need to first set up a matrix, A. This was done by using two classes- SparseMatrix
and HeatEquation2D. The SparseMatrix class has four methods to help set up a matrix object. It has a method
to initialize the size of the matrix, a method to add entries of the matrix in COO form, a method to convert the matrix to CSR
form and a method to multiply the matrix with a vector. Creating a SparseMatrix object allows easier implementation of 
the CGSolver since I can just pass in the object into the function instead of separate vectors in CSR format.

  The HeatEquation2D class has two methods, one to setup the system of equations and one to solve them. In the Setup
method an input file with the length, width, h, hot temperature and cold temperature are read in and then the four methods 
within SparseMatrix are called in order to set up the matrix A. A is set up based on the discrete form of the steady state heat equation. The Setup method also creates the b and x vectors. The second method in HeatEquation2D takes the SpareMatrix
object created in Setup, converts it to CSR, and passes it to CGSolver. 

  The output of the CGSolver is the number of iterations it takes for the system to converge to the solution. If the system 
does not converge, -1 is returned. Throughout my CGSolver algorithm I had many of the same operations between matrices 
and vectors. So to eliminate redundancy I created a matvecops file with six different functions.

  Inside CGSolver there is also a function that writes the solution vector, in conjunction with the isothermal boundaries to a file. The CGSolves calls it for every 10 iterations, including the first and last one.
  
  The first function in my matvecops files takes a matrix and vector and multiplies them together. The second and 
third both take two vectors and find the sum and the difference respectively. My fourth finds the dot product of two vectors. 
The fifth ones takes a scalar and a vector and returns the product. The last function finds the 2-norm of a vector. Every 
time one of these operations came up in the CGSolver, I would call the function from the matvecops file instead of rewriting 
it in the CGSolver. 

  Breaking up the project into these different functions and classes make it easier to solve the system of equations using 
the CGSolver. Using multiple files also creates less room for error occur while setting up the system of equations and solving
it. 

 The bonus.py file creates an animation of all the solution files for a particular input.

## Compiling and Running
  To use the code, you need to create a main program that calls in the HeatEquation2D class. First create an constructor of 
the class in main.cpp. Then you need a file with the length, width, h, hot temperature, and cold temperature values. This file is used to call the Setup method. Then the Solve method is called on your constructor using the prefix for the solution files that you want outputted. The code is them complied using the provided  makefile. The makefile included the variable for the c++ complier, g++. It also includes the flags for the warnings we want to be raised. For this project, we are concerned about -Wall, -Wextra, and -Wconversion warnings. Our makefile also links all of the programs that have functions that we want run. It links the CGSolver, COO2CSR, matevecops, sparse, and heat files, which are all dependencies, to the main executable. 

  With all of the files and makefile in the same directory, you can compile the code by calling make. Then to run the code we use " ./main $<$input file$>$ $<$solution prefix$>$ ". 
  
 To run the post processing python file, we need to use "python3 postprocess.py $<$input file$>$ $<$solution file$>$ ". 
  
  Finally to visualize our results, the python program outputs a pseudo color plot of the temperature distribution and the mean temperature isoline. The following is a sample result given input2 and solution157 as the inputs to the program.
  
 ![alt text](https://github.com/sreji/2D-Steady-State-Heat-Equations/blob/master/image1.png) 


To run the bonus.py, an input file and a folder with all of the solution files for that input need to be passed as parameters.
We use "  python3 bonus.py $<$input file$>$ $<$solution files folder$>$ ". In order for this code to run, the ffmpeg package needs to be installed to save a mp4. 

 The next three images show the progression of the animation for input2. 

 ![alt text](https://github.com/sreji/2D-Steady-State-Heat-Equations/blob/master/image2.png) 
 
 ![alt text](https://github.com/sreji/2D-Steady-State-Heat-Equations/blob/master/image3.png) 
 
 ![alt text](https://github.com/sreji/2D-Steady-State-Heat-Equations/blob/master/image4.png) 
   
 
