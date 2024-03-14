#include "Matrix.h"
#include <exception>

using namespace std;

/*
 * WC: Theta(n)
 * BC: Theta(n)
 * Avg: Theta(n)
 */
Matrix::Matrix(int nrLines, int nrCols) {
    _nrLines = nrLines;
    _nrCols = nrCols;
    capacity = 5;
    size = 0;

    tuples = new Tuple[capacity];
    left = new int[capacity];
    right = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        left[i] = -1;
        right[i] = -1;
    }
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
int Matrix::nrLines() const {
    return _nrLines;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
int Matrix::nrColumns() const {
    return _nrCols;
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(logn)
 */
TElem Matrix::element(int i, int j) const {
    if (i < 0 || j < 0 || i > _nrLines || j > _nrCols)
        throw exception();
    for (int k = 0; k < size; k++) {
        if (tuples[k].row == i && tuples[k].column == j) {
            return tuples[k].value;
        }
    }
    return NULL_TELEM;
}

/*
 * WC: Theta(n^2)
 * BC: Theta(1)
 * Avg: Theta(n^2)
*/
TElem Matrix::modify(int i, int j, TElem e) {
    if (size == capacity)
        resize(_nrLines * 2, _nrCols * 2);
    if (i < 0 || j < 0 || i >= _nrLines || j >= _nrCols)
        throw std::exception();

    // Search for existing tuple with matching row and column values
    for (int k = 0; k < size; k++) {
        if (tuples[k].row == i && tuples[k].column == j) {
            // Check if the new value is 0
            if (e == 0) {
                // Shift elements to the left to remove the tuple
                for (int m = k; m < size - 1; m++) {
                    tuples[m] = tuples[m + 1];
                }

                // Update BST pointers (left and right arrays) for the shifted elements
                for (int n = 0; n < size; n++) {
                    if (left[n] > k) {
                        left[n]--;
                    }
                    if (right[n] > k) {
                        right[n]--;
                    }
                }

                size--;

                return NULL_TELEM;
            } else {
                // Update the value of the existing tuple
                TElem previousValue = tuples[k].value;
                tuples[k].value = e;
                return previousValue;
            }
        }
    }

    // Add new tuple if the value is not 0
    if (e != 0) {
        // Add new tuple at the end
        tuples[size].row = i;
        tuples[size].column = j;
        tuples[size].value = e;

        // Update BST pointers (left and right arrays)
        left[size] = size - 1;
        right[size] = -1;

        // Increase size of the matrix
        size++;
    }

    return NULL_TELEM;
}


/*
 * WC: Theta(n^3)
 * BC: Theta(n^3)
 * Avg: Theta(n^3)
 */
Matrix Matrix::multiply(const Matrix &other) const {
    if (_nrCols != other._nrLines) {
        throw exception();
    }

    int resultRows = _nrLines;
    int resultCols = other._nrCols;
    Matrix result(resultRows, resultCols);

    //parcurgem ficare pozitie
    for (int i = 0; i < resultRows; i++) {
        for (int j = 0; j < resultCols; j++) {
            TElem value = 0;

            //calculam valoarea elemenntului
            for (int k = 0; k < _nrCols; k++) {
                TElem value1 = element(i, k);
                TElem value2 = element(k, j);
                value = value + (value1 * value2);
            }
            result.modify(i, j, value);
        }
    }
    return result;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
Matrix::~Matrix() {
    delete[] tuples;
    delete[] left;
    delete[] right;
}

void Matrix::resize(int newNrLines, int newNrCols) {
    Matrix resizedMatrix(newNrLines, newNrCols);

    for (int i = 0; i < size; i++) {
        int row = tuples[i].row;
        int column = tuples[i].column;
        TElem value = tuples[i].value;

        if (row < newNrLines && column < newNrCols) {
            resizedMatrix.modify(row, column, value);
        }
    }
    *this = resizedMatrix;

}

