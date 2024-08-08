#include "../utils/common.hpp"
#include "binary_tree_zh.cpp"


template <typename T>
class BinarySearchTreeZH
{
private:
    TreeNodeZH<T>* root;

    enum class Direction
    {
        left,
        right
    };

    void freeMemoryTreeZH(TreeNodeZH<T>* root)
    {
        if (root == nullptr)
        {
            return;
        }
        freeMemoryTreeZH(root->left);
        freeMemoryTreeZH(root->right);
        delete root;
    }

    // Return the node that actually will be deleted for remove()
    // There has to be at least one node within the child tree of inputNode in that direction
    TreeNodeZH<T>* GetNodeTBD(TreeNodeZH<T>* inputNode, Direction dir)
    {
        TreeNodeZH<T>* currNode = inputNode;
        TreeNodeZH<T>* prevNode = nullptr;
        if (dir == Direction::left)
        {
            prevNode = currNode;
            currNode = currNode->left;
            while (currNode != nullptr)
            {
                prevNode = currNode;
                currNode = currNode->right;
            }
        }
        else if (dir == Direction::right)
        {
            prevNode = currNode;
            currNode = currNode->right;
            while (currNode != nullptr)
            {
                prevNode = currNode;
                currNode = currNode->left;
            }
        }
        return prevNode;
    }

public:
    BinarySearchTreeZH() :
        root{ nullptr }
    {}

    ~BinarySearchTreeZH()
    {
        freeMemoryTreeZH(root);
    }

    TreeNodeZH<T>* getRoot()
    {
        return root;
    }

    TreeNodeZH<T>* search(T val)
    {
        TreeNodeZH<T>* searchNode = root;
        while (searchNode != nullptr)
        {
            if (val > searchNode->val)
            {
                searchNode = searchNode->right;
            }
            else if (val < searchNode->val)
            {
                searchNode = searchNode->left;
            }
            else if (val == searchNode->val)
            {
                // Break early, will return searchNode at the end any way.
                break;
            }
        }
        return searchNode;
    }

    void insert(T val)
    {
        // If tree is empty, make the inserted value the root
        if (root == nullptr)
        {
            root = new TreeNodeZH<T>(val);
        }

        TreeNodeZH<T>* currNode = root;
        TreeNodeZH<T>* prevNode = nullptr;

        while (currNode != nullptr)
        {
            if (val == currNode->val)
            {
                return;
            }
            else if (val > currNode->val)
            {
                prevNode = currNode;
                currNode = currNode->right;
            }
            else if (val < currNode->val)
            {
                prevNode = currNode;
                currNode = currNode->left;
            }
        }
        if (val > prevNode->val)
        {
            prevNode->right = new TreeNodeZH<T>(val);
        }
        else
        {
            prevNode->left = new TreeNodeZH<T>(val);
        }
    }

    void remove(T val)
    {
        if (root == nullptr)
        {
            return;
        }

        TreeNodeZH<T>* currNode = root;
        TreeNodeZH<T>* prevNode = nullptr;

        while (currNode != nullptr)
        {
            if (val == currNode->val)
            {
                break;
            }
            else if (val > currNode->val)
            {
                prevNode = currNode;
                currNode = currNode->right;
            }
            else if (val < currNode->val)
            {
                prevNode = currNode;
                currNode = currNode->left;
            }
        }

        if (currNode == nullptr)
        {
            return;
        }

        // If one of the child is nullptr, meaning there's only one child tree
        if (currNode->left == nullptr || currNode->right == nullptr)
        {
            TreeNodeZH<T>* child = currNode->left == nullptr ? currNode->right : currNode->left;
            // currNode is a leaf, simply delete it
            if (currNode == root)
            {
                root = child;
            }
            else
            {
                if (prevNode->left == currNode)
                {
                    prevNode->left = child;
                }
                else if (prevNode->right == currNode)
                {
                    prevNode->right = child;
                }
            }
            delete currNode;
        }
        else
        {
            TreeNodeZH<T>* nodeTBD = GetNodeTBD(currNode, Direction::left);
            T tmpVal = nodeTBD->val;
            // nodeTBD will be leaf node, which falls in previous category so use remove() to delete it
            remove(tmpVal);
            currNode->val = tmpVal;
        }
    }
};

/* Driver Code */
int main() {
    /* 初始化二叉搜索树 */
    BinarySearchTreeZH<int>* bst = new BinarySearchTreeZH<int>();
    // 请注意，不同的插入顺序会生成不同的二叉树，该序列可以生成一个完美二叉树
    vector<int> nums = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    for (int num : nums) {
        bst->insert(num);
    }
    cout << endl << "初始化的二叉树为\n" << endl;
    bfsPrintTree(bst->getRoot());

    /* 查找节点 */
    TreeNodeZH<int>* node = bst->search(7);
    cout << endl << "查找到的节点对象为 " << node << "，节点值 = " << node->val << endl;

    /* 插入节点 */
    bst->insert(16);
    cout << endl << "插入节点 16 后，二叉树为\n" << endl;
    bfsPrintTree(bst->getRoot());

    /* 删除节点 */
    bst->remove(1);
    cout << endl << "删除节点 1 后，二叉树为\n" << endl;
    bfsPrintTree(bst->getRoot());
    bst->remove(2);
    cout << endl << "删除节点 2 后，二叉树为\n" << endl;
    bfsPrintTree(bst->getRoot());
    bst->remove(4);
    cout << endl << "删除节点 4 后，二叉树为\n" << endl;
    bfsPrintTree(bst->getRoot());
    bst->remove(12);
    cout << endl << "删除节点 12 后，二叉树为\n" << endl;
    bfsPrintTree(bst->getRoot());
    bst->remove(8);
    cout << endl << "删除节点 8 后，二叉树为\n" << endl;
    bfsPrintTree(bst->getRoot());
    // 释放内存
    delete bst;

    return 0;
}