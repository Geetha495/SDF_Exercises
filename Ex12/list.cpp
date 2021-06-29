#include <iostream>
#include <list>

template <typename T>
class queue_t
{
public:
	virtual void enqueue(T t) = 0;
	virtual void dequeue() = 0;
	virtual T head() = 0;
};

template <typename T>
class queueAdapter : public queue_t<T>, public std::list<T>
{
	static int index;

public:
	void enqueue(T t)
	{
		this->push_back(t);
	}
	void dequeue()
	{
		this->pop_front();
	}
	T head()
	{
		return this->front();
	}
};
template <typename T>
int queueAdapter<T>::index = 0;

int main()
{
	queue_t<int> *s = new queueAdapter<int>;
	for (int i = 1; i <= 5; i++)
	{
		s->enqueue(i);
	}
	for (int i = 1; i <= 5; i++)
	{
		std::cout << s->head() << "  ";
		s->dequeue();
	}
	std::cout << std::endl;
}
