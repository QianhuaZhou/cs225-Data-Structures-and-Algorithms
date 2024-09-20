/**
 * @file room.cpp
 * Implementation of the Room class.
 */

#include <iostream>
#include "room.h"

Room::Room()
    : name(""), capacity(0), count(0), max_letters(26),letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const std::string& init_name, int init_capacity)
    : name(init_name),
      capacity(init_capacity),
      count(0),
      max_letters(26),
      letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const Room& other)
{
    copy(other);
}

Room& Room::operator=(const Room& other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Room::~Room()
{
    clear();
}

void Room::addLetter(const Letter& L)
{
    
    std::cout << __LINE__ << std::endl;
    //letters[letterCount++] = L;
    //std::cout << "letterCount: " << letterCount << "max_letters: " << max_letters <<  std::endl;
    if(letterCount < max_letters) letters[letterCount++] = L;
    std::cout << __LINE__ << std::endl;
    count += L.count;
}

int Room::spaceRemaining()
{
    return capacity - count;
}

void Room::print(std::ostream & stream /* = std::cout */)
{
    stream << name << " (" << count << "/" << capacity << "):";
    for (int L = 0; L < letterCount; L++)
        stream << " " << letters[L].letter;
    stream << std::endl;
}

void Room::clear()
{
    if (letters != nullptr) delete[] letters;
    letters = nullptr;
}

void Room::copy(const Room& other)
{   
    //if(&other == this) return *this;
    name = other.name;
    capacity = other.capacity;
    count = other.count;
    letterCount = other.letterCount;
    max_letters = other.max_letters;
    if(letters != nullptr)  delete[] letters;
    letters = new Letter[max_letters];
    std::cout <<__LINE__ << std::endl;
    for(int i = 0; i < max_letters; i++){
        letters[i] = other.letters[i];
    }
    std::cout <<__LINE__ << std::endl;
    
    

}
