/**
 * @file puzzle.cpp
 * Implementation of puzzle class.
 */
#include "puzzle.h"
#include <set>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#include <limits>

/**
* Default constructor for the puzzle state. This should initialize the
* puzzle to the solved state.
*/
PuzzleState::PuzzleState(){
    char curr = '1';
    std::vector<char>& m = gainMatrix();
    for(unsigned int row = 0; row < 4; ++row){
        for(unsigned int col = 0; col < 4; ++col){
            //matrix[row][col] = curr - 48;
            m.push_back(curr - 48);
            curr++;
        }
    }
    //matrix[3][3] = 0;
    m[15] = 0;
    emptyIdx = {3, 3};
}

/**
* Custom constructor for the puzzle state. Invalid inputs should initialize
* the puzzle representing all zeros. A char is used to represent the value
* of each tile, where 0 represents the empty space, it is also typically how
* a byte is represented in C/C++. Almost always, a char will represent a octet
* (8 bits), which allow for 256 possible values, in this case, since each
* tile can only have a value from 0-15 (4-bits), using a char is sufficient.
*
* @param state The starting state of the puzzle. The first entry in the
* array is the top left tile, then the remaining entries are in row-major
* order. The following is a depiction of a puzzle where the value of each
* tile represents its index in the array:
* 0  1  2  3
* 4  5  6  7
* 8  9  10 11
* 12 13 14 15
*/
PuzzleState::PuzzleState(const std::array<char, 16> state){
    for(unsigned int i = 0; i < 16; ++i){
        matrix.push_back(state[i]);
        if(state[i] == 0){
            emptyIdx = {i/4, i%4};
        }
    }
}

 /**
* Convert the puzzle state to an array.
* @return an array representing the state of the puzzle in the same format
* as described in the constructor.
*/
std::array<char, 16> PuzzleState::asArray() const{
    std::array<char, 16> ret;
    const std::vector<char>& m = gainMatrix();
    for(unsigned int i = 0; i < 16; ++i){
        ret[i] = m[i];
    }
    return ret;
}

/**
* Overloaded operator== for the puzzle state. Puzzles are equal when the
* value of each tile is the same.
* @param rhs The puzzle state to compare to
*/
bool PuzzleState::operator==(const PuzzleState &rhs) const{
    // const std::vector<char>& m = gainMatrix();
    // const std::vector<char>& rhs_m = rhs.gainMatrix();
    // for(unsigned int i = 0; i < 16; ++i){
    //     if(m[i] != rhs_m[i]) return false;
    // }
    // return true;
    return gainMatrix() == rhs.gainMatrix();
}

/**
* Overloaded operator!= for the puzzle state.
* @param rhs The puzzle state to compare to
*/
bool PuzzleState::operator!=(const PuzzleState &rhs) const{
    return !(rhs == *this);
}

/**
* Overloaded operator< for the puzzle state. The PuzzleState with the first
* tile value less than the corresponding tile in the other PuzzleState is
* considered less, you can assume both puzzle states are valid.
* @param rhs The puzzle state to compare to
*/
bool PuzzleState::operator<(const PuzzleState &rhs) const{
    // const std::vector<char>& m = gainMatrix();
    // const std::vector<char>& rhs_m = rhs.gainMatrix();
    // for(unsigned int i = 0; i < 16; ++i){
    //     if(m[i] < rhs_m[i]){
    //         return true;
    //     }else if(m[i] > rhs_m[i]){
    //         return false;
    //     }
    // }
    // return false;
    return gainMatrix() < rhs.gainMatrix();
}

/**
* Get the neighbor specified by the direction. If the direction refers to an
* invalid neighbor, return PuzzleState representing all zeros.
* @param direction The direction to move a tile (e.x. UP means the empty
* space should move down).
*/
PuzzleState PuzzleState::getNeighbor(Direction direction) const{
    unsigned int row = emptyIdx.first;
    unsigned int col = emptyIdx.second;
    std::array<char, 16> temp = asArray();
    if(direction == Direction::UP){
        if(row != 3){
            std::swap(temp[(row+1)*4 + col], temp[row*4 + col]);
            return PuzzleState(temp);
        }
    }else if(direction == Direction::DOWN){
        if(row != 0){
            std::swap(temp[(row-1)*4 + col], temp[row*4 + col]);
            return PuzzleState(temp);
        }
    }else if(direction == Direction::LEFT){
        if(col != 3){
            std::swap(temp[row*4 + col + 1], temp[row*4 + col]);
            return PuzzleState(temp);
        }
    }else if(direction == Direction::RIGHT){
        if(col != 0){
            std::swap(temp[row*4 + col - 1], temp[row*4 + col]);
            return PuzzleState(temp);
        }
    }
    return PuzzleState(std::array<char, 16>());
}

