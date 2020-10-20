//
// Created by DELL on 2020/5/4.
//

#ifndef PROGRAM_STOCK_H
#define PROGRAM_STOCK_H

class Stock{
private:
    double S; // Initial stock price S0
    double T; // Time to M
    double V; // Historical volitility
    double r; // risk free rate
    double n; // number of steps

public:
    Stock(){};
    Stock(double InitialPrice, double SimulatePeriod, double RiskFreeRate, double Volatility, int StepsYouWant){
        S = InitialPrice;
        T = SimulatePeriod;
        r = RiskFreeRate;
        n = StepsYouWant;
        V = Volatility;
    }
    Stock(string ticket);
    double findMean(Vector<double> a);
    double simulate();
    Vector<double> randomNormal(int M, double Std, double seed);
};




double Stock::simulate() {
    Vector<double> res_Vec;
    Vector<double> St;
    Vector<double> dwt;
    St.push_back(S);
    for (int i = 0; i <= n; ++i) {
        Vector<double> epsilon = randomNormal(0,1,i);
        dwt.push_back(epsilon[i] * sqrt(T/n));
    }
    for (int j = 0; j <= 1000; ++j) {
        for (int k = 0; k <= n; ++k) {
            St.push_back(St[k] + r * St[k] * T/n + V * St[k] * dwt[k]);
        }
        res_Vec.push_back(St[n]);
    }
    cout << findMean(res_Vec);
    return 0;
}


double Stock::findMean(Vector<double> a) {
    double sum = 0.0;
    int i;
    for (i = 0; i < a.size() ; i++){
        sum += a[i];
    }
    double mean = sum / a.size();
    return mean;
}

Vector<double> Stock::randomNormal(int M, double Std, double seed){
    default_random_engine generator;
    generator.seed(seed);
    normal_distribution<double> distribution(M,Std);
    Vector <double> Normal;
    for (int i=0; i<= 1000; ++i) {
        Normal.push_back(distribution(generator));
    }
    return Normal;
}

#endif //PROGRAM_STOCK_H
