#include <iostream>
#include <cmath>

#define maxSize 5

template <typename T>
class Row
{
public:
	T *row = {0};
	unsigned n;

	T &operator[](unsigned j)
	{
		if (j >= n)
		{
			std::cout << "Matrix index out of bound(row), exiting";
			exit(0);
		}
		return row[j];
	}
};

template <typename T>
class Matrix
{
	unsigned m;
	T mtrx[maxSize][maxSize];
	Row<T> r;

public:
	Matrix(unsigned _m, unsigned _n)
	{
		m = _m;
		r.n = _n;
	}
	Row<T> &operator[](unsigned i)
	{
		if (i >= m)
		{
			std::cout << "Matrix index out of bound, exiting";
			exit(0);
		}
		r.row = mtrx[i];
		return r;
	}
	Matrix operator+(Matrix B)
	{
		if (B.m == m && ((B.r).n == (r.n)))
		{
			Matrix C(m, r.n);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < r.n; j++)
				{
					C[i][j] = mtrx[i][j] + B[i][j];
				}
			}
			return C;
		}
		else
		{
			std::cout << "Matrices can't be added, exiting";
			exit(0);
		}
	}
	Matrix operator-(Matrix B)
	{
		if (B.m == m && ((B.r).n == (r.n)))
		{
			Matrix C(m, r.n);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < r.n; j++)
				{
					C[i][j] = mtrx[i][j] - B[i][j];
				}
			}
			return C;
		}
		else
		{
			std::cout << "Matrices can't be subtracted, exiting";
			exit(0);
		}
	}

	Matrix operator*(Matrix B)
	{
		if (r.n == B.m)
		{
			Matrix C(m, r.n);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < (B.r).n; j++)
				{
					C[i][j] = 0;
					for (int k = 0; k < (B.r).n; k++)
					{
						C[i][j] += mtrx[i][k] * B[k][j];
					}
				}
			}

			return C;
		}
		else
		{
			std::cout << "Matrices can't be multiplied, exiting";
			exit(0);
		}
	}

	Matrix<float> operator^(int n)
	{
		if (n == -1)
		{
			return this->inv();
		}
	}

	void display()
	{
		for (int i = 0; i < m; i++)
		{
			std::cout << "\t";
			for (int j = 0; j < r.n; j++)
				std::cout << mtrx[i][j] << "\t";
			std::cout << std::endl;
		}
	}

	Matrix submatrix(int i, int j)
	{
		Matrix s(m - 1, m - 1);
		int x, y, c1 = 0, c2 = 0;
		for (x = 0; x < m; x++)
		{
			c2 = 0;
			if (x != i)
			{
				for (y = 0; y < m; y++)
				{
					if (y != j)
					{
						s[c1][c2] = mtrx[x][y];
						c2++;
					}
				}
				c1++;
			}
		}
		return s;
	}

	T det()
	{
		int d = 0;
		if (m == 1)
		{
			return (*this)[0][0];
		}
		if (m == 2)
		{
			return ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);
		}
		int sign = 1;
		for (int i = 0; i < m; i++)
		{
			d += sign * (*this)[0][i] * ((this->submatrix(0, i)).det());
			sign = -sign;
		}
		return d;
	}

	T minor(int i, int j)
	{
		return submatrix(i, j).det();
	}

	Matrix transpose()
	{
		Matrix Trnspse(r.n, m);
		for (int i = 0; i < r.n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				Trnspse[i][j] = (*this)[j][i];
			}
		}
		return Trnspse;
	}

	Matrix adj()
	{
		Matrix cofactor(m, m);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cofactor[i][j] = pow(-1, i + j) * minor(i, j);
			}
		}
		Matrix adj(m, m);
		adj = cofactor.transpose();
		return adj;
	}

	Matrix<float> inv()
	{
		float d = this->det();
		if (d != 0)
		{
			Matrix<float> inver(m, m);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < m; j++)
				{
					inver[i][j] = (this->adj())[i][j] / d;
				}
			}
			//(this->adj()).display();
			return inver;
		}
		else
		{
			std::cout << "Inverse does not exists, exiting";
			exit(0);
		}
	}
};

int main()
{
	Matrix<int> A(3, 3), B(3, 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			A[i][j] = 1;
			B[i][j] = 1;
		}
	}

	std::cout << "A: " << std::endl;
	A.display();

	std::cout << "B : " << std::endl;
	B.display();

	std::cout << "add : " << std::endl;
	(A + B).display();

	std::cout << "subtract : " << std::endl;
	(A - B).display();

	std::cout << "multiply : " << std::endl;
	(A * B).display();

	Matrix<int> C(3,3);
	std::cout<<"enter elements of a 3*3 mtrix to find inverse :\n";
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cin>>C[i][j];
		}		
	}

	std::cout<<"C: "<<std::endl;
	C.display();

	std::cout<<"inverse :"<<std::endl;
	(C^(-1)).display();

	return 0;
}
