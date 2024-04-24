#ifndef _myhashmap_h
#define _myhashmap_h

#include <string>
#include <sstream>
#include "myhashcode.h"
#include "myvector.h"
/*
 * 该类实现了key与value之间的高效关联。该类与 stanford HashMap 类的接口几乎相同，
 * 它使用哈希表作为底层表示同时维持一个负载系数，这使得它能在 O(1) 平均时间内运行。
 *
 * MyHashMap 的缺点是基于范围的 for 循环和其他迭代模式会以不可预测和看似随机的顺序访问key。
 * MyHashMap 添加/访问/删除条目的操作只需 O(1) 。
 * -----------------------------------------
 * 参考: https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/HashMap#Method:toString
 * 更新：
 *      1. 2024.4.8：重写并添加中文注释
 *      2. 2024.4.14：添加"myvector.h" 以实现keys(), values()
 *      3. 2024.4.24: 添加mapAll支持callback函数
 */
template <typename KeyType, typename ValueType>
class MyHashMap {
public:
    /*
     * 方法：MyHashMap
     * 使用: MyHashMy<KeyType, ValueType> mhp;
     * ------------------
     * 默认构造函数
     */
    MyHashMap();

    /*
     * 方法：～MyHashMap
     * 使用：隐式调用
     * -------------
     * 自动释放stack区的内存以及手动释放heap pool区的内存
     */
    ~MyHashMap();

    /*
     * 方法：get
     * 使用: ValueType key = map.get(key);
     * ----------------------------------
     * 返回此hashmap中与 key 相关的value。
     */
    ValueType get(const KeyType &key) const;

    /*
     * 方法：isEmpty
     * 使用：if (map.isEmpty()) ...
     * ---------------------------
     * 如果hashmap中没有key-value对返回true
     */
    bool isEmpty() const;


    /*
     * Method: keys;
     * Usage: MyVector<KeyType> keys = map.keys();
     * -------------------------------------------
     * Returns a Vector copy of all keys in this map.
     * The keys will appear in the same order that a for-each loop
     * over the map would produce them. Because a map cannot contain duplicate keys,
     * the elements of the vector will be unique.
     */
    MyVector<KeyType> keys() const;

    /*
     * 方法：put
     * 使用：map.put(key, value);
     * -------------------------
     * 将value与此hashmap中的key关联。与 key 关联的任何先前value都会被新value替换。
     */
    void put(const KeyType &key, const ValueType &value);

    /*
     * 方法：remove
     * 使用：hashmap.remove(key);
     * -------------------------
     * 删除hashmap中键为key对应的key-value对
     */

    void remove(const KeyType &key);

    /*
     * 方法：size
     * 使用：int nEntries = map.size();
     * -------------------------------
     * 返回此map中key-value对的数量
     */
    int size() const;

    /*
     * 方法：clear
     * 使用：map.clear();
     * -----------------
     * 清空map上的所有key-value对。
     */
    void clear();

    /*
     * 方法：containsKey
     * 使用：if (map.containsKey(key)) ...
     * ----------------------------------
     * 如果此map中有 key 的条目，则返回 true。
     */
    bool containsKey(const KeyType &key) const;

    /*
     * 方法：equals
     * 使用：if (map1.equals(map2)) ...
     * -------------------------------
     * 判断两个map是否含有相同的key-value对
     */
    bool equals(const MyHashMap<KeyType, ValueType> &src) const;

    /*
     * 方法：toString
     * 使用：string str = map.toString();
     * --------------------------------
     * 返回此map的可打印字符串，如"{k1:v1, k2:v2, k3:v3}"。key/value对 将以不可预测的顺序列出。
     */

    std::string toString() const;

    /*
     * Method: values
     * Usage: MyVector<ValueType> values = map.values();
     * -------------------------------------------------
     * Returns a Vector copy of all values in this map. The values will appear in the
     * same order that a for-each loop over the map would produce them. A map can contain
     * duplicate values, so the elements of the vector are not guaranteed to be unique.
     */
    MyVector<ValueType> values() const;


