#include<iostream>
#include <cstdlib>
#include <cassert>
#include<fstream>
#include<sstream>
using namespace std;

/*Generic Safe Array Class*/
template <class T> class SA;
template <class T> class SM;
template <class T> ostream& operator<<(ostream& os, SA<T> s);
template <class T> ostream& operator<< (ostream& os, SM<T> s);

template < class T > class SA {
private:
	int low, high;
	T *p;

public:

	SA() {
		low = 0;
		high = -1;
		p = NULL;

	}

	SA(int l, int h) {
		if ((h - l + 1) <= 0) {
			cout << "constructor bounds error" << endl;
			exit(1);
		}
		low = l;
		high = h;
		p = new T[h - l + 1];
	}

	SA(int i) {
		low = 0;
		high = i - 1;
		p = new T[i];
	}

	SA(const SA & s) {
		int size = s.high - s.low + 1;
		p = new T[size];
		for (int i = 0; i < size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
	}

	~SA() {
		delete[]p;
	}

	T & operator[](int i) {
		if (i < low || i > high) {
			cout << "index " << i << " out of range" << endl;
			exit(1);
		}
		return p[i - low];
	}

	SA & operator=(const SA & s) {
		if (this == &s)
			return *this;
		delete[]p;
		int size = s.high - s.low + 1;
		p = new T[size];
		for (int i = 0; i < size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
		return *this;
	}

	int* operator+(int i) {
		return &p[low + i];
	}

	friend ostream& operator<< <T> (ostream& os, SA<T> s);

};



template <class T> ostream & operator<<(ostream & os, SA < T > s) {
	int size = s.high - s.low + 1;
	for (int i = 0; i < size; i++)
		os << s.p[i] << endl;
	return os;
}



/*Safe array within safe array*/



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

	//friend ostream& operator<<(ostream& os, SM<T> s);



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


int main() {
	

	SM<int> a(3, 4); // (int x, int d);
	SM<int> b(3, 4); // (int x, int d);
	SM<int> c; 

	b[1][2] = 35;
	a[2][3] = 3;
	std::cout << a[2][3] << std::endl;
	a[1][1] = a[2][3] * b[1][2]; // 38

	std::cout << a[1][1];


	 
	std::cin.get();
}