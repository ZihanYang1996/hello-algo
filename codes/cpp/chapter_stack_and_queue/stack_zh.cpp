#include "../utils/common.hpp"

int main()
{
    stack<int> stack;

    stack.push(1);
    stack.push(3);
    stack.push(2);
    stack.push(5);
    stack.push(4);
    cout << "stack = ";
    printStack(stack);

    int top = stack.top();
    cout << "top = " << top << endl;

    stack.pop();
    cout << "pop = " << top << ", after pop stack = ";
    printStack(stack);

    int size = stack.size();
    cout << "size = " << size << endl;

    bool empty = stack.empty();
    cout << "empty = " << empty << endl;    

}