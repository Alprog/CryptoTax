#include "monetary_value.h"

#include "assert.h"

void MonetaryValue::operator+=(const MonetaryValue& adding)
{
    assert(adding.currency == currency);
    amount += adding.amount;
}

void MonetaryValue::operator-=(const MonetaryValue& subtracting)
{
    assert(subtracting.currency == currency);
    assert(amount >= subtracting.amount);
    amount -= subtracting.amount;
}

MonetaryValue operator-(const MonetaryValue& lhs, const MonetaryValue& rhs)
{
    assert(lhs.currency == rhs.currency);
    return { lhs.amount - rhs.amount, lhs.currency };
}

std::ostream& operator<<(std::ostream & os, const MonetaryValue & value)
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

