#include <iostream>
#include <fstream>
#include <sstream>

#include "../headers/DataModel.h"



void loadCSVData(const string &filename, vector<Stock> &stocks) {
    ifstream fin(filename);
    if (fin) {

        string header;
        getline(fin, header);
        while (!fin.eof()) {

            string line;

            while (getline(fin, line)) {
                string stock_symbol;
                string company_name;
                double price;
                double dividend_yield;
                int volume_traded;;

                string token;
                istringstream sin(line);

                getline(sin, token, ',');
                stock_symbol = token;

                getline(sin, token, ',');
                company_name = token;

                getline(sin, token, ',');
                price = stod(token);

                getline(sin, token, ',');
                dividend_yield = stod(token);

                getline(sin, token, ',');
                volume_traded = stoi(token);

                Stock stock = {stock_symbol, company_name, price, dividend_yield, volume_traded};
                stocks.push_back(stock);

            }
        }
    }
    fin.close();
}

void general() {
    vector<Stock> stocks;
    loadCSVData("../stock_market_data.csv", stocks);

    cout << "Stock Symbol | Company Name | Stock price | Dividend yield | Volume traded" << endl;

    for (Stock stock : stocks) {
        cout << stock.stock_symbol << " ";
        cout << stock.company_name << " ";
        cout << stock.price << " ";
        cout << stock.dividend_yield << " ";
        cout << stock.volume_traded << endl;
    }
}
int main() {
    general();
    return 0;
}