#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <string>
#include <vector>
using namespace std;
//
// Created by vladikslon on 2/25/25.
//

struct Stock {
    string stock_symbol;
    string company_name;
    double price;
    double dividend_yield;
    int volume_traded;
};

void loadCSVData(vector<Stock> &stocks);


#endif //DATAMODEL_H
