#pragma once

#include "tax_year.h"

class TaxReport
{
public:
    TaxYear& GetTaxYear(int year);

    void print();

private:
    std::vector<TaxYear> taxYears;
};