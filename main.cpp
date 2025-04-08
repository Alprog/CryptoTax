
#include "html.hpp"

#include "transaction_reader.h"

import std;


int main()
{
    TransactionReader reader;
    for (int i = 1; i <= 6; i++)
    {
        std::string path = std::format("C:/CryptoTax/WebData/{}.html", i);
        reader.ParseHtmlFile(path);
    }

    auto& transactions = reader.GetTransactions();
    int i = 1;
    for (auto transaction : transactions)
    {
        std::cout << i++ << " ";
        std::cout << ToString(transaction.type) << std::endl;
    }

    return 0;
}