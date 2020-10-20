//
// Created by DELL on 2020/3/8.
//

#ifndef Q1_Q1_H
#define Q1_Q1_H

#include "Option.h"



class AmericanOption: public Option{
public:
    AmericanOption(string type, double strike, double spot, double rate,
                   double volatility, double timeToMature, int N):
                   Option(type, strike, spot, rate, volatility, timeToMature, N) {};
    double getPrice();
};



double AmericanOption::getPrice() {
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

//    cout << "Finish calculating end prices." << endl;
    //cout << " Stock price: " << endl;
    //printMatrix(stockPrice);

    double intermediate;
    for (int j = column-2; j > -1; j--) {

        for (int k = 0; k < optionPrice.size(); ++k) {
            if (k % 2 != 0){
                intermediate = (optionPrice[k-1]*p+optionPrice[k]*q)/(1+rate);
                //cout << "A " << optionPrice[k-1] << " and " << optionPrice[k] << " and " << 1+rate << endl;
                //*exp(-rate*timeToMature/N)
                optionPrice1.push_back(intermediate);
                //cout << optionPrice[k-1] << " and " << optionPrice[k] << " and " << intermediate << endl;
            }
        }
        optionPrice = optionPrice1;
        //show(optionPrice);
        optionPrice1.clear();
        for (int m = 0; m < optionPrice.size(); m++) {
            for (int l = 0; l < pow(2, column-1-j); l++) {
                optionPrice1.push_back(optionPrice[m]);
            }
        }
        //show(optionPrice1);
        //show(optionPrice);
        for (int n = 0; n < row; n++) {
            if (type == "call"){
                price[n][j] = max(stockPrice[n][j]-strike, optionPrice1[n]);
                optionPrice1[n] = price[n][j];
            }else{
                price[n][j] = max(strike-stockPrice[n][j], optionPrice1[n]);
                optionPrice1[n] = price[n][j];
            }
        }
        optionPrice.clear();
        int index = pow(2, column-1-j);
        for (int i = 0; i < optionPrice1.size(); i++) {
            if ((i+1) % index == 0){
                optionPrice.push_back(optionPrice1[i]);
            }
        }
        //show(optionPrice1);
        //cout << "next" << endl;
        optionPrice1.clear();
    }
    // cout << "Finish calculating option price." << endl;
    //cout << " Option value: " << endl;
    //printMatrix(price);
    //cout << " Option price at the starting point: " << price[0][0] << endl;
    return price[0][0];
}




#endif //Q1_Q1_H
