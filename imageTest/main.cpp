#include "image.cpp"

int main()
{
    
    Image img("test.jpg");

    img.addChromaticEffect();

    img.write("test2.png");

    return 0;
}
