#pragma once

#include "deal_type.h"

import std;

struct TradeRecord
{
    explicit TradeRecord(std::string currency, float coinAmount, float costValue, float sellAmount);

    std::string currency;
    DealType type;

    float coinAmount;
    float costValue;
    float sellAmount;

    float getProfit() const;
    bool isCompatible(const TradeRecord& other) const;

    void operator +=(const TradeRecord& other);
    friend std::ostream& operator<<(std::ostream& os, const TradeRecord& record);
};