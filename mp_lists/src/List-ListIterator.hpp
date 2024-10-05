
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;
    ListNode* tail_;

  public:
    ListIterator() : position_(nullptr), tail_(nullptr){ }
    ListIterator(ListNode* x, ListNode* tail) : position_(x), tail_(tail){ }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        //ListIterator ret(new List::ListNode(position_->next->data));//should not use new keyword to create the ListIterator, it return a reference(when return point, can I use new?)
        //if (position_ && position_->next) {
        // Move the iterator forward to the next node
        //position_ = position_->next;
       // }
        if(position_) position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        ListNode* temp = position_;
        if (position_ != nullptr) {
            position_ = position_->next;
        }
        return ListIterator(temp, tail_);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        if(position_ == nullptr){//end
            position_ = tail_;
        }else if (position_->prev != nullptr) {
            position_ = position_->prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {//difference with post-dec?
        // @TODO: graded in mp_lists part 1
        ListNode* temp = position_;
        if (position_ == nullptr){//end
            position_ = tail_;
        }else if(position_->prev != nullptr) {
            position_ = position_->prev;
        }
        return ListIterator(temp, tail_);
        
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        /*
        if(rhs.position_ != position_) return true;//the ListIterator is not a class, shouldn't use this.position_
        return false;
        */
        return rhs.position_ != position_;
    }

    bool operator==(const ListIterator& rhs) {
        return (rhs.position_) == position_;//call bool operator!=(const ListIterator& rhs)
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};