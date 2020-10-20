//
// Created by DELL on 2020/5/4.
//

#ifndef PROGRAM_PORTFOLIO_H
#define PROGRAM_PORTFOLIO_H

#include "PortfolioHelp.h"

double BZPC(vector<double> weight, SortedList<Stocks> *List);

class Portfolio{
public:
    SortedList<Stocks> Tickets;
    SortedList<double> Shares;
    SortedList<double> Weight;
    Portfolio()= default;

    Portfolio& operator=(const Portfolio& rhs){
        Tickets = rhs.Tickets;
        Shares = rhs.Shares;
        Weight = rhs.Weight;
    };

    double calculate();
    void calculateWithRandom(double startAeest);
};

double Portfolio::calculate() {
    int number = Tickets.getNumElems(); // Number of stocks in this portfolio
    LinkedNode<Stocks>* tempStock = Tickets.getStart(); // Starting pointer pf stocks
    LinkedNode<double>* tempShares = Shares.getStart(); // Starting pointer of Shares
    Vector<double> VectorWealth;
    double temp;
    int number2 = tempStock->getValue().AdjClose.size();
    for (int i = 0; i < number2 ; i++) {
        tempStock->getValue().AdjClose;
        tempShares->getValue();
        temp = 0;
        for (int j = 0; j < number; j++) {
            //cout << tempStock->getValue().AdjClose[i]<< " and " << tempShares->getValue() << endl;
            temp += tempStock->getValue().AdjClose[i] * tempShares->getValue();
            //cout << temp << endl;
            tempStock = tempStock->getNext();
            tempShares = tempShares->getNext();

        }
        VectorWealth.push_back(temp);
        tempStock = Tickets.getStart();
        tempShares = Shares.getStart();
    }
    cout << "At the beginning, value of this portfolio is: " << VectorWealth[0] << endl;
    cout << "At the End, value of this portfolio is: " << VectorWealth[VectorWealth.size()-1] << endl;
    cout << "Asset profit and loss: " << VectorWealth[VectorWealth.size()-1] - VectorWealth[0] << endl;
    cout << "With every 100 dollars, you earned: " <<
         (VectorWealth[VectorWealth.size()-1] - VectorWealth[0])/VectorWealth[0]*100 << endl;
    return VectorWealth[VectorWealth.size()];
}

void Portfolio::calculateWithRandom(double startAeest) {
    int number = Tickets.getNumElems();
    vector<double> meanRVec_all, miuVec, weightVec(number, 0), randomNum,
                   portfolioPrice, portfolioReturn, tempVec1, tempVec2,
                   resultReturnMean, resultPriceChange, resultReturnSD;
    double tempPrice, tempReturn, open;
    vector<vector<double>> markWeight;
    LinkedNode<Stocks>* tempStock;
    for (int time = 0; time < 1000; time++){
        tempStock = Tickets.getStart();
        randomNum = normalDist(0.0, 1.0, number);
        for (int i = 0; i < randomNum.size(); ++i) randomNum[i] = abs(randomNum[i]);
        for (int i = 0; i < randomNum.size(); ++i) weightVec[i] = randomNum[i]/findSum(randomNum);
        open = 0;
        for (int j = 0; j < number; j++) {
            open += (tempStock->getValue().Open[0] -
                    (tempStock->getValue().Close[0]-tempStock->getValue().Close[0]))* weightVec[0];
            if (j != number-1){
                tempStock = tempStock->getNext();
            }
        }
        portfolioPrice.clear();
        portfolioReturn.clear();
        for (int t = 0; t < tempStock->getValue().dailyReturn.size(); t++) {
            tempPrice = 0;
            tempReturn = 0;
            tempStock = Tickets.getStart();
            for (int j = 0; j < number; j++) {
                tempVec1.push_back(tempStock->getValue().AdjClose[t]);
                tempVec2.push_back(tempStock->getValue().dailyReturn[t]);
                if (j != number-1){
                    tempStock = tempStock->getNext();
                }
            }
            for (int n = 0; n < number; n++) {
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
        markWeight.push_back(weightVec);
    }
    vector<double> standardizedReturnSD = standardize(resultReturnSD);
    vector<double> standardizedPriceChange = standardize(resultPriceChange);
    double sharpRatio;
    vector<double> weight;
    double tempBest = (findMean(resultReturnMean)*252-0.0219)/BZPC(markWeight[0], &Tickets);
    int series = 0;
    for (int j = 0; j < standardizedPriceChange.size(); ++j) {
        weight = markWeight[j];
        sharpRatio = (findMean(resultReturnMean)*252-0.0219)/BZPC(weight, &Tickets);
        if(sharpRatio > tempBest){
            tempBest = sharpRatio;
            series = j;
        }
    }
    cout << "The optimal weight with highest sharp ratio "<< tempBest << " is:" << endl;
    LinkedNode<Stocks>* tempC;
    for (int k = 0; k < number; ++k) {
        if (k == 0){
            tempC = Tickets.getStart();
        }else{
            tempC = tempC->getNext();
        }
        cout << markWeight[series][k] << " of " << tempC->getValue().ticket << ", ";
    }
    cout << "\n";
    for (int k = 0; k < number; ++k) {
        if (k == 0){
            tempC = Tickets.getStart();
        }else{
            tempC = tempC->getNext();
        }
        cout << "Buy " << startAeest*markWeight[series][k]/tempC->getValue().Open[k] <<
                " shares of " << tempC->getValue().ticket << endl;
    }

    vector<double> portfolioValue;
    double temp;
    for (int k = 0; k < tempC->getValue().Date.size(); k++) {
        for (int m = 0; m < number; m++) {
            if (m == 0){
                tempC = Tickets.getStart();
            }else{
                tempC = tempC->getNext();
            }
            temp += markWeight[series][m]*tempC->getValue().AdjClose[k];
            portfolioValue.push_back(temp);
        }
    }


    ofstream fout;
    fout.open("../output/trackingValue.csv");
    for (int i = 0; i < tempC->getValue().Date.size(); i++) {
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< tempC->getValue().Date[i] << "\t" << ",";
        fout << setiosflags(ios::left)<<setw(8)<<setfill(' ')<< portfolioValue[i] << "\n";
    }
    fout.close();
}

double BZPC(vector<double> weight, SortedList<Stocks> *List){
    double result = 0;
    LinkedNode<Stocks>* tempA;
    LinkedNode<Stocks>* tempB;
    for (int i = 0; i < List->getNumElems(); ++i) {
        if (i == 0){
            tempA = List->getStart();
        }else{
            tempA = tempA->getNext();
        }
        for (int i = 0; i < List->getNumElems(); ++i) {
            if (i == 0){
                tempB = List->getStart();
            }else{
                tempB = tempB->getNext();
            }
            result += sampleSd(tempA->getValue().AdjClose)*weight[i]
                    * sampleSd(tempB->getValue().AdjClose)*weight[i]
                    * CorrelationCoefficient(tempA->getValue().AdjClose, tempB->getValue().AdjClose);
        }
    }
    return  sqrt(result);
}

#endif //PROGRAM_PORTFOLIO_H
