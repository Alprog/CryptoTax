#include "transaction.h"

Transaction::Transaction(int index)
    : index{ index }
{
}

MonetaryValue Transaction::GetSourceFeeValue() const
{
    auto value = source.coinValue;
    value.amount = value.amount * feePercent / 100;
    return value;
}

MonetaryValue Transaction::GetFeeSekValue() const
{
    auto value = destination.sekEquivalent;
    value.amount = value.amount * feePercent / 100;
    return value;
}

void Transaction::Print()
{
    std::cout << index << " ";
    std::cout << ToString(type) << " " << std::endl;
    std::cout << "   " << time_point << std::endl;
    std::cout << "   " << source.walletName << " -> " << destination.walletName << std::endl;
    std::cout << "   " << source.coinValue << " -> " << destination.coinValue << std::endl;
    std::cout << "   " << source.sekEquivalent << " -> " << destination.sekEquivalent << std::endl;
    if (feePercent != 0)
    {
        std::cout << "   fee: " << GetSourceFeeValue() << " (" << feePercent << "%)" << std::endl;
    }
}