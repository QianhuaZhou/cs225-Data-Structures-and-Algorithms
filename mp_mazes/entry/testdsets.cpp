/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
    DisjointSets s;
    s.addelements(50);
    s.setunion(2, 3);
     for(unsigned int i = 0; i < 10; ++i) {
        std::cout << s.set[i] << " ";
    }
    std::cout << std::endl;
    s.setunion(3, 5);
    s.setunion(5, 7);
    for(unsigned int i = 0; i < 10; ++i) {
        std::cout << s.set[i] << " ";
    }
    std::cout << std::endl;
    s.setunion(7, 2);
     for(unsigned int i = 0; i < 10; ++i) {
        std::cout << s.set[i] << " ";
    }
    std::cout << std::endl;
    s.setunion(4, 6);
     for(unsigned int i = 0; i < 10; ++i) {
        std::cout << s.set[i] << " ";
    }
    std::cout << std::endl;
   
    cout << s.find(7) << endl;
    std::cout << __LINE__ << std::endl;
    cout << s.find(5) << endl;
    std::cout << __LINE__ << std::endl;
    cout << s.find(6) << endl;
    std::cout << __LINE__ << std::endl;

    s.addelements(1);
    cout << s.find(50) << endl;

    s.setunion(50, 3);

    cout << s.find(50) << endl;
    cout << "Disjoint Sets test complete" << endl;

    
    return 0;
}