/**
* Gets all possible PuzzleStates that result from a single move.
* @return All possible next PuzzleStates in any order
*/
std::vector<PuzzleState> PuzzleState::getNeighbors() const{
    std::vector<PuzzleState> ret;
    PuzzleState invalid = PuzzleState(std::array<char, 16>());
    if(getNeighbor(Direction::UP) != invalid) ret.push_back(getNeighbor(Direction::UP));
    if(getNeighbor(Direction::DOWN) != invalid) ret.push_back(getNeighbor(Direction::DOWN));
    if(getNeighbor(Direction::LEFT) != invalid) ret.push_back(getNeighbor(Direction::LEFT));
    if(getNeighbor(Direction::RIGHT) != invalid) ret.push_back(getNeighbor(Direction::RIGHT));
    return ret;
}

 /**
* Calculates the "manhattan distance" between the current state and the goal
* state. This is the sum of the manhattan distances of each tile's current
* location to its goal location.
* @param desiredState The state to calculate the distance to
* @return The manhattan distance between the current and goal states
*/
int PuzzleState::manhattanDistance(const PuzzleState desiredState) const{
    const std::vector<char>& d_m = desiredState.gainMatrix();
    int ret = 0;
    for(unsigned int i = 0; i < 16; ++i){
        if(matrix[i] == 0) continue;
        auto it = std::find(d_m.begin(), d_m.end(), matrix[i]);
        if(it != d_m.end()){
            int idx = static_cast<int>(i);
            int d_idx = std::distance(d_m.begin(), it);
            ret += abs(idx/4 - d_idx/4) + abs(idx%4 - d_idx%4);
        }
    }
    return ret;
}


/**
* Solves the puzzle using BFS.
* @param startState The starting state of the puzzle
* @param desiredState The final goal state of the puzzle after solving
* @param iterations The number of iterations it took to solve the puzzle. An
* iteration is defined as the number of times a state is popped from the data
* structure (NOTE: this should include the start and desired states, but not any
* states that are immediately discarded, if applicable). We will use the value
* stored at this pointer to evaluate efficiency. Ignore if NULL.
* @return The path to the solution. The first element of the vector is the start
* state, and the last element is the desired state. Empty if no solution exists.
*/


std::vector<PuzzleState> solveBFS(const PuzzleState& startState, const PuzzleState& desiredState, size_t* iterations) {
    // Queue for BFS
    std::queue<PuzzleState> frontier;

    // Maps to track visited states and reconstruct the path
    std::map<PuzzleState, PuzzleState> came_from;
    std::set<PuzzleState> visited;

    // Initialize the frontier
    frontier.push(startState);
    visited.insert(startState);
    came_from[startState] = PuzzleState(); // Empty parent for the start state

    size_t iterationCount = 0;
    if (iterations != nullptr) {
        *iterations = 0;
    }

    while (!frontier.empty()) {
        // Increment iteration count
        iterationCount++;
        if (iterations != nullptr) {
            *iterations = iterationCount;
        }

        // Get the current state
        PuzzleState current = frontier.front();
        frontier.pop();

        // If the goal is reached, reconstruct the path
        if (current == desiredState) {
            std::vector<PuzzleState> path;
            while (current != startState) {
                path.push_back(current);
                current = came_from[current];
            }
            path.push_back(startState);
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors
        for (const PuzzleState& next : current.getNeighbors()) {
            if (visited.find(next) == visited.end()) {
                // Mark as visited
                visited.insert(next);

                // Add to the frontier
                frontier.push(next);

                // Record the path
                came_from[next] = current;
            }
        }
    }

    // Return an empty vector if no solution is found
    return {};
}


std::vector<PuzzleState> solveAstar(const PuzzleState& startState, const PuzzleState& desiredState, size_t* iterations) {
    using StatePriority = std::pair<PuzzleState, int>;
    auto compare = [](const StatePriority& a, const StatePriority& b) {
        return a.second > b.second; // Min-heap: smallest priority first
    };
    std::priority_queue<StatePriority, std::vector<StatePriority>, decltype(compare)> frontier(compare);

    frontier.push({startState, 0});

    std::map<PuzzleState, PuzzleState> came_from;
    std::map<PuzzleState, int> cost_so_far;

    came_from[startState] = PuzzleState();
    cost_so_far[startState] = 0;

    size_t iterationCount = 0;
    if (iterations != nullptr) {
        *iterations = 0;
    }

    while (!frontier.empty()) {
        iterationCount++;
        if (iterations != nullptr) {
            *iterations = iterationCount;
        }
        PuzzleState current = frontier.top().first;
        frontier.pop();
        if (current == desiredState) {
            std::vector<PuzzleState> path;
            while (current != startState) {
                path.push_back(current);
                current = came_from[current];
            }
            path.push_back(startState);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const PuzzleState& next : current.getNeighbors()) {
            //std::cout << next << std::endl;
            int new_cost = cost_so_far[current] + 1; 
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                int priority = new_cost + next.manhattanDistance(desiredState);

                frontier.push({next, priority});

                came_from[next] = current;
            }
        }
    }
    return {};
}
