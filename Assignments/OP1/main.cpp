/*****************************************************************************
 *
 *  Title:            Doubly linked list vector implementation
 *  Course:           2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        Uses a singly linked list as the backend for an STL like "vector"
 *        class definition.
 *
 *  Usage:
 *        Use it like a vector program
 *
 *  Files: main.cpp
 *         output.txt
 *****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000 // infinity

using namespace std;

// Node for our linked list
struct Node {
  int data;

  Node *next;

  Node(int x) {
    data = x;
    next = NULL;
  }
};
/**
 * MyVector
 *
 * Description:
 *      Uses a doubly linked list to create a vector class.
 *
 * Public Methods:
 *      MyVector() { init(); }
 *      MyVector(int A[], int aSize)
 *      MyVector(string FileName)
 *      MyVector(const MyVector &other)
 *      void init()
 *      void inorderPush(int x)
 *      void sortList()
 *      void pushFront(int x)
 *      void pushFront(const MyVector &other)
 *      void pushRear(const MyVector &other)
 *      bool pushAt(int i, int x)
 *      void pushRear(int x)
 *      void Print(MyVector V1)
 *      void destroy()
 *      int Find(int key)
 *      Node *_Find(int index)
 *      void operator<<(const MyVector &rhs)
 *      friend ostream &operator<<(ostream &os, const MyVector &rhs)
 *      int operator[](int index)
 *      MyVector operator=(const MyVector &rhs)
 *      MyVector operator==(const MyVector &rhs)
 *      MyVector operator+(const MyVector &rhs)
 *      MyVector operator*(const MyVector &rhs)
 *      MyVector operator/(const MyVector &rhs)
 *      MyVector operator-(const MyVector &rhs)
 *
 * Private Methods:
 *      void _inorderPush(int x)
 *
 * Usage:
 *
 *
 */
class MyVector {
private:
  Node *head; // base pointer of list
  Node *tail;
  int size;
  static ofstream fout;
  string fileName;
  bool sorted;

