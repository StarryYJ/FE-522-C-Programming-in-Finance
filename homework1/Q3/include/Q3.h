//
// Created by DELL on 2020/3/7.
//

#ifndef Q3_Q3_H
#define Q3_Q3_H

// For Problem 3:
class Money{
public:
    Money():USD("$0.0"){};
    Money(string moneyAmount);
    Money operator+(Money in);
    Money operator-(Money in);
    Money operator*(int ind);
    Money operator*(double ind);
    Money operator/(int ind);
    Money operator/(double ind);
    bool operator==(const Money &in);
    bool operator==(string in);
    Money operator=(string in);
    Money operator=(Money in);
    void transfer();
    string getValue() const {
        return USD;
    }
    void setValue(string input) {
        USD = input;
    }
    string help;

    string rounding(){
        transfer();
        result = cent;
        dealResult();
    }




private:
    string USD, USDC;
    double cent,result;
    string dealResult();
};

ostream& operator<<(ostream &os, const Money &iObj){
    os << iObj.getValue();
    return (os);
};
istream& operator>>(istream &is, Money &iObj){
    cout << "Please enter your money amount as a string: " << endl;
    is >> iObj.help;
    iObj.setValue(iObj.help);
};


// Below is the details of my functions

Money::Money(string moneyAmount){
    USD = moneyAmount;
}

void Money::transfer() {
    int pos = USD.find(".");
    if (pos == -1) USDC = USD + "00.0";
    else if (USD.size() - pos == 2 ) USDC = USD.substr(1,pos-1) + USD.substr(pos+1) + "0.0";
    else if (USD.size() - pos == 3 ) USDC = USD.substr(1,pos-1) + USD.substr(pos+1) + ".0";
    else if (USD.size() - pos > 3 ) USDC =USD.substr(1,pos-1) + USD.substr(pos+1, 2) + "." + USD.substr(pos+3);
    cent = atof (USDC.c_str());
}
string Money::dealResult(){
    string  output = to_string(result);
    int pos = output.find("."), len = output.size();
    if (pos == - 1) output = output.insert(len-2, ".");
    else if (output.size() - pos >= 2) {
        string temp = output.substr(pos+1, 1);;
        if (int i = atoi(temp.c_str()) >=5 ) result++;
        output = to_string(result).substr(0, pos);
        output.insert(output.size()-2, ".");
    }
    if (output.find(".")==0) output.insert(0,"0");
    output.insert(0,"$");
    return output;
}

Money Money::operator+(Money in){
    transfer();
    in.transfer();
    result = cent + in.cent;
    Money output(dealResult());
    return output;
}
Money Money::operator-(Money in){
    transfer();
    in.transfer();
    result = cent-in.cent;
    Money output(dealResult());
    return output;
}
Money Money::operator*(int ind){
    transfer();
    result = cent*ind;
    Money output(dealResult());
    return output;
}
Money Money::operator*(double ind){
    transfer();
    result = cent*ind;
    Money output(dealResult());
    return output;
}
Money Money::operator/(int ind){
    transfer();
    result = cent/ind;
    Money output(dealResult());
    return output;
}
Money Money::operator/(double ind){
    transfer();
    result = cent/ind;
    Money output(dealResult());
    return output;
}
bool Money::operator==(const Money &in){
    if (USD == in.USD) return true;
    else return false;
}

bool Money::operator==(string in){
    if (USD.c_str() == in) return true;
    else return false;
}
Money Money::operator=(string in){
    USD = in;
    transfer();
};
Money Money::operator=(Money in){
    USD = in.USD;
};





#endif //Q3_Q3_H
