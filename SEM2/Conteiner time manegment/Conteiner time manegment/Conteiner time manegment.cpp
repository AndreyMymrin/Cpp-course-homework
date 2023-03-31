#include <chrono> 
#include <iostream> 

#include <vector> 
#include <array> 
#include <deque> 
#include <list> 
#include <forward_list>
#include <functional>
typedef std::chrono::duration<float> fsec;
using namespace std::chrono;

template <typename F, typename... Args>
float Time_counter(F function, Args... args)
{
    auto t_start = steady_clock::now();
    F(args);
    auto t_end = steady_clock::now();
    return ((fsec)(t_end - t_start)).count();
}

void use_method(std::vector<int> conteiner,int args) {
    conteiner.push_back(args);
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

        std::cout << i << ' ' << 
            Time_counter(use_method, data, 5) << "sec \n";
    }
}


//Используя разработанный хронометр измерьте время рассмотренных на семинаре операций для 5 типов контейнеров, 
//при заполненности 10, 1000, 100000 различных элементов.Составе таблицу.