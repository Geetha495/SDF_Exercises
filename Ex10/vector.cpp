
#include <iostream>
#include <vector>

template <typename T>
class stack_t
{
public:
	virtual void push(T t) = 0;
	virtual void pop() = 0;
	virtual T top() = 0;
};

template <typename T>
class stackAdapter : public stack_t<T>, public std::vector<T>
{

public:
	void push(T t)
	{
		this->push_back(t);
	}
	void pop()
	{
		this->pop_back();
	}
	T top()
	{
		return this->back();
	}
};

int main()
{
	stack_t<int> *s = new stackAdapter<int>;
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
