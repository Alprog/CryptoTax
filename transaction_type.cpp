#include "transaction_type.h"

#include "assert.h"

std::vector<std::string> g_TransactionTypeNames = {
    "Unknown",
    "Deposit",
    "Buy",
    "Sell",
    "Exchange",
    "Withdrawal",
    "Send",
    "Transfer",
    "Cost",
    "Airdrop"
};

std::string ToString(TransactionType type)
{
    int index = static_cast<int>(type);
    assert(index >= 0 && index < g_TransactionTypeNames.size());
    return g_TransactionTypeNames[index];
}

TransactionType ParseTransactionType(std::string text)
{
    int count = g_TransactionTypeNames.size();
    for (int i = 0; i < count; i++)
    {
        if (text == g_TransactionTypeNames[i])
        {
            return static_cast<TransactionType>(i);
        }
    }
    return TransactionType::Unknown;
}