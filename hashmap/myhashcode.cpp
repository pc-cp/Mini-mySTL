#include <iostream>
#include <string>
#include <sstream>
#include "myhashcode.h"
/*
 * Implementation notes: myhashCode
 * ------------------------------
 * This function takes a string key and uses it to derive a hash code,
 * which is a nonnegative integer related to the key by a deterministic
 * function that distributes keys well across the space of integers.
 * The general method is called linear congruence, which is also used
 * in random-number generators. The specific algorithm used here is
 * called djb2 after the initials of its inventor, Daniel J. Bernstein.
 */

// Starting point for first cycle
extern const int HASH_SEED = 5381;
// Multiplier for each cycle
extern const int HASH_MULTIPLIER = 33;
// All 1 bits except the sign
extern const int HASH_MASK = unsigned(-1) >> 1;

int myhashCode(const std::string &str) {
    unsigned hash = HASH_SEED;
    int n = str.length();
    for(int i = 0; i < n; ++i) {
        hash = HASH_MULTIPLIER * hash + str[i];
    }

    return int(hash % HASH_MASK);
}

