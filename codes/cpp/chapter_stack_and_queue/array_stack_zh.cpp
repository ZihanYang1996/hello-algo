#include "../utils/common.hpp"

template <typename T>
class ArrayStack
{
private:
    vector<T> stack;

public:
    int size()
    {
        return stack.size();
    }

    bool isEmpty()
    {
        return stack.empty();
    }

    void push(T val)
    {
        stack.emplace_back(val);
    }

    T pop()
    {
        T val = top();
        stack.pop_back();
        return val;
    }

    T top()
    {
        if (isEmpty())
        {
            throw out_of_range("Stack is empty");
        }
        return stack.back();
    }

    vector<T> toVector()
    {
        return stack;
    }
};

int main()
{
    /* 初始化栈 */
    ArrayStack<int>* stack = new ArrayStack<int>();

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
