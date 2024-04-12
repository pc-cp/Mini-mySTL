#include <iostream>
#include <cassert>
#include "myhashmap.h"
using namespace std;
int main() {
    MyHashMap<int, string> mhp;
    mhp.put(1, "A");
    mhp.put(2, "B");

    assert(mhp.get(2) == "B");
    assert(mhp[2] == "B");
    cout << mhp[2] << endl;

    mhp[2] = "C";
    assert(mhp[2] == "C");
    assert(mhp.containsKey(2));
    assert(!mhp.containsKey(3));
    assert(mhp.size() == 2);
    mhp.clear();
    assert(mhp.size() == 0);
    mhp[2] = "D";
    assert(mhp.size() == 1);
    assert(mhp[2] == "D");

    MyHashMap<int, string> mhp2 = mhp;
    mhp2[1] = "A";
    assert(mhp2.size() == 2);
    assert(mhp.size() == 1);

    assert(!mhp.equals(mhp2));
    mhp[1] = mhp2[1];
    assert(mhp.equals(mhp2));

    cout << mhp << endl;
    mhp.remove(2);
    cout << mhp << endl;
    mhp.remove(1);
    cout << mhp << endl;
    if(mhp.isEmpty()) {
        cout << "mhp is empty" << endl;
    }

    const MyHashMap<int, string> mhp3 = mhp2;
    cout << mhp3 << endl;
    cout << mhp3[3] << endl;
    // mhp3[3] = "C";
    mhp2[3] = "D";
    cout << mhp3[3] << endl;

    mhp = mhp3;
    cout << mhp << endl;
    mhp[3] = "C";
    cout << mhp << endl;
    cout << mhp3 << endl;
    cout << "Class MyHashMap unit test succeed." << endl;

    return 0;
}