  /**
   * @brief Private version of inOrder push.
   *
   * @param x
   */
  void _inorderPush(int x) {
    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (curr->data > x) { // loop to find proper location
      prev = curr;
      curr = curr->next;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
  }

public:
  /**
   * @brief Default constructor
   *
   */
  MyVector() { init(); }

  /**
   * @brief Overloaded Constructor
   *
   * @param int   *A - pointer to array
   * @param int   aSize - size of array
   */
  MyVector(int A[], int aSize) {
    init();

    for (int i = 0; i < aSize; i++) {
      pushRear(A[i]);
    }
  }

  /**
   * @brief Overloaded Constructor
   *
   * @param string FileName - file to open and read
   *
   * Assumes infile will contain numbers only delimited by spaces or
   * new lines.
   */
  MyVector(string FileName) {
    init();

    ifstream fin;
    int x = 0;

    fin.open(FileName);
    while (!fin.eof()) {
      fin >> x;
      pushRear(x);
    }
  }

  /**
   * @brief Copy Constructor
   *
   * @param MyVector &other
   */
  MyVector(const MyVector &other) {
    init();

    Node *temp = other.head;

    while (temp) {
      pushRear(temp->data);
      temp = temp->next;
    }
  }

  /**
   * @brief - Initialize the data members so we don't
   *      have duplicate lines in each constructor.
   *
   */
  void init() {
    head = tail = NULL;
    fileName = "";
    size = 0;
    sorted = 0;
  }

  /**
   * @brief Public version of inOrder push.
   *
   * @param x
   */
  void inorderPush(int x) {
    if (!sorted) {
      sortList();
    }

    if (!head) {
      pushFront(x); // call push front for empty list (or pushRear would work)
    } else if (x < head->data) {
      pushFront(x); // call push front if x is less than head
    } else if (x > tail->data) {
      pushRear(x); // call push rear if x > tail
    } else {
      _inorderPush(x); // call private version of push in order
    }
  }

  /**
   * @brief Sort the current values in the linked list.
   *
   * @returns None
   */
  void sortList() {
    Node *newFront = head;
    while (newFront->next) {
      Node *smallest = newFront;
      Node *current = newFront;
      int minimum = INF;
      while (current) {
        if (current->data < minimum) {
          smallest = current;
          minimum = current->data;
        }
        current = current->next;
      }
      smallest->data = newFront->data;
      newFront->data = minimum;
      newFront = newFront->next;
    }
    sorted = true;
  }

  /**
   * @brief Add value to front of list.
   *
   * @param x
   */
  void pushFront(int x) {
    Node *tempPtr = new Node(x);

    // empty list make head and tail
    // point to new value
    if (!head) {
      head = tail = tempPtr;
      // otherwise adjust head pointer
    } else {
      tempPtr->next = head;
      head = tempPtr;
    }
    size++;
  }

  /**
   * @brief This method loads values from 'other' list in 'this' list.
   *          It loads an array first so we can process the values in
   *          reverse so they end up on 'this' list in the proper order.
   *          If we didn't use the array, we would reverse the values
   *          from the 'other' list.
   *
   * @depends - Uses `pushFront(int)`
   * @param MyVector& other
   * @return None
   */
  void pushFront(const MyVector &other) {
    Node *otherPtr = other.head;         // get copy of other lists head
    int *tempData = new int[other.size]; // allocate memory to hold values

    // load other list into array
    int i = 0;
    while (otherPtr) {
      tempData[i] = otherPtr->data;
      otherPtr = otherPtr->next;
      ++i;
    }

    // process list in reverse in order to keep them
    // in their original order.
    for (int i = other.size - 1; i >= 0; i--) {
      pushFront(tempData[i]);
    }
  }

  /**
   * @brief -  Add 'other' list's values to end of 'this' list.
   * @note - Uses `pushRear(int)`
   * @param MyVector& other
   * @return None
   */
  void pushRear(const MyVector &other) {
    Node *otherPtr = other.head; // get copy of other lists head

    while (otherPtr) { // traverse and add
      pushRear(otherPtr->data);
      otherPtr = otherPtr->next;
    }
  }

  /**
   * @brief Push value onto list at soecified position, if it exists.
   *
   * @param int i - location index
   * @param inr x - value to add
   * @return bool - true add successful / false add failed
   */
  bool pushAt(int i, int x) {
    if (i >= size) {
      return false;
    }

    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (i > 0) { // loop to find proper location
      prev = curr;
      curr = curr->next;
      i--;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
    return true;
  }

  /**
   * @brief - Add value to rear of list
   *
   * @param int x - value to be added
   * @return None
   */
  void pushRear(int x) {
    Node *tempPtr = new Node(x);

    if (!head) {
      head = tail = tempPtr;

    } else {
      tail->next = tempPtr;
      tail = tempPtr;
    }
    size++; // add to size of list
  }

  /**
   * @brief Destroy the My Vector object
   *
   */
  /* ~MyVector() {
     Node *curr = head;
     Node *prev = head;

     while (curr) {
       prev = curr;
       curr = curr->next;
       cout << "deleting: " << prev->data << endl;
       delete prev;
     }
   }*/

  /**
   * @brief - Print the Vector to console
   *
   * @param MyVector V1
   * @return None
   */
  void Print(MyVector V1) {
    Node *trav = V1.head;     // temp pointer copies head
    while (trav != nullptr) { // this loops until temp is NULL
      cout << trav->data;
      if (trav->next) {
        cout << ", ";
      }
      trav = trav->next;
    }
  }

  /**
   * @brief - Destorys the Vector
   *
   * @param none
   * @return None
   */
  void destroy() {
    Node *prev = head;        // temp pointer copies head
    Node *curr = head;        // temp pointer copies head
    while (curr != nullptr) { // this loops until temp is NULL
      prev = curr;
      curr = curr->next;
      delete prev;
    }
    head = tail = nullptr;
  }

  /**
   * @brief - Finds a key in the vector
   *
   * @param int key
   * @return int - index number
   */
  int Find(int key) {
    Node *trav = head; // temp pointer copies head
    int index = 0;

    while (trav) { // this loops until temp is NULL
      if (trav->data == key) {
        return index;
      }
      trav = trav->next; // move to next Node
      index++;
    }
    return -1;
  }

  /**
   * @brief - finds the key in the vector
   *
   * @param int index
   * @return node find
   */
  Node *_Find(int index) {
    Node *trav = head; // temp pointer copies head

    while (trav && index--) { // this loops until index is empty
      trav = trav->next;      // move to next Node
    }
    return trav;
  }

  /**
   * @brief - Overrides the << operator
   *
   * @param const MyVector &rhs
   * @return none
   */
  void operator<<(const MyVector &rhs) {
    Node *trav = rhs.head;    // temp pointer copies head
    while (trav != nullptr) { // this loops until temp is NULL
      cout << trav->data;     // print data from Node
      if (trav->next) {
        cout << ", ";
      }
      trav = trav->next; // move to next Node
    }
    cout << endl;
  }

  /**
   * @brief - Overrides the << operator
   *
   * @param const MyVector &rhs,ostream &os
   * @return ostream
   */
  friend ostream &operator<<(ostream &os, const MyVector &rhs) {
    Node *temp = rhs.head; // temp pointer copies head

    while (temp) { // this loops until temp is NULL
                   // same as `while(temp != NULL)`

      os << temp->data; // print data from Node
      if (temp->next) {
        os << ", ";
      }
      temp = temp->next; // move to next Node
    }
    os << endl;
    return os;
  }

  /**
   * @brief - Overrides the [] operator
   *
   * @param int index
   * @return int
   */
  int operator[](int index) {
    Node *temp = _Find(index);
    return temp->data;
  }

  /**
   * @brief - Overrides the = operator
   *
   * @param const MyVector &rhs
   * @return MyVector
   */
  MyVector operator=(const MyVector &rhs) {
    if (this == &rhs) {
      return rhs;
    }
    if (head) {
      this->destroy();
    }

    Node *trav = rhs.head; // temp pointer copies head

    while (trav != nullptr) { // this loops until temp is NULL
      this->pushRear(trav->data);
      trav = trav->next; // move to next Node
    }
    return *this;
  }

  /**
   * @brief - Overrides the == operator
   *
   * @param const MyVector &rhs
   * @return MyVector
   */
  MyVector operator==(const MyVector &rhs) {
    Node *trav = rhs.head;    // temp pointer copies head
    Node *temp = this->head;  // temp pointer copies head
    while (trav != nullptr) { // this loops until temp is NULL
      if (temp->data == trav->data) {
        trav = trav->next; // move to next Node
        temp = temp->next; // move to next Node
      } else {
        cout << "0\n";
        return rhs;
      }
    }
    cout << "1\n";
    return rhs;
  }

  /**
   * @brief - Overrides the + operator
   *
   * @param const MyVector &rhs
   * @return MyVector
   */
  MyVector operator+(const MyVector &rhs) {
    MyVector V;
    Node *less;    // temp pointer copies head
    Node *greater; // temp pointer copies head
    if (rhs.size < this->size) {
      less = rhs.head;
      greater = this->head;

    } else {
      greater = rhs.head;
      less = this->head;
    }
    while (less != nullptr) { // this loops until temp is NULL
      V.pushRear(less->data + greater->data);
      less = less->next;       // move to next Node
      greater = greater->next; // move to next Node
    }
    while (greater != nullptr) { // this loops until temp is NULL
      V.pushRear(greater->data);
      greater = greater->next; // move to next Node
    }
    return V;
  }

  /**
   * @brief - Overrides the * operator
   *
   * @param const MyVector &rhs
   * @return MyVector
   */
  MyVector operator*(const MyVector &rhs) {
    MyVector V;
    Node *less;    // temp pointer copies head
    Node *greater; // temp pointer copies head
    if (rhs.size < this->size) {
      less = rhs.head;
      greater = this->head;

    } else {
      greater = rhs.head;
      less = this->head;
    }
    while (less != nullptr) { // this loops until temp is NULL
      V.pushRear(less->data * greater->data);
      less = less->next;       // move to next Node
      greater = greater->next; // move to next Node
    }
    while (greater != nullptr) { // this loops until temp is NULL
      V.pushRear(greater->data);
      greater = greater->next; // move to next Node
    }
    return V;
  }

  /**
   * @brief - Overrides the / operator
   *
   * @param const MyVector &rhs
   * @return MyVector
   */
  MyVector operator/(const MyVector &other) {
    MyVector V;
    Node *rhs; // temp pointer copies head
    Node *lhs; // temp pointer copies head

    rhs = other.head;
    lhs = this->head;

    while (rhs && lhs) { // this loops until temp is NULL
      V.pushRear(lhs->data / rhs->data);
      rhs = rhs->next; // move to next Node
      lhs = lhs->next; // move to next Node
    }
    while (rhs) {
      V.pushRear(rhs->data);
      rhs = rhs->next;
    }
    while (lhs) {
      V.pushRear(lhs->data);
      lhs = lhs->next;
    }
    return V;
  }

  /**
   * @brief - Overrides the - operator
   *
   * @param const MyVector &rhs
   * @return MyVector
   */
  MyVector operator-(const MyVector &other) {
    MyVector V;
    Node *rhs; // temp pointer copies head
    Node *lhs; // temp pointer copies head

    rhs = other.head;
    lhs = this->head;

    while (rhs && lhs) { // this loops until temp is NULL
      V.pushRear(lhs->data - rhs->data);
      rhs = rhs->next; // move to next Node
      lhs = lhs->next; // move to next Node
    }
    while (rhs) {
      V.pushRear(rhs->data);
      rhs = rhs->next;
    }
    while (lhs) {
      V.pushRear(lhs->data);
      lhs = lhs->next;
    }
    return V;
  }
};

int main() {
  int a1[] = {1, 2, 3, 4, 9};
  int a2[] = {10, 20, 30};

  MyVector v1(a1, 5);
  MyVector v2(a2, 3);

  ofstream fout;
  fout.open("output.txt");

  cout << v1[2] << endl;
  // writes out 3

  //   v1[4] = 9;
  //   v1 now = [1,2,3,4,9]

  cout << v1 << endl;
  //  writes out [1,2,3,4,9] to console.

  fout << v1 << endl;
  // writes out [1,2,3,4,9] to your output file.

  MyVector v3 = v1 + v2;
  cout << v3 << endl;
  // writes out [11,22,33,4,9] to console.

  v3 = v1 - v2;
  cout << v3 << endl;
  // writes out [-9,-18,-27,4,9] to console.

  v3 = v2 - v1;
  cout << v3 << endl;
  //  writes out [9,18,27,4,9] to console.

  v3 = v2 * v1;
  cout << v3 << endl;
  // writes out [10,40,90,4,9] to console.

  v3 = v1 * v2;
  cout << v3 << endl;
  // writes out [10,40,90,4,9] to console.

  v3 = v1 / v2;
  cout << v3 << endl;
  // writes out [0,0,0,4,9] to console.

  v3 = v2 / v1;
  cout << v3 << endl;
  // writes out [10,10,10,4,9] to console.

  cout << (v2 == v1) << endl;
  //  writes 0 to console (false) .

  MyVector v4 = v1;
  cout << (v4 == v1) << endl;
  //  writes 1 to console (true) .
}