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
    std::cout << "As the value of n increases, e approaches 2.718, however as n increases further the 1/n term becomes much smaller leading to imprecision in the 1 + 1/n calculation where 1/n ~ 0, and thus for large n e becomes 1." << std::endl;
    std::cout << std::endl;

    // 1b
    for(int i=0; i < 8; i++){

        double x1 = (1 / arr[i]);
        float value = log(1 + x1);
        std::cout << arr[i] << " " << value << std::endl;

    }
    std::cout << std::endl;

    // 2
    int arr2[] = {2, 5, 10, 20, 30, 40};
    for (int i = 0; i < 6; i++)
    {
        float x = 100;
        std::cout << "Original Value of x: " << x << std::endl;

        for (int n = 0; n < arr2[i]; n++)
        {
            x = sqrt(x);
        }
        std::cout << "Value of n: " << arr2[i] << " Final value of x after square rooting n times: " << x << std::endl;

        for (int n = 0; n < arr2[i]; n++)
        {
            x *= x;
        }

        std::cout << "Value of n: " << arr2[i] << " Final value of x after multiplying n times: " << x << std::endl;
        std::cout << std::endl;

    }

    std::cout << "As the value of n increases, square rooting x n-times leads x to become very small and its exact value is lost due to minimal precision. Then when trying to recreate the original value by squaring x n-times it will be incorrect." << std::endl;
    std::cout << std::endl;

    // 3
    double arr3[]= {10e-5, 10e-6, 10e-7, 10e-8, 10e-9, 10e-10, 10e-11, 10e-12, 10e-13, 10e-14, 10e-15};
    for (int i = 0; i < 11; i ++)
    {
        double z = (exp(arr3[i]) - 1) / arr3[i];
        std::cout << "Original approach value: " << z << std::endl;

        double y = exp(arr3[i]);
        z = y == 1 ? 1 : ((y - 1) / log(y));
        std::cout << "Alternative approach value: " << z << std::endl;

        std::cout << std::endl;
    }

    std::cout << "As the value of x decreases, z approaches 1 but if x is too small its precision is lost and so z will deviate from 1." << std::endl;
    std::cout << std::endl;


}