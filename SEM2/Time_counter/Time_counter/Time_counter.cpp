#include <iostream>
#include <chrono>

using namespace std::chrono;
int function(int n);

steady_clock::duration Time_counter(int f(int), int n) {

    steady_clock::time_point t_start = steady_clock::now();
    f(n);
    steady_clock::time_point t_end = steady_clock::now();
    return t_end - t_start;
}

int function(int n) {
    int a = 0;
    for (int i = 0; i < n; i++) {
        a += i;
    }
    //std::cout << a << "\n"; // release works!
    return a;
}

int main()
{
    steady_clock::duration T = Time_counter(function, 1000000);
    
    std::cout << duration_cast<microseconds>(T).count()<<" microseconds";

    //std::cout << T.count();
}