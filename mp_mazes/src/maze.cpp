/* Your code here! */

#include "maze.h"

SquareMaze::SquareMaze(){
    width_ = 0;
    height_ = 0;
    size_ = 0;
}

/**
* Makes a new SquareMaze of the given height and width.
*
* If this object already represents a maze it will clear all the
* existing data before doing so. You will start with a square grid (like
* graph paper) with the specified height and width. You will select
* random walls to delete without creating a cycle, until there are no
* more walls that could be deleted without creating a cycle. Do not
* delete walls on the perimeter of the grid.
*
* Hints: You only need to store 2 bits per square: the "down" and
* "right" walls. The finished maze is always a tree of corridors.)
*
* @param width The width of the SquareMaze (number of cells)
* @param height The height of the SquareMaze (number of cells)
*/
void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;
    size_ = width * height;
    sets.addelements(size_);
    
    rdwalls = std::vector<std::pair<bool, bool>>(size_, {true, true});
    while(sets.size(0) != size_){
        int X = rand() % width_;//[0, width_ - 1].
        int Y = rand() % height_;
        int dir = rand() % 2;
        int cur = X + Y * width_;
        int atRight = (X + 1) + Y * width_;
        int atDown = X + (Y + 1) * width_;
        if(dir == 0){
            if (X != width_ - 1) {
               //std::cout << __LINE__ << " cur = " << cur << " atRight = " << atRight << " sets.find(cur)= " << sets.find(cur) << " sets.find(atRight) = " << sets.find(atRight) << std::endl;
                if (sets.find(cur) != sets.find(atRight)) {
                    setWall(X, Y, RIGHT, false);
                    sets.setunion(cur, atRight);
                }
            }
        } else { //down 
            if (Y != height_ - 1) {
                //std::cout << __LINE__ <<  " cur = " << cur << " atDown = " << atDown << " sets.find(cur)= " << sets.find(cur) << " sets.find(atDown) = " << sets.find(atDown) << std::endl;
                if (sets.find(cur) != sets.find(atDown)) {
                    setWall(X, Y, DOWN, false);
                    sets.setunion(cur, atDown);
                }
            }
        }
    
    }
    /*
     std::cout << __LINE__ << "size = " << sets.set.size() << std::endl;
    for(int & i : sets.set){
            std::cout << i << " ";
        }
    std::cout << std::endl;
    */
}

/**
* This uses your representation of the maze to determine whether it is
* possible to travel in the given direction from the square at
* coordinates (x,y).
*
* For example, after makeMaze(2,2), the possible input coordinates will
* be (0,0), (0,1), (1,0), and (1,1).
*
* You can not step off of the maze or through a wall.
*
* This function will be very helpful in solving the maze. It will also
* be used by the grading program to verify that your maze is a tree that
* occupies the whole grid, and to verify your maze solution. So make
* sure that this function works!
*
* @param x The x coordinate of the current cell
* @param y The y coordinate of the current cell
* @param dir The desired direction to move from the current cell
* @return whether you can travel in the specified direction
*/
bool SquareMaze::canTravel(int x, int y, Direction dir) const{
    if (dir == 0) {
        if (x < width_ - 1 && !rdwalls[x + y*width_].first) {
            return true;
        } 
    }

    if (dir == 1) {
        if (y < height_ - 1 && !rdwalls[x + y*width_].second) {
            return true;
        } 
    }

    if (dir == 2) {
        if (x > 0 && !rdwalls[(x - 1) + y*width_].first) {
            return true;
        }
    }

    if (dir == 3) {
        if (y > 0 && !rdwalls[x + (y - 1)*width_].second) {
            return true;
        }
    }

    return false;
}

