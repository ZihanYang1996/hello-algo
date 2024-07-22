#include "../utils/common.hpp"

template <typename T>
class ArrayDequeZH
{
private:
    vector<T> vals;
    int queSize;
    int front;

public:
    ArrayDequeZH(int capacity) :
        queSize{ 0 },
        front{ 0 }
    {
        vals.resize(capacity);
    }

    int capacity()
    {
        return vals.size();
    }

    int size()
    {
        return queSize;
    }

    bool isEmpty()
    {
        return size() == 0;
    }

    int index(int i)
    {
        return (i + capacity()) % capacity();
    }

    void pushFirst(T val)
    {
        if (queSize == capacity())
        {
            throw out_of_range("Deque is full");
        }
        front = index(front - 1);
        vals[front] = val;
        queSize++;
    }

    void pushLast(T val)
    {
        if (queSize == capacity())
        {
            throw out_of_range("Deque is full");
        }
        int rear = index(front + queSize);
        vals[rear] = val;
        queSize++;
    }

    T peekFirst()
    {
        if (isEmpty())
        {
            throw out_of_range("Deque is empty");
        }
        return vals[front];
    }

    T peekLast()
    {
        if (isEmpty())
        {
            throw out_of_range("Deque is empty");
        }
        int rear = index(front + queSize - 1);
        return vals[rear];
    }

    T popFirst()
    {
        T val = peekFirst();
        front = index(front + 1);
        queSize--;
        return val;
    }

    T popLast()
    {
        T val = peekLast();
        queSize--;
        return val;
    }

    vector<T> toVector()
    {
        vector<T> result(queSize);
        for (int i = 0, j = front; i < queSize; i++, j++)
        {
            result[i] = vals[index(j)];
        }
        return result;
    }
};

/* Driver Code */
int main() {
    /* 初始化双向队列 */
    ArrayDequeZH<int> *deque = new ArrayDequeZH<int>(10);
    deque->pushLast(3);
    deque->pushLast(2);
    deque->pushLast(5);
    cout << "双向队列 deque = ";
    printVector(deque->toVector());

    /* 访问元素 */
    int peekFirst = deque->peekFirst();
    cout << "队首元素 peekFirst = " << peekFirst << endl;
    int peekLast = deque->peekLast();
    cout << "队尾元素 peekLast = " << peekLast << endl;

    /* 元素入队 */
    deque->pushLast(4);
    cout << "元素 4 队尾入队后 deque = ";
    printVector(deque->toVector());
    deque->pushFirst(1);
    cout << "元素 1 队首入队后 deque = ";
    printVector(deque->toVector());

    /* 元素出队 */
    int popLast = deque->popLast();
    cout << "队尾出队元素 = " << popLast << "，队尾出队后 deque = ";
    printVector(deque->toVector());
    int popFirst = deque->popFirst();
    cout << "队首出队元素 = " << popFirst << "，队首出队后 deque = ";
    printVector(deque->toVector());

    /* 获取双向队列的长度 */
    int size = deque->size();
    cout << "双向队列长度 size = " << size << endl;

    /* 判断双向队列是否为空 */
    bool isEmpty = deque->isEmpty();
    cout << "双向队列是否为空 = " << boolalpha << isEmpty << endl;
    return 0;
}
