#include <iostream>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

using u128 = unsigned long long;

unordered_map<int, u128> cache;

u128 fib(int n) {
    if (n < 1) return 0;
    if (cache.find(n) != cache.end()) return cache[n];
    if(n==1 || n==2) return 1;
    u128 res = fib(n-1) + fib(n-2);
    cache[n] = res;
    return res;
}




int main () {
    int n = 1000;
    // for(int i=0; i<n; i++) {
    //     cout << fib(i+1) << "\n";
    // }
    auto start = high_resolution_clock::now();
    u128 res = fib(n);
    auto stop = high_resolution_clock::now();
    cout << res << "\n";
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Total time taken: " << duration.count()/1000.0f << "ms\n";
    return 0;
}

