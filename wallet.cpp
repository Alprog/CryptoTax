#include "wallet.h"

Wallet::Wallet(std::string name)
    : name{name}
{
    assets.reserve(100);
}

std::string Wallet::GetName() const
{
    return name;
}

Asset& Wallet::GetAsset(std::string currency)
{
    for (auto& asset : assets)
    {
        if (asset.coinValue.currency == currency)
        {
            return asset;
        }
    }
    return assets.emplace_back(currency);
}

void Wallet::PrintBalance() const
{
    std::cout << "Wallet: " << name << std::endl;

    for (auto& asset : assets)
    {
        if (asset.coinValue.amount > 0)
        {
            std::cout << "  " << asset.coinValue;
            std::cout << " (" << asset.sekEquivalent << ")";
            std::cout << " av. " << asset.getAverageSekValue() << std::endl;
        }
    }
}

bool Wallet::IsEmpty() const
{
    for (auto& asset : assets)
    {
        if (asset.coinValue.amount > 0)
        {
            return false;
        }
    }
    return true;
}