/**
* Sets whether or not the specified wall exists.
*
* This function should be fast (constant time). You can assume that in
* grading we will not make your maze a non-tree and then call one of the
* other member functions. setWall should not prevent cycles from
* occurring, but should simply set a wall to be present or not present.
* Our tests will call setWall to copy a specific maze into your
* implementation.
* 
* NOTE: You will only need to support setting the bottom or right walls 
* of every squares in the grid
*
* @param x The x coordinate of the current cell
* @param y The y coordinate of the current cell
* @param dir The desired direction to set the wall. This will always be RIGHT or DOWN
* @param exists true if setting the wall to exist, false otherwise
*/
void SquareMaze::setWall(int x, int y, Direction dir, bool exists){
    int idx = y*height_ + x;
    rdwalls[idx] = (dir == 0) ? std::make_pair(exists, rdwalls[idx].second) 
                          : std::make_pair(rdwalls[idx].first, exists);
}

/**
* Solves this SquareMaze.
*
* For each square on the bottom row (maximum y coordinate), there is a
* distance from the starting point (startX, 0) (i.e. any position on the
* top row), which is defined as the length (measured as a number of steps)
* of the only path through the maze from the starting point to that square.
*
* Select the square in the bottom row with the largest distance from the
* starting point as the destination of the maze. `solveMaze()` returns
* the winning path from the origin to the destination as a vector of
* directions.
*
* If multiple paths of maximum length exist, use the one with the
* destination cell that has the smallest x value.
*
* HINT: this function should run in time linear in the number of cells
* in the maze.
*
* @return a vector of directions taken to solve the maze
*/
std::vector<Direction> SquareMaze::solveMaze(int startX){
    std::queue<int> q;
    std::vector<int> length(size_, -1);
    std::vector<Direction> path(size_);
    std::vector<int> previous(size_, -1);
    q.push(startX);
    length[startX] = 0;
    while(!q.empty()){
        int currIdx = q.front();
        int X = currIdx % width_;
        int Y = currIdx / width_;
        if(currIdx + 1 < size_ && canTravel(X, Y, RIGHT) && length[currIdx + 1] == -1){
            length[currIdx + 1] = length[currIdx] + 1;
            path[currIdx+ 1] = RIGHT;
            previous[currIdx + 1] = currIdx;
            q.push(currIdx + 1);
        }

        if(currIdx + width_ < size_ && canTravel(X, Y, DOWN) && length[currIdx + width_] == -1){
            length[currIdx + width_] = length[currIdx] + 1;
            path[currIdx + width_] = DOWN;
            previous[currIdx + width_] = currIdx;
            q.push(currIdx + width_);
        }
        
        if(currIdx - 1 >= 0 && canTravel(X, Y, LEFT) && length[currIdx - 1] == -1){

            length[currIdx - 1] = length[currIdx] + 1;
            path[currIdx - 1] = LEFT;
            previous[currIdx - 1] = currIdx;
            q.push(currIdx - 1);
        }

        if(currIdx - width_ >= 0 && canTravel(X, Y, UP) && length[currIdx - width_] == -1){

            length[currIdx - width_] = length[currIdx] + 1;
            path[currIdx - width_] = UP;
            previous[currIdx - width_] = currIdx;
            q.push(currIdx - width_);
        }
        q.pop();
    }
    int maxLength = 0;
    int maxIdx = 0;
    for(int i = 0; i < width_; ++i){
        if(length[(height_ - 1) * width_ + i] > maxLength){
            maxIdx = (height_ - 1) * width_ + i;
            maxLength = length[maxIdx];
        }
    }
    int solX = maxIdx % width_;
    int solY = maxIdx / width_;
    std::vector<Direction> longestPath;
    while(maxIdx != startX){
        longestPath.push_back(path[maxIdx]);
        maxIdx = previous[maxIdx];
    }
    std::reverse(longestPath.begin(), longestPath.end());
    return longestPath;
}

