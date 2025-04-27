#pragma once

#include "wallet.h"

import std;

struct Transaction;
class TaxYear;

class Savings
{
public:
    Savings();

    Wallet& GetWallet(std::string name);

    MonetaryValue Perform(Transaction& transaction, TaxYear& taxYear);
    void RecalculateAverages();
    void PrintBalance();

private:
    std::vector<Wallet> wallets;
};