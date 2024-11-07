/* Your code here! */
#include "dsets.h"
#include <cmath>
#include <iostream>
/**
     * Creates n unconnected root nodes at the end of the vector.
     * @param num The number of nodes to create
     */
void DisjointSets::addelements(int num){
    for(int i = 0; i < num; ++i){
        set.push_back(-1);
    }
}

/**
    * This function should compress paths and works as described in lecture.
    * @return the index of the root of the up-tree in which the parameter
    *  element resides.
    */
int DisjointSets::find(int elem){
    if(set[elem] < 0) return elem;
    //path compress: connect current note to root
    set[elem] = find(set[elem]);
    return set[elem];
    //return find(set[elem]);
}

 

/**
    * This function should be implemented as union-by-size. That is, when you
    * setunion two disjoint sets, the smaller (in terms of number of nodes)
    * should point at the larger. This function works as described in lecture,
    * except that you should not assume that the arguments to setunion are
    * roots of existing uptrees.
    *
    * Your setunion function SHOULD find the roots of its arguments before
    * combining the trees. If the two sets are the same size, make the tree
    * containing the second argument point to the tree containing the first.
    * (Note that normally we could break this tie arbitrarily, but in this case
    * we want to control things for grading.)
    *
    * @param a Index of the first element to union
    * @param b Index of the second element to union
    */
void DisjointSets::setunion(int a, int b){
    int rootA = find(a);
    int rootB = find(b);
    //std::cout << "rootA = " << rootA << "  rootB = " << rootB << std::endl;
    if(rootA == rootB) return;
    if(abs(set[rootA]) >= abs(set[rootB])){
        set[rootA] = set[rootA] + set[rootB];
        set[rootB] = rootA;

    }else{
        set[rootB] = set[rootA] + set[rootB];
        set[rootA] = rootB;
    }
}

/**
    * This function should return the number of nodes in the up-tree containing 
    * the element.
    * @return number of nodes in the up-tree containing the element
    */
int DisjointSets::size(int elem){
    int root = find(elem);
    return -1 * set[root];

}

/**
    * This function returns the direct parent of the node in the vector
    * For example, if the vector has structure
    * `Index: 0  |  1 |  2 |  3 |  4 |  5 |  6 |  7`
    * `Value: -1 | -1 |  4 |  6 |  7 | -1 | -2 | -3`
    * (corresponding to `{0}, {1}, {2, 4, 7}, {3, 6}`)
    * Then `getValue(2)` should return 4, NOT 7
    */
int DisjointSets::getValue(int elem) const{
    return set[elem];
}