#ifndef _mymap_h
#define _mymap_h

#include <string>
#include <sstream>
#include "myvector.h"
/*
 * 映射内部使用二叉搜索树（BST）结构。由于选择了这种内部表示法，因此存储在 Map 中的键的 KeyType
 * 必须通过 less 函数和/或 < 运算符定义自然排序，以便键可以被比较和排序。
 * ValueType 不需要提供任何此类自然排序。基于范围的 for 循环将按排序顺序遍历映射键。
 * 添加/访问/删除条目的映射操作将在 O(logN) 时间内完成。
 * ---------------------------------------------
 * 参考：https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/Map
 * 更新：
 *      1. 2024.4.9: 第一版
 *      2. 2024.4.10: 修复bug：remove方法删除后仅仅修改了key，而没有修改value
 *
              remove this->   (1,"D")                             X(0,"D") vlaue值没有改变
                             /     \                              /     \
                          (0,"A")  (3,"C")     vlaue值没有改变X(-1,"A")  (3,"C")
                          /        /     \                              /     \
                       (-1,"B")  (2,"E") (5,"F")                      (2,"E") (5,"F")

                 下面是正确的：
                        (0,"A")
                        /     \
                   (-1,"B")  (3,"C")
                             /     \
                           (2,"E") (5,"F")
 *
 *      3. 2024.4.13: 修改了 void inOrder(TreeNode *root, std::ostringstream &os) const;
 *                    将它变成更通用的
 *                          void inOrder(TreeNode *root, MyVector<std::pair<KeyType, ValueType>> &res) const;

                      这样bool equals(const MyMap<KeyType, ValueType>& map) const;就不需要
                      bool equalsRec(const TreeNode *lhs, const TreeNode *rhs) const;
                      尽管我原先是为了使MyMap对MySet更加支持 bool isSubsetOf(const MySet<ValueType> &set2) const;
                      为了实现MySet，或许添加 keys() 和 values() 是美好的
 */

template <typename KeyType, typename ValueType>
class MyMap{
public:
    /*
     * 构造函数：MyMap
     * 使用： MyMap map;
     * ----------------
     * 初始化一个新的空 map，将指定类型的键和值关联起来。
     */
    MyMap();

    /*
     * 方法： ~MyMap
     * 使用：隐式调用
     * ------------
     * 将内部的BST的heap区内存释放
     */
    ~MyMap();

    /*
     * 方法：clear
     * 使用：map.clear();
     * -----------------
     * 将BST设置为空
     */
    void clear();

    /* 方法：containsKey
     * 使用：if(map.containsKey(key)) . . .
     * -----------------------------------
     * 检查map中是否含有键为key的key-value对
     */
    bool containsKey(const KeyType &key) const;

    /*
     * 方法：equals
     * 使用：if(map.equals(map2)) . . .
     * -------------------------------
     * 检查两个map是否相等
     */
    bool equals(const MyMap<KeyType, ValueType>& map) const;

    /*
     * 方法： get
     * 使用：ValueType value = map.get(key);
     * ------------------------------------
     * 返回map中键为key对应的value。如果没有这个key，则返回“”
     */
    ValueType get(const KeyType &key) const;

    /*
     * 方法：isEmpty
     * 使用：if(map.isEmpty()) . . .
     * ----------------------------
     * 检查map是否为空
     */
    bool isEmpty() const;

    /*
     * Method: keys
     * Usage: MyVector<KeyType> vec = map.keys();
     * ------------------------------------------
     * Returns a Vector copy of all keys in this map.
     * The keys will appear in the same order that a
     * for-each loop over the map would produce them.
     * Because a map cannot contain duplicate keys,
     * the elements of the vector will be unique.
     */
    MyVector<KeyType> keys() const;

    /*
     * 方法：put
     * 使用：map.put(key, value);
     * -------------------------
     * 将map中键为key的value更新
     */
    void put(const KeyType &key, const ValueType &value);

    /*
     * 方法：remove
     * 使用：map.remove(key);
     * ---------------------
     * 移除map中键为key的key-value对
     */
    void remove(const KeyType &key);

    /*
     * 方法：size
     * 使用：int count = map.size();
     * ----------------------------
     * 返回map中key-value对的数量
     */
    int size() const;

    /*
     * 方法：toString
     * 使用：cout << map.toString() << endl;
     * ------------------------------------
     * 将map中的key-value以string类型返回
     */
    std::string toString() const;


