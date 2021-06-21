#include<iostream>

class Base
{
	public:
		virtual ~Base()
		{
			std::cout<<"Base class destructor..."<<"\n";
		} // virtual destructor

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
	~Derived() override
	{
		std::cout<<"Derived Destructor..."<<"\n"; //It will be called as base class destructor is  virtual
		delete ptr;
		std::cout<<"memory deleted"<<std::endl; //memory is deleted
	}
};

int main()
{
	Base* base = new Derived();
	delete base;

	return 0;
}