## #include "myvector.h"
This class stores an ordered list of values similar to an array. It supports traditional array selection using square brackets, as well as inserting and removing elements. Operations that access elements by index run in O(1) time. Operations, such as insert and remove, that must rearrange elements run in O(N) time.

| Constructor          |  Complexity   | Description                                                    |
|:---------------------|:-------------:|:---------------------------------------------------------------|
| `MyVector()`         |     O(1)      | Initializes a new empty vector.                                |
| `MyVector(n, value)` |     O(N)      | Initializes a new vector storing n copies of the given value.  |
---
| Methods                             | Complexity | Description                                                                               |
|:------------------------------------|:----------:|:------------------------------------------------------------------------------------------|
| `size()`                            |    O(1)    | Returns the number of elements in this vector.                                            |
| `sort()`                            |  O(NlogN)  | Rearranges the elements in this vector into sorted order.                                 |
| `toString()`                        |    O(N)    | Returns a printable string representation of this vector.                                 |
| `isEmpty()`                         |    O(1)    | Returns true if this vector contains no elements.                                         |
| `clear()`                           |    O(1)    | Removes all elements from this vector.                                                    |
| `equals(vec)`                       |    O(N)    | Returns true if the two vectors contain the same elements in the same order.              |
| `get(index)`                        |    O(1)    | Returns the element at the specified index in this vector.                                |
| `set(index, value)`                 |    O(1)    | Replaces the element at the specified index in this vector with value.                    |
| `insert(index, value)`              |    O(N)    | Inserts **value** into this vector at the specified **index**.                            |
| `remove(index)`                     |    O(N)    | Removes the element at the specified index from this vector.                              |
| `add(value)`                        |    O(1)    | Adds a new value to the end of this vector.                                               |
| `mapAll(fn)`                        |    O(N)    | Calls the specified function on each element of this vector in order of ascending index.  |

---
| Operators                           |  Complexity   | Description                                                             |
|:------------------------------------|:-------------:|:------------------------------------------------------------------------|
| `for (ValueType elem : vec) `       |     O(N)      | Iterates through the elements in a vector in order of ascending index.  |
| `vec[index] `                       |     O(1)      | Overloads [] to select elements from this vector.                       |
| `vec1 = vec2`                       |     O(N)      | Assign the value of vec2 to vec1.                                       |
| `ostream << vec`                    |     O(N)      | Outputs the contents of the vector to the given output stream.          |
| `istream >> vec`                    |     O(N)      | Reads the contents of the given input stream into the vector.           |