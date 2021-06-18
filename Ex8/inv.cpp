#include<iostream>
#include<cmath>

#define maxSize 5
class Row  
{
	public :
	float* row ={0};
	unsigned n;
	Row(unsigned _n)
	{
		n=_n;
	}
	
	float& operator[](unsigned j)
	{
		if (j >= n) 
		{
			std::cout << "Matrix index out of bound(row), exiting";
			exit(0);
		}
		return row[j];
	}
};

class Matrix
{	public:
	unsigned  m;
	float mtrx[maxSize][maxSize];
	Row r;

	public :
	Matrix(unsigned _m,unsigned _n)
	{
		m=_m;
		r.n =_n;
	}
	Row& operator[](unsigned i)
	{
		if (i >= m) 
		{
			std::cout << "Matrix index out of bound, exiting";
			exit(0);
		}
		r.row = mtrx[i];
		return r;
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

Matrix submatrix(int i, int j)
{
	Matrix s(m-1,m-1);
	int x,y,c1=0,c2=0;
	for(x=0;x<m;x++)
	{
		c2=0;
		if(x!=i)
		{
			for(y=0;y<m;y++)
			{
				if( y!=j)
				{
					s[c1][c2]=mtrx[x][y];
					c2++;
				}

			}
		c1++;
		}
		
	}
	return s;

}

float det()
{
   int d= 0;
   if (m == 1) {
      return (*this)[0][0];
   }
   if (m == 2) {
      return ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);
   }
   int sign = 1;
   for (int i = 0; i < m; i++) {
      d += sign * (*this)[0][i] * ( (this->submatrix(0,i) ).det());
      sign = -sign;
   }
   return d;
}

int minor(int i,int j)
{
	
	return submatrix(i,j).det();

}

Matrix adj()
{
	Matrix adj(m,m);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			adj[i][j]=pow(-1,i+j)*minor(i,j);
		}
	}
	return adj;
}

	// Matrix operator^(int p)
	// {
	// 	if(p==-1)
	// 	{
	// 		if(m==r.n)
	// 		{
	// 			return inv();
				
	// 		}
	// 		else
	// 		{
	// 			std::cout << "Inverse can't be calculated for non-square matrices, exiting";
	// 			exit(0);
	// 		}
	// 	}
	// }





Matrix inv()
{
	
	float d=this->det();
	if(d!=0)
	{
		Matrix inver(m,m);
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<m;j++)
			{
				inver[i][j]= (this->adj())[i][j]/d;
			}
		}
		(this->adj()).display();
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
	Matrix A(3,3);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cin>>A[i][j];
		}		
	}

	std::cout<<"A: "<<std::endl;
	A.display();

	std::cout<<"det :"<<A.det()<<std::endl;

	std::cout<<"inverse :"<<std::endl;
	(A.inv()).display();

}