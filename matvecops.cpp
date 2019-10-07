#include <cmath> 
#include <vector>

#include "matvecops.hpp"

//Finds the product of a matrix and a vector and stores it in a new vector. 
std::vector<double> matvecMulti (std::vector<double> & vectorValues, std::vector <int> 
	& rowPointer, std::vector <int> &columnIndex, std::vector<double> &matrixValue) {
	std::vector<double> matvecMultiSolution; 
	for (unsigned int i = 0; i < vectorValues.size(); i++) {
		double tempSolution = 0.0; 
		for (int j = rowPointer[i]; j<rowPointer[i+1]; j++) {
			tempSolution += matrixValue[j] * vectorValues[columnIndex[j]]; 
		}
		matvecMultiSolution.push_back(tempSolution); 
	}
	return matvecMultiSolution;
}

//Finds the sum of two vectors and stores it in a new vector. 
std::vector<double> vecvecAdd (std::vector<double> &firstVector, std::vector<double> &secondVector) {
	std::vector<double> vecvecAddSolution; 
	for (unsigned int i = 0; i < firstVector.size(); i++) {
		vecvecAddSolution.push_back(firstVector[i] + secondVector [i]); 
	} 
	return vecvecAddSolution; 
}

//Finds the difference of two vectors and stores it in a new vector. 
std::vector<double> vecvecSub (std::vector<double> &firstVector, std::vector<double> &secondVector) {
	std::vector<double> vecvecSubSolution; 
	for (unsigned int i = 0; i < firstVector.size(); i++) {
		vecvecSubSolution.push_back(firstVector[i] - secondVector [i]); 
	} 
	return vecvecSubSolution; 
}

//Finds the scalar product of two vectors. 
double vecvecMulti (std::vector<double> &firstVector, std:: vector<double> &secondVector) {
	double vecvecMultiSolution = 0.0; 
	for (unsigned int i = 0; i < firstVector.size(); i++) {
		vecvecMultiSolution += firstVector[i] * secondVector[i]; 
	}
	return vecvecMultiSolution; 
}

//Finds the product of a vector and a scalar. 
std::vector<double> vecscalarMulti (double scalarValue, std::vector<double> &vectorValues) {
	std::vector<double>vecScalarSolution;
	for (unsigned int i = 0; i<vectorValues.size(); i++) {
		vecScalarSolution.push_back(scalarValue * vectorValues[i]); 
	}
	return vecScalarSolution; 
}

//Finds the 2-norm of a vector.
double vecNorm (std:: vector<double> & vectorValues) {
	double normValue = 0.0; 
	for (unsigned int i = 0; i < vectorValues.size(); i++) {
		normValue += pow(vectorValues[i], 2); 
	}
	normValue = sqrt(normValue); 
	return normValue; 
}