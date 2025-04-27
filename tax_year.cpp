#include "tax_year.h"

TaxYear::TaxYear(int year)
    : year{ year }
{
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
