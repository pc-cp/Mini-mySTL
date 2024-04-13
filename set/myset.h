/*
 * File: set.h
 * -----------
 * This interface exports the Set class, a collection for storing a set
 * of distince elements.
 */
#ifndef _myset_h
#define _myset_h

#include <fstream>
#include <ostream>
#include "mymap.h"
#include "myvector.h"


/*
 * Class: MySet<ValueType>
 * -----------------------
 * This template class stores a collection of distinct element.
 * 集合内部使用二叉搜索树（BST）结构。由于选择了这种内部表示法，存储在集合中的元素类型的 ValueType
 * 必须通过 less 函数和/或 < 操作符定义自然排序，以便对元素进行比较和排序。
 * 基于范围的 for 循环将按排序顺序遍历元素。添加/查找/删除元素的 Set 操作只需运行 O(logN) 时间。
 * O(logN)的时间复杂度基于BST是平衡的情况下，目前没有保证树的平衡性。
 *
 * 参考：https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/Set
 * 时间：
 *      1. 2024.4.13: 第一版
 */

template <typename ValueType>
class MySet{
public:
    /*
     * Constructor: MySet
     * Usage: Set<ValueType> Set;
     * --------------------------
     * Initializes an empty set of the specified value type.
     */

    MySet();

    /*
     * Destructor: ~Set
     * ----------------
     * Frees any heap storage associated with set.
     */
    ~MySet();

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
    MySet<ValueType> & difference(const MySet<ValueType> &set2);

    /*
     * Method: equals
     * Usage: if (set1.equals(set2)) ...
     * ---------------------------------
     * Returns true if the two sets contain exactly the same element values.
     * Identical in behavior to the == operator.
     */
    bool equals(const MySet<ValueType>& set2) const;

    /*
     * Method: first
     * Usage: ValueType value = set.first();
     * -------------------------------------
     * Returns the first value in the set when considered in sorted order.
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
    MySet<ValueType>& intersect(const MySet<ValueType>& set2);

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
    bool isSubsetOf(const MySet<ValueType> &set2) const;

    /*
     * Method: isSupersetOf
     * Usage: if (set1.isSupersetOf(set2)) ...
     * ---------------------------------------
     * Returns true if every element of set2 is contained in this set.
     */
    bool isSupersetOf(const MySet<ValueType> & set2) const;

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
    bool operator==(const MySet<ValueType> &set2) const;

    /*
     * Operator: !=
     * Usage: set1 != set2
     * -------------------
     * Returns true if set1 and set2 are different.
     */
    bool operator!=(const MySet<ValueType> &set2) const;

    /*
     * Operator: +
     * Usage: set1 + set2
     *        set1 + value
     * -------------------
     * Returns the union of sets set1 and set2, which is the set of elements
     * that appear in at least one of the two sets. The second form returns
     * the set formed by adding a single element.
     */

    MySet<ValueType> operator+(const MySet<ValueType> &set2) const;
    MySet<ValueType> operator+(const ValueType &value) const;

    /*
     * Operator: *
     * Usage: set1 * set2
     * ------------------
     * Returns the intersection of sets set1 and set2, which is the set of all
     * elements that appear in both.
     */

    MySet<ValueType> operator*(const MySet<ValueType> &set2) const;

    /*
     * Operator: -
     * Usage: set1 - set2
     *        set1 - value
     * -------------------
     * Returns the difference of sets set1 and set2, which is all of the
     * elements that appear in set1 but not set2. The second form returns
     * the set formed by removing a single element.
     */

    MySet<ValueType> operator-(const MySet<ValueType> &set2) const;
    MySet<ValueType> operator-(const ValueType &value) const;

    /*
     * Operator: +=
     * Usage: set1 += set2
     *        set1 += value;
     * ---------------------
     * Adds all elements from set2 (or the single specified value) to set1.
     */
    MySet<ValueType> & operator +=(const MySet<ValueType> &set2);
    MySet<ValueType> & operator+=(const ValueType &value);

    /*
     * Operator: *=
     * Usage: set1 *= set2;
     * --------------------
     * Removes any elements from set1 that are not present in set2.
     */
    MySet<ValueType>& operator *= (const MySet<ValueType> &set2);

    /*
     * Operator: -=
     * Usage: set1 -= set2;
     *        set1 -= value;
     * ---------------------
     * Removes all elements from set2 (or a single value) from set1.
     */
    MySet<ValueType>& operator-=(const MySet<ValueType> &set2);
    MySet<ValueType>& operator-=(const ValueType &value);

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
    MySet& unionWith(const MySet<ValueType> & set2);
    /*
     *  deepCopy
     *  copyConstructor and assignment operator
     *  default version is fine, because we have MyMap ~.
     */
    MySet(const MySet<ValueType> &src) = default;
    MySet<ValueType>& operator=(const MySet<ValueType> &src) = default;

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
    MyMap<ValueType, bool> map;     // Map used to store the elements

};

// The implementation of the class goes here.

/*
 * Implementation notes: Constructor and destructor
 * ------------------------------------------------
 * The constructor and destructor are empty because the MyMap class manages
 * the underlying representation.
 */
template <typename ValueType>
MySet<ValueType>::MySet() {
    /* Empty */
}

