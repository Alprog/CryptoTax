
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
        std::cout << ToString(transaction.type) << " " << std::endl;
        std::cout << "   " << transaction.time_point << std::endl;
        std::cout << "   " << transaction.source.wallet << " -> " << transaction.destination.wallet << std::endl;
        std::cout << "   " << transaction.source.coinValue << " -> " << transaction.destination.coinValue << std::endl;
        std::cout << "   " << transaction.source.sekEquivalent << " -> " << transaction.destination.sekEquivalent << std::endl;
    }

    return 0;
}