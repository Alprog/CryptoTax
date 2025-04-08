#pragma once

#include "transaction_type.h"
#include "asset.h"

import std;

struct Transaction
{
    TransactionType type;
    
    Asset source;
    Asset destination;

    std::string time;
};