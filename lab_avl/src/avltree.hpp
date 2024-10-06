/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    //Node* node = t;
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    updateHeight(t);
    updateHeight(temp);
    t = temp;//need directly modify the reference
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    //Node* node = t;
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    updateHeight(t);
    updateHeight(temp);
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == nullptr) return;
    int b = gainBalance(subtree);
    if(b == 2){//right is overweight
        int right_b = gainBalance(subtree->right);
        if(right_b >= 0){//left rotation(may not be only 1/-1 !!!)
            rotateLeft(subtree);
        }else{//right_b = -1, right-left rotation
            rotateRightLeft(subtree);
        }
    }else if(b == -2){
        int left_b = gainBalance(subtree->left);
        if(left_b <= 0){//right rotation
            rotateRight(subtree);
        }else{//left_b = 1, left-right rotation
            rotateLeftRight(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
   if (subtree == NULL || subtree->key == key){
        subtree = new Node(key, value);
   }else if (key < subtree->key) {
        insert(subtree->left, key, value);
    }else {//(key > subtree->key)
        insert(subtree->right, key, value);
    }
    updateHeight(subtree);
    rebalance(subtree);
    
    
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) return;
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
    
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree->left;
            while(iop->right != nullptr) iop = iop->right;
            subtree->key = iop->key;
            subtree->value = iop->value;
            remove(subtree->left, iop->key);
        } else {
            /* one-child remove */
            // your code here
            Node* temp = subtree;
            subtree = (subtree->left != nullptr) ? subtree->left : subtree->right;
            delete temp;
            temp = nullptr;
        }
        
    }
    //std::cout << __LINE__ << " subtree is empty: " << std::boolalpha << (subtree == nullptr) << std::endl;
    updateHeight(subtree);//must always first update height, then rebalance with updated height
    //std::cout << __LINE__ << "subtree->height = " << subtree->height << std::endl;
    rebalance(subtree);
       

}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node* subtree){
    if(subtree == nullptr) return;
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
int AVLTree<K, V>::gainBalance(Node* subtree){
    /*
    if(subtree->right == nullptr && subtree->left == nullptr){
        return 0;
    }else if(subtree->right == nullptr){
        return -1 - subtree->left->height;
    }else if(subtree->left == nullptr){
        return subtree->right->height - (-1);
    }else{
        return subtree->right->height - subtree->left->height;
    }
    simplify version:
    */
     if (subtree == nullptr) {
        return 0;
    }
    return heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    
}