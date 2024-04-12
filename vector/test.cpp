// #include <iostream>
// #include <cassert>
// #include "myvector.h"
// using namespace std;

// int main() {

//     MyVector<int> vec1, vec2(10, 1), vec3(9);

//     assert(vec1.size() == 0);
//     assert(vec1.isEmpty());
//     assert(!vec3.isEmpty());

//     vec2.clear();

//     vec1 = vec3;
//     vec2 = MyVector<int>(2, 11);
//     vec1[2] = 111;
//     assert(vec1[2] == 111);

//     vec1.remove(2);
//     assert(vec1.size() == 8);
//     assert(vec1[2] == 0);

//     vec1.add(99);
//     assert(vec1.size() == 9);
//     assert(vec1[8] == 99);
//     assert(vec1[2] == 0);
//     vec1[8] = 999;
//     assert(vec1[8] == 999);


//     MyVector<int> vec;
//     vec.add(8); vec.add(3); vec.add(1); vec.add(4); vec.add(2); vec.add(7);
//     cout << vec << endl;

//     vec.sort();
//     cout << vec << endl;
//     cout << vec[2] << endl;
//     // cout << vec[10] << endl; // throw std::out_of_range("operator []: the index is not in the array index.");
//     cout << "class MyVector is pass unit test successfully." << endl;
//     return 0;
// }
