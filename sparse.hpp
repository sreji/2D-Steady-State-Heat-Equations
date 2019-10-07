#ifndef SPARSE_HPP
#define SPARSE_HPP

#include <vector>

// This class creates a sparse matrix object and uses methods to perform 
// operations on the matrix. 
class SparseMatrix
{
  private:

    // These are the private attributes that define the
    // sparse matrix. 
    std::vector<int> i_idx;
    std::vector<int> j_idx;
    std::vector<double> a;
    int ncols;
    int nrows;

  public:
    // Method to modify sparse matrix dimensions. The inputs
    // are the number of rows and number of columns in the matrix.
    void Resize(int nrows, int ncols);

    // Method to add entry to matrix in COO format. The inputs 
    // are the row position, the column position, and the value.
    void AddEntry(int i, int j, double val);

    // Method to convert COO matrix to CSR format using provided function. 
    void ConvertToCSR();

    // Method to perform sparse matrix vector multiplication using CSR formatted matrix. 
    // The input is the vector that is to be multiplied. 
    std::vector<double> MulVec(std::vector<double> &vec);
};

#endif // SPARSE_HPP  
