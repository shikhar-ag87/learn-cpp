#include<iostream>
#include<string>


using namespace std;

int decToBin(int n) {
    int res = 0;
    int i = 1;
    while (n>0) {
        res += (n%2) * i;
        n/=2;
        i*=10;
    }
    return res;
}

int main() {
    int n = 4;
    cout << decToBin(n) << "\n";
    cout << decToBin(n-1) << "\n";
    return 0;
}