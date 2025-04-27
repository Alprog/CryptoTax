#pragma once

import std;

struct MonetaryValue
{
    float amount = 0;
    std::string currency;

    void operator+=(const MonetaryValue& adding);
    void operator-=(const MonetaryValue& subtracting);

    friend MonetaryValue operator-(const MonetaryValue& lhs, const MonetaryValue& rhs);
    friend std::ostream& operator<<(std::ostream& os, const MonetaryValue& value);
};