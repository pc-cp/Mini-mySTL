/*
 * File: myhashset.h
 * -----------------
 * This interface exports the HashSet class, a collection for storing a set
 * of distince elements.
 */
#ifndef _myhashset_h
#define _myhashset_h

#include <fstream>
#include <iostream>
#include <sstream>
#include "myhashmap.h"
#include "myvector.h"


/*
 * class HashSet<ValueType>
 * ------------------------
 * 该类存储不同元素的集合。该类实现了存储不同元素集合的高效抽象。
 * 除了使用哈希表作为底层表示之外，该类与 Set 类完全相同。HashSet 类的优点是运行时间恒定，
 * 而 Set 类的运行时间为 O(log N)。HashSet 的缺点是，基于范围的 for 循环和其他迭代模式
 * 会以不可预测的、看似随机的顺序访问元素。添加/访问/删除元素的 HashSet 操作运行时间为 O(1)。
 *
 * 参考：https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/HashSet
 * 时间：
 *      1. 2024.4.14: 第一版
 */

template <typename ValueType>
class MyHashSet{
public:
    /*
     * Constructor: MyHashSet
     * Usage: HashSet<ValueType> Set;
     * --------------------------
     * Initializes an empty set of the specified value type.
     */

    MyHashSet();

    /*
     * Destructor: ~MyHashSet
     * ----------------------
     * Frees any heap storage associated with set.
     */
    ~MyHashSet();

    /*
     * Method: size
     * Usage: int count = set.size();
     * ------------------------------
     * Returns the number of elements in this set.
     */
    int size() const;

    /*
     * Method: isEmpty
     * Usage: if(set.isEmpty()) . . .
     * ------------------------------
     * Returns true if this set contains no elements.
     */
    bool isEmpty() const;

    /*
     * Method: add
     * Usage: set.add(value);
     * ----------------------
     * Adds an element to this set if it is not already there.
     */
    void add(const ValueType &value);

    /*
     * Method: remove
     * Usage: set.remove(value);
     * -------------------------
     * Removes an element from this set. If the value was not contained in the
     * set, the set remains unchanged.
     */

    void remove(const ValueType &value);

    /*
     * Method: contains
     * Usage: if(set.contains(value)) . . .
     * ------------------------------------
     * Returns true if the specified value is in this set.
     */
    bool contains(const ValueType &value) const;

    /*
     * Method: difference
     * Usage: set1.difference(set2);
     * -----------------------------
     * Removes from this set all elements that are present in set2.
     * Returns a reference to this set, which has been modified in place.
     *
     * If you want a new set, consider set1 - set2 instead.
     */
    MyHashSet<ValueType> & difference(const MyHashSet<ValueType> &set2);

    /*
     * Method: equals
     * Usage: if (set1.equals(set2)) ...
     * ---------------------------------
     * Returns true if the two sets contain exactly the same element values.
     * Identical in behavior to the == operator.
     */
    bool equals(const MyHashSet<ValueType>& set2) const;

    /*
     * Method: first
     * Usage: ValueType value = set.first();
     * -------------------------------------
     * Returns the first value in the hashset when considered in sorted order.
     * If set is empty, first signals an error.
     */
    ValueType first() const;

    /*
     * Method: intersect
     * Usage: set.intersect(set2);
     * ---------------------------
     * Removes from this set all elements that are not present in set2.
     * Returns a reference to this set, which has been modified in place.
     * If you want a new set, consider set1 * set2 instead.
     */
    MyHashSet<ValueType>& intersect(const MyHashSet<ValueType>& set2);

    /*
     * Method: clear
     * Usage: set.clear();
     * -------------------
     * Removes all elements from this set.
     */
    void clear();

    /*
     * Method: isSubsetOf
     * Usage: if(set.isSubsetOf(set2)) . . .
     * -------------------------------------
     * Implements the subset relation on sets. It returns true if every
     * element of this set is contained in set2.
     */
    bool isSubsetOf(const MyHashSet<ValueType> &set2) const;

