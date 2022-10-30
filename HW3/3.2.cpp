#include <iostream>

// Basic print function to print the array uptil the index.
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
    // Check to see if running sum is equal to x. If so, print out the arr up to the index (which is the last item placed in the array).
    if (sum == x)
    {
        print(arr, index);
        return;
    }

    // Set value equal to 1 on each call so that we can count up to our target x for each iteration
    int value = 1;
        
        // Loop and recurse while value is less than or equal to differences of x-sum and // Index is 0 OR // Value is less than or equal to the previous value in array
        // Allows for multiple 1s to be placed.
        // When the stack frames get returned from print, then value++ is called, to increment the value and start overwriting the array.
    while ((value <= x-sum) && ((index == 0) || (value <= arr[index-1])))
    {
        // Sets value of array at index.
        arr[index] = value;

        // Recurse by adding sum with value to get new sum that will be compared on the next stack and increment index by 1 to fill in the next 
        // part of the array if sum != x.
        solution(x, arr, sum+value, index+1);

        // Increments
        value++;
    }
}

int main()
{
    int a = 4;
    int arr[a];
    solution(a, arr, 0, 0);

    int b = 5;
    int brr[b];
    solution(b, brr, 0, 0);

    return 0;
}