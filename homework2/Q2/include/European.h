//
// Created by DELL on 2020/4/29.
//

#ifndef Q2_EUROPEAN_H
#define Q2_EUROPEAN_H

#include "Option.h"

class EuropeanOption: public Option{
public:
    EuropeanOption(string type, double strike, double spot, double rate,
                   double volatility, double timeToMature, int N):
                   Option(type, strike, spot, rate, volatility, timeToMature, N) {};
    double getPrice();
};


double EuropeanOption::getPrice() {
    u = exp(volatility*pow(timeToMature/N, 0.5));
    d = exp(-volatility*pow(timeToMature/N, 0.5));
    p = (exp(rate*timeToMature/N)-d)/(u-d);
    q = 1-p;
    direction.clear();
    int column = N+1;
    int row = pow(2, N);
    stockPrice.resize(row);
    for (unsigned i = 0; i < row; ++i) { stockPrice[i].resize(column); }
    price = stockPrice; // don't need to resize again

    for (int i = 0; i < row; ++i) { stockPrice[i][0] = spot; }
    vector<int> helpVec; // odd means corresponding up in this period
    for (int j = 1; j < column; j++) {
        helpVec.clear();
        for (int k = 0; k < pow(2, j); ++k) {
            for (int i = 0; i < pow(2, N-j); ++i) {
                helpVec.push_back(k+1);
            }
        }
        direction.resize(row);
        for (int i = 0; i < row; i++) {
            if (helpVec[i] % 2 == 0){
                stockPrice[i][j] = stockPrice[i][j-1] * d;
                direction[i].append("T");
            } else {
                stockPrice[i][j] = stockPrice[i][j-1] * u;
                direction[i].append("H");
            }
        }
    }

    //cout << "Finish calculating stock price." << endl;
    // printMatrix(stockPrice);

    vector<double> optionPrice, optionPrice1;

    if(type == "call"){
        for (int i = 0; i < row; ++i) {
            price[i][column-1] = getMax(0, stockPrice[i][column-1] - strike);
            optionPrice.push_back(price[i][column-1]);
        }
    }else {
        for (int i = 0; i < row; ++i) {
            price[i][column-1] = getMax(0, strike-stockPrice[i][column-1]);
            optionPrice.push_back(price[i][column-1]);
        }
    };

    //cout << "Finish calculating end prices." << endl;

    double intermediate;
    for (int j = column-2; j > -1; j--) {

        for (int k = 0; k < optionPrice.size(); ++k) {
            if (k % 2 != 0){
                intermediate = (optionPrice[k-1]*p+optionPrice[k]*q)*exp(-rate*timeToMature/N);
                optionPrice1.push_back(intermediate);
                //cout << optionPrice[k-1] << " and " << optionPrice[k] << " and " << intermediate << endl;
            }
        }
        optionPrice = optionPrice1;
        optionPrice1.clear();
        for (int m = 0; m < optionPrice.size(); m++) {
            for (int l = 0; l < pow(2, column-1-j); l++) {
                optionPrice1.push_back(optionPrice[m]);
            }
        }
        for (int n = 0; n < row; n++) {
            price[n][j] = optionPrice1[n];
        }
        optionPrice1.clear();
    }
    //cout << "Finish calculating option price." << endl;
    //printMatrix(price);
    return price[0][0];
}

#endif //Q2_EUROPEAN_H
