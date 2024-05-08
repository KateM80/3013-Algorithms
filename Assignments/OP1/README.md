## OP1 - Vector Class
### Kate Morgan
### Description:

Optional program. Uses a singly linked list as the backend for an STL like "vector" class definition.
This program was made by me for OOP in spring 2023, I was given permision to just reupload it here. 
### Files

|   #   | File             | Description                                        |
| :---: | ---------------- | -------------------------------------------------- |
|   1   | [main.cpp](OP1/main.cpp)       | Main file for running the program|
| 2 | [output.txt] | Sample output file | 


### Instructions
## Requirements

- Your class will be a basic container type of integers that can grow or shrink easily without the need to copy values over to newly allocated memory when resizing (I will explain this more in class).
- Initializing your class instance:
  - From an array
    - `V1 = new (int *A, int size)` : *adds each item from an array type*
  - From a file 
    - `V1 = new Vector(string FileName)` : *read until eof loading each value into list* 
  - From another instance of same type 
    - `V2 = new Vector(Vector V1)` : *traverse* `other.list` *adding each value to* `this.list`
- Adding items to your class instance:
  - To the front
    - `V.pushFront(int val)` : *adds single value to front of* `this.list`
    - `V.pushFront(Vector V2)`: *adds entire* `other.list` *to front of* `this.list`
  - To the rear
    - `V.pushRear(int val)` : *adds single value to rear of* `this.list`
    - `V.pushRear(Vector V2)` : *adds entire* `other.list` *to rear of* `this.list`
  - At a specified location (if it exists)
    - `V.pushAt(int loc,int val)`
  - In ascending or descending order (order set by constructor or setter)
    - `V.inOrderPush(int val)` : *adds single value to proper location in order to maintain order (ascending or descending)*
    - This requires the list to be sorted from the beginning. We can discuss this more in class.
- Removing items from a class instance:
  - From the front
    - `val = V.popFront()` : *removes single value from front of list*
  - From the rear
    - `val = V.popRear()` : *removes single value from rear of list*
  - A specified location
    - `val = V.popAt(int loc)` : *removes single value from an indexed location if index between* `0 and size of list -1`
  - By a search than removal (if it exists)
    - `loc = V.find(int val)`  : *find location of item (index) if it exists*
    - `val = V.popAt(int loc)`) : *then use index to remove item*
- Printing
  - Output should look similar to: [v<sub>1</sub>, v<sub>2</sub>, v<sub>3</sub>, ... , v<sub>n</sub>]
