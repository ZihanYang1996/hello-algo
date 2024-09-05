#include "../utils/common.hpp"

// Use greater<T> for Max Heap, use less<T> for Min Heap
template <typename T = int, typename Container = vector<T>, typename Compare = greater<T>>
class Heap
{
private:
    Container heap;
    Compare comp;

    // Get the index of left child
    int left(int index)
    {
        return 2 * index + 1;
    }

    // Get the index of right child
    int right(int index)
    {
        return 2 * index + 2;
    }

    int parent(int index)
    {
        return (index - 1) / 2;
    }

    void ShifUp(int index)
    {
        while (true)
        {
            int pIndex = parent(index);
            if (pIndex >= 0 && comp(heap[index], heap[pIndex]))
            {
                swap(heap[index], heap[pIndex]);
                index = pIndex;
            }
            else
            {
                break;
            }
        }
    }

    void ShiftDown(int index)
    {
        while (true)
        {
            int leftIndex = left(index);
            int rightIndex = right(index);
            if (rightIndex >= size())
            {
                break;
            }
            int candidateIndex = comp(heap[leftIndex], heap[rightIndex]) ? leftIndex : rightIndex;
            if (comp(heap[candidateIndex], heap[index]))
            {
                swap(heap[candidateIndex], heap[index]);
                index = candidateIndex;
            }
            else
            {
                break;
            }
        }
    }

public:
    Heap(Container nums) :
        comp(Compare()) // or comp(), which use the defualt constructor
    {
        // comp = Compare() // can also be initialized in the constructor body
        heap = nums;
        for (int i = parent(size() - 1); i >= 0; i--)
        {
            ShiftDown(i);
        }
    }

    // Get heap size
    int size()
    {
        return heap.size();
    }

    bool isEmpty()
    {
        return size() == 0;
    }

    T peek()
    {
        return heap[0];
    }

    void push(T val)
    {
        heap.push_back(val);
        ShifUp(size() - 1);
    }

    void pop()
    {
        if (isEmpty())
        {
            throw out_of_range("堆为空");
        }

        swap(heap[0], heap[size() - 1]);
        heap.pop_back();
        ShiftDown(0);
    }

    /* 打印堆（二叉树）*/
    void print() {
        cout << "堆的数组表示：";
        printVector(heap);
        cout << "堆的树状表示：" << endl;
        TreeNode* root = vectorToTree(heap);
        printTree(root);
        freeMemoryTree(root);
    }
};

int main()
{
    /* 初始化大顶堆 */
    vector<int> vec{9, 8, 6, 6, 7, 5, 2, 1, 4, 3, 6, 2};
    Heap<int, vector<int>, greater<int>> maxHeap(vec);
    // Heap<int, vector<int>, less<int>> maxHeap(vec);  // Min Heap also works (even it's called maxHeap :) )
    cout << "\n输入列表并建堆后" << endl;
    maxHeap.print();

    /* 获取堆顶元素 */
    int peek = maxHeap.peek();
    cout << "\n堆顶元素为 " << peek << endl;

    /* 元素入堆 */
    int val = 7;
    maxHeap.push(val);
    cout << "\n元素 " << val << " 入堆后" << endl;
    maxHeap.print();

    /* 堆顶元素出堆 */
    peek = maxHeap.peek();
    maxHeap.pop();
    cout << "\n堆顶元素 " << peek << " 出堆后" << endl;
    maxHeap.print();

    /* 获取堆大小 */
    int size = maxHeap.size();
    cout << "\n堆元素数量为 " << size << endl;

    /* 判断堆是否为空 */
    bool isEmpty = maxHeap.isEmpty();
    cout << "\n堆是否为空 " << isEmpty << endl;

    return 0;
}