#ifndef matevecops_HPP
#define matevecops_HPP

#include <vector>

//Takes a in a matrix and a vector as arguments, finds the product between the two and returns
//the solution as a vector. 
std::vector<double> matvecMulti (std::vector<double> & vectorValues, std::vector <int> & rowPointer, 
	std::vector <int> &columnIndex, std::vector<double> &matrixValue); 

//Takes two vectors as arguments, finds the sum between the two and returns the solution as 
//a vector.
std::vector<double> vecvecAdd (std::vector<double> &firstVector, std::vector<double> &secondVector); 

//Takes two vectors as arguments, finds the difference between two and returns the solution
//as a vector.
std::vector<double> vecvecSub (std::vector<double> &firstVector, std::vector<double> &secondVector); 

//Takes in two vectors as arguments, finds the product of them and returns the solution
//as a double.
double vecvecMulti (std::vector<double> &firstVector, std:: vector<double> &secondVector); 

//Takes in a scalar and a vector as arguements, finds the product and returns the solution
//as a vector. 
std::vector<double> vecscalarMulti (double scalarValue, std::vector<double> &vectorValues);

//Takes in a vector as an argument, calculates the 2-norm and returns the solution as 
//a double.
double vecNorm (std:: vector<double> & vectorValues); 

#endif


