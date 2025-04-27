#pragma once

#include "wallet.h"

import std;

struct Transaction;

class Savings
{
public:
    Savings();

    Wallet& GetWallet(std::string name);

    MonetaryValue Perform(Transaction& transaction);
    void RecalculateAverages();
    void PrintBalance();

private:
    std::vector<Wallet> wallets;
};