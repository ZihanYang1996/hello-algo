#include "../utils/common.hpp"
#include "binary_tree_zh.cpp"

template <typename T>
TreeNodeZH<T>* vectorToTreeDFSZH(const vector<T>& arr, int index)
{
    if (index < 0 || index >= arr.size() || arr[index] == INT_MAX)
    {
        return nullptr;
    }
    TreeNodeZH<T>* currentNode = new TreeNodeZH<T>(arr[index]);
    currentNode->left = vectorToTreeDFSZH(arr, index * 2 + 1);
    currentNode->right = vectorToTreeDFSZH(arr, index * 2 + 2);
    return currentNode;
}

template <typename T>
TreeNodeZH<T>* vectorToTreeZH(const vector<T>& arr)
{
    return vectorToTreeDFSZH(arr, 0);
}




template <typename T>
class ArrayBinaryTreeZH
{
private:
    vector<T> tree;
    enum class Order
    {
        PRE,
        IN,
        POST
    };

public:
    ArrayBinaryTreeZH(vector<T> arr)
    {
        tree = arr;
    }

    int size()
    {
        return tree.size();
    }

    T val(int index)
    {
        if (index < 0 || index >= size())
        {
            return INT_MAX;
        }
        return tree[index];
    }

    int left(int index)
    {
        return 2 * index + 1;
    }

    int right(int index)
    {
        return 2 * index + 2;
    }

    int parent(int index)
    {
        return (index - 1) / 2;
    }

    vector<T> levelOrder()
    {
        vector<T> res;
        queue<int> q;
        if (val(0) == INT_MAX)
        {
            return res;
        }
        q.push(0);
        while (!q.empty())
        {
            int nodeIndex = q.front();
            q.pop();
            // cout << nodeIndex;
            res.push_back(val(nodeIndex));
            if (val(left(nodeIndex)) != INT_MAX)
            {
                q.push(left(nodeIndex));
            }
            if (val(right(nodeIndex)) != INT_MAX)
            {
                q.push(right(nodeIndex));
            }            
        }
        return res;
    }

    vector<T> preOrder()
    {
        vector<T> res;
        dfs(0, Order::PRE, res);
        return res;
    }

    vector<T> inOrder()
    {
        vector<T> res;
        dfs(0, Order::IN, res);
        return res;
    }

    vector<T> postOrder()
    {
        vector<T> res;
        dfs(0, Order::POST, res);
        return res;
    }

private:
    void dfs(int rootIndex, Order order, vector<T>& res)
    {
        if (val(rootIndex) == INT_MAX)
        {
            return;
        }
        if (order == Order::PRE)
        {
            res.push_back(val(rootIndex));
        }
        dfs(left(rootIndex), order, res);
        if (order == Order::IN)
        {
            res.push_back(val(rootIndex));
        }
        dfs(right(rootIndex), order, res);
        if (order == Order::POST)
        {
            res.push_back(val(rootIndex));
        }
    }

};

/* Driver Code */
int main() {
    // 初始化二叉树
    // 使用 INT_MAX 代表空位 nullptr
    vector<int> arr = {1, 2, 3, 4, INT_MAX, 6, 7, 8, 9, INT_MAX, INT_MAX, 12, INT_MAX, INT_MAX, 15};
    TreeNodeZH<int> *root = vectorToTreeZH(arr);
    cout << "\n初始化二叉树\n";
    cout << "二叉树的数组表示：\n";
    printVector(arr);
    cout << "二叉树的链表表示：\n";
    bfsPrintTree(root);

    // 数组表示下的二叉树类
    ArrayBinaryTreeZH<int> abt(arr);

    // 访问节点
    int i = 1;
    int l = abt.left(i), r = abt.right(i), p = abt.parent(i);
    cout << "\n当前节点的索引为 " << i << "，值为 " << abt.val(i) << "\n";
    cout << "其左子节点的索引为 " << l << "，值为 " << (l != INT_MAX ? to_string(abt.val(l)) : "nullptr") << "\n";
    cout << "其右子节点的索引为 " << r << "，值为 " << (r != INT_MAX ? to_string(abt.val(r)) : "nullptr") << "\n";
    cout << "其父节点的索引为 " << p << "，值为 " << (p != INT_MAX ? to_string(abt.val(p)) : "nullptr") << "\n";

    // 遍历树
    vector<int> res = abt.levelOrder();
    cout << "\n层序遍历为： ";
    printVector(res);
    res = abt.preOrder();
    cout << "前序遍历为： ";
    printVector(res);
    res = abt.inOrder();
    cout << "中序遍历为： ";
    printVector(res);
    res = abt.postOrder();
    cout << "后序遍历为： ";
    printVector(res);

    return 0;
}