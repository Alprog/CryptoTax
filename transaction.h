#pragma once

#include "transaction_type.h"
#include "transaction_asset.h"

import std;

struct Transaction
{
    TransactionType type;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> time_point;
    
    TransactionAsset source;
    TransactionAsset destination;

    std::string time;
};