#ifndef HEAT_HPP
#define HEAT_HPP

#include <string>
#include <vector>

#include "sparse.hpp"

// This class creates a sparse matrix object using the SparseMatrix
// class. Methods can be called to setup up a system of equations 
// based on a given input file and then to solve the system and print
// out the solution files. 
class HeatEquation2D
{
  private:
    SparseMatrix A;
    std::vector<double> b, x;
    std::vector<double> hotBoundary, coldBoundary;
    int numberColumns;  

  public:
    // Method to setup Ax=b system. The input is a file and it returns 
    // the status of if the system was able to be setup.
    int Setup(std::string inputfile);

    // Method to solve system using CGsolver. It takes in the prefix 
    // of the solution file names and it returns the status of if the 
    // system was able to be solved. 
    int Solve(std::string soln_prefix);
};

#endif /* HEAT_HPP */
