#include "transaction_reader.h"

#include "html.hpp"
#include <assert.h>
#include "utils.h"

import std;

void TransactionReader::ParseHtmlFile(std::string path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    ParseHtmlText( buffer.str() );
}

std::vector<Transaction>& TransactionReader::GetTransactions()
{
    return transactions;
}

void TransactionReader::ParseHtmlText(std::string htmlText)
{
    html::parser p;
    html::node_ptr node = p.parse(htmlText);

    std::vector<html::node*> wellLists = node->select("div.well-list");
    assert(wellLists.size() == 1);
    for (auto* wellList : wellLists)
    {
        ParseWellList(wellList);
    }
}

void TransactionReader::ParseWellList(html::node* wellList)
{
    for (auto& node : *wellList)
    {
        if (node->tag_name == "h6")
        {
            ParseDateHeader(node.get());
        }
        else if (node->tag_name == "div")
        {
            ParseWell(node.get());
        }
    }
}

void TransactionReader::ParseDateHeader(html::node* dateHeader)
{
    std::string text = dateHeader->to_text();
    std::istringstream iss(text);
    std::chrono::year_month_day ymd;
    iss >> std::chrono::parse("%b %d, %Y", ymd);
    current_date = ymd;
}

void TransactionReader::ParseWell(html::node* well)
{
    auto& transaction = transactions.emplace_back();

    auto leftColumn = well->at(0);   
    transaction.type = ParseTransactionType( leftColumn->select("div.txn-tag")[0]->to_text() );
    std::string timeString = leftColumn->select("span.pe-auto")[0]->to_text();

    std::istringstream iss(timeString);
    std::chrono::minutes minutes;
    iss >> std::chrono::parse("%I:%M %p", minutes);
    
    transaction.time_point = current_date + minutes;

    auto middleColumn = well->at(1);
    auto subColumns = middleColumn->select("div.media-body");
    transaction.source = ParseTransactionAsset(subColumns.at(0));
    transaction.destination = ParseTransactionAsset(subColumns.at(1));
}

TransactionAsset TransactionReader::ParseTransactionAsset(html::node* div)
{
    TransactionAsset asset;
    
    std::string rows[3];
    for (int i = 0; i < 3; i++)
    {
        rows[i] = div->size() > i ? div->at(i)->to_text() : "";
    }

    if (!rows[0].empty())
    {
        if (rows[0].contains("kr"))
        {
            rows[1] = rows[0];
        }
        else
        {
            asset.wallet = rows[0];
        }
    }

    if (!rows[1].empty())
    {
        asset.coinValue = ParseMonetaryValues(rows[1]);
        if (asset.coinValue.currency == "SEK")
        {
            asset.sekEquivalent = asset.coinValue;
        }
    }

    if (!rows[2].empty())
    {
        asset.sekEquivalent = ParseMonetaryValues(rows[2]);
        assert(asset.sekEquivalent.currency == "SEK");
    }

    return asset;
}

MonetaryValue TransactionReader::ParseMonetaryValues(std::string divText)
{
    std::string EUR = { -30, -126, -84 }; // ˆ
    replace(divText, EUR, "EUR");
    replace(divText, "&nbsp;", "");
    replace(divText, " ", "");
    replace(divText, "+", "");
    replace(divText, "-", "");
    replace(divText, ",", ".");
    replace(divText, "krcost", "SEK");
    replace(divText, "kr", "SEK");
    removeNonAnsi(divText);

    MonetaryValue result;
    result.amount = std::stof(divText);

    constexpr const char* digits = "0123456789.";
    int startIndex = divText.find_first_not_of(digits, 0);
    int endIndex = divText.find_first_of(digits, startIndex);
    int size = endIndex > startIndex ? endIndex - startIndex : -1;
    result.currency = divText.substr(startIndex, size);

    return result;
}
