//
// Created by DELL on 2020/3/8.
//

#ifndef Q1_Q1_H
#define Q1_Q1_H

#include "chrono"
#include "std_lib_facilities.h"

// For Problem 1: Functions to generate random number distributions
vector<double> normalDist(double mean, double sd, int length);
vector<double> poissonDist(int k, int length);
vector<double> chisquaredDist(double k, int length);
vector<double> gammaDist(double mean, double sd, int length);
vector<double> bernoulliDist(double p, int length);
// For Problem 1: Functions to get statistics
double findMean(vector<double> inputVec);
double powerFun(double inputNum, int index);
double sampleSd(vector<double> inputVec);
double findMedium(vector<double> input);
// For Problem 1: Function to get mean, medium and standard deviation of a specific vector
vector<double> toulanfun(vector<double> input);





// Below is the details of my functions
vector<double> normalDist(double mean, double sd, int length){
    vector<double> normalVec;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    normal_distribution<double> dis(mean,sd);
    for (int i=0; i<length; ++i) normalVec.push_back(dis(gen));
    return normalVec;
}

vector<double> poissonDist(int k, int length){
    vector<double> poisVec;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    poisson_distribution<int> dis(k);
    for (int i=0; i<length; ++i) poisVec.push_back(dis(gen));
    return poisVec;
}

vector<double> chisquaredDist(double k, int length){
    vector<double> chisVec;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    chi_squared_distribution<double> dis(k);
    for (int i=0; i<length; ++i) chisVec.push_back(dis(gen));
    return chisVec;
}

vector<double> gammaDist(double mean, double sd, int length){
    vector<double> gammaVec;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    gamma_distribution<double> dis(mean,sd);
    for (int i=0; i<length; ++i) gammaVec.push_back(dis(gen));
    return gammaVec;
}

vector<double> bernoulliDist(double p, int length){
    vector<double> bVec;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    bernoulli_distribution  dis(p);
    for (int i=0; i<length; ++i) bVec.push_back(dis(gen));
    return bVec;
}

double findMean(vector<double> inputVec){
    double sum = 0.0;
    for (int i = 0; i < inputVec.size(); i++) {
        sum += inputVec[i];
    }
    float mean = (sum/inputVec.size());
    return mean*1.0;
}

double powerFun(double inputNum, int index){
    float result = 1.0;
    for (int i = 0; i < index; i++) {
        result *= inputNum;
    }
    return result*1.0;
}

double sampleSd(vector<double> inputVec){
    float sum2 = 0.0;
    float mean = findMean(inputVec);
    float sd;
    for (int i = 0; i < inputVec.size(); i++) {
        sum2 += powerFun(inputVec[i] - mean, 2);
    }
    sd = sqrt(sum2/(inputVec.size()-1));
    return sd*1.0;
}

double findMedium(vector<double> input){
    sort(input);
    double result;
    if (input.size()%2 == 0) result = (input[input.size()/2] + input[input.size()/2+1])/2;
    else result = input[input.size()/2+1];
    return result*1.0;
}

vector<double> toulanfun(vector<double> input){
    vector<double> result;
    result.push_back(findMean(input));
    result.push_back(findMedium(input));
    result.push_back(sampleSd(input));
    return result;
}



#endif //Q1_Q1_H
