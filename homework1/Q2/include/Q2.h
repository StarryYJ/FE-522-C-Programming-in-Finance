//
// Created by DELL on 2020/3/8.
//

#ifndef Q2_Q2_H
#define Q2_Q2_H

// For Problem 2-1: Function to test whether 2 numbers have different symbols
bool differentSymbolOrNot(double number1, double number2);
// For Problem 2-1: Function of Bisection method, input should be a vector of the indexes for function f(x)=0
//                  And initial guess which is an interval with Upper Bound b and Lower Bound a
double BisectionMethod(vector<double> index, double a, double b);
// For Problem 2-2:
double insideFun(double x, vector<double> indexes);//To compute f(x) for my polynomial function
double SecantMethod(vector<double> index, double xa, double xb);



bool differentSymbolOrNot(double number1, double number2){
    bool result = false;
    if (number1 > 0 && number2 < 0) result = true;
    else if (number1 < 0 && number2 > 0) result = true;
    return result;
}

double BisectionMethod(vector<double> index, double a, double b){
    if (a==b){
        cout << "Please enter different 'a' and 'b'.";
        exit(1);
    }
    float c,fa=0,fb=0,fc=0;
    for (int i = 0; i < index.size(); i++){
        fa+=index[i]*pow(a,i);
        fb+=index[i]*pow(b,i);
    }
    if (fa==0) return a;
    else if (fb==0) return b;
    if (differentSymbolOrNot(fa, fb)==false){
        cout << "Please make f(a) and f(b) one positive and one negative.";
        exit(2);
    }
    while (true){
        c = (a+b)/2;
        fa=fb=fc=0;
        for (int i = 0; i < index.size(); i++){
            fa+=index[i]*pow(a,i);
            fb+=index[i]*pow(b,i);
            fc+=index[i]*pow(c,i);
        }
        if (abs(fc) <= 0.01 | abs(a-c)<0.01 | abs(b-c)<0.01) break;
        else if (differentSymbolOrNot(fb,fc) == false) b = c;
        else if (differentSymbolOrNot(fa,fc) == false) a = c;
    }
    return c;
}

double insideFun(double x, vector<double> indexes){
    double fx=0.0;
    for (int i = 0; i < indexes.size(); i++) fx += indexes[i]*pow(x,i);
    return fx;
}


double SecantMethod(vector<double> index, double xa, double xb){
    vector<double> xn = {xa, xb};
    double e = 0.01, tempx;
    int n = 2;
    while (abs(insideFun(xn[n-1], index)) >= e){
        tempx = xn[n-1] - insideFun(xn[n-1], index)*(xn[n-1] - xn[n-2])/(insideFun(xn[n-1], index)-insideFun(xn[n-2], index));
        xn.push_back(tempx);
        n++;
    }
    return xn[xn.size()-1];
}












#endif //Q2_Q2_H
