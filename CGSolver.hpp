#ifndef CGSOLVER_HPP
#define CGSOLVER_HPP

#include <vector>
#include <string>

#include "heat.hpp"
#include "sparse.hpp"

// Function that implements the CG algorithm for a linear system Ax = b,
// where A is in CSR format.  The starting guess for the solution is provided 
// in x, and the solver runs a maximum number of iterations equal to the size 
// of the linear system.  Function returns the number of iterations to converge 
// the solution to the specified tolerance, or -1 if the solver did not converge. 
int CGSolver(SparseMatrix A,
             std::vector<double> &b,
             std::vector<double> &x,
             double tol, std::string soln_prefix,std::vector<double> hotBoundary, 
             std::vector<double> coldBoundary, int numberColumns);

// This function is called by the CGSolver function and allows it to write solution files
// and output them. 
void writeFile(std::string soln_prefix, int niter, std::vector<double> x,
	std::vector<double> hotBoundary, std::vector<double> coldBoundary, int numberColumns);

#endif /* CGSOLVER_HPP */
