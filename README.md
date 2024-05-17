# Mini-mySTL

Mini-mySTL是一个C++标准模板库（STL）的简化实现，包含常见的容器类如 `vector`、`map` 和 `set`。这个项目的目标是帮助学习和理解STL容器的内部工作原理。

## 功能特点

- 实现了 `vector`, `map`, `set` 等常见容器类
- 支持基本的插入、删除、查找等操作
- 提供详细的时间复杂度分析
- 易于理解和扩展

## 容器类列表

- [vector](./vector/myvector.h)
- [hashmap](./hashmap/myhashmap.h)
- [hashset](./hashset/myhashset.h)
- [map](./map/mymap.h)
- [set](./set/myset.h)
- [pqueue](./pqueue/mypqueue.h)

## 复杂度分析

### vector

| 操作     | 时间复杂度 | 空间复杂度 |
|----------|-------------|-------------|
| 插入末尾 | O(1) 均摊   | O(n)        |
| 删除末尾 | O(1)        | O(n)        |
| 随机访问 | O(1)        | O(1)        |
| 查找     | O(n)        | O(1)        |

### hashmap

| 操作     | 时间复杂度 | 空间复杂度 |
|----------|-------------|-------------|
| 插入末尾 | O(1) 均摊   | O(n)        |
| 删除末尾 | O(1)        | O(n)        |
| 随机访问 | O(1)        | O(1)        |
| 查找     | O(n)        | O(1)        |

### hashset

| 操作     | 时间复杂度 | 空间复杂度 |
|----------|-------------|-------------|
| 插入末尾 | O(1) 均摊   | O(n)        |
| 删除末尾 | O(1)        | O(n)        |
| 随机访问 | O(1)        | O(1)        |
| 查找     | O(n)        | O(1)        |

### map

| 操作     | 时间复杂度 | 空间复杂度 |
|----------|-------------|-------------|
| 插入末尾 | O(1) 均摊   | O(n)        |
| 删除末尾 | O(1)        | O(n)        |
| 随机访问 | O(1)        | O(1)        |
| 查找     | O(n)        | O(1)        |

### set

| 操作     | 时间复杂度 | 空间复杂度 |
|----------|-------------|-------------|
| 插入末尾 | O(1) 均摊   | O(n)        |
| 删除末尾 | O(1)        | O(n)        |
| 随机访问 | O(1)        | O(1)        |
| 查找     | O(n)        | O(1)        |


### pqueue

| 操作     | 时间复杂度 | 空间复杂度 |
|----------|-------------|-------------|
| 插入末尾 | O(1) 均摊   | O(n)        |
| 删除末尾 | O(1)        | O(n)        |
| 随机访问 | O(1)        | O(1)        |
| 查找     | O(n)        | O(1)        |

参考：
1. [Stanford CS106B接口](https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/)
