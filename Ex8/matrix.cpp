#include<iostream>
#include<cmath>

#define maxSize 5
template<typename T>
class Row;

template<typename T>
class Matrix
{	
	unsigned  m;
	T mtrx[maxSize][maxSize];
	Row<T> r;

	public :
	Matrix(unsigned _m,unsigned _n)
	{
		m=_m;
		r.n=_n;
	}
	Row<T>& operator[](unsigned i)
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
		if(B.m==m &&   ( (B.r).n == (r.n)) )
		{
			Matrix C(m,r.n);
			for(int i=0;i<m;i++)
			{
				for(int j=0;j<r.n;j++)
				{
					C[i][j]=mtrx[i][j]+B[i][j];
				}
			}
			return C;
		}
		else{
			std::cout << "Matrices can't be added, exiting";
			exit(0);
		}
	}
	Matrix operator-(Matrix B)
	{
		if(B.m==m &&   ( (B.r).n == (r.n)) )
		{
			Matrix C(m,r.n);
			for(int i=0;i<m;i++)
			{
				for(int j=0;j<r.n;j++)
				{
					C[i][j]=mtrx[i][j]-B[i][j];
				}
			}
			return C;
		}
		else{
			std::cout << "Matrices can't be subtracted, exiting";
			exit(0);
		}
	}

	Matrix operator*(Matrix B)
	{
		if(r.n == B.m )
		{
			Matrix C(m,r.n);
			for(int i=0;i<m;i++)
			{
				for(int j=0;j<(B.r).n;j++)
				{
					C[i][j]=0;  
					for(int k=0;k<(B.r).n;k++)    
					{    
						C[i][j]+=mtrx[i][k]*B[k][j];    
					}    
				}
			}
			
			return C;
		}
		else{
			std::cout << "Matrices can't be multiplied, exiting";
			exit(0);
		}
	}

	void display()
	{
		for (int i=0; i<m; i++)
		{
			std::cout<<"\t";
			for (int j=0; j<r.n; j++)
				std::cout << mtrx[i][j] << " ";
			std::cout << std::endl;
		}
	}
};

template<typename T>
class Row  
{
	public :
	T* row ={0};
	unsigned n;
	
	T& operator[](unsigned j)
	{
		if (j >= n) 
		{
			std::cout << "Matrix index out of bound(row), exiting";
			exit(0);
		}
		return row[j];
	}
};

int main()
{
	Matrix<int> A(3,3),B(3,3);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			A[i][j]= 1;
			B[i][j]=1;
		}		
	}

	std::cout<<"A: "<<std::endl;
	A.display();

	std::cout<<"B : "<<std::endl;
	B.display();

	std::cout<<"add : "<<std::endl;
	(A+B).display();

	std::cout<<"subtract : "<<std::endl;
	(A-B).display();

	std::cout<<"multiply : "<<std::endl;
	(A*B).display();

	return 0;

}