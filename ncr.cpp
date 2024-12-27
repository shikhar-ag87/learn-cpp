#include<iostream>

using namespace std;

int ncr(int n, int r) {
    int res = 1;
    for (int i = 0; i < r; i++)
    {
        res *= (n-i);
    }
    
    for (int i = 0; i < r; i++)
    {
        res /= (r-i);
    }
    
    

    return res;
}

int main() {
    int n = 5;
    int r = 3;
    cout << ncr(n, r) << "\n";
    return 0;
}