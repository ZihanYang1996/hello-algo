#include "../utils/common.hpp"

priority_queue<int, vector<int>, greater<int>> topKHeap(vector<int>& nums, int k)
{
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = 0; i < k; i++)
    {
        heap.push(nums[i]);
    }
    for (int i = k; i < nums.size(); i++)
    {
        if (nums[i] > heap.top())
        {
            heap.pop();
            heap.push(nums[i]);
        }
    }
    return heap;
}

// Driver Code
int main() {
    vector<int> nums = {1, 7, 6, 3, 2};
    int k = 3;

    priority_queue<int, vector<int>, greater<int>> res = topKHeap(nums, k);
    cout << "最大的 " << k << " 个元素为: ";
    printHeap(res);

    return 0;
}