#pragma once

#include "transaction_type.h"
#include "transaction_asset.h"

import std;

struct Transaction
{
    explicit Transaction(int index);

    int index;

    TransactionType type;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> time_point;
    
    TransactionAsset source;
    TransactionAsset destination;

    std::string time;
    float feePercent;

    MonetaryValue GetSourceFeeValue() const;
    MonetaryValue GetFeeSekValue() const;
    void Print();
};