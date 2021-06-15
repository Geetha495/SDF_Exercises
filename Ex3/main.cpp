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

#include <fmt/core.h>
#include "thread_pool.h"
#include "thread_safe_q.h"
#include <cstdlib>
#include <chrono>

// create a function to be given to a thread
// as a "work"
void print_sum(int a, int b)
{
    fmt::print("print_sum: {}\n",a+b);

}


//another function to act as "work" to be put in the worklist
//of a worker thread
void print_mul(int a, int b)
{
    fmt::print("print_mul: {}\n",a*b);
}


//array of testcases
constexpr std::pair<int, int> arr[] = {
 {2,3}, {3,4}, {-5, 6}, {9,90}, {-7,-7},
 {0,0}, {-12,-14}, {103,203}
};

int main()
{

    thread_pool_t tp(4); //initialize thread pool

    constexpr size_t arrsz = sizeof(arr)/sizeof(std::pair<int,int>);
    for(unsigned i=0;i<arrsz;i++)
    {
        //push works in a worklist
        tp.get_worklist()->push(print_sum,arr[i].first,arr[i].second);
        //push works in a worklist
        tp.get_worklist()->push(print_mul,arr[i].first,arr[i].second);
    }
    std::this_thread::sleep_for(std::chrono::seconds(20));
    tp.join_threads();
    return EXIT_SUCCESS;
}
