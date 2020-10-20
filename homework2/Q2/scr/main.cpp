
#include "American.h"
#include "European.h"

void OutputFun(Option& Opt){
    cout << "Delta greek:" << Opt.getDelta() << endl;
    cout << "Rho greek: " << Opt.getRho() << endl;
    cout << "Theta greek: " << Opt.getTheta() << endl;
    cout << "Vega greek: " << Opt.getVega() << endl;
}

int main() {

    AmericanOption American1("call", 105, 100, 0.05, 0.2, 1, 3);
    EuropeanOption European1("call", 105, 100, 0.05, 0.2, 1, 3);
    AmericanOption American2("put", 90, 100, 0.05, 0.2, 1, 3);
    EuropeanOption European2("put", 90, 100, 0.05, 0.2, 1, 3);

    cout << "American call price: " << American1.getPrice() << endl;
    cout << "American put price: " << American2.getPrice() << endl;
    cout << "European call price: " << European1.getPrice() << endl;
    cout << "European put price: " << European2.getPrice() << endl;

    cout << "\n" << "European Call Greeks" << endl;
    OutputFun(European1);
    cout << "\n" << "European Put Greeks" << endl;
    OutputFun(European2);
    cout << "\n" << "American Call Greeks" << endl;
    OutputFun(American1);
    cout << "\n" << "American Put Greeks" << endl;
    OutputFun(American2);

    return 0;
}
