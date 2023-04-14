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
    for (int i = 1; i < str.length(); i++) {
        if (is_action(str[i])) {
            return 1;
        }
    }
    return 0;
}
bool is_any_bracket(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        if (is_bracket(str[i])) {
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
            if (is_left(data[i])) list.push_front(data[i]);
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
int plus_minus(char simbol) {
    if (simbol == '-') return -1;
    else return 1;
}

std::string core_cal(std::string str) {
    std::cout << '\n' << str << '\n';
    double number1 = 0;
    double number2 = 0;
    char operation;
    static std::string final = "";
    int i = 0;
    int pm1 = 1;
    int pm2 = 1;
    if (is_action(str[0])) {
        pm1 = plus_minus(str[0]);
        i++;
    }
    for (i; i < str.length();) {
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
        if (is_action(str[i])) {
            pm2 = plus_minus(str[i]);
            i++;
        }
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
        }
        break;
    }
    double result = caleculation(pm1*number1, pm2*number2, operation);
    std::string new_str = std::to_string(result);
    for (int j = i; j < str.length(); j++) {
        new_str.push_back(str[j]);
    }
    //std::cout << "new " << number1 << ' ' << number2 << ' ' << operation << '\n';
    //std::cout << "a " << new_str << '\n';
    if (is_any_action(new_str) && search_for_left_action(new_str,new_str.length()-1) != 0) core_cal(new_str);
    else final = new_str;
    return final;
}

std::string order_of_actions(std::string str) {
    std::string new_str;
    static std::string last = "";
    if (search_for_important_point(str) != 0) {
        int important_point = search_for_important_point(str);
        int dash = (search_for_left_action(str, important_point - 1) != 0);
        std::string data;
        for (int i = search_for_left_action(str, important_point - 1) + dash; i < search_for_right_action(str, important_point + 2); i++) {
            data.push_back(str[i]);
        }
        for (int i = 0; i < search_for_left_action(str, important_point - 1) + dash; i++) {
            new_str.push_back(str[i]);
        }
        new_str = new_str + (core_cal(data));
        for (int i = search_for_right_action(str, important_point + 2); i < str.length(); i++) {
            new_str.push_back(str[i]);
        }
        //std::cout << "core " << core_cal(data) << '\n';
    }
    else if(search_for_left_action(str, str.length()-1) != 0){
        int important_point = search_for_left_action(str, str.length() - 1);
        std::string data;
        for (int i = 0; i < search_for_right_action(str, important_point + 1); i++) {
            data.push_back(str[i]);
        }
        new_str = new_str + (core_cal(data));
        for (int i = search_for_right_action(str, important_point + 1); i < str.length(); i++) {
            new_str.push_back(str[i]);
        }
        //std::cout << "core " << core_cal(data) << '\n';
    }

    std::cout <<"str " << new_str << '\n';
    //std::cout << "is " << is_any_action(new_str) << '\n';
    if (is_any_action(new_str)) order_of_actions(new_str);
    else last = new_str;
    return last;
}

std::string caleculator(std::string str) {
    if (!is_cbs(str)) {
        std::cout << "Wrong CBS\n";
        return std::string("Wrong CBS\n");
    }

    if (is_pair(str[0], str[str.length() - 1])) caleculator(str.erase(0, 1).erase(str.length() - 2, 1));
    static std::string cal_final = "";
    std::string data;
    for (int i = search_for_left_bracket(str, search_for_right_bracket(str)) + 1; i < search_for_right_bracket(str); i++) {
        data.push_back(str[i]);
    }

    std::string new_str;
    
    for (int i = 0; i < search_for_left_bracket(str, search_for_right_bracket(str)); i++) {
        new_str.push_back(str[i]);
    }
    //if (str[search_for_left_bracket(str, search_for_right_bracket(str))] == '[') {
    //    new_str += order_of_actions(data);
    //}
    new_str += order_of_actions(data);
    for (int i = search_for_right_bracket(str)+1; i < str.length(); i++) {
        new_str.push_back(str[i]);
    }
    std::cout << "aaa " <<new_str <<'\n';
    if (is_any_bracket(new_str)) caleculator(new_str);
    else cal_final = order_of_actions(new_str);
    return cal_final;
}

int main()
{
    std::string str = "[-(2.2+3()+6*2]-5";
    std::cout <<"final " << caleculator(str);
    //std::string str2 = "-5*-1";
    //std::cout << order_of_actions(str2);
    return 1;
}



//Создайте программу, принимающую арифметическое выражение через поток ввода.
//Программа должна посчитать результат арифметического выражения.
//Необходимо реализовать операции : +, -, *, / , %, ^ (Возведение в степень), [](модуль выражения в скобках).
//Для определения порядка операций могут использоваться скобки двух видов : (), {}.