    /*
     * Method: isSupersetOf
     * Usage: if (set1.isSupersetOf(set2)) ...
     * ---------------------------------------
     * Returns true if every element of set2 is contained in this set.
     */
    bool isSupersetOf(const MyHashSet<ValueType> & set2) const;

    /*
     * Method: last
     * Usage: ValueType value = set.last();
     * ------------------------------------
     * Returns the last value in the set when considered in sorted order.
     * If set is empty, last signals an error.
     */
    ValueType last() const;
    /*
     * Operator: ==
     * Usage: set1 == set2
     * -------------------
     * Returns true if set1 and set2 contain the same elements.
     */
    bool operator==(const MyHashSet<ValueType> &set2) const;

    /*
     * Operator: !=
     * Usage: set1 != set2
     * -------------------
     * Returns true if set1 and set2 are different.
     */
    bool operator!=(const MyHashSet<ValueType> &set2) const;

    /*
     * Operator: +
     * Usage: set1 + set2
     *        set1 + value
     * -------------------
     * Returns the union of sets set1 and set2, which is the set of elements
     * that appear in at least one of the two sets. The second form returns
     * the set formed by adding a single element.
     */

    MyHashSet<ValueType> operator+(const MyHashSet<ValueType> &set2) const;
    MyHashSet<ValueType> operator+(const ValueType &value) const;

    /*
     * Operator: *
     * Usage: set1 * set2
     * ------------------
     * Returns the intersection of sets set1 and set2, which is the set of all
     * elements that appear in both.
     */

    MyHashSet<ValueType> operator*(const MyHashSet<ValueType> &set2) const;

    /*
     * Operator: -
     * Usage: set1 - set2
     *        set1 - value
     * -------------------
     * Returns the difference of sets set1 and set2, which is all of the
     * elements that appear in set1 but not set2. The second form returns
     * the set formed by removing a single element.
     */

    MyHashSet<ValueType> operator-(const MyHashSet<ValueType> &set2) const;
    MyHashSet<ValueType> operator-(const ValueType &value) const;

    /*
     * Operator: +=
     * Usage: set1 += set2
     *        set1 += value;
     * ---------------------
     * Adds all elements from set2 (or the single specified value) to set1.
     */
    MyHashSet<ValueType> & operator +=(const MyHashSet<ValueType> &set2);
    MyHashSet<ValueType> & operator+=(const ValueType &value);

    /*
     * Operator: *=
     * Usage: set1 *= set2;
     * --------------------
     * Removes any elements from set1 that are not present in set2.
     */
    MyHashSet<ValueType>& operator *= (const MyHashSet<ValueType> &set2);

    /*
     * Operator: -=
     * Usage: set1 -= set2;
     *        set1 -= value;
     * ---------------------
     * Removes all elements from set2 (or a single value) from set1.
     */
    MyHashSet<ValueType>& operator-=(const MyHashSet<ValueType> &set2);
    MyHashSet<ValueType>& operator-=(const ValueType &value);

    /*
     * Method: toString
     * Usage: string str = set.toString();
     * -----------------------------------
     * Returns a printable string representation of this set,
     * such as "{value1, value2, value3}". The values are listed
     * in sorted order.
     */
    std::string toString() const;


    /*
     * Method: unionWith
     * Usage: set1.unionWith(set2);
     * ----------------------------
     * Adds to this set all elements from set2. Returns a reference
     * to this set, which has been modified in place. If you want a
     * new set, consider set1 + set2 instead.
     */
    MyHashSet& unionWith(const MyHashSet<ValueType> & set2);
    /*
     *  deepCopy
     *  copyConstructor and assignment operator
     *  default version is fine, because we have MyMap ~.
     */
    MyHashSet(const MyHashSet<ValueType> &src) = default;
    MyHashSet<ValueType>& operator=(const MyHashSet<ValueType> &src) = default;

    // The private section of the class goes here.