    /*
     * 拷贝构造函数和赋值操作符进行deepCopy
     * 使用: MyHashMap<KeyType, ValueType> map2 = map1, map3;     // 此处map2使用拷贝构造函数
     *      map3 = map1;                                         // 此处map3使用赋值语句
     * ---------------------------------
     */
    MyHashMap(const MyHashMap<KeyType, ValueType> &src);
    MyHashMap<KeyType, ValueType> &operator= (const MyHashMap<KeyType, ValueType> &src);

    /*
     * 重载运算符[]
     * 使用：MyHashMap<KeyType, ValueType> map;
     *      map[key] = "value";
     * ---------------------------------------
     * 选择与 key 关联的value。通过这种语法，我们可以很容易地把 map
     * 看成是一个以 key 类型为索引的 "关联数组"。如果 key 已经存在于 map 中，
     * 该函数将返回其关联值的引用。如果 key 不在 map 中，则会创建一个新条目，
     * 其value将设置为值类型的默认值。
     * 注意：返回值应为 ValueType &，因为可能需要修改map[key]。
     *
     * 一个const限定的对象仅能调用其const限定的member functions。
     * 一个类可以根据constness来对其member functions进行重载。
     * 在这种情况下，仅有const限定的object可以调用const版本的member function，
     * 其他情况的object调用non-const member function。
     */
    ValueType & operator[] (const KeyType &key);

    const ValueType operator[] (const KeyType &key) const;

    /*
     * 重载运算符==
     * 使用： if(hmp1 == hmp2) {
     *          cout << "hmp1 == hmp2" << endl;
     *       }
     * ----------------------------------------
     * 因为equals目的与其相同，所以看作该重载是equals的wrapper函数。
     */
    bool operator == (const MyHashMap<KeyType, ValueType> &hmp2) const;
    bool operator != (const MyHashMap<KeyType, ValueType> &hmp2) const;

    /* 类的私有部分*/
    /*
     * 关于内部表示的说明
     * ---------------
     * 该版本的 HashMap 类使用哈希表，将键值对保存在一个桶数组中，
     * 每个桶都是一个所有相同hash Code对应key-value的链接列表，这些key散列到该桶。
     */

    /*
     * Method: mapAll
     * Usage: map.mapAll(fn);
     * ----------------------
     * Iterates through the map entries and calls fn(key, value) for each one.
     * The entries are processed in unpredictable order.
     */
    void mapAll(void (*fn) (const KeyType &, const ValueType &)) const;
private:

    /* 散列表中类型的定义（拉链法） */

    struct Cell {
        KeyType key;
        ValueType value;
        Cell *link;
    };

    /* 负载系数声明 */
    static const double REHASH_THRESHOLD;
    /* 初始散列表的长度 */
    static const int INITIAL_BUCKET_COUNT = 10;

    /* 实例变量 */
    Cell **buckets;         // Dynamic array of pointers to cells
    int nBuckets;           // The number of buckets in the array
    int entries;

    /* 方法：findCell
     * 使用：Cell *cp = findCell(bucket, key);
     * --------------------------------------
     * 在散列表中第bucket个篮子里搜索键为key的结构体Cell，
     * 如果存在键为key的Cell，则返回该Cell的地址，
     * 反之返回NULL。
     */
    Cell * findCell(int bucket, const KeyType &key) const;

    /*
     * 方法：rehashing
     * 使用：if(size()*1.0/nBuckets > REHASH_THRESHOLD) {
     *          rehashing();
     *      }
     * ---------------------------------------------------
     * 如果负载系数超过阈值（REHASH_THRESHOLD），则需要重新扩大指针数组的长度（篮子）的数量以维持
     * 散列表操作（查找、删除、插入）的性能。
     */
    void rehashing();

    /*
     * 方法：deepCopy
     * 使用：deepCopy(src);
     * -------------------
     * 用定义过的hashmap初始化一个新的hashmap或者hashmap之间进行赋值时，
     * 因为每个hashmap维护一个动态内存分配的散列表，所以需要进行深拷贝使得每个
     * hashmap之间管理的散列表独立。
     */
    void deepCopy(const MyHashMap<KeyType, ValueType> &src);

    /*
     * 方法：sequentialTraversal
     * 使用：sequentialTraversal(traversalResult);
     * --------------------------
     * 像keys()和values()需要得到hashTable中所有的keys和values
     * 所以这里通过下标 顺序遍历 buckets这个指针数组。将{key: value}
     * 放入traversalResult中
     */
    void sequentialTraversal(MyVector<std::pair<KeyType, ValueType>> &vec) const;
};


