#include <iostream>

void print(int arr[], int num)
{
    for (int i = 0; i < num; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void solution(int x, int arr[], int sum, int index)
{
    if (sum == x)
    {
        print(arr, index);
        return;
    }

    int value = 1;
                                // Index is 0 OR // Value is less than or equal to the previous value in array
    while ((value <= x-sum) && ((index == 0) || (value <= arr[index-1])))
    {
        arr[index] = value;

        solution(x, arr, sum+value, index+1);

        value++;
    }
}


int main()
{
    int a = 4;
    int arr[4];
    solution(a, arr, 0, 0);
    return 0;
}