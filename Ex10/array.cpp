#include <iostream>
#include <array>

template <typename T>
class stack_t
{
public:
	virtual void push(T t) = 0;
	virtual void pop() = 0;
	virtual T top() = 0;
};

template <typename T,std::size_t SZ>
class stackAdapter : public stack_t<T>, public std::array<T,SZ>
{
	static int index;
public:
	void push(T t)
	{	
		this->at(index++)=t;
	}
	void pop()
	{
		index--;
	}
	T top()
	{
		return this->at(index-1);
	}
};
template<typename T, std::size_t SZ>
int stackAdapter<T,SZ>::index = 0;

int main()
{
	stack_t<int> *s = new stackAdapter<int,5>;
	for (int i = 1; i <= 5; i++)
	{
		s->push(i);
	}
	for (int i = 1; i <= 5; i++)
	{
		std::cout << s->top() << "  ";
		s->pop();
	}
	std::cout << std::endl;
}
