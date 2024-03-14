#pragma once
//2.ADT Matrix – repräsentiert als schwachbesetzte Matrix (sparse) mit Tupeln der Form (Zeile, Spalte, Wert)
// (Wert ≠ 0), wobei die Tupel in lexikographischen Reihenfolge nach (Zeile, Spalte) in einem BST mit einer
// verketteten Repräsentierung auf Arrays gespeichert werden.

#include <vector>

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    struct Tuple {
        int row;
        int column;
        TElem value;
    };

    Tuple* tuples;
    int* left;
    int* right;
    int capacity;
    int size;
    int _nrLines;
    int _nrCols;


public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    Matrix multiply(const Matrix& other) const;

    void resize(int newNrLines, int newNrCols);

	// destructor
	~Matrix();

};
