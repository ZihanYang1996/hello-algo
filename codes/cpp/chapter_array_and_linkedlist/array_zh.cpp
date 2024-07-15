#include "../utils/common.hpp"

template <typename T>
void printArrayZH(T* arr, int n)
{
    cout << "[";

    for (int i = 0; i < n-1; i++)
    {
        cout << arr[i] << ", ";
    }
    if (n >= 1)
    {
        cout << arr[n - 1] << "]" << endl;
    }
    else
    {
        cout << "]" << endl;
    }
}

int randomAccess(int* nums, int size)
{
    int randomIndex = rand() % size;
    int randomNum = nums[randomIndex];
    return randomNum;
}


void insert(int* nums, int size, int num, int index)
{
    for (int i = size - 1; i > index; i--)
    {
        nums[i] = nums[i-1];
    }
    nums[index] = num;
}

void remove(int* nums, int size, int index)
{
    for (int i = index; i < size - 1; i++)
    {
        nums[i] = nums[i + 1];
    }
}

int* extend(int* nums, int size, int enlarge)
{
    int* res = new int[size + enlarge];

    for (int i = 0; i < size; i++)
    {
        res[i] = nums[i];
    }
    delete[] nums;
    return res;
}


int main()
{
    int size = 5;
    int* arr = new int[size];
    printArrayZH(arr, size);

    int* nums = new int[size]{1, 3, 2, 5, 4};
    printArrayZH(nums, size);

    int randomNum = randomAccess(nums, size);
    cout << randomNum << endl;

    insert(nums, size, 6, 3);
    printArrayZH(nums, size);

    remove(nums, size, 2);
    printArrayZH(nums, size);

    int enlarge = 3;
    nums = extend(nums, size, enlarge);
    size += enlarge;
    printArray(nums, size);

    insert(nums, size, 10, 5);
    printArray(nums, size);
}