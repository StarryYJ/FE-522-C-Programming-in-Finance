#include "std_lib_facilities.h"
#include "LinkNode.h"



int main()
{
    SortedList LIST;
    LIST.insertValue(2.0);
    LIST.insertValue(3.0);
    LIST.insertValue(5);
    LIST.insertValue(0);
    LIST.insertValue(2);
    LIST.insertValue(1);
// Test print out function
    LIST.printBackward();
    LIST.printForward();
// Test removeFront and Test remove Last
    pair<bool, int> result;
    result = LIST.removeFront();
    cout << "bool: " << result.first << " , front value: " << result.second << endl;
    result = LIST.removeBack();
    cout << "bool: " << result.first << " , front value: " << result.second << endl;
    LIST.printForward();
// Test bool getElemAtIndex function
    cout << LIST.getElemAtIndex(3).first << endl;
    cout << "The 3rd elements in the array is(index starts at 0): " << LIST.getElemAtIndex(3).second << endl;
// Test the copy constructor and = operator
    cout << "construct new linked list from copy constructor: "<< endl;
    SortedList LIST_copy(LIST);
    LIST_copy.printForward();
    cout << "construct new linked list from assingment operator = : "<< endl;
    SortedList LIST_equal = LIST;
    LIST_equal.printForward();
// Test getNumElems() function and the clear function:
    cout << "The number of elements in the LIST is: " << LIST.getNumElems() << endl;
    LIST.clear();
    cout <<"Now the number of elements in this linked list is: " << LIST.getNumElems() << endl;

    return 0;
}




