#pragma once

#include "tax_year.h"

class TaxReport
{
public:
    TaxYear& GetTaxYear(int year);

private:
    std::vector<TaxYear> taxYears;
};