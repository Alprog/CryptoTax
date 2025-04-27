#pragma once

#include "trade_record.h"

import std;

class TaxYear
{
public:
    explicit TaxYear(int year);

    void add(const TradeRecord& newRecord);
    void print();
    int getYear() const;

private:
    int year;
    std::vector<TradeRecord> records;
};