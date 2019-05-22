
#include<iostream>
#include <cstdlib>
#include <cassert>
#include<fstream>
#include<sstream>
using namespace std;
template <class T> class SA;
template <class T> class SM;
template <class T> ostream& operator<<(ostream& os, SA<T> s);
template <class T> ostream& operator<< (ostream& os, SM<T> s);
template < class T > class SM {
private:
	int row_low;
	int row_high;
	int col_low;
	int col_high;
	SA < SA < T > > matrix;
public:

	SM(int rows, int cols) {
		if (rows <= 0 || cols <= 0) {
			cout << "Please enter a valid row and columns size" << endl;
			exit(1);
		}
		row_low = 0;
		row_high = rows - 1;
		col_low = 0;
		col_high = cols - 1;
		matrix = SA < SA < T > >(rows);
		for (int j = 0; j < rows; j++)
			matrix[j] = SA < T >(cols);
	}

	SM() {
	}

	SM(int row_min, int row_max, int col_min, int col_max) {
		if ((row_max - row_min + 1) <= 0) {
			cerr << "constructor error in Matrix bounds definition" << endl;
			exit(1);
		}
		row_low = row_min;
		row_high = row_max;
		col_low = col_min;
		col_high = col_max;
		matrix = SA < SA < T > >(row_min, row_max);
		for (int i = row_min; i <= (row_max); i++)
			matrix[i] = SA < T >(col_min, col_max);
	}

	SM(int square_size) {
		row_low = 0;
		row_high = square_size - 1;
		col_low = 0;
		col_high = square_size - 1;
		matrix = SA < SA < T > >(square_size);
		for (int j = 0; j < square_size; j++)
			matrix[j] = SA < T >(square_size);
	}

	//destructor

	~SM() {
	}

	SA < T > &operator[](int i) {
		if (i < row_low || i > row_high) {
			cout << "index " << i << " out of range in Matrix" << endl;
			exit(1);
		}
		return matrix[i];
	}
	/*Matrix Multiplication*/

	SM < T > operator*(SM & s) {
		if ((col_high - col_low + 1) != (s.row_high - s.row_low + 1)) {
			return 0;
		}
		int rows = (row_high - row_low + 1);
		int cols = (s.col_high - s.col_low + 1);
		SM < int >result(rows, cols);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				result[r][c] = 0;
			}
		}

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				for (int i = 0; i < (s.row_high - s.row_low + 1); i++) {
					result[r][c] += ((*this)[r + row_low][i + col_low]) * (s[i + s.row_low][c + s.col_low]);
				}
			}
		}
		return result;
	}

	int getRows() {
		return row_high - row_low + 1;

	}

	int getCols() {
		return col_high - col_low + 1;

	}

	SA < T >* operator+(int i) {
		return &matrix[i];

	}

	friend ostream& operator<< <T>(ostream& os, SM<T> s);



};

template <class T>

ostream & operator<<(ostream & os, SM < T > s) {

	for (int i = s.row_low; i <= s.row_high; i++) {

		for (int j = s.col_low; j <= s.col_high; j++) {

			os << s.matrix[i][j] << " ";

		}

		os << endl;

	}

	return os;

}



void printMatrix(int **matrix, int rows, int columns)

{

	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < columns; j++) {

			cout << matrix[i][j] << ' ';

		}

		cout << '\n';

	}

}

