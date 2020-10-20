#include "std_lib_facilities.h"
#include "Q4Q5.h"
#include <fstream>
#include <iomanip>


int main() {

    // Problem 5:
    vector<string> types;
    vector<double> bid, ask, spot, strike, rate, givenVol, price, impliedVol, BisectionVol, SecantVol;
    vector<int> matureDay;
    double BVol, SVol;
    getValues( bid, ask, spot, strike, rate, matureDay, givenVol, price, types);
    for (int i = 0; i < price.size(); ++i) {
        EuropeanOption test1(types[i], spot[i], strike[i], rate[i], givenVol[i], matureDay[i]);
        BVol = test1.getBisectionVol(price[i]);
        SVol = test1.getSecantVol(price[i]);
        BisectionVol.push_back(BVol);
        SecantVol.push_back(SVol);
    }

    // Problem 5: output to a file
    vector<string> colNames = {"Type", "Bid", "Ask", "Spot", "Strike", "Rate", "DaysToMaturity",
                               "ImpliedVolatility", "BisectionVol", "SecantVol"};
    ofstream fout;
    fout.open("../../output/Q5Output.txt");
    for (int j = 0; j < 6; j++)  fout << setiosflags(ios::left)<<setw(8)<<setfill(' ') << colNames[j] << "\t";
    for (int j = 6; j < colNames.size()-1; j++) fout << setiosflags(ios::left)<<setw(20)<<setfill(' ') << colNames[j] << "\t";
    fout << setiosflags(ios::left)<<setw(20)<<setfill(' ')<< colNames[colNames.size()-1] << "\n";
    for (int i = 0; i < 12; i++) {
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< types[i] << "\t";
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< bid[i] << "\t";
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< ask[i] << "\t";
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< spot[i] << "\t";
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< strike[i] << "\t";
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< rate[i] << "\t";
        fout << setiosflags(ios::left)<<setw(20)<<setfill(' ')<< matureDay[i] << "\t";
        fout << setiosflags(ios::left)<<setw(20)<<setfill(' ')<< givenVol[i] << "\t";
        fout << setiosflags(ios::left)<<setw(20)<<setfill(' ')<< BisectionVol[i] << "\t";
        fout << setiosflags(ios::left)<<setw(20)<<setfill(' ')<< SecantVol[i] << "\n";
    }
    fout.close();

    return 0;
}




