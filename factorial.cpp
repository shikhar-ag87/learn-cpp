#include <iostream>


using namespace std;

int factorial(int n) {
    if(n<0) return 0;
    int res = 1;
    for(int i=n; i>0; i--) {
        res *= i;
    }
    return res;
}




int main () {
    int n = -5;
    cout << factorial(n)  << "\n";
    return 0;
}

