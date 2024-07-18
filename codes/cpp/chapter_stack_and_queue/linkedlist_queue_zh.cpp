#include "../utils/common.hpp"

template <typename T>
struct ListNodeZH
{
    T val;
    ListNodeZH* next;
    ListNodeZH(T x) :
        val{ x },
        next{ nullptr }
    {}
};

template <typename T>
class LinkedListQueue
{
private:
    ListNodeZH<T>* front;
    ListNodeZH<T>* rear;
    int queueSize;

public:
    LinkedListQueue() :
        front{ nullptr },
        rear{ nullptr },
        queueSize{ 0 }
    {}

    ~LinkedListQueue()
    {
        ListNodeZH<T>* pre;
        while (front != nullptr)
        {
            pre = front;
            front = front->next;
            delete pre;
        }
    }

    int size()
    {
        return queueSize;
    }

    bool isEmpty()
    {
        return size() == 0;
    }

    void push(T val)
    {
        ListNodeZH<T>* node = new ListNodeZH<T>(val);
        if (front == nullptr)
        {
            front = node;
            rear = node;
        }
        else
        {
            rear->next = node;
            rear = node;
        }
        queueSize++;
    }

    T peek()
    {
        if (isEmpty())
        {
            throw out_of_range("Queue is empty");
        }
        return front->val;
    }

    T pop()
    {
        T num = peek();
        ListNodeZH<T>* tmp = front;
        front = front->next;
        delete tmp;
        queueSize--;
        return num;
    }

    vector<T> toVector()
    {
        vector<T> result(size());
        ListNodeZH<T>* node = front;
        for (int i = 0; i < size(); i++)
        {
            result[i] = node->val;
            node = node->next;
        }
        return result;
    }

};

/* Driver Code */
int main() {
    /* 初始化队列 */
    LinkedListQueue<int>* queue = new LinkedListQueue<int>();

    /* 元素入队 */
    queue->push(1);
    queue->push(3);
    queue->push(2);
    queue->push(5);
    queue->push(4);
    cout << "队列 queue = ";
    printVector(queue->toVector());

    /* 访问队首元素 */
    int peek = queue->peek();
    cout << "队首元素 peek = " << peek << endl;

    /* 元素出队 */
    peek = queue->pop();
    cout << "出队元素 pop = " << peek << "，出队后 queue = ";
    printVector(queue->toVector());

    /* 获取队列的长度 */
    int size = queue->size();
    cout << "队列长度 size = " << size << endl;

    /* 判断队列是否为空 */
    bool empty = queue->isEmpty();
    cout << "队列是否为空 = " << empty << endl;

    // 释放内存
    delete queue;

    return 0;
}
