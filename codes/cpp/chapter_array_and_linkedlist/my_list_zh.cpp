#include "../utils/common.hpp"

class MyList
{
private:
    int *arr;
    int arrCapacity{10};
    int arrSize{0};
    int extendRatio{2};

public:
    MyList()
    {
        arr = new int[arrCapacity];
    }

    ~MyList()
    {
        delete[] arr;
    }

    int size()
    {
        return arrSize;
    }

    int capacity()
    {
        return arrCapacity;
    }

    int get(int index)
    {
        if (index < 0 || index >= size())
        {
            throw out_of_range("Index out of bound");
        }
        return arr[index];
    }

    void set(int index, int num)
    {
        if (index < 0 || index >= size())
        {
            throw out_of_range("Index out of bound");
        }
        arr[index] = num;
    }

    void add(int num)
    {
        if (size() == capacity())
        {
            extendCapacity();
        }
        arr[size()] = num;
        arrSize++;
    }

    void insert(int index, int num)
    {
        if (index < 0 || index >= size())
        {
            throw out_of_range("Index out of bound");
        }
        if (size() == capacity())
        {
            extendCapacity();
        }
        for (int i = size(); i > index; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = num;
        arrSize++;
    }

    int remove(int index)
    {
        if (index < 0 || index >= size())
        {
            throw out_of_range("Index out of bound");
        }
        int num = arr[index];
        for (int i = index; i < size() - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arrSize--;
        return num;
    }

    vector<int> toVector()
    {
        vector<int> result(size());
        for (int i = 0; i < size(); i++)
        {
            result[i] = arr[i];
        }
        return result;
    }

    void extendCapacity()
    {
        int newCapacity = arrCapacity * extendRatio;
        int *temp = arr;
        arr = new int[newCapacity];

        for (int i = 0; i < size(); i++)
        {
            arr[i] = temp[i];
        }

        delete[] temp;
        arrCapacity = newCapacity;
    }
};

int main()
{
    /* 初始化列表 */
    MyList *nums = new MyList();
    /* 在尾部添加元素 */
    nums->add(1);
    nums->add(3);
    nums->add(2);
    nums->add(5);
    nums->add(4);
    cout << "列表 nums = ";
    vector<int> vec = nums->toVector();
    printVector(vec);
    cout << "容量 = " << nums->capacity() << " ，长度 = " << nums->size() << endl;

    /* 在中间插入元素 */
    nums->insert(3, 6);
    cout << "在索引 3 处插入数字 6 ，得到 nums = ";
    vec = nums->toVector();
    printVector(vec);

    /* 删除元素 */
    nums->remove(3);
    cout << "删除索引 3 处的元素，得到 nums = ";
    vec = nums->toVector();
    printVector(vec);

    /* 访问元素 */
    int num = nums->get(1);
    cout << "访问索引 1 处的元素，得到 num = " << num << endl;

    /* 更新元素 */
    nums->set(1, 0);
    cout << "将索引 1 处的元素更新为 0 ，得到 nums = ";
    vec = nums->toVector();
    printVector(vec);

    /* 测试扩容机制 */
    for (int i = 0; i < 10; i++) {
        // 在 i = 5 时，列表长度将超出列表容量，此时触发扩容机制
        nums->add(i);
    }
    cout << "扩容后的列表 nums = ";
    vec = nums->toVector();
    printVector(vec);
    cout << "容量 = " << nums->capacity() << " ，长度 = " << nums->size() << endl;

    // 释放内存
    delete nums;

    return 0;
}