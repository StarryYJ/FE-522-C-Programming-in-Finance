#include "std_lib_facilities.h"
#include "Q6.h"

int main() {
    stock stock1("apple"),
          stock2("BOA"),
          stock3("facebook"),
          stock4("macdonald"),
          stock5("nintendo");

    vector<double> meanRVec_all, miuVec, weightVec = {0,0,0,0,0}, randomNum,
                   portfolioPrice, portfolioReturn, tempVec1, tempVec2;
    double tempPrice, tempReturn, open;

    vector<double> resultReturnMean, resultPriceChange, resultReturnSD;
    vector<vector<double>> markWeight;

    for (int time = 0; time < 1000; time++){
        randomNum = normalDist(0.0, 1.0, 5);
        for (int i = 0; i < randomNum.size(); ++i) randomNum[i] = abs(randomNum[i]);
        for (int i = 0; i < randomNum.size(); ++i) weightVec[i] = randomNum[i]/findSum(randomNum);
        open = (stock1.Open[0]-(stock1.Close[0]-stock1.AdjClose[0])) * weightVec[0]
                + (stock2.Open[0]-(stock2.Close[0]-stock2.AdjClose[0]))* weightVec[1]
                + (stock3.Open[0]-(stock3.Close[0]-stock3.AdjClose[0]))* weightVec[2]
                + (stock4.Open[0]-(stock4.Close[0]-stock4.AdjClose[0]))* weightVec[3]
                + (stock5.Open[0]-(stock5.Close[0]-stock5.AdjClose[0]))* weightVec[4];
        portfolioPrice.clear();
        portfolioReturn.clear();
        for (int t = 0; t < stock1.dailyReturn.size(); t++) {
            tempPrice = 0;
            tempReturn = 0;
            tempVec1 = {stock1.AdjClose[t], stock2.AdjClose[t], stock3.AdjClose[t],
                        stock4.AdjClose[t], stock5.AdjClose[t]};
            tempVec2 = {stock1.dailyReturn[t], stock2.dailyReturn[t], stock3.dailyReturn[t],
                        stock4.dailyReturn[t], stock5.dailyReturn[t]};
            for (int n = 0; n < 5; n++) {
                tempPrice += tempVec1[n]*weightVec[n];
                tempReturn += tempVec2[n]*weightVec[n];
            }
            portfolioPrice.push_back(tempPrice);
            portfolioReturn.push_back(tempReturn);
        }
        // What I care is the fluctuation of daily returns, and the price change of portfolio
        resultReturnSD.push_back(sampleSd(portfolioReturn));
        resultReturnMean.push_back(findMean(portfolioReturn));
        resultPriceChange.push_back(portfolioPrice[portfolioPrice.size()-1]-open);
        markWeight.push_back({weightVec[0], weightVec[1], weightVec[2],
                             weightVec[3], weightVec[4]});
    }

    vector<double> standardizedReturnSD = standardize(resultReturnSD);
    vector<double> standardizedPriceChange = standardize(resultPriceChange);

    double sharpRatio;
    vector<double> weight;


    double tempBest = (findMean(resultReturnMean)*252-0.0219)/BZPC(markWeight[0], stock1.dailyReturn,
                       stock2.dailyReturn, stock3.dailyReturn, stock4.dailyReturn, stock5.dailyReturn);

    int series = 0;
    for (int j = 0; j < standardizedPriceChange.size(); ++j) {
        weight = markWeight[j];
        sharpRatio = (findMean(resultReturnMean)*252-0.0219)/BZPC(weight, stock1.dailyReturn,
                      stock2.dailyReturn, stock3.dailyReturn, stock4.dailyReturn, stock5.dailyReturn);
        if(sharpRatio > tempBest){
            tempBest = sharpRatio;
            series = j;
        }
    }

    cout << "The optimal weight with highest sharp ratio "<< tempBest << " is:" << endl;
    cout << markWeight[series][0] << " of stock1" << endl;
    cout << markWeight[series][1] << " of stock2" << endl;
    cout << markWeight[series][2] << " of stock3" << endl;
    cout << markWeight[series][3] << " of stock4" << endl;
    cout << markWeight[series][4] << " of stock5" << endl;

    cout << "Buy " << 1000000*markWeight[series][0]/stock1.Open[0] << " shares of stock1;" << endl;
    cout << 1000000*markWeight[series][1]/stock2.Open[0] << " shares of stock2;" << endl;
    cout << 1000000*markWeight[series][2]/stock3.Open[0] << " shares of stock3;" << endl;
    cout << 1000000*markWeight[series][3]/stock4.Open[0] << " shares of stock4;" << endl;
    cout << 1000000*markWeight[series][4]/stock5.Open[0] << " shares of stock5." << endl;

    vector<double> portfolioValue;
    double temp;
    for (int k = 0; k < stock1.AdjClose.size(); k++) {
        temp = markWeight[series][0]*stock1.AdjClose[k] + markWeight[series][1]*stock2.AdjClose[k]
               + markWeight[series][2]*stock3.AdjClose[k]+ markWeight[series][3]*stock4.AdjClose[k]
               + markWeight[series][4]*stock5.AdjClose[k];
        portfolioValue.push_back(temp);
    }

    ofstream fout;
    fout.open("../../output/Q6Output.csv");
    for (int i = 0; i < portfolioValue.size(); i++) {
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< stock1.Date[i] << "\t" << ",";
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< portfolioValue[i] << "\n";
    }
    fout.close();


    return 0;
}
