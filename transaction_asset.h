#pragma once

#include "monetary_value.h"

import std;

struct TransactionAsset
{
    std::string walletName = "*";
    MonetaryValue coinValue;
    MonetaryValue sekEquivalent;
};