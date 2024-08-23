#include <iostream>
using namespace std;

int solve(int a,int b, char ch){
    switch(ch){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
    }
    return 0;
}
int main(){
    int a,b;
    char ch;
    cout << "Hello!\nWelcome to Simple Calculator!" << endl;
    cout << "Enter two spaced integers:" << endl;
    cin >> a >> b;
    cout << "Enter the operation to be performed:" << endl;
    cin >> ch;
    cout << "Solution:" << solve(a,b,ch);
    return 0;
}