/* 负载系数初始化 */
template <typename KeyType, typename ValueType>
const double MyHashMap<KeyType, ValueType>::REHASH_THRESHOLD = 0.7;

template <typename KeyType, typename ValueType>
MyHashMap<KeyType, ValueType>::MyHashMap() {
    entries = 0;
    nBuckets = INITIAL_BUCKET_COUNT;
    buckets = new Cell* [nBuckets];
    for(int i = 0; i < nBuckets; ++i) {
        buckets[i] = NULL;
    }
}

/*
 * 实现笔记：~MyHashMap
 * ------------------
 * 遍历整个指针数组，然后对每个指针指向的链表进行单独释放内存。
 * 因为链表中的Cell在heap内存中的区域是离散分布的。因为
 * 这个方法的调用暗示着该对象不再使用，所以像私有变量
 * entries、nBuckets无需维护。
 */
template <typename KeyType, typename ValueType>
MyHashMap<KeyType, ValueType>::~MyHashMap() {
    for(int i = 0; i < nBuckets; ++i) {
        Cell *p = buckets[i];
        Cell *q = NULL;

        while(p) {
            q = p->link;
            delete p;
            p = q;
        }
    }
}

template <typename KeyType, typename ValueType>
ValueType MyHashMap<KeyType, ValueType>::get(const KeyType &key) const {
    int bucket = hashCode(key) % nBuckets;
    Cell *cp = findCell(bucket, key);
    return (cp == NULL) ? "" : cp->value;
}

template <typename KeyType, typename ValueType>
bool MyHashMap<KeyType, ValueType>::isEmpty() const {
    return entries == 0;
}

template <typename KeyType, typename ValueType>
MyVector<KeyType> MyHashMap<KeyType, ValueType>::keys() const {
    MyVector<std::pair<KeyType, ValueType>> keysAndValues;
    sequentialTraversal(keysAndValues);

    MyVector<KeyType> keys;
    for(int i = 0; i < keysAndValues.size(); ++i) {
        keys.add(keysAndValues[i].first);
    }
    return keys;
}

template <typename KeyType, typename ValueType>
void MyHashMap<KeyType, ValueType>::sequentialTraversal(MyVector<std::pair<KeyType, ValueType>> &vec) const {
    for(int i = 0; i < nBuckets; ++i) {
        Cell *cp = buckets[i];
        while(cp) {
            vec.add({cp->key, cp->value});
            cp = cp->link;
        }
    }
}

/*
 * 实现笔记：put
 * -----------
 * 将key-value对存储在hash Table中，首先对key进行查找，
 * 如果表中已经存在key，则用参数value更新。反之使用头插法
 * 将key-value插入到hash Table中。注意维护key-value数量的变量entries需要+1
 *
 * 注意，如果添加key-value后，负载系数超过阈值，则需要重新hashing。
 */
template <typename KeyType, typename ValueType>
void MyHashMap<KeyType, ValueType>::put(const KeyType &key, const ValueType &value) {
    int bucket = hashCode(key) % nBuckets;
    Cell *cp = findCell(bucket, key);
    if(cp == NULL) {
        cp = new Cell;
        cp->key = key;
        cp->link = buckets[bucket];
        buckets[bucket] = cp;
        entries ++;
    }
    cp->value = value;

    if(size()*1.0/nBuckets > REHASH_THRESHOLD) {
        rehashing();
    }
}

/*
 * 实现笔记：remove
 * --------------
 * 首先查找key对应的结构体Cell的地址cp
 * 如果cp不为空，从该key对应的链表头查找cp前一个Cell r
 * 如果cp为头结点，则将头指针指向下一个结点
 * 反之查找cp的前一个结点地址r，将r下一个结点指向cp的下一个结点
 * 删除结点cp，同时更新私有变量entries
 */
