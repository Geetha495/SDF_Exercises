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

#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H

#include <vector>
#include <thread>
#include <functional>
#include <list>
#include <mutex>
#include "thread_safe_q.h"
#include <limits>

using worklistt = thread_safe_worklist_t;
/**
 * @brief empty_queue() function to act as default for std::optional
 * 
 */
void empty_queue()
{
    //    static unsigned i=0;
    //  fmt::print("empty_queue:Job queue was empty {}\n",i++);
}

/**
 * @brief keep_working is a function for the worker threads to 
 * take worklist wl, keep getting the work (std::function<void()>)
 * and execute it, if the worklist is empty it will return {} as 
 * part of std::optional 
 * 
 * @param wl worklist from which the thread will keep retrieving
 * work (std::function<void()>) and execute  
 */
void keep_working(worklistt *wl, bool* flag)
{
    // if(wl->empty())
    //     std::cout<<"empty"<<std::endl;
    while ( ( !(wl->empty()) ) && (*flag) )
    {
        std::optional<std::function<void()>> work = wl->get();
        auto f = work.value_or(empty_queue);
        f();
    }
}

/**
 * @brief thread_pool_t is a thread pool class that creates up to
 * num_threads number of threads and only one threadsafe
 * worklist. Each thread will operate on that worklist.
 * 
 */
class thread_pool_t
{
    unsigned num_threads; // number of threads in the thread pool
    std::vector<std::thread *> workers; // vector that stores pointers to worker threads
    std::vector<worklistt *> worklists; //vector that stores pointers to worklists
    static bool flag; 
    std::mutex m;                       //mutex for thread-safety
    /**
     * @brief Create a worker object if pool is not saturated. No extra worklist
     * is  created.
     * 
     */
    void create_worker()
    {
        flag=true;
        std::lock_guard<std::mutex> guard(m);
        if (workers.size() < num_threads)
        {
            // thread_safe_worklist_t* wl = new thread_safe_worklist_t;
            // worklists.push_back(wl);
            std::thread *t = new std::thread(keep_working, worklists.back(),&flag);
            workers.push_back(t);
        }
    }
    //###########################################

    thread_pool_t(unsigned _nthreads) : num_threads(_nthreads){
        thread_safe_worklist_t* wl = new thread_safe_worklist_t;
        worklists.push_back(wl);
    }; // private constructor

public:   
    static thread_pool_t* getInstance(unsigned _nthreads)
    {
        static thread_pool_t* instance;
        if( instance == nullptr )
        {
            //std::lock_guard<std::mutex> guard(m);
            std::this_thread::sleep_for(std::chrono::seconds(20));
            if(instance == nullptr )
            {
                instance = new thread_pool_t(_nthreads);
                // thread_safe_worklist_t* wl = new thread_safe_worklist_t();
                // worklists.push_back(wl);
            }
    	}  
        return instance;
    }

    //######################################

    int get_workers_size() { return workers.size(); }
   
    void join_threads()
    {
        flag=false;
        for (auto worker : workers)
        {
            worker->join();
        }
        std::cout << "Terminated Gracefully !" << std::endl;
    }
    /**
     * @brief Get the worklist object which has the smallest
     *     number of pending "work" in the list. 
     * 
     * Caution: This is thread-safe. Here, pool is
     * a singleton so that multiple objects are not present.
     * The worklist pointer that gets returned will be the smallest
     * when it was returned (because it's  thread-safe).
     * 
     * @return worklistt* , a pointer to the worklist having "lesser" work 
     */
    worklistt *get_worklist()
    {
        create_worker();
        unsigned min = std::numeric_limits<unsigned>::max();
        unsigned index;
        size_t sz = worklists.size();
        for (unsigned i = 0; i < sz; i++)
        {
            size_t tmpsz = worklists[i]->size();
            if (tmpsz < min)
            {
                min = tmpsz;
                index = i;
            }
        }
        return worklists[index];
    }
};

bool thread_pool_t::flag = true;

#endif
