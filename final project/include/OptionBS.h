//
// Created by DELL on 2020/5/6.
//

#ifndef PROGRAM_OPTIONBS_H
#define PROGRAM_OPTIONBS_H

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

class OptionBS{

public:
private:
    string Type;

    double St, K, r, price;
    int T;

public:
    OptionBS(string type, double spotPrice, double strikePrice,
             double interestRate, int timeToMature, double Price);
    double getBisectionVol();
    double getSecantVol();
};

OptionBS::OptionBS(string type, double spotPrice, double strikePrice,
                   double interestRate, int timeToMature, double Price){
    if (type == "Call") type.assign("call");
    else if (type == "Put") type.assign("put");
    if (type != "call" && type != "put"){
        cout << "Wrong input of type!" << endl;
        exit(1);
    }else{
        Type = type;
        St = spotPrice;
        K = strikePrice;
        r = interestRate;
        T = timeToMature;
        price = Price;
    }
}

double OptionBS::getBisectionVol(){
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

double OptionBS::getSecantVol(){
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
#endif //PROGRAM_OPTIONBS_H
