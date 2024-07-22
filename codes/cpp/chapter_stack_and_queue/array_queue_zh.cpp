#include "../utils/common.hpp"

template <typename T>
class ArrayQueue
{
private:
    T* vals;
    int front;
    int queueSize;
    int queueCapacity;

public:
    ArrayQueue(int capacity) :
        front{ 0 },
        queueSize{ 0 },
        queueCapacity{ capacity },
        vals{new T[capacity]}
    {}

    ~ArrayQueue()
    {
        delete[] vals;
    }

    int capacity()
    {
        return queueCapacity;
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
        if (queueSize == queueCapacity)
        {
            cout << "Queue is full" << endl;
            return;
        }
        int rear = (front + queueSize) % queueCapacity;
        vals[rear] = val;
        queueSize++;
    }
    
    T peek()
    {
        if (isEmpty())
        {
            throw out_of_range("Queue is empty");
        }
        return vals[front];
    }

    T pop()
    {
        T val = peek();
        front = (front + 1) % queueCapacity;
        queueSize--;
        return val;
    }

    vector<T> toVector()
    {
        vector<T> result(queueSize);
        for (int i = 0, j = front; i < queueSize; i++, j++)
        {
            result[i] = vals[j % queueCapacity];
        }
        return result;
    }

};

int main()
{
    int capacity = 10;
    ArrayQueue<int>* queue = new ArrayQueue<int>(capacity);


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

    /* 测试环形数组 */
    for (int i = 0; i < 10; i++) {
        queue->push(i);
        queue->pop();
        cout << "第 " << i << " 轮入队 + 出队后 queue = ";
        printVector(queue->toVector());
    }

    // 释放内存
    delete queue;

    return 0;
}