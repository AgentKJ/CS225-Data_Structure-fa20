/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim]) {
      return first < second;
    }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int currentDist = 0;
    int potentialDist = 0;
    for (int i = 0; i < Dim; i++) {
      currentDist += ((currentBest[i] - target[i]) * (currentBest[i] - target[i]));
      potentialDist += ((potential[i] - target[i]) * (potential[i] - target[i]));
    }
    currentDist = sqrt(currentDist);
    potentialDist = sqrt(potentialDist);
    if (currentDist == potentialDist) {
      return currentBest > potential;
    } else {
      return currentDist > potentialDist;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = newPoints.size();
    points = newPoints;
    root = NULL;
    if (size != 0) {
      root = new KDTreeNode();
      buildTree(root, newPoints, 0);
    }
}

template <int Dim>
void KDTree<Dim>::buildTree(KDTreeNode* subroot, vector<Point<Dim>> newPoints, int curDim) {
  newPoints = sort(newPoints, curDim);
  vector<Point<Dim>> smaller, larger;
  
  int median = (newPoints.size() - 1) / 2;
  subroot->point = newPoints[median];
  subroot->left = NULL;
  subroot->right = NULL;

  for (int i = 0; i < median; i++) {
    smaller.push_back(newPoints[i]);
  }
  for (int i = median + 1; i < (int) newPoints.size(); i++) {
    larger.push_back(newPoints[i]);
  }
  if (!smaller.empty()) {
    subroot->left = new KDTreeNode();
    buildTree(subroot->left, smaller, (curDim + 1) % Dim);
  }
  if (!larger.empty()) {
    subroot->right = new KDTreeNode();
    buildTree(subroot->right, larger, (curDim + 1) % Dim);
  }
}

template <int Dim>
vector<Point<Dim>> KDTree<Dim>::sort(vector<Point<Dim>> newPoints, int curDim) {
  vector<Point<Dim>> sorted;
  while (!newPoints.empty()) {
    Point<Dim> smallest = newPoints[0];
    int index = 0;
    for (int i = 1; i < (int) newPoints.size(); i++) {
      if (smallerDimVal(newPoints[i], smallest, curDim)) {
        smallest = newPoints[i];
        index = i;
      }
    }
    sorted.push_back(smallest);
    newPoints.erase(newPoints.begin() + index);
  }
  return sorted;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if (size == 0) {
      return Point<Dim>();
    } else {
      return findNearestNeighbor(query, root, 0);
    }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTree<Dim>::KDTreeNode *current, int curDim) const
{
  Point<Dim> currentBest;
  if (smallerDimVal(query, current->point, curDim)) {
    if (current->left) {
      currentBest = findNearestNeighbor(query, current->left, (curDim + 1) % Dim);
    }
    if (shouldReplace(query, currentBest, current->point)) {
      currentBest = current->point;
    }

    double potentialDist = (current->point[curDim] - query[curDim]) * (current->point[curDim] - query[curDim]);
    double currentDist = 0;
    for (int i = 0; i < Dim; ++i) {
      currentDist += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
    }
    potentialDist = sqrt(potentialDist);
    currentDist = sqrt(currentDist);

    if (potentialDist <= currentDist) {
      if (current->right) {
        if (shouldReplace(query, currentBest, findNearestNeighbor(query, current->right, (curDim + 1) % Dim))) {
          currentBest = findNearestNeighbor(query, current->right, (curDim + 1) % Dim);
        }
      }
    }
  } else {
    if (current->right) {
      currentBest = findNearestNeighbor(query, current->right, (curDim + 1) % Dim);
    }
    if (shouldReplace(query, currentBest, current->point)) {
      currentBest = current->point;
    }

    double potentialDist = (current->point[curDim] - query[curDim]) * (current->point[curDim] - query[curDim]);
    double currentDist = 0;
    for (int i = 0; i < Dim; ++i) {
      currentDist += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
    }
    potentialDist = sqrt(potentialDist);
    currentDist = sqrt(currentDist);

    if (potentialDist <= currentDist) {
      if (current->left) {
        if (shouldReplace(query, currentBest, findNearestNeighbor(query, current->left, (curDim + 1) % Dim))) {
          currentBest = findNearestNeighbor(query, current->left, (curDim + 1) % Dim);
        }
      }
    }
  }
  
  return currentBest;
}

