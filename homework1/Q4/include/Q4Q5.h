//
// Created by DELL on 2020/3/6.
//

#ifndef HOMEWORK1_Q4_Q6_Q4_Q6_H
#define HOMEWORK1_Q4_Q6_Q4_Q6_H

#include <algorithm>

// will be used in problem 5, in this way my EuropeanOption class could be clearer.
// This dInBS class stands for d(d1 and d2) in BS model.
// Because d1 and d2 change when volatility changes, I made this class to update d1 and d2 when do Iteration to vol.
class dInBS{
public:
    double St, K, r, vol, T;
    dInBS(double St1, double K1, double r1, double vol1, int T1){
        St = St1;
        K = K1;
        r = r1;
        vol = vol1;
        T = T1/365.0;
    };
    double d1_1, d2_1, callP, putP;
    void calculate(){
        d1_1 = (log(St/K)+(r+vol*vol/2)*T)/(vol*sqrt(T));
        d2_1 = d1_1-vol*sqrt(T);
        callP = (0.5 * erfc(-d1_1 * M_SQRT1_2))*St-(0.5 * erfc(-d2_1 * M_SQRT1_2))*K*exp(-r*T);
        putP = (0.5 * erfc(d2_1 * M_SQRT1_2))*K*exp(-r*T)-(0.5 * erfc(d1_1 * M_SQRT1_2))*St;
    }

};


// For problem 4:
class EuropeanOption{
private:
    string Type;
    double call();
    double put();
    double St, K, r, vol, d1, d2, T;

public:
    EuropeanOption(string type, double spotPrice, double strikePrice,
                   double interestRate, double volatility, double timeToMature);
    double getPrice();
    double getBisectionVol(double price);
    double getSecantVol(double price);
};
// For problem 5:
void getValues(
        vector<double> &bid, vector<double> &ask, vector<double> &spot, vector<double> &strike,
        vector<double> &rate, vector<int> &matureDay, vector<double> &givenVol,
        vector<double> &price, vector<string> &types
);


EuropeanOption::EuropeanOption(string type, double spotPrice, double strikePrice,
                               double interestRate, double volatility, double timeToMature){
    if (type == "Call") type.assign("call");
    else if (type == "Put") type.assign("put");
    if (type != "call" && type != "put"){
        cout << "Wrong input of type!" << endl;
        exit(1);
    }else if (volatility >= 1 | volatility < 0){
        cout << "Volatility out of range!" << endl;
        exit(2);
    }else if(timeToMature < 0){
        cout << "Time to mature cannot be negative!" << endl;
        exit(3);
    }else{
        Type = type;
        St = spotPrice;
        K = strikePrice;
        r = interestRate;
        vol = volatility;
        T = timeToMature;
        d1 = (log(St/K)+(r+vol*vol/2)*T)/(vol*sqrt(T));
        d2 = d1-vol*sqrt(T);
    }
}

double EuropeanOption::getPrice() {
    if(Type == "call") return call();
    else return put();
}
double EuropeanOption::call() {
    return (0.5 * erfc(-d1 * M_SQRT1_2))*St-(0.5 * erfc(-d2 * M_SQRT1_2))*K*exp(-r*T);
}
double EuropeanOption::put() {
    return (0.5 * erfc(d2 * M_SQRT1_2))*K*exp(-r*T)-(0.5 * erfc(d1 * M_SQRT1_2))*St;
}

// Detailed function for problem 5:

void getValues(
        vector<double> &bid, vector<double> &ask, vector<double> &spot, vector<double> &strike,
        vector<double> &rate, vector<int> &matureDay, vector<double> &givenVol,
        vector<double> &price, vector<string> &types
){
    string filename = "../../input/Options.txt";
    ifstream infile;
    infile.open(filename);
    //if (infile.good()){
    //cout << "Open successfully" << endl;
    //}
    while (!infile.eof()){
        string s;
        infile >> s;
        if (infile.eof()) break;
        types.push_back(s);
        double d;
        int i;
        infile >> d;
        bid.push_back(d);
        infile >> d;
        ask.push_back(d);
        infile >> d;
        spot.push_back(d);
        infile >> d;
        strike.push_back(d);
        infile >> d;
        rate.push_back(d);
        infile >> i;
        matureDay.push_back(i);
        infile >> d;
        givenVol.push_back(d);
    }
    for (int i = 0; i < bid.size(); ++i)  price.push_back((bid[i]+ask[i])/2);
}

double EuropeanOption::getBisectionVol(double price){
    double small = 0.0, big = 1;
    dInBS c(St, K, r, (small + big)/2, T);
    c.calculate();
    if (Type == "call"){
        while (abs(c.callP-price) > 0.001 & abs(small-big) > 0.001){
            c.vol = (small + big)/2;
            c.calculate();
            if (c.callP  - price < -0.001) small = (small + big)/2;
            else if (c.callP - price > 0.001)  big = (small + big)/2;
        }
    } else if (Type == "put"){
        while (abs(c.putP-price) > 0.001 & abs(small-big) > 0.001){
            c.vol = (small + big)/2;
            c.calculate();
            if (c.putP  - price < -0.001) small = (small + big)/2;
            else if (c.putP - price > 0.001) big = (small + big)/2;
        }
    }
    return c.vol;
};

double EuropeanOption::getSecantVol(double price){
    dInBS a(St, K, r, 0.0, T);
    dInBS b(St, K, r, 0.5, T);
    vector<double> volVec = {0.0, 0.5};
    double tempV;
    int n = 2;
    if (Type == "call"){
        while (abs(b.callP-price) > 0.001){
            a.vol = volVec[n-2];
            b.vol = volVec[n-1];
            a.calculate();
            b.calculate();
            tempV = volVec[n-1] -(b.callP-price)*(b.vol-a.vol)/(b.callP-a.callP);
            volVec.push_back(tempV);
            n++;
        }
        return b.vol;
    } else if (Type == "put"){
        while (abs(b.putP-price) > 0.001){
            a.vol = volVec[n-2];
            b.vol = volVec[n-1];
            a.calculate();
            b.calculate();
            tempV = volVec[n-1] -(b.putP-price)*(b.vol-a.vol)/(b.putP-a.putP);
            volVec.push_back(tempV);
            n++;
        }
        return b.vol;
    }
}




#endif //HOMEWORK1_Q4_Q6_Q4_Q6_H
