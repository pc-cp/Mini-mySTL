/*
 * File: myvector.h
 * ----------------
 * 该类存储类似于数组的一个有序的值列表。它支持像传统数组一样使用方括号选择，以及插入和删除元素。
 * 通过索引访问元素的操作运行时间为 O(1)。如插入和移除，必须重新排列元素的操作，运行时间为 O(N)。
 * -------------------------------------------------------------------------------
 * 参考：https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/Vector.html
 * 时间：
 *      1. 2024.4.12: 第一版
 *
 */

#ifndef _myvector_h
#define _myvector_h
#include <sstream>
#include <ostream>

template <typename ValueType>
class MyVector {
public:
    /*
     * Constructor: MyVector
     * Usage: MyVector<ValueType> vec;
     *        MyVector<ValueType> vec(n, value);
     * -----------------------------------------
     * Initializes a new Vector object. The first form creates an empty vector;
     * the second creates a Vector of size n in which each element is initialized
     * to the specified value or the default value for the element type.
     */

    MyVector();
    MyVector(int n, ValueType value = ValueType());


    /*
     * Destructor: ~MyVector
     * Usage: (usually implicit)
     * -------------------------
     * Frees any heap storage allocated by this vector.
     */

    ~MyVector();

    /*
     * Method: size
     * Usage: int n = vec.size();
     * --------------------------
     * Returns the number of values in this vector.
     */

    int size() const;

    /*
     * Method: sort;
     * Usage: vec.sort();
     * ------------------
     * Rearrange the elements in this vector into sorted order.
     * Elements are compared using the < operator.
     *
     * In sorted order, the minimum element is placed at index 0;
     * the maximum is at index size()-1.
     */
    void sort();

    /*
     * Method: toString
     * Usage: vec.toString();
     * ----------------------
     * Returns a printable string representation of this vector,
     * such as "{value1, value2, value3}".
     */
    std::string toString() const;

    /*
     * Method: isEmpty();
     * Usage: if(vec.isEmpty()) . . .
     * ------------------------------
     * Returns true if this vector contains no elements.
     */

    bool isEmpty() const;

    /*
     * Method: clear
     * Usage: vec.clear();
     * -------------------
     * Removes all elements from this vector.
     */
    void clear();

    /*
     * Method: equals
     * Usage: if(vec1.equals(vec2)) . . .
     * ----------------------------------
     * Returns true if the two vectors contain exactly the
     * same element values in the same order.
     *
     * Identical in behavior to the == operator.
     */
    bool equals(const MyVector<ValueType>& v) const;

    /*
     * Method: get
     * Usage: ValueType value = vec.get(index);
     * ----------------------------------------
     * Returns the element at the specified index in this vector. This method
     * signals an error if the index is not in the array index.
     */
    ValueType get(int index) const;

    /*
     * Method: set
     * Usage: vec.set(index, value);
     * -----------------------------
     * Replaces the element at the specified index in this vector with a new
     * value. The previous value at that index is overwritten. This method
     * signals an error if the index is not in the array range.
     */

    void set(int index, ValueType value);

    /*
     * Method: insert
     * Usage: vec.insert(index, value);
     * ----------------------------
     * Inserts the element into this vector before the specified index. All
     * subsequent elements are shifted one position to the right. This method
     * signals an error if the index is outside the range from 0 up to end
     * including the length of the vector.
     */

    void insert(int index, ValueType value);

    /*
     * Method: remove
     * Usage: vec.remove(index);
     * -------------------------
     * Removes the element at the specified from this vector. All
     * subsequent elements are shifted one position to the left. This
     * method signals an error if the index is outside the array range.
     */
    void remove(int index);

    /*
     * Method: add
     * Usage: vec.add(value);
     * ----------------------
     * Adds a new value to the end of this vector.
     */

    void add(ValueType value);

    /*
     * Operator: []
     * Usage: vec[index]
     * -----------------
     * Overloads [] to select elements from this vector. This extension
     * enables the use of traditional array notation to get or set individual
     * elements. This method signals an error if the index is outside the
     * array range.
     *
     * The file supports two versions of this operator,
     * one for const vectors and one for mutable vectors.
     */

    ValueType & operator[] (int index);
    const ValueType& operator[](int index) const;

    /*
     * Copy constructor and assignment operator
     * ----------------------------------------
     * These methods implement deep copying for vectors.
     */
    MyVector(const MyVector<ValueType> &src);
    MyVector<ValueType> & operator=(const MyVector<ValueType> &src);

    /*
     * Private section
     * Notes on the representation
     * ---------------------------
     * This version of the vector.h interface stores the elements in a
     * dynamic array of the specified element type. If the space in the
     * array is ever exhausted, the implementation doubles the array capacity.
     */

private:
    static const int INITIAL_CAPACITY = 10;

    ValueType *array;
    int capacity;
    int count;

    void deepCopy(const MyVector<ValueType> &src);
    void expandCapacity();

    void heapSort();
    void down(int index, int size);


};

/*
 * Implementation notes: MyVector constructor and deconstructor
 * ------------------------------------------------------------
 * The two implementations of the constructor each allocate storage for
 * the dynamic array and then initialize the other fields of the object.
 * The destructor frees the heap memory used by the dynamic array.
 */

template <typename ValueType>
MyVector<ValueType>::MyVector() {
    capacity = INITIAL_CAPACITY;
    array = new ValueType[capacity];
    count = 0;
}

template <typename ValueType>
MyVector<ValueType>::MyVector(int n, ValueType value) {
    capacity = n;
    array = new ValueType[capacity];
    for(int i = 0; i < capacity; ++i) {
        array[i] = value;
    }
    count = capacity;
}


