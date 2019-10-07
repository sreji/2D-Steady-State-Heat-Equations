#include "COO2CSR.hpp"
#include "matvecops.hpp"
#include "sparse.hpp"


// This method takes in the rows and columns of the sparse matrix 
// and stores them as class attributes. 
void SparseMatrix::Resize(int nrows, int ncols) { 
	this -> nrows = nrows; 
	this -> ncols = ncols; 
}

// This method takes in the paraements to create a COO matrix and
// places them into vectors that are class attributes. 
void SparseMatrix::AddEntry(int i, int j, double val) { 
	i_idx.push_back(i); 
	j_idx.push_back(j); 
	a.push_back(val); 
}

// This method takes converts a sparse COO matrix to CSR format.
// It calls a function from the COO2CSR file. 
void SparseMatrix::ConvertToCSR() {
	COO2CSR(a, i_idx, j_idx); 
}

// This method uses the class attributes of the sparce matrix and 
// performs matrix vector multiplication given a vector as a 
// parameter. 
std::vector<double> SparseMatrix::MulVec(std::vector<double> &vec) {
	return matvecMulti(vec, i_idx, j_idx, a); 
}