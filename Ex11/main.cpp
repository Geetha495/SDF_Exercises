#include <iostream>
#include <map>

template <typename T>
class multiset_t
{
public:
	virtual void insert(T t) = 0;
	virtual void remove(T t) = 0;
	virtual void remove_all(T t) = 0;
	virtual void print()=0;
};

template <typename T>
class multisetAdapter : public multiset_t<T>, public std::map<T,T>
{
	static int index;
public:
	void insert(T t)
	{
		if(!(*this)[t])
		{
			++index;
			this->std::map<T,T>::insert(std::pair<T,T>(t,0));
			(*this)[t]=1;
		}
		else
		{
			(*this)[t]++;
		}
	}
	void remove(T t)
	{
		if((*this)[t]>1)
		{
			(*this)[t]--;
		}
		else if((*this)[t]==1)
		{
			this->erase(t);
		}
	}
	void remove_all(T t)
	{
		if((*this)[t])
		{
			this->erase(t);
		}
	}

	void print()
	{
		for(auto& x : *this)
		{
			for(int i=0;i<x.second;i++)
			{
				std::cout<<x.first<<" ";
			}
		}
	}


};
template<typename T>
int multisetAdapter<T>::index =-1;

int main()
{
	multiset_t<int> *m = new multisetAdapter<int>;
	for (int i = 1; i <= 5; i++)
	{
		m->insert(i);
		m->insert(i+2);
	}
	std::cout<<"before :";
	m->print();
	m->remove(4);
	std::cout << std::endl;
	std::cout<<"after removing 4 :";
	m->print();
	m->remove_all(5);
	std::cout << std::endl;
	std::cout<<"after removing all 5 :";
	m->print();

	
	std::cout << std::endl;
}