    /*
     * Method: values
     * Usage: MyVector<ValueType> vec = map.values();
     * ----------------------------------------------
     * Returns a Vector copy of all values in this map.
     * The values will appear in the same order that a for-each
     * loop over the map would produce them.
     * A map can contain duplicate values, so the elements
     * of the vector are not guaranteed to be unique.
     */
    MyVector<ValueType> values() const;

    /*
     * 运算符： []
     * 使用：ValueType value = map[key];
     * --------------------------------
     * 返回键为key对应的value，通过这种语法，我们可以很容易地将 map 视为一个以 key 类型
     * 为索引的 "关联数组"。如果 key 已经存在于 map 中，该函数将返回其关联值的引用。
     * 如果 map 中没有 key，则会创建一个新条目，其值将设置为值类型的默认值。
     */
    ValueType & operator [] (const KeyType &key);

    /*
     * 运算符： []
     * 使用：ValueType value = map[key];
     * --------------------------------
     * 返回键为key对应的value，通过这种语法，我们可以很容易地将 map 视为一个以 key 类型
     * 为索引的 "关联数组"。如果 key 已经存在于 map 中，该函数将返回其关联值的引用。
     *
     * 注意：如果 map 中没有 key，仅仅返回valueType的默认值而不改变map本身。
     */
    const ValueType operator [] (const KeyType &key) const;

    /*
     * 拷贝构造函数和赋值操作符
     * 使用：
     *      MyMap<KeyType, ValueType> mm2 = mm1, mm3;   // 这里mm2使用了拷贝构造函数而非默认构造函数
     *      mm3 = mm2;  // 这里mm3使用了赋值操作符
     * ----------------------------------------
     * 因为MyMap内部维护一个动态内存分配的BST，所以需要 覆盖 默认的拷贝构造函数和赋值操作符以进行深拷贝
     */
    MyMap(const MyMap<KeyType, ValueType> &src);
    MyMap<KeyType, ValueType>& operator= (const MyMap<KeyType, ValueType> &src);

private:
    struct TreeNode {
        KeyType key;
        ValueType value;

        TreeNode *left;
        TreeNode *right;
    };

    TreeNode *root;     // BST
    int entries;        // BST中key-value对的数量

    /*
     * 方法：deepCopy，deepCopyRec
     * 使用：deepCopy(map);
     *      deepCopyRec(map.root);
     * ---------------------------
     * 构造一棵和src一样的BST
     * 其中deepCopy是deepCopyRec的wrapper函数
     */
    void deepCopy(const MyMap<KeyType, ValueType> &src);
    void deepCopyRec(const TreeNode *rhs);

    /*
     * 方法：findTreeNode
     * 使用：TreeNode *cp = findTreeNode(map.root, key);
     * ------------------------------------------------
     * 在map中查找键为key的结点，因为这里可能需要插入和移除
     * 所以返回类型为引用以改变map中BST当前结点
     */
    TreeNode * &findTreeNode(TreeNode *&root, const KeyType &key);
    /*
     * 方法：isExist
     * 使用：TreeNode* cp = isExist(map.root, key);
     * -------------------------------------------
     * 因为像get方法为const限定，所以无法使用像findTreeNode这类会修改BST的方法（非const限定）
     * 所以该方法可以看作是findTreeNode的const限定版本
     */
    TreeNode* isExist(TreeNode *root, const KeyType &key) const;
    /*
     * 方法：deleteTree;
     * 使用：deleteTree(map.root);
     * --------------------------
     * 使用后序遍历(PostOrder)来释放BST的内存
     */
    void deleteTree(TreeNode *root);


    /*
     * 方法：rightMostNodeInLeftSubTree
     * 使用：TreeNode* cp = rightMostNodeInLeftSubTree(root);
     * -----------------------------------------------------
     * 在remove方法中，可能会遇到删除内部结点（非叶子结点）情况，此时
     * 需要结合该结点的孩子数量来进行删除：
     *  1. 若该结点没有孩子，则直接将其替换成nullptr
     *  2. 若该结点有一个孩子：
     *      1. 若为左孩子，则用左子树的最右侧结点替换该结点，然后删除该最右侧结点
     *      2. 若为右孩子，则用右子树的最左侧结点替换该结点，然后删除该最左侧结点
     *  3. 若该结点有两个孩子：
     *      我们约定用左子树的最右侧结点替换该结点，然后删除该最右侧结点（个人偏好）
     */
    TreeNode* rightMostNodeInLeftSubTree(TreeNode *root);

    TreeNode* leftMostNodeInRightSubTree(TreeNode *root);
    /*
     * 方法：inOrder
     * 使用：inOrder(map.root, os);
     * ---------------------------
     * 因为toString需要遍历整个BST，同时保持key的有序，所以使用
     * 该函数进行遍历，并且将输出存入在ostream对象内
     */
    void inOrder(TreeNode *root, MyVector<std::pair<KeyType, ValueType>> &res) const;
};


