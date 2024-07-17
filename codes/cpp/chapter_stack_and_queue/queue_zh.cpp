#include "../utils/common.hpp"

int main()
{
    queue<int> queue;

    queue.push(1);
    queue.push(3);
    queue.push(2);
    queue.push(5);
    queue.push(4);
    printQueue(queue);

    int front = queue.front();
    cout << "front = " << front << endl;

    queue.pop();
    cout << "after pop: " << endl;
    printQueue(queue);

    int size = queue.size();
    cout << "size = " << size << endl;

    bool empty = queue.empty();
    cout << "wheter empty: " << empty << endl;
}