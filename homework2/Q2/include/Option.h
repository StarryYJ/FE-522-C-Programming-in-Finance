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

    virtual double getPrice(){};
    double getDelta();
    double getRho();
    double getVega();
    double getTheta();
    void printMatrix(vector<vector<double>>& A); // can be used to print out the process, same the next
    void show(vector<double>& A);

protected:
    string type;
    double strike, spot, rate, volatility, timeToMature, u, d, p, q, N;
    vector<string> direction;
    vector<vector<double>> price, stockPrice;
};



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
//        u = exp(volatility*pow(timeToMature/N, 0.5));
//        d = exp(-volatility*pow(timeToMature/N, 0.5));
//        p = (exp(rate*timeToMature/N)-d)/(u-d);
//        q = 1-p;
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
    //cout << "Therefore, the price of this option is " << price[0][0] << endl;
}

double getMax(double a, double b){
    if (a > b) return a;
    else return b;
}

double Option::getDelta(){
    double sjx = 0.1, p1, p2;
    p1 = getPrice();
    //cout << p1 << endl;
    spot += sjx;
    p2 = getPrice();
    //cout << p2 << endl;
    spot -= sjx;
    return (p2-p1)/sjx;
}

double Option::getRho(){
    double sjx = 0.01, p1, p2;
    p1 = getPrice();
    rate += sjx;
    p2 = getPrice();
    rate -= sjx;
    return (p2-p1)/sjx;
}
double Option::getVega(){
    double sjx = 0.01, p1, p2;
    p1 = getPrice();
    volatility += sjx;
    p2 = getPrice();
    volatility -= sjx;
    return (p2-p1)/sjx;
}

double Option::getTheta(){
    double sjx = 0.01, p1, p2;
    p1 = getPrice();
    //cout << p1 << "wew" << endl;
    timeToMature = timeToMature + sjx;
    p2 = getPrice();
    //cout << p2 << "efs" << endl;
    timeToMature -= sjx;
    return (p2-p1)/sjx;
}

void Option::show(vector<double>& A){
    cout << "start" << "\t";
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << "\t";
    }
    cout << "end" << endl;
}

#endif //Q2_Q2_H
