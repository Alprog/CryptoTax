#pragma once

#include "asset.h"

import std;

class Wallet
{
public:
    explicit Wallet(std::string name);

    std::string GetName() const;
    Asset& GetAsset(std::string currency);
    void PrintBalance() const;
    bool IsEmpty() const;

private:
    std::string name;
    std::vector<Asset> assets;
};