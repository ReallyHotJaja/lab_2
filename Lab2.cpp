#include<iostream>
#include <fstream>
#include<string>

using std::string;
using std::ifstream;
using std::cout;

const char *str;
int RevMath();
int NumCheck();
int ForwAdd();
double ForwMult();
int prior();

char get(){
    return *str++;
}

char peek(){
    return *str;
}

int NumCheck(){
    int result = get() - '0';
    while (peek() >= '0' && peek() <= '9'){
        result = 10*result + get() - '0';
    }
    return result;
}

int ForwAdd(){
    int result;
    double a = ForwMult();
    if (a == 1.5){
        return -1;
    }
    else{
        result = a;
    }
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += ForwMult();
        else
            result -= ForwMult();
    return result;
}

int prior(){
    if (peek() >= '0' && peek() <= '9')
        return NumCheck();
    if (peek() == '('){
        get(); 
        int result = ForwAdd();
        get(); 
        return result;
    }
    if (peek() == '-'){
        get();
        return -prior();
    }
    return 0; 
}

double ForwMult(){
    int result = prior();
    while (peek() == '*' || peek() == '/')
        if (get() == '*')
            result *= prior();
        else{
            int b = prior();
            if (b == 0){
                return 1.5 ;
                break;
            }
            else{
            result /= b;
            }
        }
    return result;
}

int RevMath(){
    int result = 0;
    int a = prior();
    while(peek() != '='){
    get();
    int b = prior();
    get();
    switch (peek()){
    case '/':
        get();
        if (b == 0) {
        return -1;
        }
        else{
            result = a / b;
            a = result;
            break;
        }
    case '*':
        get();
        result = a * b;
        a = result;
        break;
    
    case '+':
        get();
        result = a + b;
        a = result;
        break;
    case '-':
        get();
        result = a - b;
        a = result;
        break;
    }
    }
    return result;
}

int main(int argc, char* argv[]){
    string line;
    if(argv[1] == "--forward"){
        str = argv[2];
        int result = ForwAdd();
        cout << result;
    }
    if (argv[1] == "--reverse"){
        str = argv[2];
        int result = RevMath();
        cout << result;
    }
    if (argv[1] == "--file"){
          ifstream myfile (argv[3]);
          if(argv[2] == "--forward"){
            if (myfile.is_open()){
                 while (getline(myfile, line)){
                 str = const_cast<char*>(line.c_str());
                 int result = ForwAdd();
                 cout << result << std::endl;
                }
                 myfile.close();
            }
            else cout << "Error";
            }
          if (argv[2] == "--reverse"){
            if (myfile.is_open()){
                 while (getline(myfile,line)){
                 str = const_cast<char*>(line.c_str());
                 int result = RevMath();
                 cout << result << std::endl;
                }
                 myfile.close();
            }
            else cout << "Error";
            }
    }
    return 0;
}