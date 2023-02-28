#include <chrono>
#include <iostream>
using namespace std::chrono;
template <typename F, typename... Args>
steady_clock::duration Time_counter(F Function, Args... args)
{
    steady_clock::time_point t_start = steady_clock::now();
    Function(args...);
    steady_clock::time_point t_end = steady_clock::now();
    return t_end - t_start;
}


int plus_fn(int a, int b) { return a + b; }
int minus_fn(int a, int b) { return a - b; }
int increment(int& a) { return a++; }

int function(int n) {
    int a = 0;
    for (int i = 0; i < n; i++) {
        a += i;
    }
    return a;
}

int main()
{
    std::cout << duration_cast<microseconds>(Time_counter(plus_fn, 5, 10)).count() << " microseconds\n" << std::endl;

    std::cout << duration_cast<microseconds>(Time_counter(function, 10000)).count() << " microseconds\n";
}