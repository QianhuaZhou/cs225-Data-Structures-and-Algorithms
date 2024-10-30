#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {

  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {//queue, FIFO
    /** @todo [Part 1] */
    auto it = std::find(work_list.begin(), work_list.end(), point);
    if(it != work_list.end()) return;
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {//stack, LIFO
    /** @todo [Part 1] */
    auto it = std::find(work_list.begin(), work_list.end(), point);
    if(it != work_list.end()) work_list.erase(it);
    work_list.push_front(point); // LIFO: Add to the front for DFS behavior
    
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns): start_(start), png_(png), fns_(fns), tolerance_(tolerance){  
    /** @todo [Part 1] */
   
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(this);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }



  ImageTraversal::Iterator::Iterator(): work_list_(), traversal_(nullptr), current_(Point(0, 0)), visited(){
     
  }


  //self-defined
  ImageTraversal::Iterator::Iterator(ImageTraversal* traversal):
  traversal_(traversal), current_(traversal->start_){
    work_list_.push_back(current_);

    visited.resize(traversal->png_.width());
    for (unsigned i = 0; i < traversal->png_.width(); ++i) {
       visited[i].resize(traversal->png_.height());
      for (unsigned j = 0; j < traversal->png_.height(); ++j) {
         visited[i][j] = false;
      }
    }
  }


  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    if (work_list_.empty()) {
        *this = Iterator();  
        return *this;
    }
    current_ = traversal_->fns_.peek(work_list_);
    traversal_->fns_.pop(work_list_);
    
    //std::cout << "Marking visited: (" << current_.x << ", " << current_.y << ")\n";
    //visited.insert({current_, true});
    visited[current_.x][current_.y] = true;
    /*
     std::cout << "*******traversal throught visited *******" << std::endl;
    for(auto pair : visited){
      std::cout << "Point: (" << pair.x << ", " << pair.y << ") " << std::endl;
    }
    std::cout << "*******traversal end *******" << std::endl;
   
    */
   
    Point right(current_.x + 1, current_.y);
    Point down(current_.x, current_.y + 1);
  
    Point left(current_.x - 1, current_.y);;
    Point up(current_.x, current_.y - 1);
 
    if (ValidToVisit(right)) traversal_->fns_.add(work_list_, right);
    if (ValidToVisit(down)) traversal_->fns_.add(work_list_, down);
    if (ValidToVisit(left)) traversal_->fns_.add(work_list_, left);
    if (ValidToVisit(up)) traversal_->fns_.add(work_list_, up);

    if(!work_list_.empty()){
      current_ = traversal_->fns_.peek(work_list_);
    }else{
       *this = Iterator();  
      return *this;
    }
 
    return *this;
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return current_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return (traversal_ != other.traversal_) || (current_.x != other.current_.x || current_.y != other.current_.y);

  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }


bool Traversals::ImageTraversal::Iterator::ValidToVisit(const Point& p){
  if(p.x >= traversal_->png_.width() || p.y >= traversal_->png_.height()) return false;
    if(visited[p.x][p.y]) return false;

    const HSLAPixel& pix_curr = traversal_->png_.getPixel(p.x, p.y);
    const HSLAPixel& pix_start = traversal_->png_.getPixel(traversal_->start_.x, traversal_->start_.y);
    if(calculateDelta(pix_curr, pix_start) >= traversal_->tolerance_) return false;
    return true;
  }

}
