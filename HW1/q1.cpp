#include <cmath>
#include <array>
#include <iostream>
#include <bitset>
#include <iomanip>
#include <climits>
#include <cstring>

void exponent_extractor(double num)
{
    // Extract the exponent.
    union
    {
        double input; // assumes sizeof(double) == sizeof(long)
        unsigned long output;

    } data;

    data.input = num;

    std::bitset<sizeof(double) * CHAR_BIT> bits(data.output);
    std::cout << "Bit value of double entered: " << bits << std::endl;

    // Shift all bits to the right so that the LSB of the exponent is the LSB.
    std::bitset<sizeof(double) * CHAR_BIT> rs = bits >> 52;
    std::cout << "Right shifting 52 bits: " << rs << std::endl;

    // Create an bit mask of all 1s and then right shift it 53 spaces. This is so that you only AND with the exponent regions.
    // The mantissa has been discarded by right shifting 52 bits, and the sign is the only thing left, so by shifting 53 bits we are avoiding
    // the sign bit.
    std::bitset<sizeof(double) * CHAR_BIT> mask(-1);
    std::bitset<sizeof(double) * CHAR_BIT> mask_rs = mask >> 53;
    std::cout << "Mask to extract exponent: " << mask_rs << std::endl;

    // Use Bit wise & to extract the exponent and then convert to unsigned long integer.
    std::bitset<sizeof(double) * CHAR_BIT> exponent = rs & mask_rs;
    
    unsigned long exp = exponent.to_ulong();
    unsigned long ub_exp = exp - 1023;

    std::cout << "Exponent is: " << exp << " Unbiased Exponent is: " << ub_exp << " Value of the exponent term: " << pow(2, ub_exp) << std::endl;

    // Convert exponent
    int b10_exponent = log10(2) * ub_exp;
    std::cout << "Base 10 is: " << b10_exponent << std::endl;
    std::cout << std::endl;

}

int main()
{
    // 1a
    float arr[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    for(int i=0; i < 8; i++){

        //float x = (1.0 / arr[i]);
        //float value = pow((1.0 + x), arr[i]);
        float x = 1.0 + (1.0 / arr[i]);
        float value = pow(x, arr[i]);

        std::cout << arr[i] << " " << std::setprecision(16) << value << std::endl;

    }
    std::cout << "As the value of n increases, e approaches 2.718, however as n increases further the 1/n term becomes much smaller leading to imprecision in the 1.0 + 1/n calculation where 1/n ~ 0." << std::endl;
    std::cout << std::endl;

    // 1b
    for(int i=0; i < 8; i++){

        float x1 = (1 / arr[i]);
        volatile float y = 1 + x1;
        volatile float z = y - 1;

        float value = z == 0 ? x1 : x1 * log(y) / z;

        float final_value = arr[i]*value;

        std::cout << arr[i] << " " << exp(final_value) << std::endl;

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

    std::cout << "As the value of x decreases, z approaches 1 but if x is too small its precision is lost and so z will deviate alot from 1." << std::endl;
    std::cout << std::endl;

    // 4
    // Function above has all the code and comments
    exponent_extractor(65.56);
    exponent_extractor(1.5);
    exponent_extractor(4.5);
}