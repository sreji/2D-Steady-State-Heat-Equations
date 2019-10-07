#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>
#include <vector> 

#include "CGSolver.hpp"
#include "heat.hpp"
#include "sparse.hpp"

// This method reads in the input file and creates a sparse matrix, A, with the 
// information. It also initializes the b and x vectors. 
int HeatEquation2D::Setup (std::string inputfile) {

	// This reads in the input file and stores the values as variables. The input 
	// file should have a length, a width, the number of intervals (h), the cold air
	// temperature, and the hot fluid temperature. 
	std::ifstream input(inputfile);
	double length, width, h, coldTemp, hotTemp; 
	if (input.is_open()) {
		input >> length >> width >> h; 
		input >> coldTemp >> hotTemp; 
		input.close(); 
	}
	// If the file does not exist, then then system will fail to setup. 
	else {
		return 1; 
	}

	// If either of these variables are zero, then the system will fail to setup
	// fail to setup. 
	if (length == 0 or width == 0 or h == 0) {
		return 1;
	}

	// These values represent the rows, columns, and nodes of the geometry of the  
	// pipe. 
	int numberRows = (int) (width/h) - 1; 
	numberColumns = (int) (length/h); 
	int numberNodes = numberRows * numberColumns; 

	// Initializes nrows and ncols in the sparce.cpp/.hpp files. 
	A.Resize(numberNodes, numberNodes);

	// Initializes the b and x vectors. 
	b.resize(numberNodes, 0.0); 
	x.resize(numberNodes, 1.0);

	// Resizes the cold and hot boundary vectors to fit this particular system.
	// Fills in the hot boundary vector so that we can add it to the solution file
	// in CGSolver.  
	//coldBoundary.resize(numberColumns + 1); 
	hotBoundary.resize(numberColumns + 1, hotTemp);
	coldBoundary.resize(numberColumns+ 1); 	


	// Fills in the A matrix, b vector and a vector of the cold bondaries.
	// It fills in the entries for each node.  
	for (int j = 0; j < numberRows; j++) { 
		for (int i = 0; i < numberColumns; i++) { 

			// For A.AddEntry, the first parameter is always the same value
			// because we want to fill in the same row of the sparse matrix. 
			int currentIndex = i + (numberColumns*j); 

			// Fills in the center entry. 
			A.AddEntry(currentIndex,currentIndex, 4.0); 
			
			// Fills in the left entry. If the point is on the left most side
			// it accounts for that and wraps around the domain. 
			if (i == 0) {
				A.AddEntry(currentIndex, numberColumns*(j+1)-1, -1.0); 
			}
			else {
				A.AddEntry(currentIndex, i +(numberColumns*j)-1, -1.0); 
			}

			// Fills in the right entry. If the point is on the right most side
			// it accounts for that and wraps around the domain. 
			if (i == numberColumns-1) {
				A.AddEntry(currentIndex, numberColumns*j, -1.0); 
			}
			else {
				A.AddEntry(currentIndex, i + (numberColumns * j) + 1, -1.0); 
			}

			// Fills in the bottom entry. If the point is on the bottom row it 
			// accounts for fills in the b vector with the equation for the cool jet. 
			if (j == 0) {
				b[currentIndex] = -1 * coldTemp * (exp (-10 * (pow((i * h) 
					- (length/2),2))) - 2); 
				// This fills in the cold boundary vector so we can add it to the 
				// solution file in CGSolver. 
				coldBoundary[i]= -1 * coldTemp * (exp (-10 * (pow((i * h) 
					- (length/2),2))) - 2);
			}
			else {
				A.AddEntry(currentIndex, i + (numberColumns * (j-1)), -1.0); 
			}

			// Fills in the top entry. If the point is on the top row it accounts for
			// that and fills in the hot boundary vector with the hot boundary.
			if (j == numberRows-1) {
				b[currentIndex] = hotTemp; 
			}
			else {
				A.AddEntry(currentIndex, i + (numberColumns * (j+1)), -1.0); 
			}
		}
	}

	// This fills in the last entry in the cold boundary vector. It is not accounted for
	// in the loop above because this point is ommitted from A. 
	coldBoundary[numberColumns] = -1 * coldTemp * (exp (-10 * (pow((numberColumns * h) 
		- (length/2),2))) - 2);
	
	return 0; 
}

// This method solves the system of equations Ax = b. 
int HeatEquation2D::Solve(std::string soln_prefix) {
	
	// Converts matrix A to CSR from COO. 
	A.ConvertToCSR(); 

	// Uses CGSolver and returns number of iterations if the solution converges or
	// -1 if it does not. Calling CGSolver also outputs the solution files. 
	double tol = 1.e-5; 
	int iterations = CGSolver(A, b, x, tol, soln_prefix, hotBoundary, coldBoundary, numberColumns);

	// If the CGSolver returns -1 then the system failed to be solved. 
	if (iterations == -1) {
		return 1; 
	}
	else {
		std::cout<<"SUCCESS: CG solver converged in " << iterations << " iterations." << std::endl; 
		return 0;
	} 
}