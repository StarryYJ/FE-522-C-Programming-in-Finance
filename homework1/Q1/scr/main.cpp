#include "Q1.h"
#include <fstream>
#include <iomanip>


int main() {
    // Problem 1
    // Generate 5 random number distributions
    vector<double> normal = normalDist(10, 5, 10000);
    vector<double> poisson = poissonDist(5, 10000);
    vector<double> chi_squared = chisquaredDist(5, 10000);
    vector<double> gamma = gammaDist(10, 5, 10000);
    vector<double> bernoulli = bernoulliDist(0.5, 10000);
    // Get the statistics of the distributions
    vector<vector<double>> Q1result = {{toulanfun(normal)}, toulanfun(poisson), toulanfun(chi_squared),
                                       toulanfun(gamma), toulanfun(bernoulli)};
    vector<string> rowNames = {"Normal", "Poisson", "ChiSquared", "Gamma", "Bernoulli"};
    ofstream fout;
    fout.open("../../output/Q1Output.txt");
    fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< "Distribution" << "\t\t";
    fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< "Mean"  << "\t\t";
    fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< "Medium" << "\t\t";
    fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< "Sample sd"  << "\n";
    for (int i = 0; i < 5; i++) {
        fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< rowNames[i] << "\t\t";
        fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< Q1result[i][0] << "\t\t";
        fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< Q1result[i][1] << "\t\t";
        fout << setiosflags(ios::left)<<setw(15)<<setfill(' ')<< Q1result[i][2] << "\n";
    }
    fout.close();




}
