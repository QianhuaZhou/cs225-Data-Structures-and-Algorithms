/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* tmp = find(root, key);
    if (tmp == nullptr) {
        throw std::runtime_error("Key not found");
    }
    return tmp->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if(subtree == nullptr || subtree->key == key) return subtree;
    if(subtree->key > key) return find(subtree->left, key);
    return find(subtree->right, key);
   
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{   //need analyze, not very familiar
    //assume the insert location is a leaf position
    // your code here
    Node*& position = find(subtree, key);
    if(position == nullptr){
        position = new Node(key, value);
    }

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    std::swap(first->key, second->key);
    std::swap(first->value, second->value);
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    Node*& position = find(subtree, key);
    if(position == nullptr){
        std::cout << "the passed in key doesn't exist.";
        return;
    }
    if(position->left == nullptr && position->right == nullptr){//0 children
        delete position;
        position = nullptr;
    }else if(position->left != nullptr && position->right != nullptr){//2 children
        //fine IOP(rightmost children in left subtree)
        Node* iop = position;
        iop = iop->left;
        while(iop->right != nullptr){
            iop = iop->right;
        }
        swap(iop, position);
        remove(position->left, iop->key);
    }else{//1 children
        Node* tmp = position;
        position = (position->left != nullptr) ? position->left : position->right;
        delete tmp;
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> tree;
    for(auto pair : inList){
        tree.insert(pair.first, pair.second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::sort(inList.begin(), inList.end());
    std::vector<int> histogram;
    do{
        BST<K, V> tree;
        for(const auto& pair :inList){
            tree.insert(pair.first, pair.second);
        }
        int height = tree.height();
        if(histogram.size() <= static_cast<size_t>(height)){
            histogram.resize(height + 1, 0);//if directly give assign the vector with correct size, what should the size be?
        }
        histogram[height]++;
    }while(std::next_permutation(inList.begin(), inList.end()));
    return histogram;
}