#pragma once

#include "monetary_value.h"
#include "transaction_asset.h"

import std;

struct Asset
{
    explicit Asset(std::string currency);

    void operator+=(const TransactionAsset& income);
    void operator-=(const TransactionAsset& spending);
    void operator-=(const MonetaryValue& spending);

    MonetaryValue spend(const TransactionAsset& spending); // return sek cost of spending

    double getAverageSekValue() const;

    MonetaryValue coinValue;
    MonetaryValue sekEquivalent;
};