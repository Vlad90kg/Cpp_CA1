#include <iostream>
#include <fstream>
#include <iomanip>
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

void display(vector<Stock> &stocks) {

    cout << left << setw(15) << "Stock Symbol |"
         << left << setw(15) << "Company Name |"
         << right << setw(13) << "Stock price | "
         << right << setw(15) << "Dividend yield |"
         << right << setw(15) << "Volume traded" << endl;
    for (Stock stock : stocks) {
         cout << left << setw(15) << stock.stock_symbol
         << left << setw(15) << stock.company_name
         << right << setw(11) << stock.price
         << right << setw(17) << stock.dividend_yield
         << right << setw(17) << stock.volume_traded << endl;
    }
}

void general() {
    vector<Stock> stocks;
    loadCSVData("../stock_market_data.csv", stocks);


    display(stocks);



}
int main() {
    general();
    return 0;
}