template <typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::MyMap() {
    root = nullptr;
    entries = 0;
}

template <typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::~MyMap() {
    clear();
}

/*
 * 实现笔记：clear
 * -------------
 * 最后需要将root设置为nullptr，否则导致root为悬挂指针会带来安全隐患。
 */
template <typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear() {
    deleteTree(root);
    root = nullptr;
}

template <typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::containsKey(const KeyType &key) const {
    TreeNode *cp = isExist(root, key);
    return cp != nullptr;
}


template <typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::equals(const MyMap<KeyType, ValueType> &map) const {
    MyVector<std::pair<KeyType, ValueType>> inOrder1, inOrder2;
    inOrder(this->root, inOrder1);
    inOrder(map.root, inOrder2);
    if(inOrder1.size() != inOrder2.size()) {
        return false;
    }
    for(int i = 0; i < inOrder1.size(); ++i) {
        if(inOrder1[i].first != inOrder2[i].first || inOrder1[i].second != inOrder2[i].second) {
            return false;
        }
    }
    return true;
}

template <typename KeyType, typename ValueType>
ValueType MyMap<KeyType, ValueType>::get(const KeyType& key) const {
    TreeNode* cp = isExist(root, key);
    return (cp == nullptr) ? "" : cp->value;
}

template <typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::isEmpty() const {
    return entries == 0;
}

template <typename KeyType, typename ValueType>
MyVector<KeyType> MyMap<KeyType, ValueType>::keys() const {
    MyVector<KeyType> res;

    MyVector<std::pair<KeyType, ValueType>> inOrder1;
    inOrder(this->root, inOrder1);
    for(int i = 0; i < inOrder1.size(); ++i) {
        res.add(inOrder1[i].first);
    }
    return res;
}

/*
 * 实现笔记： put
 * ------------
 * 这里有趣的在于    TreeNode *&cp = findTreeNode(root, key);
 * 如果cp不是引用的话，修改cp不会修改BST。
 */
template <typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::put(const KeyType &key, const ValueType &value){
    TreeNode *&cp = findTreeNode(root, key);
    if(cp == nullptr) {
        cp = new TreeNode;
        cp->key = key;
        cp->left = cp->right = nullptr;
        entries++;
    }
    cp->value = value;
}

/*
 * 实现笔记：remove
 * -----------------------------------------------------
 * 在remove方法中，可能会遇到删除内部结点（非叶子结点）情况，此时
 * 需要结合该结点的孩子数量来进行删除：
 *  1. 若该结点没有孩子，则直接将其替换成nullptr
 *  2. 若该结点有一个孩子：
 *      1. 若为左孩子，则用左子树的最右侧结点替换该结点，然后删除该最右侧结点
 *      2. 若为右孩子，则用右子树的最左侧结点替换该结点，然后删除该最左侧结点
 *  3. 若该结点有两个孩子：
 *      我们约定用左子树的最右侧结点替换该结点，然后删除该最右侧结点（个人偏好）
 *  注意：递归～～
 */
template <typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::remove(const KeyType &key) {
    TreeNode *&cp = findTreeNode(root, key);
    if(cp != nullptr) {
        // 1. 该结点没有孩子
        if(cp->left == nullptr && cp->right == nullptr) {
            delete cp;
            cp = nullptr;
            entries--;
        }

        else {
            // 该结点有左孩子（只有左孩子或者是有两个孩子）
            if(cp->left) {
                TreeNode *rightMostNode = rightMostNodeInLeftSubTree(cp->left);
                std::pair<KeyType, ValueType> rightMostNodeInfo(rightMostNode->key, rightMostNode->value);
                remove(rightMostNodeInfo.first);
                cp->key = rightMostNodeInfo.first;
                cp->value = rightMostNodeInfo.second;
            }
            // 该结点仅有右孩子
            else {
                TreeNode *leftMostNode = leftMostNodeInRightSubTree(cp->right);
                std::pair<KeyType, ValueType> leftMostNodeInfo(leftMostNode->key, leftMostNode->value);
                remove(leftMostNodeInfo.first);
                cp->key = leftMostNodeInfo.first;
                cp->value = leftMostNodeInfo.second;
            }
        }
    }
}

template <typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::size() const {
    return entries;
}

