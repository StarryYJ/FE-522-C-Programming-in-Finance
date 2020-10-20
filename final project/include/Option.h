//
// Created by DELL on 2020/3/8.
//

#ifndef Q2_Q2_H
#define Q2_Q2_H

#include "std_lib_facilities.h"

double getMax(double a, double b);

class Option{

public:
    Option(string Type, double Strike, double spot, double Rate,
           double Volatility, double TimeToMature, int n);
    Option(){};

    double getAmericanPrice(bool showPrice);
    double getEuropeanPrice(bool showPrice);
    void getPrice(bool showPrice);
    void printMatrix(vector<vector<double>>& A); // can be used to print out the process, same the next
    void show(vector<double>& A);


protected:
    string type;
    double strike, spot, rate, volatility, timeToMature, u, d, p, q, N;
    vector<string> direction;
    vector<vector<double>> price, stockPrice;
};


#include "Option.h"
Option::Option(string Type, double Strike, double Spot, double Rate,
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

void Option::printMatrix(vector<vector<double>>& A){
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
}

double getMax(double a, double b){
    if (a > b) return a;
    else return b;
}

void Option::show(vector<double>& A){
    cout << "start" << "\t";
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << "\t";
    }
    cout << "end" << endl;
}


double Option::getAmericanPrice(bool showPrice) {
    double EuropeanaPrice = getEuropeanPrice(false);
    int column = N+1;
    int row = pow(2, N);
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
    double intermediate;
    for (int j = column-2; j > -1; j--) {

        for (int k = 0; k < optionPrice.size(); ++k) {
            if (k % 2 != 0){
                intermediate = (optionPrice[k-1]*p+optionPrice[k]*q)*exp(-rate*timeToMature/N);//here
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
    if (showPrice == true){
        cout << "The stock price tree is:" << endl;
        printMatrix(stockPrice);
        cout << "Value tree of American Option is:" << endl;
        printMatrix(price);
        getEuropeanPrice(true);
    }else{
        cout << "Price of this American Option should be: " << price[0][0] << endl;
        cout << "Price of this European Option should be: " << EuropeanaPrice << endl;
    }
    return price[0][0];
}


double Option::getEuropeanPrice(bool showPrice) {
    direction.clear();
    price.clear();
    stockPrice.clear();
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
    }
    double intermediate;
    for (int j = column-2; j > -1; j--) {

        for (int k = 0; k < optionPrice.size(); ++k) {
            if (k % 2 != 0){
                intermediate = (optionPrice[k-1]*p+optionPrice[k]*q)*exp(-rate*timeToMature/N);//here
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
            price[n][j] = optionPrice1[n];
        }
        optionPrice1.clear();
    }
    if (showPrice == true){
        cout << "Value tree of European Option is: " << endl;
        printMatrix(price);
    }
    return price[0][0];
}

void Option::getPrice(bool showPrice) {
    getAmericanPrice(showPrice);
    getEuropeanPrice(false);
}



#endif //Q2_Q2_H
