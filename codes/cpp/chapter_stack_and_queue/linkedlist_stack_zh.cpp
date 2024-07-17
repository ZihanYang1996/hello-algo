#include "../utils/common.hpp"

template <typename T>
struct ListNodeZH
{
    T val;
    ListNodeZH* next;
    ListNodeZH(T x) :
        val(x),
        next(nullptr)
    {
    }
};

template <typename T>
class LinkedListStack
{
private:
    ListNodeZH<T>* stackTop;
    int stackSize;

public:
    LinkedListStack() :
        stackTop{ nullptr },
        stackSize{ 0 }
    {}

    ~LinkedListStack()
    {
        ListNodeZH<T>* pre;
        while (stackTop != nullptr)
        {
            pre = stackTop;
            stackTop = stackTop->next;
            delete pre;
        }
    }

    int size()
    {
        return stackSize;
    }

    bool isEmpty()
    {
        return size() == 0;
    }

    void push(T val)
    {
        ListNodeZH<T>* node = new ListNodeZH<T>(val);
        node->next = stackTop;
        stackTop = node;
        stackSize++;
    }

    T pop()
    {
        T val = top();

        ListNodeZH<T>* tmp = stackTop;
        stackTop = stackTop->next;

        stackSize--;
        delete tmp;
        
        return val;
    }

    T top()
    {
        if (isEmpty())
        {
            throw out_of_range("Stack is empty");
        }
        return stackTop->val;
    }

    vector<T> toVector()
    {
        vector<T> result(size());
        ListNodeZH<T>* node = stackTop;
        for (int i = size() - 1; i >= 0; i--)
        {
            result[i] = node->val;
            node = node->next;
        }
        return result;
    }


};


int main()
{
    /* 初始化栈 */
    LinkedListStack<int> *stack = new LinkedListStack<int>();

    /* 元素入栈 */
    stack->push(1);
    stack->push(3);
    stack->push(2);
    stack->push(5);
    stack->push(4);
    cout << "栈 stack = ";
    printVector(stack->toVector());

    /* 访问栈顶元素 */
    int top = stack->top();
    cout << "栈顶元素 top = " << top << endl;

    /* 元素出栈 */
    top = stack->pop();
    cout << "出栈元素 pop = " << top << "，出栈后 stack = ";
    printVector(stack->toVector());

    /* 获取栈的长度 */
    int size = stack->size();
    cout << "栈的长度 size = " << size << endl;

    /* 判断是否为空 */
    bool empty = stack->isEmpty();
    cout << "栈是否为空 = " << empty << endl;

    // 释放内存
    delete stack;

    return 0;
}