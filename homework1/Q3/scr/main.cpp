#include "std_lib_facilities.h"
#include "Q3.h"

// Details of functions are all included in header file "homework1.h"


int main(){
    // Problem 3
    Money money1("$1.3221"), money2("$22.0029");
//    Money money3 = money2 + money1;
//    cout << money2 << " + " << money1 << " = " << money3 << endl;
//    Money money4 = money2 - money1;
//    cout << money2 << " + " << money1 << " = " << money4 << endl;
//    Money money5_1 = money2 * 2;
//    cout << money2 << " times " << 2 << " = " << money5_1 << endl;
//    Money money5_2 = money2 * 0.25;
//    cout << money2 << " times " << 0.25 << " = " << money5_2 << endl;
//    Money money6_1 = money2 / 4;
//    cout << money2 << " divided by " << 4 << " = " << money6_1 << endl;
//    Money money6_2 = money2 / 0.5;
//    cout << money2 << " divided by " << 0.5 << " = " << money6_2 << endl;


    Money money7;
    Money money8 = money1;
    if (money1 == money2)  cout << "money1 = money2" << endl;
    else cout << "money1 not equal to money2" << endl;
    if (money1 == money8) cout << "money1 = money8" << endl;
    else cout << "money1 not equal to money8" << endl;
    if (money1 == "$1.3221") cout << "money1 = $1.3221" << endl;
    else cout << "money1 not equal to $1.3221" << endl;

    cin >> money7;
    cout << money7;

    return 0;
}




