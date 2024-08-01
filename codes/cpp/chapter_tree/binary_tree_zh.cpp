#include "../utils/common.hpp"

template <typename T>
struct TreeNodeZH
{
    T val;
    TreeNodeZH* left;
    TreeNodeZH* right;
    TreeNodeZH(T val) :
        val{ val },
        left{ nullptr },
        right{ nullptr }
    {}
};

template <typename T>
void bfsPrintTree(TreeNodeZH<T>* root)
{
    if (root == nullptr)
    {
        return;
    }

    std::queue<TreeNodeZH<T>*> q;
    q.push(root);

    while (!q.empty())
    {
        // Get how many node in current level
        // Then only process these node currently in the queue
        // Then whatever gets pushed into the queue in this loop will be the node on next level
        // Then repeat until the end
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++)
        {
            TreeNodeZH<T>* currentNode = q.front();
            q.pop();

            if (currentNode->left != nullptr)
            {
                q.push(currentNode->left);
            }
            if (currentNode->right != nullptr)
            {
                q.push(currentNode->right);
            }
            cout << currentNode->val;
        }
        if (!q.empty())
        {
            cout << " ";
        }
    }
    cout << endl;
}

template <typename T>
void freeMemoryTreeZH(TreeNodeZH<T>* root)
{
    if (root != nullptr)
    {
        freeMemoryTreeZH(root->left);
        freeMemoryTreeZH(root->right);
        cout << root->val << "is freed in memory\n";
        delete root;
    }
}


int main()
{
    /* 初始化二叉树 */
    // 初始化节点
    TreeNodeZH<int>* n1 = new TreeNodeZH<int>(1);
    TreeNodeZH<int>* n2 = new TreeNodeZH<int>(2);
    TreeNodeZH<int>* n3 = new TreeNodeZH<int>(3);
    TreeNodeZH<int>* n4 = new TreeNodeZH<int>(4);
    TreeNodeZH<int>* n5 = new TreeNodeZH<int>(5);
    TreeNodeZH<int>* n6 = new TreeNodeZH<int>(6);
    TreeNodeZH<int>* n7 = new TreeNodeZH<int>(7);
    TreeNodeZH<int>* n8 = new TreeNodeZH<int>(8);
    TreeNodeZH<int>* n9 = new TreeNodeZH<int>(9);
    TreeNodeZH<int>* n10 = new TreeNodeZH<int>(10);

    // 构建节点之间的引用（指针）
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->left = n6;
    n3->right = n7;
    n4->left = n8;
    n4->right = n9;
    n5->left = n10;
    cout << endl << "初始化二叉树" << endl;
    bfsPrintTree(n1);

    /* 插入与删除节点 */
    TreeNodeZH<int>* P = new TreeNodeZH<int>(0);
    n1->left = P;
    P->left = n2;
    cout << endl << "插入节点 P 后" << endl;
    bfsPrintTree(n1);
    
    // 删除节点 P
    n1->left = n2;
    delete P;
    cout << endl << "删除节点 P 后" << endl;
    bfsPrintTree(n1);

    // 释放内存
    freeMemoryTreeZH(n1);

    return 0;
}