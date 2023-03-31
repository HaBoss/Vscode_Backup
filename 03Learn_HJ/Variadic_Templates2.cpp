#include <iostream>
using namespace std;

void print(const char* s){
    while(*s){
        if(*s == '%' && *(++s) != '%')
            throw std::runtime_error("invalid format string: missing arguments");
        cout << *s++;
    }
}

template<typename T , typename... Args>
void print(const char *s, T value, Args... args){
    while(*s){
        if(*s == '%' && *(++s) != '%'){
            cout << value << endl;
            printf(++s, args...);
            return;
        }
        cout << *s++;
    }
    throw std::logic_error("extra arguments provided to printf");
}

int main(){
    int *pi = new int;
    print("%d%s%p%f\n",15,"This is Ace.",pi,3.141592);
}