/**
* Draws the maze without the solution.
*
* First, create a new PNG. Set the dimensions of the PNG to
* (width*10+1,height*10+1). where height and width were the arguments to
* makeMaze. Blacken the entire topmost row and leftmost column of
* pixels, except for the entrance. Instead make a gap above the specified 
* start point defined as the inclusive region from ((start*10)+1, 0) to ((start+1)*10-1, 0).
* [The gap is the pixels larger than start*10 and smaller than (start+1)*10 ]
* For each square in the maze, call its maze coordinates (x,y). If the right wall exists,
* then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from
* 0 to 10. If the bottom wall exists, then blacken the pixels with
* coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
*
* The resulting PNG will look like the sample image, except there will
* be no exit from the maze and the red line will be missing.
*
* @return a PNG of the unsolved SquareMaze
*/
cs225::PNG *SquareMaze::drawMaze(int start) const{
    cs225::PNG* image = new cs225::PNG(width_*10+1, height_*10+1);
    for(int i = 0; i < height_*10 + 1; ++i){//topmost
        image->getPixel(0, i).l = 0;
    }
    for(int i = 0; i < width_*10 + 1; ++i){//leftmost
        if(i >= 10*start && i < 10*(1+start)) continue;
        image->getPixel(i, 0).l = 0;
    }
    for(int i = 0; i < static_cast<int>(rdwalls.size()); ++i){
            int x = i % width_;
            int y = i / width_;
            if(rdwalls[i].first){
                for(int k = 0; k <= 10; ++k){
                    image->getPixel((x+1)*10, y*10+k).l = 0;
                }
            }
            if(rdwalls[i].second){
                for(int k = 0; k <= 10; ++k){
                    image->getPixel(x*10+k, (y+1)*10).l = 0;
                }
            }
    }
    return image;
}

/**
* This function calls drawMaze, then solveMaze; it modifies the PNG
* from drawMaze to show the solution vector and the exit.
*
* Start at pixel (5,5). Each direction in the solution vector
* corresponds to a trail of 11 red pixels in the given direction. If the
* first step is downward, color pixels (5,5) through (5,15) red. (Red is
* 0,1,0.5,1 in HSLA). Then if the second step is right, color pixels (5,15)
* through (15,15) red. Then if the third step is up, color pixels
* (15,15) through (15,5) red. Continue in this manner until you get to
* the end of the solution vector, so that your output looks analogous
* the above picture.
*
* Make the exit by undoing the bottom wall of the destination square:
* call the destination maze coordinates (x,y), and whiten the pixels
* with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
*
* @return a PNG of the solved SquareMaze
*/
cs225::PNG *SquareMaze::drawMazeWithSolution(int start){
    cs225::PNG* image = drawMaze(start);
    std::vector<Direction> dirs = solveMaze(start);
    int currX = start*10 + 5;
    int currY = 5;
    for(Direction& dir : dirs){
        if(dir == DOWN){
            for(int k = 0; k < 11; k ++){
                image->getPixel(currX, currY+k) = cs225::HSLAPixel(0, 1, 0.5, 1);
            }
            currY += 10;
        }else if(dir == RIGHT){
            for(int k = 0; k < 11; k ++){
                image->getPixel(currX+k, currY) = cs225::HSLAPixel(0, 1, 0.5, 1);
            }
            currX += 10;
        }else if(dir == UP){
            for(int k = 0; k < 11; k ++){
                image->getPixel(currX, currY-k) = cs225::HSLAPixel(0, 1, 0.5, 1);
            }
            currY -= 10;
        }else if(dir == LEFT){
            for(int k = 0; k < 11; k ++){
                image->getPixel(currX-k, currY) = cs225::HSLAPixel(0, 1, 0.5, 1);
            }
            currX -= 10;
        }
    }
    //std::cout << __LINE__ << " currX = " << currX << " currY = " << currX << std::endl;
    currX -= 4;
    currY += 5;
    for(int k = 0; k < 9; ++k){
        image->getPixel(currX+k, currY).l = 1;
        image->getPixel(currX+k, currY).a = 1;
    }
    return image;
}
