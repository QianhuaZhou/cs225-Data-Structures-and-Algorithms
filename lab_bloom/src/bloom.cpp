/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"

using namespace std;
// std::vector<hashFunction> hv;
// std::vector<bool> bv;
BF::BF(uint64_t size, std::vector<hashFunction> hashList){

    // Your code here 

    bv = vector<bool>(size);
    hv = vector<hashFunction>(hashList.size());
    for(unsigned int i = 0; i < hashList.size(); ++i){
        hv[i] = hashList[i];
    } 

}

BF::BF(const BF& other){
    // Your code here 
    //if(*this == &other) return;
    bv.clear();
    hv.clear();
    bv.resize(other.bv.size());
    hv.resize(other.hv.size());
    for(unsigned int i = 0; i < other.bv.size(); ++i){
        bv[i] = other.bv[i];
    } 
    for(unsigned int i = 0; i < other.hv.size(); ++i){
        hv[i] = other.hv[i];
    } 
}

BF::~BF(){
    return;
}
// std::vector<hashFunction> hv;
// std::vector<bool> bv;
void BF::add(const int & key){
    // Your code here 
    size_t size_ = bv.size();
    for(hashFunction& hash : hv){
        int hashValue = hash(key) % size_;
        //if (hashValue < 0) hashValue += size_;
        if(!bv[hashValue]){
            bv[hashValue] = true;
        }
    }
}

bool BF::contains(const int& key) const{
    // Your code here 
    size_t size_ = bv.size();
    for(const hashFunction& hash : hv){
        int hashValue = hash(key) % size_;
        if(!bv[hashValue]){
            return false;
        }
    }
    return true;
}

void BF::bit_union(const BF& other){
    // Your code here 
    for(unsigned int i = 0; i < other.bv.size(); ++i){
        if(!bv[i] && !other.bv[i]) bv[i] = false;
        else bv[i] = true;
    } 
}

void BF::intersect(const BF& other){
    // Your code here 
    for(unsigned int i = 0; i < other.bv.size(); ++i){
        if(bv[i] && other.bv[i]) bv[i] = true;
        else bv[i] = false;
    } 
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here

    float fp = 0.0;
    float tn = 0.0;
    BF b(size, hashList);
    for(int& i : inList) b.add(i);
    for(unsigned int i = 0; i < max; ++i){
        auto it = find(inList.begin(), inList.end(), i);
        if(it == inList.end() && b.contains(i)) fp++;
        if(it == inList.end() && !b.contains(i)) tn++;
    }
    return fp/(fp+tn);

}

bool getBitFromArray(std::vector<char> bv, int index){
    // Your code here
    return getBitFromByte(bv[index/8], index % 8);
    
}

bool getBitFromByte(char in, int index){
    // Your code here
    if (index < 0 || index > 7) {
        throw std::out_of_range("Index must be between 0 and 7");
    }
    return (static_cast<unsigned char>(in) >> (7-index)) & 1;
    

}

