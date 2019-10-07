#include <vector>
#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>

#include "CGSolver.hpp"
#include "matvecops.hpp"
#include "heat.hpp"
#include "sparse.hpp"
#include <iomanip> 

// This function takes inputs from the heat.cpp file and output solution files and the
// number of iterations, if the solution converges, for the system Ax = b. 
int CGSolver(SparseMatrix A, std::vector<double> &b, std::vector<double> &x, double tol,
	std::string soln_prefix, std::vector<double> hotBoundary, std::vector<double> coldBoundary, 
	int numberColumns) {

	// Finds the initial r for when r = b - Ax. 
	std::vector<double> Ax = A.MulVec(x);
	std::vector<double> r = vecvecSub (b, Ax);

	// Fines the norm of the initial r.
	double initialL2normr  = vecNorm (r);

	std:: vector<double> p = r; 

	// Niter counts the number of interations. Nitermax is set
	// to be the size of the system. 
	int niter = 0; 
	int niterMax = int(b.size()); 

	// This while loop checks for converges and finds that solution.
	while (niter < niterMax) {  
		// Writing solution Files:
		if (niter %10==0) { 
			writeFile(soln_prefix, niter,x,hotBoundary, coldBoundary, numberColumns); 
		}

		niter = niter + 1;
		// Calculates alpha. 
		double numeratorAlpha = vecvecMulti(r, r); 
		std::vector<double> ptransposeAp = A.MulVec(p); 
		double denominatorAlpha = vecvecMulti (p, ptransposeAp); 
		double alpha = numeratorAlpha/denominatorAlpha;

		// Finds the updated new vectors for x and r. 
		std::vector<double> alphap = vecscalarMulti(alpha, p);
		x = vecvecAdd(x, alphap); 
		std::vector<double> alphaAp = vecscalarMulti(alpha, ptransposeAp);
		r = vecvecSub(r, alphaAp); 

		// Checks to see if the covergence criterion is met and ends while
		// loop if it has been met. 
		double newL2normr = vecNorm(r); 
		if (newL2normr/initialL2normr < tol) {
			writeFile(soln_prefix, niter,x,hotBoundary, coldBoundary, numberColumns); 	
			break;
		}

		// Calculates beta and updates the p vector. 
		double numeratorBeta = vecvecMulti(r, r); 
		double beta = numeratorBeta/numeratorAlpha;
		std::vector<double> betap = vecscalarMulti(beta, p);  
		p =  vecvecAdd(r,betap); 
	}

	// If system does not converge. 
	if (niter == niterMax + 1) {
		niter = -1; 
	}

	// Returns number of interations or -1 if it does not converge. 
	return niter; 
}

// This function helps write the output files. 
void writeFile(std::string soln_prefix, int niter, std::vector<double> x,
	std::vector<double> hotBoundary, std::vector<double> coldBoundary, int numberColumns){
	
	// Adds the second set of period boundaries that were not used for the system solution
	// calculations. 
	for (unsigned int i = 0; i < x.size(); i = i + numberColumns + 1) {
		x.insert(x.begin() + i + numberColumns, x[i]);
	}

	// Creates a full solution vector that includes all the unknown variables, and the 
	// isothermal boundaries. 
	std::vector<double> solutionVector; 
	solutionVector.insert(solutionVector.end(), coldBoundary.begin(), coldBoundary.end()); 
	solutionVector.insert(solutionVector.end(), x.begin(), x.end()); 
	solutionVector.insert(solutionVector.end(), hotBoundary.begin(), hotBoundary.end()); 

	// Creates the name of the solution files and outputs the full solution vector to the file.
	std::ostringstream tempName;
	tempName << soln_prefix <<std::setw(3) << std::setfill('0') << niter << ".txt"; 
	std::string fileName = tempName.str(); 
	std::ofstream solutionFile(fileName);
	if(solutionFile.is_open()) {
		for(unsigned int i = 0; i < solutionVector.size(); i++) {
			solutionFile << std::scientific  << std::setprecision(4) << solutionVector[i] << std::endl;
    		}
    	solutionFile.close(); 
	}	
}