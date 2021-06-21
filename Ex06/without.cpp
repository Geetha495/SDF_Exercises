#include<iostream>

class Base
{
	public:
		~Base()
		{
			std::cout<<"Base class destructor..."<<"\n";
		} //not virtual destructor

};

class Derived:public Base{
int* ptr;
public:
	Derived()
	{
		if(ptr == nullptr)
		{
			ptr = new int;
		}
	}
	~Derived()
	{
		std::cout<<"Derived Destructor..."<<"\n"; //It won't be called as base class destructor is not virtual
		delete ptr;
		std::cout<<"memory deleted"<<std::endl; // memory is not deleted
	}
};

int main()
{
	Base* base = new Derived();//upcasting
	delete base;

	return 0;
}