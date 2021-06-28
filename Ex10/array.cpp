/*    Copyright (C) 2021  Saurabh Joshi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <assert.h>
#include <array>
#include <optional>
#include <stdexcept>
#include <iostream>

template <typename T,std::size_t SZ>
class stack_t
{

std::array<T,SZ> arr;
std::size_t index=0;

public:

void push(const T elem) noexcept
{
  arr.at(index)=elem; 
  ++index;
}


std::optional<T> top() const
{
    if(index==0)
    {
        return {};
    }

    auto tmp= arr[index-1];
    return tmp;
}

bool pop()
{
    if(index==0){
        return false;
    }
    index--;
    return true;
}

};
template<typename T,std::size_t SZ>
class array_t
{
	public:
	virtual void push_into_array(T )=0;
	virtual std::optional<T> top_of_array()=0;
	virtual bool pop_an_array()=0;
};

template<typename T,std::size_t SZ>
class array_to_stack_adapter : public array_t<T,SZ> , stack_t<T,SZ>
{
	public:
	void push_into_array(T data)
	{
		this->push(data);
	}
	std::optional<T> top_of_array()
	{
		return this->top();
	}
	bool pop_an_array()
	{
		return this->pop();
	}
};

int main()
{
    array_t<int,5>* arr = new array_to_stack_adapter<int,5>;
    for(int i=1;i<=5;i++)
    {
	    arr->push_into_array(i);
    }
    bool flag=true;
    while(flag)
    {    
	std::cout<<arr->top_of_array().value_or(0)<<" , ";
	flag=arr->pop_an_array();
    }
    std::cout<<std::endl;

    return 0;
}