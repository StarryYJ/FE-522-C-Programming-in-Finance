#include "Q1.h"



int main() {
    cout << "American call: " ;
    AmericanOption AOption1("Call", 105, 100, 0.05, 0.2, 1, 3);
    cout << AOption1.getPrice() << endl;

    cout << "American put: " ;
    AmericanOption AOption2("put", 95, 100, 0.05, 0.2, 1, 3);
    cout << AOption2.getPrice() << endl;

    AmericanOption AOptionTEST1("both", 105, 100, 0.05, 0.2, 1, 3);
    //AmericanOption AOptionTEST2("call", 105, 100, 0.05, 5, 1, 3);

    return 0;
}
