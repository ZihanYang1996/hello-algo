#include "../utils/common.hpp"

template <typename T>
struct TreeNodeZH
{
    T val{};
    int height{};
    TreeNodeZH<T>* parent{};
    TreeNodeZH<T>* left{};
    TreeNodeZH<T>* right{};

    TreeNodeZH() = default;
    explicit TreeNodeZH(int inVal, TreeNodeZH<T>* parent = nullptr) :
        val{ inVal },
        parent{ parent }
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
            if (i != levelSize - 1)
            {
                cout << ".";
            }

        }
        if (!q.empty())
        {
            cout << "   ";
        }
    }
    cout << endl;
}

template <typename T>
class AVLTree
{
private:
    TreeNodeZH<T>* root;

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

    int height(TreeNodeZH<T>* node)
    {
        return node == nullptr ? -1 : node->height;
    }

    void updateHeight(TreeNodeZH<T>* node)
    {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    int balanceFactor(TreeNodeZH<T>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    TreeNodeZH<T>* rightRotation(TreeNodeZH<T>* node)
    {
        TreeNodeZH<T>* child = node->left;
        TreeNodeZH<T>* grandChild = child->right;

        node->left = grandChild;
        child->right = node;

        // Only need to update height if the node's children changed, and the order should from bottom to top
        updateHeight(node);
        updateHeight(child);

        return child;
    }

    TreeNodeZH<T>* leftRotation(TreeNodeZH<T>* node)
    {
        TreeNodeZH<T>* child = node->right;
        TreeNodeZH<T>* grandChild = child->left;

        node->right = grandChild;
        child->left = node;

        updateHeight(node);
        updateHeight(child);

        return child;
    }

    TreeNodeZH<T>* rotate(TreeNodeZH<T>* node)
    {
        int _balanceFactor = balanceFactor(node);

        // Left-leaning tree
        if (_balanceFactor > 1)
        {
            if (balanceFactor(node->left) >= 0)
            {
                return rightRotation(node);
            }
            else
            {
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
        }
        // Right-leaning tree
        else if (_balanceFactor < -1)
        {
            if (balanceFactor(node->right) <= 0)
            {
                return leftRotation(node);
            }
            else
            {
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
        }

        // Balanced tree, just return the node
        return node;
    }

    // Try improve it by adding flag indicating whether node in serted or not
    TreeNodeZH<T>* insertHelper(TreeNodeZH<T>* node, T val)
    {
        if (node == nullptr)
        {
            return new TreeNodeZH<T>{ val };
        }

        if (val == node->val)
        {
            return node;
        }
        else if (val < node->val)
        {
            node->left = insertHelper(node->left, val);
        }
        else if (val > node->val)
        {
            node->right = insertHelper(node->right, val);
        }

        updateHeight(node);

        node = rotate(node);

        return node;
    }

    TreeNodeZH<T>* removeHelper(TreeNodeZH<T>* node, T val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (val < node->val)
        {
            node->left = removeHelper(node->left, val);
        }
        else if (val > node->val)
        {
            node->right = removeHelper(node->right, val);
        }
        else if (val == node->val)
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                TreeNodeZH<T>* child = node->left == nullptr ? node->right : node->left;
                if (child == nullptr)
                {
                    delete node;
                    return nullptr;
                }
                else
                {
                    delete node;
                    node = child;
                }
            }
            else
            {
                TreeNodeZH<T>* tmpNode = node->right;
                while (tmpNode->left != nullptr)
                {
                    tmpNode = tmpNode->left;
                }
                T tmpVal = tmpNode->val;
                node->right = removeHelper(node->right, tmpVal); //  root, node will also work but node->right is fastest
                node->val = tmpVal;
            }
        }
        updateHeight(node);
        node = rotate(node);

        return node;
    }

    TreeNodeZH<T>* searchHelper(TreeNodeZH<T>* node, T val)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (val < node->val)
        {
            return searchHelper(node->left, val);
        }
        else if (val > node->val)
        {
            return searchHelper(node->right, val);
        }
        else if (val == node->val)
        {
            return node;
        }
    }


public:
    AVLTree() : root{ nullptr } {};

    ~AVLTree()
    {
        freeMemoryTreeZH(root);
    }

    TreeNodeZH<T>* getRoot()
    {
        return root;
    }

    void insert(T val)
    {
        root = insertHelper(root, val);
    }

    void remove(T val)
    {
        root = removeHelper(root, val);
    }

    TreeNodeZH<T>* search(T val)
    {
        return searchHelper(root, val);
    }

};

template <typename T>
void testInsert(AVLTree<T>& tree, int val) {
    tree.insert(val);
    cout << "\n插入节点 " << val << " 后，AVL 树为" << endl;
    bfsPrintTree(tree.getRoot());
}

template <typename T>
void testRemove(AVLTree<T> &tree, int val) {
    tree.remove(val);
    cout << "\n删除节点 " << val << " 后，AVL 树为" << endl;
    bfsPrintTree(tree.getRoot());
}

/* Driver Code */
int main() {
    /* 初始化空 AVL 树 */
    AVLTree<int> avlTree;

    /* 插入节点 */
    // 请关注插入节点后，AVL 树是如何保持平衡的
    testInsert(avlTree, 1);
    testInsert(avlTree, 2);
    testInsert(avlTree, 3);
    testInsert(avlTree, 4);
    testInsert(avlTree, 5);
    testInsert(avlTree, 8);
    testInsert(avlTree, 7);
    testInsert(avlTree, 9);
    testInsert(avlTree, 10);
    testInsert(avlTree, 6);

    /* 插入重复节点 */
    testInsert(avlTree, 7);

    /* 删除节点 */
    // 请关注删除节点后，AVL 树是如何保持平衡的
    testRemove(avlTree, 8); // 删除度为 0 的节点
    testRemove(avlTree, 5); // 删除度为 1 的节点
    testRemove(avlTree, 4); // 删除度为 2 的节点

    /* 查询节点 */
    TreeNodeZH<int> *node = avlTree.search(7);
    cout << "\n查找到的节点对象为 " << node << "，节点值 = " << node->val << endl;
}
