#include <cmath>
#include <array>
#include <iostream>

int main()
{
    // 1a
    float arr[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    for(int i=0; i < 8; i++){

        float value;
        value = pow((1 + (1 / arr[i])), arr[i]);
        std::cout << arr[i] << " " << value << std::endl;

    }

    // 1b

}