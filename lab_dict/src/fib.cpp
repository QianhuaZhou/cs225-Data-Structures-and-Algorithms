/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fib(n-1) + fib(n-2);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    //note the use of keyword static to avoid add map a parameter to the function
    static std::map<int, int> map{{0, 0}, {1, 1}};
    auto it = map.find(n);
    if(it != map.end()){//need calculate and insert it into map
        return map[n];
    }else{
        map[n] = memoized_fib(n-1) + memoized_fib(n-2);
    }
    return map[n];
}
