#include "../utils/common.hpp"

struct ListNodeZH
{
    int val;
    ListNodeZH* next;

    ListNodeZH(int x) :
        val(x), 
        next(nullptr)
    {

    }
};

void printLinkedListZH(ListNodeZH* head)
{
    vector<int> list;
    while (head != nullptr)
    {
        list.emplace_back(head->val);
        head = head->next;
    }
    cout << strJoin("->", list) << endl;
}

void insert(ListNodeZH* n0, ListNodeZH* P)
{
    ListNodeZH* n1 = n0->next;
    n0->next = P;
    P->next = n1;
}

void remove(ListNodeZH *n0)
{
    if (n0->next == nullptr)
    {
        return;
    }

    ListNodeZH* P = n0->next;
    ListNodeZH* n1 = P->next;

    n0->next = n1;
    delete P;
}

ListNodeZH* access(ListNodeZH* head, int index)
{
    for (int i = 0; i < index; i++)
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        head = head->next;
    }
    return head;
}

int find(ListNodeZH* head, int target)
{
    int index = 0;
    while (head != nullptr)
    {
        if (head->val == target)
        {
            return index;
        }
        else
        {
            head = head->next;
            index++;
        }
    }
    return -1;
}

int main()
{
    ListNodeZH* n0 = new ListNodeZH(1);
    ListNodeZH* n1 = new ListNodeZH(3);
    ListNodeZH* n2 = new ListNodeZH(2);
    ListNodeZH* n3 = new ListNodeZH(5);
    ListNodeZH* n4 = new ListNodeZH(4);

    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    printLinkedListZH(n0);

    insert(n0, new ListNodeZH(0));
    printLinkedListZH(n0);

    remove(n0);
    printLinkedListZH(n0);

    ListNodeZH* node = access(n0, 3);
    cout << "链表中索引 3 处的节点的值 = " << node->val << endl;

    int index = find(n0, 2);
    cout << "链表中值为 2 的节点的索引 = " << index << endl;
}