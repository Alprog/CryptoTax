#include "tax_report.h"

TaxYear& TaxReport::GetTaxYear(int year)
{
    for (auto& taxYear : taxYears)
    {
        if (taxYear.getYear() == year)
        {
            return taxYear;
        }
    }
    return taxYears.emplace_back(year);
}

void TaxReport::print()
{
    for (auto& taxYear : taxYears)
    {
        taxYear.print();
        std::cout << std::endl;
    }
}
