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

#include "mylist.h"
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>

//typename iterator_traits<InputIterator>::difference_type
template <class InputIterator, class UnaryPredicate>
int my_count_if(InputIterator first, InputIterator last, UnaryPredicate pred)
{
  int count=0;
  while (first!=last) {
    if (pred(*first)) ++count;
    ++first;
  }
  return count;
}

int main()
{

    int arr[] = {4,32,54,-9,0,0,3,2,-90,123123,-451212};
    constexpr size_t asize=sizeof(arr)/sizeof(int);
    mylist_t<int> l;
    for(unsigned i=0;i<asize;i++)
    {
            l.push_front(arr[i]);

    }
    std::cout << "pushed" << std::endl;
    std::cout << "size of list is " << l.size() << std::endl;
    auto foo = [](const auto& x){return x;};
    std::cout << my_count_if(l.begin(),l.end(),foo) << std::endl;
    return EXIT_SUCCESS;
}

