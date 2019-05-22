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


