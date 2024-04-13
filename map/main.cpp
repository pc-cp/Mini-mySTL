#include <iostream>
#include <cassert>
#include <string>
#include "mymap.h"
#include "myvector.h"
using namespace std;
int main() {
    MyMap<int, string> mhp;
    mhp.put(1, "A");
    mhp.put(2, "B");

    assert(mhp[2] == "B");

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

    MyMap<int, string> mhp2 = mhp;
    mhp2[1] = "A";
    assert(mhp2.size() == 2);
    assert(mhp.size() == 1);

    assert(!mhp.equals(mhp2));
    mhp[1] = mhp2[1];
    assert(mhp.equals(mhp2));
    cout << mhp << endl;
    mhp.remove(2);
    cout << mhp << endl;

    const MyMap<int, string> mhp3 = mhp2;
    cout << mhp3 << endl;
    assert(mhp3[1] == "A");

    cout << mhp << endl;
    mhp[3] = "C";
    cout << mhp << endl;
    mhp[0] = "A";
    mhp[-1] = "B";
    mhp[5] = "F";
    mhp[2] = "E";
    cout << mhp << endl;
    mhp.remove(2);
    mhp.remove(3);
    cout << mhp << endl;
    // MyVector<int> keys = mhp.keys();
    // cout << keys << endl;
    // MyVector<string> values = mhp.values();
    // cout << values << endl;
    cout << "Class MyMap unit test succeed." << endl;

    return 0;
}
