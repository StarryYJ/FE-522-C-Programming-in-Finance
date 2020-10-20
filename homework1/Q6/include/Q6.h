//
// Created by DELL on 2020/3/8.
//

#ifndef Q6_Q6_H
#define Q6_Q6_H

#include <chrono>

class stock{
public:
    stock(string ticketName);

    string ticket;
    vector<string> Date;
    vector<double> Open, High, Low, Close, AdjClose, Volume, dailyReturn;
};

vector<double> normalDist(double mean, double sd, int length);
double findSum(vector<double> inputVec);
double findMean(vector<double> inputVec);
vector<double> standardize(vector<double> input);
double cov(vector<double> A, vector<double> B);
double CorrelationCoefficient(vector<double> A, vector<double> B);
double BZPC(vector<double> weight, vector<double> stock1, vector<double> stock2, vector<double> stock3,
            vector<double> stock4, vector<double> stock5);

stock::stock(string ticketName){
    ticket = ticketName;
    string filename = "../../input/" + ticket + ".csv";
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

vector<double> normalDist(double mean, double sd, int length){
    // construct a random generator engine from a time-based seed

    vector<double> normalVec;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    normal_distribution<double> dis(mean,sd);

    for (int i=0; i<length; ++i){
        normalVec.push_back(dis(gen));
    }

    return normalVec;
}

double findSum(vector<double> inputVec){
    double sum = 0.0;
    for (int i = 0; i < inputVec.size(); i++) {
        sum += inputVec[i];
    }
    return sum;
}

double findMean(vector<double> inputVec){
    double sum = 0.0;
    for (int i = 0; i < inputVec.size(); i++) {
        sum += inputVec[i];
    }
    float mean = (sum/inputVec.size());
    return mean;
}

double powerFun(double inputNum, int index){
    float result = 1.0;
    for (int i = 0; i < index; i++) {
        result *= inputNum;
    }
    return result;
}

double sampleSd(vector<double> inputVec){
    float sum2 = 0.0;
    float mean = findMean(inputVec);
    float sd;
    for (int i = 0; i < inputVec.size(); i++) {
        sum2 += powerFun(inputVec[i] - mean, 2);
    }
    sd = sqrt(sum2/(inputVec.size()-1));
    return sd;
}

double findMax(vector<double> input){
    double value = input[0];
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] > value) value = input[i];
    }
    return value;
}

double findMin(vector<double> input){
    double value = input[0];
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] < value) value = input[i];
    }
    return value;
}

vector<double> standardize(vector<double> input){
    double max = findMax(input);
    double min = findMin(input);
    double range = max-min;
    vector<double> out;
    for (int i = 0; i < input.size(); ++i)  {
        out.push_back((input[i]-min)/range);
    }
    return out;
}

double cov(vector<double> A1, vector<double> B1){
    vector<double> E1;
    for (int i = 0; i < A1.size(); ++i) {
        E1.push_back(A1[i]*B1[i]);
    }
    return findMean(E1)-findMean(A1)*findMean(B1);
}


double CorrelationCoefficient(vector<double> A2, vector<double> B2){
    return cov(A2,B2)/(sampleSd(A2)*sampleSd(B2));
}

double BZPC(vector<double> weight, vector<double> stock1, vector<double> stock2, vector<double> stock3,
            vector<double> stock4, vector<double> stock5){
    vector<double> SDs;
    double result, A, B, C, D, E;
    A = sampleSd(stock1)*weight[0];
    B = sampleSd(stock2)*weight[1];
    C = sampleSd(stock3)*weight[2];
    D = sampleSd(stock4)*weight[3];
    E = sampleSd(stock5)*weight[4];

    result = A*A + B*B + C*C + D*D + E*E + 2*CorrelationCoefficient(stock1,stock2)
            + 2*weight[0]*weight[1]*sampleSd(stock1)*sampleSd(stock2)*CorrelationCoefficient(stock1, stock2)
            + 2*weight[0]*weight[2]*sampleSd(stock1)*sampleSd(stock3)*CorrelationCoefficient(stock1, stock3)
            + 2*weight[0]*weight[3]*sampleSd(stock1)*sampleSd(stock4)*CorrelationCoefficient(stock1, stock4)
            + 2*weight[0]*weight[4]*sampleSd(stock1)*sampleSd(stock5)*CorrelationCoefficient(stock1, stock5)
            + 2*weight[1]*weight[2]*sampleSd(stock2)*sampleSd(stock3)*CorrelationCoefficient(stock2, stock3)
            + 2*weight[1]*weight[3]*sampleSd(stock2)*sampleSd(stock4)*CorrelationCoefficient(stock2, stock4)
            + 2*weight[1]*weight[3]*sampleSd(stock2)*sampleSd(stock5)*CorrelationCoefficient(stock2, stock5)
            + 2*weight[2]*weight[3]*sampleSd(stock3)*sampleSd(stock4)*CorrelationCoefficient(stock3, stock4)
            + 2*weight[2]*weight[4]*sampleSd(stock3)*sampleSd(stock5)*CorrelationCoefficient(stock3, stock5)
            + 2*weight[3]*weight[4]*sampleSd(stock4)*sampleSd(stock5)*CorrelationCoefficient(stock4, stock5);
    return  sqrt(result);
}
#endif //Q6_Q6_H
