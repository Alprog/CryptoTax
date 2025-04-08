#pragma once

import std;

enum TransactionType
{
    Unknown,
    Deposit, 
    Buy,
    Sell,
    Exchange,
    Withdrawal,
    Send,
    Transfer,
    Cost,
    Airdrop,
};

std::string ToString(TransactionType type);
TransactionType ParseTransactionType(std::string text);

