//
// Created by DELL on 2020/3/8.
//

#ifndef Q1_Q1_H
#define Q1_Q1_H

#include "std_lib_facilities.h"

double getMax(double a, double b);

class AmericanOption{
public:
    AmericanOption(string Type, double Strike, double Spot, double Rate,
                   double Volatility, double TimeToMature, int n);
    double getPrice();
private:
    string type;
    vector<string> direction;
    double strike, spot, rate, volatility, timeToMature, vEnd, N, p, q, u, d;
    vector<vector<double>> price, stockPrice;
    void printMatrix(vector<vector<double>>& A);
};


AmericanOption::AmericanOption(string Type, double Strike, double Spot, double Rate,
                               double Volatility, double TimeToMature, int n){
    if (Type == "Call") Type.assign("call");
    else if (Type == "Put") Type.assign("put");
    if (Type != "call" && Type != "put"){
        cout << "Wrong input of type!" << endl;
        exit(1);
    }else if (Volatility >= 1 | Volatility < 0){
        cout << "Volatility out of range!" << endl;
        exit(2);
    }else if(TimeToMature < 0){
        cout << "Time to mature cannot be negative!" << endl;
        exit(3);
    }else{
        type = Type;
        strike = Strike;
        spot = Spot;
        rate = Rate;
        volatility = Volatility;
        timeToMature = TimeToMature;
        N = n;
        u = exp(volatility*pow(timeToMature/N, 0.5));
        d = exp(-volatility*pow(timeToMature/N, 0.5));
        p = (exp(rate*timeToMature/N)-d)/(u-d);
        q = 1-p;
    }
}


double AmericanOption::getPrice() {

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
                intermediate = (optionPrice[k-1]*p+optionPrice[k]*q)*exp(-rate*timeToMature/N);
                optionPrice1.push_back(intermediate);
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
        optionPrice1.clear();
    }
    // cout << "Finish calculating option price." << endl;
//    cout << " Option value: " << endl;
//    printMatrix(price);
//    cout << " Option price at the starting point: " << price[0][0] << endl;
    return price[0][0];
}

void AmericanOption::printMatrix(vector<vector<double>>& A){
    int row = A.size();
    int column = A[0].size();
    for (int i = 0; i < row; ++i) {
        cout << right << setw(10) << direction[i] ;
        for (int j = 0; j < column; ++j) {
            cout << right << setw(10) << A[i][j] ;
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "Therefore, the price of this option is " << price[0][0] << endl;
}

double getMax(double a, double b){
    if (a > b) return a;
    else return b;
}

#endif //Q1_Q1_H
