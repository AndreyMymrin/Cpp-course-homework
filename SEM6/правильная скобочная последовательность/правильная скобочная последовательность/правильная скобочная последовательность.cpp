#include <iostream>
#include <string>
#include <forward_list>

bool is_left(char simbol) {
    if (simbol == '(' || simbol == '[' || simbol == '{')
        return 1;
    else return 0;
}

bool is_bracket(char simbol) {
    if (simbol == '(' || simbol == '[' || simbol == '{' ||
        simbol == ')' || simbol == ']' || simbol == '}')
        return 1;
    else return 0;
}


bool is_pair(char simbol1, char simbol2) {
    if (simbol1 == '(' && simbol2 == ')' ||
        simbol1 == '[' && simbol2 == ']' ||
        simbol1 == '{' && simbol2 == '}' ) return 1;
    else return 0;
}
void print_list(std::forward_list<char> list) {
    std::string str;
    while (!list.empty()) {
        str.insert(str.begin(), list.front());
        list.pop_front();
    }
    std::cout << str <<std::endl;
}
bool is_cbs(std::string str) {
    
    std::forward_list<char> list;
    std::string data;
    for (int i = 0; i < str.length(); i++) {
        if (is_bracket(str[i])) {
            data.push_back(str[i]);
        }
    }
    for (int i = 0; i < data.length(); i++) {
        if (is_left(data[i])) list.push_front(data[i]);
        else {
            if (is_pair(list.front(), data[i])) {
                std::cout << list.front() << ' ' << data[i] << '\n';
                list.pop_front();
            }
            else return 0;
        }
        //print_list(list);
    }
    std::cout << "list:";
    print_list(list);
    return list.empty();
}

int main()
{
    std::string str = "[]({(([]ADADAD))})";
    std::cout << "Answer is : " << is_cbs(str);
    return 1;
}


/*
Правильная скобочная последовательность(ПСП) — символьная последовательность, составленная в алфавите, состоящем из символов, 
сгруппированных в упорядоченные пары(типы скобок, графически обозначаемые "(" и «)», "[" и «]», «/*» и «/» и т.п.), 
удовлетворяющая определённым правилам, обеспечивающим последовательную вложенность подпоследовательности, 
обрамлённых открытой и закрытой скобкой одного типа.
Напишите программу принимающую строку, и проверяющую, является ли она правильной скобочной последовательностью.
Типы скобок : (), {}, [].
*/