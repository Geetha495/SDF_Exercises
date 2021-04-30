#include <iostream>

template <typename T> T max(T a, T b) 
{
  return a >= b ? a : b; 
}

template <typename T, typename... Args>//variadic template
 T max(T a,T b, Args... args) 
{
    return max(max(a,b),args...);
}

int main() 
{
  std::cout << max(1, 2, 3,4) << ":" << max(1.2, -2.3, 3.1) << std::endl;
  return 0;
}
