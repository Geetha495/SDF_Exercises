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

#ifndef __THREAD_SAFE_Q_H
#define __THREAD_SAFE_Q_H


#include <mutex>
#include <queue>
#include <functional>
#include <utility>
#include <condition_variable>
#include <optional>
#include <thread>
#include <iostream>

/**
 * @brief thread_safe_worklist_t is a thread safe worklist that maintains
 * a vector of "work" (std::function<void ()>). An item is never
 * removed from the worklist, only an index is maintained that points
 * to the next item that should be processed
 * 
 */
class thread_safe_worklist_t
{

std::vector<std::function<void ()>> q; // underlying container for "work"
std::mutex m; //mutex for thread safety
//std::condition_variable cv;
unsigned index=0; //index that points to an item in 'q' that should be processed next

public:
/**
 * @brief This is a variadic template function that takes a function with arbitrary
 * number of arguments and binds all the argument values to convert it to
 * std::function<void ()> ("currying") and then pushes the item in q
 * 
 * @tparam F This is a type for the function  
 * @tparam Args Argument typess to the function
 * @param fun function
 * @param args arguments to the function
 */
template <typename F, typename... Args>
void push(F fun,Args&&... args)
{
    std::lock_guard<std::mutex> guard(m);

    //bind all the arguments that is provided so that we only need to push
    //a function object without any argument in the queue. 
    auto f = std::bind(std::forward<F>(fun),std::forward<Args>(args)...);
    q.emplace_back(std::function<void ()> ([f]{f();}));
    ((std::cout << args << ':'), ...);
    std::cout << std::endl;
   // cv.notify_all();
}


/**
 * @brief tries to retrive a "work" from q. If q is empty at the time of
 * retrieval, returns {} as part of std::optional 
 * 
 * @return std::optional<std::function<void()>> 
 */
std::optional<std::function<void()>> get()
{
    std::lock_guard<std::mutex> guard(m);
 //   std::unique_lock<std::mutex> lk(m);
//    cv.wait(lk,[&,this](){return !this->q.empty();});
  //  std::function<void ()>& elem = q.front();
    if(index < q.size())
    {
        std::cout << "get_id: " << std::this_thread::get_id() << ":" << index << ":" << q.size() << std::endl;
       return q[index++]; 
    }

    return {};

}

/**
 * @brief returns the size of the q at the moment in a thread-safe manner
 * 
 * @return size_t 
 */
size_t size()
{
    std::lock_guard<std::mutex> guard(m);
    return q.size();
}

/**
 * @brief  
 * 
 * @return true if q is empty 
 * @return false if q is NOT empty
 */
bool empty()
{
    std::lock_guard<std::mutex> guard(m);
    return q.empty();
}

    
};

#endif