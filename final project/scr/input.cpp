//
// Created by DELL on 2020/5/10.
//


#include "Stock.h"
#include "Stocks.h"
#include "Option.h"
#include "Portfolio.h"
#include "OptionBS.h"
#include <ctype.h>

Stock StockIn();
Option OptionIn();
Portfolio PortfolioIn();
string toUpper(string in);

auto DataIn(){
    string choice2, choice;
    while (choice2 != "stock" & choice2 != "option" & choice2 != "portfolio" & choice2 != "exit" ){
        cout << "Do you want to analyze stock, option or portfolio? " ;
        cin >> choice2;
        choice2 = toUpper(choice2);
        if (choice2 == "STOCK"){
            Stock MyStock;
            MyStock = StockIn();
            cout << "According to Monte Carlo simulation, the stock price is likely to be: "
                 << MyStock.simulate() << endl;
        }else if (choice2 == "OPTION"){
            Option MyOption;
            MyOption = OptionIn();
            cout << "Do you want to see the binomial tree? " ;
            cin >> choice;
            choice = toUpper(choice);
            if (choice == "YES"){
                MyOption.getPrice(true);
            }else{
                MyOption.getPrice(false);
            }
        }else if (choice2 == "PORTFOLIO"){
            //Portfolio MyPortfolio;
            //MyPortfolio = PortfolioIn();
            PortfolioIn();
        }else if (choice2 == "EXIT"){
            cout << "Have a good day." << endl;
            exit(1);
        }else{
            cout << "Please type in what kink of financial asset you want to analyze:" << endl;
            cout << "You could type 'exit' to exit anytime." << endl;
        }
        cout << "Do you want to continue or exit? ";
        cin >> choice2;
        choice2 = toUpper(choice2);
        if (choice2 == "EXIT"){
            cout << "Have a good day." << endl;
            exit(1);
        }
    }
}

Stock StockIn() {
    string choice;
    cout << "You want to input data yourself or read from file? (A/B) ";
    double InitialPrice, SimulatePeriod, RiskFreeRate, Volatility;
    int StepsYouWant;
    while (choice != "A" & choice != "B" & choice != "exit") {
        cin >> choice;
        if (choice == "A") {
            cout << "What's the volatility: ";
            cin >> Volatility;
        } else if (choice == "B") {
            string ticket;
            Stocks MyStocks;
            cout << "What's the ticket symbol you want to analyze? " ;
            cin >> ticket;
            MyStocks = Stocks(ticket);
            Volatility = MyStocks.HVol();
        } else if (choice == "exit") {
            cout << "Have a good day." << endl;
            exit(1);
        } else {
            cout << "If you want to input data yourself, please type 'A', " << endl;
            cout << "if you need to import data from files, please type 'B'." << endl;
            cout << "You could type 'exit' to exit." << endl;
        }
    }
    cout << "What's the initial stock price: ";
    cin >> InitialPrice;
    cout << "How long you want to simulate (in year): ";
    cin >> SimulatePeriod;
    cout << "What's the risk free rate you want to use: ";
    cin >> RiskFreeRate;
    cout << "How many steps you want use in this simulation: ";
    cin >> StepsYouWant;
    Stock AnalyzeStock(InitialPrice, SimulatePeriod, RiskFreeRate, Volatility, StepsYouWant);
    return AnalyzeStock;
};

Option OptionIn(){
    string choice;
    cout << "You want to price an option or calculate volatility? (A/B) ";
    while (choice != "A" & choice != "B" & choice != "exit") {
        cin >> choice;
        choice = toUpper(choice);
        double Spot, Strike, RiskFreeRate, Volatility, TimeToMature;
        string Type;
        if (choice == "A") {
            int TermsYouWant;
            cout << "Are you analyzing a call option or a put? ";
            cin >> Type;
            cout << "What's the spot price: ";
            cin >> Spot;
            cout << "What's the strike price: ";
            cin >> Strike;
            cout << "What's the risk free rate you want to use: ";
            cin >> RiskFreeRate;
            cout << "What's the volatility: ";
            cin >> Volatility;
            cout << "What's the time to mature in year: ";
            cin >> TimeToMature;
            cout << "How many terms you want in this binomial tree model: ";
            cin >> TermsYouWant;
            Option AnalyzeOption(Type, Strike, Spot, RiskFreeRate, Volatility, TimeToMature, TermsYouWant);
            return AnalyzeOption;
        } else if (choice == "B") {
            double price;
            cout << "Are you analyzing a call option or a put? ";
            cin >> Type;
            cout << "What's the spot price: ";
            cin >> Spot;
            cout << "What's the strike price: ";
            cin >> Strike;
            cout << "What's the risk free rate you want to use: ";
            cin >> RiskFreeRate;
            cout << "What's the time to mature in days: ";
            cin >> TimeToMature;
            cout << "What's the option price? ";
            cin >> price;
            OptionBS MyOptionBS(Type, Spot, Strike, RiskFreeRate, TimeToMature, price);
            cout << "The implied volatility is: " <<  MyOptionBS.getSecantVol() << endl;
        } else if (choice == "EXIT") {
            cout << "Have a good day." << endl;
            exit(1);
        } else {
            cout << "If you want to price an option, please type 'A', " << endl;
            cout << "if you need to calculate volatility, please type 'B'." << endl;
            cout << "You could type 'exit' to exit. " ;
        }
    }
}

Portfolio PortfolioIn(){
    string ticket, choice;
    Portfolio AnalyzePortfolio;
    Stocks tempStock;
    double share;
    int stockNum;
    while (choice != "A" & choice != "B" & choice != "exit"){
        cout << "You want to set shares, or use random weight? (A/B) ";
        cin >> choice;
        choice = toUpper(choice);
        cout << "How many stocks you want in this portfolio? ";
        cin >> stockNum;
        if (choice == "A"){
            while (stockNum > 0){
                cout << "What's the ticket symbol you want to analyze? ";
                cin >> ticket;
                ticket = toUpper(ticket);
                tempStock = Stocks(ticket);
                AnalyzePortfolio.Tickets.insertValue(tempStock);
                cout << "How many shares you want to buy of this stock? ";
                cin >> share;
                AnalyzePortfolio.Shares.insertValue(share);
                stockNum--;
            }
            AnalyzePortfolio.calculate();
            return AnalyzePortfolio;
        }else if (choice == "B"){
            double startAeest;
            cout << "How much starting capital do you prefer? " ;
            cin >> startAeest;
            while (stockNum > 0){
                cout << "What's the ticket symbol you want to analyze? ";
                cin >> ticket;
                ticket = toUpper(ticket);
                tempStock = Stocks(ticket);
                AnalyzePortfolio.Tickets.insertValue(tempStock);
                stockNum--;
            }
            AnalyzePortfolio.calculateWithRandom(startAeest);
            return AnalyzePortfolio;
        }else if (choice == "EXIT"){
            cout << "Have a good day!" << endl;
            exit(1);
        }else{
            cout << "If you want to set shares, please type 'A' " << endl;
            cout << "If you want to use random weight, please type 'B' " << endl;
            cout << "You could type 'exit' to exit. " << endl;
        }
    }
}


string toUpper(string in){
    for (int i = 0; i < in.size(); i++) {
        in[i] = toupper(in[i]);
    }
    return in;
}