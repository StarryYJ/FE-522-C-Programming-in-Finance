#include "std_lib_facilities.h"
#include "Q4Q5.h"
#include <fstream>
#include <iomanip>


int main() {
    // Problem 4:
    EuropeanOption option1("call", 100, 105, 0.05, 0.2, 1);
    cout << option1.getPrice() << endl;

    EuropeanOption option2("put", 100, 105, 0.05, 0.2, 1);
    cout << option2.getPrice() << endl;

    EuropeanOption option3("call", 100, 105, 0.05, 0.2, -1);

    return 0;
}




