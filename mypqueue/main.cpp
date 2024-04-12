
#include <iostream>
#include <string>
#include "mypqueue.h"

using namespace std;

int main() {
    MyPQueue<string> mpq;
    mpq.enqueue("A", 1604);
    mpq.enqueue("B", 2708);
    mpq.enqueue("C", 1861);
    mpq.enqueue("D", 3169);
    mpq.enqueue("E", 2193);
    
    while(!mpq.isEmpty()) {
        cout << mpq.dequeue() << endl;
    }
    return 0;
}
