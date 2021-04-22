# SDF_Exercises

1. Implement max function using variadic template that can take arbitrary number of arguments (which are comparable) and returns the maximum element.

2. Take the [thread_pool](https://github.com/sbjoshi/sanganak-examples/tree/main/cs1023-2021-cpp-examples/thread_pool) example and make it terminate gracefully.

3. Implement a thread_pool with a single queue instead of one queue per thread.

4. Make the thread_pool a singleton

5. Implement a thread_pool with one queue per thread where the thread will terminate if the queue is empty. In this case, the pool need to create another worker thread if there are lesser threads than std::'thread'::hardware_concurrency() .

6. Explore destructors and why they need to be virtual.

7. Explore which operators can not be overloaded.

8. Implement a template class for matrix. Implement operations for addition, inverse, multiplication of matrices etc.

9. Implement an intermediate representation (IR) for an assignment statement. e.g., x=y+z*3+w/q; any such string should be parsed in a composite object asgn_statement_t. This can further have expr_t with subclasses for add_exprt, mul_exprt etc (expression for every kind of operation, both unary and binary , cover 5 operators _, -, /, * and %. Note that at the end (leaves) you will have either a const_t or a variable_t. A const_t will have a value. Implement an interpreter for such a statement which will evaluate the statement in a given context_t where context_t is nothing but a symbol table that maps variables to values. For example, the statement above under the context (y=5,z=10,w=3,q=2) is evaluated to x=36. Use visitor pattern to evaluate the expression. Also use visitor pattern to count the number of constants and variable in a statement.

10. Implement a template adapter class stack which uses (1) an std::list (2) an std::array.

11. Implement a template adapter class multiset which uses std::map. Note that a multiset is a container which can contain multiple elements of the same value e.g., { 3,4,8,7,3,9,7} is a multiset because 3 and 7 appears twice. Implement methods to insert, remove, remove_all so that a new element can be inserted in this multiset, one element of the given value can be removed and all the elements with the given value can be removed. (Hint: have something to maintain duplicity of an element).