    /*
     * Notes on the representation
     * ---------------------------
     * This implementation of the Set class uses a map as its underlying
     * data structure. The value field in the map is ignored, but is declared
     * as a bool to suggest the presence or absence of a value.
     * The fact that this class is layered on the top of an existing collection
     * makes it substantially easier to implement.
     */
private:
    /* Instance variables */
    MyHashMap<ValueType, bool> map;     // Map used to store the elements

};

// The implementation of the class goes here.

/*
 * Implementation notes: Constructor and destructor
 * ------------------------------------------------
 * The constructor and destructor are empty because the MyMap class manages
 * the underlying representation.
 */
template <typename ValueType>
MyHashSet<ValueType>::MyHashSet() {
    /* Empty */
}

template <typename ValueType>
MyHashSet<ValueType>::~MyHashSet() {
    /* Empty */
}

/*
 * Implementation notes: size, isEmpty, add, remove, contains, clear
 * -----------------------------------------------------------------
 * These methods forward their operation to the underlying MyMap object.
 */

template <typename ValueType>
int MyHashSet<ValueType>::size() const {
    return map.size();
}

template <typename ValueType>
bool MyHashSet<ValueType>::isEmpty() const {
    return map.isEmpty();
}

template <typename ValueType>
void MyHashSet<ValueType>::add(const ValueType &value) {
    map.put(value, true);
}

template <typename ValueType>
void MyHashSet<ValueType>::remove(const ValueType &value) {
    map.remove(value);
}

template <typename ValueType>
bool MyHashSet<ValueType>::contains(const ValueType &value) const {
    return map.containsKey(value);
}

template <typename ValueType>
MyHashSet<ValueType> & MyHashSet<ValueType>::difference(const MyHashSet<ValueType> &set2) {
    return *this -= set2;
}

template <typename ValueType>
bool MyHashSet<ValueType>::equals(const MyHashSet<ValueType>& set2) const {
    return *this == set2;
}

template <typename ValueType>
ValueType MyHashSet<ValueType>::first() const {
    if(isEmpty()) throw std::out_of_range("Set is empty.");
    MyVector<ValueType> values = (this->map).keys();
    return values[0];
}

template <typename ValueType>
MyHashSet<ValueType>& MyHashSet<ValueType>::intersect(const MyHashSet<ValueType>& set2) {
    return (*this) *= set2;
}

template <typename ValueType>
void MyHashSet<ValueType>::clear() {
    map.clear();
}

/*
 * Implementation notes: isSubset
 * ------------------------------
 * This method simply checks to see whether each element of the current
 * set is an element of the second.
 */
template <typename ValueType>
bool MyHashSet<ValueType>::isSubsetOf(const MyHashSet<ValueType> &set2) const {
    MyVector<ValueType> values = (this->map).keys();
    for(int i = 0; i < values.size(); ++i) {
        if(!set2.contains(values[i])) {
            return false;
        }
    }
    return true;
}

template <typename ValueType>
bool MyHashSet<ValueType>::isSupersetOf(const MyHashSet<ValueType> & set2) const {
    return set2.isSubsetOf(*this);
}

template <typename ValueType>
ValueType MyHashSet<ValueType>::last() const {
    if(isEmpty()) throw std::out_of_range("Set is empty.");
    MyVector<ValueType> values = (this->map).keys();
    return values[values.size()-1];
}


/*
 * Implementation notes: operator==, operator!=
 * --------------------------------------------
 * These operators make use of the fact that two sets are equal only
 * if each set is a subset of the other.
 */

template <typename ValueType>
bool MyHashSet<ValueType>::operator == (const MyHashSet<ValueType> &set2) const {
    return isSubsetOf(set2) && set2.isSubsetOf(*this);
}

template <typename ValueType>
bool MyHashSet<ValueType>::operator != (const MyHashSet<ValueType> &set2) const {
    return !((*this) == set2);
}

/*
 * Implementation notes: operator+
 * -------------------------------
 * The union operator copies the first set and then adds the elements
 * from the second to it.
 */