template <typename KeyType, typename ValueType>
std::string MyMap<KeyType, ValueType>::toString() const {
    std::ostringstream os;
    MyVector<std::pair<KeyType, ValueType>> inOrderResult;
    inOrder(this->root, inOrderResult);
    for(int i = 0; i < inOrderResult.size(); ++i) {
        if(os.str() != "") {
            os << ", ";
        }
        os << "{" << inOrderResult[i].first << ": " << inOrderResult[i].second << "}";
    }

    return os.str();
}

template <typename KeyType, typename ValueType>
MyVector<ValueType> MyMap<KeyType, ValueType>::values() const {
    MyVector<ValueType> res;

    MyVector<std::pair<KeyType, ValueType>> inOrder1;
    inOrder(this->root, inOrder1);
    for(int i = 0; i < inOrder1.size(); ++i) {
        res.add(inOrder1[i].second);
    }
    return res;
}


/*
 * 实现笔记：operator<<
 * ------------------
 * 返回必须是stream的引用，因为stream不可拷贝
 */
template <typename KeyType, typename ValueType>
std::ostream& operator << (std::ostream &os, const MyMap<KeyType, ValueType> &map) {
    return os << map.toString();
}

template <typename KeyType, typename ValueType>
ValueType & MyMap<KeyType, ValueType>::operator [] (const KeyType &key) {
    TreeNode *&cp = findTreeNode(root, key);
    if(cp == nullptr) {
        cp = new TreeNode;
        cp->key = key;
        cp->value = ValueType();
        cp->left = cp->right = nullptr;
        entries++;
    }
    return cp->value;
}

template <typename KeyType, typename ValueType>
const ValueType MyMap<KeyType, ValueType>::operator [] (const KeyType &key) const {
    TreeNode *cp = isExist(root, key);
    if(cp == nullptr) {
        // throw std::out_of_range("Key does not exist.");
        return ValueType();
    }
    return cp->value;
}


template <typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::MyMap(const MyMap<KeyType, ValueType> &src) {
    root = nullptr;
    entries = 0;
    deepCopy(src);
}

template <typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>& MyMap<KeyType, ValueType>::operator= (const MyMap<KeyType, ValueType> &src) {
    if(this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}


template <typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::deepCopy(const MyMap<KeyType, ValueType> &src) {
    deepCopyRec(src.root);
}


template <typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::deepCopyRec(const TreeNode *rhs) {
    if(rhs != nullptr) {
        put(rhs->key, rhs->value);
        deepCopyRec(rhs->left);
        deepCopyRec(rhs->right);
    }
}



template <typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::inOrder(TreeNode *root, MyVector<std::pair<KeyType, ValueType>> &res) const{
    if(root == nullptr) {
        return ;
    }
    else {
        inOrder(root->left, res);
        res.add(std::pair<KeyType, ValueType>(root->key, root->value));
        inOrder(root->right, res);
    }
}



template <typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::deleteTree(TreeNode *root) {
    if(root == nullptr) {
        return ;
    }
    else {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        entries--;
    }
}


template <typename KeyType, typename ValueType>
typename MyMap<KeyType, ValueType>::TreeNode* MyMap<KeyType, ValueType>::rightMostNodeInLeftSubTree(TreeNode *root) {
    if(root->right) {
        return rightMostNodeInLeftSubTree(root->right);
    }
    else {
        return root;
    }
}

template <typename KeyType, typename ValueType>
typename MyMap<KeyType, ValueType>::TreeNode* MyMap<KeyType, ValueType>::leftMostNodeInRightSubTree(TreeNode *root) {
    if(root->left) {
        return leftMostNodeInRightSubTree(root->left);
    }
    else {
        return root;
    }
}



template <typename KeyType, typename ValueType>

/*
 * 实现笔记：findTreeNode
 * --------------------
 * 返回引用使得像put和remove方法可以修改BST生效。
 */
typename MyMap<KeyType, ValueType>::TreeNode *& MyMap<KeyType, ValueType>::findTreeNode(TreeNode *&root, const KeyType &key) {
    if(root == nullptr) {
        return root;
    }

    else {
        if(key == root->key) {
            return root;
        }
        else if(key < root->key) {
            return findTreeNode(root->left, key);
        }
        else {
            return findTreeNode(root->right, key);
        }
    }
}

template <typename KeyType, typename ValueType>
typename MyMap<KeyType, ValueType>::TreeNode *  MyMap<KeyType, ValueType>::isExist(TreeNode *root, const KeyType &key) const {
    if(root == nullptr) {
        return root;
    }

    else {
        if(key == root->key) {
            return root;
        }
        else if(key < root->key) {
            return isExist(root->left, key);
        }
        else {
            return isExist(root->right, key);
        }
    }
}

#endif //_mymap_h
