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
class HashMapOpenAddressingZH
{
private:
    int size;
    int capacity;
    const double loadThres = 2.0 / 3.0;
    const int extendRatio = 2;
    vector<PairZH<TKey, TVal>*> buckets;
    PairZH<TKey, TVal>* TOMBSTONE = new PairZH<TKey, TVal>(static_cast<TKey>(static_cast<int>(TKey()) - 1), TVal());

public:
    HashMapOpenAddressingZH() :
        size(0),
        capacity(4),
        buckets(capacity, nullptr)
    {}

    ~HashMapOpenAddressingZH()
    {
        for (const auto& pair : buckets)
        {
            if (pair != nullptr && pair != TOMBSTONE)
            {
                delete pair;
            }
        }
        delete TOMBSTONE;
        cout << "HashMapOpenAddressingZH has been successfully destructed" << endl;
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

    int findBucket(TKey key)
    {
        int index = hashFunc(key);

        int firstTombstone = -1;

        while (buckets[index] != nullptr)
        {
            if (buckets[index]->key == key)
            {
                // If there was Tombstone before current index, move the pair at index to where the Tombstone is, and assign this index Tombstone
                if (firstTombstone != -1)
                {
                    buckets[firstTombstone] = buckets[index];
                    buckets[index] = TOMBSTONE;
                    return firstTombstone;
                }
                return index;
            }
            if ((firstTombstone == -1) && (buckets[index] == TOMBSTONE))
            {
                firstTombstone = index;
            }
            // loop index back to begining
            index = (index + 1) % capacity;
        }

        return firstTombstone == -1 ? index : firstTombstone;
    }

    TVal get(TKey key)
    {
        int index = findBucket(key);
        if (buckets[index] != nullptr && buckets[index] != TOMBSTONE)
        {
            return buckets[index]->val;
        }
        else
        {
            return TVal{};
        }

    }

    void put(TKey key, TVal val)
    {
        if (loadFactor() > loadThres)
        {
            extend();
        }

        int index = findBucket(key);
        if (buckets[index] != nullptr && buckets[index] != TOMBSTONE)
        {
            buckets[index]->val;
        }
        else
        {
            PairZH<TKey, TVal>* pair = new PairZH<TKey, TVal>{ key, val };
            buckets[index] = pair;
            size++;
        }
    }

    void remove(TKey key)
    {
        int index = findBucket(key);
        if (buckets[index] != nullptr && buckets[index] != TOMBSTONE)
        {
            delete buckets[index];
            buckets[index] = TOMBSTONE;
            size--;
        }
    }

    void extend()
    {
        capacity *= extendRatio;
        vector<PairZH<TKey, TVal>*> bucketsTmp = buckets;
        buckets = vector<PairZH<TKey, TVal>*>(capacity, nullptr);
        size = 0;

        for (const auto& pairTmp : bucketsTmp)
        {
            if (pairTmp != nullptr && pairTmp != TOMBSTONE)
            {
                put(pairTmp->key, pairTmp->val);
                delete pairTmp;
            }
        }
    }
    
    void print()
    {
        for (const auto& pair : buckets)
        {
            if (pair == nullptr)
            {
                cout << "nullptr" << endl;
            }
            else if (pair == TOMBSTONE)
            {
                cout << "TOMBSTONE" << endl;
            }
            else
            {
                cout << pair->key << " -> " << pair->val << endl;
            }
        }
    }
};

int main() {
    // 初始化哈希表
    HashMapOpenAddressingZH<int, string> hashmap;

    // 添加操作
    // 在哈希表中添加键值对 (key, val)
    hashmap.put(12836, "小哈");
    hashmap.put(15937, "小啰");
    hashmap.put(16750, "小算");
    hashmap.put(13276, "小法");
    hashmap.put(10583, "小鸭");
    cout << "\n添加完成后，哈希表为\nKey -> Value" << endl;
    hashmap.print();

    // 查询操作
    // 向哈希表中输入键 key ，得到值 val
    string name = hashmap.get(13276);
    cout << "\n输入学号 13276 ，查询到姓名 " << name << endl;

    // 删除操作
    // 在哈希表中删除键值对 (key, val)
    hashmap.remove(16750);
    cout << "\n删除 16750 后，哈希表为\nKey -> Value" << endl;
    hashmap.print();

    return 0;
}