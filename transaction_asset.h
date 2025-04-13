#pragma once

#include "monetary_value.h"

import std;

struct TransactionAsset
{
    std::string wallet = "*";
    MonetaryValue coinValue;
    MonetaryValue sekEquivalent;
};