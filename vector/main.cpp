#include <iostream>
#include "myvector.h"

void printInt(const int &value) {
    std::cout << value << " ";
}

int main() {
    // Test constructors
    MyVector<int> vec1;
    MyVector<int> vec2(5, 42);

    std::cout << "After initialization:" << std::endl;
    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;

    // Test size, isEmpty, and clear
    std::cout << "vec1 size: " << vec1.size() << std::endl;
    std::cout << "vec1 is empty: " << vec1.isEmpty() << std::endl;

    vec1.add(10);
    vec1.add(20);
    vec1.add(30);

    std::cout << "After adding elements to vec1:" << std::endl;
    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec1 size: " << vec1.size() << std::endl;
    std::cout << "vec1 is empty: " << vec1.isEmpty() << std::endl;

    vec1.clear();
    std::cout << "After clearing vec1:" << std::endl;
    std::cout << "vec1: " << vec1 << std::endl;

    // Test get and set
    vec2.set(1, 99);
    std::cout << "After setting vec2[1] to 99:" << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    std::cout << "vec2[1]: " << vec2.get(1) << std::endl;

    // Test insert and remove
    vec2.insert(2, 55);
    std::cout << "After inserting 55 at index 2 in vec2:" << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;

    vec2.remove(1);
    std::cout << "After removing element at index 1 in vec2:" << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;

    // Test equals
    MyVector<int> vec3(5, 42);
    vec3.set(1, 99);
    vec3.insert(2, 55);
    vec3.remove(1);

    std::cout << "vec3: " << vec3 << std::endl;
    std::cout << "vec2 equals vec3: " << (vec2.equals(vec3) ? "true" : "false") << std::endl;

    // Test toString
    std::cout << "vec2 toString: " << vec2.toString() << std::endl;

    // Test sort
    vec2.add(3);
    vec2.add(7);
    vec2.add(1);
    std::cout << "Before sorting vec2: " << vec2 << std::endl;
    vec2.sort();
    std::cout << "After sorting vec2: " << vec2 << std::endl;

    // Test operator[]
    vec2[0] = 100;
    std::cout << "After setting vec2[0] to 100:" << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    std::cout << "vec2[0]: " << vec2[0] << std::endl;

    // Test mapAll
    std::cout << "Mapping all elements in vec2: ";
    vec2.mapAll(printInt);
    std::cout << std::endl;

    // Test begin and end iterators
    std::cout << "Using iterators to print vec2: ";
    for(auto it = vec2.begin(); it != vec2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test stream operators
    std::cout << "Enter elements for vec1 (comma separated): ";
    std::cin >> vec1;
    std::cout << "vec1 after input: " << vec1 << std::endl;

    for(auto item : vec1) {
        std::cout << item << " ";
    }

    return 0;
}
