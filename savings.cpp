#include "savings.h"

#include "transaction.h"
#include "assert.h"

Savings::Savings()
{
    wallets.reserve(100);
}

Wallet& Savings::GetWallet(std::string name)
{
    for (auto& wallet : wallets)
    {
        if (wallet.GetName() == name)
        {
            return wallet;
        }
    }
    return wallets.emplace_back(name);
}

MonetaryValue Savings::Perform(Transaction& transaction)
{
    auto& lhs = transaction.source;
    auto& rhs = transaction.destination;
    
    auto& srcAsset = GetWallet(lhs.walletName).GetAsset(lhs.coinValue.currency);
    auto& dstAsset = GetWallet(rhs.walletName).GetAsset(rhs.coinValue.currency);

    if (transaction.type == TransactionType::Deposit)
    {
        dstAsset += rhs;
        return {};
    }

    if (transaction.type == TransactionType::Buy)
    {
        auto total = srcAsset.coinValue.amount;
        auto spending = lhs.coinValue;
        spending.amount *= (100 + transaction.feePercent) / 100;

        bool spendAll = spending.amount / total > 0.99;
        if (!spendAll)
        {
            assert(false);
        }

        dstAsset.coinValue += rhs.coinValue;
        dstAsset.sekEquivalent += srcAsset.sekEquivalent;
        
        srcAsset.coinValue.amount = 0;
        srcAsset.sekEquivalent.amount = 0;        
        return {};
    }

    if (transaction.type == TransactionType::Sell)
    {
        auto cost = srcAsset.spend(lhs);
        dstAsset += rhs;

        auto gain = rhs.sekEquivalent - cost;
        return gain;
    }

    if (lhs.coinValue.amount > 0)
    {
        srcAsset -= lhs;
    }

    switch (transaction.type)
    {
    case TransactionType::Send:
    case TransactionType::Cost:
    case TransactionType::Withdrawal:
        return {};
    }

    if (rhs.coinValue.amount > 0)
    {
        dstAsset += rhs;
    }   

    return {};
}

void Savings::PrintBalance()
{
    for (auto& wallet : wallets)
    {
        if (!wallet.IsEmpty())
        {
            wallet.PrintBalance();
        }
    }
}
