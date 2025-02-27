#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <unordered_map>

#include "../headers/DataModel.h"

void display(vector<Stock> &stocks);

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
int returnElementIndex(const vector<Stock> &stocks, const string &company_name) {
    int index = 0;

    for (const auto& stock : stocks) {
        if (stock.company_name == company_name) {
            return index;
        }
        index++;
    }
    return -1;
}

unordered_map<string, int> stockVolumeStatistics(const vector<Stock> &stocks) {
    unordered_map<string, int> statistics;
    string stockVolumeUnder100k;

    for (const auto& stock : stocks) {
        if (stock.volume_traded < 100000) {
            if (statistics.contains("Stocks with volume traded below 100k")) {
                statistics["Stocks with volume traded below 100k"] += 1;
            }else {
                statistics.insert({"Stocks with volume traded below 100k", 1});
            }

        } else if (stock.volume_traded < 500000 && stock.volume_traded >= 100000) {
            if (statistics.contains("Stocks with volume traded between 100k and 500k")) {
                statistics["Stocks with volume traded between 100k and 500k"] += 1;
            } else {
                statistics.insert({"Stocks with volume traded between 100k and 500k", 1});
            }
        } else if (stock.volume_traded >= 500000 && stock.volume_traded < 1000000) {
            if (statistics.contains("Stocks with volume traded between 100k and 500k")) {
                statistics["Stocks with volume traded between 500k and 1kk"] += 1;
            } else {
                statistics.insert({"Stocks with volume traded between 500k and 1kk", 1});
            }
        } else if (stock.volume_traded >= 1000000) {
            if (statistics.contains("Stocks with volume traded over million")) {
                statistics["Stocks with volume traded over million"] += 1;
            } else {
                statistics.insert({"Stocks with volume traded over million", 1});
            }
        }
    }
    return statistics;
}

void displaySubset(const vector<Stock> &stocks, const double &desired_price) {
    bool found = false;
    vector<Stock> subset;
    for (const auto& stock : stocks) {
        if (stock.price <= desired_price) {
            found = true;
            subset.push_back(stock);
        }
    }
    if (found) {
        cout << "Stocks with price equal to desired or less are below:" << endl;
        display(subset);
    }
}
void display(vector<Stock> &stocks) {

    cout << left << setw(15) << "Stock Symbol |"
         << left << setw(15) << "Company Name |"
         << right << setw(13) << "Stock price | "
         << right << setw(15) << "Dividend yield |"
         << right << setw(15) << "Volume traded" << endl;
    for (const Stock& stock : stocks) {
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
    int companyNameIndex = returnElementIndex(stocks, "Katz");
    cout << "Company Name: " << companyNameIndex << endl;
    unordered_map<string, int> statistics = stockVolumeStatistics(stocks);
    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        cout << it->first << " | " << it->second << endl;
    }

    cout << "Enter the price: " << endl;
    double price;
    cin >> price;
    displaySubset(stocks, price);

}
int main() {
    general();
    return 0;
}