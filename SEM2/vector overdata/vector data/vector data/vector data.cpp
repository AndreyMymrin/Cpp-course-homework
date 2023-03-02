#include <iostream>
#include <vector>
int main()
{
    std::vector<int> v = { 1 };
    std::cout << v.size() << ' ' << v.capacity() << '\n';
    for (int i = 0; i < 10000000; i++) {
        int prev_capacity = v.capacity();
        v.push_back(i);
        if (v.capacity() != prev_capacity) std::cout << '\n' << v.size() << ' ' << v.capacity() << ' ' << (float)v.capacity() / prev_capacity << '\n';
    }

}

//Определите, во сколько раз расширяется пространство выделяемое под std::vector при нехватке памяти.

/*
Ответ: увеличивается в 1.5 раза
*/