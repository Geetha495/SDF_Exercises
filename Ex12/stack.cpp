#include <iostream>
#include <stack>

template <typename T>
class queue_t
{
public:
	virtual void enqueue(T t) = 0;
	virtual void dequeue() = 0;
	virtual T head() = 0;
};

template <typename T>
class queueAdapter : public queue_t<T>
{
	std::stack<T> s1,s2;

public:
	void enqueue(T t)
	{
		while(!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
		s1.push(t);
		while(!s2.empty())
		{
			s1.push(s2.top());
			s2.pop();
		}
		
	}
	void dequeue()
	{
		if (s1.empty()) 
		{
			std::cout << "Queue is Empty";
			exit(0);
        	}
		s1.pop();
	}
	T head()
	{
		return s1.top();
	}
};

int main()
{
	queue_t<int> *q = new queueAdapter<int>;
	for (int i = 1; i <= 5; i++)
	{
		q->enqueue(i);
	}
	for (int i = 1; i <= 5; i++)
	{
		std::cout << q->head() << "  ";
		q->dequeue();
	}
	std::cout << std::endl;
}