template <typename ValueType>
MyVector<ValueType>::~MyVector() {
    delete [] array;
}

/*
 * Implementation notes: size, isEmpty, clear
 * ------------------------------------------
 * These methods require only the count field and do not look at the data.
 */
template <typename ValueType>
int MyVector<ValueType>::size() const {
    return count;
}

/*
 * Implementation notes: sort
 * --------------------------
 * Use heapSort to rearrange the elements in this vector into sorted order.
 */
template <typename ValueType>
void MyVector<ValueType>::sort() {
    if(isEmpty()) return ;
    insert(0, -1);
    heapSort();
    remove(0);
}

template <typename ValueType>
void MyVector<ValueType>::heapSort() {
    int size = count-1;
    for(int i = size/2; i >= 1; i--) down(i, size);

    while(size) {
        ValueType temp = array[1];
        array[1] = array[size];
        array[size] = temp;

        size--;
        down(1, size);
    }
}

template <typename ValueType>
void MyVector<ValueType>::down(int u, int size) {
    int t = u;
    if(2*u <= size && array[2*u] > array[t]) t = 2*u;
    if(2*u+1 <= size && array[2*u+1] > array[t]) t = 2*u+1;
    if(t != u) {
        ValueType temp = array[t];
        array[t] = array[u];
        array[u] = temp;
        down(t, size);
    }
}

template <typename ValueType>
std::string MyVector<ValueType>::toString() const {
    std::ostringstream oss;
    oss << "{";
    for(int i = 0; i < count; ++i) {
        if(i) {
            oss << ", ";
        }
        oss << (*this)[i];
    }
    oss << "}";
    return oss.str();
}


template <typename ValueType>
bool MyVector<ValueType>::isEmpty() const {
    return count == 0;
}

template <typename ValueType>
void MyVector<ValueType>::clear() {
    count = 0;
}

template <typename ValueType>
bool MyVector<ValueType>::equals(const MyVector& v) const {
    if(count != v.count) return false;
    for(int i = 0; i < count; ++i) {
        if((*this)[i] != v[i]) return false;
    }
    return true;
}


/*
 * Implementation notes: get, set
 * ------------------------------
 * These methods first test that the index is in range and then get or set
 * the appropriate index position in the dynamic array.
 */
template <typename ValueType>
ValueType MyVector<ValueType>::get(int index) const {
    if(!(index >= 0 && index < count)) throw std::out_of_range("get: the index is not in the array index.");
    return array[index];
}

template <typename ValueType>
void MyVector<ValueType>::set(int index, ValueType value) {
    if(!(index >= 0 && index < count)) throw std::out_of_range("set: the index is not in the array index.");

    array[index] = value;
}

/*
 * Implementation notes: add, insert, remove
 * -----------------------------------------
 * These methods must shift the existing elements in the array to make
 * room for a new element or to close up the space left by a deleted one.
 */
template <typename ValueType>
void MyVector<ValueType>::insert(int index, ValueType value) {
    if(!(index >= 0 && index <= count)) throw std::out_of_range("insert: the index is not in the array index.");
    if(count == capacity) expandCapacity();
    for(int i = count; i > index; i--) {
        array[i] = array[i-1];
    }
    array[index] = value;
    count++;
}


template <typename ValueType>
void MyVector<ValueType>::remove(int index) {
    if(!(index >= 0 && index < count)) throw std::out_of_range("remove: the index is not in the array index.");
    for(int i = index; i < count-1; i ++) {
        array[i] = array[i+1];
    }
    count--;
}

template <typename ValueType>
void MyVector<ValueType>::add(ValueType value) {
    insert(count, value);
}

/*
 * Implementation notes: MyVector selection
 * ----------------------------------------
 * The following code implements traditional array selection using square
 * brackets for the index. To ensure that clients can assign to array
 * elements, this method uses an & to return the result by reference.
 */
template <typename ValueType>
ValueType& MyVector<ValueType>::operator [](int index) {
    if(!(index >= 0 && index < count)) throw std::out_of_range("operator []: the index is not in the array index.");
    return array[index];
}

template <typename ValueType>
const ValueType& MyVector<ValueType>::operator[](int index) const {
    if(!(index >= 0 && index < count)) throw std::out_of_range("operator []: the index is not in the array index.");
    return array[index];
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * These methods follow the standard template, leaving the work to deepCopy.
 */
template <typename ValueType>
MyVector<ValueType>::MyVector(const MyVector<ValueType> &src) {
    deepCopy(src);
}

template <typename ValueType>
MyVector<ValueType> & MyVector<ValueType>::operator =(const MyVector<ValueType> &src) {
    if(this != &src) {
        delete [] array;
        deepCopy(src);
    }
    return *this;
}

/*
 * Implementation notes: deepCopy
 * ------------------------------
 * Copies the data from the src parameter into the current object.
 * All dynamic memory is reallocated to create a "deep copy" in
 * which the current object and the source object are independent.
 *
 */
template <typename ValueType>
void MyVector<ValueType>::deepCopy(const MyVector<ValueType> &src) {
    capacity = src.capacity;
    count = src.count;
    array = new ValueType[capacity];
    for(int i = 0; i < count; ++i) {
        array[i] = src.array[i];
    }
}

/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This method doubles the array capacity whenever it runs out of space.
 */
template <typename ValueType>
void MyVector<ValueType>::expandCapacity() {
    ValueType * oldArray = array;

    capacity *= 2;
    array = new ValueType[capacity];
    for(int i = 0; i < count; ++i) {
        array[i] = oldArray[i];
    }
    delete [] oldArray;
}

template <typename ValueType>
std::ostream& operator << (std::ostream& os, const MyVector<ValueType> &vec) {
    return os << vec.toString();
}

#endif
