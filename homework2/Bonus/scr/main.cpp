#include "std_lib_facilities.h"
#include "bonus.h"


int main()
{
    SortedList<double> LIST;
    LIST.insertValue(2.0);
    LIST.insertValue(3.0);
    LIST.insertValue(5.5);
    LIST.insertValue(0.2);
    LIST.insertValue(0.2);
    LIST.insertValue(0.01);
    LIST.insertValue(6.6);

// Test print out function
    LIST.printBackward();
    LIST.printForward();
// Test removeFront and Test remove Last
    pair<bool, double> result;
    result = LIST.removeFront();
    cout << "bool: " << result.first << " , front value: " << result.second << endl;
    result = LIST.removeBack();
    cout << "bool: " << result.first << " , front value: " << result.second << endl;
    LIST.printForward();
// Test getNumElems() function
    cout << "The number of elements in the LIST is: " << LIST.getNumElems() << endl;
// Test bool getElemAtIndex function
    cout << LIST.getElemAtIndex(3).first << endl;
    cout << "The 3rd elements in the array is(index starts at 0): " << LIST.getElemAtIndex(3).second << endl;
// Test the copy constructor and = operator
    cout << "construct new linked list from copy constructor: "<< endl;
    SortedList<double> LIST_copy(LIST);
    LIST_copy.printForward();
    cout << "construct new linked list from assingment operator = : "<< endl;
    SortedList<double> LIST_equal = LIST;
    LIST_equal.printForward();
// Test the clear function:
    cout << "The number of elements in the LIST is: " << LIST.getNumElems() << endl;
    LIST.clear();
    cout <<"Now the number of elements in the LIST is: " << LIST.getNumElems() << endl;
    return 0;
}


