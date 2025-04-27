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

    if (transaction.type == TransactionType::Sell || transaction.type == TransactionType::Exchange)
    {
        auto cost = srcAsset.spend(lhs);
        dstAsset += rhs;

        auto gain = rhs.sekEquivalent - cost;
        return gain;
    }

    if (transaction.type == TransactionType::Send)
    {
        auto cost = srcAsset.spend(lhs);
        auto gain = rhs.sekEquivalent - cost;
        return gain;
    }

    if (transaction.type == TransactionType::Transfer)
    {
        double averageSekValue = srcAsset.getAverageSekValue();

        auto cost = srcAsset.spend(lhs);
        
        dstAsset.coinValue += rhs.coinValue;
        
        auto receiveSekAmount = rhs.coinValue.amount * averageSekValue;
        dstAsset.sekEquivalent += MonetaryValue(receiveSekAmount, "SEK");

        return {};
    }

    if (transaction.type == TransactionType::Withdrawal)
    {
        srcAsset -= lhs;
        return {};
    }

    if (lhs.coinValue.amount > 0)
    {
        srcAsset -= lhs;
    }

    switch (transaction.type)
    {
    case TransactionType::Cost:
        return {};
    }

    if (rhs.coinValue.amount > 0)
    {
        dstAsset += rhs;
    }   

    return {};
}

void Savings::RecalculateAverages()
{
    Wallet globalWallet("global");
    for (auto& wallet : wallets)
    {
        for (auto& asset : wallet.GetAssets())
        {
            if (asset.coinValue.amount != 0)
            {
                globalWallet.GetAsset(asset.GetCurrency()).coinValue += asset.coinValue;
                globalWallet.GetAsset(asset.GetCurrency()).sekEquivalent += asset.sekEquivalent;
            }
        }
    }
    
    for (auto& wallet : wallets)
    {
        for (auto& asset : wallet.GetAssets())
        {
            if (asset.coinValue.amount != 0)
            {
                auto sekAverage = globalWallet.GetAsset(asset.GetCurrency()).getAverageSekValue();
                asset.SetAverageSekValue(sekAverage);
            }
        }
    }
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
