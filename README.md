# SDF_Exercises

[1](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex01).    Implement max function using variadic template that can take arbitrary number of arguments (which are comparable) and returns the maximum element.

[2](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex02). Take the [thread_pool](https://github.com/sbjoshi/sanganak-examples/tree/main/cs1023-2021-cpp-examples/thread_pool) example and make it terminate gracefully.

[3](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex03). Implement a [thread_pool](https://github.com/sbjoshi/sanganak-examples/tree/main/cs1023-2021-cpp-examples/thread_pool) with a single queue instead of one queue per thread.

[4](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex04). Make the [thread_pool](https://github.com/sbjoshi/sanganak-examples/tree/main/cs1023-2021-cpp-examples/thread_pool) a singleton

5. Implement a thread_pool with one queue per thread where the thread will terminate if the queue is empty. In this case, the pool need to create another worker thread if there are lesser threads than std::'thread'::hardware_concurrency() .

[6](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex06). Explore destructors and why they need to be virtual.

[7](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex07). Explore which operators can not be overloaded.

[8](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex08). Implement a template class for matrix. Implement operations for addition, inverse, multiplication of matrices etc.

[9](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex09). Implement an intermediate representation (IR) for an assignment statement. e.g., x=y+z*3+w/q; any such string should be parsed in a composite object asgn_statement_t. This can further have expr_t with subclasses for add_exprt, mul_exprt etc (expression for every kind of operation, both unary and binary , cover 5 operators _, -, /, * and %. Note that at the end (leaves) you will have either a const_t or a variable_t. A const_t will have a value. Implement an interpreter for such a statement which will evaluate the statement in a given context_t where context_t is nothing but a symbol table that maps variables to values. For example, the statement above under the context (y=5,z=10,w=3,q=2) is evaluated to x=36. Use visitor pattern to evaluate the expression. Also use visitor pattern to count the number of constants and variable in a statement.

[10](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex10). Implement a template adapter class stack which uses [(1)](https://github.com/Geetha495/SDF_Exercises/blob/main/Ex10/list.cpp) an std::list [(2)](https://github.com/Geetha495/SDF_Exercises/blob/main/Ex10/array.cpp) an std::array.

[11](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex11). Implement a template adapter class multiset which uses std::map. Note that a multiset is a container which can contain multiple elements of the same value e.g., { 3,4,8,7,3,9,7} is a multiset because 3 and 7 appears twice. Implement methods to insert, remove, remove_all so that a new element can be inserted in this multiset, one element of the given value can be removed and all the elements with the given value can be removed. (Hint: have something to maintain duplicity of an element).

[12](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex12). Implement a template adapter class queue_t using [two std::stack](https://github.com/Geetha495/SDF_Exercises/blob/main/Ex12/stack.cpp), [list](https://github.com/Geetha495/SDF_Exercises/blob/main/Ex12/list.cpp). This class should allow enqueue and deque operation. enqueue adds an element to the queue and dequeue removes the element which was the oldest element from the queue. Unlike stack this is a FIFO (First-in-First-Out) interface. If you need implement a head operation which returns the element at the head of the queue (oldest element).

[13](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex13). Implement a reverse iterator on the list that was given in the class. Implement rbegin() and rend() method and then the reverse iterator would go back in the list when you do ++. You need to have a pointer to previous listnode_t as well for this case.

[14](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex14). Implement an iterator in the list (defined in the class and available in the repo) which only goes through element at even position in the list.

[15](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex15). Define a class readert which keeps getting a string from a user and then send it to all its observers. Implement an observer which just prints this string, another observer which prints the frequency of every alphabet inside the string (a: 4, b:5, c:6 indicating 'a' appeared 4 times in the string etc), another observer that takes the string writes it to a file. (a) Implement all the classes in a thread-safe manner (b) use subscribe and unsubscribe method and random times and see how the behaviour changes.

[16](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex16). Think of cases where the update() on the observer is computationally very heavy. Implement an event manager that shields the subject from the runtime of the update() of the observer. Think of scenario with multiple subjects and observers where event manager can be really useful.

17. Implement various sorting algorithms (insertion sort, quick sort, merge sort) as a strategy and ask a user to choose at run-time which of these to use for sorting. (DO NOT use sort available in the standard library)

18. Implement a linear search and a binary search algorithm on an array/vector as strategies. (DO NOT use search available in standard library)

[19](https://github.com/Geetha495/SDF_Exercises/tree/main/Ex19). Regarding visitor pattern discussed in the class. The exercise below are in no particular order and one can do mix and match:
  - [=>](https://github.com/Geetha495/SDF_Exercises/blob/main/Ex19/a.cpp) Fix the parsing and/or evaluation so that the answer expected for (3+4-5+6-7) = 1
  - Make the example generic (either by making use of any generic or using templates for const_exprt) for taking different kinds of constants
  - Enrich the input language by supporting other binary operators (mul_exprt, div_exprt, rem_exprt, shr_exprt (>>), shl_exprt(<<) etc)
  - Add var_exprt with type info and separately implement contextt or symbol_tablet that can provide a value for variable
  - [=>](https://github.com/Geetha495/SDF_Exercises/blob/main/Ex19/e.cpp) Remove the need for dynamic_cast by augmenting interface of visitort for all expressions.

20. The iterator defined for the tree at (https://github.com/sbjoshi/sanganak-examples/blob/main/cs1023-2021-cpp-examples/iterator/btree.cpp (Links to an external site.)). Make the iterator compatible with standard template library so that one can use algorithms that use ForwardIterator such as (count/count_if, copy, transform etc)
