#include<iostream>
#include<vector>

using namespace std;



int main() {
    vector<char> vec = {65,66,67};
    
    for(int val : vec) {
        cout << val << "\n";
    }

    int arr[5] = {1,2,3,4,5};
    
    for(int val : arr) {
        cout << val << "\n";
    }

    cout << "size of vector = " << vec.size() << "\n";
    cout << "max size of vector = " << vec.capacity() << "\n";
    for (int i = 0; i < 30; i++)
    {
        vec.push_back(i);
    }
    
    cout << "size of vector = " << vec.size() << "\n";
    cout << "max size of vector = " << vec.capacity() << "\n";
    return 0;
}