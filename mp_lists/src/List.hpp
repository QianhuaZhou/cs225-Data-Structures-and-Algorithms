/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {//the keyword class and typename can be interchanged
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  //don't understand why shouldn't use iterator here--can directly use head_, much more efficient
  /*
   for(List<T>::ListIterator it = List<T>::begin(); it != List<T>::end(); it++){
    NodeList* tmp = it.position_;
    delete tmp;
  }
  */
  while(head_ != nullptr){
    ListNode* tmp = head_;
    head_ = head_->next;
    delete tmp;
  }
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if(head_ == nullptr){
    head_ = tail_ = newNode;
  }else{
    newNode -> next = head_;
    head_->prev = newNode;
    head_ = newNode;
    //newNode->prev = head_;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if(head_ == nullptr){
    head_ = tail_ = newNode;
  }else{
    tail_ -> next = newNode;
    newNode ->prev = tail_;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;
  if(splitPoint == 0 || curr == nullptr) return start;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != nullptr && curr->prev != nullptr) {//have to check "curr->prev"
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every odd node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if(head_ == nullptr) return;
  ListNode* tmp = head_->next;
  int count = 1;
  while(tmp != nullptr && tmp!= tail_){
    if(count % 2 != 1){
      count++;
      tmp = tmp->next;
      continue;
    }
    ListNode* toLast = tmp;
    count ++;
    //head_->next = tmp;//--head should not changed after the frist iteration, only the tmp->prev = head_ is enouthg
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    tmp = tmp->next;
    toLast->prev = tail_;
    toLast->next = nullptr;
    tail_->next = toLast;
    tail_ = toLast;
  }
  
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
 /*
 template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {//reference, cannot use to iterate
  /// @todo Graded in mp_lists part 2
  if(startPoint == nullptr || endPoint == nullptr) return;
  ListNode* curr = startPoint;
  ListNode* start = startPoint;
  ListNode* end = endPoint;
  while(start != end && start->prev != end){//not "start->next != end"
    //cannot use std::swap(start->start, start->end); because data is type T, type T may not have a valid swap implement
    ListNode* s = new ListNode(end->data);
    ListNode* e = new ListNode(start->data);
    if(start == head_){
      head_ = s;
      s->prev = nullptr;
      s->next = start->next;
    }else{
      start->prev->next = s;
      s->prev = start->prev;
      s->next = start->next;
      start->next->prev = s;
    }
    
    if(end == tail_){
      tail_ = e;
      end->prev->next = e;
      e->next = nullptr;
    }else{
      end->prev->next = e;
      e->prev = end->prev;
      e->next = end->next;
      end->next->prev = e;
    }
    start = start->next;
    end = end->prev;
    
  }
}
 */

template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {//reference, cannot use to iterate
  /// @todo Graded in mp_lists part 2
  if(startPoint == endPoint || startPoint == nullptr || endPoint == nullptr) return;
  ListNode* tmp;
  ListNode* current = startPoint;
  ListNode* start_prev = startPoint->prev;
  ListNode* end_next = endPoint->next;
  ListNode* initial_start = startPoint;
  ListNode* initial_end = endPoint;
  while(current != end_next){
    tmp = current->prev;
    current->prev = current->next;
    current->next = tmp;
    current = current->prev;
  }

  initial_end->prev = start_prev;
  initial_start->next = end_next;
  if(start_prev != nullptr) start_prev->next = initial_end;
  if(end_next != nullptr) end_next->prev = initial_start;

  startPoint = initial_end;
  endPoint = initial_start;

  if(head_ == initial_start) head_ = initial_end;
  if(tail_ == initial_end) tail_ = initial_start;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  if(n <= 1 || head_ == nullptr) return;
  int len = length_;
  ListNode * start = head_;
  ListNode * end = head_;
  while(start != nullptr){
    int count = 0;
    end = start;
    while(end->next != nullptr && count < n - 1){
      end = end->next;
      count ++;
    }
    reverse(start, end);
    if(count != n - 1 || end->next == nullptr) break;
    start = end->next;
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  if(first == nullptr) return second;
  if(second == nullptr) return first;
  ListNode* ret_head = nullptr;
  ListNode* ret = ret_head;
  ListNode* curr_f = first;
  ListNode* curr_s = second;
  while(curr_f != nullptr && curr_s != nullptr){
    if(curr_f->data < curr_s->data){
      if(ret != nullptr){
        ret->next = curr_f;
        curr_f->prev = ret;
        ret = ret->next;
      }else{
        ret_head = curr_f;
        ret = curr_f;
      }
      curr_f = curr_f->next;
      //ret = ret->next;
    }else{
       if(ret != nullptr){
        ret->next = curr_s;
        curr_s->prev = ret;
        ret = ret->next;
        }else{
          ret_head = curr_s;
          ret = curr_s;
        }
        curr_s = curr_s->next;
    }
  }
  while(curr_f != nullptr){
    ret->next = curr_f;
    ret = ret->next;
    curr_f = curr_f->next;
  }
  
  while(curr_s != nullptr){
    ret->next = curr_s;
    ret = ret->next;
    curr_s = curr_s->next;
  }
  return ret_head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {//important
  /// @todo Graded in mp_lists part 2
  if(chainLength == 0 || chainLength == 1) return start;
  int len = chainLength / 2;
  ListNode* half = split(start, len);
  ListNode* left = mergesort(start, len);
  ListNode* right = mergesort(half, chainLength - len);
  return merge(left, right);
}
