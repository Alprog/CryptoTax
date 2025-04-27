
#include "html.hpp"

#include "transaction_reader.h"
#include "savings.h"
#include "tax_report.h"

import std;

int main()
{
    TransactionReader reader;
    for (int i = 1; i <= 6; i++)
    {
        std::string path = std::format("C:/CryptoTax/WebData/{}.html", i);
        reader.ParseHtmlFile(path);
    }

    TaxReport report;
    Savings savings;
    int i = 0;    
    for (auto& transaction : reader.GetTransactions())
    {
        auto& taxYear = report.GetTaxYear(transaction.getYear());

        transaction.Print();
        std::cout << std::endl;
        auto gain = savings.Perform(transaction, taxYear);
        if (gain.amount != 0)
        {
            std::cout << "                                               " << gain << std::endl;
        }

        savings.RecalculateAverages();
        savings.PrintBalance();

        std::cout << "\n-------------------------------------------------\n\n";
    }
    
    //system("cls");

    report.print();

    
    return 0;
}