#include<iostream>

using namespace std;

int sumDigits(int n) {
    int res = 0;
    while(n>0) {
        res += n%10;
        n/=10;
    }   

    return res;
}

int main() {
    int n = 2;
    cout << sumDigits(n) << "\n";
    return 0;
}