template <typename ValueType>
MyHashSet<ValueType> MyHashSet<ValueType>::operator+ (const MyHashSet<ValueType> &set2) const {

    MyHashSet<ValueType> unionSet = *this;
    MyHashSet<ValueType> difference = set2 - (*this);
    MyVector<ValueType> values = difference.map.keys();
    for(int i = 0; i < values.size(); ++i) {
        unionSet.add(values[i]);
    }
    return unionSet;

}


template <typename ValueType>
MyHashSet<ValueType> MyHashSet<ValueType>::operator+ (const ValueType &value) const {

    MyHashSet<ValueType> unionSet = (*this);
    unionSet.add(value);
    return unionSet;
}

/*
 * Implementation notes: operator*
 * -------------------------------
 * The intersection operator adds elements to an empty set only if they
 * appera in both sets.
 */
template <typename ValueType>
MyHashSet<ValueType> MyHashSet<ValueType>::operator* (const MyHashSet<ValueType> &set2) const {
    MyHashSet<ValueType> intersectionSet;

    MyVector<ValueType> values = (*this).map.keys();
    for(int i = 0; i < values.size(); ++i) {
        if(set2.contains(values[i])) {
            intersectionSet.add(values[i]);
        }
    }
    return intersectionSet;
}

/*
 * Implementation notes: operator-
 * -------------------------------
 * The set difference operator adds elements from the first set only
 * if they do not appear in the second.
 */
template <typename ValueType>
MyHashSet<ValueType> MyHashSet<ValueType>::operator- (const MyHashSet<ValueType> &set2) const {

    MyHashSet<ValueType> differenceSet;
    MyVector<ValueType> values = (*this).map.keys();
    for(int i = 0; i < values.size(); ++i) {
        if(!set2.contains(values[i])) {
            differenceSet.add(values[i]);
        }
    }
    return differenceSet;

}

template <typename ValueType>
MyHashSet<ValueType> MyHashSet<ValueType>::operator- (const ValueType &value) const {
    MyHashSet<ValueType> differenceSet = *this;
    differenceSet.remove(value);
    return differenceSet;
}

/*
 * Implementation notes: shorthand assignment operators
 * ----------------------------------------------------
 * These operators modify the current set but are otherwise similar to
 * the operators that create new sets.
 */
template <typename ValueType>
MyHashSet<ValueType>& MyHashSet<ValueType>::operator+= (const MyHashSet<ValueType> &set2) {
    *this = *this + set2;
    return *this;
}


template <typename ValueType>
MyHashSet<ValueType>& MyHashSet<ValueType>::operator+= (const ValueType &value) {
    *this = *this + value;
    return *this;
}

template <typename ValueType>
MyHashSet<ValueType> & MyHashSet<ValueType>::operator*= (const MyHashSet<ValueType> &set2) {
    *this  = (*this) * set2;
    return *this;
}

template <typename ValueType>
MyHashSet<ValueType> & MyHashSet<ValueType>::operator-= (const MyHashSet<ValueType> &set2) {
    *this = *this - set2;
    return *this;

}

template <typename ValueType>
MyHashSet<ValueType> & MyHashSet<ValueType>::operator-= (const ValueType &value) {
    *this = *this - value;
    return *this;
}


template <typename ValueType>
std::string MyHashSet<ValueType>::toString() const {
    MyVector<ValueType> keys = this->map.keys();
    return keys.toString();
}

template <typename ValueType>
MyHashSet<ValueType> & MyHashSet<ValueType>::unionWith(const MyHashSet<ValueType> & set2) {
    return (*this) += set2;
}



template <typename ValueType>
std::ostream & operator <<(std::ostream & os, const MyHashSet<ValueType> &set) {
    return os << set.toString();
}

template <typename ValueType>
std::istream & operator>> (std::istream &is, MyHashSet<ValueType> &set) {
    MyVector<ValueType> values;
    is >> values;
    for(int i = 0; i < values.size(); ++i) {
        set.add(values[i]);
    }
    return is;
}

#endif //_myhashset_h
