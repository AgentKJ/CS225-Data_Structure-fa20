/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
using namespace std;
#include <iostream>
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    tail_ = head_->next;
    delete head_;
    head_ = tail_;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    newNode -> next = head_;
    head_ -> prev = newNode;
    head_ = newNode;
    length_++;
  } else if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
    length_++;
  }


}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  
  if (tail_ != NULL) {
    newNode -> prev = tail_;
    tail_-> next = newNode;
    tail_ = newNode;
    length_++;
  } else if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
    length_++;
  }

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1

  /*ListNode * curr = start;
  ListNode * temp;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    temp = curr;
    curr = curr->next;
  }

  if (curr != NULL) {
    curr->prev = NULL;
  }
  if (temp != NULL) {
    temp->next = NULL;
  }

  return curr;*/
  ListNode *curr = start;

  for (int i = 0; i < splitPoint - 1 && curr != NULL; i++) {
    if (curr->next != NULL) {
      curr = curr->next;
    }
  }

  if (curr != NULL) {
      curr = curr->next;
      curr->prev->next = NULL;
      tail_ = curr->prev;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode *curr = head_;
  ListNode *temp = NULL;
  bool test = true;
  while (curr != NULL) {
    if (curr->next == NULL || curr->next->next == NULL) {
      break;
    }
    if (curr->prev != NULL) {
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
    } else {
      curr->next->prev = NULL;
    }
    
    if (test) {
      head_ = curr->next;
      test = false;
    }
    curr->prev = curr->next->next;

    if (curr->next->next->next == NULL) {
      curr->next = NULL;
    } else {
      curr->next = curr->next->next->next;
      curr->next->prev = curr;
    }
    curr->prev->next = curr;
    temp = curr;
    curr = curr->next;
  }
  tail_ = temp;
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL) {
    return;
  }

  ListNode *leftend = startPoint->prev;
  ListNode *rightend = endPoint->next;
  ListNode *start = startPoint;
  ListNode *end = endPoint;

  ListNode *curr = startPoint;
  ListNode *temp = NULL;

  while (curr != endPoint) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }
  curr->next = curr->prev;
  curr->prev = leftend;
  startPoint->next = rightend;
  if (leftend != NULL) {
    leftend->next = endPoint;
  } else {
    head_ = endPoint;
  }

  if (rightend != NULL) {
    rightend->prev = startPoint;
  } else {
    tail_ = startPoint;
  }


  startPoint = end;
  endPoint = start;

  return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n > 1 && head_ != NULL) {
    ListNode *startPoint = head_;
    while (startPoint != NULL) {
      ListNode *endPoint = startPoint;
      for (int i = 0; i < n - 1; i++) {
        if (endPoint->next != NULL) {
          endPoint = endPoint->next;
        }
      }

      reverse(startPoint, endPoint);
      startPoint = endPoint->next;
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // Go till the tail of the list
    if (tail_ != NULL) {
        while (tail_->next != NULL) {
          tail_ = tail_->next;
        }     
    }

    length_ = length_ + otherList.length_;

    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode *first, ListNode *second) {
  /// @todo Graded in MP3.2
  
  // Check if any is empty
  if (!first && !second) {
    return NULL;
  } else if (!first) {
    return second;
  } else if (!second) {
    return first;
  }

  ListNode *temp;
  ListNode *toReturn;
  ListNode *headFirst = first;
  ListNode *headSecond = second;

  // Set the first node of the result
  if (first->data < second->data) {
    toReturn = headFirst;
    headFirst = headFirst->next;
  } else {
    toReturn = headSecond;
    headSecond = headSecond->next;
  }

  temp = toReturn;

  // Do till both list are empty
  while (headSecond != NULL && headFirst != NULL) {
    // If there's no more in the first list
    if (headFirst == NULL) {
      if (headSecond == NULL) {
        break;
      } else {
        temp->next = headSecond;
        temp->next->prev = temp;
        temp = temp->next;
        headSecond = headSecond->next;
      }
    } else if (headSecond->data < headFirst->data && headSecond != NULL) {
      temp->next = headSecond;
      temp->next->prev = temp;
      temp = temp->next;
      headSecond = headSecond->next;
    } else {
      temp->next = headFirst;
      temp->next->prev = temp;
      temp = temp->next;
      headFirst = headFirst->next;
    }
  }

  if (headSecond == NULL) {
    temp->next = headFirst;
    headFirst->prev = temp;
  }
  if (headFirst == NULL) {
    temp->next = headSecond;
    headSecond->prev = temp;
  }

  return toReturn;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start->next == NULL) {
    return start;
  } else {
    int splitPoint = chainLength / 2;
    ListNode *half = split(start, splitPoint);
    return merge(mergesort(start, splitPoint), mergesort(half, (chainLength % 2) + splitPoint));
  }
}
