#pragma once

#include "trade_record.h"
#include "monetary_value.h"

import std;

class TaxYear
{
public:
    explicit TaxYear(int year);

    void report(const MonetaryValue coinValue, const MonetaryValue& sekCost, const MonetaryValue& sellValue);

    void add(const TradeRecord& newRecord);
    void print();
    int getYear() const;

private:
    int year;
    std::vector<TradeRecord> records;
};