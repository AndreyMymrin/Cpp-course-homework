#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <thread>
#include <vector>

int global_counter = 0;

bool is_cross(double l, double y, double catet1, double catet2) {
    if (y + catet2/sqrt(pow(catet1,2) + pow(catet2,2))*l/2 >= 1 || y - catet2 / sqrt(pow(catet1, 2) + pow(catet2, 2)) *l/2 <= 0 ||
        y + catet2 / sqrt(pow(catet1, 2) + pow(catet2, 2)) * l / 2 <= 0 || y - catet2 / sqrt(pow(catet1, 2) + pow(catet2, 2)) * l / 2 >= 1) {
        return 1;
    }
    else return 0;
}
void caleculation(int n, double l) {
    static int aaa = time(NULL);
    srand(aaa);
    aaa++;
    int counter = 0;
    for (int i = 0; i < n; i++) {
        double catet1 = rand() / double(RAND_MAX) * 2 - 1;
        double catet2 = rand() / double(RAND_MAX) * 2 - 1;
        double y = rand() / double(RAND_MAX);
        if (pow(catet1, 2) + pow(catet2, 2) <= 1) counter += is_cross(l, y, catet1, catet2);
        else {
            i--;
        }
    }
    global_counter += counter;
    //std::cout << 2 * l / counter * n << '\n';
    
    //return 2 * l / counter * n;
}


int main()
{
    double l = 0.9;
    int n = 10000000;
    int n_thr = std::thread::hardware_concurrency();
    std::cout << "Number of threads: " << n_thr << '\n';
    std::vector<std::thread> vec;
    for (int j = 0; j < n_thr; j++) {
        std::thread th(caleculation, n, l);
        vec.push_back(std::move(th));
    }
    for (std::thread& thr : vec) {
        thr.join();
    }
    std::cout << "Result: " << (2 * l / global_counter * n * n_thr);
}
//Реализуйте алгоритм определения числа пи методом Бюффона.
//Выбирете кол - во бросков иглы, обеспечивающих точность 0.00005.Создайте многопоточную версию.
//Число используемое потоков должно определяться автоматически.