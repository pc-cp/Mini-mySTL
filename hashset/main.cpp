#include "myhashset.h"
#include "myvector.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    MyHashSet<char> s1, s2, s3;
    // {a, b, c}
    s1.add('a');
    s1.add('b');
    s1.add('c');

    // {a, b, d}
    s2.add('b');
    s2.add('a');
    s2.add('d');

    // {a, b, c, d}
    // cout << s1 + s2 << endl;
    // {a, b}
    // cout << s1 * s2 << endl;
    // {c}
    // cout << s1 - s2 << endl;

    // {c}
    s3 = s1 - s2;
    // cout << s3 << endl;

    assert(s3.isSubsetOf(s1));
    assert(!s3.isSubsetOf(s2));
    // {a, b, c, d}
    s3 += s2;
    // cout << s3 << endl;
    // {a, b, d}
    s3 *= s2;
    // cout << s3 << endl;

    // {d}
    s3.difference(s1);
    // cout << s3 << endl;

    // {a, b, c}
    s3 = s1;
    // cout << s3 << endl;
    assert(s3.equals(s1));
    assert(s3 == s1);
    assert(s3.first() == 'a');

    // {a, b}
    s3 *= s2;
    // cout << s3 << endl;

    // {a, b}
    s3.intersect(s1);
    // cout << s3 << endl;
    assert(s3.isSubsetOf(s2));
    assert(s2.isSupersetOf(s3));
    assert(!s2.equals(s3));
    // {a, b, c}
    // cout << s1 << endl;
    // {a, b, d}
    // cout << s2 << endl;
    // {a, b, c, d}
    // cout << s2.unionWith(s1) << endl;
    // s3.clear();
    // assert(s3.last() == 'b');
    // s3.first();
    cout << "Class MyHashSet unit test succeed." << endl;
    return 0;
}
