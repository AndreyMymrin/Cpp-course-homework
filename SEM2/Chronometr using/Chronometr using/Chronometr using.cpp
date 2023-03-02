#include <chrono>
#include <iostream>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>

using namespace std::chrono;
template <typename F, typename... Args>
steady_clock::duration Time_counter(F Function, Args... args)
{
    steady_clock::time_point t_start = steady_clock::now();
    Function(args...);
    steady_clock::time_point t_end = steady_clock::now();
    return t_end - t_start;
}
int main()
{
    srand(time(0));
    int a[] = { 10, 1000, 100000 };
    for (int i : a) {
        std::vector<int> data;
        for (int j = 0; j < i; j++) {
            data.push_back(rand() % 100);
        }
        std::cout << i << ' ' << duration_cast<microseconds>(Time_counter(std::vector<int>::push_back, 5)).count() << " microseconds\n";
}


//Используя разработанный хронометр измерьте время рассмотренных на семинаре операций для 5 типов контейнеров,
//при заполненности 10, 1000, 100000 различных элементов.Составе таблицу.