#include <vector>
#include <iostream>

// Generic print function
void print(std::vector<int> array)
{
    for (int i = 0; i < array.size(); i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void game(std::vector<int> array, int m, int starting_index)
{
    // base case to print and return when there is only 1 person left in the circle.
    if (array.size() == 1)
    {
        std::cout << "Position " << array[0] << " corresponding to person: " << array[0] + 1 << " is the winner!" << std::endl;
        return;
    }

    // Get index to remove by counting m elements from starting index and using modulo operator to stay within vector size bounds
    int removal_index = (starting_index + m) % array.size();

    // Remove the element at the removal index
    array.erase(array.begin() + removal_index);
    
    // Print array to see how it is changing
    // print(array);

    // since the index was removed, we start counting from the same spot we removed because the next value is now in that spot recursively.
    game(array, m, removal_index); 
}

int main()
{
    std::vector<int> array;

    int m = 2;
    int n = 5;

    for (int i = 0; i < n; i++)
    {
        array.push_back(i);
    }

    print(array);
    int starting_position_index = 0;

    // Pass in m-1 so that our array index matches up with our counting people
    game(array, m-1, starting_position_index);

    return 0;
}