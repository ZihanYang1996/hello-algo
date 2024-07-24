#include "../utils/common.hpp"

template <typename TKey, typename TVal>
struct PairZH
{
public:
    TKey key;
    TVal val;
    PairZH(TKey key, TVal val) :
        key{ key },
        val{ val }
    {}
};

template <typename TKey, typename TVal>
class ArrayHashMapZH
{
private:
    vector<PairZH<TKey, TVal>*> buckets;

public:
    ArrayHashMapZH()
    {
        buckets = vector<PairZH<TKey, TVal>*>(100);
    }

    ~ArrayHashMapZH()
    {
        // Just trying use iterator here, can always use for (const auto& bucket : buckets)
        for (auto iter = buckets.begin(); iter != buckets.end(); iter++)
        {
            delete* iter;
        }

        // for (const auto& bucket : buckets) {
        //     delete bucket;
        // }
        buckets.clear();
    }

    int hashFunc(TKey key)
    {
        int index = static_cast<int>(key) % 100;
        return index;
    }

    TVal get(TKey key)
    {
        int index = hashFunc(key);
        PairZH<TKey, TVal>* pair = buckets[index];
        if (pair == nullptr)
        {
            return TVal{};
        }
        return pair->val;
    }

    void put(TKey key, TVal val)
    {
        int index = hashFunc(key);
        PairZH<TKey, TVal>* pair = new PairZH<TKey, TVal>{key, val};
        buckets[index] = pair;
    }

    void remove(TKey key)
    {
        int index = hashFunc(key);
        delete buckets[index];
        buckets[index] = nullptr;
    }

    vector<PairZH<TKey, TVal>*> pairSet()
    {
        vector<PairZH<TKey, TVal>*> pairSet;
        for (PairZH<TKey, TVal>* pair : buckets)
        {
            if (pair != nullptr)
            {
                pairSet.push_back(pair);
            }
        }
        return pairSet;
    }

    vector<TKey> keySet()
    {
        vector<TKey> keySet;
        for (PairZH<TKey, TVal>* pair : buckets)
        {
            if (pair != nullptr)
            {
                keySet.push_back(pair->key);
            }
        }
        return keySet;
    }

    vector<TVal> valueSet()
    {
        vector<TVal> valueSet;
        for (const auto& pair : buckets)
        {
            if (pair != nullptr)
            {
                valueSet.push_back(pair->val);
            }
        }
        return valueSet;
    }

    void print()
    {
        for (const auto& kv : pairSet())
        {
            cout << kv->key << " -> " << kv->val << endl;
        }
    }
};

/* Driver Code */
int main() {
    /* 初始化哈希表 */
    ArrayHashMapZH<int, string> map = ArrayHashMapZH<int, string>();

    /* 添加操作 */
    // 在哈希表中添加键值对 (key, value)
    map.put(12836, "小哈");
    map.put(15937, "小啰");
    map.put(16750, "小算");
    map.put(13276, "小法");
    map.put(10583, "小鸭");
    cout << "\n添加完成后，哈希表为\nKey -> Value" << endl;
    map.print();

    /* 查询操作 */
    // 向哈希表中输入键 key ，得到值 value
    string name = map.get(15937);
    cout << "\n输入学号 15937 ，查询到姓名 " << name << endl;

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    map.remove(10583);
    cout << "\n删除 10583 后，哈希表为\nKey -> Value" << endl;
    map.print();

    /* 遍历哈希表 */
    cout << "\n遍历键值对 Key->Value" << endl;
    for (auto kv : map.pairSet()) {
        cout << kv->key << " -> " << kv->val << endl;
    }

    cout << "\n单独遍历键 Key" << endl;
    for (auto key : map.keySet()) {
        cout << key << endl;
    }

    cout << "\n单独遍历值 Value" << endl;
    for (auto val : map.valueSet()) {
        cout << val << endl;
    }

    return 0;
}
