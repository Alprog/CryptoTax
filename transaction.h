#pragma once

#include "transaction_type.h"

import std;

struct Transaction
{
    TransactionType type;

    std::string time;
};