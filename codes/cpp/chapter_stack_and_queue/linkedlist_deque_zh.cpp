#include "../utils/common.hpp"

template <typename T>
struct DoublyListNodeZH
{
    T val;
    DoublyListNodeZH* next;
    DoublyListNodeZH* prev;
    DoublyListNodeZH(T val) :
        val{ val },
        next{ nullptr },
        prev{ nullptr }
    {}
};

template <typename T>
class LinkedListDequeZH
{
private:
    DoublyListNodeZH<T>* front;
    DoublyListNodeZH<T>* rear;
    int queueSize = 0;

public:
    LinkedListDequeZH() :
        front{ nullptr },
        rear{ nullptr }
    {}

    ~LinkedListDequeZH()
    {
        DoublyListNodeZH<T>* pre = front;
        while (front != nullptr)
        {
            front = front->next;
            delete pre;
            pre = front;
        }
    }

    int size()
    {
        return queueSize;
    }

    int isEmpty()
    {
        return size() == 0;
    }

    void pushFirst(T val)
    {
        push(val, true);
    }

    void pushLast(T val)
    {
        push(val, false);
    }

    T popFirst()
    {
        return pop(true);
    }

    T popLast()
    {
        return pop(false);
    }

    T peekFirst()
    {
        if (isEmpty())
        {
            throw out_of_range("Deque is empty!");
        }
        return front->val;
    }

    T peekLast()
    {
        if (isEmpty())
        {
            throw out_of_range("Deque is empty!");
        }
        return rear->val;
    }

    vector<T> toVector()
    {
        vector<T> result(size());
        DoublyListNodeZH<T>* node = front;
        for (int i = 0; i < size(); i++)
        {
            result[i] = node->val;
            node = node->next;
        }
        return result;
    }

private:
    void push(T val, bool isFront)
    {
        DoublyListNodeZH<T>* node = new DoublyListNodeZH<T>(val);
        if (isEmpty())
        {
            front = node;
            rear = node;
        }
        else if (isFront)
        {
            node->next = front;
            front->prev = node;
            front = node;
        }
        else if (!isFront)
        {
            rear->next = node;
            node->prev = rear;
            rear = node;
        }
        queueSize++;
    }

    T pop(bool isFront)
    {
        if (isEmpty())
        {
            throw out_of_range("Deque is empty!");
        }

        T val;
        if (isFront)
        {
            val = front->val;
            DoublyListNodeZH<T>* tmp = front;
            front = front->next;
            if (front != nullptr)
            {
                front->prev = nullptr;
            }
            delete tmp;
        }
        else if (!isFront)
        {
            val = rear->val;
            DoublyListNodeZH<T>* tmp = rear;
            rear = rear->prev;
            if (rear != nullptr)
            {
                rear->next = nullptr;
            }
            delete tmp;
        }
        queueSize--;
        return val;
    }

};

int main() {
    /* 初始化双向队列 */
    LinkedListDequeZH<int> *deque = new LinkedListDequeZH<int>();
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
    cout << "元素 4 队尾入队后 deque =";
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

    // 释放内存
    delete deque;

    return 0;
}