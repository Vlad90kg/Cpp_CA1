#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <list>
#include <sstream>
#include <unordered_map>

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

void displayStock(const Stock &stock) {
    cout << left << setw(15) << stock.stock_symbol
         << left << setw(15) << stock.company_name
         << right << setw(11) << stock.price
         << right << setw(17) << stock.dividend_yield
         << right << setw(17) << stock.volume_traded << endl;

}

void displayTitle() {
    cout << left << setw(15) << "Stock Symbol |"
         << left << setw(15) << "Company Name |"
         << right << setw(13) << "Stock price | "
         << right << setw(15) << "Dividend yield |"
         << right << setw(15) << "Volume traded" << endl;
}
void display(vector<Stock> &stocks) {
    displayTitle();
    for (const Stock& stock : stocks) {
        displayStock(stock);
    }
}


minMaxAvg minMaxAverage(const vector<Stock> &stocks) {
    int min = numeric_limits<int>::max(), max = numeric_limits<int>::min(),  avg = 0;
    Stock minStock, maxStock;
    for (const Stock& stock : stocks) {
        if (stock.volume_traded < min) {
            min = stock.volume_traded;
        } else if (stock.volume_traded > max) {
            max = stock.volume_traded;
        }
        avg += stock.volume_traded;
    }

    for (const Stock& stock : stocks) {
        if (stock.volume_traded == min) {
            minStock = stock;
        }else if (stock.volume_traded == max) {
            maxStock = stock;
        }
    }
    avg /= static_cast<int>(stocks.size());
    minMaxAvg min_max_avg = {minStock, maxStock,avg};
    return  min_max_avg;
};

void displayMinMaxAvg(const minMaxAvg &min_max_avg) {
    displayTitle();
    cout << "The least traded stock:" << endl;
    displayStock(min_max_avg.min);
    cout << "The most traded stock:" << endl;
    displayStock(min_max_avg.max);
    cout << "Average: " << min_max_avg.average << endl;
}
list<Stock> returnMatchingStocks(const vector<Stock> &stocks, const string &stock_symbol_input) {
    list<Stock> matching_stocks;
    for (auto it = stocks.begin(); it != stocks.end(); ++it) {
        if ((it ->stock_symbol).find(stock_symbol_input) != string::npos) {
            matching_stocks.push_back(*it);
        }
    }
    return matching_stocks;
}
void displayInDescOrder(vector<Stock> stocks) {
    ranges::sort(stocks, [](const Stock &stock1, const Stock &stock2) {return stock1.price > stock2.price;});
    display(stocks);
}
void general() {
    vector<Stock> stocks;
    loadCSVData("../stock_market_data.csv", stocks);
    bool exit = false;
    bool toMenu = false;
    char option;
    cout <<"Stock Market Data Application Menu" << endl;
    do {
        cout << "1. Display All Stocks" << endl;
        cout << "2. Search by Company Name" << endl;
        cout << "3. Stock Volume Statistics" << endl;
        cout << "4. Filter Stocks by Price" << endl;
        cout << "5. Min, Max, & Average Volume" << endl;
        cout << "6. Find Stocks by Stock Symbol" << endl;
        cout << "7. Display Stocks Sorted Descending by Price" << endl;
        cout << "8. Exit" << endl;
        cin >> option;
        switch ( option) {

            case '1':
                display(stocks);

                do {
                    cout << "1. Back to main menu." << endl;
                    cout << "2. Exit." << endl;
                    cin >> option;
                    switch (option) {
                        case '1':
                            toMenu = true;
                            break;
                        case '2':
                            exit = true;
                            break;
                        default:
                            cout << "Invalid option" << endl;
                    }
                } while (!exit && !toMenu);

                break;
            case '2': {
                string company;
                cout << "Enter Company Name: ";
                // Clear the newline from previous input
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, company);
                int index = returnElementIndex(stocks, company);
                if (index != -1)
                    cout << "Company found at index: " << index << endl;
                else
                    cout << "Company not found." << endl;
                break;
            }
            case '3': {
                unordered_map<string, int> stats = stockVolumeStatistics(stocks);
                for (const auto &entry : stats) {
                    cout << entry.first << " | " << entry.second << endl;
                }
                break;
            }
            case '4': {
                double price;
                cout << "Enter maximum desired price: ";
                cin >> price;
                displaySubset(stocks, price);
                break;
            }
            case '5': {
                minMaxAvg result = minMaxAverage(stocks);
                displayMinMaxAvg(result);
                break;
            }
            case '6': {
                string symbol;
                cout << "Enter stock symbol (or part of it) to search: ";
                cin >> symbol;
                list<Stock> matchingStocks = returnMatchingStocks(stocks, symbol);
                if (matchingStocks.empty()) {
                    cout << "No matching stocks found." << endl;
                } else {
                    for (const auto &stock : matchingStocks) {
                        displayStock(stock);
                    }
                }
                break;
            }
            case '7':
                displayInDescOrder(stocks);
                break;
            case '8':
                cout << "Exiting application." << endl;
                break;
            default:
                cout << "Invalid option, please try again." << endl;
        }
    }while (!exit);


    // display(stocks);
    // const int companyNameIndex = returnElementIndex(stocks, "Katz");
    // cout << "Company Name: " << companyNameIndex << endl;
    // unordered_map<string, int> statistics = stockVolumeStatistics(stocks);
    // for (auto &[first, second] : statistics) {
    //     cout << first << " | " << second << endl;
    // }
    //
    // cout << "Enter the price: " << endl;
    // double price;
    // cin >> price;
    // displaySubset(stocks, price);
    // minMaxAvg min_max_avg = minMaxAverage(stocks);
    // displayMinMaxAvg(min_max_avg);
    //
    // cout << "Input capital letters next line to find the stocks with matching stock symbols: " << endl;
    // string stock_symbol_input;
    // cin >> stock_symbol_input;
    // list<Stock> matching_stocks = returnMatchingStocks(stocks, stock_symbol_input);
    // displayTitle();
    // if (!matching_stocks.empty()) {
    //     for (Stock& stock : matching_stocks) {
    //         displayStock(stock);
    //     }
    // } else {
    //     cout << "No matching stocks found" << endl;
    // }
    //
    // displayInDescOrder(stocks);

}
int main() {
    general();
    return 0;
}