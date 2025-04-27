#include "asset.h"

#include "assert.h"

Asset::Asset(std::string currency)
{
    coinValue = { 0, currency };
    sekEquivalent = { 0, "SEK" };
}

void Asset::operator+=(const TransactionAsset& income)
{
    coinValue += income.coinValue;
    sekEquivalent += income.sekEquivalent;
}

void Asset::operator-=(const TransactionAsset& spending)
{
    *this -= spending.coinValue;
}

void Asset::operator-=(const MonetaryValue& spending)
{
    double averageSekValue = getAverageSekValue();
    coinValue -= spending;
    sekEquivalent.amount = coinValue.amount * averageSekValue;
}

MonetaryValue Asset::spend(const TransactionAsset& spending)
{
    double averageSekValue = getAverageSekValue();
    coinValue -= spending.coinValue; // spend

    auto oldSekEquivalent = sekEquivalent;
    sekEquivalent.amount = coinValue.amount * averageSekValue; // preserve same average value

    return oldSekEquivalent - sekEquivalent;
}

double Asset::getAverageSekValue() const
{
    return sekEquivalent.amount / coinValue.amount;
}