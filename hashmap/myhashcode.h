/*
 * File: myhashcode.h
 * ----------------
 * The stanford implementation of the HashMap class uses
 * the hash funcion for string, which was developed by
 * Daniel J.Bernstein.
 */

#ifndef _myhashcode_h
#define _myhashcode_h

#include <iostream>

extern const int HASH_SEED;
extern const int HASH_MULTIPLIER;
extern const int HASH_MASK;

int myhashCode(const std::string &str);

/*
 * 方法：hashCode
 * 使用：int bucket = hashCode(key);
 * --------------------------------
 * 计算key的hash Code，这里key支持多个类型
 * 但是需要保证KeyType支持插入操作符（<<）
 * 对于自己定义的类型，特别注意
 */
template <typename T>
int hashCode(const T &rat);

template <typename T>
int hashCode(const T &rat) {
    std::ostringstream os;
    os << rat;
    return myhashCode(os.str());
}
#endif