template <typename KeyType, typename ValueType>
void MyHashMap<KeyType, ValueType>::remove(const KeyType &key) {
    int bucket = hashCode(key) % nBuckets;
    Cell *cp = findCell(bucket, key);
    if(cp != NULL) {
        Cell *r = buckets[bucket];
        if(r == cp) {
            buckets[bucket] = buckets[bucket]->link;
        }
        else {
            while(r->link->key != cp->key) {
                r = r->link;
            }
            r->link = cp->link;
        }
        delete cp;
        entries--;
    }
}


template <typename KeyType, typename ValueType>
int MyHashMap<KeyType, ValueType>::size() const {
    return entries;
}

/*
 * 实现笔记：clear
 * -------------
 * 将hash Table中所有的key-value对删除
 * 注意需要将指针数组中每个元素指向NULL。
 * 同时更新相应的私有变量entries，因为clear操作
 * 后可能重新使用该对象。
 */
template <typename KeyType, typename ValueType>
void MyHashMap<KeyType, ValueType>::clear() {
    for(int i = 0; i < nBuckets; ++i) {
        Cell *cp = buckets[i];
        Cell *q = NULL;
        while(cp) {
            q = cp->link;
            delete cp;
            entries --;
            cp = q;
        }
        buckets[i] = NULL; // miss will lead error.
    }
}

template <typename KeyType, typename ValueType>
bool MyHashMap<KeyType, ValueType>::containsKey(const KeyType &key) const {
    int bucket = hashCode(key) % nBuckets;
    Cell *cp = findCell(bucket, key);
    return cp != NULL;
}

template <typename KeyType, typename ValueType>
bool MyHashMap<KeyType, ValueType>::equals(const MyHashMap<KeyType, ValueType> &other) const {
    if(size() != other.size() || nBuckets != other.nBuckets) {
        return false;
    }

    Cell *pThis, *pOther;
    for(int i = 0; i < nBuckets; ++i) {
        pThis = buckets[i], pOther = other.buckets[i];
        while(pThis || pOther) {
            if(!pThis || !pOther) return false;
            if(pThis->key != pOther->key || pThis->value != pOther->value) return false;
            pThis = pThis->link;
            pOther = pOther->link;
        }
    }
    return true;
}


/*
 * 使用字符串输出流ostringstream来将key-value转换成字符串表示
 * 然后使用ostringstream的str()方法作为返回值
 * ostringstream的官方文档：https://en.cppreference.com/w/cpp/io/basic_ostringstream
 * 注意：这个实现要求KeyType和ValueType支持插入操作符(<<)。
 */
template <typename KeyType, typename ValueType>
std::string MyHashMap<KeyType, ValueType>::toString() const{
    std::ostringstream oss;

    Cell *cp = NULL;
    for(int i = 0; i < nBuckets; ++i) {
        cp = buckets[i];
        while(cp) {
            oss << "{" << cp->key << ": " << cp->value << "}";
            cp = cp->link;
        }
    }
    return oss.str();
}

template <typename KeyType, typename ValueType>
MyVector<ValueType> MyHashMap<KeyType, ValueType>::values() const {
    MyVector<std::pair<KeyType, ValueType>> keysAndValues;
    sequentialTraversal(keysAndValues);

    MyVector<ValueType> values;
    for(int i = 0; i < keysAndValues.size(); ++i) {
        values.add(keysAndValues[i].second);
    }
    return values;
}

/*
 * 实现笔记：operator<<
 * -------------------
 * 利用MyHashMap中的方法toString()使得插入操作符支持类MyHashMap
 */
template <typename KeyType, typename ValueType>
std::ostream & operator<< (std::ostream &os, const MyHashMap<KeyType, ValueType> & hashmap) {
    return os << hashmap.toString();
}

template <typename KeyType, typename ValueType>
typename MyHashMap<KeyType, ValueType>::Cell * MyHashMap<KeyType, ValueType>::findCell(int bucket, const KeyType &key) const {
    Cell *p = buckets[bucket];
    while(p && p->key != key) {
        p = p->link;
    }

    return p;
}

/*
 * 实现笔记：rehashing
 * -----------------
 * 将hash Table中指针数组的长度增加一倍
 * 并将原来的key-value对重新hash，因为
 * 数组长度变化导致之前的key对应的hash Code
 * 变化，如果不重新hash的话，则之前的key-value
 * 无法查找到。
 *
 * 注意：需要将原来的heap内存释放掉。
 */
