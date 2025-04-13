#pragma once

import std;

struct MonetaryValue
{
    float amount = 0;
    std::string currency;

    friend std::ostream& operator<<(std::ostream& os, const MonetaryValue& value) 
    {
        if (value.currency.empty())
        {
            os << "*";
        }
        else
        {
            os << value.amount << " " << value.currency;
        }
        return os;
    }
};