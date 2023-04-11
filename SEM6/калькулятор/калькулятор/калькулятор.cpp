#include <iostream>
#include <string>
#include <vector>
#include <forward_list>
void print_list(std::forward_list<char> list) {
    std::string str;
    while (!list.empty()) {
        str.insert(str.begin(), list.front());
        list.pop_front();
    }
    std::cout << str << std::endl;
}

bool is_number(char simbol) {
    if (simbol == '0' || simbol == '1' || simbol == '2' || simbol == '3' || simbol == '4' || simbol == '5' ||
        simbol == '6' || simbol == '7' || simbol == '8' || simbol == '9')
        return 1;
    else return 0;
}
bool is_action(char simbol) {
    if (simbol == '+' || simbol == '-' || simbol == '*' || simbol == '/' || simbol == '%' || simbol == '^') {
        return 1;
    }
    else return 0;
}
bool is_important_action(char simbol) {
    if (simbol == '*' || simbol == '/' || simbol == '%' || simbol == '^') {
        return 1;
    }
    else return 0;
}

bool is_left(char simbol) {
    if (simbol == '(' || simbol == '[' || simbol == '{')
        return 1;
    else return 0;
}
bool is_right(char simbol) {
    if (simbol == ')' || simbol == ']' || simbol == '}')
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
        simbol1 == '{' && simbol2 == '}') return 1;
    else return 0;
}
bool is_any_action(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        if (is_action(str[i])) {
            return 1;
        }
    }
    return 0;
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
                list.pop_front();
            }
            else return 0;
        }
    }
    return list.empty();
}

int search_for_right_bracket(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        if (is_right(str[i])) {
            return i;
        }
    }
    return -1;
}
int search_for_left_bracket(std::string str, int index) {
    int j = -1;
    for (int i = 0; i < index; i++) {
        if (is_left(str[i])) {
            j = i;
        }
    }
    return j;
}

int search_for_left_action(std::string str, int index) {
    for (int i = index; i >= 0; i--) {
        if (is_action(str[i])) {
            return i;
        }
    }
    return 0;
}
int search_for_right_action(std::string str, int index) {
    for (int i = index; i < str.length(); i++) {
        if (is_action(str[i])) {
            return i;
        }
    }
    return str.length();
}
int search_for_important_point(std::string str) {
    int important_point = 0;
    for (int i = 0; i < str.length(); i++) {
        if (is_important_action(str[i])) {
            important_point = i;
            break;
        }
    }
    return important_point;
}

double caleculation(double number1, double number2, char action) {
    switch (action)
    {
    case '+':
        return number1 + number2;
    case '-':
        return number1 - number2;
    case '*':
        return number1 * number2;
    case '/':
        return number1 / number2;
    case '^':
        return pow(number1,number2);
    }

}

std::string core_cal(std::string str) {
    std::cout << '\n' << str << '\n';
    double number1 = 0;
    double number2 = 0;
    char operation;
    int i = 0;
    for (i = 0; i < str.length();) {        
        while (is_number(str[i])) {
            number1 = 10 * number1 + (int(str[i]) - 48);
            i++;
        }
        if (str[i] == '.' || str[i] == ',') {
            i++;
            int power = 1;
            while (is_number(str[i])) {
                number1 = number1 + (int(str[i]) - 48) * pow(0.1, power);
                power++;
                i++;
            }
        }
        operation = str[i];
        i++;
        //std::cout << "operation " << operation << '\n';
        while (is_number(str[i])) {
            number2 = 10 * number2 + (int(str[i]) - 48);
            i++;
        }
        if (str[i] == '.' || str[i] == ',') {
            i++;
            int power = 1;
            while (is_number(str[i])) {
                number2 = number2 + (int(str[i]) - 48) * pow(0.1, power);
                power++;
                i++;
            }
            i = str.length();
        }
    }
    //std::cout << number1 << ' ' << number2 << ' ' << operation << '\n';
    double result = caleculation(number1, number2, operation);
    std::string new_str = std::to_string(result);
    for (int j = i; j < str.length(); j++) {
        new_str.push_back(str[j]);
    }
    return new_str;
}

std::string order_of_actions(std::string str) {
    std::string new_str;
    static std::string last = "";
    if (search_for_important_point(str) != 0) {
        int important_point = search_for_important_point(str);
        int dash = (search_for_left_action(str, important_point - 1) != 0);
        std::string data;
        for (int i = search_for_left_action(str, important_point - 1) + dash; i < search_for_right_action(str, important_point + 1); i++) {
            data.push_back(str[i]);
        }
        //std::cout << core_cal(data) << '\n';
        for (int i = 0; i < search_for_left_action(str, important_point - 1) + dash; i++) {
            new_str.push_back(str[i]);
        }
        new_str = new_str + (core_cal(data));
        for (int i = search_for_right_action(str, important_point + 1); i < str.length(); i++) {
            new_str.push_back(str[i]);
        }
       // std::cout << "a: " << new_str << '\n';
    }
    else if(search_for_right_action(str, 0) != 0){
        int important_point = search_for_right_action(str, 0);
        //std::cout << "point " << important_point << '\n';
        std::string data;
        for (int i = 0; i < search_for_right_action(str, important_point + 1); i++) {
            data.push_back(str[i]);
        }
        //std::cout << core_cal(data) << '\n';
        new_str = new_str + (core_cal(data));
        for (int i = search_for_right_action(str, important_point + 1); i < str.length(); i++) {
            new_str.push_back(str[i]);
        }
    }
    std::cout << new_str << '\n';
    if (is_any_action(new_str)) order_of_actions(new_str);
    else last = new_str;
    return last;
}

int caleculator(std::string str) {
    if (!is_cbs(str)) {
        std::cout << "Wrong CBS\n";
        return -666;
    }
    std::string data;
    for (int i = search_for_left_bracket(str, search_for_right_bracket(str)) + 1; i < search_for_right_bracket(str); i++) {
        data.push_back(str[i]);
    }

    std::string new_str;
    
    for (int i = 0; i < search_for_left_bracket(str, search_for_right_bracket(str)) + 1; i++) {
        new_str.push_back(str[i]);
    }
    new_str += order_of_actions(data);
    for (int i = search_for_right_bracket(str); i < str.length(); i++) {
        new_str.push_back(str[i]);
    }
    std::cout << "aaa " <<new_str;
    return 1;
}

int main()
{
    std::string str = "1+[(11/2+30.3*21+4*13+7+18)+3]";
    caleculator(str);
    return 1;
}



//Создайте программу, принимающую арифметическое выражение через поток ввода.
//Программа должна посчитать результат арифметического выражения.
//Необходимо реализовать операции : +, -, *, / , %, ^ (Возведение в степень), [](модуль выражения в скобках).
//Для определения порядка операций могут использоваться скобки двух видов : (), {}.