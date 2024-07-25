#include "../utils/common.hpp"

template <typename TKey, typename TVal>
struct PairZH
{
    TKey key;
    TVal val;
    PairZH(TKey key, TVal val) :
        key{ key },
        val{ val }
    {}
};

template <typename TKey, typename TVal>
class HashMapChainingZH
{
private:
    int size;
    int capacity;
    double loadThres;
    int extendRatio;
    vector<vector<PairZH<TKey, TVal>*>> buckets;

public:
    HashMapChainingZH() :
        size{ 0 },
        capacity{ 4 },
        loadThres{ 2.0 / 3.0 },
        extendRatio{ 2 }
    {
        buckets.resize(capacity);
    }

    ~HashMapChainingZH()
    {
        for (auto& bucket : buckets)
        {
            for (const auto& pair : bucket)
            {
                delete pair;
            }
        }
    }

    int hashFunc(TKey key)
    {
        int index = static_cast<int>(key) % capacity;
        return index;
    }

    double loadFactor()
    {
        return static_cast<double>(size) / static_cast<double>(capacity);
    }

    TVal get(TKey key)
    {
        int index = hashFunc(key);
        for (const auto& pair : buckets[index])
        {
            if (pair->key == key)
            {
                return pair->val;
            }
        }
        return TVal{};
    }

    void put(TKey key, TVal val)
    {
        if (loadFactor() > loadThres)
        {
            extend();
        }

        int index = hashFunc(key);
        for (auto& pair : buckets[index])
        {
            if (pair->key == key)
            {
                pair->val = val;
                return;
            }
        }
        buckets[index].push_back(new PairZH<TKey, TVal>(key, val));
        size++;
    }

    void remove(TKey key)
    {
        int index = hashFunc(key);
        auto& bucket = buckets[index];
        for (int i = 0; i < bucket.size(); i++)
        {
            delete bucket[i];
            bucket.erase(bucket.begin() + i);
            size--;
            return;
        }
    }

    void extend()
    {
        vector<vector<PairZH<TKey, TVal>*>> tempBuckets = buckets;

        capacity *= extendRatio;
        buckets.clear();
        buckets.resize(capacity);
        size = 0;

        for (auto& tempBucket : tempBuckets)
        {
            for (auto& pair : tempBucket)
            {
                put(pair->key, pair->val);
                delete pair;
            }
        }
    }

    void print()
    {
        for (auto& bucket : buckets)
        {
            cout << "[";
            for (auto& pair : bucket)
            {
                cout << pair->key << " -> " << pair->val << ", ";
            }
            cout << "]" << endl;
        }
    }
};

/* Driver Code */
int main() {
    /* 初始化哈希表 */
    HashMapChainingZH<int, string> map = HashMapChainingZH<int, string>();
    // map.get(3);

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
    string name = map.get(13276);
    cout << "\n输入学号 13276 ，查询到姓名 " << name << endl;

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    map.remove(12836);
    cout << "\n删除 12836 后，哈希表为\nKey -> Value" << endl;
    map.print();

    return 0;
}