#include "transaction_reader.h"

#include "html.hpp"
#include <assert.h>

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
    std::string date = dateHeader->to_text();
}

void TransactionReader::ParseWell(html::node* well)
{
    auto& transaction = transactions.emplace_back();

    auto leftColumn = well->at(0);   
    transaction.type = ParseTransactionType( leftColumn->select("div.txn-tag")[0]->to_text() );
    std::string time = leftColumn->select("span.pe-auto")[0]->to_text();

    auto middleColumn = well->at(1);
    auto subColumns = middleColumn->select("div.media-body");
    transaction.source = ParseAsset(subColumns.at(0));
    transaction.destination = ParseAsset(subColumns.at(1));
}

Asset TransactionReader::ParseAsset(html::node* div)
{
    Asset asset;

    if (div->size() > 0)
    {
        asset.wallet = div->at(0)->to_text();
    }

    if (div->size() > 2)
    {
        asset.currency = div->at(1)->to_text();
    }

    //auto selected = div->select("div.mb-1");

    //if (selected.size() > 0)
    //{
    //    asset.wallet = selected.at(0)->to_text();
    //}
    //else
    //{
    //    asset.wallet = "X";
    //}
    
    return asset;

    // std::string sum = dstColumn->select("span.pe-auto")[0]->to_text();
}