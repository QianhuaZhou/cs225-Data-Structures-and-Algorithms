
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <iostream>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    //return (_elems[2*currentIdx]!=nullptr) || (_elems[2*currentIdx+1]!=nullptr);
    return (2 * currentIdx) < _elems.size();//in heap structure, no empty element with exist in the vector
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    if (right < _elems.size() && higherPriority(_elems[right], _elems[left]))
        return right;
    return left;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx)){
        int minChildIdx = maxPriorityChild(currentIdx);
        if(higherPriority(_elems[minChildIdx], _elems[currentIdx])){
            std::swap(_elems[currentIdx], _elems[minChildIdx]);
            heapifyDown(minChildIdx);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    //std::sort(elems.begin(), elems.end());
    _elems.push_back(T());  // Add a dummy element to index 0, as heaps are usually 1-indexed
    for(const T& i : elems){
        _elems.push_back(i);
    }
    /*
    for(size_t i = 2; i < elems.size() ; ++i){
        heapifyUp(i);
    }
    */
    
    for(size_t i = elems.size()/2; i >= 1; --i){
        heapifyDown(i);
    }

}

template <class T, class Compare>
T heap<T, Compare>::pop()//reminMin
{
    // @TODO Remove, and return, the element with highest priority
    T minValue = _elems[1];
    _elems[1] = _elems[_elems.size() - 1];
    //_elems[_elems.size() - 1] = nullptr;
    _elems.pop_back();
    heapifyDown(1);
    return minValue;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    for(size_t i = 2; i < _elems.size() - 1; ++i){
        heapifyUp(i);
    }
    for(size_t i = _elems.size()/2; i >= 1; --i){
        heapifyDown(i);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() <= 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
