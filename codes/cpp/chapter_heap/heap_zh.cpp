#include "../utils/common.hpp"

// priority_queue<int> means
// priority_queue<int, vector<int>, less<int>>;
// there will be compliation error if pass in priority_queue<int, vector<int>, greater<int>>;
void testPush(priority_queue<int>& heap, int val)
{
    heap.push(val);
    cout << "\n元素 " << val << " 入堆后" << endl;
    printHeap(heap);
}

void testPop(priority_queue<int> &heap) {
    int val = heap.top();
    heap.pop();
    cout << "\n堆顶元素 " << val << " 出堆后" << endl;
    printHeap(heap);
}

/* Driver Code */
int main() {
    /* 初始化堆 */
    // 初始化小顶堆
    // priority_queue<int, vector<int>, greater<int>> minHeap;
    // 初始化大顶堆
    priority_queue<int, vector<int>, less<int>> maxHeap;
    

    cout << "\n以下测试样例为大顶堆" << endl;

    /* 元素入堆 */
    testPush(maxHeap, 1);
    testPush(maxHeap, 3);
    testPush(maxHeap, 2);
    testPush(maxHeap, 5);
    testPush(maxHeap, 4);

    /* 获取堆顶元素 */
    int peek = maxHeap.top();
    cout << "\n堆顶元素为 " << peek << endl;

    /* 堆顶元素出堆 */
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);
    testPop(maxHeap);

    /* 获取堆大小 */
    int size = maxHeap.size();
    cout << "\n堆元素数量为 " << size << endl;

    /* 判断堆是否为空 */
    bool isEmpty = maxHeap.empty();
    cout << "\n堆是否为空 " << isEmpty << endl;

    /* 输入列表并建堆 */
    // 时间复杂度为 O(n) ，而非 O(nlogn)
    vector<int> input{1, 3, 2, 5, 4};
    priority_queue<int, vector<int>, greater<int>> minHeap(input.begin(), input.end());
    cout << "输入列表并建立小顶堆后" << endl;
    printHeap(minHeap);

    return 0;
}
