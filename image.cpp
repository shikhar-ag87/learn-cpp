#include <iostream>

using std::cout;
using std::cin;

struct Image {
    using u32 = unsigned long;

    u32 _height;
    u32 _width;
    bool _hasAlpha;
    u32 *_data;

    Image(int height, int width, bool hasAlpha) {
        height = height;
        width = width;
        hasAlpha=hasAlpha;
        u32 d[_height][_width][(hasAlpha ? 4 : 3)];
        _data = &d[0][0][0];
    }
    


};


int main() {

    char *filename;
    cout << "Enter file name: ";
    cin >> filename;
    cout << "\nloading file \"" << filename << "\"\n";
    


    return 0;
}


