#include "../utils/common.hpp"

template <typename Tkey, typename TValue>
void printHashMapZH(const unordered_map<Tkey, TValue>& map)
{
    for (const auto& kv : map)
    {
        cout << kv.first << " -> " << kv.second << endl;
    }
}


int main()
{
    unordered_map<int, string> map;

    map[12836] = "小哈";
    map[15937] = "小啰";
    map[16750] = "小算";
    map[13276] = "小法";
    map[10583] = "小鸭";

    printHashMapZH(map);

    string name = map[15937];
    cout << name << endl;

    map.erase(10583);
    printHashMapZH(map);

    // Using iterator, also avoid unnecessary copy, just like range-based for-loop using const auto&
    for (auto iter = map.begin(); iter != map.end(); iter++)
    {
        cout << iter->first << " -> " << iter->second << endl;
    }

}