template <typename ValueType>
MySet<ValueType>::~MySet() {
    /* Empty */
}

/*
 * Implementation notes: size, isEmpty, add, remove, contains, clear
 * -----------------------------------------------------------------
 * These methods forward their operation to the underlying MyMap object.
 */

template <typename ValueType>
int MySet<ValueType>::size() const {
    return map.size();
}

template <typename ValueType>
bool MySet<ValueType>::isEmpty() const {
    return map.isEmpty();
}

template <typename ValueType>
void MySet<ValueType>::add(const ValueType &value) {
    map.put(value, true);
}

template <typename ValueType>
void MySet<ValueType>::remove(const ValueType &value) {
    map.remove(value);
}

template <typename ValueType>
bool MySet<ValueType>::contains(const ValueType &value) const {
    return map.containsKey(value);
}

template <typename ValueType>
MySet<ValueType> & MySet<ValueType>::difference(const MySet<ValueType> &set2) {
    return *this -= set2;
}

template <typename ValueType>
bool MySet<ValueType>::equals(const MySet<ValueType>& set2) const {
    return *this == set2;
}

template <typename ValueType>
ValueType MySet<ValueType>::first() const {
    if(isEmpty()) throw std::out_of_range("Set is empty.");
    MyVector<ValueType> values = (this->map).keys();
    return values[0];
}

template <typename ValueType>
MySet<ValueType>& MySet<ValueType>::intersect(const MySet<ValueType>& set2) {
    return (*this) *= set2;
}

template <typename ValueType>
void MySet<ValueType>::clear() {
    map.clear();
}

/*
 * Implementation notes: isSubset
 * ------------------------------
 * This method simply checks to see whether each element of the current
 * set is an element of the second.
 */
template <typename ValueType>
bool MySet<ValueType>::isSubsetOf(const MySet<ValueType> &set2) const {
    MyVector<ValueType> values = (this->map).keys();
    for(int i = 0; i < values.size(); ++i) {
        if(!set2.contains(values[i])) {
            return false;
        }
    }
    return true;
}

template <typename ValueType>
bool MySet<ValueType>::isSupersetOf(const MySet<ValueType> & set2) const {
    return set2.isSubsetOf(*this);
}

template <typename ValueType>
ValueType MySet<ValueType>::last() const {
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
bool MySet<ValueType>::operator == (const MySet<ValueType> &set2) const {
    return isSubsetOf(set2) && set2.isSubsetOf(*this);
}

template <typename ValueType>
bool MySet<ValueType>::operator != (const MySet<ValueType> &set2) const {
    return !((*this) == set2);
}

/*
 * Implementation notes: operator+
 * -------------------------------
 * The union operator copies the first set and then adds the elements
 * from the second to it.
 */
template <typename ValueType>
MySet<ValueType> MySet<ValueType>::operator+ (const MySet<ValueType> &set2) const {

    MySet<ValueType> unionSet = *this;
    MySet<ValueType> difference = set2 - (*this);
    MyVector<ValueType> values = difference.map.keys();
    for(int i = 0; i < values.size(); ++i) {
        unionSet.add(values[i]);
    }
    return unionSet;

}


template <typename ValueType>
MySet<ValueType> MySet<ValueType>::operator+ (const ValueType &value) const {

    MySet<ValueType> unionSet = (*this);
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
MySet<ValueType> MySet<ValueType>::operator* (const MySet<ValueType> &set2) const {
    MySet<ValueType> intersectionSet;

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
MySet<ValueType> MySet<ValueType>::operator- (const MySet<ValueType> &set2) const {

    MySet<ValueType> differenceSet;
    MyVector<ValueType> values = (*this).map.keys();
    for(int i = 0; i < values.size(); ++i) {
        if(!set2.contains(values[i])) {
            differenceSet.add(values[i]);
        }
    }
    return differenceSet;

}

template <typename ValueType>
MySet<ValueType> MySet<ValueType>::operator- (const ValueType &value) const {
    MySet<ValueType> differenceSet = *this;
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
MySet<ValueType>& MySet<ValueType>::operator+= (const MySet<ValueType> &set2) {
    *this = *this + set2;
    return *this;
}


template <typename ValueType>
MySet<ValueType>& MySet<ValueType>::operator+= (const ValueType &value) {
    *this = *this + value;
    return *this;
}

template <typename ValueType>
MySet<ValueType> & MySet<ValueType>::operator*= (const MySet<ValueType> &set2) {
    *this  = (*this) * set2;
    return *this;
}

template <typename ValueType>
MySet<ValueType> & MySet<ValueType>::operator-= (const MySet<ValueType> &set2) {
    *this = *this - set2;
    return *this;

}

template <typename ValueType>
MySet<ValueType> & MySet<ValueType>::operator-= (const ValueType &value) {
    *this = *this - value;
    return *this;
}


template <typename ValueType>
std::string MySet<ValueType>::toString() const {
    MyVector<ValueType> keys = this->map.keys();
    return keys.toString();
}

template <typename ValueType>
MySet<ValueType> & MySet<ValueType>::unionWith(const MySet<ValueType> & set2) {
    return (*this) += set2;
}



template <typename ValueType>
std::ostream & operator <<(std::ostream & os, const MySet<ValueType> &set) {
    return os << set.toString();
}



#endif //_myset_h