template <typename KeyType, typename ValueType>
void MyHashMap<KeyType, ValueType>::rehashing() {
    int oldNBuckets = nBuckets;
    Cell **oldBuckets = buckets;

    entries = 0;
    nBuckets *= 2;
    buckets = new Cell* [nBuckets];

    for(int i = 0; i < nBuckets; ++i) {
        buckets[i] = NULL;
    }

    for(int i = 0; i < oldNBuckets; ++i) {
        Cell *p = oldBuckets[i];
        Cell *r = nullptr;
        while(p) {
            r = p->link;
            this->put(p->key, p->value);
            delete p;
            p = r;
        }
    }
}

template <typename KeyType, typename ValueType>
MyHashMap<KeyType, ValueType>::MyHashMap(const MyHashMap<KeyType, ValueType> &src) {
    deepCopy(src);
}

template <typename KeyType, typename ValueType>
MyHashMap<KeyType, ValueType>& MyHashMap<KeyType, ValueType>::operator =(const MyHashMap<KeyType, ValueType> &src) {
    if(this != &src) {
        // free old heap storage
        clear();
        delete [] buckets;
        nBuckets = 0;

        // deepCopying
        deepCopy(src);
    }
    return *this;
}

template <typename KeyType, typename ValueType>
void MyHashMap<KeyType, ValueType>::deepCopy(const MyHashMap<KeyType, ValueType> &src) {
    nBuckets = src.nBuckets;
    entries = src.entries;
    buckets = new Cell* [nBuckets];
    for(int i = 0; i < nBuckets; ++i) {
        buckets[i] = NULL;
    }

    for(int i = 0; i < nBuckets; ++i) {
        Cell *p = src.buckets[i];
        Cell *q = buckets[i];
        while(p) {
            Cell *tmp = new Cell;
            tmp->key = p->key;
            tmp->value = p->value;
            tmp->link = NULL;

            if(buckets[i] == NULL) {
                buckets[i] = tmp;
            }
            else {
                q->link = tmp;
            }

            q = tmp;
            p = p->link;
        }
    }

}

/*
 * 实现笔记： operator[]
 * -------------------
 * 实现此操作符可以将hashmap抽象成key-value的关联数组，
 * 注意：如果key不存在，则该操作会自动创建该key，其value为
 * 默认值。
 */
template <typename KeyType, typename ValueType>
ValueType & MyHashMap<KeyType, ValueType>::operator[] (const KeyType &key) {

    int bucket = hashCode(key) % nBuckets;

    Cell *cp = findCell(bucket, key);
    if(cp == NULL) {
        cp = new Cell;
        cp->key = key;
        cp->value = ValueType ();
        cp->link = buckets[bucket];
        buckets[bucket] = cp;
        entries ++;
    }
    return cp->value;
}

/*
 * 实现笔记： operator[]
 * -------------------
 * 根据方法的constness实现此操作符可以将hashmap抽象成key-value的关联数组，
 * 注意：如果key不存在，则什么都不发生
 */
template <typename KeyType, typename ValueType>
const ValueType MyHashMap<KeyType, ValueType>::operator[] (const KeyType &key) const{

    int bucket = hashCode(key) % nBuckets;

    Cell *cp = findCell(bucket, key);
    if(cp == NULL) {
        // throw std::out_of_range("Key does not exist.");
        return ValueType();
    }
    else {
        return cp->value;
    }
}

template <typename KeyType, typename ValueType>
bool MyHashMap<KeyType, ValueType>::operator == (const MyHashMap<KeyType, ValueType> &hmp2) const {
    return this->equals(hmp2);
}

template <typename KeyType, typename ValueType>
bool MyHashMap<KeyType, ValueType>::operator != (const MyHashMap<KeyType, ValueType> &hmp2) const {
    return !(*this == hmp2);
}

template <typename KeyType, typename ValueType>
void MyHashMap<KeyType, ValueType>::mapAll(void (*fn) (const KeyType &, const ValueType &)) const {
    for(int bucket = 0; bucket < nBuckets; ++bucket) {
        Cell *temp = buckets[bucket];
        while(temp != nullptr) {
            fn(temp->key, temp->value);
            temp = temp->link;
        }
    }
}

#endif // _myhashmap_h
