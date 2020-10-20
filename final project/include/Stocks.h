//
// Created by DELL on 2020/5/4.
//

#ifndef PROGRAM_STOCKS_H
#define PROGRAM_STOCKS_H

#include "Stock.h"

class Stocks{
public:
    Stocks(){};
    Stocks(string ticketName);

    string ticket;
    vector<string> Date;
    vector<double> Open, High, Low, Close, AdjClose, Volume, dailyReturn;

    //Vector<double> FindDrt();
   // double findMean(Vector<double> a);
    //double Findsd();
    double HVol();
    double simulate(double S1, double T1, double V1, double r1, double n1, Vector<double> stock);
    Vector<double> randomNormal(int M, double Std);
};


Stocks::Stocks(string ticketName){
    ticket = ticketName;
    string filename = "../input/" + ticket + ".csv";
    ifstream infile;
    infile.open(filename);
    //if (infile.good()){
    //cout << "Open successfully" << endl;
    //}
    while (!infile.eof()){
        string s;
        infile >> s;
        if (infile.eof()) break;
        Date.push_back(s);
        double d;
        infile >> d;
        Open.push_back(d);
        infile >> d;
        High.push_back(d);
        infile >> d;
        Low.push_back(d);
        infile >> d;
        Close.push_back(d);
        infile >> d;
        Volume.push_back(d);
        infile >> d;
        AdjClose.push_back(d);
    }
    for (int i = 1; i < AdjClose.size(); i++) {
        dailyReturn.push_back(log(AdjClose[i]/AdjClose[i-1]));
    }
}

double findMean(Vector<double> a) {
    double sum = 0.0;
    int i;
    for (i = 0; i < a.size() ; i++){
        sum += a[i];
    }
    double mean = sum / a.size();
    return mean;
}

double sampleSd(vector<double> inputVec){
    float sum2 = 0.0;
    float mean = findMean(inputVec);
    float sd;
    for (int i = 0; i < inputVec.size(); i++) {
        sum2 += pow(inputVec[i] - mean, 2);
    }
    sd = sqrt(sum2/(inputVec.size()-1));
    return sd;
}

double Stocks::HVol() {
    double std = sampleSd(dailyReturn);
    return std * sqrt(252);
}

Vector<double> Stocks::randomNormal(int M, double Std){
    default_random_engine generator;
    normal_distribution<double> distribution(M,Std);
    Vector <double> Normal;
    for (int i=0; i<= 1000; ++i) {
        Normal.push_back(distribution(generator));
    }
    return Normal;
}


double Stocks::simulate(double S1, double T1, double V1, double r1, double n1, Vector<double> stock) {
    double S0 = S1;
    double V = V1;
    double T = T1/252;
    double n = n1;
    double r = r1;
    double dt = T/n;
    double Vol;
    double sd;
    Vector<double> Daily_re;
    Vol = HVol();
    Vector<double> epsilon = randomNormal(0,1);
    Vector<double> res_Vec;
    Vector<double> St;
    Vector<double> dwt;
    St.push_back(S0);
    for (int i = 0; i <= 1000; ++i) {
        dwt.push_back(epsilon[i] * sqrt(dt));
    }
    for (int j = 0; j < 1000; ++j) {
        for (int k = 0; k <= n; ++k) {
            St.push_back(St[k] + r * St[k] * dt + Vol * St[k] * dwt[k]);
        }
        res_Vec.push_back(St[n]);
    }
    cout << findMean(res_Vec) << endl;
    return 0;
}


#endif //PROGRAM_STOCKS_H
