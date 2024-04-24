#ifndef mypqueue_h
#define mypqueue_h

#include <string>
#include <sstream>
/*
 * 该类模拟一种称为优先级队列的结构，其中的值按优先级顺序处理。
 * 与传统的英语用法一样，较低的优先级数字对应较紧急的优先级，因此优先级为 1
 * 的项目优先于优先级为 2 的项目。优先级队列的基本操作是 enqueue（添加指定优先级的值）
 * 和 dequeue（删除最紧急优先级的值）。这两个操作的运行时间都是 O(logN)。
 *
 * 注意：优先级队列不允许通过索引访问元素，也不能使用基于范围的 for 循环遍历元素。
 * ------------------------------------------------------------------
 * 参考：https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/PriorityQueue
 * 更新：
 *      1. 2024.4.11: 第一版
 *
 *
 */

template <typename ValueType>
class MyPQueue {
public:
    /* 构造器
     * 使用：MyPQueue<ValueType> pqueue;
     * --------------------------------
     * 初始化一个新的优先级队列，该队列最初为空。
     *
     */
    MyPQueue();

    /*
     * 析构函数：
     * 使用：隐式调用
     * ------------
     * 释放该类申请的动态内存
     */
    ~MyPQueue();

    /*
     * 方法：clear
     * 使用：pqueue.clear();
     * --------------------
     * 删除优先级队列中的所有元素。
     */
    void clear();


    /*
     * 方法：enqueue
     * 使用：pqueue.enqueue(value, priority);
     * -------------------------------------
     * 以指定的优先级向优先级队列中添加值。
     */
    void enqueue(const ValueType &value, int priority);


    /*
     * 方法：isEmpty
     * 使用：if(pqueue.isEmpty()) . . .
     * -------------------------------
     * 如果优先级队列不包含任何元素，则返回 true。
     */
    bool isEmpty();
    /*
     * 方法：dequeue
     * 使用：pqueue.dequeue();
     * ----------------------
     * 删除并返回最前端（最紧急）的值。
     */
    ValueType dequeue();

    /*
     * 拷贝构造函数和赋值语句
     * ------------------
     * MyPQueue<ValueType> p2 = p1, p3;     // p2使用拷贝构造
     * p3 = p1;                             // p3使用赋值语句
     * ----------------------------------------------------
     * 将属于该类的对象管理的动态内存独立
     */
    MyPQueue (const MyPQueue<ValueType> & src);
    MyPQueue<ValueType> & operator= (const MyPQueue<ValueType> & src);

private:
    static const int INITIAL_CAPACITY = 10;
    struct Cell {
        ValueType value;
        int priority;
    };

    Cell *heap;
    int capacity;
    int entries;

    void deepCopy(const MyPQueue<ValueType> &src);
    /*
     * 向下调整，通常用于dequeue时需要将最后一个元素替换根结点，
     * 此时需要对根结点进行向下调整
     */
    void down(int index);

    /*
     * 向上调整，通常用于enqueue时需要将当前元素放入heap中合适的位置
     * 此时需要对新插入的结点进行向上调整
     */
    void up(int index);

    /*
     * 当heap中内存不够时，需要进行扩容，新的heap空间为
     * 原来空间的两倍。
     */
    void expandCapacity();
};


/*
 * 实现笔记：MyPQueue();
 * -------------------
 * 因为底层使用heap来存储，也就是部分有序树（partially ordered tree）的数组实现，
 * 为了方便从父结点到达子结点，我们默认从下标1开始，这样，假设当前结点下标为u，
 *      左孩子下标为：2*u
 *      右孩子下标为：2*u+1
 */
template <typename ValueType>
MyPQueue<ValueType>::MyPQueue() {
    capacity = INITIAL_CAPACITY;
    heap = new Cell[capacity];
    entries = 0;
}

template <typename ValueType>
MyPQueue<ValueType>::~MyPQueue() {
    delete [] heap;
}


template <typename ValueType>
void MyPQueue<ValueType>::clear() {
    entries = 0;
}

/*
 * 实现笔记：enqueue
 * ---------------
 * 首先将新插入的元素放到heap的末尾，然后根据其
 * 优先级进行向上调整
 */
template <typename ValueType>
void MyPQueue<ValueType>::enqueue(const ValueType &value, int priority) {
    if(entries+1 == capacity) expandCapacity();
    heap[++entries] = {value, priority};
    up(entries);
}

template <typename ValueType>
bool MyPQueue<ValueType>::isEmpty() {
    return entries == 0;
}

/*
 * 实现笔记：dequeue
 * ----------------
 * 因为出队的时候，将优先级最高的元素进行删除操作
 * 也就是heap中的根结点（heap[1]）,所以将最后
 * 一个元素替换根结点后，对根结点进行向下调整，
 * 使得出队完成后，结构仍然满足heap的要求。
 */
template <typename ValueType>
ValueType MyPQueue<ValueType>::dequeue() {
    if(isEmpty()) throw std::out_of_range("queue is empty");

    ValueType result = heap[1].value;
    heap[1] = heap[entries--];
    down(1);
    return result;
}


template <typename ValueType>
MyPQueue<ValueType>::MyPQueue (const MyPQueue<ValueType> & src) {
    deepCopy(src);
}

template <typename ValueType>
MyPQueue<ValueType> & MyPQueue<ValueType>::operator= (const MyPQueue<ValueType> & src) {
    if(this != &src) {
        delete [] heap;
        deepCopy(src);
    }
    return *this;
}

template <typename ValueType>
void MyPQueue<ValueType>::deepCopy(const MyPQueue<ValueType> &src) {
    capacity = src.capacity;
    entries = src.entries;
    heap = new Cell[capacity];
    for(int i = 1; i <= entries; ++i) {
        heap[i] = src.heap[i];
    }
}


/*
 * 实现笔记：down
 * ------------
 * 如果当前结点比其孩子结点中最高优先级要低，则交换当前结点和优先级最高的孩子结点
 * 递归处理优先级最高的孩子结点的位置，类似于向下调整
 */
template <typename ValueType>
void MyPQueue<ValueType>::down(int index) {
    int t = index;
    if(2*index <= entries && heap[2*index].priority < heap[t].priority) t = 2*index;
    if(2*index+1 <= entries && heap[2*index+1].priority < heap[t].priority) t = 2*index+1;

    if(t != index) {
        Cell temp = heap[t];
        heap[t] = heap[index];
        heap[index] = temp;
        down(t);
    }
}

/*
 * 实现笔记：up
 * ----------
 * 如果当前结点的优先级比父结点的优先级低，则将它们交换
 * 然后递归处理父结点的位置，类似于向上调整
 */
template <typename ValueType>
void MyPQueue<ValueType>::up(int index) {
    int t = index;
    if(index/2 >= 1 && heap[t].priority < heap[index/2].priority) t = index/2;
    if(t != index) {
        Cell temp = heap[t];
        heap[t] = heap[index];
        heap[index] = temp;
        up(t);
    }
}

template <typename ValueType>
void MyPQueue<ValueType>::expandCapacity() {
    Cell *oldHeap = heap;

    capacity *= 2;
    heap = new Cell[capacity];
    for(int i = 1; i <= entries; ++i) {
        heap[i] = oldHeap[i];
    }
    delete [] oldHeap;
}

#endif // mypqueue_h
