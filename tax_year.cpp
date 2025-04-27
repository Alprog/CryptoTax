#include "tax_year.h"

#include "assert.h"

TaxYear::TaxYear(int year)
    : year{ year }
{
}

void TaxYear::report(const MonetaryValue coinValue, const MonetaryValue& sekCost, const MonetaryValue& sellValue)
{
    assert(coinValue.currency != "SEK");
    assert(sekCost.currency == "SEK");
    assert(sellValue.currency == "SEK");
    TradeRecord record(coinValue.currency, coinValue.amount, sekCost.amount, sellValue.amount);
    if (record.type != DealType::NoChange)
    {
        add(record);
    }
}

void TaxYear::add(const TradeRecord& newRecord)
{
    for (auto& record : records)
    {
        if (record.isCompatible(newRecord))
        {
            record += newRecord;
            return;
        }
    }

    records.emplace_back(newRecord);
}

void TaxYear::print()
{
    std::cout << year << std::endl;

    float totalProfit = 0;
    for (auto& record : records)
    {
        std::cout << record << std::endl;
        totalProfit += record.getProfit();
    }

    std::cout << "total profit: " << totalProfit;
}

int TaxYear::getYear() const
{
    return year;
}
