#include "../utils/common.hpp"

int main()
{
    vector<int> nums{1, 3, 2, 5, 4};
    printVector(nums);
    
    int num = nums[1];
    cout << "访问索引 1 处的元素，得到 num = " << num << endl;

    nums[1] = 0;
    cout << "将索引 1 处的元素更新为 0 ，得到 nums = ";
    printVector(nums);

    nums.clear();
    cout << "清空列表后 nums = ";
    printVector(nums);  

    nums.push_back(1);
    nums.push_back(3);
    nums.push_back(2);
    nums.emplace_back(5);
    nums.emplace_back(4);
    cout << "添加元素后 nums = ";
    printVector(nums);

    nums.insert(nums.begin() + 3, 6);
    cout << "在索引 3 处插入数字 6 ，得到 nums = ";
    printVector(nums);

    nums.erase(nums.begin() + 3);
    cout << "删除索引 3 处的元素，得到 nums = ";
    printVector(nums);

    int count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        count += nums[i];
    }
    cout << count << endl;

    count = 0;
    for (auto x : nums)
    {
        count += x;
    }
    cout << count << endl;

    vector<int> nums1{6, 8, 7, 10, 9};
    nums.insert(nums.end(), nums1.begin(), nums1.end());
    cout << "将列表 nums1 拼接到 nums 之后，得到 nums = ";
    printVector(nums);

    cout << *(nums.end()-1) << endl;    

    sort(nums.begin(), nums.begin()+3);
    cout << "排序列表前三个元素后 nums = ";
    printVector(nums);

    sort(nums.begin(), --nums.end());
    cout << "排序列表出最后一位元素以外后 nums = ";
    printVector(nums);    

    sort(nums.begin(), nums.end());
    cout << "排序列表后 nums = ";
    printVector(nums);    
}

