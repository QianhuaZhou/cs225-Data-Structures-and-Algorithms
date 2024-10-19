/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    //double vals[Dim];
    if(first[curDim] != second[curDim]) return first[curDim] < second[curDim];
    return first < second;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double sum1 = 0.0;
    double sum2 = 0.0;
    for(unsigned int i = 0; i < Dim; ++i){
      sum1 += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      sum2 += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    if(sum1 != sum2) return sum2 < sum1;
    return potential < currentBest;
}


//helper funtion
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(std::vector<Point<Dim>>& points, int left, int right, int dimension){
  if(left > right) return nullptr;
  int medianIdx = findMedian(points, left, right, dimension);
  KDTreeNode* node = new KDTreeNode(points[medianIdx]);
  node->left = buildTree(points, left, medianIdx - 1, (dimension + 1) % Dim);
  node->right = buildTree(points, medianIdx + 1, right, (dimension + 1) % Dim);
  return node;
}

template <int Dim>
int  KDTree<Dim>::findMedian(std::vector<Point<Dim>>& points, int left, int right, int dimension){
  int medianIdx = (left + right) / 2;
  auto cmp = [dimension](const Point<Dim>& a, const Point<Dim>& b){
    return smallerDimVal(a, b, dimension);
  };//lambda function
  select(points.begin() + left, points.begin() + right + 1, points.begin() + medianIdx, cmp);
  return medianIdx;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> data = newPoints;
    root = buildTree(data, 0, data.size() - 1, 0);
    size = data.size();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  //KDTreeNode(const Point<Dim> &point)
  root = new KDTreeNode(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this == &rhs || rhs == nullptr) return;
  if(this != nullptr) ~KDTree();
  size = rhs.size();
  root = new KDTreeNode(rhs.root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  remove(root);
}

//helper funtion
template <int Dim>
void KDTree<Dim>::remove(KDTreeNode* root){
  if(root == nullptr) return;
  remove(root->left);
  remove(root->right);
  delete root;
}

//helper function
template<int Dim>
double KDTree<Dim>::distanceSquared(const Point<Dim>& point1, const Point<Dim>& point2) const {
    double sum = 0.0;
    // Iterate over all dimensions and compute the squared difference
    for (int i = 0; i < Dim; ++i) {
        double diff = point1[i] - point2[i];
        sum += diff * diff;
    }
    return sum;  // Return the squared distance
}


template<int Dim>
Point<Dim> KDTree<Dim>::findNearest(KDTreeNode* node, const Point<Dim>& query, int depth, Point<Dim>& best) const{
  if(node == nullptr) return best;
  int currDim = depth % Dim;
  //double nodeDist = distanceSquared(query, node->point);
  //double bestDist = distanceSquared(query, best);
  //shouldReplace(const Point<Dim>& target,
                                //const Point<Dim>& currentBest,
                                //const Point<Dim>& potential)
                                //shouldReplace(query, bestDist, nodeDist)
  //if(nodeDist < bestDist || (nodeDist == bestDist && node->point < best)){
  //std::cout << std::boolalpha; 
  //std::cout << __LINE__ << " best: " << best << " node->point: " << node->point << " shouldReplace: " << shouldReplace(query, best, node->point) << std::endl;

  if(shouldReplace(query, best, node->point)){
    //bestDist = nodeDist;
    best = node->point;
  }
  //determine which subtree to search first
  KDTreeNode* nearSubtree = nullptr;
  KDTreeNode* farSubtree = nullptr;
  if(query[currDim] < node->point[currDim]){
    nearSubtree = node->left;
    farSubtree = node->right;
  }else{
    nearSubtree = node->right;
    farSubtree = node->left;
  }
  //Recur on the nearer subtree 
  best = findNearest(nearSubtree, query, depth + 1, best);
  //Check if we need to search the farther subtree
  double planeDist = query[currDim] - node->point[currDim];
  /*
  double bestSquared = 0;
  for(int i = 0; i < Dim; ++i){
    double diff = query[i] - best[i];
    bestSquared += diff * diff;
  }
  */
  double bestSquared = distanceSquared(query, best);
  //if(shouldReplace(query, best, node->point)){--need to calculate the dis to the plane, it is insufficient to only check those two point in shouldReplace
  //std::cout << __LINE__  << "planeDistSquared: " << planeDist * planeDist << ", bestSquared: " << bestSquared << std::endl;

  if (planeDist * planeDist <= bestSquared) {
    best = findNearest(farSubtree, query, depth + 1, best);
  }
  return best;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if(root == nullptr) throw std::runtime_error("KDTree is empty.");
    Point<Dim> best = root->point;
    //double bestDist = distanceSquared(query, best);
    return findNearest(root, query, 0, best);
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */    
    if(start == end || k < start || k >= end) throw std::out_of_range("Invalid range or k is out of bounds.");
    quickselect(start, end, k, cmp);
    
}

// Helper function to partition the range using iterators
template <typename RandIter, typename Comparator>
RandIter partition(RandIter start, RandIter end, RandIter pivot, Comparator cmp) {
   auto pivotValue = *pivot;
   std::iter_swap(pivot, end - 1);
   RandIter storeIndex = start;
   for(RandIter i = start; i < end - 1; ++i){
    if(cmp(*i, pivotValue)){
      std::iter_swap(i, storeIndex);
      ++storeIndex;
    }
   }
   std::iter_swap(storeIndex, end - 1);
   return storeIndex;
}

// Quickselect function using iterators and comparator
template <typename RandIter, typename Comparator>
void quickselect(RandIter start, RandIter end, RandIter k, Comparator cmp) {
   if(start == end) return;
   RandIter pivot = start + std::distance(start, end)/2;
   RandIter pivotPos = partition(start, end, pivot, cmp);
   if(pivotPos == k){
    return;//// The k-th smallest element is now at position k
   }else if(k < pivotPos){
    quickselect(start, pivotPos, k, cmp);
   }else{
    quickselect(pivotPos + 1, end, k, cmp);
   }
}


