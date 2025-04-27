
#include "trade_record.h"

#include "assert.h"

DealType GetDealType(float gainValue)
{
    if (gainValue > 0)
    {
        return DealType::Profit;
    }
    else if (gainValue < 0)
    {
        return DealType::Loss;
    }
    else
    {
        return DealType::NoChange;
    }
}

TradeRecord::TradeRecord(std::string currency, float coinAmount, float costValue, float sellAmount)
    : currency{ currency }
    , coinAmount{ coinAmount }
    , costValue{ costValue }
    , sellAmount{ sellAmount }
{
    type = GetDealType(getProfit());
}

float TradeRecord::getProfit() const
{
    return sellAmount - costValue;
}

bool TradeRecord::isCompatible(const TradeRecord& other) const
{
    return currency == other.currency && type == other.type;
}

void TradeRecord::operator+=(const TradeRecord& other)
{
    assert(isCompatible(other));
    coinAmount += other.coinAmount;
    costValue += other.costValue;
    sellAmount += other.sellAmount;
}

std::ostream& operator<<(std::ostream& os, const TradeRecord& r)
{
    constexpr const char* fmt = "sell {} {} ({} sek) for {} sek | profit/loss: {}";
    os << std::format(fmt, r.coinAmount, r.currency, r.costValue, r.sellAmount, r.getProfit());
    return os;
}
